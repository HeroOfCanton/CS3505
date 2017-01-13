/* 
 * Authors: James Lundgren, Ryan Welling
 * Date Created: Feb 3, 2015
 * Date Last Modified: Feb 6, 2015
 * parse_file.cpp
 * 
 * This file will take a single command line argument .txt file
 * and parse it out, according to the specifications in Assign4.
 *
 * This file will also generate a report of unstocked and well-
 * stocked products, after a series of transactions have been run
 * on the corresponding food items and warehouses.
 *
 * This file contains the main method for running our program. 
 */

#include"warehouse.h"
#include"food_item.h"

#include<iostream>
#include<cstring> // used for atoi
#include<cstdlib> // used for atoi
#include<fstream> // used for file reading

using namespace std; 

// Member variable
map<string, warehouse> warehouses;
map<string, food_item> food_items;

// Member functions
void generate_report();
food_item get_fooditem(string name);

/**
 * Main method for parsing input .txt file
 *
 * Calls generate_report() at the end
 */
int main(int argc, char* argv[])
{
  
  // Get the file we need
  ifstream in(argv[1]);
    
  string word;

  // Go through the file
  while (in >> word)
    {      
      // check the first word of the line, do the appropriate action based off
      // of what it is



      // Add a new food item to the food_items map
      if (word == "FoodItem")
	{

	  // Need to get upc, shelf-life, and name from the current line
	  // Each for loop advances the word to the appropriate value we need to grab
	  // The upc is 4 words in from the FoodItem word, get it.
	  string upc;
	  for (int i = 0; i < 4; i ++)
	    in >> upc;
	  
	  string shelf_life;
	  for (int i = 0; i < 3; i ++)
	    in >> shelf_life;
	  
	  // Since product names can have spaces, we need to continuously check for the
	  // end of the line, signifying the end of the product name. String1 grabs each
	  // individual word of the name, and name2 is the concatenated name
	  string name1;
	  string name2;
	  
	  // move forward past the 'Name:' word
	  in >> name1;

	  while(in >> name1)
	    {
	      
	      // looks for the new line by looking for a non-space character
	      char check = in.peek();
	      if (check != ' ')
		{
		  // add the last word of the name
		  name2 += name1;
		  break;
		}

	      // add the word to the name
	      name2 += name1 + " ";
	    } 
	  
	  // we need to get the shelf life as an int
	  int _shelf_life = atoi(shelf_life.c_str());
	  
	  // make the food item, add it to food_items map so we can find/use it later.
	  food_item item(upc, _shelf_life, name2);
	  food_items[upc] = item;	  
	}
      




      // Add a new warehouse to the warehouse map
      else if (word == "Warehouse")
	{
	  // Since the warehouses can have more than one word in their names, and we 
	  // know that it will be at the end of the line, look for the first non-space 
	  // character as we concatenate to warehouse_name2
	  string warehouse_name1;
	  string warehouse_name2;
	 
	  // move forward past the dash
	  in >> warehouse_name1;
	  
	  // get the warehouse name
	  while(in >> warehouse_name1)
	    {
	      if(in.peek() != ' ')
	      {
		// add the final word of the warehouse name, no space
		warehouse_name2 += warehouse_name1;
		break;
	      }
	      // add the word plus a space
	      warehouse_name2 += warehouse_name1 + " ";		
	    }
	
	  // Add it to the warehouses map for later use
	  warehouse _warehouse(warehouse_name2);
	  warehouses[warehouse_name2] = _warehouse;
	}





           
      // don't need to do anything, just skip ahead 2 words
      else if (word == "Start")
	{	
	  in >> word;
	  in >> word;
	}



           
      // need to grab upc, quantity, and warehouse name, add to that warehouses
      // inventory
      else if (word == "Receive:")
	{
	  string upc;
	  in >> upc;
	  
	  string quantity;
	  in >> quantity;
	  
	  // same as else if (word == "warehouse")
	  string warehouse_name1;
	  string warehouse_name2;
	  
	  while(in >> warehouse_name1)
	    {
	      if(in.peek() != ' ')
	      {
		warehouse_name2 += warehouse_name1;
		break;
	      }
	      
	      warehouse_name2 += warehouse_name1 + " ";		
	    }

	  int quantity_int = atoi(quantity.c_str());
	  food_item temp_fi = get_fooditem(upc);
	  
	  // add the food item to the warehouse
	  warehouses[warehouse_name2].add(temp_fi, quantity_int);
	}
           





      // need to grab upc, quantity, and warehouse name, remove from that warehouses
      // inventory
      else if (word == "Request:")
	{
	  
	  string upc;
	  in >> upc;

	  string quantity;
	  in >> quantity;

	  string warehouse_name1;
	  string warehouse_name2;
	  
	  while(in >> warehouse_name1)
	    {
	      if(in.peek() != ' ')
	      {
		warehouse_name2 += warehouse_name1;
		break;
	      }
	      
	      warehouse_name2 += warehouse_name1 + " ";		
	    }
	  
	  int quantity_int = atoi(quantity.c_str());
	  food_item temp_fi = get_fooditem(upc);
	  
	  // remove the food item from the warehouse
	  warehouses[warehouse_name2].remove(upc, quantity_int);
	}
      




      // advance the day on all warehouse objects, effectively decreases the shelf
      // life of each item in that warehouse, removes any were shelf-life == 0
      else if (word == "Next")
	{
	  map<string, warehouse>::iterator it = warehouses.begin();
	  
	  // get each warehouse object and advance the day
	  for(it; it != warehouses.end(); it++)
	    {
	      it->second.nextDay(); 
	    }	  
	}
      



      // we are at the end of the file, jump out of the loop
      else if (word == "End")
	{
	  break;
	}      
    }

  // finished parsing the provided file, generate the report
  generate_report();
}



/*
 * Helper method used to get the food item out of the
 * food_items map 
 */
food_item get_fooditem(string name)
{
  map<string, food_item>::iterator it = food_items.begin();
  
  // get the warehouse object
  for(it; it != food_items.end(); it++)
    {
      if (it->first == name)
	{
	  return it->second;
	}
    }
}

/*
 * Helper method that generates the final report
 */
void generate_report()
{
  map<string, food_item>::iterator it_fi = food_items.begin(); 
  map<string, warehouse>::iterator it_wh = warehouses.begin();
  
  map<string, string> unstocked;
  map<string, string> stocked;
  
  // iterate through each food item
  for(it_fi; it_fi != food_items.end(); it_fi++)
  {
      // create/reset count of how many warehouses item shows up in
      int warehouse_count = 0;

      // iterate through each warehouse for the specific food item
      for(it_wh; it_wh != warehouses.end(); it_wh++)
	{
	  // get the backing map to each warehouse and go to key == UPC
	  // and check to see if vector<food_item> is empty
	  if (!(it_wh->second.getMap()[it_fi->first].empty()))
	    {
	      warehouse_count++;
	    }
	}

      // if count is < 1, it's not stocked anywhere, add to unstocked list
      if (warehouse_count < 1) 
	{
	  unstocked[it_fi->first] = it_fi->second.getName();
	}
      
      // if count > 1, it's stocked at least 2 places, add to well stocked list
      else if (warehouse_count > 1)
	{
	  stocked[it_fi->first] = it_fi->second.getName();
	}
      
      // Reset warehouse iterator for the next warehouse object
      it_wh = warehouses.begin();
  }
  
  cout << "Report by Ryan Welling and James Lundgren" << endl;
  cout << endl;
  
  // Print out Unstocked Products (warehouses stocking food_item == 0)
  cout << "Unstocked Products:" << endl; 
  map<string, string>::iterator it_un = unstocked.begin(); 
  
  for(it_un; it_un != unstocked.end(); it_un++)
    cout << it_un->first << " " << it_un->second << endl;
  
  cout << endl;
  
  // Print out Well-Stocked Products (warehouses stocking food_item >= 2)
  cout << "Well-Stocked Products:" << endl; 
  map<string, string>::iterator it_st = stocked.begin(); 
  
  for(it_st; it_st != stocked.end(); it_st++)
    cout << it_st->first << " " << it_st->second << endl;
  
  cout << endl;
}
