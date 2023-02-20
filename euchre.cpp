// Project UID 1d9f47bfc76643019cfbf037641defe1
#include <iostream>
#include <array>
#include <string>
#include "Player.h"
using namespace std;

//We recommend writing a Game ADT.


//The Game and its helper functions do the hard work,
//and the main() function is simple.

class Game {
 public:
 //constructer
  Game(/* game details */);
  //void play();
    void error_Message() {
    //if stream is bad or something 
  cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;
  }

  

   private:
  //std::vector<Player*> players;
//Pack pack;
//Which helper functions would help simplify the play() function?
// Add these as private member functions.
// Functions that shuffle, deal, make trump,
//and play a hand are a good starting point.
  //void shuffle();
  //void deal(/* ... */);
  //void make_trump(/* ... */);
  //void play_hand(/* ... */);
  //Name strings 
  
//EFFECTS Reads a Suit from a stream, for example "Spades" -> SPADES
std::istream & operator>>(std::istream &is) {
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
  while (is) {}
  is >> pack >> shuffle >> points_to_win >> name1 >> name1_type >>
   name2 >> name2_type >> name3 >> name3_type >> name4 >> name4_type; 
    return is;
  }


};
//It should have a constructor that takes in details like the players,
//points to win, etc. and a public play() function.
//DEFAULT CONSTRUCTOR 
Game::Game() {
}
//NON DEFAULT CONSTRUCTOR 
//Game::Game() {
   // Player get_name(); 
    
//}


int main() {
    //To compile and run a Euchre game with four players.
    //make euchre.exe
    // ./euchre.exe pack.in noshuffle 1 Adi Simple
    // Barbara Simple Chi-Chih Simple Dabbala Simple
    //get stream 
    // Assume pack_filename is a variable
    //containing the specified pack filename from argv
//cout << "Error opening " << ///pack_filename << endl;

     //Check if human name or simple name to decide which function to call

//At the beginning of each hand, announce the hand,
    //starting at zero, followed by the dealer and the upcard.
//Print the decision of each player during the making procedure.
    //Print an extra newline when making, adding, and discarding is complete.
//Each of the five tricks is announced, including the lead,
    //cards played and the player that took the trick.
    //Print an extra newline at the end of each trick.
//At the end of the hand, print the winners of the hand.
    //When printing the names of a partnership, print the player
    //with the lower index first. For example, Adi was specified on
    //the command line before Chi-Chih, so he goes first.
//If a march occurs, print march! followed by a newline.
    //If euchre occurs, print euchred! followed by a newline.
    //If neither occurs, print nothing.
//Print the score, followed by an extra newline.
//When the game is over, print the winners of the game.
}//At the end of a game, delete the Player objects created by the Player_factory.

//or (size_t i = 0; i < players.size(); ++i) {
  //delete players[i];
//}

//SCORING
//The team that takes the majority of tricks receives points for that hand. 
//If the winning team had also ordered up, they get 1 point for taking 3 or 4 tricks,
//and 2 points for taking all 5.
// Taking all 5 tricks is called a march. If the winning team did not order up,
//they receive 2 points for taking 3, 4 or 5 tricks, which is called euchred.

// the first side to reach 10 points wins the game.
//In this project, the number of points needed to
//win is specified when the program is run.
