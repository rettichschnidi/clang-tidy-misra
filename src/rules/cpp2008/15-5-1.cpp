//===--- 15-5-1.cpp - clang-tidy-misra ------------------------------------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "15-5-1.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

namespace {
template <typename T> const clang::Stmt *searchStmt(const clang::Stmt *S) {
  if (!S) {
    return nullptr;
  }

  if (llvm::isa<T>(S)) {
    return S;
  }

  for (auto c : S->children()) {
    if (auto b = searchStmt<T>(c)) {
      return b;
    }
  }

  return nullptr;
}
}

namespace clang {
namespace tidy {
namespace misra {
namespace cpp2008 {

using namespace clang::ast_matchers;

Rule_15_5_1::Rule_15_5_1(llvm::StringRef Name, ClangTidyContext *Context)
    : ClangTidyMisraCheck(Name, Context) {}

void Rule_15_5_1::registerMatchers(ast_matchers::MatchFinder *Finder) {
  auto matcher = cxxDestructorDecl().bind("CXXDestructorDecl");
  Finder->addMatcher(matcher, this);
}

void Rule_15_5_1::checkImpl(
    const ast_matchers::MatchFinder::MatchResult &Result) {
  if (const auto *D =
          Result.Nodes.getNodeAs<CXXDestructorDecl>("CXXDestructorDecl")) {
    // No body -> no error possible!
    if (!D->hasBody()) {
      return;
    }

    Stmt *body = D->getBody();
    auto cxxThrowStmt = searchStmt<CXXThrowExpr>(body);
    auto cxxCatchStmt = searchStmt<CXXCatchStmt>(body);

    // dctor throws, check if there's a catch block
    if (cxxThrowStmt && !cxxCatchStmt) {
      diag(cxxThrowStmt->getLocStart());
    }
  }
}

} // namespace cpp2008
} // namespace misra
} // namespace tidy
} // namespace clang
