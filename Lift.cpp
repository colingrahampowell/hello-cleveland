/******************************************************************************
** Program Filename: Lift.cpp
** Author: Colin Powell
** Date: 8/4/16
** Description: Final Project - Lift derived class implementation file
** Input: User selection of menu options relating to specific room actions.
** Output: Menu-based interface, output to console.
*******************************************************************************/

#include "Lift.hpp"

/******************************************************************************
** Function: Lift()
** Description: Lift class default constructor
** Parameters: idIn, the room's unique ID. 
** Pre-Conditions: none
** Post-Conditions: An instance of the Lift class has been created.
*******************************************************************************/

Lift::Lift(std::string idIn, std::string infopath) : Room(idIn, infopath)
{
	validChoices.push_back('T');	
	menuOptions << "T: Take lift down to the stage." << std::endl;

	liftTaken = false;

	roomDescription << 
	"You're greeted by a lift on this side of the catwalk. Seems that the stage\n"
	"manager came good after all. It looks much more functional than the one\n"
	"that you took to get up here.\n";
}

/******************************************************************************
** Function: specialAction()
** Description: Lift specialAction() function. Allows the user to take the lift
** down (and end the game, in this case).
** Parameters: none.
** Pre-Conditions: none.
** Post-Conditions: liftTaken is set to true, and a string is returned describing
** the results.
*******************************************************************************/

std::string Lift::specialAction()
{
	std::ostringstream liftNarr;

	liftTaken = true;

	liftNarr << 
	"You step into the lift. The caged doors close around you.\n" 
	"Inside, you see a button marked 'STAGE LEVEL'. You press it, and the \n"
	"lift starts to whirr gently down onto the wingspace of the stage. Finally.\n";

	return liftNarr.str();
}

/******************************************************************************
** Function: interact()
** Description: Lift derived class interact() function. Allows the user the basic
** set of actions along with an option for taking the lift down to the stage. 
** Parameters: none.
** Pre-Conditions: none.
** Post-Conditions: If the character has chosen to take the lift down, the function
** returns true, and liftTaken has been set to true.
*******************************************************************************/

bool Lift::interact()
{
	char userChoice = '\0';

	std::cout << this->lookAround();

	liftTaken = false;	//can only take the lift once.

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

		else if(userChoice == 'T')
			std::cout << std::endl << this->specialAction();

		std::cout << std::endl;

	/* if 'T' is selected, the game doesn't need to  continue */
	} while(userChoice != 'T' && userChoice != 'M'); 

	return liftTaken;
}
