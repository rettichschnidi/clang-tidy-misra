//===--- 10-3-2.cpp - clang-tidy-misra ------------------------------------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "10-3-2.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

namespace clang {
namespace tidy {
namespace misra {
namespace cpp2008 {

using namespace clang::ast_matchers;

Rule_10_3_2::Rule_10_3_2(llvm::StringRef Name, ClangTidyContext *Context)
    : ClangTidyMisraCheck(Name, Context) {}

void Rule_10_3_2::registerMatchers(ast_matchers::MatchFinder *Finder) {
  Finder->addMatcher(
      methodDecl(isVirtual(), unless(isImplicit())).bind("VirtualMethod"),
      this);
}

void Rule_10_3_2::checkImpl(
    const ast_matchers::MatchFinder::MatchResult &Result) {
  if (const auto *methodDecl =
          Result.Nodes.getNodeAs<CXXMethodDecl>("VirtualMethod")) {
    if (!methodDecl->isOutOfLine() &&
        !methodDecl->getCanonicalDecl()->isVirtualAsWritten()) {
      diag(methodDecl->getLocation());
    }
  }
}

} // namespace cpp2008
} // namespace misra
} // namespace tidy
} // namespace clang
