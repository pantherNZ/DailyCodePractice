#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <tuple>
#include <unordered_set>

struct PairHash
{
	template< class A, class B >
	size_t operator()( const std::pair< A, B >& pair ) const
	{
		return std::hash< A >()( pair.first ) ^ std::hash< B >()( pair.second ) * 13;
	}
};

typedef std::pair< int, int > Coord;
bool Traverse( const std::vector< std::string >& data, std::unordered_set< Coord, PairHash >& visited, Coord coord );

int main()
{
	std::fstream file( "bricks.txt" );
	std::vector< std::string > data;
	data.reserve( 32 );
	std::string line;

	while( std::getline( file, line ) )
	{
		if( ( data.size() & 1 ) == 1 )
			line.erase( line.begin() );
		data.push_back( line );
	}

	std::unordered_set< Coord, PairHash > visited;
	bool path_found = false;

	for( int i = 0; i < ( int )data.front().size(); i += 2 )
	{
		if( Traverse( data, visited, Coord( i / 2, 0 ) ) )
		{
			path_found = true;
			break;
		}
	}

	if( path_found )
		std::cout << "A valid path was found\n";
	else
		std::cout << "No path was found\n";

	std::cin.get();
}

bool Traverse( const std::vector< std::string >& data, std::unordered_set< Coord, PairHash >& visited, Coord coord )
{
	// Found bottom
	if( coord.second >= ( int )data.size() )
		return true;

	if( coord.first < 0 || ( coord.first * 2 ) >= ( int )data[coord.second].size() - 1 )
		return false;

	// Is this a valid spot?
	if( data[coord.second][coord.first * 2] != '{' || data[coord.second][coord.first * 2 + 1] != '}' )
		return false;

	// Already visited
	if( visited.find( coord ) != visited.end() )
		return false;

	visited.insert( coord );

	// Right
	if( Traverse( data, visited, Coord( coord.first + 1, coord.second ) ) )
		return true;

	// Left
	if( Traverse( data, visited, Coord( coord.first - 1, coord.second ) ) )
		return true;

	// Down
	if( Traverse( data, visited, Coord( coord.first, coord.second + 1 ) ) )
		return true;

	// Even depth means we can move down or left
	if( ( coord.second & 1 ) == 0 )
	{
		if( Traverse( data, visited, Coord( coord.first - 1, coord.second + 1 ) ) )
			return true;
	}
	// Even depth means we can move down or right
	else
	{
		if( Traverse( data, visited, Coord( coord.first + 1, coord.second + 1 ) ) )
			return true;
	}

	return false;
}