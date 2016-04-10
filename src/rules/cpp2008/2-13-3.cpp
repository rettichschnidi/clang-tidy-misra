//===--- 2-13-3.cpp - clang-tidy-misra ------------------------------------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "2-13-3.h"
#include "clang/ASTMatchers/ASTMatchers.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"
#include "clang/Frontend/CompilerInstance.h"

namespace clang {
namespace tidy {
namespace misra {
namespace cpp2008 {

using namespace clang::ast_matchers;

Rule_2_13_3::Rule_2_13_3(llvm::StringRef Name, ClangTidyContext *Context)
    : ClangTidyMisraCheck(Name, Context) {}

void Rule_2_13_3::registerMatchers(ast_matchers::MatchFinder *Finder) {
  Finder->addMatcher(implicitCastExpr().bind("ImplicitCastExpr"), this);
  Finder->addMatcher(integerLiteral().bind("IntegerLiteral"), this);
}

void Rule_2_13_3::checkImpl(
    const ast_matchers::MatchFinder::MatchResult &Result) {
  if (const auto *castExpr =
          Result.Nodes.getNodeAs<ImplicitCastExpr>("ImplicitCastExpr")) {
    // Bail out early if this location should not be checked
    if (doIgnore(castExpr->getLocStart())) {
      return;
    }

    const IntegerLiteral *intLiteral =
        dyn_cast<IntegerLiteral>(castExpr->getSubExpr());
    // Bail out if this node is not an integer literal beeing casted
    if (!intLiteral) {
      return;
    }

    // Bail out if the source is already an unsigned integer
    if (isUnsignedIntegerLiteral(intLiteral)) {
      return;
    }

    // Bail out if this is not an integer to integer casting operation
    if (castExpr->getCastKind() != CK_IntegralCast) {
      return;
    }

    // Bail out if the integer simply gets truncated to a smaller integral type
    // of the same signedness
    if (castExpr->getSubExpr()->getType()->isSignedIntegerOrEnumerationType() ==
        castExpr->getType()->isSignedIntegerOrEnumerationType()) {
      return;
    }

    // Figure out if the parent is an explicit casting operation which would
    // legalizes this implicit one.
    const auto &parents = getASTContext().getParents(*castExpr);
    assert(parents.size() == 1 && "Expect exactly one parent node.");

    // Bail out if this is not the first if in a if...else-if clause
    if (parents[0].get<ExplicitCastExpr>() != nullptr) {
      return;
    }

    // At this point we can be fairly sure that this casting is the result of
    // a rule violation.
    diag(intLiteral->getLocation());
    return;
  }

  if (const auto *intLiteral =
          Result.Nodes.getNodeAs<IntegerLiteral>("IntegerLiteral")) {
    if (isUnsignedIntegerLiteral(intLiteral)) {
      dealWithUnsignedInteger(intLiteral);
    }
  }
}

bool Rule_2_13_3::isUnsignedIntegerLiteral(const IntegerLiteral *intLiteral) {
  llvm::APSInt result;
  intLiteral->EvaluateAsInt(result, getASTContext(), Expr::SE_NoSideEffects);
  return result.isUnsigned();
}

void Rule_2_13_3::dealWithUnsignedInteger(const IntegerLiteral *intLiteral) {
  // See if one char after the integer literal is a "U"
  std::string lexem = srcLocToTokenString(intLiteral->getLocStart());
  if (lexem.rfind("U") == std::string::npos) {
    diag(intLiteral->getLocation());
  }
}

} // namespace cpp2008
} // namespace misra
} // namespace tidy
} // namespace clang
