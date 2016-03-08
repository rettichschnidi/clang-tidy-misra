//===--- 6.2.cpp - clang-tidy-misra ---------------------------------------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "6.2.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Lex/Preprocessor.h"
#include "rules/common/BannedInclude.h"
#include "rules/common/BannedMacro.h"
#include <cassert>

namespace clang {
namespace tidy {
namespace misra {
namespace c2012 {

Rule_6_2::Rule_6_2(llvm::StringRef Name, ClangTidyContext *Context)
    : ClangTidyMisraCheck(Name, Context) {}

void Rule_6_2::registerMatchers(ast_matchers::MatchFinder *Finder) {
  using namespace ast_matchers;
  Finder->addMatcher(fieldDecl(hasType(isInteger())).bind("FieldDecl"), this);
}

void Rule_6_2::checkImpl(const ast_matchers::MatchFinder::MatchResult &Result) {
  auto FD = *Result.Nodes.getNodeAs<FieldDecl>("FieldDecl");

  // Rule applies only to bit fields
  if (!FD.isBitField()) {
    return;
  }

  // Rule applies only to single bit fields
  if (FD.getBitWidthValue(CI->getASTContext()) != 1) {
    return;
  }

  // Rule does not apply to unnamed bit fields
  if (FD.isUnnamedBitfield()) {
    return;
  }

  // At this stage, a signed integer type qualifies as error
  assert(FD.getType().getTypePtrOrNull());
  if (FD.getType().getTypePtr()->isSignedIntegerType()) {
    diag(FD.getLocStart());
  }
}

} // namespace c2012
} // namespace misra
} // namespace tidy
} // namespace clang
