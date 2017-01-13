/*
 * Authors: James Lundgren & Ryan Welling
 * Date Created: Feb 3, 2015
 * Date Last Modified: Feb 6, 2015
 * warehouse.cpp
 *
 * This class is warehouse house object.  It contains a
 * backing map of a Key: string (representing a food_item UPC)
 * and a Value: vector<food_item>.  This allows O(1) access
 * to the food_item and then O(N) access to the items in the vector
 */

#include "warehouse.h"
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>

using namespace std;

/****************
 * CONSTRUCTORS *
 ***************/

// Default Constructor
warehouse::warehouse()
{
  name = "";
}

// Constructor with just warehouse name
warehouse::warehouse(string _name)
{
  name = _name;
}

// Copy Constructor
warehouse::warehouse(const warehouse &w)
{
  name = w.name;
  warehouseMap = w.warehouseMap;
}

// Destructor
warehouse::~warehouse()
{

}

/********************
 * PUBLIC FUNCTIONS *
 *******************/

/**
 * This function takes in a food_item object and a quantity and adds it to 
 * the backing map.  It should parse out the UPC from the food_item object 
 * and use that as the key for the map.
 */
void warehouse::add(food_item _food_item, int quantity)
{
  // If KVP exists, adds _food_item to vector. If KVP doesn't exist
  // creates key and value with _food_item.
  for(int i = 0; i < quantity; i++) 
  {
    warehouseMap[_food_item.getUPC()].push_back(_food_item);
  }
}

/**
 * This function DOES NOT remove the key / value pair associated with the
 * passed in UPC parameter; rather, it erases the food_items from the vector
 * until vector.empty()
 *
 * This function should also remove the oldest food item (closest shelf_life
 * to zero) if there are multiple options to choose from.
 */
void warehouse::remove(string upc, int quantity)
{
  for(int i = 0; i < quantity; i++)
  {
    map<string, foodItem>::iterator it = warehouseMap.find(upc);
    
    // Key was found, do something with UPC 
    if(it != warehouseMap.end() )
    {
      // If value is empty, food items have been removed already, return
      if(it->second.empty())
	return;
      
      // value has something in it, now we need to find the oldest food_item
      // start with shelflife of item at 0
      int oldest = it->second.at(0).getShelfLife();
      int index = 0; // index to be erased
      int count = 0; // count to keep track of where we are
      
      // walk vector
      BOOST_FOREACH( food_item &f, it->second )
      {
	// grab shelflife, if older, update oldest and index
	if(f.getShelfLife() < oldest)
	{
	  oldest = f.getShelfLife();
	  index = count;
	}
	count++;
      }
      // when we're done, index should be where oldest item is, erase it
      it->second.erase(it->second.begin() + index);
    }
    // Key was not found, exit method doing nothing
    else
    {
      return;
    }
  }
}

/**
 * This function iterates through the backing map's key / value pairs and
 * decriments the shelf life variable and checks to see if that becomes 0.
 * If shelf_life == 0, item is removed from warehouse
 */
void warehouse::nextDay()
{
  map<string, foodItem>::iterator it = warehouseMap.begin();

  // use for loop from lab example to walk map, then boost_foreach down vector list
  for(it; it != warehouseMap.end(); it++)
  { 
    vector<food_item> temp;

    BOOST_FOREACH( food_item &f, it->second )
    {
      // grab shelflife and decriment
      int sl = f.getShelfLife();

      f.setShelfLife(--sl);
      
      // After decriment, if shelf life is not equal to zero, add it to a temp vector
      // which will replace it->second when we are done
      if(f.getShelfLife() != 0)
      {
	temp.push_back(f);
      }
    }
    it->second = temp;
    /*
    itr = it->second.begin();
    cout << "AFTER PROCESSING" << endl;
    for(itr; itr != it->second.end(); ++itr)
    {
      cout << itr->getShelfLife() << " " << itr->getName() << endl;
    }
    */  
  }
}

/**
 * Accessor method for backing map
 */
map<string, foodItem> warehouse::getMap()
{
  return warehouseMap;
}

/*******************
 * DEBUG FUNCTIONS *
 ******************/

/**
 * Returns backing map's size
 */
int warehouse::size()
{
  return warehouseMap.size();
}

/**
 * Returns a vector<string> of all items in the backing map
 */
vector<string> warehouse::printMap()
{
  map<string, foodItem>::iterator itr = warehouseMap.begin();
  string printLine;
  vector<string> stuffInMap;
  for(itr; itr != warehouseMap.end(); itr++)
  {
    printLine = itr->first + " => ";
    printLine += "\n";
    BOOST_FOREACH( food_item f, itr->second )
    {
      printLine += " UPC: " + f.getUPC() + " ";
      printLine += "Name: " + f.getName() + " ";
      printLine += "Shelf Life: " + boost::lexical_cast<std::string>(f.getShelfLife());
      printLine += "\n";
      stuffInMap.push_back(printLine);
    }
  }
  return stuffInMap;
}
