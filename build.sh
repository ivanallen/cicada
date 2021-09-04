#!/bin/bash

if [ ! -d build ]; then
    mkdir build
fi

cd build

cmake -DCMAKE_INSTALL_PREFIX=../output ..

make && make test && make install
