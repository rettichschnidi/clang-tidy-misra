// RUN: %python %S/../check_clang_tidy.py %s misra-cpp2008-6-4-2 %t

void compliant(int a, int b, int c, int d, int e, int f) {
  if (a) {
  }

  if (b) {
  } else if (c) {
  } else {
  }

  if (d) {
  } else if (e) {
  } else if (f) {
  } else {
  }
}

void violations(int x, int y) {
  if (x) {
  } else if (y) { // CHECK-MESSAGES: :[[@LINE]]:10: warning: All if ... else if constructs shall be terminated with an else clause. [misra-cpp2008-6-4-2]
  }
  if (x) {
  } else if (y) {
  } else if (y) {
  } else if (y) { // CHECK-MESSAGES: :[[@LINE]]:10: warning: All if ... else if constructs shall be terminated with an else clause. [misra-cpp2008-6-4-2]
  }
}
