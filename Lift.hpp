/******************************************************************************
** Program Filename: Lift.hpp
** Author: Colin Powell
** Date: 8/4/16
** Description: Final Project - Lift derived class header file
** Input: N/A
** Output: N/A
*******************************************************************************/

#ifndef LIFT_HPP
#define LIFT_HPP

#include <string>
#include <sstream>
#include <cctype>

#include "Room.hpp"

class Lift : public Room
{
	protected:
		bool liftTaken;
		virtual std::string specialAction();

	public:
		Lift(std::string, std::string);
		virtual bool interact();
};

#endif
