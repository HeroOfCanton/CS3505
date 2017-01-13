/*
 * map 
 */

#include<iostream>
#include<map>
#include<vector>

using namespace std;

int main()
{
  map<char,int> mymap; //Creating a map
  mymap.insert (pair<char,int>('a',100)); //inserting values into a map
  mymap.insert (make_pair('z', 500));

  //Displaying elements in a map
  cout<<"The map now contains"<<endl;
  for(map<char,int>::iterator it=mymap.begin(); it != mymap.end(); it++)
    cout<<it->first<<" => "<<it->second <<endl;

  cout<<endl;

  cout<<"Removing a value"<<endl;
  //Remove a value from the map
  mymap.erase('z'); //provide key as parameter
  
  cout<<endl;
  cout<<"Now the map contains"<<endl;
  for(map<char,int>::iterator it=mymap.begin(); it != mymap.end(); it++)
    cout<<it->first<<" => "<<it->second <<endl;


  //An example of how a map of vectors can be created.
  vector<int> a, b;
  map<int, int> m;
  for (size_t i = 0; i < a.size(); ++i)
    m[a[i]] = b[i];

  return 0;
}
