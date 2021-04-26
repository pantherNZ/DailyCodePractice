#include "Boggle.h"

#include <iostream>

int main()
{
	Boggle boggle;
	const auto guess1 = boggle.MakeGuess( "guess" );

	const auto answers = boggle.GetAnswers();
	const auto guess2 = boggle.MakeGuess( answers[0] );
	const auto guess3 = boggle.MakeGuess( answers[0].substr( 1 ) );

	const auto length_5_answers = boggle.GetAnswersByCount( 5 );

	const auto& guesses = boggle.GetGuesses();
	boggle.Solve();


	int temp;
	std::cin >> temp;

	return 0;
}