//===--- 18-0-2.cpp - clang-tidy-misra ------------------------------------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "18-0-2.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Lex/Preprocessor.h"
#include "rules/common/BannedInclude.h"
#include <string>

namespace clang {
namespace tidy {
namespace misra {
namespace cpp2008 {

Rule_18_0_2::Rule_18_0_2(llvm::StringRef Name, ClangTidyContext *Context)
    : ClangTidyMisraCheck(Name, Context) {}

void Rule_18_0_2::registerMatchers(ast_matchers::MatchFinder *Finder) {
  using namespace clang::ast_matchers;
  Finder->addMatcher(
      callExpr(callee(functionDecl(matchesName("^(std)?::(atof|atoi|atol)$"))))
          .bind("CallExpr"),
      this);
}

void Rule_18_0_2::checkImpl(
    const ast_matchers::MatchFinder::MatchResult &Result) {
  if (const auto *callExpr = Result.Nodes.getNodeAs<CallExpr>("CallExpr")) {
    diag(callExpr->getLocStart());
    callExpr->getCallee()->dumpColor();
  }
}

} // namespace cpp2008
} // namespace misra
} // namespace tidy
} // namespace clang
