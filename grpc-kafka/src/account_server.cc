#include <bits/stdc++.h>

#include "./brokers/kafka.cc"

int main(int argc, const char **argv) {

  signal(SIGINT, sigterm);
  signal(SIGTERM, sigterm);

  KafkaConsumer *kafkaConsumer
    = new KafkaConsumer("localhost", "c-a-3", "test");
  kafkaConsumer->start();
  cout << "end" << endl;

  delete kafkaConsumer;

  return 0;
}
