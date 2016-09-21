/**************************************************************************************
This is a console executable, that makes use of the BullCow class.
This acts as the view in a MVC pattern, and is responsible for all user interaction.
For game logic see the FBullCowGame class.
***************************************************************************************/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax Unreal friendly
using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();
int32 GetPlayersNumber();

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

void PrintIntro()
{
	std::cout << "\n\nWelcome to Bulls and Cows, Nigga.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the isogram i'm thinking of?\n";
	return;
}

// plays a single game to complition
void PlayGame()
{
	int32 PlayersNumber = GetPlayersNumber();
	BCGame.Reset(PlayersNumber);
	int32 MaxTries = BCGame.GetMaxTries();

	// loop asking for guesses while game 
	// is NOT won and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess(); 

		// submit valid guess to the game and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n";
	}
	PrintGameSummary();
	return;
}

// loop continually until user gives a valid guess
FText GetValidGuess() 
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "\nTry " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Just give me the guess: ";
		std::cin >> Guess;
				
		// check status and give feedback
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n";
			break;
		default:
			// assume the guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); // keep looping until we get no errors
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "\nWanna another round? Yes or no?\n";
	FText Response = "";
	std::cin >> Response;
	return  (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon()) {
		std::cout << "Great job, nigger! You tougher than you look!\n";
	}
	else {
		std::cout << "Better luck next time. \n";
	}
	return;
}

int32 GetPlayersNumber()
{
	int32 PlayersNumber;
	do {
		std::cout << "Choose the word length from 3 to 7\n";
		std::cin >> PlayersNumber;
		if ((PlayersNumber >= 3) && (PlayersNumber <= 7) && std::cin.get() == '\n') {
			return PlayersNumber;
		}
		else {
			std::cout << "Please, enter the correct number.\n\n";
			std::cin.clear();
			while (std::cin.get() != '\n');
		}
	} while (true);
}
