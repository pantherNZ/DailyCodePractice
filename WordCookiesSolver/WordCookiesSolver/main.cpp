#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <unordered_map>

int main( int argc, char* argv[] )
{
	std::vector< std::string > words;
	unsigned min_length = 2;
	unsigned max_length = 9999;

	// Arguments
	if( argc > 2 )
	{
		for( int i = 1; i < argc; ++i )
		{
			if( std::string( argv[i] ) == "-minlength" && argc > i + 1 )
			{
				++i;
				min_length = ( unsigned )atoi( argv[i] );
			}
			else if( std::string( argv[i] ) == "-maxlength" && argc > i + 1 )
			{
				++i;
				max_length = ( unsigned )atoi( argv[i] );
			}
		}
	}

	{
		std::ifstream input_sorted( "Words_Sorted.txt" );
		std::string temp_str;

		if( input_sorted.is_open( ) )
		{
			// Read in file
			while( std::getline( input_sorted, temp_str ) )
				words.push_back( temp_str );
		}
		else
		{
			std::ifstream input( "Words_Corncob.txt" );

			// Read in file
			while( std::getline( input, temp_str ) )
			{
				if( temp_str.length( ) <= 8 && temp_str.length( ) > 1 )
				{
					const auto insert_pos = std::upper_bound( words.begin( ), words.end( ), temp_str, []( const std::string& a, const std::string& b )
					{
						return a.length( ) < b.length( );
					} );

					words.insert( insert_pos, temp_str );
				}
			}

			// Output (saved in length order)
			{
				std::ofstream output( "Words_Sorted.txt" );

				for( auto& word : words )
					output << word << "\n";

				std::cout << "Words have been sorted into \"Words_Sorted.txt\"..." << "\n\n";
			}
		}
	}

	while( true )
	{
		// Input letters
		std::string letters;
		std::cout << "Input letters: " << "\n";
		std::cin >> letters;
		std::cout << "\n" << "Results: " << "\n";

		auto length = letters.length( );

		// Search for anagrams
		for( auto& word : words )
		{
			if( word.length( ) > length || word.length( ) > max_length )
				break;

			if( word.length( ) < min_length  )
				continue;

			std::unordered_map<char, int> mapTable;
			bool valid = true;

			for( char c : letters )
				mapTable[c] = mapTable.find( c ) != mapTable.end( ) ? mapTable[c] + 1 : 1;

			for( char c : word )
			{
				if( mapTable.find( c ) != mapTable.end( ) )
				{
					mapTable[c] = mapTable[c] - 1;

					if( mapTable[c] < 0 )
						valid = false;
				}
				else
					valid = false;

				if( !valid )
					break;
			}

			if( valid )
				std::cout << word << "\n";;
		}

		std::cout << "\n";;
	}
}