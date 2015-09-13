//===--- 17.1.cpp - clang-tidy-misra --------------------------------------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "17.1.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Lex/Preprocessor.h"
#include "rules/common/BannedInclude.h"
#include "rules/common/BannedMacro.h"

namespace clang {
namespace tidy {
namespace misra {
namespace c2012 {

Rule_17_1::Rule_17_1(llvm::StringRef Name, ClangTidyContext *Context)
    : ClangTidyMisraCheck(Name, Context) {}

void Rule_17_1::registerPPCallbacksImpl() {
  using BannedIncludePPCallback = common::BannedInclude<Rule_17_1>;
  CI->getPreprocessor().addPPCallbacks(
      ::llvm::make_unique<BannedIncludePPCallback>(
          *this, BannedIncludePPCallback::StringSet{"stdarg.h"}));

  using BannedMacroPPCallback = common::BannedMacro<Rule_17_1>;
  CI->getPreprocessor().addPPCallbacks(
      ::llvm::make_unique<BannedMacroPPCallback>(
          *this, BannedMacroPPCallback::StringSet{"va_arg", "va_start",
                                                  "va_end", "va_copy"}));
}

void Rule_17_1::registerMatchers(ast_matchers::MatchFinder *Finder) {
  Finder->addMatcher(ast_matchers::varDecl().bind("VarDecl"), this);
}

void Rule_17_1::checkImpl(
    const ast_matchers::MatchFinder::MatchResult &Result) {
  auto VD = *Result.Nodes.getNodeAs<VarDecl>("VarDecl");

  // Report error on usage of type "va_list"
  if (VD.getType().getDesugaredType(*Result.Context) ==
      Result.Context->getBuiltinVaListType().getDesugaredType(
          *Result.Context)) {
    diag(VD.getLocStart());
  }
}

} // namespace c2012
} // namespace misra
} // namespace tidy
} // namespace clang
