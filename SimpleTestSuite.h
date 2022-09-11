#pragma once
//+-----------------------------------------------------------------------------
// 
//  File:         SerialTestSuite.h
//  Description:  A simple test suite for Throw-the-switch's Unity test framework
//                (http://www.throwtheswitch.org/unity) supported by the PlatformIO
//                (http://www.platformio.org/) development environment.
//
//  History:      09/10/2022 - Original version.
//  
//------------------------------------------------------------------------------
//  Feel free to use in any way you wish; but please, be kind and do good!
//------------------------------------------------------------------------------
#include <unity.h>

#ifdef ARDUINO
# include <Arduino.h>
#endif

#include <functional>
#include <vector>
#include <string>

typedef void (*TestFunc)(void);

class test_suite {
  typedef std::tuple<std::string, TestFunc, int> TestItem;
  typedef std::vector<TestItem> TestList;

  test_suite(void)=default;

  public:
    virtual ~test_suite(void)=default;

    static test_suite& getInstance(void) {
      static test_suite suite;
      return suite;
    }

    void registerTest(std::string name, TestFunc func, const int line) {
      m_Tests.push_back(std::make_tuple(name, func, line));
    }

    void runTests(void) {
      UNITY_BEGIN();

      for (TestItem test : m_Tests) {
        std::string name = std::get<0>(test) + "()";
        TestFunc func = std::get<1>(test);
        int line = std::get<2>(test);

        UnityDefaultTestRun(func, name.c_str(), line);
      }

      UNITY_END();
    }

  private:
    TestList m_Tests;

}; // class test_suite

struct auto_register {
  auto_register(std::string name, TestFunc func, const int line) {
    test_suite::getInstance().registerTest(name, func, line);
  }

  virtual ~auto_register(void)=default;
}; // struct auto_register

#define SIMPLE_TEST(test_name)                                                  \
void test_name(void);                                                           \
static auto_register autoRegister_##test_name(#test_name, test_name, __LINE__); \
void test_name(void)

#ifdef MAIN_DEFINED
  // You can still define your own main() function, if desired. Useful for
  // when you want to combine several test files into a single test program
# define RUN_ALL_TESTS()
#elif defined(ARDUINO)
# define RUN_ALL_TESTS()                    \
    void loop(void) { /* no-op */ }         \
    void setup(void) {                      \
      delay(2000);                          \
      test_suite::getInstance().runTests(); \
    }                                       \
    struct eat_this_semicolon {};
#else
# define RUN_ALL_TESTS()                    \
  int main(int argc, const char* argv[]) {  \
    test_suite::getInstance().runTests();   \
  }                                         \
  struct eat_this_semicolon {};
#endif // MAIN_DEFINED
