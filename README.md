# gRPC C++ communication for quake modules 
### Compilation using cmake:

Prepare python server:
https://github.com/kamilo116/grpc_server_python.git


To generate the client interfaces:
TODO:  add gRPC source tree to your project (preferrably as a git submodule) and add it to your cmake project with add_subdirectory.

```sh
$ sudo apt-get install golang
$ mkdir build && cd build
$ cmake
$ make
 
```
Which internally invokes the proto-compiler as:

```sh
$ protoc -I . --cpp_out=. canal_data.proto
$ protoc -I . --grpc_out=. --plugin=protoc-gen-grpc=grpc_cpp_plugin canal_data.proto
```
RUN:
```sh
$ ./canal_data
 
```


//////////////

### ALTERNATIVE COMPILATION:



To generate the client interfaces:

```sh
$ make 
 
```
Which internally invokes the proto-compiler as:

```sh
$ protoc -I . --cpp_out=. canal_data.proto
$ protoc -I . --grpc_out=. --plugin=protoc-gen-grpc=grpc_cpp_plugin canal_data.proto
```
Example:
```
protoc -I . --cpp_out=. canal_data.proto
g++ -std=c++11 `pkg-config --cflags protobuf grpc`  -c -o canal_data.pb.o canal_data.pb.cc
protoc -I . --grpc_out=. --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` canal_data.proto
g++ -std=c++11 `pkg-config --cflags protobuf grpc`  -c -o canal_data.grpc.pb.o canal_data.grpc.pb.cc
g++ -std=c++11 `pkg-config --cflags protobuf grpc`  -c -o quake_event_generator.o quake_event_generator.cc
g++ canal_data.pb.o canal_data.grpc.pb.o quake_event_generator.o -L/usr/local/lib `pkg-config --libs protobuf grpc++ grpc` -Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed -ldl -o quake_event_generator
```

RUN:
```sh
$ ./quake_event_generator
 
```
