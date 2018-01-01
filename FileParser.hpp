/******************************************************************************
** Filename: FileParser.hpp
** Author: Colin Powell
** Description: File Parser class specification ("header") file
*******************************************************************************/

#ifndef PARSER_HPP		//include guards
#define PARSER_HPP 

#include <string>
#include <vector>		
#include <fstream>
#include <iostream>		//for file operations
#include <iterator>		//for reading from file
#include <map>

class FileParser 
{
	
	protected:

		typedef std::map< std::string, std::vector<std::string> > vecMap;
		vecMap content;
		std::string trim( std::string& );
		int findNextTarget( const std::string& ); 	

	public:
		FileParser( const std::string&, const std::vector<std::string> );
//		~FileParser();
	
		std::vector<std::string> getTarget( std::string& );

};

#endif
