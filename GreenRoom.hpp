/******************************************************************************
** Program Filename: GreenRoom.hpp
** Author: Colin Powell
** Date: 8/4/16
** Description: Final Project - GreenRoom derived class implementation file
** Input: N/A
** Output: N/A
*******************************************************************************/

#ifndef GREENROOM_HPP	//include guards
#define GREENROOM_HPP

#include <string>
#include <sstream>

#include "Room.hpp"

class GreenRoom : public Room
{
	protected:
		bool doorUnlocked;	//tracks special ability activation
		virtual std::string specialAction();

	public:
		GreenRoom(std::string);
		virtual bool interact();
};

#endif
