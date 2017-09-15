/******************************************************************************
** Program Filename: HeroTest.cpp
** Author: Colin Powell
** Date: 8/4/16
** Description: Performs a series of tests to verify functionality of the Hero
** and Item classes.
** Input: none.
** Output: The results of a series of tests.
*******************************************************************************/

#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::string;

#include "Hero.hpp"
#include "Item.hpp"

/******************************************************************************
** Function: main()
** Description: HeroTest's main() function.
** Parameters: none.
** Pre-Conditions: none.
** Post-Conditions: Performs a series of tests to verify functionality of the 
** Hero and Item classes. 
*******************************************************************************/

int main()
{
	Hero *nigel = new Hero();

	cout << "Creating four objects: a skeleten key, an old broom, a rickety";
	cout << " ladder, and a ballpoint pen." << endl;

	Item *key = new Item("A skeleton key.", "KEY");
	Item *broom = new Item("An old broom.", "BROOM");
	Item *ladder = new Item("A rickety ladder.", "LADDER");
	Item *pen = new Item("A ballpoint pen.", "PEN");

	cout << key->getDescription() << endl;
	cout << broom->getID() << endl;

	cout << "Attempting to pick up without roadie...";

	if(nigel->pickUp(key))
		cout << "Picked up key." << endl;
	else 
		cout << "ERROR - no roadie" << endl;

	nigel->displayItems();

	cout << "Recruiting roadie...";
	
	if(nigel->recruitRoadie())
		cout << "Recruited." << endl;

	if(nigel->pickUp(key)) 
		cout << "Picked up key." << endl;
	else 
		cout << "ERROR - key" << endl;

	if(nigel->pickUp(broom))
		cout << "Picked up broom." << endl;
	else 
		cout << "ERROR - broom" << endl;

	if(nigel->pickUp(ladder))
		cout << "Picked up ladder." << endl;
	else 
		cout << "ERROR - ladder" << endl;

	if(nigel->pickUp(pen))
		cout << "Picked up pen." << endl;
	else 
		cout << "ERROR - pen" << endl;

	cout << nigel->displayItems();

	cout << "Dropping ladder..." << endl;
	Item* newItem = nigel->drop("LADDER");
	cout << newItem->getID() << endl;
	cout << newItem->getDescription() << endl;
	delete newItem;
	newItem = NULL;

	cout << nigel->displayItems();

	cout << "Dropping broom..." << endl;
	newItem = nigel->drop("BROOM");
	cout << newItem->getID() << endl;
	cout << newItem->getDescription() << endl;
	delete newItem;
	newItem = NULL;

	cout << nigel->displayItems();

	cout << "Dropping key..." << endl;
	newItem = nigel->drop("KEY");
	cout << newItem->getID() << endl;
	cout << newItem->getDescription() << endl;
	delete newItem;
	newItem = NULL;

	cout << nigel->displayItems();

	cout << "Dropping something else..." << endl;
	newItem = nigel->drop("KEY");
	if(newItem == NULL)
		cout << "Item is null!" << endl;

	delete nigel;

	return 0;

}
