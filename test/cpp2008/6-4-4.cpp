// Developed and copyright by: bansan85 <legarrec.vincent@gmail.com>
// RUN: %python %S/../check_clang_tidy.py %s misra-cpp2008-6-4-4 %t
void compliant(int a) {
  switch (a) {
    case 1: {
      break;
    }
    default: {
      break;
    }
  }
}


void violations(int x) {
  switch (x) {
    case 0:
    case 1: {
      if (x == 0) {
        case 2: {// CHECK-MESSAGES: :[[@LINE]]:9: warning: A switch-label shall only be used when the most closely-enclosing compound statement is the body of a switch statement. [misra-cpp2008-6-4-4]
          break;
        }
      }
      break;
    }
    default: {
      break;
    }
  }
}
