#include <iostream>\

using namespace std;

class massive {
private:
  int * elements;

  void resize(int num){
    int * temp;

    temp = elements;
    elements = new int[2 * num];

    for (int i = 0; i < count; i++) {
      elements[i] = temp[i];
    }

    for (int i = count; i < 2 * num; i++) {
      elements[i] = 0;
    }

    size = 2 * num;

    delete[] temp;
  }

public:
  int size;
  int count;

  massive(int num = 5){
    elements = new int[num + num / 2];
    size = num + num / 2;
    count = num;
  }

  ~massive(){
    delete[] elements;
  }

  int & operator [](int n){
    if(n >= size) resize(n);
    if(n >= count) count = n + 1;
    return elements[n];
  }

  void unionising(massive b){
    bool k = false;

    for (int i = 0; i < b.count; i++) {
      k = false;
      for(int j = 0; j < count; j++){
        if(b[i] == elements[j]) k = true;

      }
      if(!k) elements[count + 1] = b[i];
    }
  }

};

int main() {
  massive a(10), b;
  int N = 20;

  for (int i = 0; i < N; i++) {
    //cin >> a[i];
    a[i] = i;
    b[i] = i/2 + 5;
  }

  a.unionising(b);

  for (int i = 0; i < N; i++) {
    cout << a[i] << "  ";
  }

  //delete a;
  return 0;
}
