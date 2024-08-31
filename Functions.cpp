#include <iostream>
#include <stdlib.h>
#include <string>
#include "blackjack.h"
using namespace std;

int generateRandomCard(const int min, const int max) {
	int randomCardValue = (rand() % max) + min;
	return randomCardValue;
}

string generateRandomSuit(const int cardValue) {
	string suit;
	string newString;

	int randomNum = (rand() % 4) + 1;

	switch (randomNum) {
	case 1:
		suit = "Spades";
		break;
	case 2:
		suit = "Hearts";
		break;
	case 3:
		suit = "Diamonds";
		break;
	case 4:
		suit = "Clubs";
		break;
	default:
		break;
	}

	if (cardValue > 1 && cardValue < 11) {
		newString = to_string(cardValue) + " of " + suit;
		return newString;
	}
	else {
		switch (cardValue) {
		case 1:
			newString = ("Ace of " + suit);
			break;
		case 11:
			newString = ("Jack of " + suit);
			break;
		case 12:
			newString = ("Queen of " + suit);
			break;
		case 13:
			newString = ("King of " + suit);
			break;
		}

		return newString;
	}
}

bool isBlackjack(const int pointsTotal) {
	if (pointsTotal == 21) {
		return true;
	}
	return false;
}

void displayOutcome(const float playerBalance, const float balanceUpdate, const string whatWon, const bool playerWon, const bool Tie) {
	if (playerWon == true) {
		cout << "\nCongratulations! You " << whatWon << endl; 
	}
	else if (Tie == true) {
		cout << "\nYou both Tied!" << endl;
	}
	else {
		cout << "\nDealer has won the round!" << endl;
	}
	
	printf("Balance Update: +$%.2f\n", balanceUpdate);
	printf("Your new balance is $%.2f.\n", playerBalance);
}

void displayPlayerChoices(int cardTotal) {
	cout << "\n=== CHOOSE AN OPTION ===\n(1) to Hit\n(2) to Stand\n(3) to Double Down\n\tCURRENT TOTAL: " << to_string(cardTotal) << endl;
}

float updatePlayerBalance(const float playerBalance, const float wager, const bool playerBlackjack, const bool playerCardWin, const bool computerBlackjack, const bool computerCardWin) { 
	float newBalance = playerBalance; 

	//Blackjack Win Check
	if (playerBlackjack == true) {
		if (computerBlackjack == true) {
			newBalance = newBalance;
			displayOutcome(newBalance, 0, "hit Blackjack!", false, true);
		}
		else {
			newBalance = (newBalance + wager) + 0.5 * wager;
			displayOutcome(newBalance, (wager + (0.5*wager)), "hit Blackjack!", true, false); 
		}
	}
	else if (computerBlackjack == true) {
		newBalance = newBalance - wager; 
		displayOutcome(newBalance, -wager, "hit Blackjack!", false, false);
	}

	//Hand Win Check
	if (playerCardWin == true) {  
		if (computerCardWin == true) { 
			newBalance = newBalance;
			displayOutcome(newBalance, 0, "won the Hand!", false, true);
		}
		else {
			newBalance = newBalance + wager; 
			displayOutcome(newBalance, wager, "won the Hand!", true, false);
		}
	}
	else if (computerCardWin == true) { 
		newBalance = newBalance - wager;
		displayOutcome(newBalance, -wager, "won the Hand!", false, false);
	}

	//Bust Check
	if (computerBlackjack == false && computerCardWin == false) {
		newBalance = newBalance + wager;
		displayOutcome(newBalance, wager, "won the Round!", true, false);
	}

	return newBalance;
}

