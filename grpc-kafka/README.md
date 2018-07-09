Steps

protoc -I ./protos --cpp_out=. ./protos/helloworld.proto

g++ -std=c++11 `pkg-config --cflags protobuf grpc`  -c -o helloworld.pb.o helloworld.pb.cc

protoc -I ./protos --grpc_out=. --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` ./protos/helloworld.proto

g++ -std=c++11 `pkg-config --cflags protobuf grpc`  -c -o helloworld.grpc.pb.o helloworld.grpc.pb.cc

g++ -std=c++11 `pkg-config --cflags protobuf grpc`  -c -o greeter_client.o greeter_client.cc

g++ helloworld.pb.o helloworld.grpc.pb.o greeter_client.o -L/usr/local/lib `pkg-config --libs protobuf grpc++ grpc` -Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed -ldl -o greeter_client



protoc -I ./protos --cpp_out=. ./protos/helloworld.proto
files helloworld.pb.h and helloworld.pb.cc are generated
equivalent make:
  make helloworld.pb.cc
as the file is tagged as precious, the file helloworld.pb.h is kept

STATUS: OK
make build/helloworld.pb.cc

g++ -std=c++11 `pkg-config --cflags protobuf grpc`  -c -o helloworld.pb.o helloworld.pb.cc
equivalent make: make helloworld.pb.o

STATUS: OK

protoc -I ./protos --grpc_out=. --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` ./protos/helloworld.proto
helloworld.grpc.pb.h helloworld.grpc.pb.cc are generated
equivalent make: make helloworld.grpc.pb.cc


g++ -std=c++11 `pkg-config --cflags protobuf grpc`  -c -o helloworld.grpc.pb.o helloworld.grpc.pb.cc
make helloworld.grpc.pb.o


g++ -std=c++11 `pkg-config --cflags protobuf grpc`  -c -o greeter_client.o greeter_client.cc

g++ helloworld.pb.o helloworld.grpc.pb.o greeter_client.o -L/usr/local/lib `pkg-config --libs protobuf grpc++ grpc` -Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed -ldl -o greeter_client
