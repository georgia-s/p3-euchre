// Project UID 1d9f47bfc76643019cfbf037641defe1
#include <iostream>
#include <array>
#include <string>
#include "Player.h"
#include <vector>
using namespace std;

/*INPUT IS GIVEN
1 pack file
2 shuffled
3 points to win
4,5 player 0 name & type
6,7 player 1
8,9 player 2
10,11 player 3
/*
//**LOGIC & VARIABLES NEEDED**
1. NEED A WAY TO KEEP SCORE
2. NEED A WAY TO TRACK THE CURRENT DEALER
  - int dealer_posistion = 0;
  - increments dealer each round, when you get to player 3, use moduolo
3. a vector of players <player0,player1,player2,player3>
4. keeps track of what player is leading each trick
5. A way to keep track of how many tricks a team has won in a given round
6. Way to keep track what trump is
7. way to keep track which team called trump
*/

/* PLAY THE GAME
1. Determining whether a game has won yet
- check if either team has >= pointsToWin
2. deal the cards to each player
- 3 2 3 2 2 3 2 3
3. Get the upcard
- ask each player if they want to make trump
- in round 2, you have to ask which suit they want to make trump 
4. have the player to the left of the dealer lead
- IE. if dealer is in position 0, player in pos 1 leads
- play 5 tricks to euchre
- player 0 play a card, then player one plays a card...
- after they all play a card, determine who the winner of that trick is, the winner of that trick dictates who is the leader for the next trick
- card less consideres trump suit
  - helps to determine who wis the suit
  - only considers 2 cards
  Trump is hearts
  <player0,player1,player2,player3>
  <card0,card1,card2,card3>
  - have to compare them all seperately
  <9Diamonds,AceDiamonds,9Hearts,10ofDiamonds>
- bracket style 
- trick point goes to winner 
- leader is whoever played the winner, whoever played the highest card in the game
- DETERMINING THE SCORE
  - 1. winning team did not call trump 
      - they will get 2 points given to them
  - 2. winning team called trump 
      - did they get 3/5, 4/5, or 5/5 tricks?
        - 3/5 or 4/5 gets 1 points and 5/5 gets 2 points
    - repeat cycle at the top and check if anyone has won yet! 




// STEPS
/*
1. Read in input
2. Validate input
3. Play the game
*/
// We recommend writing a Game ADT.

// The Game and its helper functions do the hard work,
// and the main() function is simple.

class Game
{
public:
//GAME IS WON BOOL
bool gameWon (Game points_to_win, Game teamOneScore, Game teamTwoScore) {
  if ((teamOneScore == points_to_win) ||(teamTwoScore == points_to_win)){
    return true;
  }
  else {
    return false; 
  }
}
//CHECK IF PLAYER IS SIMPLE OR HUMAN 
bool isHuman(Game string str) {
  if (str == simple) {
    return false; 
  }
  else {
    return true; 
  }
}

  // constructer
  Game(/* game details */);
  // void play();
  void error_Message()
  {
    // if stream is bad or something
    cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
         << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
         << "NAME4 TYPE4" << endl;
  }
  //GETTER, RETURNS PRIVATE MEMBERS OF TEAM ONE AND TWO SCORES 
  int get_score(int team) {
    if (team == 1) {
      return teamOneScore;
    }
    else if (team == 2) {
      return teamTwoScore; 
    }
  }
  int get_dealer_posistion(int dealer_posistion) {
    return dealer_posistion; 
  }

private:
  // std::vector<Player*> players;
  // Pack pack;
  // Which helper functions would help simplify the play() function?
  //  Add these as private member functions.
  //  Functions that shuffle, deal, make trump,
  // and play a hand are a good starting point.
  // void shuffle();
  // void deal(/* ... */);
  // void make_trump(/* ... */);
  // void play_hand(/* ... */);
int teamOneScore = 0;
int teamTwoScore = 0;
int pointstowin = 0; 
vector<string> players;

//DEAL FUNCTION
void Deal {
  for (int i = 0; i < pack.size(); i++){
//CALL IN ADD CARD  from player.cpp
  }

}
//READS IN USER INPUT
istream & operator>>(istream &is) {
   string name1;
    string name2;
    string name3;
    string name4;
    string name1_type;
    string name2_type;
    string name3_type;
    string name4_type;
    string pack;
    string shuffle;
    string points_to_win;
  while (is) {
 is >> pack >> shuffle >> points_to_win >> name1 >> name1_type >>
        name2 >> name2_type >> name3 >> name3_type >> name4 >> name4_type;
  }
  return is; 
}
//OUTS INPUT
ostream & operator<<(ostream &os){


}

// It should have a constructor that takes in details like the players,
// points to win, etc. and a public play() function.
// DEFAULT CONSTRUCTOR
Game::Game()
{
}
// NON DEFAULT CONSTRUCTOR
// Game::Game() {
//  Player get_name();

}; 

int main() {
/*
STEP 1- READ IN INPUT & VALIDATE IT 
- To compile and run a Euchre game with four players.
- make euchre.exe
- ./euchre.exe pack.in noshuffle 1 Adi Simple
- Barbara Simple Chi-Chih Simple Dabbala Simple
-  Assume pack_filename is a variable
-  containing the specified pack filename from argv
- get stream
-- cout << "Error opening " << ///pack_filename << endl;
STEP 2- 
STEP 3
STEP 4 
- Ask player if they would like to make trump IF HUMAN
*/
cout << "Would you like to make trump? " << endl << "Please enter yes/no"; 
string answer;
// cin << answer; 


  // 

  // Check if human name or simple name to decide which function to call

  // At the beginning of each hand, announce the hand,
  // starting at zero, followed by the dealer and the upcard.
  // Print the decision of each player during the making procedure.
  // Print an extra newline when making, adding, and discarding is complete.
  // Each of the five tricks is announced, including the lead,
  // cards played and the player that took the trick.
  // Print an extra newline at the end of each trick.
  // At the end of the hand, print the winners of the hand.
  // When printing the names of a partnership, print the player
  // with the lower index first. For example, Adi was specified on
  // the command line before Chi-Chih, so he goes first.
  // If a march occurs, print march! followed by a newline.
  // If euchre occurs, print euchred! followed by a newline.
  // If neither occurs, print nothing.
  // Print the score, followed by an extra newline.
  // When the game is over, print the winners of the game.
} // At the end of a game, delete the Player objects created by the Player_factory.

// or (size_t i = 0; i < players.size(); ++i) {
// delete players[i];
//}

// SCORING
// The team that takes the majority of tricks receives points for that hand.
// If the winning team had also ordered up, they get 1 point for taking 3 or 4 tricks,
// and 2 points for taking all 5.
//  Taking all 5 tricks is called a march. If the winning team did not order up,
// they receive 2 points for taking 3, 4 or 5 tricks, which is called euchred.

// the first side to reach 10 points wins the game.
// In this project, the number of points needed to
// win is specified when the program is run.
