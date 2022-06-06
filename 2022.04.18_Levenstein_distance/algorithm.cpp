#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <time.h>
#include <fstream>

using namespace std;

void mass_print(vector<vector<int>> a, int wid, int heig){
    for(int i = 0; i < wid; i++){
      for(int j = 0; j < heig; j++){
        if (a[i][j] / 10 == 0) cout<< a[i][j] << "   ";
        else cout<< a[i][j] << "    ";
      }
    cout<<endl;
    }
}

int triple_min(int a, int b, int c){
  return min(min(a,b),c);
}

int m(char a, char b){
  if(a == b) return 0;
  return 1;
}

int main(){
  ofstream log("log.txt");

  string a, b;
  cout << "Write to words:" << endl;
  cin >> a >> b;

  log << time(0) << "   " << "Words were given." << endl;
  log << "Words:  " << a << " , " << b << endl;
  //cout << a << b;

  vector<vector<int>> d(a.size() + 1, vector<int>(b.size() + 1, 0));
  log << time(NULL) << "   " << "Vector created." << endl;

  for (int i = 0; i <= a.size(); i++) {
    d[i][0] = i;
  }

  for (int i = 0; i <= b.size(); i++) {
    d[0][i] = i;
  }

  for (int i = 0; i <= 2 * max(a.size(), b.size()) + 1; i++) {
    for (int j = 0, k = i; j <= i + 1 && k >= 0; j++, k--) {

      log << time(NULL) << "   " << k << " " << j << "  skip " << endl;

      if(k > a.size() || j > b.size()) continue;

      log << time(NULL) << "   " << k << " " << j << "  value: ";

      if(k == 0 && j == 0) {
        d[k][j] = 0;
        log << 0 << endl;
        continue;
      }

      if(k == 0 && j > 0) {
        d[k][j] = j;
        log << j << endl;
        continue;
      }

      if(k > 0 && j == 0) {
        d[k][j] = k;
        log << k << endl;
        continue;
      }

      if(k > 0 && j > 0){
        d[k][j] = triple_min(d[k][j - 1] + 1, d[k - 1][j] + 1, d[k - 1][j - 1] + m(a[k - 1], b[j - 1]));
        log << triple_min(d[k][j - 1] + 1, d[k - 1][j] + 1, d[k - 1][j - 1] + m(a[k - 1], b[j - 1])) << endl;
        continue;
      }
    }
  }

  log << time(NULL) << "   " << "Matrix calculating ended." << endl;

  cout << d[a.size()][b.size()] << endl;

  log << time(NULL) << "   " << "Levenstein lenght: " << d[a.size()][b.size()] << endl;

  if (a.size() + b.size() < 25) mass_print(d, a.size() + 1, b.size() + 1);

  log.close();

  return 0;
}
