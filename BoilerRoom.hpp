/******************************************************************************
** Program Filename: BoilerRoom.hpp
** Author: Colin Powell
** Date: 8/4/16
** Description: Final Project - BoilerRoom derived class implementation file
** Input: N/A
** Output: N/A
*******************************************************************************/

#ifndef BOILERROOM_HPP		//include guards
#define BOILERROOM_HPP

#include <string>
#include <sstream>

#include "Room.hpp"

class BoilerRoom : public Room
{
	protected:
		bool liftActive;	//special activity tracker
		void updateDescription();
		virtual std::string specialAction();

	public:
		BoilerRoom(std::string);
		virtual bool interact();
};

#endif
