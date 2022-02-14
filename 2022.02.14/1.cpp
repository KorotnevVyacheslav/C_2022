#include<iostream>
#include<vector>

using namespace std;

void mass_print(vector<vector<short int>> a, int wid, int heig){
  cout<<"Massive printing started!"<< endl;
  for(int i = 0; i < wid; i++){
    for(int j = 0; j < heig; j++){
      cout<< a[i][j] << " ";
    }
    cout<<endl;
  }
  cout<<"Massive printing ended!"<< endl;
}

int main(){
  const int Width = 10;
  const int Height = 10;
  const int NumberOfElements = 1;
  const int NumberOfEterations = 10

  vector<vector<short int>> table(Width,vector<short int>(Height, 0));
  vector<pair <int, int>> elements(NumberOfElements, pair <int, int> (rand() % Width, rand() % Height));

  for(int i = 0; i < NumberOfElements; i++){
    table[elements[i].first][elements[i].second] = 1;
  }
  cout << Width;

  for(int iter = 0; iter < NumberOfEterations; iter++){
    for(int i = 0; i < NumberOfElements; i++){
      
    }
  }

  mass_print(table, Width, Height);
  cout<<endl;
  return 0;
}
