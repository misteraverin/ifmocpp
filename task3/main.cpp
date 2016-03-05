#include "rational.h"
#include <stdio.h>

using namespace std;

int main(){
  rational a(1, 3);
  rational b(1, 6);
  rational c = a - b;
  printf("%d", c.getDenom());
  return 0;
}