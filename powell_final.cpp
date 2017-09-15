/******************************************************************************
** Program Filename: powell_final.cpp
** Author: Colin Powell
** Date: 8/4/16
** Description: Final Project - main()
** Input: User selection of menu options relating to specific room actions.
** Output: Menu-based interface, output to console.
*******************************************************************************/

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

#include "Room.hpp"
#include "GreenRoom.hpp"
#include "LoadingDock.hpp"
#include "JanRoom.hpp"
#include "BoilerRoom.hpp"
#include "Catwalk.hpp"
#include "DressingRoom.hpp"
#include "FlySpace.hpp"
#include "ControlRoom.hpp"
#include "Lift.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::ostringstream;

std::string displayTurnsRemaining(int);
//void createLowerLevel(Room *&, Room *&, Room *&, Room *&);
void createLowerLevel(Room *&);
void resetLowerLevel(Room *&);
void createUpperLevel(Room *&);
void resetUpperLevel(Room *&);
//void createUpperLevel(Room *&, Room *&, Room *&, Room *&, Room *&);
void clearLevel(Room *&);
void createLift(Room *&, Room *&);
bool performJump();
std::string displayTitle();

char inputBinaryChoice(char, char);

/******************************************************************************
** Function: main()
** Description: The program's main() function.
** Parameters: none.
** Pre-Conditions: none.
** Post-Conditions: A text-based adventure game has been output to the screen. 
*******************************************************************************/

int main()
{
	Hero *nigel = new Hero;		//our hero

	srand(time(0));

	bool specialAction = false;		//tracks if a room's special ability is triggered
	bool jumpedOntoStage = false;	//tracks if player has taken a shortcut
	bool tookLift = false;			//tracks if player wins the "normal" way
	bool gameEnded = false;			//tracks if player is in the last room
	int timer = 15;					//15 turns until game over

	/* lower level */
	Room *lower = new GreenRoom("Green Room");
	createLowerLevel(lower);

	/* upper level (empty for now...) */
	Room *upper = new Catwalk("Catwalk");

	/* establish starting state */
	Room *currentRoom = lower;	//set start room
	currentRoom->placeHero(nigel);
	nigel = NULL;

	/* prompt the user to start the game */
	std::cout << displayTitle();
	std::cout << "Start the game? (Y/N): ";

	char userChoice = inputBinaryChoice('Y', 'N');
	if(userChoice == 'Y') {

		std::cout << std::endl;

		do {

			std::cout << displayTurnsRemaining(timer) << std::endl << std::endl;

			specialAction = currentRoom->interact();	//tracks state of special ability
		
			/* before moving, we check the result of any special ability */
			if( specialAction ) {	
		
				if ( currentRoom->getID() == "Lift") {
					tookLift = true;	//signifies a "normal" win
					gameEnded = true;
				}

				else if ( currentRoom->getID() == "Green Room" ) {	//boiler room door unlocked
					resetLowerLevel(lower);	//add the boiler room 
				}	

				else if( currentRoom->getID() == "Boiler Room" ) {	//lift accessed
					/* allow movement to upper room */
					lower->getEast()->connect(NULL, NULL, NULL, NULL, upper, NULL);
				}

				else if( currentRoom->getID() == "Catwalk" ) 	//lowered the stonehenge
					timer += 3;	//buying extra time

				else if ( (currentRoom->getID() == "Fly Space: North")  //jumped off of the catwalk
							|| (currentRoom->getID() == "Fly Space: South")
							|| (currentRoom->getID() == "Fly Space: West")) 
				{
					jumpedOntoStage = performJump();
					gameEnded = true;
				}

				else if ( currentRoom->getID() == "Control Room" ) 	//talked to the stage mgr.
					resetUpperLevel(upper);
			}

			/* if the game should continue to another room */
			if( gameEnded == false ) {
				
				Room *newRoom = currentRoom->move();

				/* if we have just moved into the boiler room, lock the door */
				if (newRoom->getID() == "Boiler Room" 
					&& currentRoom->getID() == "Green Room") {	
					//disconnect boiler room to disallow movement elsewhere
					lower->getEast()->connect(NULL, NULL, NULL, NULL, NULL, NULL);
				}
				
				/* if the first lift was taken, disable it */
				else if ( newRoom->getID() == "Catwalk" 
							&& currentRoom->getID() == "Boiler Room" ) 
				{	
					/* delete the west flyspace, replace it with a lift */			
					createUpperLevel(upper);
				}

				currentRoom = newRoom;
				specialAction = false;
				timer--;
			}

		} while ( timer >= 0  && (gameEnded == false) );

		/*	final state  */
		if(jumpedOntoStage) {
			std::cout << "Holy crap, you did it! You jumped onto the stage!\n";
			std::cout << "You win!\n"; 
			std::cout << std::endl;
		}

		else if (jumpedOntoStage == false && tookLift == false) {
			std::cout << "SPLAT! You and your bandmates land with a thud onto\n";
			std::cout << "the stage. It hurts. It really hurts. You don't think\n";
			std::cout << "that there's going to be a show tonight. You have\n";
			std::cout << "lost the game. Surely this is a dark day in the history\n";
			std::cout << "of Spinal Tap.\n";
			std::cout << std::endl;
		}

		else if(tookLift) {
			std::cout << "You've finally made it onto the stage. You win!\n";
			std::cout << std::endl;
		}
		else {
			std::cout << "Time has run out! The crowd has grown restless and left\n";
			std::cout << "You have lost the game. Surely this is a dark day in the\n";
			std::cout << "history of Spinal Tap.\n";
			std::cout << std::endl;
		}
	}

	clearLevel(lower);
	delete lower;

	clearLevel(upper);
	delete upper;

	return 0;
}

/******************************************************************************
** Function: displayTurnsRemaining()
** Description: Displays the number of turns remaining until the game ends.
** Parameters: int timeLeft, the number of turns remaining.
** Pre-Conditions: timeLeft should be a valid int parameter.
** Post-Conditions: The value of timeleft has been formatted and returned as a 
** string.
*******************************************************************************/

std::string displayTurnsRemaining(int timeLeft)
{
	const int HEADER_WIDTH = 30;

	std::ostringstream timerHeader;

	for(int i = 0; i < HEADER_WIDTH; i++)
		timerHeader << "-";
	
	timerHeader << "TURNS REMAINING: " << timeLeft;

	for(int i = 0; i < HEADER_WIDTH; i++)
		timerHeader << "-";

	return timerHeader.str();
}

/******************************************************************************
** Function: createLowerLevel()
** Description: 
** Parameters: 
** Pre-Conditions: 
** Post-Conditions: Memory has been allocated to each Room pointer, and Rooms
** have been linked together into a structure as indicated below. 
*******************************************************************************/

void createLowerLevel(Room *&center)
{			
	Room *north = new JanRoom("Janitor's Closet");
	Room *south = new DressingRoom("Dressing Room");
	Room *west = new LoadingDock("Loading Dock");

	/* north, south, east, west, up, down */
	center->connect(north, south, NULL, west, NULL, NULL);
	north->connect(NULL, center, NULL, west, NULL, NULL);
	south->connect(center, NULL, NULL, west, NULL, NULL);
	west->connect(north, south, center, NULL, NULL, NULL);
}


/******************************************************************************
** Function: createUpperLevel()
** Description: Creates the upper level game environment, links rooms together
** to form the 'catwalk' portion of the game.
** Parameters: center, north, south, east, west: all references to Room pointers
** Pre-Conditions: All parameters must be valid Room derived types.
** Post-Conditions: Memory has been allocated to each Room pointer, and Rooms
** have been linkled together into a structure as indicated below.
*******************************************************************************/

void createUpperLevel(Room *&center)
{
	Room *north = new FlySpace("Fly Space: North");
	Room *south = new FlySpace("Fly Space: South");
	Room *east = new ControlRoom("Control Room");
	Room *west = new FlySpace("Fly Space: West");

	/* north, south, east, west, up, down */
	center->connect(north, south, east, west, NULL, NULL);
	cout << center->getEast()->getID() << endl;

	north->connect(NULL, center, NULL, NULL, NULL, NULL);
	south->connect(center, NULL, NULL, NULL, NULL, NULL);
	east->connect(NULL, NULL, NULL, center, NULL, NULL);
	west->connect(NULL, NULL, center, NULL, NULL, NULL);
}

/******************************************************************************
** Function: clearLowerLevel()
** Description: Frees all memory associated with a level of the game.
** Parameters: center, north, south, east, west: all references to Room pointers.
** Pre-Conditions: All parameters must be valid Room derived types. All parameters
** should point to dynamically-allocated objects.
** Post-Conditions: All memory associated with the parameters has been freed, and
** each parameter has been set to NULL.
*******************************************************************************/

void clearLevel(Room *&center)
{

	Room *north = center->getNorth();
	delete north;
	north = NULL; 

	Room *south = center->getSouth();
	delete south;
	south = NULL;

	Room *west = center->getWest();
	delete west;
	west = NULL;

	Room *east = center->getEast(); 
	delete east;
	east = NULL;

}

/******************************************************************************
** Function: displayTitle()
** Description: Displays the opening title and sets the scene for the game.
** Parameters: none.
** Pre-Conditions: none.
** Post-Conditions: A string has been returned describing the opening conditions
** for the game.
*******************************************************************************/

std::string displayTitle()
{
	std::ostringstream title;

	title << 
	"\"HELLO CLEVELAND!\" : A text-based adventure inspired by the classic 1984 film\n"
	"\"This Is Spinal Tap\".\n\n"

	"The time: 1982. The place: The Xanadu Star Theater, Cleveland, Ohio.\n\n" 

	"YOU are Nigel Tufnel, lead guitarist of the world-famous rock band Spinal Tap,\n" 
	"touring across the USA to promote your new album, \"Smell the Glove\".\n\n"

	"The time has come for tonight's show to start; the crowd is getting restless,\n" 
	"as the incessant chanting of \"TAP! TAP! TAP!\" filters its way through the\n" 
	"theater's labyrinthine backstage. \"Well, we've kept them waiting long enough\n" 
	"- let's do it to 'em\", says Derek, the bassist. Your instruments are tuned,\n" 
	"the miniature sandwiches have been eaten, and the stage is set - but, wait,\n"
	"the stage door is locked! You try shouting through the door for someone to\n"
	"open it, but your efforts are fruitless. Can you find your way onto the stage\n"
	"before the crowd gets restless and leaves?\n"	
	<< std::endl;

	return title.str();
}

/******************************************************************************
** Function: performJump()
** Description: Performs a "jump" off of the catwalk level. High-risk, high-
** reward move in the game.
** Parameters: none.
** Pre-Conditions: none.
** Post-Conditions: Returns true if a randomly-created number between 0 and 1
** is 0, and false otherwise.
*******************************************************************************/

bool performJump()
{
	if( (rand() % 2) == 0 ) {	//1-in-2 chance of pulling this off...
		return true;
	}

	return false;
}

/*******************************************************************************
** Function: inputBinaryChoice()
** Description: Returns one of two possible characters representing a binary
** user choice
** Parameters: firstChoice and secondChoice, char parameters representing the 
** desired user choices.  
** Pre-Conditions: firstChoice and secondChoice are valid char arguments.
** Post-Conditions: the function returns either firstChoice or secondChoice.
*******************************************************************************/

char inputBinaryChoice(char firstChoice, char secondChoice)
{
	std::string inputLine;	//stores user input
	bool badChar;		//tracks if valid character has been entered
	char chIn;			//stores single-character input

	do {
		badChar = true;
		std::getline(std::cin, inputLine);

		/* if input is not 1 character, not valid. Must be 'O' or 'A' */
		if((inputLine.length() == 1) 
			&& (toupper(inputLine[0]) == firstChoice 
				|| toupper(inputLine[0]) == secondChoice))	{
				
				badChar = false;
				chIn = toupper(inputLine[0]);
		}
		else {
			cout << "Enter " << firstChoice << " or " << secondChoice << ": ";
			badChar = true;
		}

	} while (badChar);

	return chIn;
}

/*******************************************************************************
** Function: resetLowerLevel()
** Description: readjusts the structure of the lower level after the character
** finds the boiler room key. Allows access to the boiler room.
** Parameters: lower, the central node in the lower level.
** Pre-Conditions: lower must be initialized.
** Post-Conditions: the east room in the lower level is now a Boiler Roon.
** memory associated with the previous east room has been deleted.
*******************************************************************************/

void resetLowerLevel(Room *&lower)
{
	/* allow access to boiler room */
	Room *east = lower->getEast();
	delete east;

	east = new BoilerRoom("Boiler Room");
	
	/* keep state of rooms that should stay */
	Room *north = lower->getNorth();
	Room *south = lower->getSouth();
	Room *west = lower->getWest();

	/* connect the rooms back together */
	east->connect(NULL, NULL, NULL, lower, NULL, NULL);
	lower->connect(north, south, east, west, NULL, NULL); 
}

/*******************************************************************************
** Function: resetUpperLevel()
** Description: readjusts the structure of the upper level after the character
** uses the intercom. Allows access to the lift.
** Parameters: upper, the central node in the upper level.
** Pre-Conditions: upper must be initialized.
** Post-Conditions: the west room in the upper level is now a Lift. Memory 
** associated with the previous west room has been deleted.
*******************************************************************************/

			
void resetUpperLevel(Room *&upper)
{
	/* allow access to lift  */
	Room *west = upper->getWest();
	delete west;

	west = new Lift("Lift");

	/* keep state of rooms that should stay */
	Room *north = upper->getNorth();
	Room *south = upper->getSouth();
	Room *east = upper->getEast();

	/* connect the rooms back together */
	west->connect(NULL, NULL, upper, NULL, NULL, NULL);
	upper->connect(north, south, east, west, NULL, NULL); 

}
