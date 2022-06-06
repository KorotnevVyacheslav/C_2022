#include <iostream>
#include <algorithm>

using namespace std;

union branch{
  int value;
  int height;
  int size;
  branch * right;
  branch * left;

  branch(int _value, branch * _right = nullptr, branch * _left = nullptr){
    value = _value;
    right = _right;
    left = _left;
  }
};

class tree {
private:
  branch * first;

  int height_calculating(branch * el){

    if(el == nullptr) return 0;

    int a = height_calculating((*el).left), b = height_calculating((*el).right);
    (*el).size = max(a, b);
    (*el).height = b - a;
    return (*el).size;
  }

  void height_all_calculating(){
    int a;
    a = height_calculating(first);
  }

  void small_left_rotation(branch * el){
    if(!((*el).left && (*(*el).right).left && (*(*el).right).right)) return;
    if(!((*(*el).left).height == 2 && (*(*(*el).right).left).height <= (*(*(*el).right).right).height)) return;

    branch * a = el;

    el = (*el).right;
    (*el).left = a;
    (*(*el).left).left = (*a).left;
    (*(*el).left).right = (*(*a).right).left;

    height_calculating(el);

    delete a;
  }

  void small_right_rotation(branch * el){
    if(!((*el).right && (*(*el).left).left && (*(*el).left).right)) return;
    if(!((*(*el).right).height == 2 && (*(*(*el).left).right).height <= (*(*(*el).left).left).height)) return;

    branch * a = el;

    el = (*el).left;
    (*el).right = a;
    (*(*el).right).right = (*a).right;
    (*(*el).right).left = (*(*a).left).right;

    height_calculating(el);

    delete a;
  }

  void big_left_rotation(branch * el){
    if(!((*el).left && (*(*el).right).right && (*(*(*el).right).left).left && (*(*(*el).right).left).right)) return;
    if (!((*(*el).right).height - (*(*el).left).height == 2 && (*(*(*el).right).left).height > (*(*(*el).right).right).height)) return;

    branch * a = el;

    el = (*(*el).right).left;
    (*el).left = a;
    (*(*el).left).right = (*(*(*a).right).left).left;
    (*el).right = (*a).right;
    (*(*el).right).left = (*(*(*el).right).left).right;

    height_calculating(el);

    delete a;
  }

  void big_right_rotation(branch * el){
    if(!((*el).right && (*(*el).left).left && (*(*(*el).left).right).left && (*(*(*el).left).right).right)) return;
    if(!((*(*el).left).height - (*(*el).right).height == 2 && (*(*(*el).left).left).height < (*(*(*el).left).right).height)) return;

    branch * a = el;

    el = (*(*a).left).right;
    (*el).left = (*a).left;
    (*(*el).left).right = (*(*(*a).left).right).left;
    (*el).right = a;
    (*(*el).right).left = (*(*(*a).left).right).right;

    height_calculating(el);

    delete a;
  }

  void insert_p(int value, branch * el){
    if(value > (*el).value) {
      if((*el).right) insert_p(value, (*el).right);
      if(!((*el).right)) (*el).right = new branch (value);
    }

    if(value < (*el).value) {
      if((*el).left) insert_p(value, (*el).left);
      if(!((*el).left)) (*el).left = new branch (value);
    }

    small_left_rotation(el);
    small_right_rotation(el);
    big_left_rotation(el);
    big_right_rotation(el);
  }

  void deleting(branch * el){
    if((*el).right) deleting((*el).right);
    if((*el).left) deleting((*el).left);

    delete el;
  }

  void erase_p(int value, branch * el){
    ;
  }

public:
  tree (int firtsValue = 0){
    first = new branch (firtsValue);
    (*first).height = 0;
  };

  virtual ~tree (){
    deleting(first);
  };

  void insert(int value){
    insert_p(value, first);
  };

  void erase(int value){
    erase_p(value, first);
  };


};

int main(){

  tree a(10);
  return 0;
}
