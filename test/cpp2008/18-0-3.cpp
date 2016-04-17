// RUN: %python %S/../check_clang_tidy.py %s misra-cpp2008-18-0-3 %t

#include <cstdlib>

void useFromGlobalNs() {
  abort();                     // CHECK-MESSAGES: :[[@LINE]]:3: warning: The library functions abort, exit, getenv and system from library <cstdlib> shall not be used. [misra-cpp2008-18-0-3]
  exit(EXIT_FAILURE);          // CHECK-MESSAGES: :[[@LINE]]:3: warning: The library functions abort, exit, getenv and system from library <cstdlib> shall not be used. [misra-cpp2008-18-0-3]
  getenv("HOME");              // CHECK-MESSAGES: :[[@LINE]]:3: warning: The library functions abort, exit, getenv and system from library <cstdlib> shall not be used. [misra-cpp2008-18-0-3]
  system("cat /proc/cpuinfo"); // CHECK-MESSAGES: :[[@LINE]]:3: warning: The library functions abort, exit, getenv and system from library <cstdlib> shall not be used. [misra-cpp2008-18-0-3]
}

void useFromStdNs() {
  std::abort();                     // CHECK-MESSAGES: :[[@LINE]]:3: warning: The library functions abort, exit, getenv and system from library <cstdlib> shall not be used. [misra-cpp2008-18-0-3]
  std::exit(EXIT_FAILURE);          // CHECK-MESSAGES: :[[@LINE]]:3: warning: The library functions abort, exit, getenv and system from library <cstdlib> shall not be used. [misra-cpp2008-18-0-3]
  std::getenv("HOME");              // CHECK-MESSAGES: :[[@LINE]]:3: warning: The library functions abort, exit, getenv and system from library <cstdlib> shall not be used. [misra-cpp2008-18-0-3]
  std::system("cat /proc/cpuinfo"); // CHECK-MESSAGES: :[[@LINE]]:3: warning: The library functions abort, exit, getenv and system from library <cstdlib> shall not be used. [misra-cpp2008-18-0-3]
}

struct S {
  void abort();
  void exit(int);
  char *getenv(const char *);
  int system(const char *);
};

void legalUsage() {
  S s;
  s.abort();
  s.exit(EXIT_FAILURE);
  s.getenv("HOME");
  s.system("cat /proc/cpuinfo");
}
