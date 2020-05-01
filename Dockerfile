FROM ubuntu:16.04
MAINTAINER SamuelXing

RUN apt-get update && \
    apt-get install -y automake autoconf vim cmake protobuf-compiler libprotobuf-dev
