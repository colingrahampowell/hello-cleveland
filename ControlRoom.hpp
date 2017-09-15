/******************************************************************************
** Program Filename: ControlRoom.hpp
** Author: Colin Powell
** Date: 8/4/16
** Description: Final Project - ControlRoom derived class header file
** Input: User selection of menu options relating to specific room actions.
** Output: Menu-based interface, output to console.
*******************************************************************************/

#ifndef CONTROLROOM_HPP
#define CONTROLROOM_HPP

#include <string>
#include <sstream>
#include <cctype>

#include "Room.hpp"

class ControlRoom : public Room
{
	protected:
		bool talked;	//tracks special activity
		virtual std::string specialAction();

	public:
		ControlRoom(std::string);
		virtual bool interact();
};

#endif
