// Name: Sanshray Thapa
// SFU ID: 301456437

// The strategy is based on the strategy at bicyclecards.com/how-to-play/blackjack/
/*
 Strategy: Based on the dealer's revealed card, only hit until a certain point
 Don't risk going bust; hope that dealer hits and goes bust.
 
 If player doesnt have ace:
    If dealerHandScore ( only revealed card) is between 7 - A, hit until playerHandScore is at least 17 ( be risky)
    If dealerHandScore ( only revealed card) is between 4 - 6, hit until playerHandScore is at least 12 ( don't be risky)
    If dealerHandScore ( only revealed card) is between 2 - 3, hit until playerHandScore is at least 13 ( be a little risky)
 
 If player has ace:
 Hit until playerHandScore is at least 18 ( be risky)
 */

// I hereby confirm that this is my own work and I have not violated any of SFU’s Code of Academic Integrity and Good Conduct (S10.01).

#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
using namespace std;

// Global constants
const int DECK_SIZE = 52;
const int NUM_RANKS = 13;
const int NUM_SUITS = 4;
const int WIN= 1;
const int DRAW = 0;
const int LOSS = -1;
const int MAX_CARDS_HAND = 12;
const int ALIGN = 4;
const int DEALER_LIMIT = 17;
const int WINNING_SCORE = 21;
const int ACE_VALUE_ONE = 1;
const int ACE_VALUE_ELEVEN = 11;
const int FIRST_CARD = 0;
const int GOOD_UPCARD = 11;
const int POOR_UPCARD = 6;
const int FAIR_UPCARD = 3;
const int PLAYER_LIMIT_ACE = 18;
const int PLAYER_LIMIT_GU = 17;
const int PLAYER_LIMIT_PU = 12;
const int PLAYER_LIMIT_FU = 13;
// Card structure
struct Card{
    string suitName;
    string description;
    int rank;
    int value;
    
    Card(){
         suitName = "";
         description = "";
         rank = 0;
         value = 0;
    }
};

// Card array structure
struct CardArray{
    Card * cards ;
    int elementNum;
    int currentElementNum;
    
    CardArray(){
         cards = nullptr;
         elementNum = 0;
         currentElementNum = 0;
    }
};

// Function Prototypes
void getNewDeck(CardArray & deck);
void printDeck(const CardArray & deck);
void swap(CardArray & x, CardArray & y);
void shuffleDeck(const CardArray & deck);
int blackjack(CardArray & deck);
void deal(CardArray & deck,CardArray & hand);
void dealFirstCard(CardArray & deck,CardArray & playerHand,CardArray & dealerHand);
void dealSecondCard(CardArray & deck,CardArray & playerHand,CardArray & dealerHand);
int countScore(CardArray & hand);
string hitOrStand();
void displayHand(CardArray & hand);
void playGames(CardArray & deck);
bool startHand(int numGames);
bool checkAces(CardArray & deck);
void changeAceValue(CardArray & deck);
void changeAllAceValues(CardArray & deck);
int chooseAceValue(CardArray & playerHand, int playerHandScore);
void printBlackjackLoss(CardArray & playerHand,CardArray & dealerHand);
void printBlackjackWin(CardArray & playerHand,CardArray & dealerHand);
void printBlackjackTie(CardArray & playerHand,CardArray & dealerHand);
void printLoss(CardArray & playerHand,CardArray & dealerHand);
void printWin(CardArray & playerHand,CardArray & dealerHand);
void printDealerLoss(CardArray & playerHand,CardArray & dealerHand);
void printDealerWin(CardArray & playerHand,CardArray & dealerHand);
int printRoundResult(CardArray & playerHand,CardArray & dealerHand, int playerHandScore, int dealerHandScore);
void giveAdvice(CardArray & playerHand, CardArray & dealerHand, int playerHandScore);


// Main function
int main() {
    
    srand(unsigned(time(0)));
     
    CardArray deck;
    deck.currentElementNum = deck.elementNum = DECK_SIZE;
    
    getNewDeck(deck);
    cout << "Sorted deck" << endl;
    printDeck(deck);
    shuffleDeck(deck);
    cout << "Shuffled deck" << endl;
    printDeck(deck);
    delete[]deck.cards;
    
    playGames(deck);

    return 0;
}

// Creates arrays of card suit, card rank, value and a short description
void getNewDeck(CardArray & deck){
    deck.currentElementNum = DECK_SIZE;
    deck.elementNum = DECK_SIZE;
    deck.cards = new Card [DECK_SIZE];
    // Static arrays with elements to fill the dynamic arrays with
    int rank[NUM_RANKS] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 };
    string suitName[NUM_SUITS] = { "Spades", "Hearts", "Diamonds", "Clubs" };
    int value[NUM_RANKS] = { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10 };
    string description[DECK_SIZE];

    // Populate description with a deck or ordered cards
    int i = 0;
    while( i < DECK_SIZE){
        for (int j = 0; j < NUM_SUITS; j++){
            for(int k = 0; k < NUM_RANKS; k++){
                if (rank[k] == 1){
                    description[i] = "A";
                }
                else if (rank[k] == 11){
                    description[i] = "J";
                }
                else if (rank[k] == 12){
                    description[i] = "Q";
                }
                else if (rank[k] == 13){
                    description[i] = "K";
                }
                else{
                   description[i] = to_string(rank[k]);
                }
                description[i] += suitName[j][0];
                i++;
            }
        }
    }

    // Array of suit names
    i = 0;
    while (i < DECK_SIZE){
        for (int j = 0; j < NUM_SUITS; j++){
            for (int k = 0; k < NUM_RANKS; k++) {
                deck.cards[i].suitName = suitName[j][0];
                i++;
            }
        }
    }
    
    // Array of ranks
    i = 0;
    while (i < DECK_SIZE){
        for (int j = 0; j < NUM_SUITS; j++){
            for (int k = 0; k < NUM_RANKS; k++) {
                deck.cards[i].rank = rank[k];
                i++;
            }
        }
    }
    
    // Array of card value
    i = 0;
    while (i < DECK_SIZE){
        for (int j = 0; j < NUM_SUITS; j++){
            for (int k = 0; k < NUM_RANKS; k++) {
                deck.cards[i].value = value[k];
                i++;
            }
        }
    }
    
    // Array of short description
    for (int i = 0 ; i < DECK_SIZE; i++){
        deck.cards[i].description = description[i];
    }

}

// Prints a deck of cards in order
void printDeck(const CardArray & deck){
    for (int i = 0 ; i < DECK_SIZE; i++){
        cout << setw(ALIGN) << deck.cards[i].description;
        // Starts new line once 13 lines are printed
        if ( i % NUM_RANKS  == NUM_RANKS - 1){
            cout << endl;
        }
    }
    cout << endl;
}

// Swaps two elements
void swap(CardArray & x, CardArray & y)
{
    CardArray temp = x;
    x = y;
    y = temp;
}

// Shuffles a deck by swapping two cards
void shuffleDeck(const CardArray & deck){
    for (int i = 0 ; i < DECK_SIZE; i++){
        int randomNum = rand () % DECK_SIZE;
        swap(deck.cards[i], deck.cards[randomNum]);
    }
}

// Takes the last index (card) of deck array and gives it to the user/ dealer
void deal(CardArray & deck,CardArray & hand){

    hand.cards[hand.currentElementNum] = deck.cards[deck.currentElementNum - 1];
    hand.currentElementNum++;
    deck.currentElementNum--;
    
    // Refill deck once the deck is empty
    if (deck.currentElementNum == 0){
        shuffleDeck(deck);
        deck.currentElementNum = DECK_SIZE;
    }
}

// Counts total score by adding the value of each card
int countScore(CardArray & hand){
    int score = 0;
    for (int i = 0; i < hand.currentElementNum; i++){
        score += hand.cards[i].value;
    }
    return score;
}

// Asks for user to hit or stand
// Checks user input
string hitOrStand(){
    string input= "";
    while (!(((input == "h" || input == "H") || (input == "s" || input == "S")) && (input.size() == 1))){
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
        }
    cout << "Enter h to hit or s to stand: ";
    cin >> input;
    }
    cin.ignore(10000, '\n');
    return input;
}

// Displays the current cards of user and/or dealer
void displayHand(CardArray & hand){
    for (int i = 0; i < hand.currentElementNum; i++){
        cout << setw(ALIGN) << hand.cards[i].description;
    }
    cout << endl;
}


// Runs a round of blackjack
int blackjack(CardArray & deck){
    
    CardArray playerHand;
    CardArray dealerHand;
    
    playerHand.elementNum = dealerHand.elementNum = MAX_CARDS_HAND;
    playerHand.cards = new Card[playerHand.elementNum];
    dealerHand.cards = new Card[dealerHand.elementNum];
   
    // Deals the first two cards to player and dealer
    dealFirstCard(deck, playerHand, dealerHand);
    dealSecondCard(deck, playerHand, dealerHand);
    
    // Counts the score of the player and dealer so far
    int playerHandScore = countScore(playerHand);
    int dealerHandScore = countScore(dealerHand);
   
    // Checks if dealer got blackjack and player didn't
    if (dealerHandScore == WINNING_SCORE && playerHandScore != WINNING_SCORE){
        printBlackjackLoss(playerHand,dealerHand);
        return LOSS;
    }
    
    // Checks if player got blackjack and dealer didn't
    if ( dealerHandScore != WINNING_SCORE && playerHandScore == WINNING_SCORE){
        printBlackjackWin(playerHand,dealerHand);
        return WIN;
    }
    
    // Checks if dealer and player got blackjack
    if ( dealerHandScore == WINNING_SCORE && playerHandScore == WINNING_SCORE){
        printBlackjackTie(playerHand,dealerHand);
        return DRAW;
    }
    
    cout << endl << "Dealing to player" << endl;
    cout << "-----------------" << endl;
    
    giveAdvice(playerHand,dealerHand,playerHandScore);
    string userInput = hitOrStand();
    
    // Loop that runs when the user chooses to hit
    // Loop will run until user wins, goes bust, or user chooses to stand
    while (userInput == "H" || userInput == "h"){
        cout << "+Player+:";
        deal(deck,playerHand);
        displayHand(playerHand);
        playerHandScore = countScore(playerHand);
        
        // When player's cards add up to more than 21
        if ((playerHandScore > WINNING_SCORE) && (checkAces(playerHand) == false)){
            printLoss(playerHand, dealerHand);
            return LOSS;
        }
        // Changes ace to one if player's hand has an ace
        else if ((playerHandScore > WINNING_SCORE) && (checkAces(playerHand) == true)){
            changeAllAceValues(playerHand);
            playerHandScore = countScore(playerHand);
            // Check if hand still adds up to 21
            if (playerHandScore > WINNING_SCORE){
                printLoss(playerHand, dealerHand);
                return LOSS;
            }
        }
            
        // Checks if player's hand adds up to exactly 21
        if ( playerHandScore == WINNING_SCORE){
            printWin(playerHand, dealerHand);
            return WIN;
       }
        
        // Asks user to hit or stand again if they didn't win or go bust
        else{
            cout << endl;
            giveAdvice(playerHand,dealerHand,playerHandScore);
            userInput = hitOrStand();
        }
    }
    
    // If user stands
    if (userInput == "S" || userInput == "s"){
        
        // Reveals dealer's second card
        cout << endl << "Dealing to dealer" << endl;
        cout << "-----------------" << endl;
        cout << "*Dealer*:";
        displayHand(dealerHand);
        dealerHandScore = countScore(dealerHand);
        
        // If dealer gets two aces as their first two cards
        if (dealerHandScore > WINNING_SCORE && checkAces(dealerHand) == true){
            changeAceValue(dealerHand);
            dealerHandScore = countScore(dealerHand);
        }
        
        // Dealers gets a card until their hand adds to 17 or more
        while(dealerHandScore < DEALER_LIMIT){
            cout << "*Dealer*:";
            deal(deck,dealerHand);
            displayHand(dealerHand);
            dealerHandScore = countScore(dealerHand);
            
            if (checkAces(dealerHand) == true){
                // Changes ace value if dealer would go bust
                if (dealerHandScore > WINNING_SCORE){
                    changeAceValue(dealerHand);
                    dealerHandScore = countScore(dealerHand);
                }
                // Sets ace value to 11 if the dealer hand is between 17 and 21
                if ((dealerHandScore < WINNING_SCORE) && (dealerHandScore > DEALER_LIMIT)){
                    for(int i = 0; i < dealerHand.currentElementNum; i++){
                        if(dealerHand.cards[i].value == ACE_VALUE_ONE){
                            changeAceValue(dealerHand);
                        }
                    }
                }
            }

            // When dealer's hand adds up to more than 21
             if ( dealerHandScore > WINNING_SCORE){
                 printDealerLoss(playerHand, dealerHand);
                return WIN;
            }
            
            // When dealer's hand adds up to exactly 21
            else if ( dealerHandScore == WINNING_SCORE){
                printDealerWin(playerHand, dealerHand);
                return LOSS;
            }
            
        }
       
        // Checks which value for ace gives a higher score and won't bust
        if (checkAces(playerHand) == true){
            playerHandScore = chooseAceValue(playerHand, playerHandScore);
        }
        // Reveals final score
        int result = printRoundResult(playerHand, dealerHand, playerHandScore, dealerHandScore);
        
        if (result == WIN){
            return WIN;
        }
        else if (result == LOSS){
            return LOSS;
        }
        else if (result == DRAW){
            return DRAW;
        }
    }
    return 0;
}

// Runs blackjack function as long as user inputs 'y'
void playGames(CardArray & deck){
    int gamesPlayed = 0;
    int gamesWon = 0 , gamesLost = 0, gamesTied = 0;
    cout << "BLACKJACK" << endl << "---------" << endl;
    bool play = startHand(gamesPlayed);
    cout << endl;
    while ( play == true){
        int result = blackjack(deck);
        if (result == -1){
            gamesLost++;
        }
        else if (result == 0){
            gamesTied++;
        }
        else if (result == 1){
            gamesWon++;
        }
        cout << "_____________________________" << endl << endl;
        gamesPlayed++;
        play = startHand(gamesPlayed);
    }
    // Prints totals wins, losses, and draws
    cout << endl << "Thanks for playing, you played " << gamesPlayed << " games and your record was:" << endl;
    cout << "  wins:" << setw(ALIGN) << gamesWon << endl;
    cout << "losses:" << setw(ALIGN) << gamesLost << endl;
    cout << " draws:" << setw(ALIGN) << gamesTied << endl;
}

// Deals the first card to player and dealer
void dealFirstCard(CardArray & deck,CardArray & playerHand,CardArray & dealerHand){
    cout << "Deal first card" << endl;
    cout << "---------------" << endl;
    cout << "+Player+:";
    
    deal(deck,playerHand);
    displayHand(playerHand);
    
    cout << "*Dealer*:";
    deal(deck,dealerHand);
    displayHand(dealerHand);
    cout << endl;
}

// Deals the second card to player and dealer
// Hides dealer's second card
void dealSecondCard(CardArray & deck,CardArray & playerHand,CardArray & dealerHand){
    cout << "Deal second card" << endl;
    cout << "----------------" << endl;
    
    cout << "+Player+:";
    deal(deck,playerHand);
    displayHand(playerHand);
    
    cout << "*Dealer*:";
    for (int i = 0; i < dealerHand.currentElementNum; i++){
        cout << setw(ALIGN) << dealerHand.cards[i].description;
    }
    cout << setw(ALIGN) << "??";
    deal(deck,dealerHand);
    cout << endl;
}

//  When dealer gets backjack
void printBlackjackLoss(CardArray & playerHand,CardArray & dealerHand){
    cout << "*Dealer*:";
    displayHand(dealerHand);
    cout << endl << "Dealer got blackjack. You lose." << endl;
    delete[]playerHand.cards;
    delete[]dealerHand.cards;
}

// When player gets blackjack
void printBlackjackWin(CardArray & playerHand,CardArray & dealerHand){
    cout << "+Dealer+:";
    displayHand(dealerHand);
    cout << endl << "Blackjack! You win." << endl;
    delete[]playerHand.cards;
    delete[]dealerHand.cards;
}

// When both get blackjack
void printBlackjackTie(CardArray & playerHand,CardArray & dealerHand){
    cout <<"+Dealer+:";
    displayHand(dealerHand);
    cout << endl << "Both player and dealer got blackjack. It's a tie." << endl;
    delete[]playerHand.cards;
    delete[]dealerHand.cards;
}

// When player busts
void printLoss(CardArray & playerHand,CardArray & dealerHand){
    cout << "*Dealer*:";
    displayHand(dealerHand);
    cout << endl << "Bust! You lose." << endl;
    delete[]playerHand.cards;
    delete[]dealerHand.cards;
}

// When player gets 21 after hitting
void printWin(CardArray & playerHand,CardArray & dealerHand){
    cout << "*Dealer*:";
    displayHand(dealerHand);
    cout << endl << "You win." << endl;
    delete[]playerHand.cards;
    delete[]dealerHand.cards;
}

// When dealer busts
void printDealerLoss(CardArray & playerHand,CardArray & dealerHand){
    cout << endl << "Dealer is bust, you win." << endl;
    delete[]playerHand.cards;
    delete[]dealerHand.cards;
}

// When dealer wins after hitting
void printDealerWin(CardArray & playerHand,CardArray & dealerHand){
    cout << endl << "You lose."  << endl;
    delete[]playerHand.cards;
    delete[]dealerHand.cards;
}

// Compares final scores after both player and dealer stand
int printRoundResult(CardArray & playerHand,CardArray & dealerHand, int playerHandScore, int dealerHandScore ){
    cout << endl << "Player score = " << playerHandScore << ", " << "Dealer score = " << dealerHandScore << endl;
    if (playerHandScore == dealerHandScore){
        cout << "Game is tied." << endl;
        delete[]playerHand.cards;
        delete[]dealerHand.cards;
        return DRAW;
    }
    
    else if (playerHandScore < dealerHandScore){
        cout << "You lose." << endl;
        delete[]playerHand.cards;
        delete[]dealerHand.cards;
        return LOSS;
    }
    
    else if (playerHandScore > dealerHandScore){
        cout << "You win." << endl;
        delete[]playerHand.cards;
        delete[]dealerHand.cards;
        return WIN;
    }
    return 0;
}

// Asks user if they want to play or not
// Checks user input
bool startHand(int numGames){
    string input= "";
    while (!(((input == "y" || input == "Y") || (input == "n" || input == "N")) && (input.size() == 1))){
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
        }
        if (numGames == 0){
            cout << "Do you want to play a hand of blackjack (y/n)? ";
        }
        else{
            cout << "Do you want to play another hand (y/n)? ";
        }
        cin >> input;
    }
    cin.ignore(10000, '\n');
    if (input == "y" || input == "Y"){
        return true;
    }
    else{
        return false;
    }
}

// Check if a deck has ace or not
bool checkAces(CardArray & deck){
    for( int i = 0; i < deck.currentElementNum; i++){
        if (deck.cards[i].value == 11 || deck.cards[i].value == 1 ){
            return true;
        }
    }
    return false;
}

// Chnages one of the ace value in the array from 1 to 11 and vice versa
void changeAceValue(CardArray & deck){
    for( int i = 0; i < deck.currentElementNum; i++){
        if (deck.cards[i].value == ACE_VALUE_ELEVEN){
            deck.cards[i].value = ACE_VALUE_ONE;
            i = deck.currentElementNum;
        }
        else if (deck.cards[i].value == ACE_VALUE_ONE){
            deck.cards[i].value = ACE_VALUE_ELEVEN;
            i = deck.currentElementNum;
        }
    }
}

// Chnages all of the ace values in the array from 1 to 11 and vice versa
void changeAllAceValues(CardArray & deck){
    for( int i = 0; i < deck.currentElementNum; i++){
        if (deck.cards[i].value == ACE_VALUE_ELEVEN){
            deck.cards[i].value = ACE_VALUE_ONE;
            i = deck.currentElementNum;
        }
        else if (deck.cards[i].value == ACE_VALUE_ONE){
            deck.cards[i].value = ACE_VALUE_ELEVEN;
        }
    }
}
// Chooses best possible ace value that won't make player go bust
int chooseAceValue(CardArray & playerHand, int playerHandScore){
    // Stores score where ace has a value of 1 or 11
    int scoreWithAce = countScore(playerHand);
    // Stores score where ace has different value (after its value is changed)
    changeAceValue(playerHand);
    int scoreWithDiffAce = countScore(playerHand);
    if ((scoreWithAce > scoreWithDiffAce) && (scoreWithAce <= WINNING_SCORE) ){
        playerHandScore = scoreWithAce;
    }
    else if ((scoreWithAce > scoreWithDiffAce) && (scoreWithAce > WINNING_SCORE) ){
        playerHandScore = scoreWithDiffAce;
    }
    else if ((scoreWithAce < scoreWithDiffAce) && (scoreWithDiffAce <= WINNING_SCORE) ){
        playerHandScore = scoreWithDiffAce;
    }
    else if ((scoreWithAce < scoreWithDiffAce) && (scoreWithAce > WINNING_SCORE) ){
        playerHandScore = scoreWithAce;
    }
    return playerHandScore;
}

// Offers advice based on current hand scores of player and dealer
void giveAdvice(CardArray & playerHand, CardArray & dealerHand, int playerHandScore){
    
    // Only counts dealers first card
    int dealerHandScore = dealerHand.cards[FIRST_CARD].value;
    //  When player has a soft hand
    if(checkAces(playerHand) == true){
        if(playerHandScore < PLAYER_LIMIT_ACE){
            for (int i = 0; i < playerHand.currentElementNum; i++){
                // Change all aces to 1 so advice is correct
                if(dealerHand.cards[i].value == ACE_VALUE_ELEVEN){
                    changeAceValue(dealerHand);
                }
            }
            if (playerHandScore < PLAYER_LIMIT_ACE){
                cout << "Advice: You should hit." << endl;
                cout << "Your current score is " << playerHandScore << ", hit until your score is at least 18 since you have an ace.";
            }
            else if(playerHandScore >= PLAYER_LIMIT_ACE){
                cout << "Advice: You should stand." << endl;
                cout << "Your current score is " << playerHandScore << ", if you hit you are likely to go bust.";
            }
        }
        else if(playerHandScore >= PLAYER_LIMIT_ACE){
            for (int i = 0; i < playerHand.currentElementNum; i++){
                // Change all aces to 1 so advice is correct
                if(dealerHand.cards[i].value == ACE_VALUE_ELEVEN){
                    changeAceValue(dealerHand);
                }
            }
            if (playerHandScore < PLAYER_LIMIT_ACE){
                cout << "Advice: You should hit." << endl;
                cout << "Your current score is " << playerHandScore << ", hit until your score is at least 18 since you have an ace.";
            }
            else if(playerHandScore >= PLAYER_LIMIT_ACE){
                cout << "Advice: You should stand." << endl;
                cout << "Your current score is " << playerHandScore << ", if you hit you are likely to go bust.";
            }
        }
        // Change the aces back
        changeAceValue(playerHand);
    }
    // When dealer's upcard is a fair one ( 2 to 3)
    // Player limit (fair upcard) = 13
    else if (dealerHandScore <= FAIR_UPCARD){
        if(playerHandScore < PLAYER_LIMIT_FU){
            cout << "Advice: You should hit." << endl;
            cout << "Your current score is " << playerHandScore << ", since the dealer's upcard is fair(" << dealerHandScore <<"), hit until your score is at least 13.";
        }
        else if(playerHandScore >= PLAYER_LIMIT_FU){
            cout << "Advice: You should stand." << endl;
            cout << "Your current score is " << playerHandScore << ", since the dealer's upcard is fair(" << dealerHandScore <<"), don't risk more and hope dealer goes bust.";
        }
    }
    // When dealer's upcard is a poor one ( 4 to 6)
    // Player limit (poor upcard) = 12
    else if (dealerHandScore <= POOR_UPCARD){
        if(playerHandScore < PLAYER_LIMIT_PU){
            cout << "Advice: You should hit." << endl;
            cout << "Your current score is " << playerHandScore << ", since the dealer's upcard is poor(" << dealerHandScore <<"), hit until your score is at least 12.";
        }
        else if(playerHandScore >= PLAYER_LIMIT_PU){
            cout << "Advice: You should stand." << endl;
            cout << "Your current score is " << playerHandScore << ", since the dealer's upcard is poor(" << dealerHandScore <<"), don't risk more and hope dealer goes bust.";
        }
    }
    // When dealer's upcard is a good one (7 to 11)
    // Player limit (good upcard) = 17
    else if (dealerHandScore <= GOOD_UPCARD){
        if(playerHandScore < PLAYER_LIMIT_GU){
            cout << "Advice: You should hit." << endl;
            cout << "Your current score is " << playerHandScore << ", since the dealer's upcard is good(" << dealerHandScore <<"), hit until your score is at least 17.";
        }
        else if(playerHandScore >= PLAYER_LIMIT_GU){
            cout << "Advice: You should stand." << endl;
            cout << "Your current score is " << playerHandScore << ", since the dealer's upcard is good(" << dealerHandScore <<"), don't risk more and hope dealer goes bust.";
        }
    }
    cout << endl << endl;
}
