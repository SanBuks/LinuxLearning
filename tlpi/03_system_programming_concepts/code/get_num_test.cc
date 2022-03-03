#include <iostream>
#include "tlpi_hdr.h"

void getLongTest() {
  std::cout << getLong("123432", GN_ANY_BASE, "arg1") << '\n';
}

void getIntTest() {
  std::cout << getInt("123432", GN_ANY_BASE, "arg1") << '\n';
  std::cout << getInt("123432X", GN_ANY_BASE, "arg1") << '\n';  // Fail
}

int main() {
  getLongTest();
  getIntTest();
}