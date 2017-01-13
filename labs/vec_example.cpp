/* STL 
 * Vectors (Sequence Container)
 */
#include<iostream>
#include<vector>
#include <boost/foreach.hpp>

using namespace std;

int main ()
{
  vector<int> vec;
  vec.push_back(6); //Adding elements to the end of vec.
  vec.push_back(1);
  vec.push_back(9);

  //Displaying elements in a vector
  cout<<"Elements in the vector are:"<<endl;
  for (int i=0; i<vec.size();i++)  //One way to do it. Not recommended
    cout<<vec[i]<<" ";

  cout<<endl;

  for (vector<int>::iterator itr = vec.begin(); itr!= vec.end(); ++itr) // Standard way.
    cout << *itr<<" ";

  cout<<endl;
  cout<<endl;

  //Using BOOST_FOREACH

  cout<<"Using BOOST_FOREACH to display the contents"<<endl;

  BOOST_FOREACH( int i,vec )
    {
      cout<<i<<" ";
    }

  cout<<endl;
  cout<<endl;

  //  Get a particluar element from vector
  cout<<"Element at index=2 is"<<endl;
  cout << vec[2]<<endl;
  cout << vec.at(2)<<endl;

  cout<<endl;

  //Inbuilt member functions for containers

  if(!vec.empty())
    {
      cout<<"Vector is not empty"<<endl;
    }
  
  cout<<"Size of vector is:"<<vec.size()<<endl; //size of vector

  vector<int> vec2(vec); //Copy Constructor
  
  vec.clear(); //Remove all items from vec

  cout<<"New size of vector is:"<<vec.size()<<endl; //size of vector
  
  return 0;
}
