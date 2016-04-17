// RUN: %python %S/../check_clang_tidy.py %s misra-cpp2008-18-0-4 %t

#include <ctime>

void useFromGlobalNs() {
  clock();                            // CHECK-MESSAGES: :[[@LINE]]:3: warning: The time handling functions of library <ctime> shall not be used. [misra-cpp2008-18-0-4]
  time_t currentTime = time(NULL);    // CHECK-MESSAGES: :[[@LINE]]:24: warning: The time handling functions of library <ctime> shall not be used. [misra-cpp2008-18-0-4]
  difftime(currentTime, currentTime); // CHECK-MESSAGES: :[[@LINE]]:3: warning: The time handling functions of library <ctime> shall not be used. [misra-cpp2008-18-0-4]
  tm timeStruct;
  mktime(&timeStruct); // CHECK-MESSAGES: :[[@LINE]]:3: warning: The time handling functions of library <ctime> shall not be used. [misra-cpp2008-18-0-4]
}

void useFromStdNs() {
  std::clock();                            // CHECK-MESSAGES: :[[@LINE]]:3: warning: The time handling functions of library <ctime> shall not be used. [misra-cpp2008-18-0-4]
  time_t currentTime = std::time(NULL);    // CHECK-MESSAGES: :[[@LINE]]:24: warning: The time handling functions of library <ctime> shall not be used. [misra-cpp2008-18-0-4]
  std::difftime(currentTime, currentTime); // CHECK-MESSAGES: :[[@LINE]]:3: warning: The time handling functions of library <ctime> shall not be used. [misra-cpp2008-18-0-4]
  tm timeStruct;
  std::mktime(&timeStruct); // CHECK-MESSAGES: :[[@LINE]]:3: warning: The time handling functions of library <ctime> shall not be used. [misra-cpp2008-18-0-4]
}
