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

int main(int argc, const char **argv) {
  RdKafka::Conf *conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);

  return 0;
}
