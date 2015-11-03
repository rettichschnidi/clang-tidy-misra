//===--- 18-0-5.cpp - clang-tidy-misra ------------------------------------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "18-0-5.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Lex/MacroArgs.h"
#include "clang/Lex/MacroInfo.h"
#include "clang/Lex/PPCallbacks.h"
#include "clang/Lex/Preprocessor.h"
#include "clang/Lex/Token.h"
#include <set>
#include <string>

namespace clang {
namespace tidy {
namespace misra {
namespace cpp2008 {

using namespace clang::ast_matchers;

Rule_18_0_5::Rule_18_0_5(llvm::StringRef Name, ClangTidyContext *Context)
    : ClangTidyMisraCheck(Name, Context) {}

void Rule_18_0_5::registerMatchers(ast_matchers::MatchFinder *Finder) {
  auto matcher =
      callExpr(callee(functionDecl(anyOf(
                   hasName("strcpy"), hasName("strcmp"), hasName("strcat"),
                   hasName("strchr"), hasName("strspn"), hasName("strcspn"),
                   hasName("strpbrk"), hasName("strrchr"), hasName("strstr"),
                   hasName("strtok"), hasName("strlen")))))
          .bind("CallExpr");
  Finder->addMatcher(matcher, this);
}

void Rule_18_0_5::checkImpl(
    const ast_matchers::MatchFinder::MatchResult &Result) {

  if (const auto *calExpr = Result.Nodes.getNodeAs<CallExpr>("CallExpr")) {
    diag(calExpr->getLocStart());
  }
}

} // namespace cpp2008
} // namespace misra
} // namespace tidy
} // namespace clang
