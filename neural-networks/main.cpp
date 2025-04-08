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

template <class T>
struct Data {
  uint32_t n, m;
  vector<vector<T>> content;
  vector<int> labels;
  Data(int _n, int _m) : n(_n), m(_m) {
    content.assign(n, vector<T>(m));
    labels.assign(n, 0);
  }
  Data(vector<vector<T>> _content, vector<int> _labels) {
    n = _content.size();
    m = _content[0].size();
    content = _content;
    labels = _labels;
  }

  // void print(int i, int height, int width) {
  //   cout << "Label: " << labels[i] << endl;
  //   for (uint32_t y = 0; y < height; ++y) {
  //     for (uint32_t x = 0; x < width; ++x) {
  //         cout << (content[i][y * width + x] > 128 ? '#' : '.');
  //         // cout << (int)content[0][y * width + x] << " ";
  //     }
  //     cout << endl;
  //   }
  // }

};


template <class T>
Data<T> *read_idx3_ubyte(string name) {
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

  Data<T> *data = new Data<T>(num_images, height * width);

  assert(magic_number == 0x00000803);
  cout << "Number of images: " << num_images << endl;
  cout << "Dimensions: " << height << "x" << width << endl;

  for (uint32_t i = 0; i < num_images; ++i) {

    vector<uint8_t> buffer(height * width);
    images_file.read(reinterpret_cast<char*>(buffer.data()), height * width);
    transform(buffer.begin(), buffer.end(), data->content[i].begin(),
              [](uint8_t val) { return static_cast<T>(val); });
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

  {
    vector<uint8_t> buffer(num_images);
    labels_file.read(reinterpret_cast<char*>(buffer.data()), num_images);
    transform(buffer.begin(), buffer.end(), data->labels.begin(),
              [](uint8_t val) { return static_cast<int>(val); });
  }
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
vector<T> operator*(const vector<T>& a, const vector<T>& b) {
  size_t n = a.size();
  assert(n == b.size());
  vector<T> r(n);
  for (size_t i = 0; i < n; ++i) {
    r[i] = a[i] * b[i];
  }
  return r;
}


template<class T>
T dot_scalar(const vector<T>& a, const vector<T>& b) {
  // see if we remove or keep the *
  size_t n = a.size();
  assert(n == b.size());
  T r = 0;
  for (size_t i = 0; i < n; ++i) {
    r += a[i] * b[i];
  }
  return r;
}

template<class T>
vector<T> dot(const vector<T>& a, const vector<T>& b) {
  size_t n = a.size();
  assert(n == b.size());
  vector<T> r(n);
  for (size_t i = 0; i < n; ++i) {
    r[i] = a[i] * b[i];
  }
  return r;
}

template<class T>
vector<T> dot(const vector<vector<T>>& m, const vector<T>& a) {
  int nl = m.size();
  assert(nl >= 1);
  int nc = m[0].size();
  assert(nc == (int)a.size());
  vector<T> r(nl);
  for (int l = 0; l < nl; ++l) {
    r[l] = dot_scalar(m[l], a);
    // for (int c = 0; c < nc; ++c) {
    //   r[l] += m[l][c] * a[c];
    // }
  }
  return r;
}


template<class T>
vector<vector<T>> dot_nm(const vector<T>& a, const vector<T>& b) {
  int na = a.size(); int nb = b.size();

  vector<vector<T>> r(na, vector<T>(nb));
  for (int i = 0; i < na; ++i) {
    for (int j = 0; j < nb; ++j) {
      r[i][j] = a[i] * b[j];
    }
  }
  return r;
}


template<class T>
vector<vector<T>> transpose(const vector<vector<T>>& mat) {
  int n = mat.size(); int m = mat[0].size();
  vector<vector<T>> r(m, vector<T>(n));
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      r[i][j] = mat[j][i];
    }
  }
  return r;
}

float sigmoid(float x) {
  return 1 / (1 + expf(-x));
}
double sigmoid(double x) {
  return 1 / (1 + exp(-x));
}
long double sigmoid(long double x) {
  return 1 / (1 + expl(-x));
}


template<class T>
vector<T> sigmoid(const vector<T> &a) {
  int n = a.size();
  vector<T> r(n);
  for (int i = 0; i < n; ++i) {
    r[i] = sigmoid(a[i]);
  }
  return r;
}

template<class T>
vector<T> sigmoid_prime(const vector<T> &a) {
  // sigmoid(a) * (1 - sigmoid(a));
  int n = a.size();
  vector<T> r(n);
  for (int i = 0; i < n; ++i) {
    r[i] = sigmoid(a[i]) * (1 - sigmoid(a[i]));
  }
  return r;
}


template<class T>
struct Network {
  int L;
  vector<vector<T>> biases, nabla_b, delta_nabla_b;
  vector<vector<vector<T>>> weights, nabla_w, delta_nabla_w;
  vector<int> layer_sizes;

  Network(vi _layer_sizes) {
    layer_sizes = _layer_sizes;
    L = layer_sizes.size() - 1;
    for (int i = 1; i < (int)layer_sizes.size(); ++i) {
      size_t sz = layer_sizes[i];
      size_t szp = layer_sizes[i-1];
      vector<T> v(sz);
      generate(v.begin(), v.end(), [&]() {
        return norm_dist(rng);
        // return 0.1;
      });
      biases.push_back(v);
      vector<vector<T>> wi(sz, vector<T>(szp));
      for (size_t j = 0; j < sz; ++j) {
        for (size_t k = 0; k < szp; ++k) {
          wi[j][k] = norm_dist(rng);
          // wi[j][k] = 0.1;
        }
      }
      weights.push_back(wi);
    }


    nabla_b.assign(biases.size(), vector<T>(biases[0].size()));
    nabla_w.resize(weights.size());
    for (int i = 0; i < L; ++i) {
      nabla_w[i].assign(weights[i].size(), vector<T>(weights[i][0].size()));
    }

    delta_nabla_b.assign(biases.size(), vector<T>(biases[0].size()));
    delta_nabla_w.resize(weights.size());
    for (int i = 0; i < L; ++i) {
      delta_nabla_w[i].assign(weights[i].size(), vector<T>(weights[i][0].size()));
    }
    // ps("biases", biases);
    // ps("weights", weights);
  }

  vector<T> feed_forward(vector<T> a) {
    // a' = σ(w.a+b)
    for (int i = 0; i < L; ++i) {
      a = sigmoid(dot(weights[i], a) + biases[i]);
    }
    return a;
  }

  void SGD(Data<T> *data,
           int epochs,
           int mini_batch_size,
           T eta,
           Data<T> *test_data) {
    /*
      Stochastic Gradient Descent
      epochs          = number of steps
      mini_batch_size = sample size for the stochastic gradient descent
      eta             = learning rate
    */
    int n = data->n;
    vi ind(n); iota(ind.begin(), ind.end(), 0);

    for (int ep = 0; ep < epochs; ++ep) {
      cout << "epoch: " << ep << endl;
      shuffle(ind.begin(), ind.end(), rng);
      for (int i = 0; i < n; i += mini_batch_size) {
        vi cur = {};
        for (int k = 0; k < mini_batch_size; ++k) {
          cur.push_back(ind[i+k]);
        }
        update_mini_batch(data, cur, eta);
      }

      // ps(weights, biases);

      if (test_data != nullptr) {
        evaluate(test_data);
      }
    }

  }

  int evaluate(Data<T> *data) {
    int cnt = 0;
    for (int i = 0; i < (int)data->n; ++i) {
      vector<T> input;
      for (T x: data->content[i]) {
        input.push_back(x);
      }
      auto a = feed_forward(input);
      T mx = -1E9;
      int evaluation = -1;
      for (int i = 0; i < (int)a.size(); ++i) {
        if (a[i] > mx) {
          mx = a[i];
          evaluation = i;
        }
      }
      // ps(evaluation, data->labels[i]);
      if (evaluation == data->labels[i]) ++cnt;
    }
    ps(cnt, "/", data->n);
    return cnt;
  }

  void update_mini_batch(Data<T> *data, const vi &ind, T eta) {
    vector<vector<T>> nabla_b(biases.size(), vector<T>(biases[0].size()));

    vector<vector<vector<T>>> nabla_w(weights.size());
    for (int i = 0; i < L; ++i) {
      nabla_w[i].assign(weights[i].size(), vector<T>(weights[i][0].size()));
    }

    for (int i = 0; i < (int)ind.size(); ++i) {
      // vector<uint8_t> data->content[i] => (uint8_t) data->labels[i]
      // auto [delta_nabla_b, delta_nabla_w] =
      backprop(data, ind[i]);
      for (int l = 0; l < L; ++l) {
        for (int j = 0; j < (int)nabla_b[l].size(); ++j) {
          nabla_b[l][j] += delta_nabla_b[l][j];
        }
        for (int j = 0; j < (int)nabla_w[l].size(); ++j) {
          for (int k = 0; k < (int)nabla_w[l][j].size(); ++k) {
            nabla_w[l][j][k] += delta_nabla_w[l][j][k];
          }
        }
      }
    }

    for (int l = 0; l < L; ++l) {
      for (int i = 0; i < (int)biases[l].size(); ++i) {
        biases[l][i] -= eta * nabla_b[l][i] / ind.size();
      }

      for (int i = 0; i < (int)weights[l].size(); ++i) {
        for (int j = 0; j < (int)weights[l][i].size(); ++j) {
          weights[l][i][j] -= eta * nabla_w[l][i][j] / ind.size();
        }
      }
    }
  }

  void backprop(Data<T> *data, int k) {
    int n = data->content[k].size();
    assert(n == (int)data->m);
    vector<T> activation(n);
    for (int i = 0; i < n; ++i) {
      activation[i] = data->content[k][i];
    }

    vector<vector<T>> activations = {activation};
    vector<vector<T>> zs;

    for (int i = 0; i < L; ++i) {
      vector z = dot(weights[i], activation) + biases[i];
      zs.push_back(z);
      activation = sigmoid(z);
      activations.push_back(activation);
    }

    vector<T> delta = dot(
      cost_derivative(activations.back(), data->labels[k]),
      sigmoid_prime(zs.back())
    );

    nabla_b.back() = delta;
    // ps(":", L-1, activations.size() - 2);
    // nabla_w.back() = dot_nm(delta, activations[L-1]);

    for (int i = 0; i < (int)delta.size(); ++i) {
      for (int j = 0; j < (int)activations[L-1].size(); ++j) {
        delta_nabla_w[L-1][i][j] = delta[i] * activations[L-1][j];
      }
    }

    // ps(nabla_b, nabla_w);

    for (int l = L-2; l >= 0; --l) {
      vector<T> z = zs[l];
      vector<T> sp = sigmoid_prime(z);
      vector<T> delta_r(weights[l+1][0].size());
      for (int i = 0; i < (int)weights[l+1].size(); ++i) {
        for (int j = 0; j < (int)weights[l+1][i].size(); ++j) {
          delta_r[j] += weights[l+1][i][j] * delta[i];
        }
      }
      delta = dot(delta_r, sp);
      delta_nabla_b[l] = delta;

      // ps(delta, activations[l]);
      // nabla_w[l] = dot(delta, activations[l]);
      for (int i = 0; i < (int)delta.size(); ++i) {
        for (int j = 0; j < (int)activations[l].size(); ++j) {
          delta_nabla_w[l][i][j] = delta[i] * activations[l][j];
        }
      }
    }

    // ps(nabla_b, nabla_w);
    // return make_pair(nabla_b, nabla_w);
  }

  vector<T> cost_derivative(vector<T> output_activations, int expected) {
    int n = output_activations.size();
    vector<T> r(n);
    for (int i = 0; i < n; ++i) {
      r[i] = output_activations[i] + (i == expected ? -1: 0);
    }
    return r;
  }

};



int main(int argc, const char **argv) {
#ifndef DEBUG_LOCAL
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#endif

  using T = double;
  clock_t t_clock = clock();

  const string train_name = "train";
  Data<T> *training_data = read_idx3_ubyte<T>(train_name);
  const string t10k_name = "t10k";
  Data<T> *validation_data = read_idx3_ubyte<T>(t10k_name);

  Network<T> network({784, 30, 10});
  int epochs = 5, mini_batch_size = 10;
  network.SGD(training_data, epochs, mini_batch_size, 0.5, validation_data);

  // {
  //   vector<vector<T>> content = {
  //     {0, 0},
  //     {0, 1},
  //     {1, 0},
  //     {1, 1}
  //   };
  //   vector<int> labels = {0, 1, 1, 0};

  //   Data<T> *training_data = new Data<T>(content, labels);
  //   Data<T> *validation_data = new Data<T>(content, labels);

  //   Network<T> network({2, 2, 2});
  //   network.evaluate(validation_data);

  //   int epochs = 100000, mini_batch_size = 1;
  //   network.SGD(training_data, epochs, mini_batch_size, 0.5, validation_data);
  // }

  fprintf(
    stderr,
    "Time %.3f milliseconds.\n",
    ((float)(clock() - t_clock)/CLOCKS_PER_SEC) * 1000
  );
  return 0;
}
