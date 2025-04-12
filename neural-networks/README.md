# Timing:

5 iterations: Time 53929.363 milliseconds
= 10785.8 ms by iteration

delta_nabla_b, delta_nabla_w refactored:
5 iterationss: Time 16704.770 milliseconds.
= 3340.8 ms by iteration

30 iterations : Time 67534.766 milliseconds.
= 2251.1 ms by iteration

When using same nabla
30 iterations : Time 66456.492 milliseconds.
= 2215 ms by iteration








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





Number of images: 60000
Dimensions: 28x28
Number of images: 10000
Dimensions: 28x28
epoch: 0
9159 / 10000
epoch: 1
9317 / 10000
epoch: 2
9382 / 10000
epoch: 3
9403 / 10000
epoch: 4
9431 / 10000
epoch: 5
9430 / 10000
epoch: 6
9493 / 10000
epoch: 7
9448 / 10000
epoch: 8
9513 / 10000
epoch: 9
9480 / 10000
epoch: 10
9488 / 10000
epoch: 11
9512 / 10000
epoch: 12
9509 / 10000
epoch: 13
9531 / 10000
epoch: 14
9498 / 10000
epoch: 15
9551 / 10000
epoch: 16
9534 / 10000
epoch: 17
9553 / 10000
epoch: 18
9545 / 10000
epoch: 19
9541 / 10000
epoch: 20
9551 / 10000
epoch: 21
9557 / 10000
epoch: 22
9537 / 10000
epoch: 23
9556 / 10000
epoch: 24
9522 / 10000
epoch: 25
9538 / 10000
epoch: 26
9561 / 10000
epoch: 27
9557 / 10000
epoch: 28
9521 / 10000
epoch: 29
9519 / 10000
Time 67173.312 milliseconds.
