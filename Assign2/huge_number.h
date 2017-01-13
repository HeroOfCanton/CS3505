/*
 * Ryan Welling
 * 22 Jan 2015
 * huge_number.h
 */

#ifndef HUGE_NUMBER_H
#define HUGE_NUMBER_H

#include <string>

class huge_number 
{

 private:

  std::string number;

  std::string add      (const std::string left, const std::string right) const;
  std::string multiply (const std::string left, const std::string right) const;
  std::string divide   (const std::string left, const std::string right) const;
  std::string subtract (const std::string left, const std::string right) const;  
  std::string mod      (const std::string left, const std::string right) const; 

  bool isBigger        (const std::string left, const std::string right) const;

 public: 

  huge_number();
  huge_number(std::string _num);
  huge_number(const huge_number &h);
  ~huge_number();

  std::string get_value ();

  huge_number operator+ (const huge_number &rhs) const;
  huge_number operator* (const huge_number &rhs) const;
  huge_number operator- (const huge_number &rhs) const;
  huge_number operator/ (const huge_number &rhs) const;
  huge_number operator= (const huge_number &rhs);
  huge_number operator% (const huge_number &rhs) const;
};

#endif
