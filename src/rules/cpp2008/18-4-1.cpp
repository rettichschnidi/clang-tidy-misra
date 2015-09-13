//===--- 18-4-1.cpp - clang-tidy-misra ------------------------------------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "18-4-1.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Frontend/CompilerInstance.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace misra {
namespace cpp2008 {

Rule_18_4_1::Rule_18_4_1(llvm::StringRef Name, ClangTidyContext *Context)
    : ClangTidyMisraCheck(Name, Context) {}

void Rule_18_4_1::registerMatchers(ast_matchers::MatchFinder *Finder) {
  Finder->addMatcher(newExpr().bind("new"), this);
}

void Rule_18_4_1::checkImpl(
    const ast_matchers::MatchFinder::MatchResult &Result) {
  if (const auto *newExpr = Result.Nodes.getNodeAs<CXXNewExpr>("new")) {
    // Print error on all new usages except for placement new
    assert(CI->hasASTContext());
    if (newExpr->getNumPlacementArgs() == 0 ||
        newExpr->shouldNullCheckAllocation(CI->getASTContext())) {
      diag(newExpr->getLocStart());
    }
  }
}

} // namespace cpp2008
} // namespace misra
} // namespace tidy
} // namespace clang
