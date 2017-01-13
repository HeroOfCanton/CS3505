#include <iostream>
using namespace std;

void swap (int &x, int &y) {
  int temp;
  temp = x;
  x = y;
  y = temp;
}

int main() {
  int a = 10, b = 25;
  cout << "Value of a before swap: " << a << endl;
  cout << "Value of b before swap: " << b << endl;
  swap(a, b);
  cout << "Value of a after swap: " << a << endl;
  cout << "Value of b after swap: " << b << endl;
  return 0;
}
