//===--- ClangTidyMisraCheck.cpp - clang-tidy-misra -----------------------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "ClangTidyMisraCheck.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Lex/Lexer.h"
#include "llvm/Support/Debug.h"
#include "RuleHeadlineTexts.h"

namespace clang {
namespace tidy {
namespace misra {

ClangTidyMisraCheck::ClangTidyMisraCheck(llvm::StringRef CheckName,
                                         ClangTidyContext *Context)
    : ClangTidyCheck(CheckName, Context), CheckName(CheckName),
      Context(Context), CI(nullptr) {}

void ClangTidyMisraCheck::registerPPCallbacks(CompilerInstance &Compiler) {
  this->CI = &Compiler;

  if (checkerIsActive()) {
    registerPPCallbacksImpl();
  }
}

void ClangTidyMisraCheck::registerPPCallbacksImpl() {}

void ClangTidyMisraCheck::check(
    const ast_matchers::MatchFinder::MatchResult &Result) {

  if (checkerIsActive()) {
    checkImpl(Result);
  }
}

void ClangTidyMisraCheck::checkImpl(
    const ast_matchers::MatchFinder::MatchResult &) {}

DiagnosticBuilder ClangTidyMisraCheck::diag(SourceLocation Loc,
                                            DiagnosticIDs::Level Level) {
  return ClangTidyCheck::diag(Loc, ruleHeadlines.at(CheckName), Level);
}

bool ClangTidyMisraCheck::isC() const {
  return (getCI().getLangOpts().C99 || getCI().getLangOpts().C11);
}

bool ClangTidyMisraCheck::isCPlusPlus() const {
  return getCI().getLangOpts().CPlusPlus;
}

bool ClangTidyMisraCheck::isInSystemHeader(SourceLocation loc) const {
  const SourceManager &sourceManager = getCI().getSourceManager();
  return sourceManager.isInSystemHeader(loc);
}

bool ClangTidyMisraCheck::isBuiltIn(clang::SourceLocation loc) const {
  const SourceManager &sourceManager = getCI().getSourceManager();
  const char *const filename = sourceManager.getPresumedLoc(loc).getFilename();
  return (strcmp(filename, "<built-in>") == 0);
}

bool ClangTidyMisraCheck::isCommandLine(SourceLocation loc) {
  const SourceManager &sourceManager = getCI().getSourceManager();
  const char *const filename = sourceManager.getPresumedLoc(loc).getFilename();
  return (strcmp(filename, "<command line>") == 0);
}

ASTContext &ClangTidyMisraCheck::getASTContext() const {
  assert(getCI().hasASTContext() && "Compiler instance needs AST context!");
  return getCI().getASTContext();
}

Preprocessor &ClangTidyMisraCheck::getPreprocessor() const {
  assert(getCI().hasPreprocessor() && "Compiler instance has no preprocessor!");
  return getCI().getPreprocessor();
}

CompilerInstance &ClangTidyMisraCheck::getCI() const {
  assert(CI && "Need CompilerInstance");
  return *CI;
}

bool ClangTidyMisraCheck::checkerIsActive() const {
  using std::string;

  assert((isCPlusPlus() || isC()) && "Language must be either C or C++!");
  assert(((this->CheckName.find("misra-c2012-") != string::npos) ||
          (this->CheckName.find("misra-cpp2008-") != string::npos)) &&
         "Rule must belong either to MISRA C++:2008 or to C: 2012");

  const bool enableMisraCpp2008 =
      isCPlusPlus() && this->CheckName.find("misra-cpp2008-") != string::npos;
  const bool enableMisraC2012 =
      isC() && this->CheckName.find("misra-c2012-") != string::npos;

  return enableMisraCpp2008 || enableMisraC2012;
}

bool ClangTidyMisraCheck::doIgnore(clang::SourceLocation loc) {
  if (loc.isInvalid()) {
    return true;
  }
  if (isBuiltIn(loc)) {
    return true;
  }
  if (isCommandLine(loc)) {
    return true;
  }
  if (isInSystemHeader(loc)) {
    return IgnoreSystemHeaders;
  }

  // Do not check source code locations which are not originating from an actual
  // file.
  auto spellingLocation = getCI().getSourceManager().getSpellingLoc(loc);
  auto fileName = getCI().getSourceManager().getFilename(spellingLocation);
  if (fileName.empty()) {
    return true;
  }
  return false;
}

} // namespace misra
} // namespace tidy
} // namespace clang
