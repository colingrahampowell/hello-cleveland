/******************************************************************************
** Program Filename: DressingRoom.hpp
** Author: Colin Powell
** Date: 8/4/16
** Description: Final Project - DressingRoom derived class implementation file
** Input: User selection of menu options relating to specific room actions.
** Output: Menu-based interface, output to console.
*******************************************************************************/

#ifndef DRESSING_HPP
#define DRESSING_HPP

#include <string>
#include <sstream>

#include "Room.hpp"

class DressingRoom : public Room
{
	protected:
		bool mirrorChecked;	//tracks special activity
		virtual std::string specialAction();

	public:
		DressingRoom(std::string);
		virtual bool interact();
};

#endif
