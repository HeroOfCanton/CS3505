/* 
 * Authors: James Lundgren & Ryan Welling
 * Date Created: Feb 3, 2015
 * Date Modified: Feb 3, 2015
 * warehouse.h
 * 
 * A 'Warehouse' is defined as an object containing a name and backing
 * warehouse object which is a map of warehouse name(key) and vector list
 * of food_items(value)
 */

#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <string>
#include <vector>
#include <map>
#include "food_item.h"

typedef std::vector<food_item> foodItem;

class warehouse
{
 public:
  // Constructors / Copy Constructor / Destructor
  warehouse();
  warehouse(std::string _name);
  warehouse(const warehouse &w);
  ~warehouse();

  // Functions 
  void add(food_item _food_item, int quantity);  // adds food items
  void remove(std::string upc, int quantity);    // removes food items
  void nextDay();                                // decriment shelf life, 
                                                 // call remove on expired items
  std::map<std::string, foodItem> getMap();      // returns backing map;

  // Debug Functions
  int size();                                    // returns size of backing map
  std::vector <std::string> printMap();          // returns vector of items in backing map

 private:
  // Member Variables
  std::string name;
  std::map<std::string, foodItem> warehouseMap;  // key: string upc - value: food_item
};

#endif
