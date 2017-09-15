/******************************************************************************
** Program Filename: Room.hpp
** Author: Colin Powell
** Date: 8/4/16
** Description: Final Project - Room base class specification ("header") file
** Input: N/A
** Output: N/A
*******************************************************************************/

#ifndef ROOM_HPP		//include guards
#define ROOM_HPP

#include "Hero.hpp"
#include "Item.hpp"

#include <string>
#include <sstream>
#include <vector>		//for roomItems, validChoices vectors
#include <cctype>		//for user input validation

class Room 
{
	protected:
		/* directional pointers: */
		Room *north;
		Room *south;
		Room *east;
		Room *west;
		Room *up;
		Room *down;

		std::vector <char> validChoices;	//array (vector) of valid user choices
		std::vector <Item*> roomItems;		//vector of pointers to item in the room

		std::string roomID;						//this room's unique ID
		std::ostringstream roomDescription;		//this room's description
		std::ostringstream menuOptions;			//the list of possible actions

		Hero *nigel;							//pointer to our hero

		static const int HEADER_WIDTH = 30;	//the width of display headers

		/* display */
		std::string displayMenu();
		std::string displayMoveDirections();
		std::string displayRoomItems();

		/* basic room actions */
		std::string lookAround();
		std::string takeFromHero();		
		std::string giveToHero();	
		std::string giveHint();

		/* process user input */
		char inputMenuChoice();	
		char inputMoveDir();
		std::string inputRemoveItem();
		std::string inputAddItem();

		/* input validation */
		bool isValidMenuChoice(std::string);
		bool isValidDirection(std::string);
		bool isValidChar(std::string);

		/* special room actions */
		virtual std::string specialAction() = 0;

	public:
		Room(std::string);
		virtual ~Room();

		virtual bool interact() = 0;
		Room *move();

		void connect(Room *north, Room *south, Room *east, Room *west, 
							Room *up, Room *down);

		void placeHero(Hero *);	
		
		/* getters */
		std::string getID();
		Room *&getNorth();
		Room *&getSouth();
		Room *&getEast();
		Room *&getWest();
		Room *&getUp();
		Room *&getDown();

};

#endif