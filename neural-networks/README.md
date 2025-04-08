# Timing:

5 iterations: Time 53929.363 milliseconds

delta_nabla_b, delta_nabla_w refactored:
5 iterationss: Time 16704.770 milliseconds.




# XOR

[0, 0]  0
[0, 1]  1
[1, 0]  1
[1, 1]  0


# Tests

```cpp

int test(Data *training_data) {
  for (int i = 90; i < 100; ++i) {
    training_data->print(i);
  }

  {
    vector<vector<ld>> v = {
      {1, 2, 4},
      {7, 8, 9}
    };
    ps("v", v);
    ps("transpose(v)", transpose(v));
  }
  {
    vector<ld> v = {1, 2, 4, 5, 10};
    ps(sigmoid(v));
    ps(sigmoid_prime(v));
  }

  {
    vector<int> layer_sizes = {2, 3, 10};
    Network<double> network(layer_sizes);
    vector<double> a = {1.0, 2.0};
    vector<double> b = {3.0, 4.0};
    ps("a+b", a+b);
    ps("dot a, b", dot_scalar(a, b));
    ps(network.feed_forward(a));
  }
  return 0;
}

```



```cpp
  vector<vector<T>> content = {
    {0, 0},
    {0, 1},
    {1, 0},
    {1, 1}
  };
  vector<int> labels = {0, 1, 1, 0};

  Data<T> *training_data = new Data<T>(content, labels);
  Data<T> *validation_data = new Data<T>(content, labels);

  Network<T> network({2, 2, 2});
  network.evaluate(validation_data);

  int epochs = 3, mini_batch_size = 1;
  network.SGD(training_data, epochs, mini_batch_size, 1.0, validation_data);

```
