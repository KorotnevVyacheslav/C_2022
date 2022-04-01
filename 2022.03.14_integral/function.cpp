#include <iostream>
#include <math.h>
#include <vector>
#include <cmath>

using namespace std;

double maxwell(double x, double t){
  return fma(1 / fma(sqrt(t), M_PI, 0), exp(- x * x / t), 0);
}


double maxwell_integrated(double t){
  return sqrt(t / M_PI);
}


vector<double> filling_maxwell(int num, double dx, double t){
  vector<double> v(num);
  for (int i = 0; i < num; i++) {
    v[i] = maxwell(i * dx, t);
  }
  return v;
}


vector<double> filling_linear(int num, double dx){
  vector<double> v(num);
  for (int i = 0; i < num; i++) {
    v[i] = i * dx;
  }
  return v;
}


class Integral{
private:
  vector<double> pdf;
  vector<double> psi;
  double dv;
  double result;

public:
  int number;


  void defining(std::vector<double> distribution, std::vector<double> values, double dx){
    pdf = distribution;
    psi = values;
    number = pdf.size();
    //cout << "Object defined. number: " << number << endl;
  }


  double integral_recursive(int start, int end){
    if(end - start > 1) return fma(integral_recursive(start, start + (end - start) / 2), 1, integral_recursive(start + (end - start) / 2, end));
    else return fma(fma(psi[start], pdf[start], 0), dv, 0);
  }


  double integral_simple(){
    const int num = psi.size();
    double sum;
    for (int i = 0; i < num; i++) {
      sum = fma(fma(psi[i], pdf[i], 0), dv, sum);
    }
    return sum;
  }


  double integral_doubling(){
    int N = number;
    vector<double> vec(N);
    cout << "start" << endl;
    for(int i = 0; i < N; i++){
      vec[i] = fma(psi[i], pdf[i], 0);
    }
    cout << "start 2" << endl;
    for (int i = 1; i <= N; i * 2) {
      for(int j = 0; j < N; j + 2 * i){
        if(i + j < N) vec[j]+= vec[j+i];
      }
      cout << i << endl;
    }
    return vec[0];
  }
};


void printing_results(double analytic, Integral obj){
  cout << "Analytical result: " << analytic << endl;
  cout << "Simple calculating: " << obj.integral_simple() << endl;
  cout << "Recursive calculating: " << obj.integral_recursive(0, obj.number) << endl;
  cout << "Doubling calculating: " << obj.integral_doubling() << endl;
}


int main() {
  int number = 100000;
  double delta = 0.0000001, temperature = 1;
  Integral object;
  object.defining(filling_maxwell(number, delta, temperature), filling_linear(number, delta), delta);
  printing_results(maxwell_integrated(temperature), object);
  return 0;
}
