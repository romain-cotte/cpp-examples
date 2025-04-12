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
#include <thread>
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

template <typename T>
struct Matrix {
  int rows, cols;
  vector<T> data;

  Matrix(int r, int c) : rows(r), cols(c), data(r * c) {}

  inline void init() {
    for (int i = 0; i < rows*cols; ++i) data[i] = 0;
  }

  inline T& operator()(int i, int j) {
    // writting purpose
    return data[i * cols + j];
  }

  inline const T& operator()(int i, int j) const {
    // reading purpose
    return data[i * cols + j];
  }
};


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
              [](uint8_t val) {
                return static_cast<T>(val) / 255.0;
              });
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
  // 4_200_000 calls, 70.68% of time
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
vector<T> dot(const Matrix<T>& m, const vector<T>& a) {
  // 4_200_000 calls, 70.68% of time
  assert(m.cols == (int)a.size());
  vector<T> r(m.rows);
  for (int l = 0; l < m.rows; ++l) {
    for (int c = 0; c < m.cols; ++c) {
      r[l] += m(l, c) * a[c];
    }
  }
  return r;
}


template<class T>
void dot(const Matrix<T>& m, const vector<T>& a, vector<T>& r) {
  // 4_200_000 calls, 70.68% of time
  assert(m.cols == (int)a.size());
  assert(m.rows == (int)r.size());
  // vector<T> r(m.rows);
  for (int l = 0; l < m.rows; ++l) {
    r[l] = 0;
    for (int c = 0; c < m.cols; ++c) {
      r[l] += m(l, c) * a[c];
    }
  }
  // return r;
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
  int n_threads = thread::hardware_concurrency();
  vector<thread> threads;
  mutex network_mutex;

  vector<int> layer_sizes;
  vector<vector<T>> biases, nabla_b, delta_nabla_b, buffers;
  vector<Matrix<T>> weights, nabla_w, delta_nabla_w;


  Network(vi _layer_sizes, bool random = true) {
    layer_sizes = _layer_sizes;
    L = layer_sizes.size() - 1;
    for (int i = 1; i < (int)layer_sizes.size(); ++i) {
      size_t sz = layer_sizes[i];
      size_t szp = layer_sizes[i-1];
      vector<T> v(sz);
      generate(v.begin(), v.end(), [&]() {
        if (random) return norm_dist(rng);
        return 0.1;
      });
      biases.push_back(v);

      Matrix<T> wi(sz, szp);
      // vector<vector<T>> wi(sz, vector<T>(szp));
      for (size_t j = 0; j < sz; ++j) {
        for (size_t k = 0; k < szp; ++k) {
          if (random) wi(j, k) = norm_dist(rng);
          else wi(j, k) = 0.1;
        }
      }
      weights.push_back(wi);
      nabla_w.push_back(Matrix<T>(sz, szp));
      delta_nabla_w.push_back(Matrix<T>(sz, szp));

      nabla_b.push_back(vector<T>(sz));
      delta_nabla_b.push_back(vector<T>(sz));
      buffers.push_back(vector<T>(sz));
    }

    // ps("biases", biases);
    // ps("weights", weights);
  }

  vector<T> feed_forward(vector<T> a) {
    // a' = σ(w.a+b)
    for (int i = 0; i < L; ++i) {
      dot(weights[i], a, buffers[i]);
      for (int j = 0; j < (int)biases[i].size(); ++j) {
        buffers[i][j] += biases[i][j];
      }
      a = sigmoid(buffers[i]);
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
      if (evaluation == data->labels[i]) ++cnt;
      // cout << i << " " << evaluation << " " << data->labels[i] << endl;
    }
    ps(cnt, "/", data->n);
    return cnt;
  }


  void mini_batch_iteration(Data<T> *data, int i) {
    auto [delta_nabla_w, delta_nabla_b] = backprop(data, i);
    network_mutex.lock();
    for (int l = 0; l < L; ++l) {
      for (int j = 0; j < (int)nabla_b[l].size(); ++j) {
        nabla_b[l][j] += delta_nabla_b[l][j];
      }
      for (int j = 0; j < nabla_w[l].rows; ++j) {
        for (int k = 0; k < nabla_w[l].cols; ++k) {
          nabla_w[l](j, k) += delta_nabla_w[l](j, k);
        }
      }
    }
    network_mutex.unlock();
  }

  void update_mini_batch(Data<T> *data, const vi &ind, T eta) {
    for (int i = 1; i < (int)layer_sizes.size(); ++i) {
      int l = layer_sizes[i];
      nabla_b[i-1].assign(l, 0);
      nabla_w[i-1].init();
    }

    for (int i = 0; i < (int)ind.size(); ++i) {
      threads.push_back(thread(&Network::mini_batch_iteration, this, data, ind[i]));

      if ((int)threads.size() == n_threads) {
        for (thread &thread: threads) {
          thread.join();
        }
        threads.clear();
      }
      // auto [delta_nabla_w, delta_nabla_b] = backprop(data, ind[i]);
      // for (int l = 0; l < L; ++l) {
      //   for (int j = 0; j < (int)nabla_b[l].size(); ++j) {
      //     nabla_b[l][j] += delta_nabla_b[l][j];
      //   }
      //   for (int j = 0; j < nabla_w[l].rows; ++j) {
      //     for (int k = 0; k < nabla_w[l].cols; ++k) {
      //       nabla_w[l](j, k) += delta_nabla_w[l](j, k);
      //     }
      //   }
      // }
    }

    for (thread &thread: threads) {
      thread.join();
    }
    threads.clear();


    for (int l = 0; l < L; ++l) {
      for (int i = 0; i < (int)biases[l].size(); ++i) {
        biases[l][i] -= eta * nabla_b[l][i] / ind.size();
      }

      for (int i = 0; i < weights[l].rows; ++i) {
        for (int j = 0; j < weights[l].cols; ++j) {
          weights[l](i, j) -= eta * nabla_w[l](i, j) / ind.size();
        }
      }
    }
  }

  pair<vector<Matrix<T>>, vector<vector<T>>> backprop(Data<T> *data, int k) {
    vector<vector<T>> delta_nabla_b(L);
    vector<Matrix<T>> delta_nabla_w;

    for (int i = 1; i < (int)layer_sizes.size(); ++i) {
      int l = layer_sizes[i];
      int p = layer_sizes[i-1];
      delta_nabla_b[i-1].assign(l, 0);
      delta_nabla_w.push_back(Matrix<T>(l, p));
    }
    int n = data->content[k].size();
    assert(n == (int)data->m);
    vector<T> activation(n);
    for (int i = 0; i < n; ++i) {
      activation[i] = data->content[k][i];
    }

    // If already declared in the class, it does not change
    // execution time.
    vector<vector<T>> activations = {activation};


    vector<vector<T>> zs;

    for (int i = 0; i < L; ++i) {
      vector z = dot(weights[i], activation); // + biases[i];
      for (int j = 0; j < (int)z.size(); ++j) z[j] += biases[i][j];

      zs.push_back(z);
      activation = sigmoid(z);
      activations.push_back(activation);
    }

    vector<T> delta = dot(
      cost_derivative(activations.back(), data->labels[k]),
      sigmoid_prime(zs.back())
    );

    delta_nabla_b.back() = delta;
    for (int i = 0; i < (int)delta.size(); ++i) {
      for (int j = 0; j < (int)activations[L-1].size(); ++j) {
        delta_nabla_w[L-1](i, j) = delta[i] * activations[L-1][j];
      }
    }

    for (int l = L-2; l >= 0; --l) {
      vector<T> z = zs[l];
      vector<T> sp = sigmoid_prime(z);
      vector<T> delta_r(weights[l+1].cols);
      for (int i = 0; i < weights[l+1].rows; ++i) {
        for (int j = 0; j < weights[l+1].cols; ++j) {
          delta_r[j] += weights[l+1](i, j) * delta[i];
        }
      }
      delta = dot(delta_r, sp);
      delta_nabla_b[l] = delta;

      for (int i = 0; i < (int)delta.size(); ++i) {
        for (int j = 0; j < (int)activations[l].size(); ++j) {
          delta_nabla_w[l](i, j) = delta[i] * activations[l][j];
        }
      }
    }


    return make_pair(delta_nabla_w, delta_nabla_b);
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

  int num_threads = std::thread::hardware_concurrency();
  cout << "num_threads: " << num_threads << endl;


  using T = float;
  clock_t t_clock = clock();

  const string train_name = "train";
  Data<T> *training_data = read_idx3_ubyte<T>(train_name);
  const string t10k_name = "t10k";
  Data<T> *validation_data = read_idx3_ubyte<T>(t10k_name);

  Network<T> network({784, 30, 10}, true);
  int epochs = 30, mini_batch_size = 10;

  network.SGD(training_data, epochs, mini_batch_size, 3, validation_data);

  float ms = ((float)(clock() - t_clock)/CLOCKS_PER_SEC) * 1000;
  fprintf(
    stderr,
    "Time %.3f milliseconds. %.3f = by iteration\n",
    ms,
    ms / epochs
  );

  return 0;
}
