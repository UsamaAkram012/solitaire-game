#include<iostream>
#include"PlayingCard.h"
#include"ConsoleFunctions.h"
#include"Solitaire.h"
int const PlayingCard::Diamond = 0;
int const PlayingCard::Heart = 1;
int const PlayingCard::Spade = 2;
int const PlayingCard::Club = 3;
using namespace std;
int main() {
	ConsoleFunctions cf;
	cf.SetColor(white, black);
	Solitaire S;
	S.Shuffle();
	S.dealToPlayingPiles();
	S.DisplayGame();
	S.Play();

	cf.SetCursorAt(0,50);
}