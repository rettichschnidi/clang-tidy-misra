//===--- 6-4-1.cpp - clang-tidy-misra -------------------------------------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "6-4-1.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Lex/Preprocessor.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace misra {
namespace cpp2008 {

Rule_6_4_1::Rule_6_4_1(llvm::StringRef Name, ClangTidyContext *Context)
    : ClangTidyMisraCheck(Name, Context) {}

void Rule_6_4_1::registerMatchers(ast_matchers::MatchFinder *Finder) {
  Finder->addMatcher(ifStmt().bind("if"), this);
}

void Rule_6_4_1::checkImpl(
    const ast_matchers::MatchFinder::MatchResult &Result) {
  if (const auto *ifStmt = Result.Nodes.getNodeAs<IfStmt>("if")) {
    const Stmt *thenStmt = ifStmt->getThen();
    const Stmt *elseStmt = ifStmt->getElse();
    // Check if then has a body
    if (thenStmt && isa<CompoundStmt>(thenStmt) == false) {
      diag(thenStmt->getLocStart());
    }
    // Check if else has a body or another if statement
    if (elseStmt &&
        ((isa<CompoundStmt>(elseStmt) || isa<IfStmt>(elseStmt)) == false)) {
      diag(elseStmt->getLocStart());
    }
  }
}

} // namespace cpp2008
} // namespace misra
} // namespace tidy
} // namespace clang
