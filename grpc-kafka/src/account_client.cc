#include <bits/stdc++.h>
#include <grpc++/grpc++.h>

#include "../build/account.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using account::AccountService;
using account::AddAmountRequest;
using account::Amount;
using account::GetAmountRequest;
using account::Reply;

class AccountClient {
 public:
  AccountClient(std::shared_ptr<Channel> channel)
      : stub_(AccountService::NewStub(channel)) {}

  // Assembles the client's payload, sends it and presents the response back
  // from the server.
  int AddAmount(const std::string& account_name, const double value) {
    // Data we are sending to the server.
    AddAmountRequest request;
    request.set_name(account_name);

    // Container for the data we expect from the server.
    Reply reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->AddAmount(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
      return reply.code();
    } else {
      std::cout << "An error occurred" << std::endl;
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;

      return 0;
    }
  }

  double GetAmount(const std::string& account_name) {
    GetAmountRequest request;
    request.set_name(account_name);
    Amount amount;

        // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->GetAmount(&context, request, &amount);

    // Act upon its status.
    if (status.ok()) {
      return amount.value();
    } else {
      std::cout << "An error occurred" << std::endl;
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return -1;
    }
  }


 private:
  std::unique_ptr<AccountService::Stub> stub_;
};

int main(int argc, const char **argv) {
  // Instantiate the client. It requires a channel, out of which the actual RPCs
  // are created. This channel models a connection to an endpoint (in this case,
  // localhost at port 50051). We indicate that the channel isn't authenticated
  // (use of InsecureChannelCredentials()).
  AccountClient account(grpc::CreateChannel(
      "localhost:50051", grpc::InsecureChannelCredentials()));
  std::string account_name("account-1");
  int reply = account.AddAmount(account_name, 10);
  std::cout << "Add amount OK: " << reply << std::endl;
  reply = account.AddAmount(account_name, 10);
  std::cout << "Add amount OK: " << reply << std::endl;
  reply = account.AddAmount(account_name, 10);
  std::cout << "Add amount OK: " << reply << std::endl;

  double amount = account.GetAmount(account_name);
  std::cout << "Get amount OK: " << amount << std::endl;

  return 0;
}
