#include "huge_number.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
  huge_number ha("123");
  huge_number hb("45980");
  huge_number hd("65132800");
  huge_number he("99999");
  huge_number hf("100001");
  huge_number hg("150010");
  huge_number hh("10");
  huge_number hi("20");
  huge_number hj("21720");
  huge_number hc;

  // Make sure Default Constructor returns 0
  cout << hc.get_value() << endl;
  cout << "- 0 - Default Constructor" << endl;

  // Make sure Alternate Constructor works
  cout << ha.get_value() << endl;
  cout << "- 123 - Alternate Constructor" << endl;

  // Test Multiplication
  hc = ha * hb;

  cout << ha.get_value() << endl;
  cout << hb.get_value() << endl; 
  cout << hc.get_value() << endl;
  cout << "- 5655540 - Multiplication" << endl;

  // Test Subtraction, bigger number first
  hc = hb - ha;

  cout << hb.get_value() << endl;
  cout << ha.get_value() << endl;
  cout << hc.get_value() << endl;
  cout << "- 45857 - Subtraction, bigger first" << endl;

  hc = hf - he;

  cout << hf.get_value() << endl;
  cout << he.get_value() << endl;
  cout << hc.get_value() << endl;
  cout << "- 2 - Subtraction, bigger first" << endl;

  // Test Subtraction, smaller number first
  hc = ha - hb;

  cout << ha.get_value() << endl;
  cout << hb.get_value() << endl;
  cout << hc.get_value() << endl;
  cout << "- 0 - Subtraction, smaller first" << endl;

  // Test Addition
  hc = he + hd;

  cout << he.get_value() << endl;
  cout << hd.get_value() << endl;
  cout << hc.get_value() << endl;
  cout << "- 65232799 - Addition" << endl;

  // Test Division, smaller dividend
  hc = ha / hb;

  cout << ha.get_value() << endl;
  cout << hb.get_value() << endl;
  cout << hc.get_value() << endl;
  cout << "- 0 - Division, smaller dividend" << endl;
  

  // Test Division, larger dividend
  hc = hg / hh;

  cout << hg.get_value() << endl;
  cout << hh.get_value() << endl;
  cout << hc.get_value() << endl;
  cout << "- 15001 - Division, larger dividend" << endl;
  
  // Test Division, zero dividends
  hc = hf / hh;

  cout << hf.get_value() << endl;
  cout << hh.get_value() << endl;
  cout << hc.get_value() << endl;
  cout << "- 10000 - Division, zero dividend" << endl;
    
  // Test Division, same dividend
  hc = hb / hb;

  cout << hb.get_value() << endl;
  cout << hb.get_value() << endl;
  cout << hc.get_value() << endl;
  cout << "- 1 - Division, same dividend" << endl;

  hc = hj / hi;

  cout << hj.get_value() << endl;
  cout << hi.get_value() << endl;
  cout << hc.get_value() << endl;
  cout << "- 1086 - Division, same dividend" << endl;

  // Test Modulus, smaller number first
  hc = ha % hb;

  cout << ha.get_value() << endl;
  cout << hb.get_value() << endl;
  cout << hc.get_value() << endl;
  cout << "- 123 - Modulus, smaller first" << endl;

  // Test Modulus, larger number first
  hc = hb % ha;

  cout << hb.get_value() << endl;
  cout << ha.get_value() << endl;
  cout << hc.get_value() << endl;
  cout << "- 101 - Modulus, larger first" << endl;
  
}
