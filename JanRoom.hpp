/******************************************************************************
** Program Filename: JanRoom.hpp
** Author: Colin Powell
** Date: 8/4/16
** Description: Final Project - BoilerRoom derived class implementation file
** Input: N/A
** Output: N/A
*******************************************************************************/

#ifndef JANROOM_HPP		//"include guards"
#define JANROOM_HPP

#include <string>
#include <sstream>
#include <cctype>

#include "Room.hpp"

class JanRoom : public Room
{
	protected:
		bool givenSandwich;
		virtual std::string specialAction();

	public:
		JanRoom(std::string);
		virtual bool interact();
};

#endif
