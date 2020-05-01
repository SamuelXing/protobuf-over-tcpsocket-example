# protobuf-over-tcpsocket-example
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

## Known Issue
- [google-protobuf-maximum-size](https://stackoverflow.com/questions/34128872/google-protobuf-maximum-size)

## LISCENSE
MIT

Protobuf-over-tcp-socket-example.
————————
Cmake update, proto compile. proto msg demo.
Build script.
Known issue. Protobuf max size.
Comments.code 
Searching Tag.
CI/CD status.
Reference. Socket programming. Protobuf
Code structure.
formatting tool
————————