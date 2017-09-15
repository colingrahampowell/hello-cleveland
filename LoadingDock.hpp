/******************************************************************************
** Program Filename: LoadingDock.hpp
** Author: Colin Powell
** Date: 8/4/16
** Description: Final Project - LoadingDock derived class implementation file
** Input: N/A
** Output: N/A
*******************************************************************************/

#ifndef LOADDOCK_HPP
#define LOADDOCK_HPP

#include <string>
#include <sstream>
#include <vector>
#include <cctype>

#include "Room.hpp"

class LoadingDock : public Room
{
	protected:
		bool obtainedRoadie;
		virtual std::string specialAction();

	public:
		LoadingDock(std::string);
		virtual bool interact();
};

#endif
