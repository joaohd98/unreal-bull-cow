// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordsList.h"
#include "Math/UnrealMathUtility.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
  Super::BeginPlay();
  GetValidWords(HiddenWordsList);
  SetupGame();
}

void UBullCowCartridge::GetValidWords(const TArray<FString>& words)  {
  // const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordsLists/HiddenWordList.txt");
  // FFileHelper::LoadFileToStringArrayWithPredicate(WordList, *WordListPath, [this](const FString Word) { 
  //   return IsIsogram(Word); 
  // });
  // for(int32 i = 0; i < HiddenWordsList.Num(); i++) {
  //   FString Word = HiddenWordsList[i];
  //   if(IsIsogram(Word)) {
  //     WordList.Emplace(Word);
  //   }
  // }

  for(FString Word: words) {
    if(Word.Len() > 4 && IsIsogram(*Word)) {
      WordList.Emplace(Word);
    }
  }
}

void UBullCowCartridge::SetupGame()
{
  PrintLine(TEXT("Welcome Message"));

  HiddenWord = WordList[FMath::RandRange(0, WordList.Num())];
  int32 SizeHiddenWord = HiddenWord.Len();
  Lives = SizeHiddenWord;
  bGameOver = false;

  PrintLine(FString::Printf(TEXT("The word is %s"), *HiddenWord));
  PrintLine(FString::Printf(TEXT("The number of possible words is %d "), WordList.Num()));
  PrintLine(FString::Printf(TEXT("Guest the %d letter word"), SizeHiddenWord));
  PrintLine(FString::Printf(TEXT("You have %d lives"), Lives));
  PrintLine(TEXT("Type something then press enter"));
}

void UBullCowCartridge::EndGame()
{
  PrintLine(TEXT("Press enter to play again"));
  bGameOver = true;
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
  if(bGameOver) {
    ClearScreen();
    SetupGame();
  }

  else {
    ProcessGuess(*Input);
  }
}

void UBullCowCartridge::ProcessGuess(const FString& Guess) 
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

    else if(!IsIsogram(*Guess)) {
      PrintLine(TEXT("No repeating letter, guess another")); 
    }
    
    FBullCowCount count = GetBullCows(Guess);

    PrintLine(TEXT("Wrong choice!!!!!"));
    PrintLine(FString::Printf(TEXT("you have %i bulls and %i cows!!!!!"), count.BullCount, count.CowCount));
    PrintLine(FString::Printf(TEXT("you have %d Lives!!!!!"), Lives));
    return;

  }

  PrintLine(TEXT("you have lost!!!!!"));
  EndGame();

}

FBullCowCount UBullCowCartridge::GetBullCows(const FString& Guess) const {
    FBullCowCount count;

  for(int32 i = 0; i < Guess.Len(); i++) {
    if(Guess[i] == HiddenWord[i]) {
      count.BullCount++;
      continue;
    }

    for(int32 j = 0; j < HiddenWord.Len(); j++) {
      if(i != j && Guess[i] == HiddenWord[j]) {
        count.CowCount++;
        break;
      }
    }
  }

  return count;
}

bool UBullCowCartridge::IsIsogram(const FString& Guess) const
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