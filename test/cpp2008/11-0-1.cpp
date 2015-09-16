// RUN: %python %S/../check_clang_tidy.py %s misra-cpp2008-11-0-1 %t

struct PodStruct {
  int defaultMember1;
  int defaultMember2;
};

class PodClass {
public:
  int publicMember1;
  int publicMember2;
};

class AllPrivateClass {
  int implicitPrivateMember;

private:
  int explicitPrivateMember;
};

struct NonPodStruct {
  int implicitPublicMember; // CHECK-MESSAGES: :[[@LINE]]:3: warning: Member data in non-POD class types shall be private. [misra-cpp2008-11-0-1]
public:
  int explicitPublicMember; // CHECK-MESSAGES: :[[@LINE]]:3: warning: Member data in non-POD class types shall be private. [misra-cpp2008-11-0-1]
protected:
  int explicitProtectedMember; // CHECK-MESSAGES: :[[@LINE]]:3: warning: Member data in non-POD class types shall be private. [misra-cpp2008-11-0-1]
private:
  int explicitPrivateMember;
};

class NotAllPrivateClass {
  int implicitPrivateMember;

private:
  int explicitPrivateMember;

protected:
  int protectedMember; // CHECK-MESSAGES: :[[@LINE]]:3: warning: Member data in non-POD class types shall be private. [misra-cpp2008-11-0-1]
public:
  int publicMember; // CHECK-MESSAGES: :[[@LINE]]:3: warning: Member data in non-POD class types shall be private. [misra-cpp2008-11-0-1]
};
