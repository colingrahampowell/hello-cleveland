/*
 * Filename: FileParser.cpp
 * Author: Colin Powell
 * Description: File Parsing class implementation file
 */

#include "FileParser.hpp"

/*
 * Name: trim
 * Description: trims leading / trailing whitespace from string
 */

std::string FileParser::trim( std::string &passage ) 
{
	// erase leading whitespace / special chars (including ':')
	size_t start = passage.find_first_not_of(" :\t");
	size_t end = passage.find_last_not_of(" \t\n");

	// if there is only whitespace, return empty string
	if( start == std::string::npos ) {
		return "";
	}		
	else {
		// (end - start) + 1 gives us the length of the trimmed substring
		return passage.substr( start, (end - start) + 1 );
	}
}


/*
 * Name: findNextEntry
 */

int FileParser::findNextTarget( const std::string& targets ) 
{

	return 1;
}


/*
 * Name: FileParser (constructor) 
 */

FileParser::FileParser( const std::string& path, const std::vector<std::string> targets )
{

//	std::cout << targets.size() << ": " << targets << std::endl;
	std::string temp;
	int i, j;
	bool tgtFound, nextFound;

	size_t pos = 0;		// position into string 
	size_t stop;

	// create empty vectors for targets
	for( int i = 0; i < targets.size(); i++ ) {
		content.insert( std::pair<std::string, std::vector<std::string> >( targets[i], std::vector<std::string>() ) );
	}

	std::cout << "finished creating map" << std::endl;

	// open file
	std::ifstream info( path.c_str() );

	// use iterators to place into string
	std::string roomSpecs	((std::istreambuf_iterator<char>(info)),
							(std::istreambuf_iterator<char>()	));

	// search for all targets, place into map
	while( pos < (roomSpecs.length() - 1)) {
		
		i = j = 0;	
		tgtFound = nextFound = false;

//		std::cout << "pos: " << pos << std::endl;
		while( i < targets.size() && !tgtFound ) {
			
			// look for start of any target in our list of targets
			if( roomSpecs.find( targets[i], pos ) != std::string::npos ) {
				pos = roomSpecs.find( targets[i], pos ) + targets[i].length();	
				tgtFound = true;
			}
			
			else {	
				i++;	// if not found, look for next target
			}

		}
		/*
		// find start of any target
		for( i = 0; i < targets.size(); i++ ) {
	
			if( roomSpecs.find( targets[i], pos ) != std::string::npos ) {
				pos = roomSpecs.find( targets[i], pos ) + targets[i].length();	
//				std::cout << "hdr found at pos: " << pos << std::endl;
				break;
			}

		}	
		*/

		while( j < targets.size() && !nextFound ) {
			
			// look for start of any target in our list of targets
			if( roomSpecs.find( targets[j], pos ) != std::string::npos ) {
				stop = roomSpecs.find( targets[j], pos ); 
				nextFound = true;
			}
			else {	
				j++;	// if not found, look for next target
			}
		}

		if( !nextFound ) {
			stop = roomSpecs.length() - 1;
		}	

		/*
		// find start of next target (if it exists)
		for( j = 0; j < targets.size(); j++ ) {

			if( roomSpecs.find( targets[j], pos ) != std::string::npos ) {
//				std::cout << "stop found at pos: " << stop << std::endl;
				stop = roomSpecs.find( targets[j], pos );
				break;
			}

			// we have found the last entry
			else {
				stop = roomSpecs.length() - 1;
			}
	
		}
		*/

		// create substring and trim whitespace 
		temp = roomSpecs.substr( pos, stop - pos );
		temp = FileParser::trim( temp );
	
		// assign to map
		this->content[ targets[i] ].push_back( temp );

		// update with start of next target
		pos = stop;

	}

	// TESTING TESTING TESTING	

	std::cout << "loop 0 start" << std::endl;
	for(int j = 0; j < this->content[ targets[0] ].size(); j++) {
		std::cout << j << ":" << this->content[ targets[0] ][j] << std::endl;
	}
	
	std::cout << "loop 1 start" << std::endl;
	for(int j = 0; j < this->content[ targets[1] ].size(); j++) {
		std::cout << j << ":" << this->content[ targets[1] ][j] << std::endl;
	}

	info.close();

}


/*
 * getTarget(): returns hash map containing categorized file contents 
 */

std::vector<std::string> FileParser::getTarget(std::string& target) 
{
	vecMap::iterator it = this->content.find(target);

	// if content found, return it
	if( it != this->content.end() ) { 
		return it->second;
	}	
	// otherwise, return empty vector
	else return std::vector<std::string>();
}
