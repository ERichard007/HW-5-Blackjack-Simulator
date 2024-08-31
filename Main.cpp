// Programmer: Evan Richard
// Date: 4/4/24
// File: Source.cpp
// Assignment: HW2
// Purpose: Main file containing Blackjack Game!!!

#include <iostream>
#include <stdlib.h>
#include <string>
#include <time.h>
#include "blackjack.h"
using namespace std;

int main(){
	/*GAME SETUP*/
	srand(time(0)); //2101

	string player;
	float currentBalance = ((rand() % 901) + 100);

	cout << "Enter player name: ";
	cin >> player;
	
	printf("Starting balance: %.2f\n*****THE GAMES BEGIN! GOODLUCK!*****\n\n", currentBalance);

	/*LET THE GAMES BEGIN!!*/
	while (currentBalance > 0) {
		float wager; 

		cout << "\nEnter an amount to wager: ";
		cin >> wager; 

		while (wager <= 0 || wager > currentBalance) { 
			printf("Please enter a valid amount between 0 and your balance of %.2f: ", currentBalance); 
			cin >> wager; 
		}

		/*CARD DRAWING ONE*/
		int playerAces = 0; 
		int dealerAces = 0;

		int playerActualTotal = 0;
		int computerActualTotal = 0; 

		int cardValue1 = generateRandomCard(1, 13);
		string cardSuit1 = generateRandomSuit(cardValue1);
		playerActualTotal += (cardValue1 == 1) ? 11 : cardValue1;
		playerAces += (cardValue1 == 1) ? 1 : 0; 
		cardValue1 = (cardValue1 > 10) ? 10 : cardValue1;

		int cardValue2 = generateRandomCard(1, 13);
		string cardSuit2 = generateRandomSuit(cardValue2);
		playerActualTotal += (cardValue2 == 1) ? 11 : cardValue2; 
		playerAces += (cardValue2 == 1) ? 1 : 0; 
		cardValue2 = (cardValue2 > 10) ? 10 : cardValue2; 

		cout << "Player's Hand: " << cardSuit1 << ", " << cardSuit2 << endl;

		int computerCardValue1 = generateRandomCard(1, 13);
		string computerCardSuit1 = generateRandomSuit(computerCardValue1);
		computerActualTotal += (computerCardValue1 == 1) ? 11 : computerCardValue1;
		dealerAces += (computerCardValue1 == 1) ? 1 : 0; 
		computerCardValue1 = (computerCardValue1 > 10) ? 10 : computerCardValue1;  

		int computerCardValue2 = generateRandomCard(1, 13);
		string computerCardSuit2 = generateRandomSuit(computerCardValue2); 
		computerActualTotal += (computerCardValue2 == 1) ? 11 : computerCardValue2; 
		dealerAces += (computerCardValue2 == 1) ? 1 : 0; 
		computerCardValue2 = (computerCardValue2 > 10) ? 10 : computerCardValue2;

		cout << "Dealer's Hand: " << computerCardSuit1 << ", [HIDDEN CARD]" << endl; 

		/*1st BLACKJACK CHECK*/
		int playerTotal = cardValue1 + cardValue2 + (10*playerAces);
		int computerTotal = computerCardValue1 + computerCardValue2 + (10*dealerAces); 

		if (isBlackjack(playerTotal) == true) {
			cout << "----- Dealer Reveals ----- \nDealer's Hand: " << computerCardSuit1 << ", " << computerCardSuit2 << endl; 
			if (isBlackjack(computerTotal == true)) {
				currentBalance = updatePlayerBalance(currentBalance, wager, true, false, true, false);
				continue;
			}
			else {
				currentBalance = updatePlayerBalance(currentBalance, wager, true, false, false, false);
				continue;
			}
		}

		/*PLAYER'S TURN*/
		bool continueRound = true;
		string currentHand = "Player's Hand: " + cardSuit1 + ", " + cardSuit2;
		while (continueRound == true) {
			int playerChoice;

			int cardValue3 = 0;
			string cardSuit3;

			displayPlayerChoices(playerTotal);
			cin >> playerChoice;

			while ((playerChoice < 1 || playerChoice > 3) || (playerChoice == 3 && wager*2 > currentBalance)) { 
				cout << "Please enter a valid choice!" << endl;
				displayPlayerChoices(playerTotal); 
				cin >> playerChoice; 
			}

			switch (playerChoice) {
			case 1:
				cardValue3 = generateRandomCard(1, 13);
				cardSuit3 = generateRandomSuit(cardValue3);
				playerActualTotal += (cardValue3 == 1) ? 11 : cardValue3; 
				playerAces += (cardValue3 == 1) ? 1 : 0; 
				cardValue3 = (cardValue3 > 10) ? 10 : cardValue3; 
				break;
			case 2:
				continueRound = false;
				break;
			case 3:
				cardValue3 = generateRandomCard(1, 13);
				cardSuit3 = generateRandomSuit(cardValue3); 
				playerActualTotal += (cardValue3 == 1) ? 11 : cardValue3; 
				playerAces += (cardValue3 == 1) ? 1 : 0; 
				cardValue3 = (cardValue3 > 10) ? 10 : cardValue3; 
				continueRound = false; 

				wager *= 2;
				break;
			default:
				break;
			}
			
			playerTotal = (cardValue3 == 1) ? playerTotal + cardValue3 + 10 : playerTotal + cardValue3; 
			currentHand = currentHand + ", " + cardSuit3; 
			cout << currentHand << endl;

			if (playerTotal == 21) {
				continueRound = false; 
			}
			else {
				while (playerTotal > 21) { 
					if (playerAces > 0) {
						playerTotal -= 10;
						playerAces -= 1;
					}
					else {
						continueRound = false;
						break;
					}
				}
			}
		}

		/*DEALER'S TURN*/
		continueRound = true;
		string computerHand = "Dealer's Hand: " + computerCardSuit1 + ", " + computerCardSuit2; 

		cout << "\nDEALERS TURN\n" << endl; 
		cout << "----- Dealer Reveals ----- \n" << computerHand << endl; 

		while (continueRound == true) {

			if (playerTotal > 21) {
				currentBalance = updatePlayerBalance(currentBalance, wager, false, false, true, false);
				continueRound = false;
				break;
			}

			int computerCardValue3 = 0; 
			string computerCardSuit3; 

			if (computerTotal < 17) {
				cout << "Dealer Draws ... " << endl;
				computerCardValue3 = generateRandomCard(1, 13);
				computerCardSuit3 = generateRandomSuit(computerCardValue3);
				computerActualTotal += (computerCardValue3 == 1) ? 11 : computerCardValue3;
				dealerAces += (computerCardValue3 == 1) ? 1 : 0; 
				computerCardValue3 = (computerCardValue3 > 10) ? 10 : computerCardValue3;
			}
			else {
				cout << "Dealer Stands ... " << endl;

				if (playerTotal > computerTotal) {
					currentBalance = updatePlayerBalance(currentBalance, wager, false, true, false, false); 
					continueRound = false; 
					break; 
				}
				else if (computerTotal > playerTotal) {
					currentBalance = updatePlayerBalance(currentBalance, wager, false, false, false, true); 
					continueRound = false; 
					break;
				}
				else {
					cout << "\nIts a Tie...\n" << endl;
					continueRound = false; 
					break;
				}
			}

			computerTotal = (computerCardValue3 == 1) ? computerTotal + computerCardValue3 + 10 : computerTotal + computerCardValue3;   

			computerHand = computerHand + ", " + computerCardSuit3;
			cout << computerHand << endl;  

			if (computerTotal == 21) { 
				if (playerTotal == 21) {
					currentBalance = updatePlayerBalance(currentBalance, wager, true, false, true, false); 
				}
				else {
					currentBalance = updatePlayerBalance(currentBalance, wager, false, false, true, false); 
				}
				
				continueRound = false;
			}
			else {
				while (computerTotal > 21) { 
					if (dealerAces > 0) { 
						computerTotal -= 10; 
						dealerAces -= 1;
					}
					else {
						currentBalance = updatePlayerBalance(currentBalance, wager, false, false, false, false); 
						continueRound = false;
						break;
					}
				}
			}


		}
	}
	

	return 0;
}