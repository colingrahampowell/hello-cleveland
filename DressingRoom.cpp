/******************************************************************************
** Program Filename: DressingRoom.cpp
** Author: Colin Powell
** Date: 8/4/16
** Description: Final Project - DressingRoom derived class implementation file
** Input: User selection of menu options relating to specific room actions.
** Output: Menu-based interface, output to console.
*******************************************************************************/

#include "DressingRoom.hpp"

/******************************************************************************
** Function: DressingRoom()
** Description: DressingRoom class default constructor
** Parameters: idIn, the room's unique ID. 
** Pre-Conditions: none
** Post-Conditions: An instance of the DressingRoom class has been created.
*******************************************************************************/

DressingRoom::DressingRoom(std::string idIn) : Room(idIn)
{
	validChoices.push_back('C');	
	menuOptions << "C: Check yourself in the mirror." << std::endl;

	mirrorChecked = false;

	roomDescription << 
	"This is the dressing room. A row of mirrors lines the south wall.\n"
	"Your outfits have been carefully arranged for the mid-set costume change\n"
	"A few of the makeup artists are having a chat over in the corner.\n";

	roomItems.push_back(new Item("One of your costumes", "COST"));
}

/******************************************************************************
** Function: specialAction()
** Description: DressingRoom derived class specialAction function. Allows the 
** user to examine themselves in the mirror, which produces a hint (and a gentle
** prod to hurry up.
** Parameters: none.
** Pre-Conditions: none.
** Post-Conditions: If the mirrorCheckced variable is false, the function sets it to
** true and returns a hint in string form. Otherwise, it returns a shorter string.
*******************************************************************************/

std::string DressingRoom::specialAction()
{
	std::ostringstream dressNarr;

	if( !mirrorChecked ) {
		mirrorChecked = true;

		dressNarr << 
		"As you primp in the mirror, your manager Ian shouts from the green room:\n"
		"\"Uh. lads? It's time to get going, okay? Did you talk to the janitor?\n"
		"He might know how to get to the stage.\"\n";
	}

	else {
		dressNarr << 
		"You've already looked at yourself in the mirror. You look fine.\n";
	}

	return dressNarr.str();
}

/******************************************************************************
** Function: interact()
** Description: interact() function for the DressingRoom class. Allows the user
** the basic set of actions along with an option for checking themselves in the
** mirror.
** Parameters: none. 
** Pre-Conditions: none.
** Post-Conditions: The function has returned the state of the mirrorChecked
** member variable.
*******************************************************************************/

bool DressingRoom::interact()
{
	char userChoice = '\0';

	std::cout << this->lookAround();

	do {

		userChoice = this->inputMenuChoice();

		if(userChoice == 'H')
			std::cout << std::endl << this->giveHint();

		else if(userChoice == 'L')
			std::cout << std::endl << this->lookAround();

		else if(userChoice == 'I') 
			std::cout << std::endl << nigel->displayItems();
	
		else if(userChoice == 'D') 
			std::cout << std::endl << this->takeFromHero();

		else if(userChoice == 'P') 
			std::cout << std::endl << this->giveToHero();

		else if(userChoice == 'C')
			std::cout << std::endl << this->specialAction();

		std::cout << std::endl;

	} while(userChoice != 'M'); 

	return mirrorChecked;
}