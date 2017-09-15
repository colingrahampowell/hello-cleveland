/******************************************************************************
** Program Filename: FlySpace.cpp
** Author: Colin Powell
** Date: 8/4/16
** Description: Final Project - FlySpace derived class implementation file
** Input: N/A
** Output: N/A
*******************************************************************************/

#include "FlySpace.hpp"

/******************************************************************************
** Function: FlySpace()
** Description: FlySpace class default constructor
** Parameters: idIn, the room's unique ID. 
** Pre-Conditions: There should be an object named "ROPE" somewhere in the game
** environment.
** Post-Conditions: An instance of the FlySpace class has been created.
*******************************************************************************/

FlySpace::FlySpace(std::string idIn) : Room(idIn)
{
	validChoices.push_back('S');	
	menuOptions << "S: Lower yourself down to the stage. Very Risky!" << std::endl;

	jumped = false;

	roomDescription << 
	"You're in one of the wings of the flyspace above the stage, at the far edge\n"
	"of the catwalk. The drop below is still precipitous, and the crowd is still\n"
	"getting restless.\n";
}

/******************************************************************************
** Function: specialAction()
** Description: FlySpace specialAction() function. Allows the user to "jump"
** onto the stage, provided they have a rope. 
** Parameters: none.
** Pre-Conditions: There is an item named "ROPE" in the game environment. 
** Post-Conditions: If the character has a rope, the function sets the value of
** the jumped member variable to true. It returns a string describing the results.
*******************************************************************************/

std::string FlySpace::specialAction()
{
	std::ostringstream flyspaceNarr;

	if( nigel->hasItem("ROPE") ) {

		flyspaceNarr << 
		"You tie the rope to the railing of the catwalk. The railing doesn't seem\n" 
		"particularly sturdy, but you don't have time for such details. You try\n"
		"to lower yourself onto the stage as your bandmates watch from above. Slowly, \n"
		"slowly....\n";

		jumped = true;
	}

	else {
		flyspaceNarr << 
		"The stage is too far down for you to just jump...you'll need something\n"
		"to lower yourself down with if you REALLY want to get down from here...\n";
	}

	return flyspaceNarr.str();
}

/******************************************************************************
** Function: interact()
** Description: FlySpace derived class interact() function. Allows the user the
** basic set of actions along with an option for jumping off of the catwalk.
** Parameters: none.
** Pre-Conditions: none.
** Post-Conditions: If the character has performed a successful jump (that is,
** if the value of jumped == true), the function returns true. 
*******************************************************************************/

bool FlySpace::interact()
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

		else if(userChoice == 'S')
			std::cout << std::endl << this->specialAction();

		std::cout << std::endl;

		/* if jumped, don't need to select a move option */
	} while(userChoice != 'M' && (jumped == false)); 

	return jumped;
}