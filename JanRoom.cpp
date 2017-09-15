/******************************************************************************
** Program Filename: JanRoom.cpp
** Author: Colin Powell
** Date: 8/4/16
** Description: Final Project - JanRoom derived class implementation file
** Input: User selection of menu options relating to specific room actions.
** Output: Menu-based interface, output to console.
*******************************************************************************/

#include "JanRoom.hpp"

/******************************************************************************
** Function: JanRoom()
** Description: JanRoom class default constructor
** Parameters: idIn, the room's unique ID. 
** Pre-Conditions: There should be an object named "SAN" somewhere in the game,
** representing a sandwich. There should NOT be another object in the game named
** "KEY".
** Post-Conditions: An instance of the LoadingDock class has been created.
*******************************************************************************/

JanRoom::JanRoom(std::string idIn) : Room(idIn)
{
	validChoices.push_back('G');	
	menuOptions << "G: Give the Janitor something to eat." << std::endl;

	roomDescription << 
	"You stumble into a small storage room. A few dim lightbulbs\n"
	"light shelves full of cleaning supplies. A vacuum cleaner leans against\n"
	"the wall to your left. A janitor sits at a small card table in the center\n"
	"of the room. He seems to be miffed about something. \"Can't believe I \n"
	"forgot my dinner. Now what am I gonna do?\" You ask him how to get to the stage:\n"
	"\"Yeah, uh, I think that you can get there through the boiler room. There's\n" 
	"a lift to the stage that the maintenance staff uses sometimes. You'd need\"\n"
	"a key to get in, though - wish I could remember where I left mine. Man,\n"
	"I'm hungry\"\n";

	this->givenSandwich = false;

	roomItems.push_back(new Item("A bottle of cleaning solution", "BOT"));

}

/******************************************************************************
** Function: specialAction()
** Description: JanRoom derived class specialAction function. Allows the user
** to exchange a sandwich for the boiler room key. 
** Parameters: none.
** Pre-Conditions: none.
** Post-Conditions: If the Hero object has an item with ID "SAN", the function
** deletes that object and adds an object named "KEY" to the roomItems vector.
*******************************************************************************/

std::string JanRoom::specialAction()
{
	std::ostringstream janNarr;

	if(nigel->hasItem("SAN")) {
		
		janNarr << 
		"The janitor considers your tiny sandwich. \"Hey, wow, thanks! You guys\n"
		"aren't so bad after all.\" He rises from the table to take your sandwich,\n"
		"and a key falls out of his pants pocket. He places it on the table\n"
		"\"Ah, there it is! You can take it if you want.\"\n";

		/* drop and remove the Hero's sandwich object */
		givenSandwich = true;
		Item *sandwich = nigel->drop("SAN");
		delete sandwich;

		/* add a key to the room */
		roomItems.push_back(new Item("The boiler room key", "KEY"));

		roomDescription.str("");	//clear stringstream
		roomDescription << 			//modify room description
		"You stumble into a small storage room. A single incandescent bulb\n"
		"lights shelves full of cleaning supplies. A vacuum cleaner leans against\n"
		"the wall to your left. A janitor sits at a small card table in the center\n"
		"of the room. He's munching happily on a tiny sandwich.\n";
	}

	else if(givenSandwich) {
		janNarr << 
		"He already has a sandwich! You don't have time to go around giving away\n"
		"sandwiches to everyone you meet, do you?\n";
	}
	else {
		janNarr << 
		"What are you going to give him to eat? You think that he might like\n"
		"one of those tiny sandwiches. Maybe he can figure out how to eat them.\n";
	}

	return janNarr.str();
}

/******************************************************************************
** Function: interact()
** Description: interact() function for the JanRoom class. Allows the user the
** basic set of actions along with an option for giving the room's occupant
** something to eat. 
** Parameters: none.
** Pre-Conditions: none.
** Post-Conditions: The function has returned the state of the acquiredKey 
** member variable.
*******************************************************************************/

bool JanRoom::interact()
{
	char userChoice = '\0';

	std::cout << this->lookAround();

	do {

		userChoice = this->inputMenuChoice();

		if(userChoice == 'H')		//give a hint
			std::cout << std::endl << this->giveHint();

		else if(userChoice == 'L')	//look around
			std::cout << std::endl << this->lookAround();

		else if(userChoice == 'I') //check inventory
			std::cout << std::endl << nigel->displayItems();
	
		else if(userChoice == 'D') //drop something
			std::cout << std::endl << this->takeFromHero();

		else if(userChoice == 'P') //pick something up
			std::cout << std::endl << this->giveToHero();

		else if(userChoice == 'G')	//give the janitor a sandwich
			std::cout << std::endl << this->specialAction();

		std::cout << std::endl;

	} while(userChoice != 'M'); 

	return this->givenSandwich;
}