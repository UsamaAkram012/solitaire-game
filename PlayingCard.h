#pragma once
#include<iostream>
#include<string>
#include"ConsoleFunctions.h"
using namespace std;

class PlayingCard
{
private:
	int rank; //integer 1 – 13
	int suit; //integer 0 – 3
	char color; // red or black - ‘b’ for black , ‘r’ for red
	bool faceUp; //tells if a card is face up or not
	bool top; //tells if a card is on top of a pile
public:
	static int const Heart, Club, Diamond, Spade;
	PlayingCard(int rank = 1, int suit = 0);
	void display(int row, int col);
	bool isFaceUp(); //retunrs value of faceUp
	void setFaceUp(bool); //sets value of faceUp
	bool isTop(); //retunrs value of top
	void setTop(bool); //sets value of top
	int getSuit(); //getter for suit value
	int getRank(); //getter for rank value
	char getColor(); //getter for color value
};

