#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

vector<int> recombining(int num, vector<int> a){
  int N = a.size();
  if (num < ceil(1 + log2(a.size())) - 1) {
    if (2 * num < N) a = recombining(num * 2 + 1, a);
    if (2 * num + 1 < N) a = recombining(num * 2 + 2, a);
  }
  if (2 * num < N && a[num] > a[2 * num + 1] && a[2 * num + 1] > a[2 * num + 2]) swap(a[num],a[2 * num + 1]);
  if (2 * num + 1 < N && a[num] > a[2 * num + 2] && a[2 * num + 2] > a[2 * num + 1]) swap(a[num],a[2 * num + 2]);
  return a;
}

vector<int> pyramid_sorting(vector<int> a){
  int N = a.size();
  vector<int> b(N, 0);
  for (int i = 0; i < N; i++){
    recombining(i, a);
  }
  return a;
}

int main(){
  srand(76527615);
  int N = 10;
  vector<int> v(N, 0);
  for (int i = 0; i < N; i++) {
    v[i] = rand() % 100;
  }
  v = pyramid_sorting(v);
  for (int i = 0; i < N; i++) {
    cout<< v[i] << "  ";
  }
  return 0;
}
