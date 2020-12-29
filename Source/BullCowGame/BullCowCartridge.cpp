// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"


void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
  
    SetupGame();

    PrintLine(TEXT("The Hidden Word is: %s"), *HiddenWord); // Debug line

}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{

    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else //else Checking PlayerGuess
    {
        ProcessGuess(Input);        
    }


     //PlayAgain or Quit

}

void UBullCowCartridge::SetupGame()
{
    // Welcome to the game
    PrintLine(TEXT("Welcome to the Bull Cow Game!"));

    HiddenWord = TEXT("cars");   
    Lives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("Try to guess the %i letter word."), HiddenWord.Len());
    PrintLine(TEXT("You have %i lives."), Lives);
    PrintLine(TEXT("Type in your guess."));

    //const TCHAR HW[] = TEXT("plums");
    //PrintLine(TEXT("Character 1 of the hidden word is: %c"), HiddenWord[0]);
    //PrintLine(TEXT("Character 4 of the HW array is: %c"), HW[3]);

    IsIsogram(HiddenWord);


}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Press enter to play again.")); //Prompt to PlayAgain, Press Enter To Play Again?
}

void UBullCowCartridge::ProcessGuess(FString Guess) //Check user input
{
    PrintLine(TEXT("You guessed %s"), *Guess);

    if (Guess == HiddenWord)
    {
        ClearScreen();
        PrintLine(TEXT("You are correct! You Win... Yay!"));
        EndGame();
        return;
    }
    
    if (Guess.Len() != HiddenWord.Len())
    {
        ClearScreen();
        PrintLine(TEXT("It needs to be a %i letter word. \nYou have %i lives remaining."), HiddenWord.Len(), Lives); //Check right number of characters - Promt to Guess Again - Show Lives Left
        return;
    }

    //Check if isogram (How do we check ?)
    if (!IsIsogram(Guess))
    {
        PrintLine(TEXT("No repeating letters, guess again"));
        return;
    }

    if (Guess != HiddenWord && Guess.Len() == HiddenWord.Len())
    {
        PrintLine(TEXT("Wrong word! Try again! \nYou have lost a life."), --Lives); //Remove a life - Promt to Guess Again
        PrintLine(TEXT("You have %i lives remaining."), Lives); //Show Lives Left
    }

    if (Lives <= 0) //Check if Lives <= 0
    {
        ClearScreen();
        PrintLine(TEXT("Sorry, You lost!")); //If No live Remain Show GameOver and HiddenWord in EndGame()
        PrintLine(TEXT("The word was %s"), *HiddenWord);
        EndGame();
    }
    return;
}

bool UBullCowCartridge::IsIsogram(FString Word) const
{
    //for each letter.
    //Start at element [0].
    //Compare against the next letter.
    //Until we reach [Word.Len() -1].
    //if any letters are the same return false.

    for (int32 Index = 0; Index < Word.Len(); Index++)
    {
        PrintLine(TEXT("%c"), Word[Index]);
    }

    return true;
}