#include "PlayingCard.h"

PlayingCard::PlayingCard(int rank,int suit) {
		this->rank = rank;
		this->faceUp = true;
		this->top = true;
	this->suit = suit;
	if (this->suit == 0 || this->suit == 1)
		this->color = 'r';
	else if (this->suit == 2 || this->suit == 3)
		this->color = 'b';
	else
		cout << "Invalid Suit...!";
}
void PlayingCard::display(int col, int row) {
	ConsoleFunctions cf;
	char logo = '\0';
	cf.setConsoleTitle("Playing Cards");
	if (this->color == 'r')
		cf.SetColor(red, white);
	if (this->color == 'b')
		cf.SetColor(black, white);
	if (this->suit == 0) logo = '\4';
	if (this->suit == 1) logo = '\3';
	if (this->suit == 2) logo = '\6';
	if (this->suit == 3) logo = '\5';
	cf.SetCursorAt(col, row);
	if (this->isFaceUp() == false && this->isTop() == false) {
		cf.SetColor(gray, dark_red);
		for (int j = 0; j < 2; j++) {
			for (int i = 0; i <= 8; i++) {
				if (j == 0)
					cout << "_";
				else
					cout << " ";
			}
			cf.SetCursorAt(col, ++row);
		}
	}
	if (this->isFaceUp() && this->isTop() == false) {
		if (rank < 11 && rank != 1) cout << rank;
		else if (rank == 1)  cout << "A";
		else if (rank == 11) cout << "J";
		else if (rank == 12) cout << "Q";
		else if (rank == 13) cout << "K";
		cout << logo;
		int start_pt = 1;
		if (rank == 10)
			start_pt = 2;
		for (int j = 0; j < 2; j++) {
			for (int i = start_pt; i < 8; i++)
				if (j == 1) {
					cf.SetColor(gray, white);
					cout << "_";
				}
				else cout << " ";
			if (j > 0 && j < 5) {
				if (rank == 10 && j == 1) {
					cf.SetColor(gray, white);
					cout << "___";
				}
				else {
					cf.SetColor(gray, white);
					cout << "  ";
				}
			}
			cout << endl;
			cf.SetCursorAt(col, ++row);
		}
	}
	if (this->isFaceUp() && this->isTop()) {
		if (rank < 11 && rank != 1) cout << rank;
		else if (rank == 1)  cout << "A";
		else if (rank == 11) cout << "J";
		else if (rank == 12) cout << "Q";
		else if (rank == 13) cout << "K";
		cout << logo;
		int start_pt = 1;
		if (rank == 10)
			start_pt = 2;
		for (int j = 0; j < 6; j++) {
			for (int i = start_pt; i < 8; i++) {
				cout << " ";
				if (j == 5 && i == 7) {
					cout << logo;
					if (rank < 11 && rank != 1) cout << rank;
					else if (rank == 1)  cout << "A";
					else if (rank == 11) cout << "J";
					else if (rank == 12) cout << "Q";
					else if (rank == 13) cout << "K";
				}
			}
			if (j > 0 && j < 5) {
				if (rank == 10) cout << "   ";
				else cout << "  ";
			}
			cout << endl;
			cf.SetCursorAt(col, ++row);
		}
	}
	if (this->isFaceUp()==false && this->isTop()) {
		cf.SetColor(gray, dark_red);
		for (int j = 0; j < 6; j++) {
			for (int i = 0; i <= 8; i++)
				cout << " ";
			cf.SetCursorAt(col, ++row);
		}
	}
}
bool PlayingCard::isFaceUp() {
	if (this->faceUp == true)
		return true;
	else
		return false;
}
void PlayingCard::setFaceUp(bool face) {
	if (face == true) this->faceUp = true;
	else this->faceUp = false;
}
bool PlayingCard::isTop() {
	if (this->top == true) return true;
	else return false;
}
void PlayingCard::setTop(bool top) {
	if (top == true) this->top = true;
	else this->top = false;
}
int PlayingCard::getSuit(){
	return this->suit;
}
int PlayingCard::getRank(){
	return this->rank;
}
char PlayingCard::getColor(){
	return this->color;
}

