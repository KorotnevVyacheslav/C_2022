#include <iostream>
#include <vector>
#include <string>

using namespace std;

string binary_int(int num){
  string num_bin;
  vector<bool> v;
  short int k;
  for (short int i = 0; i < 64; i++) {
    if((num >> 1) << 1 == num) v.push_back(0);
    else v.push_back(1);
    num >>= 1;
  }
  bool flag = false;
  for (int i = v.size() - 1; i >= 0; i--) {
    if(v[i] == 1) flag = true;
    if(flag && v[i]) num_bin.append("1");
    if(flag && !v[i]) num_bin.append("0");
  }
  return num_bin;
}

int main(){
  unsigned int number;
  string number_bin;
  cout << "Write your number:" << endl;
  cin >> number;
  number_bin = binary_int(number);
  cout << endl << number_bin << endl << "Programm finished." << endl;
  return 0;
}
