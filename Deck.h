#pragma once
#include<iostream>
#include"PileofCards.h"
#include"PlayingCard.h"
using namespace std;

class Deck
{
private:
	PlayingCard* deck[52];
	int size;
public:
	Deck();
	int getSize();
	bool IsEmpty();
	PlayingCard Remove(int i);
	~Deck();

};

