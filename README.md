# gRPC C++ communication for quake modules 
### Compilation using cmake:

Prepare python server:
https://github.com/kamilo116/grpc_server_python.git


To generate the client interfaces:
TODO:  add gRPC source tree to your project (preferrably as a git submodule) and add it to your cmake project with add_subdirectory.

```sh
$ sudo apt-get install golang
$ mkdir build && cd build
$ cmake ..
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


