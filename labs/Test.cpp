#include<iostream>

using namespace std;

int main()
{
  int num;
  cout << "Enter a number" << endl;
  cin >> num;

  if(num == 0)
    {
      cout << "No multiplication, you entered zero, dummy!" << endl;
    }
  else
    {
      for(int i = 0; i <= 10; i++)
	{
	  int prod = num * i;
	  cout << num << "*" << i << "=" << prod << endl;
	}
    }
  return 0;
}
