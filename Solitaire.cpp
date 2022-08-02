#include "Solitaire.h"
Solitaire::Solitaire() {
	int size = 14;
			//waste
	waste = new PileofCards(52);
	this->waste->setStartPt(12, 1);    //  col,row
	this->waste->setEndPt(20, 6);		//  x , y
			//Stock
	stock = new PileofCards(52);
	this->stock->setStartPt(1, 1);   
	this->stock->setEndPt(9, 6);	
		
			//playing pile
	int  p_t = 1;
	for (int i = 0; i < 7; i++) {
		playingPile[i] = new PileofCards(size);
		size++;
		this->playingPile[i]->setStartPt(p_t, 16);
		p_t = p_t + 11;
	}
			//home
	int h_t = 34, h_t1 = 42;
	for (int i = 0; i < 4; i++) {
		home[i] = new PileofCards(13);
		this->home[i]->setStartPt(h_t, 1);
		this->home[i]->setEndPt(h_t1, 6);
		h_t = h_t + 11;
		h_t1 = h_t1 + 11;
	}
}
//-------------------------
void Solitaire::Shuffle() {
	int i;
	while (!deckofCards.IsEmpty())
	{
		i = rand() % deckofCards.getSize();
		PlayingCard c = deckofCards.Remove(i);
		c.setFaceUp(false);
		stock->Add(c);
	}
}
//-------------------------
void Solitaire::dealToPlayingPiles() {
	int row=21, col = 9;
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < i + 1; j++) {
			PlayingCard obj=stock->Remove();
			obj.setFaceUp(false);
			obj.setTop(false);
			if (j + 1 == i + 1) {
				obj.setFaceUp(true);
				obj.setTop(true);
				playingPile[i]->setEndPt(col, row);
				row += 1;
				col += 11;
			}
			playingPile[i]->Add(obj);
		}

	}
}
//-------------------------
void Solitaire::DisplayGame() {
	stock->SimpleDisplay(1);

	waste->SimpleDisplay(0);

	for (int i = 0; i < 7; i++) {
		playingPile[i]->CascadingDisplay(i);
	}

	for (int i = 0; i < 4; i++) {
		home[i]->SimpleDisplay(0);
	}
	
}
//-------------------------
Solitaire::~Solitaire() {
	if (stock != NULL)
		delete stock;
	if (waste != NULL)
		delete waste;
	for (int i = 0; i < 4; i++) {
		if (home[i] != NULL)
			delete home[i];
		home[i] = nullptr;
	}
	for (int i = 0; i < 7; i++) {
		if (playingPile[i] != NULL)
			delete playingPile[i];
		playingPile[i] = nullptr;
	}
}
//-------------------------
PileofCards* Solitaire::getClickedPile(point p, int& a, int& c) {
	if (p.y >= 1 && p.x >= 1 && p.y <= 6 && p.x <= 8)
		return stock;
	if (p.y >= 1 && p.x >= 12 && p.y <= 6 && p.x <= 18)
		return waste;
	for (int i = 0; i < 4; i++) {
		point hx=home[i]->getStartPt(), hy=home[i]->getEndPt();
		if (p.y >= hx.y && p.x >= hx.x && p.y <= hy.y && p.x <= hy.x) {
			a = i;
			return home[i];
		}
	}
	for (int i = 0; i < 7; i++)
	{

		point pt = playingPile[i]->getStartPt(), ptt = playingPile[i]->getEndPt();

		if (p.x >= pt.x && p.x <= ptt.x && p.y >= pt.y && p.y <= ptt.y)
		{
			pt = playingPile[i]->getStartPt(), ptt = playingPile[i]->getEndPt();
			int test = 0, up = playingPile[i]->getTop();
			for (int index = pt.y; index <= ptt.y; index++)
			{
				if (up == 0)
				{
					c = 0;
					break;
				}
				else if (up == test - 1)
				{
					c = up;
					break;
				}
				else if (index == p.y)
				{
					c = (index - pt.y);

					break;
				}
				test++;
			}
			a = i;
			return playingPile[i];
		}
	}
}
//-------------------------
point Solitaire::getClickedPoint() {
	ConsoleFunctions O1;
	bool flag = false;
	point p;
	while (flag == false)
	{
		O1.DetectEvent();
		if (O1.IsMouseLeftClickEvent(p))
		{
			flag = true;
		}
	}
	return p;
}
//-------------------------
void Solitaire::moveFromStock() {
	PlayingCard O1;
	O1 = stock->Remove();
	O1.setFaceUp(true);
	waste->Add(O1);
}
//-------------------------
void Solitaire::moveFromWasteToHome(int a) {
	PlayingCard O1;
	O1 = waste->Remove();
	O1.setFaceUp(true);
	home[a]->Add(O1);
}
//-------------------------
void Solitaire::moveFromWasteToPlayingPile(int a, int c) {
	PlayingCard O1;
	O1 = waste->Remove();
	O1.setFaceUp(true);
	playingPile[a]->Add(O1);
	if(playingPile[a]->getTop()!=-1)
		playingPile[a]->setEndPt(playingPile[a]->getEndPt().x, playingPile[a]->getEndPt().y+1);
}
//-------------------------
void Solitaire::moveFromPlayingPileToHome(int a, int b, int c) {
	PlayingCard O1;
	O1 = playingPile[a]->Remove();
	O1.setFaceUp(true);
	home[b]->Add(O1);
	point ppe = playingPile[a]->getEndPt();
	if (playingPile[a]->getTop() != -1)
		playingPile[a]->setEndPt(ppe.x, ppe.y-1);
}
//-------------------------
void Solitaire::moveFromPlayingPileToPlayingPile(int a, int b, int c1, int c2) {
	for (int i = c1; i <= playingPile[a]->getTop(); i++)
	{
		PlayingCard temp = playingPile[a]->viewCard(i);

		if (playingPile[a]->getTop() != -1)
			playingPile[a]->setEndPt(playingPile[a]->getEndPt().x, playingPile[a]->getEndPt().y - 1);

		temp.setFaceUp(true);
		playingPile[b]->Add(temp);

		if (playingPile[b]->getTop() != 0)
			playingPile[b]->setEndPt(playingPile[b]->getEndPt().x, playingPile[b]->getEndPt().y + 1);
	}

	for (int i = playingPile[a]->getTop(); i >= c1; i--)
	{

		PlayingCard temp2 = playingPile[a]->Remove();

	}
	if (playingPile[a]->getTop() == -1)
		playingPile[a]->setEndPt(22, playingPile[a]->getEndPt().y);
}
//-------------------------
void Solitaire::moveFromHomeToPlayingPile(int a, int b, int c) {
	PlayingCard O1;
	O1 = home[a]->Remove();
	O1.setFaceUp(true);
	playingPile[b]->Add(O1);
	if (playingPile[b]->getTop() != -1)
		playingPile[b]->setEndPt(playingPile[b]->getEndPt().x, playingPile[b]->getEndPt().y+1);
}
//-------------------------
void Solitaire::Play() {
	point pt; 
	int a = -1, b = -1, c = -1, won = 0;    //-1 -> playingpile ctor used
	PileofCards* pile;
	xyz:		//start
	pt = getClickedPoint();
	pile = getClickedPile(pt, a, c);
		//winning condition
	for (int i = 0; i < 4; i++) {
		if (home[i]->getTop() == 12)
			won++;
		if (won == 4)
			cout << "Congratulations....! You have won the game";
	}
		if (pile == waste) {
			int op=waste->getTop();
			if (waste->getTop() == -1) {
				DisplayGame();
				cf.SetCursorAt(7, 0);
				cout << "Not specific area is clicked.....Invalid Click ";
			}

			pt = getClickedPoint();
			pile = getClickedPile(pt, a, c);
			while (pile != home[a] && pile != playingPile[a]) {
				DisplayGame();
				cf.SetCursorAt(7, 0);
				cout << "Not specific area is clicked.....Invalid Click ";
				pt = getClickedPoint();
				pile = getClickedPile(pt, a, c);
			}

			if (pile == home[a]) {
				if (home[a]->getTop() != -1) {
					if (waste->viewCard(waste->getTop()).getSuit() != home[a]->viewCard(home[a]->getTop()).getSuit() || waste->viewCard(waste->getTop()).getRank() != home[a]->viewCard(home[a]->getTop()).getRank() + 1) {
						DisplayGame();
						cf.SetCursorAt(7, 0);
						cout << "Wrong move";
						goto xyz;
					}
					else
						moveFromWasteToHome(a);
				}

				else {
					if (waste->viewCard(op).getRank() != 1) {
						DisplayGame();
						cf.SetCursorAt(7, 0);
						cout << "Not specific area is clicked.....Invalid Click ";
					}
					else
						moveFromWasteToHome(a);
				}
			}
			else if (pile == playingPile[a]) {
				if (waste->viewCard(waste->getTop()).getColor() == playingPile[a]->viewCard(playingPile[a]->getTop()).getColor() || waste->viewCard(waste->getTop()).getRank()+1 !=playingPile[a]->viewCard(playingPile[a]->getTop()).getRank() && playingPile[a]->getTop()!=-1) {
					DisplayGame();
					cf.SetCursorAt(7, 0);
					cout << "Wrong move";
					goto xyz;
				}
				if (playingPile[a]->getTop() != c) {
					DisplayGame();
					cf.SetCursorAt(7, 0);
					cout << "Wrong move";
					goto xyz;
				}
				moveFromWasteToPlayingPile(a,c);
			}	
			DisplayGame();	
		}
		else if (pile == stock) {
			cf.SetCursorAt(7, 0);
			if (stock->getTop() == -1) {
				for (int i = waste->getTop(); i > -1; i--) {
					PlayingCard O1;
					O1 = waste->Remove();
					O1.setFaceUp(false);
					stock->Add(O1);
				}
			}
			else if (stock->getTop() != -1) {
				moveFromStock();
			}
			cf.clearConsole();
			DisplayGame();

		}
		else if (pile == playingPile[a]) {
			int d, e;
			if (playingPile[a]->getTop() == -1) {
				DisplayGame();
				cf.SetCursorAt(7, 0);
				cout << "Not specific area is clicked.....Invalid Click ";
			}

			pt = getClickedPoint();
			pile = getClickedPile(pt, d, e);
			if (pile == home[d]) {
				if (home[d]->getTop() != -1) {
					if (playingPile[a]->viewCard(playingPile[a]->getTop()).getSuit() != home[d]->viewCard(home[d]->getTop()).getSuit() || 
						playingPile[a]->viewCard(playingPile[a]->getTop()).getRank() != home[d]->viewCard(home[d]->getTop()).getRank() + 1) {
						DisplayGame();
						cf.SetCursorAt(7, 0);
						cout << "Wrong move";
					}
					else
						moveFromPlayingPileToHome(a, d, c);
				}

				else {
					if (playingPile[a]->Peek().getRank() != 1) {
						DisplayGame();
						cf.SetCursorAt(7, 0);
						cout << "Not specific area is clicked.....Invalid Click ";
					}
					else
						moveFromPlayingPileToHome(a, d, c);
				}
			}

			else if (pile == playingPile[d])
			{
				int f = playingPile[d]->getTop();
				if ((playingPile[a]->viewCard(c).getColor() == playingPile[d]->Peek().getColor() ||
					playingPile[a]->viewCard(c).getRank() + 1 != playingPile[d]->Peek().getRank()) && (f != -1))
				{

					cf.clearConsole();
					DisplayGame();
					cf.SetCursorAt(7, 0);
					cout << "Can't move this card....!" << endl;
					goto xyz;
				}
				while (f != e)
				{
					cf.clearConsole();
					DisplayGame();
					cf.SetCursorAt(7, 0);
					cout << "Can't move this card....!" << endl;
					pt = getClickedPoint();
					pile = getClickedPile(pt, a, c);
				}
				moveFromPlayingPileToPlayingPile(a, d, c, e);
			}
			cf.clearConsole();
			DisplayGame();

		}
		else if (pile == home[a]) {
			if (home[a]->getTop() != -1) {
				int var;
				pt = getClickedPoint();
				pile = getClickedPile(pt, var, c);
				if (home[a]->viewCard(home[a]->getTop()).getColor() == playingPile[var]->viewCard(playingPile[var]->getTop()).getColor() ||
					home[a]->viewCard(home[a]->getTop()).getRank() + 1 != playingPile[var]->viewCard(playingPile[var]->getTop()).getRank()
					&& playingPile[var]->getTop() != -1) {
					DisplayGame();
					cf.SetCursorAt(7, 0);
					cout << "Wrong move";
					goto xyz;
				}
				if (playingPile[var]->getTop() != c) {
					DisplayGame();
					cf.SetCursorAt(7, 0);
					cout << "Wrong move";
					goto xyz;
				}
				moveFromHomeToPlayingPile(a,var,c);
				DisplayGame();
			}
		}
		else {
			cf.SetCursorAt(7, 0);
			cout << "Not specific area is clicked.....Invalid Click ";
		}
		goto xyz;    //working as while loop
}
