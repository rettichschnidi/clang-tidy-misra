// RUN: %python %S/../check_clang_tidy.py %s misra-cpp2008-18-7-1 %t

#include <csignal> // CHECK-MESSAGES: :[[@LINE]]:1: warning: The signal handling facilities of <csignal> shall not be used. [misra-cpp2008-18-7-1]

typedef sig_atomic_t clever_me_typedef;          // CHECK-MESSAGES: :[[@LINE]]:9: warning: The signal handling facilities of <csignal> shall not be used. [misra-cpp2008-18-7-1]
typedef std::sig_atomic_t clever_me_typedef_std; // CHECK-MESSAGES: :[[@LINE]]:9: warning: The signal handling facilities of <csignal> shall not be used. [misra-cpp2008-18-7-1]
clever_me_typedef globalTypedefSignalStatus;     // CHECK-MESSAGES: :[[@LINE]]:1: warning: The signal handling facilities of <csignal> shall not be used. [misra-cpp2008-18-7-1]

using clever_me_using = sig_atomic_t;    // CHECK-MESSAGES: :[[@LINE]]:25: warning: The signal handling facilities of <csignal> shall not be used. [misra-cpp2008-18-7-1]
clever_me_using globalusingSignalStatus; // CHECK-MESSAGES: :[[@LINE]]:1: warning: The signal handling facilities of <csignal> shall not be used. [misra-cpp2008-18-7-1]
