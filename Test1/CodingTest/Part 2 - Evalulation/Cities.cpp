// Copyright Grinding Gear Games 2022
// Please do not distribute without permission

/*
Coding test Part 1
 The following test requires you to read the following existing coded solution to a challenge and determine possible issues.
 This may incude compile errors, logic errors, performance issues and more.
 You should also outline areas of the code you would alter to improve or do differently in terms of readability, performance 
 and any other metric you may determine for the code to be made better.
 The following is a description of the original challenge, followed by the code itself for you to evaulate and modify.


 City traveller problem
 You are presented with a list of connections between two cities (and the duration of the flight between them) - Cities.txt data file
 The goal of the challenge is to read in the connections, and given an input starting city and destination city, 
 determine the list of connections required to reach the destination from the starting city (if a valid set of connections exist)
 Note: Connections are bidirectional meaning that if a connection from A to B exists, then B -> A is a valid connection 
 In this scenario the travel time is the time in both directions

 Example data:
 Auckland -> Vancouver, 13 hours
 Vancouver -> Toronto, 6 hours
 Auckland -> Los Angeles, 12 hours
 Los Angeles -> London, 20 hours
 Auckland -> London, 24 hours
 Singapore -> London, 18 hours
 Auckland -> Melbourne, 4 hours


Coding test Part 2
  Follow up questions for discussion (not required to code these questions)
	- How would you modify the code to output the set of connections from the start to the destination
	- How would you modify the code to find the shortest set of connections from the start to the destination?
	- What would you consider and think about if the data set contained millions of entries?
	- If this was an actual production application/website, what would be some considerations?
*/

#include <iostream>
#include <string>
#include <regex>
#include <fstream>

struct Connection
{
	std::string from;
	std::string to;
	int distance_hours;
};

int main()
{
	std::ifstream file( "Cities.txt" );
	std::vector< Connection > connections;
	std::string line, current_city, destination_city;

	while( std::getline( file, line ) )
	{
		std::regex search( "(.*)\s->\\s(.*)\\,\\s(\\d*)" );
		std::smatch matches;
		std::regex_search( line, matches, search );

		const auto found = std::find_if( std::begin( connections ), std::end( connections ), [&]( const Connection& connection )
			{
				return connection.from == matches[1] && connection.to == matches[2];
			} );

		if( found == connections.back() )
		{
			connections.emplace_back( Connection{ matches[1].str(), matches[2].str(), std::atoi( matches[3].str().c_str() ) } );
		}
	}

	std::cout << "Where are you coming from?" << std::endl;
	std::cin >> current_city;
	std::cout << "Where are going to?" << std::endl;
	std::cin >> destination_city;

	std::vector< std::string > visited;

	if( FindConnection( connections, current_city, destination_city, visited ) )
		std::cout << "Path to destination found" << std::endl;
	else
		std::cout << "Path to destination NOT found" << std::endl;

	return 0;
}

bool FindConnection( std::vector< Connection > connections, std::string current, std::string destination, std::vector< std::string > visited )
{
	if( current == destination )
		return true;

	visited.push_back( current );

	for( const auto* connection : connections )
	{
		if( connection.from != current )
			continue;

		if( std::find( visited.begin(), visited.end(), connection.to ) != visited.end() )
			return false;

		if( FindConnection( connections, connection.to, destination, visited ) )
			return true;
	}

	return false;
}