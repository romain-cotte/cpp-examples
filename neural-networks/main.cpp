/**
 * Neural networks
 *
 * see http://neuralnetworksanddeeplearning.com/chap1.html
 */
#include <algorithm>
#include <assert.h>
#include <bitset>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <stdio.h>
#include <string>
#include <time.h>
#include <vector>



#define INF 1 << 30      //          1073741824 1E9
#define INF64 1LL << 60  // 1152921504606846976 1E18

using namespace std;

template<class T1, class T2> void pr(const pair<T1,T2>& x);
template<class T, size_t SZ> void pr(const array<T,SZ>& x);
template<class T> void pr(const vector<T>& x);
template<class T> void pr(const deque<T>& x);
template<class T, class C> void pr(const set<T,C>& x);
template<class T, class C> void pr(const multiset<T,C>& x);
template<class T1, class T2> void pr(const map<T1,T2>& x);
template<class... T> void pr(const tuple<T...>& tup);

const string COLOR_RESET = "\033[0m", GREEN = "\033[1;32m";
template<class T> void pr(const T& x) {
#if COLOR == true
  cout << GREEN << x << COLOR_RESET;
#else
  cout << x;
#endif
}

template<class Arg, class... Args> void pr(const Arg& first, const Args&... rest) {
  pr(first); pr(rest...);
}
template<class T1, class T2> void pr(const pair<T1,T2>& x) {
  pr("{",x.first,", ",x.second,"}");
}
template<class T> void prContain(const T& x) {
  pr("{");bool fst = 1; for(auto &a: x) pr(!fst?", ":"",a), fst = 0;pr("}");
}
template<class T, size_t SZ> void pr(const array<T,SZ>& x) { prContain(x); }
template<class T> void pr(const vector<T>& x) { prContain(x); }
template<class T> void pr(const deque<T>& x) { prContain(x); }
template<class T, class C> void pr(const set<T,C>& x) { prContain(x); }
template<class T, class C> void pr(const multiset<T,C>& x) { prContain(x); }
template<class T1, class T2> void pr(const map<T1,T2>& x) { prContain(x); }

template<class T, size_t... I>
void pr(const T& tup, index_sequence<I...>) {
  pr("("); (..., (cout << (I == 0? "" : ", ") << get<I>(tup))); pr(")");
}
template<class... T>
void pr (const tuple<T...>& tup) {
  pr(tup, make_index_sequence<sizeof...(T)>());
}
void ps() { pr("\n"); }
void _ps_continue() { pr("\n"); }
template<class Arg, class... Args> void _ps_continue(const Arg& first, const Args&... rest) {
  pr(" ", first); _ps_continue(rest...);
}

#ifdef DEBUG_LOCAL
template<class Arg, class... Args> void ps(const Arg& first, const Args&... rest) {
  pr(first); _ps_continue(rest...);
}
#else
template<class Arg, class... Args> void ps(const Arg& first, const Args&... rest) {}
#endif

template<typename T> int remin(T& a,const T& b){if(b<a){a=b;return true;}return false;}
template<typename T> int remax(T& a,const T& b){if(a<b){a=b;return true;}return false;}

typedef vector<int> vi;
typedef long long ll;
typedef long double ld;
typedef vector<vi> vvi;
typedef pair<int, int> ii;
typedef vector<ii> vii;



uint32_t read_uint32(ifstream &file) {
  uint8_t bytes[4];
  file.read(reinterpret_cast<char*>(bytes), 4);
  return (bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | bytes[3];
}

struct Neuron {
  int id;
  long double activation = 0;
  long double threshold = 0;
  Neuron(int _id = 42) : id(_id) {}
  ~Neuron() { printf("Delete\n"); }
};

struct Images {
  uint32_t n, height, width;
  vector<vector<uint8_t>> data;
  Images(int _n, int _height, int _width) : n(_n), height(_height), width(_width) {
    data.assign(n, vector<uint8_t>(height * width));
  }
};

Images *read_idx3_ubyte(string filename) {
  ifstream file(filename, ios::binary);
  if (!file.is_open()) {
    std::cerr << "Error: impossible to open the file" << std::endl;
    return nullptr;
  }

  uint32_t magic_number = read_uint32(file);
  uint32_t num_images = read_uint32(file);
  uint32_t height = read_uint32(file);
  uint32_t width = read_uint32(file);

  Images *images = new Images(num_images, height, width);

  assert(magic_number == 0x00000803);
  cout << "Number of images: " << num_images << endl;
  cout << "Dimensions: " << height << "x" << width << endl;

  for (uint32_t i = 0; i < num_images; ++i) {
    file.read(reinterpret_cast<char*>(images->data[i].data()), height * width);
  }
  file.close();
  return images;
}



int main(int argc, const char **argv) {
#ifndef DEBUG_LOCAL
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#endif

  const std::string filename = "t10k-images.idx3-ubyte";
  Images *images = read_idx3_ubyte(filename);

  for (uint32_t y = 0; y < images->height; ++y) {
    for (uint32_t x = 0; x < images->width; ++x) {
        // cout << (image_data[0][y * img_width + x] > 128 ? '#' : '.') << " ";
        cout << (int)images->data[0][y * images->width + x] << " ";
    }
    cout << endl;
  }

  return 0;
}


