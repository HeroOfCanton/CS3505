/* 
 * Authors: James Lundgren & Ryan Welling
 * Date Created: Feb 3, 2015
 * Date Modified: Feb 3, 2015
 * food_item.h
 * 
 * A 'FoodItem' is defined as an object containing a UPC, name,
 * expiration date, and shelf life.
 */

#ifndef FOODITEM_H
#define FOODITEM_H

#include <string>

class food_item
{
 public:
  // Constructors / Copy Constructor / Destructor
  food_item();
  food_item(std::string _upc, int _shelf_life, std::string _name);
  food_item(const food_item &f);
  ~food_item();

  // Functions
  std::string getUPC() const; 
  std::string getName() const; 
  int getShelfLife() const;  
  void setShelfLife(int _shelf_life); 

 private:
  // Member Variables
  std::string upc;
  int shelf_life;
  std::string name;
};

#endif
