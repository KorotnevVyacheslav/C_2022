#include <iostream>
#include <vector>
#include <string>

using namespace std;

class float_struct{
public:
  int first;
  int second;
};

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
  float number;
  float_struct obj;
  char a;
  cout << "Write your number in format num.num :" << endl;
  cin >> obj.first >> a >> obj.second;
  cout << endl << binary_int(obj.first) << "." << binary_int(obj.second) << endl;
  cout << "Programm finished." << endl;
  return 0;
}
