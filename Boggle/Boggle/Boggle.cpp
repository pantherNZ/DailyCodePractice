#include "Boggle.h"

#include <algorithm>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <limits>

Boggle::Boggle()
{
	letters.reserve( 16 );
	for( int i = 0; i < 16; ++i )
		letters.push_back( 'A' + rand() % 26 );

	LoadWords();
}

Boggle::Boggle( const std::string& _letters )
{
	if( _letters.size() != 16U )
		throw std::exception( "Invalid letters for boggle setup (must be total length 16 for 4 rows of 4 letters)" );

	std::transform( std::begin( _letters ), std::end( _letters ), std::begin( letters ), std::toupper );

	LoadWords();
}

Boggle::Boggle( const std::array< std::string, 4 >& _letters )
{
	letters.reserve( 16 );
	for( const auto& row : _letters )
	{
		if( row.size() != 4U )
			throw std::exception( "Invalid letters for boggle setup (must be array for 4 rows each of 4 letters)" );

		std::transform( std::begin( row ), std::end( row ), std::end( letters ), std::toupper );
	}
	 
	LoadWords();
}

void Boggle::LoadWords()
{
	std::ifstream input( "Words_Corncob.txt" );
	std::string temp_str;
	words.reserve( 60000 );

	// Read in file
	while( std::getline( input, temp_str ) )
	{
		if( temp_str.length() <= 8 && temp_str.length() > 1 )
		{
			std::transform( std::begin( temp_str ), std::end( temp_str ), std::begin( temp_str ), std::toupper );

			// Sort input strings (not currently needed as the words data file is sorted)
			//const auto insert_pos = std::upper_bound( words.begin(), words.end(), temp_str, []( const std::string& a, const std::string& b )
			//	{
			//		return a.length() < b.length();
			//	} );
			//
			//words.insert( insert_pos, temp_str );
			words.push_back( temp_str );
		}
	}

	// Construct tree data structure used for fast answer searching and validation
	for( int i = 0; i < ( int )words.size(); ++i )
	{
		const auto& word = words[i];
		auto* current = &word_tree;

		for( int j = 0; j < ( int )word.size(); ++j )
		{
			auto& node = ( *current ).children[word[j]];
			if( !node )
			{
				node = std::make_shared< WordTreeNode >();
				node->letter = word[j];
			}

			if( j == ( int )word.size() - 1 )
				node->word_idx = i;

			current = node.get();
		}
	}
}

bool Boggle::MakeGuess( const std::string& guess, const bool store_guess /*= true*/ )
{
	if( guess.empty() )
		return false;
	
	// Upper case the guess
	std::string guess_upper;
	guess_upper.resize( guess.size() );
	std::transform( std::begin( guess ), std::end( guess ), std::begin( guess_upper ), std::toupper );

	if( store_guess )
		all_guesses.push_back( guess_upper );

	// Firstly check that the input guess is actually a valid word
	//WordTreeNode* current_node = &word_tree;
	//
	//for( const auto c : guess_upper )
	//{
	//	const auto found = current_node->children.find( c );
	//	if( found == current_node->children.end() )
	//		return false;
	//	current_node = found->second.get();
	//}
	//
	//bool valid = false;
	//if( current_node->word_idx )
	//	if( words[*current_node->word_idx] == guess_upper )
	//		valid = true;
	//
	//if( !valid )
	//	return false;
	if( std::find( std::begin( words ), std::end( words ), guess_upper ) == std::end( words ) )
		return false;

	// Secondly check the guess fits onto the boggle board 
	if( !TryGuessRecurse( guess_upper, std::nullopt, std::nullopt, 0 ) )
		return false;

	correct_guesses.push_back( guess_upper );

	return true;
}

bool Boggle::TryGuessRecurse( const std::string_view guess, const std::optional< int > prev_x, const std::optional< int > prev_y, const int visited ) const
{
	for( const auto c : guess )
	{
		size_t found_letter_idx = 0;
		while( true )
		{
			// Find the next valid occurrence of the searched for letter (c) in the letters
			found_letter_idx = letters.find( c, found_letter_idx );
			if( found_letter_idx == std::string::npos )
				return false;

			const auto x = ( int )found_letter_idx % 4;
			const auto y = ( int )found_letter_idx / 4;
			++found_letter_idx;
			const auto flag = GetFlag( x, y );

			// Check we haven't already visited this square
			if( visited & flag )
				continue;

			// Check the new square is within 1 tile distance from the previous
			if( prev_x && ( abs( x - *prev_x ) > 1 || abs( y - *prev_y ) > 1 ) )
				continue;

			// Last letter, then we are done
			if( guess.size() == 1 )
				return true;

			// Otherwise, continue searching with the rest of the guess
			if( TryGuessRecurse( guess.substr( 1 ), x, y, visited | flag ) )
				return true;
		}
	}

	return false;
}

void Boggle::ClearGuesses()
{
	all_guesses.clear();
}

void Boggle::ClearFound()
{
	correct_guesses.clear();
}

void Boggle::Reset()
{
	ClearGuesses();
	ClearFound();
}

std::vector< std::string > Boggle::GetFoundByLetterCount( const int count ) const
{
	if( count <= 1 )
		return {};

	std::vector< std::string > found_by_count;
	found_by_count.reserve( correct_guesses.size() );

	for( const auto& guess : correct_guesses )
		if( guess.size() == count )
			found_by_count.push_back( guess );

	return found_by_count;
}

std::vector< std::string > Boggle::GetAnswers() const
{
	std::vector< std::string > answers;
	SolveInternal( answers );
	return answers;
}

std::vector< std::string > Boggle::GetAnswersByCount( const int count ) const
{
	std::vector< std::string > answers;
	SolveInternal( answers, count );

	answers.erase( std::remove_if( std::begin( answers ), std::end( answers ), [&count]( const auto& str )
		{
			return ( int )str.length() != count;
		} ) );

	return answers;
}

void Boggle::Solve()
{
	correct_guesses.clear();
	SolveInternal( correct_guesses );
}

void Boggle::SolveInternal( std::vector< std::string >& answers_out, const int max_length ) const
{
	for( int i = 0; i < ( int )letters.size(); ++i )
	{
		const auto found = word_tree.children.find( letters[i] );
		if( found != word_tree.children.end() )
		{
			const auto x = i % 4;
			const auto y = i / 4;
			SolveInternalRecurse( *found->second, 0, x, y, GetFlag( x, y ), max_length, answers_out );
		}
	}
}

void Boggle::SolveInternalRecurse( const WordTreeNode& current_node, const int depth, const int column, const int row, const int visited, const int max_length, std::vector< std::string >& answers_out ) const
{
	// Depth checker used to eliminate scenarios where we don't care about words greater than a certain length
	if( depth > max_length )
		return;

	// We have found a node which represents a valid word, save it
	if( current_node.word_idx )
		answers_out.push_back( words[*current_node.word_idx] );

	// No more options from here, bail
	if( current_node.children.empty() )
		return;

	// Continue searching in directions
	for( int y = ( row > 0 ? row - 1 : row ); y <= ( row < 3 ? row + 1 : row ); ++y )
	{
		for( int x = ( column > 0 ? column - 1 : column ); x <= ( column < 3 ? column + 1 : column ); ++x )
		{
			if( x == column && y == row )
				continue;

			// Check if we have already visited the target square
			const auto flag = GetFlag( x, y );
			if( visited & flag )
				continue;

			// Check the current node has a child node which matches the target letter
			// If so, we recurse by doing it all again from that node (checking for word matches, searching neighbours)
			const auto found = current_node.children.find( *GetLetter( x, y ) );
			if( found != current_node.children.end() )
				SolveInternalRecurse( *found->second, depth + 1, x, y, visited | flag, max_length, answers_out );
		}
	}
}

std::optional< char > Boggle::GetLetter( const int column, const int row ) const
{
	if( row < 0 || row >= 4 || column < 0 || column >= 4 )
		return {};
	return letters[row * 4 + column];
}

int Boggle::GetFlag( const int column, const int row ) const
{
	return 1 << ( row * 4 + column );
}

