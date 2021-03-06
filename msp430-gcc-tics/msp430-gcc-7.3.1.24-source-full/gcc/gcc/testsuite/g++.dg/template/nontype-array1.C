// { dg-do compile { target c++11 } }

template <char const* STR>
class Message {
};

extern char const s1[] = "hi";
char const s2[] = "hi";
constexpr char const s3[] = "hi";  // OK since C++11

constexpr char const * f() { return s3; }

int main()
{
  Message<s1> m1;  // OK (all versions)
  Message<s2> m2;  // OK for clang since C++14, for gcc since C++17
  Message<s3> m3;  // OK for clang/gcc since C++11

  static char const s4[] = "hi";
  static constexpr char const s5[] = "hi";  // OK since C++11
  Message<s4> m4;  // { dg-error "no linkage" "" { target c++14_down } }
  Message<s5> m5;  // { dg-error "no linkage" "" { target c++14_down } }
  Message<f()> m6; // { dg-error "" "" { target c++14_down } }

  char const s8[] = "hi";
  Message<s8> m8;  // { dg-error "" }
}
