#pragma once

#include "FBullCowGame.h"
#include <map>

// to make syntax Unreal friendly
#define TMap std::map 

FBullCowGame::FBullCowGame() {} // default constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon;}

FString FBullCowGame::GetHiddenWord(int32 Number) const
{
	TMap<int32, FString> PlayersNumberToHiddenWord{ {3,"key"}, {4,"mine"}, {5,"manor"}, {6,"lumber"}, {7, "miracle"} };
	return PlayersNumberToHiddenWord[Number];
}

int32 FBullCowGame::GetMaxTries() const {
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,15}, {7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset(int32 PlayersNumber)
{
	const FString HIDDEN_WORD = GetHiddenWord(PlayersNumber); // This MUST be an isogram
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) // if the guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram; 
	}
	else if (!IsLowercase(Guess)) // if the guess isn't all lowercase
	{
		return EGuessStatus::Not_Lowercase; 
	}
	else if (Guess.length() != GetHiddenWordLength()) // if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else 
	{
		return EGuessStatus::OK;
	}
}

// receives a VALID guess and incriments turn number, and return counts
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming same guess as length

	// loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		// compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			// if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				if (MHWChar == GChar) { // if they are in the same place
					BullCowCount.Bulls++; // incriment bulls
				} 
				else {
					BullCowCount.Cows++; // must be a cow
				}
			
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) {
		bGameIsWon = true;
	} 
	else {
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const 
{ 
	// treat 0 and 1 letter word as isograms
	if (Word.length() <= 1) { return true; }

	TMap <char, bool> LetterSeen; // setup the map
	for (auto Letter : Word) // for all letters of the word
	{
		Letter = tolower(Letter); // handle mixed case
		if (LetterSeen[Letter]) { // if the letter is in the map
			return false; // we do NOT have an isogram
		} else {
			LetterSeen[Letter] = true; // add the letter to the map as seen
		}
	}
	return true; // for examples in cases where /0 is entered
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word) {
		if (!islower(Letter)) {
			return false;
		}
	}
	return true;
}
