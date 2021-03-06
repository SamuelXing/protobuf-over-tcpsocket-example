# protobuf-over-tcpsocket-example

![C/C++ CI](https://github.com/SamuelXing/protobuf-over-tcpsocket-example/workflows/C/C++%20CI/badge.svg)

An example of transmitting [protobuf](https://developers.google.com/protocol-buffers/docs/cpptutorial) messages over TCP sockets. Below is the proto using in this example.

```
syntax = "proto2";

package tutorial;

message Person {
  required string name = 1;
  required int32 id = 2;
  optional string email = 3;

  enum PhoneType {
    MOBILE = 0;
    HOME = 1;
    WORK = 2;
  }

  message PhoneNumber {
    required string number = 1;
    optional PhoneType type = 2 [default = HOME];
  }

  repeated PhoneNumber phones = 4;
}

message AddressBook {
  repeated Person people = 1;
}
```

## ENV
g++5, protobuf(proto2), cmake3.2, ubuntu 16.04

## Build
```bash
./build.sh
```

## Run
```bash
./server
./client (another terminal)
```

## Reference
- [Socket Programming in C/C++](https://www.geeksforgeeks.org/socket-programming-cc/)
- [protobuf explain](https://blog.usejournal.com/what-the-hell-is-protobuf-4aff084c5db4)

## LISCENSE
MIT
