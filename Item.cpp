/******************************************************************************
** Program Filename: Item.cpp
** Author: Colin Powell
** Date: 8/4/16
** Description: Final Project - Item class implementation file
** Input: N/A
** Output: N/A
*******************************************************************************/

#include "Item.hpp"

/******************************************************************************
** Function: Item()
** Description: Item class constructor
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: An instance of the Item class has been created.
*******************************************************************************/

Item::Item(std::string descIn, std::string idIn)
{
	this->description = descIn;
	this->itemID = idIn;
}

/* "get" functions */

std::string Item::getDescription() { return description; }
std::string Item::getID() { return itemID; }