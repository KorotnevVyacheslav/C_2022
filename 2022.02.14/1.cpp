#include<iostream>
#include<vector>
#include<time.h>
#include<fstream>

using namespace std;

void mass_print(vector<vector<short int>> a, int wid, int heig){
  /*
  Function for printing massive
  a - table of cells
  wid - width of table
  heig - height of table
  */

  cout<<"Massive printing started!"<< endl;
  for(int i = 0; i < wid; i++){
    for(int j = 0; j < heig; j++){
      if (a[i][j] == -1) cout<< a[i][j] << "   ";
      else cout<< a[i][j] << "    ";
    }
    cout<<endl;
  }
  cout<<"Massive printing ended!"<< endl;
}


pair<int, int> recalculating_position(pair<int, int> element){
  /*
  Funcction of random cell moving
  element - cell, which is need to be moved
  */

  int x = rand() % 4 + 1;
  int dx = 0, dy = 0;
  pair<int, int> new_element;

  if (x == 1) dx = 1;
  if (x == 2) dy = 1;
  if (x == 3) dx = -1;
  if (x == 4) dy = -1;

  /*
  switch (x) {
    case 0:
      dx = 0;
      dy = 0;
      break;
    case 1:
      dx = 1;
      dy = 0;
      break;
    case 2:
      dx = 0;
      dy = 1;
      break;
    case 3:
      dx = -1;
      dy = 0;
      break;
    case 4:
      dx = 0;
      dy = -1;
      break;
  }
  */
  new_element.first = element.first + dx;
  new_element.second = element.second + dy;
  return new_element;
}


vector<pair <int, int>> adding_elements(vector<pair <int, int>> el, int num){
  /*
  Function for adding elements to table by hand
  el - massive with cells
  num - number of elements to add
  */

  for(int i = 0; i < num; i++){
    char sign;
    cin >> el[i].first>> sign >> el[i].second;
  }
  return el;
}


int moving_calculation(int width, int height, int iterations, int num){
  /*
  Function for calculating moving of cell
  width - width of the table
  height - height of the table
  num - number of maximum iterations
  */

  const int Width = width;
  const int Height = height;
  const int NumberOfElements = num;
  const int NumberOfEterations = iterations;

  bool result = true;

  //creating a table for cells and massive for cells' coordinates
  vector<vector<short int>> eltable(Width,vector<short int>(Height, 0));
  vector<pair <int, int>> elements(NumberOfElements, pair <int, int> (rand() % Width, rand() % Height));

  //function for hand adding elements
  //elements = adding_elements(elements, NumberOfElements);

  // placing first cell in the center
  elements[0].first = Width / 2;
  elements[0].second = Height / 2;

  //marking living cells in table to 1
  for(int i = 0; i < NumberOfElements; i++){
    eltable[elements[i].first][elements[i].second] = 1;
  }

  pair <int, int> new_element;

  //starting calculations
  for(int iter = 0; iter < NumberOfEterations; iter++){
    //cout << "Iteration number: " << iter << endl;
    //mass_print(eltable, Width, Height);

    //understanding, is one or more cells alive
    result = false;
    for(int i = 0; i < NumberOfElements; i++){
      if (eltable[elements[i].first][elements[i].second] == 1) {
        //cout << "Cell reached the edge of the world!";
        result = true;
      }
    }
    if (!result) return iter;

    //cout<<endl;

    //changing border rules
    for(int i = 0; i < NumberOfElements; i++){
      int x = elements[i].first, y = elements[i].second;
      if(x < Width - 1  && eltable[x+1][y] != 0) {eltable[x+1][y] = -1; eltable[x][y] = -1;};
      if(y < Height - 1 && eltable[x][y+1] != 0) {eltable[x][y+1] = -1; eltable[x][y] = -1;};
      if(x > 0 && eltable[x-1][y] != 0) {eltable[x-1][y] = -1; eltable[x][y] = -1;};
      if(y > 0 && eltable[x][y-1] != 0) {eltable[x][y-1] = -1; eltable[x][y] = -1;};
      if(x == 0 || x == Width - 1) eltable[x][y] = -1;
      if(y == 0 || y == Height - 1) eltable[x][y] = -1;
    }

    //changing position
    for(int i = 0; i < NumberOfElements; i++){
      if (eltable[elements[i].first][elements[i].second] == -1) continue;

      new_element = recalculating_position(elements[i]);

      if (eltable[new_element.first][new_element.second] == 0) {
        eltable[elements[i].first][elements[i].second] = 0;
        elements[i].first = new_element.first;
        elements[i].second = new_element.second;
        eltable[new_element.first][new_element.second] = 1;
      }
    }
  }

  return iterations;

}


int main(){
  //for normal random
  srand(982792);

  int sum = 0, iterations = 200, NumberOfExperiments = 1000, max_radius = 10000, max_num = 500;

  //opening file
  ofstream outf("results_border.txt", std::ios::out);
  if (!outf.is_open()) return 0;

  //calculations for 1 cell and many borders' values
  for (size_t j = 3; j < max_radius; j++) {
    sum = 0;
    for(int i = 0; i < NumberOfExperiments; i++){
      sum += moving_calculation(j, j, max_radius * max_radius, 1);
    }
    outf << j << " " << ((1.0 * sum) / NumberOfExperiments) << endl;
  }

  /*
  //calculations for fixed borders and many numbers of cells
  for (size_t j = 1; j < max_num; j++) {
    sum = 0;
    for(int i = 0; i < NumberOfExperiments; i++){
      sum += moving_calculation(1000, 1000, 2 * max_radius * max_radius, j);
    }
    outf << 1.0 * j / 100000000 << " " << ((1.0 * sum) / NumberOfExperiments) << endl;
  }
  */
  outf.close();
  return 0;
}
