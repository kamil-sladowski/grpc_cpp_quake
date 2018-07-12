
#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>

#ifdef BAZEL_BUILD
#include "examples/protos/canal_data.grpc.pb.h"
#else
#include "canal_data.grpc.pb.h"
#endif

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using grpccommunication::QuakeEventMessage;
using grpccommunication::InjuryDataMessage;
using grpccommunication::ServerConfirmation;
using grpccommunication::SendingQuakeEvent;

class QuakeEventGenerator {
 public:
  QuakeEventGenerator(std::shared_ptr<Channel> channel)
      : stub_(SendingQuakeEvent::NewStub(channel)) {}

  // Assembles the client's payload, sends it and presents the response back
  // from the server.
  std::string sendQuakeEventData(const long timestamp, const int event_id, const int player_id) {
    // Data we are sending to the server.
    QuakeEventMessage request;
    request.set_timestamp(timestamp);
    request.set_event_id(event_id);
    request.set_player_id(player_id);

    // Container for the data we expect from the server.
    ServerConfirmation confirmation;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->sendQuakeEventData(&context, request, &confirmation);

    // Act upon its status.
    if (status.ok()) {
      return confirmation.confirm();
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }


  std::string sendInjuryData(const long timestamp, const int injury_id, const int player_id, const int new_hp_value) {
    // Data we are sending to the server.
    InjuryDataMessage request;
    request.set_timestamp(timestamp);
    request.set_injury_id(injury_id);
    request.set_player_id(player_id);
    request.set_new_hp_value(new_hp_value);

    // Container for the data we expect from the server.
    ServerConfirmation confirmation;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->sendInjuryData(&context, request, &confirmation);

    // Act upon its status.
    if (status.ok()) {
      return confirmation.confirm();
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }


 private:
  std::unique_ptr<SendingQuakeEvent::Stub> stub_;
};

int main(int argc, char** argv) {
  // Instantiate the client. It requires a channel, out of which the actual RPCs
  // are created. This channel models a connection to an endpoint (in this case,
  // localhost at port 50051). We indicate that the channel isn't authenticated
  // (use of InsecureChannelCredentials()).
  QuakeEventGenerator quake_client(grpc::CreateChannel(
      "localhost:50051", grpc::InsecureChannelCredentials()));
  long timestamp(12345678);
  int event_id(12);
  int player_id(3);
  std::string confirmation = quake_client.sendQuakeEventData(timestamp, event_id, player_id);
  std::cout << "Quake Event received: " << confirmation << std::endl;


  long timestamp2(765432);
  int injury_id(7);
  int player_id2(1);
  int new_hp_value(50);
  std::cout << "sending injury:" << std::endl;
  confirmation = quake_client.sendInjuryData(timestamp2, injury_id, player_id2, new_hp_value);
  std::cout << "Injury received: " << confirmation << std::endl;

  return 0;
}
