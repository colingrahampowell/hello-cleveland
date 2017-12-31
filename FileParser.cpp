/*
 * Filename: FileParser.cpp
 * Author: Colin Powell
 * Description: File Parsing class implementation file
 */

#include "FileParser.hpp"


/*
 * Name: findNextEntry
 */

int FileParser::findNextTarget( std::string& targets ) 
{
	/*
	std::string temp;
	int pos;

//	this->roomDesc.push_back( temp.substr(10) );
	pos = info.tellg();

	// keep reading until we have found another header
	while( std::getline(info, temp) ) {

		// if we have found another header, rewind
		if( temp.compare(0, 10, "ROOM_DESC:") == 0 ) {
			return pos;
		}	

		// otherwise, append to current descript. string
		// and update 'last read' position
		else {
//			this->roomDesc[this->roomDesc.size() - 1].append(temp);
			pos = info.tellg();		
		}
	}

	return pos;
	*/
	return 1;
}


/*
 * Name: FileParser (constructor) 
 */

FileParser::FileParser( std::string& path, const std::string targets[] )
{

	std::string temp;

	int pos = 0;		// position into string 

	// open file
	std::ifstream info( path.c_str() );

	// use iterators to place into string
	std::string roomSpecs	((std::istreambuf_iterator<char>(info)),
							(std::istreambuf_iterator<char>()	));

	/*
	for(int j = 0; j < this->roomDesc.size(); j++) {
		std::cout << j << ": " << this->roomDesc[j];
	}
	*/

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
