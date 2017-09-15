/******************************************************************************
** Program Filename: Catwalk.cpp
** Author: Colin Powell
** Date: 8/4/16
** Description: Final Project - Catwalk derived class implementation file
** Input: User selection of menu options relating to specific room actions.
** Output: Menu-based interface, output to console.
*******************************************************************************/

#include "Catwalk.hpp"

/******************************************************************************
** Function: Catwalk()
** Description: Catwalk class default constructor
** Parameters: idIn, the room's unique ID. 
** Pre-Conditions: none
** Post-Conditions: An instance of the Catwalk class has been created.
*******************************************************************************/

Catwalk::Catwalk(std::string idIn) : Room(idIn)
{
	validChoices.push_back('O');	
	menuOptions << "O: Operate winch, lower the stonehenge onto the stage." << std::endl;

	revisited = false;
	stonehengeLowered = false;

	roomDescription << 
	"The lift has skipped its stop on the stage and has taken you to the catwalk\n"
	"far above the stage floor. You can see the catwalk extend to the corners\n"
	"of the stage, although to the east appears to be some sort of control room\n"
	"You look down (wayyyy down) and see all of your beautiful customized amps\n"
	"and speakers arrayed in front of the crowd. They continue to chant: \"TAP!\n"
	"TAP! TAP!\", although you can tell that their enthusiasm is waning. In front\n"
	"of you, hanging from a winch, is a tiny stonehenge monument. There's a toolbox\n"
	"next to the winch that the stage techs must have been using to hang the henge.\n"
	"But, like, what is this tiny thing? Is this the model for the bigger stonehenge\n" 
	"that you asked for? What's this doing up here?\n";

	roomItems.push_back(new Item("A screwdriver", "SCREW"));
	roomItems.push_back(new Item("Another one of those stonehenge monuments", "MON"));
}

/******************************************************************************
** Function: specialAction()
** Description: Catwalk derived class SpecialAction function. Allows the character
** to lower a winch containing a miniature stone henge onto the stage floor.
** Parameters: none.
** Pre-Conditions: none.
** Post-Conditions: If stonehengeLowered is false, it is set to true and the 
** crowdDistracted variable is set to true. A string is returned describing the
** result of the activity.
*******************************************************************************/

std::string Catwalk::specialAction()
{
	std::ostringstream catwalkNarr;

	if( !stonehengeLowered ) {

		stonehengeLowered = true;
		crowdDistracted = true;

		catwalkNarr << 
		"You lower the tiny stonehenge down onto the stage, and the crowd roars\n"
		"with delight - they must think that the show is about to start.\n"
		"Well, I mean, hopefully it IS, right? This should buy you some time.\n";
	}

	else {
		catwalkNarr << 
		"The henge has already been lowered onto the stage. Looks ridiculous\n"
		"down there, doesn't it?\n";
	}

	return catwalkNarr.str();
}

/******************************************************************************
** Function: updateDescription()
** Description: Updates the room's description once the room's lift disappears
** to the floors below.
** Parameters: none.
** Pre-Conditions: none.
** Post-Conditions: Updates the room's roomDescription variable to a more succint
** string.
*******************************************************************************/

void Catwalk::updateDescription()
{
	//edit the room's description so that the lift isn't mentioned on the next visit
	this->roomDescription.str("");	//clear it first
	this->roomDescription << 
	"You're on the main catwalk. You look down (wayyyy down)\n"
	"and see all of your beautiful customized amps and speakers arrayed in front\n"
	"of the crowd. They continue to chant: \"TAP! TAP! TAP!\", although you can\n"
	"tell that their enthusiasm is waning. In front of you, hanging from a winch, is\n"
	"a tiny stonehenge monument. Is this, like, the model for the bigger stonehenge\n"
	"that you asked for? What's this doing up here?\n";
}

/******************************************************************************
** Function: interact()
** Description: Catwalk derived class interact() function. Allows the user the
** basic set of actions along with an option for operating the room's winch, which
** adds some 'time' back onto the clock.
** Parameters: none. 
** Pre-Conditions: none.
** Post-Conditions: if the stonehengeLowered member variable has been set to true, 
** crowdDistracted will always return false - can only activate this special
** feature once in the game.
*******************************************************************************/

bool Catwalk::interact()
{
	char userChoice = '\0';

	std::cout << this->lookAround();
	crowdDistracted = false;	//reset so this can't be triggered again.

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

		else if(userChoice == 'O') {
			std::cout << std::endl << this->specialAction();
		}

		else if(userChoice == 'M' && revisited == false) {
			std::cout << std::endl << 
			"As you consider where to go, the lift gives out a pathetic\n"
			"squeak and slowly lowers back down into the bowels of the theater.\n"
			"It doesn't respond to the call button. Bugger. Are you really stuck\n"
			"up here?" << std::endl;
		}

		std::cout << std::endl;

	} while(userChoice != 'M'); 

	if(revisited == false) {
		updateDescription();
		revisited = true;
	}

	return crowdDistracted;
}