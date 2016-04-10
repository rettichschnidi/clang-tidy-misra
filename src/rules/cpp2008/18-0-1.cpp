//===--- 18-0-1.cpp - clang-tidy-misra ------------------------------------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "18-0-1.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Lex/Preprocessor.h"
#include "rules/common/BannedInclude.h"

namespace clang {
namespace tidy {
namespace misra {
namespace cpp2008 {

Rule_18_0_1::Rule_18_0_1(llvm::StringRef Name, ClangTidyContext *Context)
    : ClangTidyMisraCheck(Name, Context) {}

void Rule_18_0_1::registerPPCallbacksImpl() {
  using BannedIncludePPCallback = common::BannedInclude<Rule_18_0_1>;
  getPreprocessor().addPPCallbacks(::llvm::make_unique<BannedIncludePPCallback>(
      *this,
      BannedIncludePPCallback::StringSet{
          "assert.h", "ctype.h", "errno.h", "fenv.h", "float.h", "inttypes.h",
          "iso646.h", "limits.h", "locale.h", "math.h", "setjmp.h", "signal.h",
          "stdarg.h", "stdbool.h", "stddef.h", "stdint.h", "stdlib.h",
          "string.h", "tgmath.h", "time.h", "uchar.h", "wchar.h", "wctype.h"}));
}

} // namespace cpp2008
} // namespace misra
} // namespace tidy
} // namespace clang
