/*
 * Colin Powell
 * Game class: implementation file
 */

#include "Game.hpp"

/*
 * Constructor: 
 */

Game::Game( std::string path ) {

	Game::parseFile( path );

}


/*
 * findAttr:
 */

std::string	Game::findAttr( const std::string& specs, 
							const std::string& attr, 	
							size_t& pos ) 
{

	std::string open = "<" + attr + ">";
	std::string close = "</" + attr + ">";	

	size_t dataStart = specs.find( open, pos ) + open.length();
	size_t len = specs.find( close, dataStart ) - dataStart;
	
	pos = dataStart + len + close.length();	// get to end of closing tag
	pos = specs.find_first_not_of(" \n", pos );	// skip ahead to end of whitespace

	return specs.substr( dataStart, len );
}

/*
 * fetchStates:
 */

size_t Game::fetchStates( const std::string& specs, size_t pos ) {

	size_t sEnd = specs.find( "##" );
	while( pos < sEnd ) {
		this->states.insert( state_pair( findAttr( specs, "state", pos ), false ) );
	}	

	return pos;
}

/*
 * fetchRooms:
 */

size_t Game::fetchRooms( const std::string& specs, size_t pos ) {
	
	size_t sEnd = specs.find( "##" );
	while( pos < sEnd ) {
		



	}

	return pos;
}

/*
 * parseFile: 
 */

void Game::parseFile( const std::string& path ) {
	
	size_t pos = 0;
	size_t stop;
	std::pair<size_t, size_t> attr;

	// open file stream for input
	std::ifstream info( path.c_str() );

	// collect into string 
	std::string specs( 	(std::istreambuf_iterator<char>(info)),
						std::istreambuf_iterator<char>() );

	// read game states into 'states' member	
	pos = fetchStates( specs, pos );
	// TESTING TESTING TESTING

	
	for( auto it : states ) {
		std::cout << it.first << ": " << it.second << std::endl;
	}
	

	// read rooms into rooms array
	/*
	while (pos < specs.length - 1) {

		sEnd = specs.find("##");
		if( sEnd == std::string::npos ) { sEnd = specs.length - 1; };
		while( pos < sEnd ) {

			// makeRoom

//			Room *newroom = new Room;

			// get access state
			attr = findAttr( specs, "enter_state", pos );
			newroom->enter_state = specs.substr( attr.first, attr.second );

			// get description
			attr = findAttr( specs, "desc", pos );
			newroom->desc = specs.substr( attr.first, attr.second );

			// get commands	
			attr = findAttr( specs, "commands", pos );
					

//			this->rooms.move(
		}
		
	}
	*/	

	info.close();		

}
