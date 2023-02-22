// Project UID 1d9f47bfc76643019cfbf037641defe1
#include <iostream>
#include <fstream>
#include <array>
#include <string>
#include "Player.h"
#include "Pack.h"
#include "Card.h"
#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;




class Game {
public:
    int teamOnePoints;
    int teamTwoPoints;
    
    

Game(string shuffleString,string file, int pointnumber, string player0name, string player1name, string player2name, string player3name, string player0type, string player1type, string player2type, string player3type) {
Sstring = shuffleString;
fileName = checkFile(file);
points_to_win = pointnumber;
addPlayer(Player_factory(player0name, player0type));
addPlayer(Player_factory(player1name, player1type));
addPlayer(Player_factory(player2name, player2type));
addPlayer(Player_factory(player3name, player3type));
}

    Game() {
    }
    string checkFile(string fileName) {
   ifstream is(fileName);
   if (is.is_open()) {
   return fileName;
   }
   else {
     return 0;
   }
 }

    
    void set_players(string player0name, string player0type, string player1name, string player1type, string player2name, string player2type, string player3name, string player3type) {
        Player *player0 = Player_factory(player0name, player0type);
        Player *player1 = Player_factory(player1name, player1type);
        Player *player2 = Player_factory(player2name, player2type);
        Player *player3 = Player_factory(player3name, player3type);
        Players.push_back(player0);
        Players.push_back(player1);
        Players.push_back(player2);
        Players.push_back(player3);
    }
    
    void deal(){
      //deals three cards to player 0
        Players[0]->add_card(pack.deal_one());
        Players[0]->add_card(pack.deal_one());
        Players[0]->add_card(pack.deal_one());
        //deals two cards to player 1
        Players[1]->add_card(pack.deal_one());
        Players[1]->add_card(pack.deal_one());
        //deals three cards to player 2
        Players[2]->add_card(pack.deal_one());
        Players[2]->add_card(pack.deal_one());
        Players[2]->add_card(pack.deal_one());
        //deals two cards to player 3
        Players[3]->add_card(pack.deal_one());
        Players[3]->add_card(pack.deal_one());
        //deals two cards to player 0
        Players[0]->add_card(pack.deal_one());
        Players[0]->add_card(pack.deal_one());
        //deals three cards to player 1
        Players[1]->add_card(pack.deal_one());
        Players[1]->add_card(pack.deal_one());
        Players[1]->add_card(pack.deal_one());
        //deals two cards to player 2
        Players[2]->add_card(pack.deal_one());
        Players[2]->add_card(pack.deal_one());
        //deals three cards to player 3
        Players[3]->add_card(pack.deal_one());
        Players[3]->add_card(pack.deal_one());
        Players[3]->add_card(pack.deal_one());
        Card upcard = pack.deal_one();
        cout << "Hand " << hand << endl;
        cout << Players[dealer]->get_name() << " deals" << endl;
        cout << upcard << " turned up" << endl;
    }
 
    void updateHand() {
        ++hand;
    }
    
    void addPlayer(Player* player) {
        Players.push_back(player);
    }
  
    void updateDealer() {
        if (dealer < 4) {
            dealer = dealer + 1;
        }
        else if (dealer == 4) {
            dealer = 0;
        }
    }
 
    void shufflePack () {
        pack.shuffle();
    }
  
 
    void errorMessage() {
        cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
         << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
         << "NAME4 TYPE4" << endl;
    }


   void make_trump() {
      while ((!Players[count]->make_trump(upcard, is_dealer(), round, order_up_suit)) && (count < 4)) {


          count++;
      }
      updateRound();
      
  }
    void updateRound() {
        round = round + 1;
        count = 0; 
    }
    bool is_dealer(){
        if (count == 0) {
            return true;
        } else {
            return false;
        }
    }
    
    //GETTER, RETURNS PRIVATE MEMBERS OF TEAM ONE AND TWO SCORES
    
    void set_points_to_win(int number){
        points_to_win = number;
    }
    
    int get_team1_score() {
        return teamOneScore;
    }
    
    int get_team2_score() {
        return teamTwoScore;
    }
    
    int get_hand() const {
        return hand;
    }
        
    Player* get_dealer() {
        dealer = hand % 4;
        return Players[dealer];
    }


private:
    Card upcard;
    int round;
    Suit order_up_suit;
    int count = 0;
    
    vector<Player*> Players;
    Pack pack;
    int dealer;
    int hand;
    string shuffle;
    int teamOneScore = 0;
    int teamTwoScore = 0;
    string points_to_win;
     string Sstring;
     string fileName; 
};




int main(int argc, char *argv[]) {
   // bool game_over = false;
    
    // sets players to input
    string shuffleString = argv[2];
    string file = argv[1]; 
    string player0name = argv[4];
    string player0type = argv[5];
    string player1name = argv[6];
    string player1type = argv[7];
    string player2name = argv[8];
    string player2type = argv[9];
    string player3name = argv[10];
    string player3type = argv[11];
    int pointnumber = atoi(argv[3]);
    
 Game g(shuffleString,file, pointnumber, player0name, player1name, player2name, player3name, player0type, player1type, player2type, player3type);
 //int pointnumber = atoi(argv[3]);
// Game g(pointnumber, player0name, player1name, player2name, player3name, player0type, player1type, player2type, player3type);
 /*PRINT ERROR MESSAGE IF:
 - If user does not put 12 arguments in to terminal, print error message
 - If points to win is not within range
 - if argument 3 is not the string shuffle or no shuffle
 - if argument 5,7,9,11 are not player types
 */
//|| (((argv[2] != "shuffle")) || (argv[2] != "noshuffle" ))


 if ((argc != 12) || ((atoi(argv[3]) < 1) || (atoi(argv[3]) > 100))){
 g.errorMessage();
 return 1;
 }


 if ((argv[5] || argv[7] || argv[9] || argv [11]) != ("Simple" || "Human")) {
   g.errorMessage();
   return 1;
 }


 g.checkFile(file);
 ifstream is(argv[1]);
 if (!is.is_open()) {
    string pack_filename = argv[1];
   cout << "Error opening " << pack_filename << endl;
 }
 //set argument 3 to points to win private variable
  //Player * player0 = Player_factory(player0name, player0type);


 //Game addPlayer(player0 player0);
  g.deal();
 g.make_trump();






}
