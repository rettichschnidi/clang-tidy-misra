// RUN: %python %S/../check_clang_tidy.py %s misra-cpp2008-27-0-1 %t

#include <cstdio> // CHECK-MESSAGES: [[@LINE]]:1: warning: The stream input/output library <cstdio> shall not be used. [misra-cpp2008-27-0-1]
