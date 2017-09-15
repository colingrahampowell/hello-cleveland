/******************************************************************************
** Program Filename: Hero.cpp
** Author: Colin Powell
** Date: 8/4/16
** Description: Final Project - Hero class implementation file
** Input: N/A
** Output: N/A
*******************************************************************************/

#include "Hero.hpp"

/******************************************************************************
** Function: Hero()
** Description: Hero class constructor
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: An instance of the Hero class has been created.
*******************************************************************************/

Hero::Hero()
{
	roadie = NULL;	// cannot initially store items.
	numItems = 0;	// current number of items.
	itemMax = 0;	// max number of items that can be carried.
}

/******************************************************************************
** Function: Hero()
** Description: Hero class destructor
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: All dynamic memory associated with the Hero object has been
** freed, and the Hero object has been destroyed.
*******************************************************************************/

Hero::~Hero() 
{ 
	for(int i = 0; i < this->numItems; i++)
		delete roadie[i];

	delete [] roadie;
}

/******************************************************************************
** Function: recruitRoadie()
** Description: Allocates memory for an array of three Item objects
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: If hasRoadie() is false, the function has allocated memory
** for an array of pointers to three Item objects and returned true. Otherwise, 
** it has returned false.
*******************************************************************************/

bool Hero::recruitRoadie()
{
	bool recruited = false;

	if(hasRoadie() == false) {
		this->itemMax = 3;
		roadie = new Item *[itemMax];

		for(int i = 0; i < itemMax; i++)
			roadie[i] = NULL;

		recruited = true;
	}

	return recruited;
}

/******************************************************************************
** Function: pickUp()
** Description: If there is space for an Item, the function adds it to the roadie
** array. 
** Parameters: Item newItem, the Item to be added to the Roadie array. 
** Pre-Conditions: none
** Post-Conditions: If the roadie array has been initialized and numItems < itemMax, 
** the function adds the desired Item object to the roadie array and returns true. 
** Otherwise, the function returns false. 
*******************************************************************************/

bool Hero::pickUp(Item *newItem)
{
	bool added = false;

	if( hasRoadie() && (numItems < itemMax) ) {
		roadie[numItems++] = newItem;
		added = true;
	}

	return added;
}

/******************************************************************************
** Function: drop()
** Description: Removes an Item from the Hero's roadie array and returns it.
** Parameters: string itemID, the ID of the Item object to be dropped.
** Pre-Conditions: The function should be called after confirming that the item
** exists, although if the function is called for a non-existent itemID, it 
** simply returns NULL.
** Post-Conditions: If an Item object with itemID == idIn exists in the roadie
** array, the pointer to that Item has been removed from the array, numItems 
** has been decremented, and array values have been shifted down as needed to 
** accommodate the removal. That Item pointer has then been returned from the 
** function. If, however, an Item object with the desired itemID is not found, 
** NULL is returned to the calling function.
*******************************************************************************/

Item *Hero::drop(std::string idIn)
{
	if( hasRoadie() && hasItem(idIn) ) {
	
		for(int i = 0; i < this->numItems; i++) {
			if( roadie[i]->getID() == idIn ) {
			
				Item* temp = roadie[i];
				roadie[i] = NULL;

				int count = i;

				while(count < (this->numItems - 1)) { 
					roadie[count] = roadie[count + 1];
					count++;
				}

				this->numItems--;
				return temp;
			}
		}
	}

	return NULL;
}

/******************************************************************************
** Function: hasRoadie()
** Description: Determines if the Hero has found a roadie to carry Items. 
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: If roadie is not equal to NULL, the function returns true.
** Otherwise, it returns false.
*******************************************************************************/

bool Hero::hasRoadie() 
{ 
	return (roadie != NULL); 
}

/******************************************************************************
** Function: hasItem()
** Description: Determines if the Hero object possesses the specified item.
** Parameters: string itemID, the ID of an Item object.
** Pre-Conditions: none
** Post-Conditions: If there is an ID match in the roadie array, the function
** returns true. Otherwise, it returns false.
*******************************************************************************/

bool Hero::hasItem(std::string itemID)
{	
	bool found = false;

	if(hasRoadie()) {	
		for(int i = 0; i < this->numItems; i++) {
			if( roadie[i]->getID() == itemID )
				found = true;
		}
	}

	return found;
}

/******************************************************************************
** Function: roadieEmpty()
** Description: Returns true if the Hero object is not currently carrying anything
** - that is, if the roadie array is empty or uninitialized. 
** Parameters: none.
** Pre-Conditions: none
** Post-Conditions: If numItems == 0, the function has returned true. Otherwise, it
** has returned false.
*******************************************************************************/

bool Hero::roadieEmpty()
{	
	return (numItems == 0);
}

/******************************************************************************
** Function: roadieAtCapacity()
** Description: 
** Parameters: none.
** Pre-Conditions: 
** Post-Conditions: 
*******************************************************************************/

bool Hero::roadieAtCapacity()
{	
	return ( (numItems == itemMax) && hasRoadie() );
}

/******************************************************************************
** Function: displayItems()
** Description: Displays the current contents of the roadie array
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: The ID and description of each Item object in the roadie
** array has been output to the console.
*******************************************************************************/

std::string Hero::displayItems()
{
	std::ostringstream itemDisplay;

	if(hasRoadie() == false) {
		itemDisplay << "You're not carrying anything. Well, you've got your ";
		itemDisplay << std::endl;
		itemDisplay << "guitar, but it's not like you're putting THAT down," << std::endl;
		itemDisplay << "right?" << std::endl;
	}

	else if(roadieEmpty()) {
		itemDisplay << "Bob the Roadie isn't carrying anything." << std::endl;
	}
	else {
		itemDisplay << std::endl;
		
		for(int i = 0; i < HEADER_WIDTH; i++)	
			itemDisplay << "-";
		
		itemDisplay << "INVENTORY";
		
		for(int i = 0; i < HEADER_WIDTH; i++)
			itemDisplay << "-"; 
		
		itemDisplay << std::endl;

		itemDisplay << std::left << std::setw(12) << "ITEM ID";
		itemDisplay << std::left << std::setw(36) << "DESCRIPTION" << std::endl;

		for(int i = 0; i < numItems; i++) {
			itemDisplay << std::left << std::setw(12) << roadie[i]->getID();
			itemDisplay << std::left << std::setw(36) << roadie[i]->getDescription();
			itemDisplay << std::endl;
		}

//		itemDisplay << "---------------------------------";
		itemDisplay << std::endl;
	}

//	itemDisplay << std::endl;

	return itemDisplay.str();

}
