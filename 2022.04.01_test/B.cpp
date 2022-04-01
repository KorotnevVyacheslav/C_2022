#include <iostream>

using namespace std;

long long func(long long num, long long iter) {
  if(num >= iter) {
    cout << ((num >> iter) - (num >> (iter + 1))) << (iter) + func(num, iter + 1) << endl;
    return ((num >> iter) - (num >> (iter + 1))) << (iter) + func(num, iter + 1);
  }
  return 0;
}

int main(){
  long long num;
  cin >> num;

  cout << func(num, 1);
  return 0;
}
