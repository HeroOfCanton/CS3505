
#include<iostream>
#include<string.h>
#include<vector>

using namespace std;


//see www.cplusplus.com/reference/cstring/strtok/

int main(){

  // get the string and place it in a character array
  char str[] = "one two three four five six\n seven eight";
 
  // vector we would return tokens in
  vector<string> a;
  
  // pointer to the position of the first character in the array
  char * pch;

  // I think this is combining all characters up until the delimiter we have defined as the second 
  // parameter of strtok, which is a space and a new line character
  pch = strtok (str, " \n");

  //set the string equal to the characters up until the delimiter
  string ex = pch;

  // loop through until the end of the line
  while (pch != NULL)
  {
    // get the word in the character pointer
    ex = pch;
    // add it to our vector
    a.push_back(ex);
    
    // get the next word
    pch = strtok(NULL, " \n");
  }
  

  // test to make sure the right things came  out
  cout << a.size() << endl;
  
  for (int i = 0; i < a.size(); i++)
    cout << a[i] << endl;
}
