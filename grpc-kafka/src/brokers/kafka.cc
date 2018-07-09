#include <algorithm>
#include <assert.h>
#include <bitset>
#include <climits>
#include <cmath>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
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
#include <sys/time.h>
#include <time.h>
#include <tuple>
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
  cout << "sigterm" << endl;
  run = false;
}

static void print_time () {
  struct timeval tv;
  char buf[64];
  gettimeofday(&tv, NULL);
  strftime(buf, sizeof(buf) - 1, "%Y-%m-%d %H:%M:%S", localtime(&tv.tv_sec));
  fprintf(stderr, "%s.%03d: ", buf, (int)(tv.tv_usec / 1000));
}

class ExampleEventCb : public RdKafka::EventCb {
 public:
  void event_cb (RdKafka::Event &event) {
    cout << "event_cb" << endl;

    print_time();

    switch (event.type())
    {
      case RdKafka::Event::EVENT_ERROR:
        std::cerr << "ERROR (" << RdKafka::err2str(event.err()) << "): " <<
            event.str() << std::endl;
        if (event.err() == RdKafka::ERR__ALL_BROKERS_DOWN)
          run = false;
        break;

      case RdKafka::Event::EVENT_STATS:
        std::cerr << "\"STATS\": " << event.str() << std::endl;
        break;

      case RdKafka::Event::EVENT_LOG:
        fprintf(stderr, "LOG-%i-%s: %s\n",
                event.severity(), event.fac().c_str(), event.str().c_str());
        break;

      case RdKafka::Event::EVENT_THROTTLE:
  std::cerr << "THROTTLED: " << event.throttle_time() << "ms by " <<
    event.broker_name() << " id " << (int)event.broker_id() << std::endl;
  break;

      default:
        std::cerr << "EVENT " << event.type() <<
            " (" << RdKafka::err2str(event.err()) << "): " <<
            event.str() << std::endl;
        break;
    }
  }
};


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
      RdKafka::TopicPartition *part;
      for (auto part: partitions) {
        part->set_offset(0);
      }

      consumer->assign(partitions);
    } else {
      consumer->unassign();
      partition_cnt = 0;
    }
    eof_cnt = 0;
  }
};

void msg_consume(RdKafka::Message* message, void* opaque) {
  std::cout << "msg_consume:" << message->err() << std::endl;
  switch (message->err()) {
    case RdKafka::ERR__TIMED_OUT:
      break;

    case RdKafka::ERR_NO_ERROR:
      /* Real message */
      msg_cnt++;
      msg_bytes += message->len();
      if (verbosity >= 3)
        std::cerr << "Read msg at offset " << message->offset() << std::endl;
      RdKafka::MessageTimestamp ts;
      ts = message->timestamp();
      if (verbosity >= 2 &&
    ts.type != RdKafka::MessageTimestamp::MSG_TIMESTAMP_NOT_AVAILABLE) {
  std::string tsname = "?";
  if (ts.type == RdKafka::MessageTimestamp::MSG_TIMESTAMP_CREATE_TIME)
    tsname = "create time";
        else if (ts.type == RdKafka::MessageTimestamp::MSG_TIMESTAMP_LOG_APPEND_TIME)
          tsname = "log append time";
        std::cout << "Timestamp: " << tsname << " " << ts.timestamp << std::endl;
      }
      if (verbosity >= 2 && message->key()) {
        std::cout << "Key: " << *message->key() << std::endl;
      }
      if (verbosity >= 1) {
        printf("New message received: %.*s\n",
               static_cast<int>(message->len()),
               static_cast<const char *>(message->payload()));
      }
      break;

    case RdKafka::ERR__PARTITION_EOF:
      /* Last message */
      if (exit_eof && ++eof_cnt == partition_cnt) {
        std::cerr << "%% EOF reached for all " << partition_cnt <<
            " partition(s)" << std::endl;
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

class ExampleConsumeCb : public RdKafka::ConsumeCb {
 public:
  void consume_cb (RdKafka::Message &msg, void *opaque) {
    std::cout << "ExampleConsumeCb:" << std::endl;
    msg_consume(&msg, opaque);
  }
};


class KafkaConsumer
{
public:
  KafkaConsumer(string brokers_, string consumer_group_, string topic):
    brokers{brokers_}, consumer_group{consumer_group_} {
    topics = { topic };

    conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
    conf->set("metadata.broker.list", brokers, errstr);
    conf->set("consume_cb", &ex_consume_cb, errstr);
    conf->set("rebalance_cb", &ex_rebalance_cb, errstr);

    if (conf->set("auto.offset.reset",  "earliest", errstr) != RdKafka::Conf::CONF_OK) {
      std::cerr << errstr << std::endl;
      exit(1);
    }

    if (conf->set("group.id",  consumer_group, errstr) != RdKafka::Conf::CONF_OK) {
      std::cerr << errstr << std::endl;
      exit(1);
    }

    consumer = RdKafka::KafkaConsumer::create(conf, errstr);
    if (!consumer) {
      std::cerr << "Failed to create consumer: " << errstr << std::endl;
      exit(1);
    }

    std::cout << "% Created consumer " << consumer->name() << std::endl;

    RdKafka::ErrorCode err = consumer->subscribe(topics);
    if (err) {
      std::cerr << "Failed to subscribe to " << topics.size() << " topics: "
                << RdKafka::err2str(err) << std::endl;
      exit(1);
    }

  };

  ~KafkaConsumer() {
    cout << "deleting kafka consumer " << consumer->name() << endl;
    consumer->close();
    delete consumer;
    RdKafka::wait_destroyed(5000);
    cout << "end wait_destroyed" << endl;
  };

  void start() {
    while (run) {
      RdKafka::Message *msg = consumer->consume(1000);
      msg_consume(msg, NULL);
      delete msg;
    }
    cout << "end run" << endl;
  }

private:
  ExampleConsumeCb ex_consume_cb;
  ExampleRebalanceCb ex_rebalance_cb;
  RdKafka::Conf *conf;
  RdKafka::KafkaConsumer *consumer;
  std::string brokers;
  std::string consumer_group;
  std::string errstr;
  vector<std::string> topics;
};


