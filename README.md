# gRPC C++ communication for quake modules 


Prepare python server:
https://github.com/kamilo116/grpc_server_python.git



To generate the client interfaces:

```sh
$ make 
 
```
Which internally invokes the proto-compiler as:

```sh
$ protoc -I . --grpc_out=. --plugin=protoc-gen-grpc=grpc_cpp_plugin canal_data.proto
$ protoc -I ../../protos/ --cpp_out=. ../../protos/helloworld.proto
```


```sh
$ ./quake_event_generator
 

```
