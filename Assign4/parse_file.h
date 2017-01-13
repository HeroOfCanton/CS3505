/*
Authors: Ryan Wellington, James Lundgren
Date Created: Feb 3, 2015
Last Modified: Feb 3, 2015


This class will contain methods to parse data from a .txt file 

 */


#ifndef PARSE_FILE
#define PARSE_FILE


#include"warehouse.h"
#include"food_item.h"
#include<boost/algorithm/string.hpp>
#include<iostream>
#include<vector> 
#include<string>
#include<map>


class parse_file
{
 public: 

 private: 


  std::map<std::string, warehouse> warehouses; //KEY: warehouse name VALUE: warehouse object

  std::string get_line(); // Gets a line from the file...not sure we will need this...
  std::vector<std::string> parse_line();  // Breaks the line up into the information that we need
  
  std::string generate_report();
  
};


#endif
