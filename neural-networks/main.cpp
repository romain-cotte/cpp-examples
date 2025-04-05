/**
 * Neural networks
 *
 * see http://neuralnetworksanddeeplearning.com/chap1.html
 */
#include <algorithm>
#include <assert.h>
#include <bitset>
#include <chrono>
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

default_random_engine generator;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
normal_distribution<double> norm_dist(0.0, 1.0);


uint32_t read_uint32(ifstream &file) {
  uint8_t bytes[4];
  file.read(reinterpret_cast<char*>(bytes), 4);
  return (bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | bytes[3];
}

struct Data {
  uint32_t n, height, width;
  vector<vector<uint8_t>> images;
  vector<uint8_t> labels;

  Data(int _n, int _height, int _width) : n(_n), height(_height), width(_width) {
    images.assign(n, vector<uint8_t>(height * width));
    labels.assign(n, 0);
  }

  void print(int i) {
    cout << "Label: " << +labels[i] << endl;
    for (uint32_t y = 0; y < height; ++y) {
      for (uint32_t x = 0; x < width; ++x) {
          cout << (images[i][y * width + x] > 128 ? '#' : '.');
          // cout << (int)images[0][y * width + x] << " ";
      }
      cout << endl;
    }
  }

};

Data *read_idx3_ubyte(string name) {
  string images_filename = "data/" + name + "-images.idx3-ubyte";
  string labels_filename = "data/" + name + "-labels.idx1-ubyte";

  ifstream images_file(images_filename, ios::binary);
  if (!images_file.is_open()) {
    std::cerr << "Error: impossible to open the images_file" << std::endl;
    return nullptr;
  }

  uint32_t magic_number = read_uint32(images_file);
  uint32_t num_images = read_uint32(images_file);
  uint32_t height = read_uint32(images_file);
  uint32_t width = read_uint32(images_file);

  Data *data = new Data(num_images, height, width);

  assert(magic_number == 0x00000803);
  cout << "Number of images: " << num_images << endl;
  cout << "Dimensions: " << height << "x" << width << endl;

  for (uint32_t i = 0; i < num_images; ++i) {
    images_file.read(reinterpret_cast<char*>(data->images[i].data()), height * width);
  }
  images_file.close();

  ifstream labels_file(labels_filename, ios::binary);
  if (!labels_file.is_open()) {
    std::cerr << "Error: impossible to open the file" << std::endl;
    return nullptr;
  }

  uint32_t num_labels = 0;
  magic_number = read_uint32(labels_file);
  num_labels = read_uint32(labels_file);
  assert(magic_number == 0x00000801);
  assert(num_labels == num_images);

  labels_file.read(reinterpret_cast<char*>(data->labels.data()), num_labels);
  labels_file.close();

  return data;
}


template<class T>
vector<T> operator+(const vector<T>& a, const vector<T>& b) {
  size_t n = a.size();
  assert(n == b.size());
  vector<T> r(n);
  for (size_t i = 0; i < n; ++i) {
    r[i] = a[i] + b[i];
  }
  return r;
}

template<class T>
T dot(const vector<T>& a, const vector<T>& b) {
  size_t n = a.size();
  assert(n == b.size());
  T r = 0;
  for (size_t i = 0; i < n; ++i) {
    r += a[i] * b[i];
  }
  return r;
}

template<class T = float>
vector<T> dot(const vector<vector<T>>& m, const vector<T>& a) {
  int nl = m.size();
  assert(nl >= 1);
  int nc = m[0].size();
  assert(nc == (int)a.size());
  vector<T> r(nl);
  for (int l = 0; l < nl; ++l) {
    r[l] = dot(m[l], a);
    // for (int c = 0; c < nc; ++c) {
    //   r[l] += m[l][c] * a[c];
    // }
  }
  return r;
}


template<class T>
vector<T> sigmoid(const vector<T> &a) {
  int n = a.size();
  vector<T> r(n);
  for (int i = 0; i < n; ++i) {
    r[i] = 1 / (1 + exp(-a[i]));
  }
  return r;
}

template<class T>
vector<T> sigmoid_prime(const vector<T> &a) {
  // sigmoid(a) * (1 - sigmoid(a));
  int n = a.size();
  vector<T> r(n);
  for (int i = 0; i < n; ++i) {
    T e = exp(-a[i]);
    r[i] = e/((1+e)*(1+e));
  }
  return r;
}


template<class T = float>
struct Network {
  int m;
  vector<vector<T>> biases;
  vector<vector<vector<T>>> weights;
  vector<int> layer_sizes;

  Network(vi _layer_sizes) {
    layer_sizes = _layer_sizes;
    m = layer_sizes.size() - 1;
    for (int i = 1; i < (int)layer_sizes.size(); ++i) {
      size_t sz = layer_sizes[i];
      size_t szp = layer_sizes[i-1];
      vector<T> v(sz);
      generate(v.begin(), v.end(), [&]() {
        return norm_dist(rng);
      });
      biases.push_back(v);
      vector<vector<T>> wi(sz, vector<T>(szp));
      for (size_t j = 0; j < sz; ++j) {
        for (size_t k = 0; k < szp; ++k) {
          wi[j][k] = norm_dist(rng);
        }
      }
      weights.push_back(wi);
    }
    // ps(biases);
    // ps(weights);
  }

  vector<T> feed_forward(vector<T> a) {
    // a' = σ(w.a+b)
    for (int i = 0; i < m; ++i) {
      // ps("::", biases[i], weights[i]);
      a = sigmoid(dot(weights[i], a) + biases[i]);
    }
    return a;
  }

  void SGD(Data *data, int epochs, int mini_batch_size, float eta, Data *test_data) {
    /*
      Stochastic Gradient Descent
      epochs          = number of steps
      mini_batch_size = sample size for the stochastic gradient descent
      eta             = learning rate
    */
    int n = data->n;
    for (int ep = 0; ep < epochs; ++ep) {
      vi ind(n); iota(ind.begin(), ind.end(), 0);
      shuffle(ind.begin(), ind.end(), rng);

      for (int i = 0; i < n; i += mini_batch_size) {
        vi cur = {};
        for (int k = 0; k < mini_batch_size; ++k) {
          cur.push_back(ind[i+k]);
        }
        update_mini_batch(data, cur, eta);
      }
      if (test_data != nullptr) {
        evaluate(test_data);
      }
    }

  }

  int evaluate(Data *data) {
    int cnt = 0;
    for (int i = 0; i < (int)data->n; ++i) {
      vector<float> input;
      for (uint8_t x: data->images[i]) {
        input.push_back(x);
      }
      auto a = feed_forward(input);
      float mx = -1E9;
      int evaluation = -1;
      for (int i = 0; i < (int)a.size(); ++i) {
        if (a[i] > mx) {
          mx = a[i];
          evaluation = i;
        }
      }
      if (evaluation == data->labels[i]) ++cnt;
    }
    ps(cnt, "/", data->n);
    return cnt;
  }

  void update_mini_batch(Data *data, const vi &ind, float eta) {
    vector<vector<T>> new_biases(biases.size(), vector<T>(biases[0].size()));
    vector<vector<vector<T>>> new_weights(
      weights.size(),
      vector<vector<T>>(weights[0].size(), vector<T>(weights[0][0].size()))
    );
    for (int i = 0; i < (int)ind.size(); ++i) {
      // vector<uint8_t> data->images[i] => (uint8_t) data->labels[i]

    }
  }

  void backprop(Data *data, int i) {
    // data->images[i] should have label data->labels[i]

    vector<vector<T>> nabla_b(biases.size(), vector<T>(biases[0].size()));

    ps("sizes", weights.size(), weights[0].size(), weights[0][0].size());

    vector<vector<vector<T>>> nabla_w(
      weights.size(),
      vector<vector<T>>(weights[0].size(), vector<T>(weights[0][0].size()))
    );
    ps(nabla_b, nabla_w);

  }

};



int main(int argc, const char **argv) {
#ifndef DEBUG_LOCAL
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#endif

  clock_t t_clock = clock();



  const string train_name = "train";
  Data *training_data = read_idx3_ubyte(train_name);
  const string t10k_name = "t10k";
  Data *validation_data = read_idx3_ubyte(t10k_name);


  for (int i = 90; i < 100; ++i) {
    training_data->print(i);
  }

  // {
  //   vector<ld> v = {1, 2, 4, 5, 10};
  //   ps(sigmoid(v));
  //   ps(sigmoid_prime(v));
  // }

  {
    vector<int> layer_sizes = {2, 3, 10};
    Network network(layer_sizes);
    vector<float> a = {1.0, 2.0};
    vector<float> b = {3.0, 4.0};
    ps("a+b", a+b);
    ps("dot a, b", dot(a, b));
    ps(network.feed_forward(a));
  }

  vector<int> layer_sizes = {784, 3, 10};
  Network network(layer_sizes);
  network.evaluate(validation_data);

  network.backprop(training_data, 0);

  fprintf(
    stderr,
    "Time %.3f milliseconds.\n",
    ((float)(clock() - t_clock)/CLOCKS_PER_SEC) * 1000
  );
  return 0;
}
