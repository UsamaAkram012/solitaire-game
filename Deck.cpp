#include "Deck.h"

Deck::Deck() {
	size=52;
	int j = 0;
	for (int i = 1; i <= 13; i++)
	{
		deck[j] = new PlayingCard(i, PlayingCard::Spade);
		j++;
	}
	for (int i = 1; i <= 13; i++)
	{
		deck[j] = new PlayingCard(i, PlayingCard::Heart);
		j++;
	}
	for (int i = 1; i <= 13; i++)
	{
		deck[j] = new PlayingCard(i, PlayingCard::Diamond);
		j++;
	}
	for (int i = 1; i <= 13; i++)
	{
		deck[j] = new PlayingCard(i, PlayingCard::Club);
		j++;
	}
}
int Deck::getSize() {
	return size;
}
bool Deck::IsEmpty() {
	if (size == 0)
		return true;
	else
		return false;
}
PlayingCard Deck::Remove(int i) {
	PlayingCard* temp = deck[i];
	deck[i] = NULL;
	for (int j = i; j < size - 1; j++) {
		deck[j] = deck[j + 1];
		deck[j + 1] = NULL;
	}
	size--;
	return *temp;
}
Deck::~Deck() {
	for (int i = 0; i < 52; i++) {
		if (deck[i] != NULL)
			delete deck[i];
	}
}
