// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::SetupGame()
{
  PrintLine(TEXT("Welcome Message"));

  HiddenWord = TEXT("cakes");
  int32 SizeHiddenWord = HiddenWord.Len();
  Lives = SizeHiddenWord;
  bGameOver = false;

  PrintLine(FString::Printf(TEXT("Guest the %d letter word"), SizeHiddenWord));
  PrintLine(FString::Printf(TEXT("You have %d lives"), Lives));
  PrintLine(TEXT("Type something then press enter"));
}

void UBullCowCartridge::EndGame()
{
  PrintLine(TEXT("Press enter to play again"));
  bGameOver = true;
}

void UBullCowCartridge::BeginPlay() // When the game starts
{
  Super::BeginPlay();
  SetupGame();    
}

void UBullCowCartridge::ProcessGuess(FString Guess) 
{
  if(Guess == HiddenWord) {
    PrintLine(TEXT("you have won!!!!!"));
    EndGame();
    return;
  } 

  int32 SizeHiddenWord = HiddenWord.Len();
  --Lives;

  if(Lives > 0) {
    
    if(Guess.Len() != SizeHiddenWord) {
      PrintLine(FString::Printf(TEXT("the hidden word has %d letters!!!!!"), SizeHiddenWord)); 
    }

    else if(!IsIsogram(Guess)) {
      PrintLine(TEXT("No repeating letter, guess another")); 
    }
    
    PrintLine(TEXT("Wrong choice!!!!!"));
    PrintLine(FString::Printf(TEXT("you have %d Lives!!!!!"), Lives));
    return;

  }

  PrintLine(TEXT("you have lost!!!!!"));
  EndGame();

}
  
void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
  if(bGameOver) {
    ClearScreen();
    SetupGame();
  }

  else {
    ProcessGuess(Input);
  }
}

bool UBullCowCartridge::IsIsogram(FString Guess) const
{

 const int32 size = Guess.Len();

  for(int32 i = 0; i < size; i++) {
    for(int32 comparasion = i + 1; comparasion < size; comparasion++) {
      if(i != comparasion && Guess[i] == Guess[comparasion]) {
        return false;
      }
    }
  }

  return true;
}