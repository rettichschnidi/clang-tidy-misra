// RUN: "%clang"-tidy -checks='-*,misra-cpp2008-27-0-1' %s -- | FileCheck %s

#include <cstdio> // CHECK: :[[@LINE]]:1: error: The stream input/output library <cstdio> shall not be used. [misra-cpp2008-27-0-1]
