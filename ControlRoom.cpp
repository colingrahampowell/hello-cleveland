/******************************************************************************
** Program Filename: ControlRoom.cpp
** Author: Colin Powell
** Date: 8/4/16
** Description: Final Project - ControlRoom derived class implementation file
** Input: User selection of menu options relating to specific room actions.
** Output: Menu-based interface, output to console.
*******************************************************************************/

#include "ControlRoom.hpp"

/******************************************************************************
** Function: ControlRoom()
** Description: ControlRoom class default constructor
** Parameters: idIn, the room's unique ID. 
** Pre-Conditions: none
** Post-Conditions: An instance of the ControlRoom class has been created.
*******************************************************************************/

ControlRoom::ControlRoom(std::string idIn) : Room(idIn)
{
	validChoices.push_back('T');	
	menuOptions << "T: Talk over the intercom" << std::endl;

	talked = false;

	roomDescription << 
	"This appears to be some sort of control room for the rigging above the\n"
	"stage. A series of knobs and dials cover the western wall, with a series of\n"
	"arcane labels: LOW WIN 1, LOW WIN 2, INTERCOM...\n"
	"You hear a dim crackling coming through the speakers.\n";

}

/******************************************************************************
** Function: specialAction()
** Description: ControlRoom specialAction() function. Allows the user to contact
** the stage manager via the intercom and activate the second stage lift.
** Parameters: none.
** Pre-Conditions: There should be an Item named "SCREW" somewhere in the game.
** Post-Conditions: If the Hero object has an item named "SCREW", the function
** has set the talked member variable to true. The function has returned a 
** string describing the result.
*******************************************************************************/

std::string ControlRoom::specialAction()
{
	std::ostringstream controlNarr;

	/* if we can fix the broken intercom with our trusty screwdriver */
	if( !talked && nigel->hasItem("SCREW") ) {

		controlNarr << 
		"You tighten the intercom's contacts with your screwdriver and the crackling\n" 
		"turns into a loud roar: \"WHERE the HELL is SPINAL TAP? Has anyone seen those\n"
		"guys? Dammit, we're running way behind schedule here.\"\n"
		"You pipe up: \"Uh, hello? Yes, this is Nigel, uh, with the band, you know\n"
		"We seem to be stuck above the stage, don't we? Intercom was broken backstage,\n"
		"so...\" There's a long pause, followed by another long string of expletives.\n"
		"When you're finally able to explain yourselves (in your own way), the\n"
		"voice on the other end bellows: \" Well, uh, okay, look: there's a lift\n"
		"on the other end of the catwalk. No, not the one that isn't working. Take\n"
		"that and you're home free.\n";

		talked = true;
	}

	else if(!talked) {	//non-functional intercom
		controlNarr << 
		"You push the TALK button on the intercom, but a screw appears to be loose\n"
		"on the control panel. You can't hold the pieces together long enough to\n"
		"make any sense of what is being said.\n";
	}

	else {
		controlNarr << 
		"You've already talked to the stage manager. Better to not bother him again\n"
		"unless you really need something.\n";
	}

	return controlNarr.str();
}

/******************************************************************************
** Function: interact()
** Description: ControlRoom derived class interact() function. Allows the user the basic
** set of actions along with an option for fixing the intercom and attempting to
** contact the stage manager.
** Parameters: none.
** Pre-Conditions: none.
** Post-Conditions: If the talked member variable is true, the function has
** returned true. 
*******************************************************************************/

bool ControlRoom::interact()
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

		else if(userChoice == 'T')
			std::cout << std::endl << this->specialAction();

		std::cout << std::endl;

	} while(userChoice != 'M'); 

	return talked;
}