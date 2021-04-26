#pragma once

#include <string>
#include <array>
#include <vector>
#include <optional>
#include <map>
#include <memory>

class Boggle
{
public:
	// Picks a random set of letters automatically
	Boggle();

	// Pass in your own set of letters (string for row by row of letters)
	Boggle( const std::string& letters );

	// Pass in your own set of letters a (array of rows of letters)
	Boggle( const std::array< std::string, 4 >& letters );

	// Validates guess to see if it is a valid possibility based on the letters, returns true if valid
	bool MakeGuess( const std::string& guess, const bool store_guess = true );

	// Reset the guesses stored internally
	void ClearGuesses();

	// Reset the found answers stored internally
	void ClearFound();

	// Reset guesses & found answers
	void Reset();

	const std::string& GetLetters() const { return letters; }

	// Returns all guesses that have been made so far (guesses are in uppercase)
	const std::vector < std::string >& GetGuesses() const { return all_guesses; }

	// Returns all answers that have been found so far (answers are in uppercase)
	const std::vector< std::string >& GetFound() const { return correct_guesses; }

	// Returns all answers that have been found so far of a specific letter count (answers are in uppercase)
	std::vector< std::string > GetFoundByLetterCount( const int count ) const;

	// Returns all possible answers (answers are in uppercase)
	std::vector< std::string > GetAnswers() const;

	// Returns all possible answers for a specific letter count (answers are in uppercase)
	std::vector< std::string > GetAnswersByCount( const int count ) const;

	// Finds all possible answers and saves them into the stored found answers internally
	void Solve();

protected:
	struct WordTreeNode
	{
		std::optional< int > word_idx;
		std::optional< char > letter;
		std::map< char, std::shared_ptr< WordTreeNode > > children;
	};

	// Loads the English dictionary of words in the words vector, also constructs and populates the word_tree data structure for fast word checking traversal
	void LoadWords();

	// Each step takes the next letter c in guess and searches for each possible valid letter in the grid by checking:
	// - The letter matches
	// - Hasn't already visited this square
	// - The square is actually within 1 tile distance of the previous
	bool TryGuessRecurse( const std::string_view guess, const std::optional< int > prev_x, const std::optional< int > prev_y, const int visited ) const;

	// Recursive function which finds all possible valid answers by using brute force
	// - Traverse all squares and then each possible connected square until no more valid words exist for that path or we run out of valid paths
	void SolveInternal( std::vector< std::string >& answers_out, const int max_length = std::numeric_limits< int >::max() ) const;
	void SolveInternalRecurse( const WordTreeNode& current_node, const int depth, const int column, const int row, const int visited, const int max_length, std::vector< std::string >& answers_out ) const;

	// Helper function to get the letter based on the x, y position (because the letters are stored in a flat string internally)
	std::optional< char > GetLetter( const int column, const int row ) const;
	// Helper to get a unique flag based on the x, y position (so we can easily check previously visited nodes during iteration etc.) - These are just powers of 2
	int GetFlag( const int column, const int row ) const;

protected:
	// Everything internally is stored in uppercase
	std::string letters;
	std::vector< std::string > correct_guesses;
	std::vector< std::string > all_guesses;

	std::vector< std::string > words;
	WordTreeNode word_tree;
};