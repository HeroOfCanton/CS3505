/*
 * Ryan Welling
 * 22 Jan 2015
 * huge_number.cpp 
*/

#include "huge_number.h"
#include <iostream>
#include <string>

using namespace std;

// Default Constructor
huge_number::huge_number() {
  number = "0";
}
// Alternate Constructor
huge_number::huge_number(string _num){ 
  number = _num;
}
// Copy Constructor
huge_number::huge_number(const huge_number &h) {
  number = h.number;
}
// Destructor
huge_number::~huge_number() {
}

/*
 * Helper function that determines if the lhs string, which represents a number, 
 * is bigger than the rhs string. Returns true if numbers are equal
 */
bool huge_number::isBigger (string left, string right) const {

  // Strip out any leading 0's from left.
  while (left.length() > 0 && left[0] == '0')
    left.erase(0, 1);
  // Strip out any leading 0's from right.
  while (right.length() > 0 && right[0] == '0')
    right.erase(0, 1);

  if(left.length() < right.length()) {
    return false;
  }

  if(left.length() > right.length()) {
    return true;
  }

  // If we get this far, length is equal, so start walking numbers
  // to find out where they differ
  for(int i = 0; i < left.length(); i++) {
    if(left[i] < right[i]) {
      return false;
    }
    if(left[i] > right[i]) {
      return true;
    }
    if(left[i] == right[i]) {
      continue;
    }
  }
  // If we get this far, the numbers are equal, so return true
  return true;
}

/*
 * Adds two numbers stored in strings, building a string result.
 */
string huge_number::add (string left, string right) const {
  // Build up a string to contain the result.
  string result = "";

  // Work right to left.
  int left_pos  = left.length()  - 1;
  int right_pos = right.length() - 1;

  int carry = 0;

  // Loop, adding columns until no more digits remain.
  while (left_pos >= 0 || right_pos >= 0 || carry > 0)
  {
    // Get the digit from each string, or 0 if none.
    int left_digit  = left_pos  >= 0 ? left[left_pos--]   - '0' : 0;
    int right_digit = right_pos >= 0 ? right[right_pos--] - '0' : 0;

    // Calcuate the sum of the digits.
    int sum = left_digit + right_digit + carry;
    carry = sum / 10;
    sum   = sum % 10 + '0';

    // Put the sum into the new string (at the left side)
    result.insert (0, 1, static_cast<char>(sum) );
  }

  // Strip out any leading 0's from our result.
  while (result.length() > 0 && result[0] == '0')
    result.erase(0, 1);

  // If the string is empty, it's a 0.  Put one back.
  if (result.length() == 0)
    result = "0";
  
  return result;
}

/*
 * Multiplies two numbers stored in strings, building a string result.
 * The algorithm is long multiplication, starting with the most significant
 * digit of the multiplier.
 */
string huge_number::multiply (string left, string right) const{
  string result = "";
  int right_pos = 0;

  while (right_pos < right.length())
  {
    result.append("0");  // Multiply the product by 10.

    int right_digit = right[right_pos++] - '0';

    for (int i = 0; i < right_digit; i++)
      result = add(result, left);
  }

  // Strip out any leading 0's from our result.  (Might not be needed)

  while (result.length() > 0 && result[0] == '0')
    result.erase(0, 1);

  // If the string is empty, it's a 0.  Put one back.

  if (result.length() == 0)
    result = "0";

  return result;
}

/*
 * Subtracts two numbers stored in strings, building a string result.
 */
string huge_number::subtract (string left, string right) const {

  // Strip out any leading 0's from left.
  while (left.length() > 0 && left[0] == '0')
    left.erase(0, 1);
  // Strip out any leading 0's from right.
  while (right.length() > 0 && right[0] == '0')
    right.erase(0, 1);

  // Before doing anything, check to see if left is >= right.  If it is,
  // return 0, for two equal numbers, and for subtraction that would result
  // in a negative number, which we don't allow
  if(isBigger(right, left)) {
    return "0";
  }
  // Build up a string to contain the result.
  string result = "";

  // Work right to left.
  int left_pos  = left.length()  - 1;
  int right_pos = right.length() - 1;
  int carry = 0;

  // Loop, subtracting columns until no more digits remain.
  while (left_pos >= 0 || right_pos >= 0 || carry > 0)
  {
    // Get the digit from each string, or 0 if none.
    int left_digit  = left[left_pos--] - '0';
    int right_digit = right_pos >= 0 ? right[right_pos--] - '0' : 0;

    // If Carry is 1, prev pass borrowed from this column to complete,
    // subtract 1 from the left_digit and continue.  Checks to see if 
    // left_digit is 0, in which case sets left_digit to 9
    if(carry == 1) {
      if(left_digit == 0) {
	left_digit = 9;
      }
      else {
	left_digit = left_digit - 1;
      }
    }

    int diff;

    // Check to see if left is less than right.  If it isn't, subtract the two
    // numbers, set carry to 0 and continue.  If it is, add 10 to left_digit
    // so that subtraction doesn't result in a negative number and set carry
    // to 1 so that we can decriment the next left_digit, which we are
    // borrowing from in this pass.
    if(left_digit >= right_digit) {
      diff = left_digit - right_digit + '0';
      if(left_digit != 9) {
	carry = 0;
      }
    }
    else {
      diff = left_digit + 10 - right_digit + '0';
      carry = 1;
    }
    // Put the sum into the new string (at the left side)
    result.insert (0, 1, static_cast<char>(diff));
  }

  // Strip out any leading 0's from our result.
  while (result.length() > 0 && result[0] == '0')
    result.erase(0, 1);

  // If the string is empty, it's a 0.  Put one back.
  if (result.length() == 0)
    result = "0";
  
  return result;
}

/*
 * Divides two numbers stored in strings, building a string result.
 * The algorithm is standard long division.  Store remainder to private variable
 * which can be used in the mod function.
 */
string huge_number::divide (string dividend, string divisor) const {

  // Strip out any leading 0's from dividend.
  while (dividend.length() > 0 && dividend[0] == '0')
    dividend.erase(0, 1);
  // Strip out any leading 0's from divisor.
  while (divisor.length() > 0 && divisor[0] == '0')
    divisor.erase(0, 1);
 
  // If strings are equal, return a 1
  if(dividend.compare(divisor) == 0) {
    return "1";
  }

  // If right hand side is bigger than left hand side, return 0 
  // eg. (2/10)
  if(isBigger(divisor, dividend)) {
      return "0";
  }

  string quotient = "";

  // Get part of the dividend equal in length to the divisor's length
  // to start with
  string dividendSub = dividend.substr(0, divisor.length());
  

  // Index to walk through the dividend starts at the length of the
  // substring we just grabbed out
  int index = dividendSub.length();
  int place = 0;

  cout << "Beginning DividendSub: " << dividendSub << endl;

  // Main while loop, which will walk dividend until we reach the end
  while (index < dividend.length() + 1) {
    // Count to keep track of subtraction, which gets put into quotient
    int count = 0;

    // Check to see if divisor is bigger than dividend substring, 
    // and that they aren't the same, if not, grab another and continue
    if (isBigger(divisor, dividendSub) && dividendSub.compare(divisor) != 0) {
	dividendSub = dividend.substr(0, divisor.length() + 1);
    }

    // If strings are equal, set count to 1
    if(dividendSub.compare(divisor) == 0) {
      count = 1;
    } 
    else {
      while(isBigger(dividendSub, divisor)) {
	dividendSub = subtract(dividendSub, divisor);
	cout << "DivSub after subtraction: " << dividendSub << endl;
	count++;
      }
	cout << "DividendSub: " << dividendSub << endl;
    }
      
    cout << "Count: " << count << endl;

    // Return count to char form and add count to quotient
    count = count + '0';
    quotient.insert (place++, 1, static_cast<char>(count));
    
    // Update dividendSub to be the result of the subtraction plus the next 
    // number in the dividend
    dividendSub = dividendSub + dividend[index];
    index++;
    cout << "DivSub after Sub + 1: " << dividendSub << endl;

    // Check to see if, after grabbing next number, if divisor is smaller than
    // new substring.  If it is, stick 0 in quotient and move to next num
    while(isBigger(divisor, dividendSub) && index < dividend.length() + 1) {
      // Strip leading zero's in the case of equal subtraction,
      // but there are more numbers in dividend
      while (dividendSub.length() > 0 && dividendSub[0] == '0') {
	dividendSub.erase(0, 1);
      }
      // If strings are equal after stripping zero, set count to 1
      if(dividendSub.compare(divisor) == 0) {
	count = 1 + '0';
      }
      else {
	count = 0 + '0';
      }
      quotient.insert (place++, 1, static_cast<char>(count));
      dividendSub = dividendSub + dividend[index];
      index++;
      cout << "DivSub after Sub + 1 again: " << dividendSub << endl;
     }
  }
  return quotient;
}

/*
 * Given 2 numbers, left and right, left % right returns remainder of 
 * division of left by right 
 */
string huge_number::mod (string left, string right) const {

  // Strip out any leading 0's from left.
  while (left.length() > 0 && left[0] == '0')
    left.erase(0, 1);
  // Strip out any leading 0's from right.
  while (right.length() > 0 && right[0] == '0')
    right.erase(0, 1);
  
  // If left is smaller than right, return left as that is remainder
  if(isBigger(right, left)) {
    return left;
  }

  // Get quotient from divide function and then multiply it
  // by the divisor(right side) and take that product and subtract it 
  // from the original dividend (left side) to produce mod (remainder)
  string quotient = divide(left, right);
  return subtract(left, multiply(right, quotient));
}

/*
 * This method simply returns the backing string object
 */
string huge_number::get_value () {
  return number;
}

/*
 * Overloads plus operator
 */
huge_number huge_number::operator+ (const huge_number &rhs) const {
  return add(number, rhs.number);
}

/*
 * Overloads multiply operator
 */
huge_number huge_number::operator* (const huge_number &rhs) const {
  return multiply(number, rhs.number);
}

/*
 * Overloads minus operator
 */
huge_number huge_number::operator- (const huge_number &rhs) const {
  return subtract(number, rhs.number);
}

/*
 * Overloads divide operator
 */
huge_number huge_number::operator/ (const huge_number &rhs) const {
  return divide(number, rhs.number);
} 

/*
 * Overloads equals operator
 */
huge_number huge_number::operator= (const huge_number &rhs) {
  number = rhs.number;
  return *this;
}

/*
 * Overloads modulus operator
 */
huge_number huge_number::operator% (const huge_number &rhs) const {
  return mod(number, rhs.number);
}


