// RUN: %python %S/../check_clang_tidy.py %s misra-cpp2008-18-0-1 %t

// CHECK-MESSAGES: [[@LINE+1]]:1: warning: The C library shall not be used. [misra-cpp2008-18-0-1]
#include <assert.h>
// CHECK-MESSAGES: [[@LINE+1]]:1: warning: The C library shall not be used. [misra-cpp2008-18-0-1]
#include <ctype.h>
// CHECK-MESSAGES: [[@LINE+1]]:1: warning: The C library shall not be used. [misra-cpp2008-18-0-1]
#include <errno.h>
// CHECK-MESSAGES: [[@LINE+1]]:1: warning: The C library shall not be used. [misra-cpp2008-18-0-1]
#include <fenv.h>
// CHECK-MESSAGES: [[@LINE+1]]:1: warning: The C library shall not be used. [misra-cpp2008-18-0-1]
#include <float.h>
// CHECK-MESSAGES: [[@LINE+1]]:1: warning: The C library shall not be used. [misra-cpp2008-18-0-1]
#include <inttypes.h>
// CHECK-MESSAGES: [[@LINE+1]]:1: warning: The C library shall not be used. [misra-cpp2008-18-0-1]
#include <iso646.h>
// CHECK-MESSAGES: [[@LINE+1]]:1: warning: The C library shall not be used. [misra-cpp2008-18-0-1]
#include <limits.h>
// CHECK-MESSAGES: [[@LINE+1]]:1: warning: The C library shall not be used. [misra-cpp2008-18-0-1]
#include <locale.h>
// CHECK-MESSAGES: [[@LINE+1]]:1: warning: The C library shall not be used. [misra-cpp2008-18-0-1]
#include <math.h>
// CHECK-MESSAGES: [[@LINE+1]]:1: warning: The C library shall not be used. [misra-cpp2008-18-0-1]
#include <setjmp.h>
// CHECK-MESSAGES: [[@LINE+1]]:1: warning: The C library shall not be used. [misra-cpp2008-18-0-1]
#include <signal.h>
// CHECK-MESSAGES: [[@LINE+1]]:1: warning: The C library shall not be used. [misra-cpp2008-18-0-1]
#include <stdarg.h>
// CHECK-MESSAGES: [[@LINE+1]]:1: warning: The C library shall not be used. [misra-cpp2008-18-0-1]
#include <stdbool.h>
// CHECK-MESSAGES: [[@LINE+1]]:1: warning: The C library shall not be used. [misra-cpp2008-18-0-1]
#include <stddef.h>
// CHECK-MESSAGES: [[@LINE+1]]:1: warning: The C library shall not be used. [misra-cpp2008-18-0-1]
#include <stdint.h>
// CHECK-MESSAGES: [[@LINE+1]]:1: warning: The C library shall not be used. [misra-cpp2008-18-0-1]
#include <stdlib.h>
// CHECK-MESSAGES: [[@LINE+1]]:1: warning: The C library shall not be used. [misra-cpp2008-18-0-1]
#include <string.h>
// CHECK-MESSAGES: [[@LINE+1]]:1: warning: The C library shall not be used. [misra-cpp2008-18-0-1]
#include <tgmath.h>
// CHECK-MESSAGES: [[@LINE+1]]:1: warning: The C library shall not be used. [misra-cpp2008-18-0-1]
#include <time.h>
// CHECK-MESSAGES: [[@LINE+1]]:1: warning: The C library shall not be used. [misra-cpp2008-18-0-1]
#include <wchar.h>
// CHECK-MESSAGES: [[@LINE+1]]:1: warning: The C library shall not be used. [misra-cpp2008-18-0-1]
#include <wctype.h>

#include <cassert>
#include <cctype>
#include <cerrno>
#include <cfenv>
#include <cfloat>
#include <cinttypes>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstdbool>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <ctgmath>
#include <ctime>
#include <cwchar>
#include <cwctype>
