#include <iostream>

using namespace std;
int main() {
  int x = 10;
  int* p;

  p = &x;
  x++;
  int y = *p;
  cout << y;
  return 0;
}
