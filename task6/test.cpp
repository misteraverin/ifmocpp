#include <iostream>
#include <string>
#include "lazy_string.h"

using namespace std;

int main() {
  lazy_string a("privet");
  a[0] = 'b';
  cout << a[0] << "\n";
  cout << "the end";
  return 0;
}