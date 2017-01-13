#include<iostream>

using namespace std;

int main() {
  double a;  
  cout << "Enter the weight: ";
  cin >> a;
  while(a < 0) {
    cout << "Weight can not be less than 0." << endl; 
    cout << "Enter the weight: ";
    cin >> a;
  }
  a = a*2.2;
  cout << "The weight is " << a << " pounds." << endl;
}
