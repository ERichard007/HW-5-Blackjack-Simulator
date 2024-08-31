#include <iostream>
using namespace std;

#ifndef BLACKJACK_H
#define BLACKJACK_H

/*Functions FUNCTION PROTOTYPES*/

//Gen: Will return a random card value between a min and max INCLUSIVE!
//Pre: Min must be greater than 0 and max no greater than 13.
//Post: returns a random integer between min and max inclusive.
int generateRandomCard(const int min, const int max);

//Gen: Will generate a random suit based off of the card value.
//Pre: cardValue must follow Preconditions of generateRandomCard function.
//Post: Will return a random string value representing the total value of the card with its number and suit included!.
string generateRandomSuit(const int cardValue);

//Gen: Returns true if blackjack or false if not blackjack.
//Pre: None.
//Post: will return true if the given amount is a blackjack! Note: must use for one player's total at a time!
bool isBlackjack(const int pointsTotal);

float updatePlayerBalance(const float playerBalance, const float wager, const bool playerBlackjack, const bool playerCardWin, const bool computerBlackjack, const bool computerCardWin); 

void displayOutcome(const float playerBalance, const float balanceUpdate, const string whatWon, const bool playerWon, const bool Tie); 

void displayPlayerChoices(int cardTotal);

#endif
