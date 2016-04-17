// RUN: %python %S/../check_clang_tidy.py %s misra-cpp2008-18-0-2 %t

#include <cstdlib>

void useAtoHell() {
  float f = atof("3.3");       // CHECK-MESSAGES: :[[@LINE]]:13: warning: The library functions atof, atoi and atol from library <cstdlib> shall not be used. [misra-cpp2008-18-0-2]
  int i = atoi("123");         // CHECK-MESSAGES: :[[@LINE]]:11: warning: The library functions atof, atoi and atol from library <cstdlib> shall not be used. [misra-cpp2008-18-0-2]
  long l = atol("1234556790"); // CHECK-MESSAGES: :[[@LINE]]:12: warning: The library functions atof, atoi and atol from library <cstdlib> shall not be used. [misra-cpp2008-18-0-2]
}

void useAtoHellWithStdPrefix() {
  float f = std::atof("3.3");       // CHECK-MESSAGES: :[[@LINE]]:13: warning: The library functions atof, atoi and atol from library <cstdlib> shall not be used. [misra-cpp2008-18-0-2]
  int i = std::atoi("123");         // CHECK-MESSAGES: :[[@LINE]]:11: warning: The library functions atof, atoi and atol from library <cstdlib> shall not be used. [misra-cpp2008-18-0-2]
  long l = std::atol("1234556790"); // CHECK-MESSAGES: :[[@LINE]]:12: warning: The library functions atof, atoi and atol from library <cstdlib> shall not be used. [misra-cpp2008-18-0-2]
}
