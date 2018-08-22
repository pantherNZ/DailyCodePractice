#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>
#include <numeric>
#include <functional>
#include <cassert>
#include <windows.h>

typedef std::tuple< int, int, bool > LineInfo;

struct State
{
	bool is_black = false;
	bool is_initialised = true;
	bool is_locked = false;

	void Lock( )
	{
		is_black = true;
		is_initialised = false;
		is_locked = true;
	}
};

State puzzle[25][25];

std::vector< int > y_values[25] =
{
	{ 7, 2, 1, 1, 7 },
	{ 1, 1, 2, 2, 1, 1 },
	{ 1, 3, 1, 3, 1, 3, 1, 3, 1 },
	{ 1, 3, 1, 1, 5, 1, 3, 1 },
	{ 1, 3, 1, 1, 4, 1, 3, 1 },
	{ 1, 1, 1, 2, 1, 1 },
	{ 7, 1, 1, 1, 1, 1, 7 },
	{ 1, 1, 3 },
	{ 2, 1, 2, 1, 8, 2, 1 },
	{ 2, 2, 1, 2, 1, 1, 1, 2 },
	{ 1, 7, 3, 2, 1 },
	{ 1, 2, 3, 1, 1, 1, 1, 1 },
	{ 4, 1, 1, 2, 6 },
	{ 3, 3, 1, 1, 1, 3, 1 },
	{ 1, 2, 5, 2, 2 },
	{ 2, 2, 1, 1, 1, 1, 1, 2, 1 },
	{ 1, 3, 3, 2, 1, 8, 1 },
	{ 6, 2, 1 },
	{ 7, 1, 4, 1, 1, 3 },
	{ 1, 1, 1, 1, 4 },
	{ 1, 3, 1, 3, 7, 1 },
	{ 1, 3, 1, 1, 1, 2, 1, 1, 4 },
	{ 1, 3, 1, 4, 3, 3 },
	{ 1, 1, 2, 2, 2, 6, 1 },
	{ 7, 1, 3, 2, 1, 1 }
};

std::vector< int > x_values[25] =
{
	{ 7, 3, 1, 1, 7 },
	{ 1, 1, 2, 2, 1, 1 },
	{ 1, 3, 1, 3, 1, 1, 3, 1 },
	{ 1, 3, 1, 1, 6, 1, 3, 1 },
	{ 1, 3, 1, 5, 2, 1, 3, 1 },
	{ 1, 1, 2, 1, 1 },
	{ 7, 1, 1, 1, 1, 1, 7 },
	{ 3, 3 },
	{ 1, 2, 3, 1, 1, 3, 1, 1, 2 },
	{ 1, 1, 3, 2, 1, 1 },
	{ 4, 1, 4, 2, 1, 2 },
	{ 1, 1, 1, 1, 1, 4, 1, 3 },
	{ 2, 1, 1, 1, 2, 5 },
	{ 3, 2, 2, 6, 3, 1 },
	{ 1, 9, 1, 1, 2, 1 },
	{ 2, 1, 2, 2, 3, 1 },
	{ 3, 1, 1, 1, 1, 5, 1 },
	{ 1, 2, 2, 5 },
	{ 7, 1, 2, 1, 1, 1, 3 },
	{ 1, 1, 2, 1, 2, 2, 1 },
	{ 1, 3, 1, 4, 5, 1 },
	{ 1, 3, 1, 3, 10, 2 },
	{ 1, 3, 1, 1, 6, 6 },
	{ 1, 1, 2, 1, 1, 2 },
	{ 7, 2, 1, 2, 5 }
};

void Initialise( )
{
	puzzle[3][3].Lock( );
	puzzle[3][4].Lock( );
	puzzle[3][12].Lock( );
	puzzle[3][13].Lock( );
	puzzle[3][21].Lock( );

	puzzle[8][6].Lock( );
	puzzle[8][7].Lock( );
	puzzle[8][10].Lock( );
	puzzle[8][14].Lock( );
	puzzle[8][15].Lock( );
	puzzle[8][18].Lock( );

	puzzle[16][6].Lock( );
	puzzle[16][11].Lock( );
	puzzle[16][16].Lock( );
	puzzle[16][20].Lock( );

	puzzle[21][3].Lock( );
	puzzle[21][4].Lock( );
	puzzle[21][9].Lock( );
	puzzle[21][10].Lock( );
	puzzle[21][15].Lock( );
	puzzle[21][20].Lock( );
	puzzle[21][21].Lock( );
}


void PrintBoard( const bool has_fault, const bool is_x_axis, const int row_index, const int current_index = -1 )
{
	HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute( hConsole, 15 );
	std::cout << std::endl << ( has_fault ? "Board hit a fault:" : "Board passed a new line:" ) << std::endl;
	for( unsigned j = 0; j < 25; ++j )
	{
		for( unsigned i = 0; i < 25; ++i )
		{		
			if( j == ( is_x_axis ? row_index : current_index ) && i == ( is_x_axis ? current_index : row_index ) )
			{
				SetConsoleTextAttribute( hConsole, 12 );
				std::cout << "F ";
			}
			else if( puzzle[j][i].is_locked )
			{
				SetConsoleTextAttribute( hConsole, 13 );
				std::cout << "L ";
			}
			else if( puzzle[j][i].is_black )
			{
				const bool current = ( is_x_axis && j == row_index ) || ( !is_x_axis && i == row_index );
				SetConsoleTextAttribute( hConsole, current ? 10 : 14 );
				std::cout << "B ";
			}
			else
			{
				SetConsoleTextAttribute( hConsole, 15 );
				std::cout << "W ";
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

bool IncrementSpaces( std::vector< int >& spaces, int& current_total, const int fault_index )
{
	for( int x = fault_index; x >= 0; x-- )
	{
		spaces[x]++;
		current_total++;

		if( current_total > 25 )
		{
			current_total -= ( spaces[x] - ( x == 0 ? 0 : 1 ) );
			spaces[x] = ( x == 0 ? 0 : 1 );
		}
		else
		{
			return true;
		}
	}

	return false;
}

bool ProcessLine( std::vector< LineInfo >& totals, unsigned index, std::vector< std::pair< int, bool > >& fault_source )
{
	std::vector< int > spaces;
	spaces.reserve( 15 );

	// Create a string with the spaces
	const unsigned row_index = std::get< 1 >( totals[index] );
	const bool is_x_axis = std::get< 2 >( totals[index] );
	const auto row = is_x_axis ? x_values[row_index] : y_values[row_index];

	// Horizontal row can be saved immediately by copying the array
	// Otherwise the saved line must be added to each vertical iteration
	std::vector< State > saved_line = is_x_axis ? std::vector< State >( std::begin( puzzle[row_index] ), std::end( puzzle[row_index] ) ) : std::vector< State >( );
	std::vector< std::pair< int, bool > > new_faults;

	spaces.push_back( 0 );

	for( unsigned j = 0; j < row.size( ) - 1; ++j )
		spaces.push_back( 1 );

	// Place on the board
	int current_index;
	int current_total = std::get< 0 >( totals[index] );

	while( current_total <= 25 )
	{
		current_index = 0;
		bool increment = false;

		if( !is_x_axis )
			saved_line.clear( );

		unsigned row_counter = 0;

		for( row_counter = 0; row_counter < row.size( ) && !increment; ++row_counter )
		{
			assert( current_index < 25 );

			// Spaces
			for( int x = 0; x < spaces[row_counter] && !increment; ++x, ++current_index )
			{		
				if( !is_x_axis )
				{
					if( puzzle[current_index][row_index].is_black && !puzzle[current_index][row_index].is_initialised )
					{
						increment = true;
						break;
					}

					saved_line.push_back( puzzle[current_index][row_index] );
					puzzle[current_index][row_index].is_black = false;
					puzzle[current_index][row_index].is_initialised = false;
				}
				else
				{
					if( puzzle[row_index][current_index].is_black && !puzzle[row_index][current_index].is_initialised )
					{
						increment = true;
						break;
					}

					puzzle[row_index][current_index].is_black = false;
					puzzle[row_index][current_index].is_initialised = false;
				}
			}

			// Fills
			for( int x = 0; x < row[row_counter] && !increment; ++x, ++current_index )
			{
				if( !is_x_axis )
				{
					if( !puzzle[current_index][row_index].is_black && !puzzle[current_index][row_index].is_initialised )
					{
						increment = true;
						break;
					}
	
					saved_line.push_back( puzzle[current_index][row_index] );
					puzzle[current_index][row_index].is_black = true;
					puzzle[current_index][row_index].is_initialised = false;
				}
				else
				{
					if( !puzzle[row_index][current_index].is_black && !puzzle[row_index][current_index].is_initialised )
					{
						increment = true;
						break;
					}

					puzzle[row_index][current_index].is_black = true;
					puzzle[row_index][current_index].is_initialised = false;
				}
			}
		}

		//if( !increment ) PrintBoard( false, is_x_axis, row_index );
	
		if( increment || !ProcessLine( totals, index + 1, fault_source ) )
		{
			//if( increment ) PrintBoard( true, is_x_axis, row_index, current_index );

			// Clear the row
			for( int x = 0; x < current_index; ++x )
			{
				is_x_axis ? 
					puzzle[row_index][x] = saved_line[x] 
					: puzzle[x][row_index] = saved_line[x];
			}

			if( !increment && !fault_source.empty() )
			{
				const auto found = std::find_if( fault_source.begin(), fault_source.end(),
					[&]( const std::pair< int, bool >& item )
				{
					return item.first == row_index && item.second == is_x_axis;
				} );

				if( found == fault_source.end() )
					return false;

				fault_source.clear( );
				new_faults.clear( );
			}
			else if( increment )
			{
				if( !puzzle[current_index][row_index].is_locked )
					new_faults.push_back( std::make_pair( current_index, !is_x_axis ) );
			}

			// Increment the spaces
			if( !IncrementSpaces( spaces, current_total, row_counter < 2 ? row_counter : row_counter - 1 ) )
			{				
				//std::cout << "Failed to increment spaces for line: " << row_index << ( is_x_axis ? " Horizontal" : " Vertical" ) << std::endl;
				fault_source = std::move( new_faults );
				return false;
			}
		}
		else
		{
			// Damn son we completed it??!?
			std::cout << "Must be complete?!" << std::endl;
			return true;
		}
	}

	// Shouldn't get here
	assert( false );
	return false;
}

int main( )
{
	Initialise( );

	std::vector< LineInfo > totals;

	// Find the lengths of the hints
	for( int i = 24; i >= 0; i-- )
	{
		int iTotalX = ( int )x_values[i].size( ) - 1;
		int iTotalY = ( int )y_values[i].size( ) - 1;

		for( unsigned x = 0; x < x_values[i].size( ); ++x )
			iTotalX += x_values[i][x];

		for( unsigned y = 0; y < y_values[i].size( ); ++y )
			iTotalY += y_values[i][y];

		totals.push_back( std::make_tuple( iTotalX, i, true ) );
		totals.push_back( std::make_tuple( iTotalY, i, false ) );
	}

	// Sort them
	std::sort( totals.begin( ), totals.end( ),
		[]( const LineInfo& item_a, const LineInfo& item_b )
	{
		return std::get< 0 >( item_a ) > std::get< 0 >( item_b );
	} );

	// Solve for every line
	std::vector< std::pair< int, bool > > faults;
	const bool solved = ProcessLine( totals, 0, faults );

	int i;
	std::cin >> i;
	return 0;
}