/******************************************************************************
** Program Filename: Item.hpp
** Author: Colin Powell
** Date: 8/4/16
** Description: Final Project - Item class specification ("header") file
** Input: N/A
** Output: N/A
*******************************************************************************/

#ifndef ITEM_HPP		//include guards
#define ITEM_HPP

#include <string>

class Item
{
	private:
		std::string description;		//a short description
		std::string itemID;				//a single-word ID for each Item
	public: 
		Item(std::string, std::string);	//description, ID

		/* "getters" */
		std::string getDescription();
		std::string getID();
};

#endif