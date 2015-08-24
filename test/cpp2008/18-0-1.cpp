// RUN: echo [{ '"directory"': '"."', '"command"': '"clang++ -std=c++11 -c %s"', '"file"': '"%s"'}] > %T/compile_commands.json
// RUN: "%clang"-tidy -checks=misra-cpp2008-18-0-1 -p=%T %s | FileCheck %s
// CHECK: :[[@LINE+1]]:1: error: The C library shall not be used. [misra-cpp2008-18-0-1]
#include <assert.h>
// CHECK: :[[@LINE+1]]:1: error: The C library shall not be used. [misra-cpp2008-18-0-1]
#include <ctype.h>
// CHECK: :[[@LINE+1]]:1: error: The C library shall not be used. [misra-cpp2008-18-0-1]
#include <errno.h>
// CHECK: :[[@LINE+1]]:1: error: The C library shall not be used. [misra-cpp2008-18-0-1]
#include <fenv.h>
// CHECK: :[[@LINE+1]]:1: error: The C library shall not be used. [misra-cpp2008-18-0-1]
#include <float.h>
// CHECK: :[[@LINE+1]]:1: error: The C library shall not be used. [misra-cpp2008-18-0-1]
#include <inttypes.h>
// CHECK: :[[@LINE+1]]:1: error: The C library shall not be used. [misra-cpp2008-18-0-1]
#include <iso646.h>
// CHECK: :[[@LINE+1]]:1: error: The C library shall not be used. [misra-cpp2008-18-0-1]
#include <limits.h>
// CHECK: :[[@LINE+1]]:1: error: The C library shall not be used. [misra-cpp2008-18-0-1]
#include <locale.h>
// CHECK: :[[@LINE+1]]:1: error: The C library shall not be used. [misra-cpp2008-18-0-1]
#include <math.h>
// CHECK: :[[@LINE+1]]:1: error: The C library shall not be used. [misra-cpp2008-18-0-1]
#include <setjmp.h>
// CHECK: :[[@LINE+1]]:1: error: The C library shall not be used. [misra-cpp2008-18-0-1]
#include <signal.h>
// CHECK: :[[@LINE+1]]:1: error: The C library shall not be used. [misra-cpp2008-18-0-1]
#include <stdarg.h>
// CHECK: :[[@LINE+1]]:1: error: The C library shall not be used. [misra-cpp2008-18-0-1]
#include <stdbool.h>
// CHECK: :[[@LINE+1]]:1: error: The C library shall not be used. [misra-cpp2008-18-0-1]
#include <stddef.h>
// CHECK: :[[@LINE+1]]:1: error: The C library shall not be used. [misra-cpp2008-18-0-1]
#include <stdint.h>
// CHECK: :[[@LINE+1]]:1: error: The C library shall not be used. [misra-cpp2008-18-0-1]
#include <stdlib.h>
// CHECK: :[[@LINE+1]]:1: error: The C library shall not be used. [misra-cpp2008-18-0-1]
#include <string.h>
// CHECK: :[[@LINE+1]]:1: error: The C library shall not be used. [misra-cpp2008-18-0-1]
#include <tgmath.h>
// CHECK: :[[@LINE+1]]:1: error: The C library shall not be used. [misra-cpp2008-18-0-1]
#include <time.h>
// CHECK: :[[@LINE+1]]:1: error: The C library shall not be used. [misra-cpp2008-18-0-1]
#include <wchar.h>
// CHECK: :[[@LINE+1]]:1: error: The C library shall not be used. [misra-cpp2008-18-0-1]
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
