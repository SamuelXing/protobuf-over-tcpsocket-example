#!/bin/bash

export CC=/usr/bin/gcc-5
export CXX=/usr/bin/g++-5

mkdir build
cd build
cmake ..
make -j
