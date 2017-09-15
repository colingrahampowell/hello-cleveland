/******************************************************************************
** Program Filename: FlySpace.hpp
** Author: Colin Powell
** Date: 8/4/16
** Description: Final Project - FlySpace derived class header file
** Input: N/A
** Output: N/A
*******************************************************************************/

#ifndef FLYSPACE_HPP
#define FLYSPACE_HPP

#include <string>
#include <sstream>
#include <cctype>

#include "Room.hpp"

class FlySpace : public Room
{
	protected:
		bool jumped;	//special action tracker
		virtual std::string specialAction();

	public: 
		FlySpace(std::string);
		virtual bool interact();
};

#endif