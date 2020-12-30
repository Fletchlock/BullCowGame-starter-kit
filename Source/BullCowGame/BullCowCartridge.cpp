// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "Containers/UnrealString.h"


// Assign path to HiddenWordList.txt and create String Array from the .txt file called Isograms using a lambda to return length and isogram
// Run SetupGame()
void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWordList.txt");
    FFileHelper::LoadFileToStringArrayWithPredicate(Isograms, *WordListPath, [](const FString& Word)
        {
            return Word.Len() > 3 && Word.Len() < 8 && IsIsogram(Word);
        });

    SetupGame();
}

// Checks what the player input on Enter key pressed
// If gave was over, clear screen and start new game
// Else run ProcessGuess(Input) with Input passed in order to compare it to the hidden word
void UBullCowCartridge::OnInput(const FString& PlayerInput)
{
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else
    {
        ProcessGuess(PlayerInput);        
    }
     //PlayAgain or Quit
}

// Set up the game with instructions and define the hidden word as well as number of lives (guesses?)
// Set game over boolian to false
void UBullCowCartridge::SetupGame()
{
    PrintLine(TEXT("Welcome to the Bull Cow Game!"));
    
    const int32 Rnd = FMath::RandHelper(Isograms.Num());
    HiddenWord = Isograms[Rnd];
    Lives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("Try to guess the %i letter word."), HiddenWord.Len());
    PrintLine(TEXT("You have %i lives."), Lives);
    PrintLine(TEXT("Type in your guess."));
    PrintLine(TEXT("The Hidden Word is: %s."), *HiddenWord); // Debug line
}

// Set game over boolian to true
// Prompt to play again
void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine(TEXT("Press enter to play again."));
}

// Check user input
// Run comparisons to check player input Guess against the hidden word
// Check for length of word as well as if IsIsogram(Guess) with the Guess passed to the function (Guess is Input)
// See comments within function for more details
void UBullCowCartridge::ProcessGuess(const FString& Guess)
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

    if (!IsIsogram(Guess)) //Check if isogram
    {
        PrintLine(TEXT("No repeating letters, guess again!"));
        return;
    }

    if (Guess != HiddenWord && Guess.Len() == HiddenWord.Len()) //True if guess does not equal hidden word AND equals length
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

// Loops through the Word array declared in BeginPlay() and checks each index looking for the same letter
bool UBullCowCartridge::IsIsogram(const FString& Word)
{
    for (int32 Index = 0; Index < Word.Len(); Index++)
    {
        for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++)
        {
            if (Word[Index] == Word[Comparison])
            {
                return false;
            }
        }
    }

    return true;
}

