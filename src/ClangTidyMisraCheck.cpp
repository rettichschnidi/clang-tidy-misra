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
      Context(Context), CI(nullptr),
      IgnoreInvalidLocations(Options.get("IgnoreInvalidLocations", true)),
      IgnoreBuiltInLocations(Options.get("IgnoreBuiltInLocations", true)),
      IgnoreCommandLineLocations(
          Options.get("IgnoreCommandLineLocations", false)) {}

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

void ClangTidyMisraCheck::storeOptions(ClangTidyOptions::OptionMap &Opts) {
  Options.store(Opts, "IgnoreInvalidLocations", IgnoreInvalidLocations);
  Options.store(Opts, "IgnoreBuiltInLocations", IgnoreBuiltInLocations);
  Options.store(Opts, "IgnoreCommandLineLocations", IgnoreCommandLineLocations);
}

void ClangTidyMisraCheck::checkImpl(
    const ast_matchers::MatchFinder::MatchResult &) {}

void ClangTidyMisraCheck::diag(SourceLocation Loc, DiagnosticIDs::Level Level) {
  if (!isIgnored(Loc)) {
    ClangTidyCheck::diag(Loc, ruleHeadlines.at(CheckName), Level);
  }
}

bool ClangTidyMisraCheck::isC() const {
  return (getCI().getLangOpts().C99 || getCI().getLangOpts().C11);
}

bool ClangTidyMisraCheck::isCPlusPlus() const {
  return getCI().getLangOpts().CPlusPlus;
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

std::string
ClangTidyMisraCheck::srcLocToTokenString(const SourceLocation start) {
  const ASTContext &C = getASTContext();
  const SourceManager &SM = C.getSourceManager();
  const LangOptions LO = C.getLangOpts();
  const SourceLocation spellLoc = SM.getSpellingLoc(start);
  unsigned tokenLength = Lexer::MeasureTokenLength(spellLoc, SM, LO);
  return std::string(SM.getCharacterData(spellLoc),
                     SM.getCharacterData(spellLoc) + tokenLength);
}

bool ClangTidyMisraCheck::isIgnored(clang::SourceLocation loc) {
  if (loc.isInvalid()) {
    return IgnoreInvalidLocations;
  }
  if (isBuiltIn(loc)) {
    return IgnoreBuiltInLocations;
  }
  if (isCommandLine(loc)) {
    return IgnoreCommandLineLocations;
  }
  return false;
}

} // namespace misra
} // namespace tidy
} // namespace clang
