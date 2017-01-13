/*
name: test_prime.cpp
author: Ryan Welling
last modified: 1/14/2014
*/

#include<iostream>
#include<cstdlib>
using namespace std;

int main(int argc, char** argv) {
  // Check to see if there are more than 1 command line arguments, error if so
  if(argc > 2 || argc == 1){
    cout << "Number of arguments is limited to 1" << endl; 
    return 1; 
  }

  int x = atoi(argv[1]);

  // Check to see if number is less than 2, error if so  
  if(x < 2) {
    cout << "Number must be greater than 1" << endl;
    return 1;
  }
  // Check to see if number is 2,3,5,7 or 11
  if(x < 4 && x > 1 || x == 11 || x == 5 || x == 7){
    cout << "Prime" << endl;
    return 0;
  }
  // Check to see if number is divisible by 2,3,5,7 or 11
  if (x % 2 == 0 || x % 3 == 0 || x % 5 == 0 || x % 7 == 0 || x % 11 == 0) {
    cout << "Composite" << endl;
    return 0;
  }
  // If we get this far, number is Prime
  cout << "Prime" << endl;
  return 0;
}
