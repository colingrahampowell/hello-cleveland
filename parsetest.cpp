
#include "FileParser.hpp"
#include <iostream>
#include <string>
//#include "Hero.hpp"
//#include "Item.hpp"
//#include "Room.hpp"
//#include "Lift.hpp"


using namespace std;

int main(int argc, char** argv) {

	std::vector<std::string> tgts;
	tgts.push_back("ROOM_DESC");
	tgts.push_back("SPEC_ACT");
	string path("./rooms/test.txt");

	cout << "testing.." << endl;

	FileParser parser( path, tgts );


//	Room *test = new Lift( "lift", "./rooms/test.txt");

//	delete test;

	return 0;
}
