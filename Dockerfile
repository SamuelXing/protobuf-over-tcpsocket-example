FROM ubuntu:16.04
MAINTAINER SamuelXing

RUN apt-get update && \
    apt-get install -y \
    g++-5 \
    automake \
    autoconf \
    cmake \
    vim \
    protobuf-compiler \
    libprotobuf-dev 

