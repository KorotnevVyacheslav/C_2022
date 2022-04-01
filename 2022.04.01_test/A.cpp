#include<iostream>
#include<vector>

using namespace std;

int main(){

  int num, lenght, cell, cat;
  vector<int> v(30, 0);


  cin >> num;
  for (int i = 0; i < num; i++){
    cin >> cell >> lenght;
    for (int j = cell; j < cell + lenght; j++){
      v[j] = 1;
    }
  }
  cin >> cat;


  int iter;
  for (int i = 0; i < 30; i++) {
    if(v[i] == 0){
      iter = 1;

      for(int j = 1; j + i < 30; j++){
        if(v[i + j] == 0) iter++;
        else break;
        if(iter == cat){
          cout << i;
          return 0;
        }
      }
    }
  }
  cout << -1;
  return 0;
}
