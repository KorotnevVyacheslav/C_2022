#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

void cout_RGB(int R, int G, int B)
{
  cout << "\x1B[38;2;" << R << ";" << G << ";" << B << "m" << " ";
}

union Colour
{
  int r;
  int g;
  int b;
};

class Cat {
private:
  string name;
  int age;
  int health;
  Colour col;

  Colour calc_colour(){
    Colour temp;
    temp.r = rand()%256;
    temp.g = rand()%256;
    temp.b = rand()%256;
    return temp;
  }

public:
  bool flag = true;

  Cat (string nickname){
    name = nickname;
    age = rand();
    col = calc_colour();
    cout << "Cat emulating proccess started." << endl;
  }
  virtual ~Cat (){
    cout << "Cat is dead." << endl;
  }

  void feed(int food_count){
    if (food_count < 0) flag = false;
    health += food_count;
  }

  void punish(int punch){
    if (punch < 0) flag = false;
    health -= punch;
  }

  void get_age(){
    cout << "Your emulated badly cat's age: " << age << endl;
  }

  void get_info(){
    col = calc_colour();
    cout << "Your cat's colour now is: (";
    cout_RGB(col.r , col.g ,col.b);
    cout << col.r << "," << col.g << "," << col.b << ")";
    cout_RGB(0, 0, 0);
    cout << endl;
    cout << "Health is: " << health << endl;
  }
};


bool finding_string(string text, string command){
    size_t pos = text.find(command);
    if (pos != std::string::npos)
        return true;
    else
        return false;
}



int main(){
  srand(82392874);
  cout << "Algorithm started." << endl << "Write name: ";
  string temp;
  cin >> temp;
  Cat object(temp);
  string deal;
  while (object.flag) {
    cin >> deal;
    if(finding_string(deal, "quit")) return 0;
    if(finding_string(deal, "help")) {
      cout << "Print quit to quit." << endl;
      cout << "Print feed to feed, then print number." << endl;
      cout << "Print punish to punish, then print number." << endl;
      cout << "Print info for info." << endl;
      cout << "Print age to know the age." << endl;
    }
    if(finding_string(deal, "feed")) {
      int health;
      cin >> health;
      object.feed(health);
    }
    if(finding_string(deal, "punish")) {
      int health;
      cin >> health;
      object.punish(health);
    }
    if(finding_string(deal, "info")) {
      object.get_info();
    }
    if(finding_string(deal, "age")) {
      object.get_age();
    }

  }
  return 0;
}
