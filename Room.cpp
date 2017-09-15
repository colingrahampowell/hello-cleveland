/******************************************************************************
** Program Filename: Room.cpp
** Author: Colin Powell
** Date: 8/4/16
** Description: Final Project - Room base class implementation file
** Input: User selection of menu options relating to specific room actions.
** Output: Menu-based interface, output to console.
*******************************************************************************/

#include "Room.hpp"

/***************************
** CONSTRUCTOR / DESTRUCTOR
****************************/

/******************************************************************************
** Function: Room(std::string, bool)
** Description: Room class default constructor
** Parameters: idIn, the room's unique ID. 
** Pre-Conditions: none
** Post-Conditions: An instance of the Room class has been created with all 
** directional pointers set to NULL, and the nigel object set to the value of
** the occupant pointer.
*******************************************************************************/

Room::Room(std::string idIn)
{
	this->roomID = idIn;

	north = NULL;
	south = NULL;
	east = NULL;
	west = NULL;
	up = NULL;
	down = NULL;
	
	this->nigel = NULL;

	validChoices.push_back('M');	//move to another room
	validChoices.push_back('H');	//get a hint
	validChoices.push_back('L');	//look around
	validChoices.push_back('I');	//check inventory
	validChoices.push_back('D');	//drop an item
	validChoices.push_back('P');	//pick something up

	for(int i = 0; i < this->HEADER_WIDTH; i++) 
		menuOptions << "-";
	
	menuOptions << "OPTIONS";

	for(int i = 0; i < this->HEADER_WIDTH; i++) 
		menuOptions << "-";
	
	menuOptions << std::endl;
	menuOptions << "M: Move to another room." << std::endl;
	menuOptions << "H: Get a hint." << std::endl;
	menuOptions << "L: Look around the room." << std::endl;
	menuOptions << "I: Check inventory." << std::endl;
	menuOptions << "D: Drop an item, remove it from your inventory." << std::endl;
	menuOptions << "P: Pick something up, add it to your inventory." << std::endl;
}

/******************************************************************************
** Function: ~Room
** Description: Room class virtual destructor
** Parameters: 
** Pre-Conditions: none
** Post-Conditions: All dynamic memory associated with the Room object and its 
** derived classes has been freed, and the Room object has been destroyed. 
*******************************************************************************/

Room::~Room()
{ 
	delete nigel;

	for(unsigned int i = 0; i < roomItems.size(); i++)
		delete roomItems[i];
}

/**************************
** ROOM ACTIONS
***************************/

/******************************************************************************
** Function: takeFromHero()
** Description: Adds a pointer to an Item object to the Room's roomItems vector, 
** after calling the Hero object's drop function.
** Parameters: 
** Pre-Conditions: none
** Post-Conditions: If an Item object was dropped by the Hero, it was added to
** the roomItems vector. Otherwise, the function has simply returned a string
** noting that the item wasn't found or that there is nothing for the Hero to
** drop.
*******************************************************************************/

std::string Room::takeFromHero()
{
	bool added = false;

	std::ostringstream takeNarr;

	if( nigel->roadieEmpty() == false ) {	//if there's something to remove
		std::string itemKey = inputRemoveItem();

		if( nigel->hasItem(itemKey) ) {		//if the hero has the desired item
			Item *newItem = nigel->drop(itemKey);	//drop it, add it to roomItems
			roomItems.push_back(newItem);

			added = true;
		}

		if(added)	//report status of hero drop:
			takeNarr << "Item removed from inventory." << std::endl;
		else 
			takeNarr << "Item not found." << std::endl;
	}
	else 
		takeNarr << "You don't have anything to drop." << std::endl;

	return takeNarr.str();
}

/******************************************************************************
** Function: giveToHero()
** Description: Removes an Item object from the roomItems vector and puts it
** in the Hero's inventory.
** Parameters: none.
** Pre-Conditions: none
** Post-Conditions: If there is an Item pointer in the roomItems vector and its ID was
** input correctly, that Item pointer has been transferred to the Hero's
** inventory.
*******************************************************************************/

std::string Room::giveToHero()
{
	bool removed = false;

	std::ostringstream giveNarr;

	/* 
	** if the Hero has a 'container', if that container isn't full, and the room 
	** isn't empty 
	*/

	if( nigel->hasRoadie() 
		&& (nigel->roadieAtCapacity() == false) 
		&& (roomItems.size() > 0)) {

		std::string itemKey = inputAddItem();

		for(unsigned int i = 0; i < roomItems.size(); i++) {
			if(roomItems[i]->getID() == itemKey) {
		
				nigel->pickUp(roomItems[i]);
				giveNarr << "Bob picks it up. ";
				giveNarr << roomItems[i]->getID() << " added to inventory."; 
				giveNarr<< std::endl;

				//order doesn't matter, so we can just swap this with the last value:
				Item *temp = roomItems[i];
				roomItems[i] = roomItems.back();
				roomItems.back() = temp;

				//and pop the last value in the vector:
				roomItems.back() = NULL;
				roomItems.pop_back();

				removed = true;
			}
		}

		if(!removed)	//report as a string
			giveNarr << "Item not found." << std::endl;
	}

	/* report any issues in string form - only the most pertinent should be reported */
	if(roomItems.size() == 0 && !removed) { 
		giveNarr << "There's nothing to pick up in this room.\n";
	}

	else {	//either the Hero doesn't have a roadie, or the roadie is at capacity
		if( nigel->hasRoadie() == false) {
			giveNarr << "You can't carry anything - you're wearing spandex!\n";
			giveNarr << "Hey, where'd that roadie go, anyway?\n";
		}

		else if( nigel->roadieAtCapacity() == true && !removed )
			giveNarr << "Bob the roadie can't carry anything else.\n";
	}

	return giveNarr.str();
}

/******************************************************************************
** Function: giveHint()
** Description: Outputs a hint to the user.
** Parameters: none.
** Pre-Conditions: none.
** Post-Conditions: A string representing a hint for winning the game has been
** returned as a string.
*******************************************************************************/

std::string Room::giveHint()
{
	std::ostringstream hint;

	hint << 
	"First, go west and get the roadie so that you can carry objects.\n"
	"Then, pick up a sandwich in the green room and give it to the janitor\n"
	"He will drop a key - pick that up, and use it to enter the boiler room\n"
	"Once the boiler room is isolated, pick up the oil in that room and try\n"
	"to activate the lift Take the lift up to the next floor. Lower the\n"
	"Stonehenge monument onto the stage to buy a little more time. Pick up\n"
	"the screwdriver. Go into the control room and use it to fix the intercom.\n"
	"Move west until you get to the new lift. Get into the lift. That's it.\n"

	"Alternatively, if you have the rope when you're on the upper level, you\n"
	"can try to jump off onto the stage floor. This will likely cause you to\n"
	"lose, but there's a chance that you pull it off.\n";

	return hint.str();
}

/**************************
** DISPLAY FUNCTIONS
***************************/

/******************************************************************************
** Function: lookAround
** Description: Returns a description of the room.
** Parameters: none.
** Pre-Conditions: none
** Post-Conditions: The room's description and the contents of its roomItems
** vector have been returned to the calling function.
*******************************************************************************/

std::string Room::lookAround() 
{ 
	std::ostringstream look;
	
	for(int i = 0; i < HEADER_WIDTH; i++)
		look << "-";

	look << this->roomID;
	
	for(int i = 0; i < HEADER_WIDTH; i++)
		look << "-";

	look << std::endl;
	look << this->roomDescription.str();
	look << std::endl;
	look << this->displayRoomItems();

	return look.str(); 
}

/******************************************************************************
** Function: displayMoveDirections
** Description: Displays possible movement directions out of the room.
** Parameters: none.
** Pre-Conditions: none
** Post-Conditions: For each directional pointer, if that pointer is not set to
** NULL, a string is returned listing that pointer's directiona as a possible
** move out of the space. 
*******************************************************************************/

std::string Room::displayMoveDirections()
{
	std::ostringstream moveDescript;
	int numdirs = 0;

	moveDescript << "Obvious Exits: " << std::endl;

	if(north != NULL) {
		moveDescript << "N: North" << std::endl;
		numdirs++;
	}
	
	if(south != NULL) {
		moveDescript << "S: South" << std::endl;
		numdirs++;
	}

	if(east != NULL) {
		moveDescript << "E: East" << std::endl;
		numdirs++;
	}

	if(west != NULL) {
		moveDescript << "W: West" << std::endl;
		numdirs++;
	}

	if(up != NULL) {
		moveDescript << "U: Up" << std::endl;
		numdirs++;
	}

	if(down != NULL) {
		moveDescript << "D: Down" << std::endl;
		numdirs++;
	}

	if(numdirs == 0)
		moveDescript << "None!" << std::endl;

	moveDescript << std::endl;

	return moveDescript.str();
}

/******************************************************************************
** Function: displayRoomItems()
** Description: 
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: The ID and description of each Item object in the roomItems
** array has been output to the console.
*******************************************************************************/

std::string Room::displayRoomItems()
{
	std::ostringstream itemDisplay;

	itemDisplay << "You search around and find: " << std::endl;

	if(roomItems.size() > 0) {

		itemDisplay << std::left << std::setw(12) << "ITEM ID";
		itemDisplay << std::left << std::setw(36) << "DESCRIPTION" << std::endl;

		for(unsigned int i = 0; i < roomItems.size(); i++) {
			itemDisplay << std::left << std::setw(12) << roomItems[i]->getID();
			itemDisplay << std::left << std::setw(36) << roomItems[i]->getDescription();
			itemDisplay << std::endl;
		}

	}
	else {
		itemDisplay << "Nothing of interest." << std::endl;
	}

		itemDisplay << std::endl;

	return itemDisplay.str();

}

/******************************************************************************
** Function: displayMenu
** Description: Returns the available menu options.
** Parameters: none.
** Pre-Conditions: none
** Post-Conditions: The contents of the menuOptions stringstream have been 
** converted to a string and returned to the calling function.
*******************************************************************************/

std::string Room::displayMenu() 
{ 
	return menuOptions.str(); 
}

/**************************
** USER INPUT
***************************/

/******************************************************************************
** Function: inputMenuChoice()
** Description: Displays the menu for the Room object and allows the user to
** select a menu choice. 
** Parameters: none.
** Pre-Conditions: none.
** Post-Conditions: The results of a Room menu choice have been returned to the
** calling function.
*******************************************************************************/

char Room::inputMenuChoice()
{	
	std::string choiceString;
	std::cout << displayMenu();
	std::cout << "What would you like to do? ";

	std::getline(std::cin, choiceString);

	while(!isValidMenuChoice(choiceString)) {
		std::cout << "You can't do that. Try something else: ";
		std::getline(std::cin, choiceString);
	}

	return toupper( choiceString.at(0) );
}

/******************************************************************************
** Function: inputMoveDir()
** Description: Displays the available move directions and allows the user to 
** select an appropriate direction.
** Parameters: none.
** Pre-Conditions: none.
** Post-Conditions: The results of a Room move choice have been returned to the
** calling function.
*******************************************************************************/

char Room::inputMoveDir()
{	
	std::string moveString;

	std::cout << displayMoveDirections();
	std::cout << "Enter a move direction: ";

	std::getline(std::cin, moveString);	//get user input

	while(!isValidDirection(moveString)) {	//validate input before returning
		std::cout << "Not a valid direction. Enter a move direction: ";
		std::getline(std::cin, moveString);
	}

	return toupper ( moveString[0] );
}

/******************************************************************************
** Function: inputRemoveItem()
** Description: Displays a list of possible items that the user can remove and
** allows the user to enter an appropriate item ID corresponding to the item
** that they wish to remove from their inventory.
** Parameters: none.
** Pre-Conditions: none.
** Post-Conditions: a string corresponding to the ID of the item that the user
** wishes to remove has been returned from the function.
*******************************************************************************/

std::string Room::inputRemoveItem()
{
	std::string itemKey;
	std::cout << nigel->displayItems();	

	std::cout << "Enter the ID of the item you'd like to remove: ";
	std::getline(std::cin, itemKey); 

	return itemKey;
}

/******************************************************************************
** Function: inputAddItem()
** Description: Displays a list of possible items that the user can add to their
** character's inventory and allows the user to enter an appropriate item ID
** corresponding to the item that they wish to add to their inventory.
** Parameters: none.
** Pre-Conditions: none.
** Post-Conditions: A string corresponding to the ID of the item that the user
** wishes to add has been returned from the function.
*******************************************************************************/

std::string Room::inputAddItem()
{
	std::string itemKey;
	std::cout << this->displayRoomItems();

	std::cout << "Enter the ID of the item you'd like to add: ";
	std::getline(std::cin, itemKey);	

	return itemKey;
}

/**************************
** INPUT VALIDATION
***************************/

/******************************************************************************
** Function: isValidChar()
** Description: isValidChar() is a function that returns true if the user's
** choice is a single character.
** Parameters: stringIn, a string that represents a user's single-character entry.
** Pre-Conditions: stringIn should be a valid string.
** Post-Conditions: returns true if the user's choice is a single character,
** false if not.
*******************************************************************************/

bool Room::isValidChar(std::string stringIn)
{
	bool valid = true;

	if(stringIn.empty() || stringIn.length() > 1)
		valid = false;
		
	return valid;
}

/******************************************************************************
** Function: isValidMenuChoice()
** Description: isValidMenuChoice() is a function that returns true if the string
** passed to it is in the validChoices vector.
** Parameters: stringIn, a string representing a user's input corresponding to a
** menu choice.
** Pre-Conditions: stringIn should be a valid string.
** Post-Conditions: If stringIn is a single character that is also in 
** the validChoices vector, the function returns true. Otherwise, it returns 
** false.
*******************************************************************************/

bool Room::isValidMenuChoice(std::string stringIn)
{
	bool valid = false;

	if (isValidChar(stringIn)) {
		for(unsigned int i = 0; i < validChoices.size(); i++) {

			if(validChoices[i] == toupper( stringIn[0]) ) {
				valid = true;
				return valid;
			}
		}
	}

	return valid;
}

/******************************************************************************
** Function: isValidDirection()
** Description: isValidDirection() is a function that returns true if the string
** passed to it corresponds to a valid move direction.
** Parameters: stringIn, a string representing a user's input corresponding to a
** desired move direction.
** Pre-Conditions: stringIn should be a valid string.
** Post-Conditions: If the parameter is a valid character that corresponds to a 
** move direction for which the matching pointer is not NULL, the function 
** returns true. Otherwise, it returns false.
*******************************************************************************/

bool Room::isValidDirection(std::string stringIn)
{	
	char moveDir = '\0';
	bool valid = false;

	if(isValidChar(stringIn)) 
		moveDir = toupper( stringIn.at(0) );

	/* match input to the correct pointer, then evaluate */
	if(moveDir == 'N' && north != NULL)
		valid = true;
	
	else if(moveDir == 'S' && south != NULL)
		valid = true;

	else if(moveDir == 'E' && east != NULL)
		valid = true;

	else if(moveDir == 'W' && west != NULL)
		valid = true;

	else if(moveDir == 'U' && up != NULL)
		valid = true;

	else if(moveDir == 'D' && up != NULL)
		valid = true;

	return valid;
}

/**************************
** PUBLIC FUNCTIONS
***************************/

/******************************************************************************
** Function: move()
** Description: Takes user input regarding a move direction, and returns a pointer 
** to the room the user wishes to move into. Moves the object's Hero pointer into
** the new space. 
** Parameters: none.
** Pre-Conditions: There should be at least one way out of the room.
** Post-Conditions: The a pointer to the Room's Hero object has been moved into 
** the next room, and a pointer to the next room has been returned to the calling 
** function. The current Room's Hero pointer has been set to NULL.
*******************************************************************************/

Room *Room::move()
{	
	Room *nextRoom = NULL;	//the room we're moving to

	char moveDir = this->inputMoveDir();	/* first, get a correct move dir */

	/* then, assign nextRoom to the corresponding directional pointer */
	if(moveDir == 'N')
		nextRoom = this->north;
	
	else if(moveDir == 'S')
		nextRoom = this->south;
	
	else if(moveDir == 'E')
		nextRoom = this->east;
	
	else if(moveDir == 'W')
		nextRoom = this->west;

	else if(moveDir == 'U')
		nextRoom = this->up;

	else if(moveDir == 'D')
		nextRoom = this->down;

	nextRoom->placeHero(this->nigel);		//move the hero,
	this->nigel = NULL;						//and set current hero to NULL

	return nextRoom;						//return the new room
}

/*******************************************************************************
** Function: placeHero()
** Description: Places a Hero object into the current room.
** Parameters:  Hero *occupant, the Hero pointer to add into the Room object.
** Pre-Conditions: occupant should be initialized. 
** Post-Conditions: the current room's Hero pointer variable has been set to 
** the value of the occupant parameter.
*******************************************************************************/

void Room::placeHero(Hero *occupant)
{
	this->nigel = occupant;
}

/*******************************************************************************
** Function: connect()
** Description: "Links" a Room object to other room objects in our game structure.
** Parameters: northIn, southIn, eastIn, westIn, upIn, downIn - all pointers to
** Room objects.
** Pre-Conditions: Room pointers should either be NULL or point to a derived
** Room object.
** Post-Conditions: The Room object's directional pointers (north, south...)
** have been set to the values of the corresponding function parameter.
*******************************************************************************/

void Room::connect(Room *northIn, Room *southIn, Room *eastIn, Room *westIn,
					Room *upIn, Room *downIn)
{
	this->north = northIn;
	this->south = southIn;
	this->east = eastIn;
	this->west = westIn;
	this->up = upIn;
	this->down = downIn;
}

/* "getters" */
std::string Room::getID() { return this->roomID; }
Room *&Room::getNorth() { return this->north; }
Room *&Room::getSouth() { return this->south; }
Room *&Room::getEast() { return this->east; }
Room *&Room::getWest() { return this->west; }
Room *&Room::getUp() { return this->up; }
Room *&Room::getDown() { return this->down; }