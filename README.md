# **SimpleTEST**

A simple to use test suite wrapper for **Throw-the-switch's** [Unity test framework](http://www.throwtheswitch.org/unity)

## **Background**

---

I've recently began unit-testing within my Arduino / ESP8266 / ESP32 projects using the [Unity Test Framework](http://www.throwtheswitch.org/unity) supported by [PlatformIO](http://www.platformio.org/) development environment.

In doing so, I've come to realize that there is so much ***boiler-plate*** code that was just screaming to be simpliflied.

### **Example**

---

For example, every test file would have a common format in which you would declare the test and then run that test within the main() call; as such:

```Arduino (c/c++)
#include "unity.h"
#include "file_under_test.h"

void setUp(void) { /* as appropriate */ }
void tearDown(void) { /* as appropriate */ }

void test_ThisTestPassesEveryTime(void) {
  TEST_ASSERT(1==1);
}

void test_ThisTestWillAlwaysFail(void) {
  TEST_ASSERT(0==1);
}

int main(void) {
  UNITY_BEGIN();
  RUNT_TEST(test_ThisTestPassesEveryTime);
  RUN_TEST(test_ThisTestWillAlwaysFail);
  return UNITY_END();
}

```

### **Simplified Version**

---

As you can see, the example above is extraordinarily repetitive. In order to save my sanity, I had to devise a simpler mechanism in which to define simple tests; hence the following:

```Arduino (c/c++)
#include "SimpleTestSuite.h"
#include "file_under_test.h"

void setUp(void) { /* as appropriate */ }
void tearDown(void) { /* as appropriate */ }

SIMPLE_TEST(test_ThisTestPassesEveryTime) {
  TEST_ASSERT(1==1);
}

SIMPLE_TEST(test_ThisTestWillAlwaysFail) {
  TEST_ASSERT(0==1);
}

RUN_ALL_TESTS();
```

### **Explanation**

The **SimpleTEST** macro hides all of the repetitive stuff by:

* forward-declaring the test by name,
* adding that test to a list of tests; and,
* beginning the test definition body - so that you can define the test.

Furthermore, the **RUN_ALL_TESTS** macro hides the definition of the *int main(void)* function which runs each test stored in the list.

### **Usage**

The example above shows the basics for how to use this system. Aside from simplifying the boiler-plate code within a test file, nothing else changes. You still setup testing within the [PlatformIO](http://www.platformio.org/) the same way; and you still have to make sure you're using the [Unity test framework](http://www.throwtheswitch.org/unity). Differences between Native/Desktop/Embedded setups still have to be defined accordingly. All you have to do is add the [SimpleTestSuite.h](https://github.com/kickshawprogrammer/SimpleTEST/tree/main/SimpleTestSuite.h) file to the search path and include it in-place of the unity.h header file.

### **Note**

---

I understand that the [Unity test framework](http://www.throwtheswitch.org/unity) is written in 100% C code which makes it difficult to include this functionality by default. At this moment, the [SimpleTestSuite.h](https://github.com/kickshawprogrammer/SimpleTEST/tree/main/SimpleTestSuite.h) is only for C++ users. However, once settled, I hope to provide a C version as well - I'm just not sure how I will accomplish this yet.

## **License**

---

Feel free to use in any way you wish; but please, be kind and do good!
