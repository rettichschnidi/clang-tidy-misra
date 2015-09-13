// RUN: %python %S/../check_clang_tidy.py %s misra-cpp2008-18-4-1 %t

#include <new> // std::nothrow

void newPlain() {
  int *i = new int; // CHECK-MESSAGES: :[[@LINE]]:12: warning: Dynamic heap memory allocation shall not be used. [misra-cpp2008-18-4-1]
}

void newArray() {
  int *i = new int[10]; // CHECK-MESSAGES: :[[@LINE]]:12: warning: Dynamic heap memory allocation shall not be used. [misra-cpp2008-18-4-1]
}

void newNoThrowPlain() {
  int *i = new (std::nothrow) int; // CHECK-MESSAGES: :[[@LINE]]:12: warning: Dynamic heap memory allocation shall not be used. [misra-cpp2008-18-4-1]
}

void newNoThrowArray() {
  int *i = new (std::nothrow) int[10]; // CHECK-MESSAGES: :[[@LINE]]:12: warning: Dynamic heap memory allocation shall not be used. [misra-cpp2008-18-4-1]
}

void newPlacement() {
  int dummy;
  int *i = new (&dummy) int; // Placement-new is allowed
}

void newPlacementArray() {
  int dummy[11];
  int *i = new (&dummy[1]) int[10]; // Placement-new is allowed
}
