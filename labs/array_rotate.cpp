#include<iostream>
#include<cstdlib>

using namespace std;

/*
 * Function to rotate the array elements by one 
 * position. Takes in the starting address of the 
 * array and array size as its parameters
 */
void rotate_array(int *ar, int size)
{
  // variable to store the last element of the array
  int temp = *(ar+size-1);
  int prev_temp = *ar;
  int prev;
  /*
   * Looping to shift element at position i
   * to position i+1
   */
  for (int i = 1; i < size; i++) 
  {
    // shifting each element down
    prev = *(ar + i);
    *(ar+i) = prev_temp;
    prev_temp = prev;
  }
  *ar = prev_temp;
}

int main(int argc, char* argv[]) 
{
  if (argc != 2) 
  {
    cout << "Invalid number of arguments" << endl;
    return 0;
  }
 /*
  * argument denotes a value whose multiples are
  * stored in the array
  */
  int val = atoi(argv[1]);
  int ar[10];
 /*
  * Looping to store values in the array
  */
  for(int i = 0; i < 10; i++) {
    *(ar+i) = val*(i+1);
  }
 /*
  * Displaying values prior to array rotation
  * and their corresponding memory location
  */
  for(int i = 0; i < 10; i++) {
    cout << *(ar+i) << " is stored at memory location " <<  ar + i << endl;
  }
  rotate_array(ar, 10);
  cout << "ROTATE BY ONE POSITION" << endl;
 /*
  * Displaying values after array rotation
  * and their corresponding memory location
  */
  for(int i = 0; i < 10; i++) {
   cout << *(ar + i) << " is stored at memory location " <<  ar + i << endl;
  }
  return 0;
}
