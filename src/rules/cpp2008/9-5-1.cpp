//===--- 9-5-1.cpp - clang-tidy-misra -------------------------------------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "9-5-1.h"
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

Rule_9_5_1::Rule_9_5_1(llvm::StringRef Name, ClangTidyContext *Context)
    : ClangTidyMisraCheck(Name, Context) {}

void Rule_9_5_1::registerMatchers(ast_matchers::MatchFinder *Finder) {
  Finder->addMatcher(recordDecl().bind("RecordDecl"), this);
}

void Rule_9_5_1::checkImpl(
    const ast_matchers::MatchFinder::MatchResult &Result) {
  if (const auto *RD = Result.Nodes.getNodeAs<CXXRecordDecl>("RecordDecl")) {
    if (RD->getTagKind() == TTK_Union) {
      diag(RD->getLocation());
    }
  }
}

} // namespace cpp2008
} // namespace misra
} // namespace tidy
} // namespace clang
