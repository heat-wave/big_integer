#include <iostream>
#include "big_integer.hpp"
using namespace std;

int main() {
    big_integer a = 5;
    big_integer b(10);
    big_integer c = a + b;
    c -= a;
    c *= b;
  return 0;
}