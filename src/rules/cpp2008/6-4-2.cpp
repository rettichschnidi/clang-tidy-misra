//===--- 6-4-2.cpp - clang-tidy-misra -------------------------------------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "6-4-2.h"
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

Rule_6_4_2::Rule_6_4_2(llvm::StringRef Name, ClangTidyContext *Context)
    : ClangTidyMisraCheck(Name, Context) {}

void Rule_6_4_2::registerMatchers(ast_matchers::MatchFinder *Finder) {
  Finder->addMatcher(
      ifStmt(hasElse(ifStmt(unless(hasElse(stmt()))).bind("if"))), this);
}

void Rule_6_4_2::checkImpl(
    const ast_matchers::MatchFinder::MatchResult &Result) {
  if (const auto *ifStmt = Result.Nodes.getNodeAs<IfStmt>("if")) {
    diag(ifStmt->getLocStart());
  }
}

} // namespace cpp2008
} // namespace misra
} // namespace tidy
} // namespace clang
