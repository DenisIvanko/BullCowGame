/**************************************************************************************
This is a console executable, that makes use of the BullCow class.
This acts as the view in a MVC pattern, and is responsible for all user interaction.
For game logic see the FBullCowGame class.
***************************************************************************************/


#include <iostream>
#include <string>
#include "FBullCowGame.h"
#include <vector>

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetGuess();
bool AskToPlayAgain();

FBullCowGame BCGame; // Instantiate a new game

// The entry point of the app
int main()
{
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);
	return 0; // Exit the application
}


// introduce the game
void PrintIntro()
{
	constexpr int32 WORD_LENGTH = 5;

	std::cout << "Welcome to Bulls and Cows, Nigga.\n";
	std::cout << "Can you guess the " << WORD_LENGTH;
	std::cout << " letter isogram i'm thinking of?\n";
	return;
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop for the number of turns asking for guesses
	// TODO change from FOR to WHILE loop once we are validating tries
	for (int32 count = 1; count <= MaxTries; count++)
	{
		FText Guess = GetGuess(); // TODO make loop check valid

		// submit valid guess to the game and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);

		// print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << std::endl;
		std::cout << std::endl;
	}
	// TODO add a game summary
}

FText GetGuess()
{
	int32 CurrentTry = BCGame.GetCurrentTry();
	// get a guess from the player
	FText Guess = "";
	std::cout << "\nTry " << CurrentTry <<". Just give me the guess, Nigga: ";
	getline(std::cin, Guess);
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "\nWanna another round, nigga? Yes or no?\n";
	FText Response = "";
	getline(std::cin, Response);

	return  (Response[0] == 'y') || (Response[0] == 'Y');
}

