// RUN: %python %S/../check_clang_tidy.py %s misra-cpp2008-6-4-1 %t

void compliant(int x, int y, int z) {
  if (x) {
  }

  if (x) {
  } else if (y) {
  }

  if (x) {
  } else if (y) {
  } else {
  }
}

void violations(int x, int y, int z) {
  if (x)
    ; // CHECK-MESSAGES: :[[@LINE]]:5: warning: An if ( condition ) construct shall be followed by a compound statement. The else keyword shall be followed by either a compound statement, or another if statement. [misra-cpp2008-6-4-1]

  if (x)
    y = 1; // CHECK-MESSAGES: :[[@LINE]]:5: warning: An if ( condition ) construct shall be followed by a compound statement. The else keyword shall be followed by either a compound statement, or another if statement. [misra-cpp2008-6-4-1]

  if (x) {
  } else
    y = 1; // CHECK-MESSAGES: :[[@LINE]]:5: warning: An if ( condition ) construct shall be followed by a compound statement. The else keyword shall be followed by either a compound statement, or another if statement. [misra-cpp2008-6-4-1]

  if (x) {
  } else if (y) {
  } else
    z = 1; // CHECK-MESSAGES: :[[@LINE]]:5: warning: An if ( condition ) construct shall be followed by a compound statement. The else keyword shall be followed by either a compound statement, or another if statement. [misra-cpp2008-6-4-1]
}
