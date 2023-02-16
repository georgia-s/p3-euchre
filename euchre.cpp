// Project UID 1d9f47bfc76643019cfbf037641defe1
#include <iostream>
using namespace std;
//We recommend writing a Game ADT. 
//It should have a constructor that takes in details like the players, points to win, etc. and a public play() function.
// The Game and its helper functions do the hard work, and the main() function is simple.
class Game {
 public:
 //constructer
  Game(/* game details */);
  void play();
   private:
  std::vector<Player*> players;
  Pack pack;
  //Which helper functions would help simplify the play() function? Add these as private member functions. Functions that shuffle, deal, make trump, and play a hand are a good starting point.
  void shuffle();
  void deal(/* ... */);
  void make_trump(/* ... */);
  void play_hand(/* ... */);

};

Game:Game() {
    rank = TWO;
    suit = SPADES;
}
//NON DEFAULT CONSTRUCTOR 
Game::Game() {
    Player get_name(); 
    
}

//To compile and run a Euchre game with four players.
    //make euchre.exe
    // ./euchre.exe pack.in noshuffle 1 Adi Simple Barbara Simple Chi-Chih Simple Dabbala Simple
int main() {
    // Assume pack_filename is a variable containing
// the specified pack filename from argv
cout << "Error opening " << pack_filename << endl;
  cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
     << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
     << "NAME4 TYPE4" << endl;

}//At the end of a game, delete the Player objects created by the Player_factory.

//or (size_t i = 0; i < players.size(); ++i) {
  //delete players[i];
//}