//===--- 16-3-2.cpp - clang-tidy-misra ------------------------------------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "16-3-2.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Lex/MacroInfo.h"
#include "clang/Lex/PPCallbacks.h"
#include "clang/Lex/Preprocessor.h"
#include "clang/Lex/Token.h"

namespace clang {
namespace tidy {
namespace misra {
namespace cpp2008 {

namespace {
class CheckerImpl : public clang::PPCallbacks {
public:
  CheckerImpl(Rule_16_3_2 &RuleChecker) : RuleChecker(RuleChecker) {}

  virtual void MacroDefined(const Token &, const MacroDirective *MD) override {
    const MacroInfo *macroInfo = MD->getMacroInfo();

    for (MacroInfo::tokens_iterator I = macroInfo->tokens_begin(),
                                    E = macroInfo->tokens_end();
         I != E; ++I) {
      const std::string tokenType = I->getName();
      // Count occurrences of "hash" and "hashhash"
      if (tokenType.find("hash") == 0) {
        RuleChecker.diag(I->getLocation());
        break;
      }
    }
  }

private:
  Rule_16_3_2 &RuleChecker;
};
}

Rule_16_3_2::Rule_16_3_2(llvm::StringRef Name, ClangTidyContext *Context)
    : ClangTidyMisraCheck(Name, Context) {}

void Rule_16_3_2::registerPPCallbacksImpl() {
  CI->getPreprocessor().addPPCallbacks(::llvm::make_unique<CheckerImpl>(*this));
}

} // namespace cpp2008
} // namespace misra
} // namespace tidy
} // namespace clang
