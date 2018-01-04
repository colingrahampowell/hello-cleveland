/*
 * Colin Powell
 * Game class: specification file
 */

#ifndef GAME_HPP
#define GAME_HPP

#include <vector>
#include <string>
#include <iterator>
#include <map>
#include <fstream>
#include <iostream>

class Game {

	protected:
		typedef std::pair<std::string, bool> state_pair;
		std::map< std::string, bool > states;
		//std::vector< Room* > rooms;

		std::string findAttr( 	const std::string&, 
								const std::string&, 
								size_t& );

		size_t fetchStates( const std::string&, size_t );
		size_t fetchRooms( const std::string&, size_t );
		void parseFile( const std::string& path );

	public:
		Game( std::string );
		~Game() {};

};

#endif
