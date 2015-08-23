set(LLVM_LINK_COMPONENTS support)
set(CLANG_TIDY_MISRA_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_clang_library(clangTidyMISRAModule
  src/MISRATidyModule.cpp
  src/ClangTidyMisraCheck.h
  src/ClangTidyMisraCheck.cpp
  src/RuleHeadlineTexts.h
  src/RuleHeadlineTexts.cpp
  src/rules/common/BannedInclude.h
  src/rules/common/BannedMacro.h
  src/rules/c2012/17.1.h
  src/rules/c2012/17.1.cpp

  LINK_LIBS
  clangAST
  clangASTMatchers
  clangBasic
  clangLex
  clangTidy
  )

target_include_directories(clangTidyMISRAModule PUBLIC src/)

#Add our tests directory
add_subdirectory(test)
