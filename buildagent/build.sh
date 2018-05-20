#!/usr/bin/env bash

set -e #Exit on first error

if [ ${TRAVIS_BRANCH} ]; then
  git_branch=${TRAVIS_BRANCH}
elif [ ${CIRCLE_BRANCH} ]; then
  git_branch=${CIRCLE_BRANCH}
else
  echo 'Branch not specified!' >&2
fi


#Check out the source code
git clone https://github.com/llvm-mirror/llvm.git --depth 1
git clone https://github.com/llvm-mirror/clang.git --depth 1 llvm/tools/clang
git clone https://github.com/llvm-mirror/clang-tools-extra.git --depth 1 \
 llvm/tools/clang/tools/extra
echo "Checking out branch ${git_branch} of clang-tidy-misra"
git clone --branch=${git_branch} \
 https://github.com/rettichschnidi/clang-tidy-misra.git --depth 1 \
 llvm/tools/clang/tools/extra/clang-tidy/misra/

#Patch clang-tidy to pick up our code
(cd llvm/tools/clang/tools/extra/ &&
 patch -p1 < clang-tidy/misra/clang-tidy.patch)

#Configure, build and test
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DLLVM_TARGETS_TO_BUILD=X86 \
 -DBUILD_SHARED_LIBS=ON ../llvm
make VERBOSE=1 -j2 check-tidy-misra
