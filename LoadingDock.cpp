/******************************************************************************
** Program Filename: LoadingDock.cpp
** Author: Colin Powell
** Date: 8/4/16
** Description: Final Project - LoadingDock derived class implementation file
** Input: User selection of menu options relating to specific room actions.
** Output: Menu-based interface, output to console.
*******************************************************************************/

#include "LoadingDock.hpp"

/******************************************************************************
** Function: LoadingDock()
** Description: LoadingDock class default constructor
** Parameters: idIn, the room's unique ID. 
** Pre-Conditions: none
** Post-Conditions: An instance of the LoadingDock class has been created.
*******************************************************************************/

LoadingDock::LoadingDock(std::string idIn) : Room(idIn)
{
	validChoices.push_back('G');	
	menuOptions << "G: Grab a Roadie to carry your stuff. Lazy buggers..." << std::endl;

	roomDescription << 
	"You step outside onto the loading dock. A large trailer is parked\n"
	"against the concrete platform - you peek inside to see several boxes stuffed\n"
	"with your new album \"Smell The Glove\". A few roadie types are chatting over\n"
	"by the dumpsters to your right\n";

	this->obtainedRoadie = false;

	roomItems.push_back(new Item("your new album, \"Smell the Glove\"", "ALB"));
}

/******************************************************************************
** Function: specialAction()
** Description: LoadingDock derived class specialAction function. Allows the 
** character to collect a roadie named Bob, which allows the character to carry
** items. 
** Parameters: none.
** Pre-Conditions: none.
** Post-Conditions: If the Hero object's hasRoadie() function returns false, the
** function calls that object's recruitRoadie() function, which allows it the
** ability to store Items. A string is returned describing the results of a 
** successful or failed action.
*******************************************************************************/

std::string LoadingDock::specialAction()
{
	std::ostringstream roadieNarr;

	if(nigel->hasRoadie()) {
		roadieNarr << "You've already got Bob, right? Don't want to be, \n"
		"like, selfish or something.\n";
	}
	else {
		roadieNarr << 
		"You see Bob the Roadie smoking a cigarette over by the trucks.\n" 
		"\"Oi, Bob, come help us carry something? It's like, between\n" 
		"these costumes, you know, and our guitars...We can't, like, tote anything\n" 
		"around.\" Bob the Roadie puts out his cigarette. \"Uh, yeah, fine, whatever\n" 
		"you need.\"\n\n";

		roadieNarr << 
		"Bob looks like a bit of wanker, but he does carry your \n"
		"stuff for a living. Being in a rock band has its perks.\n"; 

		nigel->recruitRoadie();
		this->obtainedRoadie = true;
	}

	return roadieNarr.str();
}

/******************************************************************************
** Function: interact()
** Description: interact() function for the LoadingDock class. Allows the user
** the basic set of actions along with an option for adding a roadie to the 
** user's entourage - allowing the user to carry items from room to room.
** Parameters: none.
** Pre-Conditions: none.
** Post-Conditions: The function has returned the state of its obtainedRoadie
** member variable.
*******************************************************************************/

bool LoadingDock::interact()
{
	char userChoice = '\0';
	this->obtainedRoadie = false;

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

		else if(userChoice == 'G')
			std::cout << std::endl << this->specialAction();

		std::cout << std::endl;

	} while(userChoice != 'M');

//	 && userChoice != 'Q'); 

	return this->obtainedRoadie;

}

 //	if(userChoice == 'Q')
//		return false;
//	else 
//		return true;

//	if(userChoice == 'M') 
//		nextRoom = move();
//	else 
//		nextRoom = NULL;

//	return nextRoom;