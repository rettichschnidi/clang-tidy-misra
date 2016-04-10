//===--- 17-0-5.cpp - clang-tidy-misra ------------------------------------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "17-0-5.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Lex/MacroArgs.h"
#include "clang/Lex/MacroInfo.h"
#include "clang/Lex/PPCallbacks.h"
#include "clang/Lex/Preprocessor.h"
#include "clang/Lex/Token.h"
#include <set>
#include <string>

namespace clang {
namespace tidy {
namespace misra {
namespace cpp2008 {

namespace {
class CheckerImpl : public clang::PPCallbacks {
public:
  CheckerImpl(Rule_17_0_5 &RuleChecker) : RuleChecker(RuleChecker) {}

private:
  static const std::set<std::string> IllegalFunctions;

public:
  virtual void MacroExpands(const Token &MacroNameTok, const MacroDefinition &,
                            SourceRange Range, const MacroArgs *) override {
    const std::string &macroName = MacroNameTok.getIdentifierInfo()->getName();
    if (IllegalFunctions.count(macroName)) {
      RuleChecker.diag(Range.getBegin());
    }
  }

private:
  Rule_17_0_5 &RuleChecker;
};

const std::set<std::string> CheckerImpl::IllegalFunctions = {"setjmp"};
}

using namespace clang::ast_matchers;

Rule_17_0_5::Rule_17_0_5(llvm::StringRef Name, ClangTidyContext *Context)
    : ClangTidyMisraCheck(Name, Context) {}

void Rule_17_0_5::registerMatchers(ast_matchers::MatchFinder *Finder) {
  auto matcher =
      callExpr(callee(functionDecl(hasName("longjmp")))).bind("CallExpr");
  Finder->addMatcher(matcher, this);
}

void Rule_17_0_5::registerPPCallbacksImpl() {
  getPreprocessor().addPPCallbacks(::llvm::make_unique<CheckerImpl>(*this));
}

void Rule_17_0_5::checkImpl(
    const ast_matchers::MatchFinder::MatchResult &Result) {
  if (const auto *calExpr = Result.Nodes.getNodeAs<CallExpr>("CallExpr")) {
    diag(calExpr->getLocStart());
  }
}

} // namespace cpp2008
} // namespace misra
} // namespace tidy
} // namespace clang
