// RUN: %python %S/../check_clang_tidy.py %s misra-cpp2008-19-3-1 %t

#include <cerrno>
#include <cmath>
#include <iostream>
#include <cstring>

int main() {
  errno = 0; // CHECK-MESSAGES: [[@LINE]]:3: warning: The error indicator errno shall not be used. [misra-cpp2008-19-3-1]
  double not_a_number = std::log(-1.0);

  if (errno == EDOM) {                                               // CHECK-MESSAGES: [[@LINE]]:7: warning: The error indicator errno shall not be used. [misra-cpp2008-19-3-1]
    std::cout << "log(-1) failed: " << std::strerror(errno) << '\n'; // CHECK-MESSAGES: [[@LINE]]:54: warning: The error indicator errno shall not be used. [misra-cpp2008-19-3-1]
  }
}
