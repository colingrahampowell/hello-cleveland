/******************************************************************************
** Program Filename: GreenRoom.cpp
** Author: Colin Powell
** Date: 8/4/16
** Description: Final Project - GreenRoom derived class implementation file
** Input: User selection of menu options relating to specific room actions.
** Output: Menu-based interface, output to console.
*******************************************************************************/

#include "GreenRoom.hpp"

/******************************************************************************
** Function: GreenRoom()
** Description: GreenRoom class default constructor
** Parameters: idIn, the room's unique ID. 
** Pre-Conditions: none
** Post-Conditions: An instance of the GreenRoom class has been created.
*******************************************************************************/

GreenRoom::GreenRoom(std::string idIn) : Room(idIn)
{
	validChoices.push_back('T');	
	menuOptions << "T: Try to open the boiler room door. " << std::endl;

	this->roomDescription << 
	"This is the green room. The concrete walls are painted a dour shade of beige\n" 
	"not made cheerier by the stark fluorescent light. Your manager, Ian, is sitting\n"
	"on the worn sofa talking to your girlfriend Jeanine. Should be out selling\n"
	"your new album, that\'s what he SHOULD be doing. To your left is a sandwich\n"
	"tray containing those useless little pieces of bread. Over the intercom,\n"
	"you hear a loud, garbled crackling noise - sounds like the stage manager is\n"
	"trying to reach you. To the north is some sort of storage room; to the south,\n"
	"the dressing room. The loading dock is to the west. Up the stairs, the stage door\n"
	"is most definitely locked, and none of your most vocal protestations can open\n"
	"it. To the east, you see a substantial-looking door marked BOILER ROOM. \n"; 

	this->doorUnlocked = false;

	roomItems.push_back(new Item("a tiny sandwich", "SAN"));
}

/******************************************************************************
** Function: specialAction()
** Description: GreenRoom derived class specialAction function. Allows the 
** character to open the door to the boiler room and advance the game.
** Pre-Conditions: none.
** Post-Conditions: If the Hero object has an Item in its container named "KEY",
** that item has been removed and doorUnlocked has been set to TRUE.
*******************************************************************************/

std::string GreenRoom::specialAction()
{
	std::ostringstream actionNarr;

	if(nigel->hasItem("KEY")) {	//used to open the boiler room door
		Item *key = nigel->drop("KEY");
		delete key;

		doorUnlocked = true;

		actionNarr <<
		"You put the key into the door's lock and turn the handle - this time,\n"
		"it opens! A musty smell wafts from the opened door.\n";
	}

	else if ( doorUnlocked ) {
		actionNarr << 
		"You turn the key in the lock again. The door is still open...\n";
	}

	else {
		actionNarr << 
		"The door is locked. You try to force it open, but it doesn't budge.\n";
	}

	return actionNarr.str();
}

/******************************************************************************
** Function: interact()
** Description: interact() function for the GreenRoom class. Allows the user 
** the basic set of actions along with an option for talking into the room's 
** intercom.
** Parameters: none. 
** Pre-Conditions: none.
** Post-Conditions: The function has returned the state of the talkedIntoIntercom
** parameter to the calling function.
*******************************************************************************/

bool GreenRoom::interact()
{
	char userChoice = '\0';
	std::cout << this->lookAround();

	do {

		userChoice = this->inputMenuChoice();

		if(userChoice == 'H')	//hint
			std::cout << std::endl << this->giveHint();

		else if(userChoice == 'L')	//look around
			std::cout << std::endl << this->lookAround();

		else if(userChoice == 'I') 	//inventory
			std::cout << std::endl << nigel->displayItems();
	
		else if(userChoice == 'D') 	//drop an item
			std::cout << std::endl << this->takeFromHero();

		else if(userChoice == 'P') 	//pick an item up
			std::cout << std::endl << this->giveToHero();

		else if(userChoice == 'T')	//try to open the boiler room door
			std::cout << std::endl << this->specialAction();

		std::cout << std::endl;

	} while(userChoice != 'M');

	return doorUnlocked;
}