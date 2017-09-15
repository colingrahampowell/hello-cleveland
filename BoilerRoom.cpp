/******************************************************************************
** Program Filename: BoilerRoom.cpp
** Author: Colin Powell
** Date: 8/4/16
** Description: Final Project - BoilerRoom derived class implementation file
** Input: User selection of menu options relating to specific room actions.
** Output: Menu-based interface, output to console.
*******************************************************************************/

#include "BoilerRoom.hpp"

/******************************************************************************
** Function: BoilerRoom()
** Description: BoilerRoom class default constructor
** Parameters: idIn, the room's unique ID. Hero *occupant, the room's current 
** occupant.
** Pre-Conditions: none
** Post-Conditions: An instance of the LoadingDock class has been created.
*******************************************************************************/

BoilerRoom::BoilerRoom(std::string idIn) : Room(idIn)
{
	validChoices.push_back('T');	
	menuOptions << "T: Try coaxing the lift into operation" << std::endl;

	liftActive = false;

	roomDescription << 
	"You open a heavy door, turn on the light, and look around. This is no\n"
	"place for a rock star of your caliber. A furnace, caked in soot, dominates\n"
	"the dark room, as rats scurry out of the weak beam of light cast by the single\n"
	"exposed bulb. You look to your right and see a collection of tools marked\n"
	"\"XANADU STAR MAINTENANCE\".\" In the corner of the room is a forlorn hydraulic\n"
	"lift. What are we doing in here, again?\" says David, the guitarist.\n" 
	"\"Like, where's the stage, Nigel? This is getting old.\"\n\n"
	"As you get your bearings, you hear the door clang shut behind you. You turn,\n"
	"and hear muffled voices on the other side of the door - \"Hey, Barry, check\n"
	"this out- looks like someone left the key in the lock. Must have been one of\n"
	"those maintenance guys. Never pick up after themselves. Well, at least they\n"
	"You hear the quiet click of the door being locked. You try shouting, but\n"
	"there is no response.\n";

	roomItems.push_back(new Item("An oil can", "OIL"));
	roomItems.push_back(new Item("A paint brush", "BRUSH"));
	roomItems.push_back(new Item("A length of rope", "ROPE"));
}

/******************************************************************************
** Function: specialAction()
** Description: BoilerRoom derived class specialAction function. Allows the user
** to apply a can of oil to the room's hydraulic lift to try and get it working.
** Parameters: none.
** Pre-Conditions: The Hero object should have a chance to acquire an Item named
** OIL before or during occupancy of this space. 
** Post-Conditions: If the Hero object has an Item named "OIL", the function
** sets the liftActive member variable to true and removed the oil from the Hero's
** inventory. A string is returned describing the results.
*******************************************************************************/

std::string BoilerRoom::specialAction()
{
	std::ostringstream boilerNarr;

	if( nigel->hasItem("OIL")) {
		this->liftActive = true;	//activate the lift

		boilerNarr << 
		"You apply the oil to important-looking parts of the lift's motor.\n"
		"This time, when you push the UP button, the lift reluctantly groans.\n"
		"to life.\n";

		/* drop the oil, and remove it */
		Item *oil = nigel->drop("OIL");
		delete oil;
	}

	else if ( liftActive ) {
		boilerNarr << 
		"The lift appears to be working, but it sure isn't happy about it.\n";
	}

	else {
		boilerNarr << 
		"You push the UP button on the wall next to the lift, at which point\n"
		"the lift's motor emits a horrible grinding noise and refuses to budge.\n";
	}	

	return boilerNarr.str();
}

/******************************************************************************
** Function: updateDescription()
** Description: Updates the room's description once the Hero object is "locked
** in" to the space.
** Parameters: none.
** Pre-Conditions: none.
** Post-Conditions: Updates the room's roomDescription variable to a more succint
** string.
*******************************************************************************/

void BoilerRoom::updateDescription()
{
	//edit the room's description so that the lift isn't mentioned on the next visit
	this->roomDescription.str("");	//clear it first
	this->roomDescription <<  
	"This is no place for a rock star of your caliber.\n"
	"A furnace, caked in soot, dominates the dark room, as rats scurry out of the\n" 
	"weak beam of light cast by the single exposed bulb. You look to your right\"\n" 
	"and see a collection of tools marked \"XANADU STAR MAINTENANCE\". In the\n"
	"corner of the room is a forlorn hydraulic lift.\n";
	
}

/******************************************************************************
** Function: interact()
** Description: BoilerRoom derived class interact() function. Allows the user the
** basic set of actions along with an option for working on the room's hydraulic
** lift.
** Parameters: none. 
** Pre-Conditions: none.
** Post-Conditions: liftActive must be true for the function to return. It returns
** the value of liftActive to the caller.
*******************************************************************************/

bool BoilerRoom::interact()
{
	char userChoice = '\0';

	std::cout << this->lookAround();

	do {

		userChoice = this->inputMenuChoice();

		if(userChoice == 'H')
			std::cout << std::endl << this->giveHint();

		else if(userChoice == 'L') {
			updateDescription();
			std::cout << std::endl << this->lookAround();
		}

		else if(userChoice == 'I') 
			std::cout << std::endl << nigel->displayItems();
	
		else if(userChoice == 'D') 
			std::cout << std::endl << this->takeFromHero();

		else if(userChoice == 'P') 
			std::cout << std::endl << this->giveToHero();

		else if(userChoice == 'T')
			std::cout << std::endl << this->specialAction();

		else if(userChoice == 'M') {
			if(!liftActive) {
				std::cout << std::endl;
				std::cout << "The lift seems to be the only way out of here...";
				std::cout << "if only it were working.";
				std::cout << std::endl;
			}
		}

		std::cout << std::endl;

	} while((userChoice != 'M') || (!liftActive)); 

	return liftActive;
}