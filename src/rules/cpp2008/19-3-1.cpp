//===--- 19-3-1.cpp - clang-tidy-misra ------------------------------------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "19-3-1.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Lex/Preprocessor.h"
#include "rules/common/BannedMacro.h"

namespace clang {
namespace tidy {
namespace misra {
namespace cpp2008 {

Rule_19_3_1::Rule_19_3_1(llvm::StringRef Name, ClangTidyContext *Context)
    : ClangTidyMisraCheck(Name, Context) {}

void Rule_19_3_1::registerPPCallbacksImpl() {
  using BannedMacroPPCallback = common::BannedMacro<Rule_19_3_1>;
  CI->getPreprocessor().addPPCallbacks(
      ::llvm::make_unique<BannedMacroPPCallback>(
          *this, BannedMacroPPCallback::StringSet{"errno"}));
}

} // namespace cpp2008
} // namespace misra
} // namespace tidy
} // namespace clang
