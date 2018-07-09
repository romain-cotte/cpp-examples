#include <bits/stdc++.h>
#include <grpc++/grpc++.h>

#include "../build/helloworld.grpc.pb.h"
#include "../build/account.grpc.pb.h"
#include "./brokers/kafka.cc"

using namespace std;

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using helloworld::HelloRequest;
using helloworld::HelloReply;
using helloworld::Greeter;

using account::AccountService;
using account::AddAmountRequest;
using account::Amount;
using account::GetAmountRequest;
using account::Reply;


// Logic and data behind the server's behavior.
class GreeterServiceImpl final : public Greeter::Service {
  Status SayHello(ServerContext* context, const HelloRequest* request,
                  HelloReply* reply) override {
    std::string prefix("Hello ");
    reply->set_message(prefix + request->name());
    return Status::OK;
  }
};

class AccountServiceImpl final : public AccountService::Service {
  Status AddAmount(ServerContext* context, const AddAmountRequest* request,
                   Reply* reply) override {
    cout << "Add amount:" << endl;
    const string str = "test";
    if (accounts.count(str)) {
      accounts[str] += 10;
    } else {
      accounts[str] = 10;
    }

    reply->set_code(1);
    return Status::OK;
  }

  Status GetAmount(ServerContext* context, const GetAmountRequest* request,
                   Amount* amount) override {
    const string str = "test";

    amount->set_value(accounts[str]);
    return Status::OK;
  }

};

void RunServer() {
  std::string server_address("0.0.0.0:50051");
  AccountServiceImpl service;

  ServerBuilder builder;
  // Listen on the given address without any authentication mechanism.
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  // Register "service" as the instance through which we'll communicate with
  // clients. In this case it corresponds to an *synchronous* service.
  builder.RegisterService(&service);
  // Finally assemble the server.
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();
}

int main(int argc, const char **argv) {

  // signal(SIGINT, sigterm);
  // signal(SIGTERM, sigterm);

  // KafkaConsumer *kafkaConsumer = new KafkaConsumer("localhost", "consumer-1", "test");

  // std::thread consumer_thread(&KafkaConsumer::start, kafkaConsumer);

  // std::thread server_thread(RunServer);

  // consumer_thread.join();
  // cout << "end" << endl;
  // delete kafkaConsumer;
  // // server_thread.join();


  Amount* amount = new Amount();
  amount->set_value(234);
  string str;

  Amount* expected_amount = new Amount();

  // std::ostringstream stream;

  // if (!amount->SerializeToOstream(&stream)) {
  //   std::cout << "0:" << 0 << std::endl;
  // } else {
  //   std::cout << "1:" << 1 << std::endl;
  //   cout << stream.str() << endl;
  // }
  amount->SerializeToString(&str);
  std::cout << "str:" << str << std::endl;

  expected_amount->ParseFromString(str);

  cout << expected_amount->value() << endl;


  return 0;
}
