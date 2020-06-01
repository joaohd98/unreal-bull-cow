// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    PrintLine(TEXT("Welcome Message"));
    PrintLine(TEXT("Guess the 4 letter word")); //Magic number remove
    PrintLine(TEXT("Type something then press enter"));
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
  ClearScreen();
  FString HiddenWord = TEXT("cake"); //Move to outside this function

  if(Input == HiddenWord) {
    PrintLine("you have won!!!!!");  
  } else {
    PrintLine("you have lost!!!!!");  
  }
}