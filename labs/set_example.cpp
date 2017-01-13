/*
 * Set (Associative container)
 */

#include<iostream>
#include<set>

using namespace std;

int main()
{
  set<int> myset;
  myset.insert(6); //Inserts value to the set
  myset.insert(1);
  myset.insert(9);

  //One way of finding an element

  set<int>::iterator it;
  it = myset.find(9); //points to the memory location of 9.
  cout<<"Item now being pointed to is:";
  cout<<*it;
  cout<<endl;

   //Recommended way of finding an element.
  const bool is_in = myset.find(9) != myset.end();
  if (is_in)
    cout<<"Element found in set"<<endl;
  else
    cout<<"Better luck next time"<<endl;

  //Checking whether element has been inserted or not.

  pair<set<int>::iterator, bool> ret;
  ret = myset.insert(1);
  if(ret.second == false)
    cout<<"Element not inserted"<<endl;
  else
    cout<<"Element inserted"<<endl;

  myset.erase(7);
  
  return 0;
}