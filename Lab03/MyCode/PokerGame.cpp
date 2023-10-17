#include "PokerGame.h"

PokerGame::PokerGame() {
	playerCards.reserve(5);
}

void PokerGame::distribute(bool usedCards[52]) {
	int i = 0;
	while (i < 5){
		srand(time(NULL));
		int x = (int)rand() % 52;
		if (!usedCards[x]){
			playerCards.push_back(x);
			i++;
			usedCards[x] = true;
		}
	}
}

void PokerGame::set(vector<int> cards) {
	for (int i = 0; i < 5; i++)
		playerCards.push_back(cards[i]);
}

void PokerGame::printCards() {
	cout << "Player cards:" << endl;
	for (int i = 0; i < 5; i++) {
		switch (playerCards[i] / 13){
		case 0:
			cout << "C" << playerCards[i] % 13 + 1 << " ";
			break;
		case 1:
			cout << "D" << playerCards[i] % 13 + 1 << " ";
			break;
		case 2:
			cout << "H" << playerCards[i] % 13 + 1 << " ";
			break;
		case 3:
			cout << "S" << playerCards[i] % 13 + 1 << " ";
			break;
		default:
			break;
		}
	}
	cout << endl;
}

void PokerGame::sortCards() {
	for (int i = 1; i < 5; i++) {
		for (int j = 0; j < 5 - i; j++) {
			if ((playerCards[j] % 13) > (playerCards[j + 1] % 13)) {
				int temp;
				temp = playerCards[j];
				playerCards[j] = playerCards[j + 1];
				playerCards[j + 1] = temp;
			}
			else if ((playerCards[j] % 13) == (playerCards[j + 1] % 13)) {
				if ((playerCards[j] / 13) > (playerCards[j + 1] / 13)) {
					int temp;
					temp = playerCards[j];
					playerCards[j] = playerCards[j + 1];
					playerCards[j + 1] = temp;
				}
			}
		}
	}
}
void PokerGame::setcardNumber() {
	cardNumber.reserve(5);
	for (int i = 0; i < 5; i++)
		cardNumber.push_back(playerCards[i] % 13 + 1);
}

void PokerGame::evaluate() {
	sortCards();
	setcardNumber();
	if (this->isStraight() && this->isFlush()) {
		type = StraightFlush;
	}
	else if (this->isFourOfKind()) {
		type = FourOfKind;
	}
	else if (this->isFullHouse()) {
		type = FullHouse;
	}
	else if (this->isFlush()) {
		type = Flush;
	}
	else if (this->isStraight()) {
		type = Straight;
	}
	else if (this->isThreeOfKind()) {
		type = ThreeOfKind;
	}
	else if (this->isTwoPairs()) {
		type = TwoPairs;
	}
	else if (this->isOnePair()) {
		type = OnePair;
	}
	else {
		type = HighCard;
		maxNumber = playerCards[4];
	}
}

int PokerGame::getType() {
	return type;
}

int PokerGame::getMaxNumber() {
	return maxNumber;
}

void PokerGame::compare(int type_, int maxNumber_) {
	if (this->getType() > type_)
		cout << "Player1 win" << endl;
	else if (this->getType() == type_) {
		if (this->getMaxNumber() % 13 > maxNumber_ % 13)
			cout << "Player1 win" << endl;
		else if (this->getMaxNumber() % 13 == maxNumber_ % 13)
		{
			this->getMaxNumber() / 13 > maxNumber_ / 13 ? cout << "Player1 win" << endl : cout << "Player2 win" << endl;
		}
		else
			cout << "Player2 win" << endl;
	}
	else
		cout << "Player2 win" << endl;
}

bool PokerGame::isStraight() {
	int flag = 1;
	for (int i = 0; i < 4; i++) {
		if ((cardNumber[i] + 1) != (cardNumber[i + 1]))
			flag = 0;
	}
	if (flag)
		maxNumber = playerCards[4];
	return (flag==1);
}

bool PokerGame::isFlush() {
	int flag = 1;
	for (int i = 0; i < 4; i++) {
		if ((playerCards[i] / 13) != (playerCards[i + 1] / 13))
			flag = 0;
	}
	if (flag)
		maxNumber = playerCards[4];
	return (flag == 1);
}

bool PokerGame::isFourOfKind() {
	if (count(cardNumber.begin(), cardNumber.end(), cardNumber[0]) == 4 && count(cardNumber.begin(), cardNumber.end(), cardNumber[4]) == 1) {
		maxNumber = playerCards[3];
		return true;
	}
	else if (count(cardNumber.begin(), cardNumber.end(), cardNumber[1]) == 4 && count(cardNumber.begin(), cardNumber.end(), cardNumber[0]) == 1) {
		maxNumber = playerCards[4];
		return true;
	}
	else
		return false;
}

bool PokerGame::isFullHouse() {
	if (cardNumber[0] == cardNumber[1] && cardNumber[1] == cardNumber[2] && cardNumber[3] == cardNumber[4]) {
		maxNumber = playerCards[2];
		return true;
	}
	else if (cardNumber[2] == cardNumber[3] && cardNumber[3] == cardNumber[4] && cardNumber[0] == cardNumber[1]) {
		maxNumber = playerCards[4];
		return true;
	}
	else
		return false;
}

bool PokerGame::isThreeOfKind() {
	if (count(cardNumber.begin(), cardNumber.end(), cardNumber[0]) == 1 && count(cardNumber.begin(), cardNumber.end(), cardNumber[1]) == 1 && count(cardNumber.begin(), cardNumber.end(), cardNumber[2]) == 3) { // 1 1 3
		maxNumber = playerCards[4];
		return true;
	}
	else if (count(cardNumber.begin(), cardNumber.end(), cardNumber[0]) == 1 && count(cardNumber.begin(), cardNumber.end(), cardNumber[1]) == 3 && count(cardNumber.begin(), cardNumber.end(), cardNumber[4]) == 1) { // 1 3 1
		maxNumber = playerCards[3];
		return true;
	}
	else if (count(cardNumber.begin(), cardNumber.end(), cardNumber[0]) == 3 && count(cardNumber.begin(), cardNumber.end(), cardNumber[3]) == 1 && count(cardNumber.begin(), cardNumber.end(), cardNumber[4]) == 1) { // 3 1 1
		maxNumber = playerCards[2];
		return true;
	}
	else
		return false;
}

bool PokerGame::isTwoPairs() {
	if (count(cardNumber.begin(), cardNumber.end(), cardNumber[0]) == 2 && count(cardNumber.begin(), cardNumber.end(), cardNumber[2]) == 2 && count(cardNumber.begin(), cardNumber.end(), cardNumber[4]) == 1) { // 2 2 1
		maxNumber = playerCards[3];
		return true;
	}
	else if (count(cardNumber.begin(), cardNumber.end(), cardNumber[0]) == 2 && count(cardNumber.begin(), cardNumber.end(), cardNumber[2]) == 1 && count(cardNumber.begin(), cardNumber.end(), cardNumber[3]) == 2) { // 2 1 2
		maxNumber = playerCards[4];
		return true;
	}
	else if (count(cardNumber.begin(), cardNumber.end(), cardNumber[0]) == 1 && count(cardNumber.begin(), cardNumber.end(), cardNumber[1]) == 2 && count(cardNumber.begin(), cardNumber.end(), cardNumber[3]) == 2) { // 1 2 2
		maxNumber = playerCards[4];
		return true;
	}
	else
		return false;
}

bool PokerGame::isOnePair() {
	if (count(cardNumber.begin(), cardNumber.end(), cardNumber[0]) == 2 && count(cardNumber.begin(), cardNumber.end(), cardNumber[2]) == 1 && count(cardNumber.begin(), cardNumber.end(), cardNumber[3]) == 1 && count(cardNumber.begin(), cardNumber.end(), cardNumber[4]) == 1) { // 2 1 1 1
		maxNumber = playerCards[1];
		return true;
	}
	else if (count(cardNumber.begin(), cardNumber.end(), cardNumber[0]) == 1 && count(cardNumber.begin(), cardNumber.end(), cardNumber[1]) == 2 && count(cardNumber.begin(), cardNumber.end(), cardNumber[3]) == 1 && count(cardNumber.begin(), cardNumber.end(), cardNumber[4]) == 1) { // 1 2 1 1
		maxNumber = playerCards[2];
		return true;
	}
	else if (count(cardNumber.begin(), cardNumber.end(), cardNumber[0]) == 1 && count(cardNumber.begin(), cardNumber.end(), cardNumber[1]) == 1 && count(cardNumber.begin(), cardNumber.end(), cardNumber[2]) == 2 && count(cardNumber.begin(), cardNumber.end(), cardNumber[4]) == 1) { // 1 1 2 1
		maxNumber = playerCards[3];
		return true;
	}
	else if (count(cardNumber.begin(), cardNumber.end(), cardNumber[0]) == 1 && count(cardNumber.begin(), cardNumber.end(), cardNumber[1]) == 1 && count(cardNumber.begin(), cardNumber.end(), cardNumber[2]) == 1 && count(cardNumber.begin(), cardNumber.end(), cardNumber[3]) == 2) { // 1 1 1 2
		maxNumber = playerCards[4];
		return true;
	}
	else
		return false;
}