
Classes: 
	 Warehouse:
		Variables: 

		name: string
		food_items: hash-table<FoodItem>, hash by upc
		expiration_dates: key, value pair, key = expiration date, value = upc 
		
		Functions: 

		get_inventory()
		add_item()
		remove_item()
			   
	 FoodItem:
		Variables:
 
		upc: string
		shelf_life: integer
		name: string
		expiration_date: date, not entirely sure on this one
		expired: bool, same as expiration date above...
		
	
		Functions: 
		none
		
	 Date: 
	       MM/DD/YYYY
	       
	       Potentially just use a library out there, otherwise 
	       need functions:
	       
	 
