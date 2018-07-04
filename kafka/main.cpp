#include <algorithm>
#include <assert.h>
#include <bitset>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <math.h>
#include <queue>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <time.h>
// #include <tuple>
#include <typeinfo>
#include <vector>

#include <librdkafka/rdkafkacpp.h>

#define SZ(x) (int)(x.size())
#define F0(i,n) for(int i=0;i<n;i++)
#define F1(i,n) for(int i=1;i<=n;i++)
#define FI(i,n) for(int i=0;i<=n;i++)
#define TR(x) cout << #x << " = " << x << endl
#define _ << " " <<
#define INF 1E9

using namespace std;
typedef vector<int> vi;

static bool run = true;
static bool exit_eof = false;
static int eof_cnt = 0;
static int partition_cnt = 0;
static int verbosity = 1;
static long msg_cnt = 0;
static int64_t msg_bytes = 0;
static void sigterm (int sig) {
  run = false;
}

class ExampleRebalanceCb : public RdKafka::RebalanceCb {
private:
  static void part_list_print(const std::vector<RdKafka::TopicPartition*>&partitions){
    for (unsigned int i = 0 ; i < partitions.size() ; i++) {
      std::cerr
        << partitions[i]->topic()
        << "[" << partitions[i]->partition() << "], ";
    }
    std::cerr << "\n";
  }

public:
  void rebalance_cb(RdKafka::KafkaConsumer *consumer,
                    RdKafka::ErrorCode err,
                    std::vector<RdKafka::TopicPartition*> &partitions) {
    std::cerr << "RebalanceCb: " << RdKafka::err2str(err) << ": ";

    part_list_print(partitions);

    if (err == RdKafka::ERR__ASSIGN_PARTITIONS) {
      consumer->assign(partitions);
      partition_cnt = (int) partitions.size();
    } else {
      consumer->unassign();
      partition_cnt = 0;
    }
    eof_cnt = 0;
  }
};


void msg_consume(RdKafka::Message* message, void* opaque) {
  switch (message->err()) {
    case RdKafka::ERR__TIMED_OUT:
      break;

    case RdKafka::ERR_NO_ERROR:
      /* Real message */
      std::cout << "Read msg at offset " << message->offset() << std::endl;
      if (message->key()) {
        std::cout << "Key: " << *message->key() << std::endl;
      }
      printf("%.*s\n",
        static_cast<int>(message->len()),
        static_cast<const char *>(message->payload()));
      break;

    case RdKafka::ERR__PARTITION_EOF:
      /* Last message */
      if (exit_eof) {
        run = false;
      }
      break;

    case RdKafka::ERR__UNKNOWN_TOPIC:
    case RdKafka::ERR__UNKNOWN_PARTITION:
      std::cerr << "Consume failed: " << message->errstr() << std::endl;
      run = false;
      break;

    default:
      /* Errors */
      std::cerr << "Consume failed: " << message->errstr() << std::endl;
      run = false;
  }
}


int main(int argc, const char **argv) {
  std::string brokers = "localhost";
  std::string errstr;
  std::string topic_str = "test";
  std::string mode;
  std::string debug;
  int32_t partition = RdKafka::Topic::PARTITION_UA;
  partition = 0;
  int64_t start_offset = RdKafka::Topic::OFFSET_BEGINNING;

  RdKafka::Conf *conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
  RdKafka::Conf *tconf = RdKafka::Conf::create(RdKafka::Conf::CONF_TOPIC);

  res = conf->set(name, val, errstr);

  if (res != RdKafka::Conf::CONF_OK) {
    std::cerr << errstr << std::endl;
    exit(1);
  }


  RdKafka::Consumer *consumer = RdKafka::Consumer::create(conf, errstr);
  if (!consumer) {
    std::cerr << "Failed to create consumer: " << errstr << std::endl;
    exit(1);
  }
  std::cout << "% Created consumer " << consumer->name() << std::endl;

  RdKafka::Topic *topic = RdKafka::Topic::create(consumer,
                                                 topic_str,
                                                 tconf,
                                                 errstr);
  if (!topic) {
    std::cerr << "Failed to create topic: " << errstr << std::endl;
    exit(1);
  }

  RdKafka::ErrorCode resp = consumer->start(topic, partition, 10);
  if (resp != RdKafka::ERR_NO_ERROR) {
    std::cerr <<
      "Failed to start consumer: " <<
      RdKafka::err2str(resp) << std::endl;
    exit(1);
  }

  /*
   * Subscribe to topics
   */
  // RdKafka::ErrorCode err = consumer->subscribe(topics);
  // if (err) {
  //   std::cerr << "Failed to subscribe to " << topics.size() << " topics: "
  //             << RdKafka::err2str(err) << std::endl;
  //   exit(1);
  // }

  /*
   * Consume messages
   */
  while (run) {
    RdKafka::Message *msg = consumer->consume(topic, partition, 1000);
    // if (!use_ccb) {
      msg_consume(msg, NULL);
    // }
    delete msg;
    consumer->poll(0);

  }

  consumer->stop(topic, partition);
  consumer->poll(1000);

  delete topic;
  delete consumer;

  return 0;
}
