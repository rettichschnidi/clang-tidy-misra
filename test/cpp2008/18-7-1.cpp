// RUN: %python %S/../check_clang_tidy.py %s misra-cpp2008-18-7-1 %t

#include <csignal> // CHECK-MESSAGES: :[[@LINE]]:1: warning: The signal handling facilities of <csignal> shall not be used. [misra-cpp2008-18-7-1]

volatile sig_atomic_t globalSignalStatus;         // CHECK-MESSAGES: :[[@LINE]]:10: warning: The signal handling facilities of <csignal> shall not be used. [misra-cpp2008-18-7-1]
volatile std::sig_atomic_t globalStdSignalStatus; // CHECK-MESSAGES: :[[@LINE]]:10: warning: The signal handling facilities of <csignal> shall not be used. [misra-cpp2008-18-7-1]

typedef volatile bool my_sig_atomic_t;
my_sig_atomic_t globalMySignalStatus; // Valid

namespace mycode {
void signal(int, int);
}

int main() {
  void (*signalHandler)(int);
  signalHandler = SIG_DFL;       // CHECK-MESSAGES: :[[@LINE]]:19: warning: The signal handling facilities of <csignal> shall not be used. [misra-cpp2008-18-7-1]
  signalHandler = SIG_IGN;       // CHECK-MESSAGES: :[[@LINE]]:19: warning: The signal handling facilities of <csignal> shall not be used. [misra-cpp2008-18-7-1]
  std::signal(1, signalHandler); // CHECK-MESSAGES: :[[@LINE]]:3: warning: The signal handling facilities of <csignal> shall not be used. [misra-cpp2008-18-7-1]

  int signalToSend = SIGABRT; // CHECK-MESSAGES: :[[@LINE]]:22: warning: The signal handling facilities of <csignal> shall not be used. [misra-cpp2008-18-7-1]
  signalToSend = SIGFPE;      // CHECK-MESSAGES: :[[@LINE]]:18: warning: The signal handling facilities of <csignal> shall not be used. [misra-cpp2008-18-7-1]
  signalToSend = SIGABRT;     // CHECK-MESSAGES: :[[@LINE]]:18: warning: The signal handling facilities of <csignal> shall not be used. [misra-cpp2008-18-7-1]
  signalToSend = SIGILL;      // CHECK-MESSAGES: :[[@LINE]]:18: warning: The signal handling facilities of <csignal> shall not be used. [misra-cpp2008-18-7-1]
  signalToSend = SIGINT;      // CHECK-MESSAGES: :[[@LINE]]:18: warning: The signal handling facilities of <csignal> shall not be used. [misra-cpp2008-18-7-1]
  signalToSend = SIGSEGV;     // CHECK-MESSAGES: :[[@LINE]]:18: warning: The signal handling facilities of <csignal> shall not be used. [misra-cpp2008-18-7-1]
  signalToSend = SIGTERM;     // CHECK-MESSAGES: :[[@LINE]]:18: warning: The signal handling facilities of <csignal> shall not be used. [misra-cpp2008-18-7-1]
  std::raise(signalToSend);   // CHECK-MESSAGES: :[[@LINE]]:3: warning: The signal handling facilities of <csignal> shall not be used. [misra-cpp2008-18-7-1]

  mycode::signal(1, 1); // Valid
}
