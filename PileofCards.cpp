#include "PileofCards.h"
PileofCards::PileofCards(int size) {
	this->size = size;
	pile = new PlayingCard[size];
	this->top = -1;
}
PileofCards::~PileofCards() {
	if(pile != NULL)
	delete pile;
}
PlayingCard PileofCards:: Peek() {
	return pile[top];
}
PlayingCard PileofCards:: Remove() {
	if (top != -1) {
		PlayingCard p=pile[top];
		top--;
		if (top != -1) {
			pile[top].setTop(true);
			pile[top].setFaceUp(true);
		}
		return p;
	}
}
void PileofCards::Add(PlayingCard & usa) {
	if (!(this->IsFull())) {
			if(top!=-1)
				pile[top].setTop(false);
			top++;
			pile[top] = usa;
			pile[top].setTop(true);
			
	}
}
bool PileofCards::IsEmpty() {
	if (top == -1)
		return true;
	else
		return false;
}
bool PileofCards::IsFull() {
	if (top ==size-1)
		return true;
	else
		return false;
}
int PileofCards::getTop() {
	return this->top;
}
void PileofCards::setStartPt(int x, int y) {
	this->startPt.x = x;
	this->startPt.y = y;  
}
point PileofCards::getStartPt() {
	return startPt;
}
void PileofCards::setEndPt(int x, int y) {
	this->endPt.x = x;
	this->endPt.y = y;
}
point PileofCards::getEndPt() {
	return endPt;
}
PileofCards& PileofCards::operator=(const PileofCards& poc) {
	if (&poc == this)
		return *this;
	*this = poc;
		return *this;
}
PlayingCard PileofCards::viewCard(int i) {
	return pile[i];
}
void PileofCards::SimpleDisplay(int var) {
	if (top == -1) {
		ConsoleFunctions cf;
		int x = startPt.x, y = startPt.y;
		cf.SetCursorAt(x,y);
		cf.SetColor(dark_green, dark_green);
		for (int j = 0; j < 6; j++) {
			for (int i = 0; i <= 8; i++) {
				cout << " ";
			}
			cf.SetCursorAt(x,++y);
		}
	}
	else {
		if (var == 1) {
			pile[top].setFaceUp(false);
		}
		pile[top].display(startPt.x, startPt.y);
		
	}


}
void PileofCards::CascadingDisplay(int index) {
	if (top == -1) {
		ConsoleFunctions cf;
		int x = startPt.x, y = startPt.y;
		cf.SetCursorAt(x,y);
		cf.SetColor(dark_green, dark_green);
		for (int j = 0; j < 6; j++) {
			for (int i = 0; i <= 8; i++) {
				cout << " ";
			}
			cf.SetCursorAt(x,++y);
		}
	}
	else {
		int x = startPt.x, y = startPt.y;
		for (int i = 0; i < top + 1; i++) {
			pile[i].display(x, y);
			y++;
		}
	}

}
