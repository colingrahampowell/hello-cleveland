/******************************************************************************
** Program Filename: Hero.hpp
** Author: Colin Powell
** Date: 8/4/16
** Description: Final Project - Hero class specification ("header") file
** Input: N/A
** Output: N/A
*******************************************************************************/

#ifndef HERO_HPP			//include guards
#define HERO_HPP

#include <string>
#include <iostream>			//for NULL keyword
#include <iomanip>
#include <sstream>

#include "Item.hpp"

class Hero
{
	private:
		Item** roadie;		// our container (array of pointers-to-Item)
		int numItems;		// current number of items
		int itemMax;		// max num. of items	
		static const int HEADER_WIDTH = 30;	

	public:
		Hero();
		~Hero();

		bool recruitRoadie();				

		bool pickUp(Item *);
		Item *drop(std::string);		

		bool hasItem(std::string);
		bool hasRoadie();
		bool roadieEmpty();
		bool roadieAtCapacity();

		std::string displayItems();
};

#endif