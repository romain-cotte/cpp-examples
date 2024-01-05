#include <fstream>
#include <iostream>
#include <string>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Infos.hpp>
#include <curlpp/Options.hpp>

#include "point.h"

size_t FileCallback(FILE *f, char* ptr, size_t size, size_t nmemb) {
  return fwrite(ptr, size, nmemb, f);
};

class OpenTopography {
private:
  // see https://stackoverflow.com/a/1563906/4388775
  inline static const std::string _url = "https://portal.opentopography.org/";
  inline static const std::string _demtype = "SRTMGL3";
  inline static const std::string _outputformat = "GTiff";
  inline static const std::string _api_key = "aeccb70d03e3cc52600a0c331f88e06c";

  static std::string _build_coor(Point center, float distance) {
    return "&south=" + std::to_string(center.y - distance) +
      "&north=" + std::to_string(center.y + distance) +
      "&west=" + std::to_string(center.x - distance) +
      "&east=" + std::to_string(center.x + distance);
  }

  static std::string _build_coor(Point upper_left, Point bottom_right) {
    return "&south=" + std::to_string(bottom_right.y) +
      "&north=" + std::to_string(upper_left.y) +
      "&west=" + std::to_string(upper_left.x) +
      "&east=" + std::to_string(bottom_right.x);
  }

  template<class... Args>
  static std::string _build_url(Args&... args) {
    return _url + "API/globaldem?demtype=" + _demtype +
      _build_coor(args...) +
      "&outputFormat=" + _outputformat +
      "&API_Key=" + _api_key;
  }

  static int _make_request(std::string filename, std::string url) {
    printf("requested url: %s\n", url.c_str());
    try {
      // That's all that is needed to do cleanup of used resources (RAII style).
      curlpp::Cleanup myCleanup;

      // Our request to be sent.
      curlpp::Easy request;

      // Set the URL.
      request.setOpt<curlpp::options::Url>(url);

      FILE *file = fopen(filename.c_str(), "w");
      if (!file) {
        std::cerr << "Error opening " << filename << std::endl;
        return EXIT_FAILURE;
      }
      curlpp::options::WriteFunction *test = new curlpp::options::WriteFunction(
        std::bind(
          &FileCallback,
          file,
          std::placeholders::_1,
          std::placeholders::_2,
          std::placeholders::_3
        )
      );
      request.setOpt(test);
      // request.setOpt(new curlpp::options::Verbose(true));

      // Send request and get a result.
      // By default the result goes to standard output.
      request.perform();
      fclose(file);

      int status_code = curlpp::infos::ResponseCode::get(request);
      if (status_code == 200) {
        return EXIT_SUCCESS;
      }

      std::ifstream file_stream(filename);
      std::cout << "An error occurred:" << std::endl;

      if (file_stream.is_open()) {
        std::cout << file_stream.rdbuf();
      }

      return EXIT_FAILURE;
    }

    catch (curlpp::RuntimeError & e) {
      std::cout << e.what() << std::endl;
      return EXIT_FAILURE;
    }

    catch (curlpp::LogicError & e) {
      std::cout << e.what() << std::endl;
      return EXIT_FAILURE;
    }
  }

public:
  static int get(std::string filename, Point upper_left, Point bottom_right) {
    std::string url = _build_url(upper_left, bottom_right);
    return _make_request(filename, url);
  }

  static int get(std::string filename, Point center, float distance) {
    std::string url = _build_url(center, distance);
    return _make_request(filename, url);
  }
};
