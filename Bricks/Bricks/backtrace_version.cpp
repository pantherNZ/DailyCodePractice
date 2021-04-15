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
bool Traverse( const std::vector< std::string >& data, std::unordered_set< Coord, PairHash >& visited, Coord coord, std::vector< Coord >& path_out );

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

	for( int i = 0; i < (int )data.front().size(); i += 2 )
	{
		std::vector< Coord > path;

		if( Traverse( data, visited, Coord( i / 2, 0 ), path ) )
		{
			std::cout << "A valid path was found:\n";
			path_found = true;

			for( int j = ( int )path.size() - 1; j >= 0; --j )
				std::cout << "(" << path[j].first << ", " << path[j].second << ")" << ( j > 0 ? ", " : "" );

			break;
		}
	}

	if( !path_found )
		std::cout << "No path was found\n";

	std::cin.get();
}

bool Traverse( const std::vector< std::string >& data, std::unordered_set< Coord, PairHash >& visited, Coord coord, std::vector< Coord >& path_out )
{
	// Found bottom
	if( coord.second >= (int )data.size() )
	{
		path_out.push_back( coord );
		return true;
	}

	if( coord.first < 0 || ( coord.first * 2 ) >= (int )data[coord.second].size() - 1 )
		return false;

	// Is this a valid spot?
	if( data[coord.second][coord.first * 2] != '{' || data[coord.second][coord.first * 2 + 1] != '}' )
		return false;

	// Already visited
	if( visited.find( coord ) != visited.end() )
		return false;

	visited.insert( coord );

	const auto move_to_next = [&]( Coord new_cord ) -> bool
	{
		if( Traverse( data, visited, new_cord, path_out ) )
		{
			path_out.push_back( coord );
			return true;
		}

		return false;
	};

	// Right
	if( move_to_next( Coord( coord.first + 1, coord.second ) ) )
		return true;

	// Left
	if( move_to_next( Coord( coord.first - 1, coord.second ) ) )
		return true;

	// Down
	if( move_to_next( Coord( coord.first, coord.second + 1 ) ) )
		return true;

	// Even depth means we can move down or left, odd means we can move down or right
	if( move_to_next( Coord( coord.first + ( ( coord.second & 1 ) ? 1 : - 1 ), coord.second + 1 ) ) )
		return true;

	return false;
}