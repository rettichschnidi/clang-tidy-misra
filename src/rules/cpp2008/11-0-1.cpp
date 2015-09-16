//===--- 11-0-1.cpp - clang-tidy-misra ------------------------------------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "11-0-1.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

namespace clang {
namespace tidy {
namespace misra {
namespace cpp2008 {

using namespace clang::ast_matchers;

Rule_11_0_1::Rule_11_0_1(llvm::StringRef Name, ClangTidyContext *Context)
    : ClangTidyMisraCheck(Name, Context) {}

void Rule_11_0_1::registerMatchers(ast_matchers::MatchFinder *Finder) {
  Finder->addMatcher(recordDecl().bind("RecrodDecl"), this);
}

void Rule_11_0_1::checkImpl(
    const ast_matchers::MatchFinder::MatchResult &Result) {
  if (const auto *decl = Result.Nodes.getNodeAs<CXXRecordDecl>("RecrodDecl")) {
    // Sort out any non-class or struct declarations
    if ((decl->isClass() || decl->isStruct()) == false) {
      return;
    }
    // We can only judge classes with a visible definition
    if (decl->hasDefinition() == false) {
      return;
    }
    // Rule applies to non-POD classes only
    // Note: POD definition from C++11, not 03. Problem?
    if (decl->isPOD()) {
      return;
    }

    // Report all non-private members
    for (const FieldDecl *fieldDecl : decl->fields()) {
      if (fieldDecl->getAccess() != AS_private) {
        diag(fieldDecl->getLocStart());
      }
    }
  }
}

} // namespace cpp2008
} // namespace misra
} // namespace tidy
} // namespace clang
