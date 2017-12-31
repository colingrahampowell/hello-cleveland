
#include "Room.hpp"
#include "Lift.hpp"
#include <iostream>
#include "Hero.hpp"
#include "Item.hpp"

int main(int argc, char** argv) {

	std::cout << "testing.." << std::endl;

	Room *test = new Lift( "lift", "./rooms/test.txt");

	delete test;

	return 0;
}
