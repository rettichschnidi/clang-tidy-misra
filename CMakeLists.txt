set(LLVM_LINK_COMPONENTS support)
set(CLANG_TIDY_MISRA_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_clang_library(clangTidyMISRAModule
  src/ClangTidyMisraCheck.cpp
  src/ClangTidyMisraCheck.h
  src/MISRATidyModule.cpp
  src/RuleHeadlineTexts.cpp
  src/RuleHeadlineTexts.h
  src/rules/c2012/17.1.cpp
  src/rules/c2012/17.1.h
  src/rules/c2012/6.2.cpp
  src/rules/c2012/6.2.h
  src/rules/cpp2008/2-13-3.cpp
  src/rules/cpp2008/2-13-3.h
  src/rules/cpp2008/6-4-1.cpp
  src/rules/cpp2008/6-4-1.h
  src/rules/cpp2008/6-4-2.cpp
  src/rules/cpp2008/6-4-2.h
  src/rules/cpp2008/9-5-1.cpp
  src/rules/cpp2008/9-5-1.h
  src/rules/cpp2008/10-3-2.cpp
  src/rules/cpp2008/10-3-2.h
  src/rules/cpp2008/10-3-3.cpp
  src/rules/cpp2008/10-3-3.h
  src/rules/cpp2008/11-0-1.cpp
  src/rules/cpp2008/11-0-1.h
  src/rules/cpp2008/12-8-2.cpp
  src/rules/cpp2008/12-8-2.h
  src/rules/cpp2008/15-5-1.cpp
  src/rules/cpp2008/15-5-1.h
  src/rules/cpp2008/16-3-1.cpp
  src/rules/cpp2008/16-3-1.h
  src/rules/cpp2008/16-3-2.cpp
  src/rules/cpp2008/16-3-2.h
  src/rules/cpp2008/17-0-1.cpp
  src/rules/cpp2008/17-0-1.h
  src/rules/cpp2008/17-0-5.cpp
  src/rules/cpp2008/17-0-5.h
  src/rules/cpp2008/18-0-1.cpp
  src/rules/cpp2008/18-0-1.h
  src/rules/cpp2008/18-0-5.cpp
  src/rules/cpp2008/18-0-5.h
  src/rules/cpp2008/18-4-1.cpp
  src/rules/cpp2008/18-4-1.h
  src/rules/cpp2008/18-7-1.cpp
  src/rules/cpp2008/18-7-1.h
  src/rules/cpp2008/19-3-1.cpp
  src/rules/cpp2008/19-3-1.h
  src/rules/cpp2008/27-0-1.cpp
  src/rules/cpp2008/27-0-1.h
  src/rules/common/BannedInclude.h
  src/rules/common/BannedMacro.h

  LINK_LIBS
  clangAST
  clangASTMatchers
  clangBasic
  clangLex
  clangTidy
  )

target_include_directories(clangTidyMISRAModule PRIVATE src/)

#Add our tests directory
add_subdirectory(test)
