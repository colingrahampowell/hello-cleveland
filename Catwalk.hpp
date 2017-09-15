/******************************************************************************
** Program Filename: Catwalk.hpp
** Author: Colin Powell
** Date: 8/4/16
** Description: Final Project - Catwalk derived class header file
** Input: N/A
** Output: N/A
*******************************************************************************/

#ifndef CATWALK_HPP		//include guards
#define CATWALK_HPP

#include <string>
#include <sstream>

#include "Room.hpp"

class Catwalk : public Room
{
	protected:
		bool stonehengeLowered;		//tracks if stonehenge has been lowered
		bool revisited;				//tracks if this is the first time in this space
		bool crowdDistracted;		//tracks if the special action has been successful

		void updateDescription();
		virtual std::string specialAction();

	public:
		Catwalk(std::string);
		virtual bool interact();
};

#endif
