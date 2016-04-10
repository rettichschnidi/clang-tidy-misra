//===--- 18-7-1.cpp - clang-tidy-misra ------------------------------------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "18-7-1.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Lex/Preprocessor.h"
#include "rules/common/BannedInclude.h"
#include "rules/common/BannedMacro.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace misra {
namespace cpp2008 {

Rule_18_7_1::Rule_18_7_1(llvm::StringRef Name, ClangTidyContext *Context)
    : ClangTidyMisraCheck(Name, Context) {}

void Rule_18_7_1::registerPPCallbacksImpl() {
  using BannedIncludePPCallback = common::BannedInclude<Rule_18_7_1>;
  getPreprocessor().addPPCallbacks(::llvm::make_unique<BannedIncludePPCallback>(
      *this, BannedIncludePPCallback::StringSet{"csignal"}));

  using BannedMacroPPCallback = common::BannedMacro<Rule_18_7_1>;
  getPreprocessor().addPPCallbacks(::llvm::make_unique<BannedMacroPPCallback>(
      *this, BannedMacroPPCallback::StringSet{
                 "SIGABRT", "SIGFPE", "SIGILL", "SIGINT", "SIGSEGV", "SIGTERM",
                 "SIG_DFL", "SIG_IGN", "SIG_ERR"}));
}

void Rule_18_7_1::registerMatchers(ast_matchers::MatchFinder *Finder) {
  Finder->addMatcher(callExpr(callee(functionDecl(anyOf(hasName("::signal"),
                                                        hasName("::raise")))))
                         .bind("CallExpr"),
                     this);

  Finder->addMatcher(
      varDecl(hasType(namedDecl(hasName("::sig_atomic_t")))).bind("VarDecl"),
      this);
}

void Rule_18_7_1::checkImpl(
    const ast_matchers::MatchFinder::MatchResult &Result) {
  if (const auto *call = Result.Nodes.getNodeAs<CallExpr>("CallExpr")) {
    diag(call->getLocStart());
  }

  if (const auto *varDecl = Result.Nodes.getNodeAs<VarDecl>("VarDecl")) {
    diag(varDecl->getTypeSpecStartLoc());
  }
}

} // namespace cpp2008
} // namespace misra
} // namespace tidy
} // namespace clang
