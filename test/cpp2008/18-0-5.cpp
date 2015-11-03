// RUN: %python %S/../check_clang_tidy.py %s misra-cpp2008-18-0-5 %t

#include <cstring>

void useStrcp(char out[]) {
  strcpy(out, "illegal"); // CHECK-MESSAGES: :[[@LINE]]:3: warning: The unbounded functions of library <cstring> shall not be used. [misra-cpp2008-18-0-5]
}

void useStrcmp(char out[]) {
  int i = strcmp(out, "illegal"); // CHECK-MESSAGES: :[[@LINE]]:11: warning: The unbounded functions of library <cstring> shall not be used. [misra-cpp2008-18-0-5]
}

void useSrcat(char out[]) {
  strcat(out, "illegal"); // CHECK-MESSAGES: :[[@LINE]]:3: warning: The unbounded functions of library <cstring> shall not be used. [misra-cpp2008-18-0-5]
}

void useStrchr(char out[]) {
  char *c = strchr(out, 'a'); // CHECK-MESSAGES: :[[@LINE]]:13: warning: The unbounded functions of library <cstring> shall not be used. [misra-cpp2008-18-0-5]
}

void useStrspn(char out[]) {
  size_t i = strspn(out, "needle"); // CHECK-MESSAGES: :[[@LINE]]:14: warning: The unbounded functions of library <cstring> shall not be used. [misra-cpp2008-18-0-5]
}

void useStrcspn(char out[]) {
  size_t i = strcspn(out, "non-needle"); // CHECK-MESSAGES: :[[@LINE]]:14: warning: The unbounded functions of library <cstring> shall not be used. [misra-cpp2008-18-0-5]
}

void useStrpbrk(char out[]) {
  char *c = strpbrk(out, "xyz"); // CHECK-MESSAGES: :[[@LINE]]:13: warning: The unbounded functions of library <cstring> shall not be used. [misra-cpp2008-18-0-5]
}

void useStrrchr(char out[]) {
  char *c = strrchr(out, 'z'); // CHECK-MESSAGES: :[[@LINE]]:13: warning: The unbounded functions of library <cstring> shall not be used. [misra-cpp2008-18-0-5]
}

void useStrstr(char out[]) {
  char *c = strstr(out, "needle"); // CHECK-MESSAGES: :[[@LINE]]:13: warning: The unbounded functions of library <cstring> shall not be used. [misra-cpp2008-18-0-5]
}

void useStr(char out[]) {
  char *c = strtok(out, "x"); // CHECK-MESSAGES: :[[@LINE]]:13: warning: The unbounded functions of library <cstring> shall not be used. [misra-cpp2008-18-0-5]
}

void useStrlen(char out[]) {
  size_t i = strlen(out); // CHECK-MESSAGES: :[[@LINE]]:14: warning: The unbounded functions of library <cstring> shall not be used. [misra-cpp2008-18-0-5]
}
