#!/usr/bin/env bash

set -e #Exit on first error

#Check out the source code
git clone https://github.com/llvm-mirror/llvm.git --depth 1
git clone https://github.com/llvm-mirror/clang.git --depth 1 llvm/tools/clang
git clone https://github.com/llvm-mirror/clang-tools-extra.git --depth 1 \
 llvm/tools/clang/tools/extra
git clone --branch=${TRAVIS_BRANCH} \
 https://github.com/rettichschnidi/clang-tidy-misra.git --depth 1 \
 llvm/tools/clang/tools/extra/clang-tidy/misra/

#Patch clang-tidy to pick up our code
(cd llvm/tools/clang/tools/extra/ &&
 patch -p1 < clang-tidy/misra/clang-tidy.patch)

#Configure, build and test
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DLLVM_TARGETS_TO_BUILD=X86 \
 -DBUILD_SHARED_LIBS=ON -DLLVM_CCACHE_BUILD=ON ../llvm
make VERBOSE=1 -j3 llvm-as
