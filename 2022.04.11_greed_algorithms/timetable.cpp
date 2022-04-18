#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void printing(vector<pair<int,int>> v, int num){
  for(int i = 0; i < num; i++){
    cout << v[i].first << "  " << v[i].second << endl;
  }
}

int main() {
  int n = 5;
  vector<pair<int,int>> times = {{1,2}, {3, 6}, {3, 4}, {5, 7}, {1, 7}};
  sort(times.begin(),times.end());
  printing(times, n);

  for (int i = 0; i < n - 1; i++) {
    if(times[i].second < times[i + 1].second && times[i].second > times[i + 1].first) {times.erase(times.begin() + i + 1); n -= 1;i--;}
  }
  for (int i = 0; i < n - 1; i++) {
    if(times[i].second - times[i].first < times[i + 1].second - times[i + 1].first && times[i].second > times[i+1].first) {times.erase(times.begin() + i + 1); n -= 1; i--;}
    if(times[i].second - times[i].first > times[i + 1].second - times[i + 1].first && times[i].second > times[i+1].first) {times.erase(times.begin() + i ); n -= 1; i--;}
  }

  cout << endl;
  printing(times,n);
  return 0;
}
