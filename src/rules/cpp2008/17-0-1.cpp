//===--- 17-0-1.cpp - clang-tidy-misra ------------------------------------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "17-0-1.h"
#include "clang/Basic/SourceLocation.h"
#include "clang/Frontend/CompilerInstance.h"
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
  CheckerImpl(Rule_17_0_1 &RuleChecker) : RuleChecker(RuleChecker) {}

private:
  static const std::set<std::string> explicitlyIllegalMacroNames;
  static const std::set<std::string> explicitlyLegalMacroNames;

  void detectViolation(const Token &MacroNameTok) {
    const std::string &name = MacroNameTok.getIdentifierInfo()->getName();
    const SourceLocation &loc = MacroNameTok.getLocation();

    // A few specific macros with two leading underscores are valid
    if (explicitlyLegalMacroNames.count(name)) {
      return;
    }
    // All other, whether exlicitly banned or starting with a leading underscore
    // constitute a violation of this rule.
    if (explicitlyIllegalMacroNames.count(name) || (name.find('_') == 0)) {
      RuleChecker.diag(loc);
    }
  }

public:
  // Detect #defines
  virtual void MacroDefined(const Token &MacroNameTok,
                            const MacroDirective *) override {
    detectViolation(MacroNameTok);
  }

  // Detect #undef
  virtual void MacroUndefined(const Token &MacroNameTok,
                              const MacroDefinition &) override {
    detectViolation(MacroNameTok);
  }

private:
  Rule_17_0_1 &RuleChecker;
};
}

const std::set<std::string> CheckerImpl::explicitlyIllegalMacroNames = {
    "__cplusplus",
    "__DATE__",
    "__FILE__",
    "__LINE__",
    "__STDC_HOSTED__",
    "__TIME__",
    "__STDC__",
    "__STDC_MB_MIGHT_NEQ_WC__",
    "__STDC_VERSION__",
    "__STDC_ISO_10646__",
    "__STDCPP_STRICT_POINTER_SAFETY__",
    "__STDCPP_THREADS__",
    "define",
    "errno",
    "assert"};

const std::set<std::string> CheckerImpl::explicitlyLegalMacroNames = {
    "__STDC_FORMAT_MACROS", "__STDC_LIMIT_MACROS"};

Rule_17_0_1::Rule_17_0_1(llvm::StringRef Name, ClangTidyContext *Context)
    : ClangTidyMisraCheck(Name, Context) {}

void Rule_17_0_1::registerPPCallbacksImpl() {
  CI->getPreprocessor().addPPCallbacks(::llvm::make_unique<CheckerImpl>(*this));
}

} // namespace cpp2008
} // namespace misra
} // namespace tidy
} // namespace clang
