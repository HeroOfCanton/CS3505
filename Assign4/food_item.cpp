/* 
 * Authors: James Lundgren & Ryan Welling
 * Date Created: Feb 3, 2015
 * Date Modified: Feb 6, 2015
 * food_item.cpp
 *
 * This class is a food_item.  It contains a string upc, 
 * int shelf_life, and string name, with appropriate 
 * accessor and mutator methods.
 */

#include "food_item.h"

using namespace std;

/********************
 *   CONSTRUCTORS   *
 *******************/                   

// Default Constructor
food_item::food_item() 
{
  upc = "0";
  shelf_life = 0;
  name = "";
}

// Alternate Constructor
food_item::food_item(std::string _upc, int _shelf_life, std::string _name) 
{
  upc = _upc;
  shelf_life = _shelf_life;
  name = _name;
}
  
// Copy Constructor
food_item::food_item(const food_item &f) 
{
  upc = f.upc;
  shelf_life = f.shelf_life;
  name = f.name;
}

// Destructor
food_item::~food_item() 
{
}

/********************
 * PUBLIC FUNCTIONS *
 *******************/

/**
 * Returns upc as a string
 */ 
string food_item::getUPC() const 
{
  return upc;
}
 
/**
 * Returns name as a string
 */
string food_item::getName() const
{
  return name;
}

/**
 * Returns shelf_life as an int
 */
int food_item::getShelfLife() const
{
  return shelf_life;
}

/**
 * Sets shelf_life variable
 */
void food_item::setShelfLife(int _shelf_life)
{
  shelf_life = _shelf_life;
} 
