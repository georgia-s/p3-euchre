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
  Game() {}
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

   void print_score() {
        cout << *Players[0] << " and " << *Players[2]
        << " have " << teamOneScore << "points" << endl;
        cout << *Players[1] << " and " << *Players[3]
        << " have " << teamTwoScore << "points" << endl;
    }
    
  void print_win(int set_points_to_win) {
      if (teamOneScore >= set_points_to_win) {
        cout << *Players[0] << " and " << *Players[2] << " win!" << endl;
      }
      else {
        cout << *Players[1] << " and " << *Players[3] << " win!" << endl;    
      }
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
       bool trump_made = false;
       while (trump_made == false && count < 4) {
           trump_made = Players[count]->make_trump(upcard, is_dealer(), round, order_up_suit);
           if (trump_made == false) {
               count++;
           }
       }
       updateRound();
  }
  void pointIncrementer(int playernumber) {
    if(playernumber == 0 || playernumber == 2) {
      teamOneScore++; 
      trickteam1++; 
    }
    if(playernumber == 2 || playernumber == 3) {
      teamTwoScore++; 
      trickteam2++; 
    }
    //increment team 1 score
    //increment team 2 score 

  }

 
  void play() {
  //pass in a trump suit
    void setLeader();
    while (trickteam1 + trickteam2 <= 5) {
      Players[leader]->lead_card(order_up_suit);       
      Card a = Players[(leader + 1) % 4]->play_card(upcard,order_up_suit);
      Card b = Players[(leader + 2) % 4]->play_card(upcard,order_up_suit);
      Card c = Players[(leader + 3) % 4]->play_card(upcard,order_up_suit);
      if (Card_less(a,b,ledcard,order_up_suit) == true && Card_less(c,b,ledcard,order_up_suit) == true) {
        pointIncrementer(playernumber);
        leader++;
            //Player b wins trick   
      }
          //card a wins
      else if (Card_less(b,a,ledcard,order_up_suit) == true && Card_less(c,a,ledcard,order_up_suit) == true) {
        //players i and i+2 get a score
        pointIncrementer(playernumber);
          //card a wins trick
          leader++;
      }
      else {
        pointIncrementer(playernumber);
        //card c wins trick 
      }
    }
}
bool isMarch(){
  if(trickteam1 || trickteam2 == 5) {
    isMarch() == true; 
  }
  else {
    isMarch() == false; 
  }
}
void setLeader(){
  int counter = 0; 
  while (is_dealer() == false) {
    counter++; 
  }
  if (is_dealer() == true) {
     Players[dealernumber] = Players[counter]; 
      if (dealernumber< 3) {
        leader = dealer + 1; 
      }
    }
    if (dealernumber < 3) {
      leader = dealer + 1; 
    }
}
 void printMarch(){
  if (isMarch() == true) {
    cout << "march!" << endl;
  }
 }
void updateRound() {
  round = round + 1;
  count = 0; 
}
 
  bool is_dealer(){
    if (count == 0) {
      return true;
    } 
    else {
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
  int playernumber; 
    Card upcard;
    int dealernumber; 
    Card ledcard; 
    int round = 1;
    Suit order_up_suit;
    int count = 0;
    vector<Card*> Table;
    vector<Player*> Players;
    Pack pack;
    int dealer;
    int hand;
    int trickteam1; 
    int trickteam2; 
    int leader; 
    string shuffle;
    int teamOneScore = 0;
    int teamTwoScore = 0;
    string points_to_win;
};


int main(int argc, char *argv[]) {
    bool game_over = false;
    
    // sets players to input
    string player0name = argv[4];
    string player0type = argv[5];
    string player1name = argv[6];
    string player1type = argv[7];
    string player2name = argv[8];
    string player2type = argv[9];
    string player3name = argv[10];
    string player3type = argv[11];
    string shuffle = argv[2]; 
    int pointsnumber = atoi(argv[3]);
    
    // opens pack
    ifstream is;
    is.open(argv[1]);
    if (!is.is_open()) {
        cout << "Error opening " << argv[1] << endl;
    }
    Pack p(is);
    
    Game g = Game();
    
    // creates the players
    g.set_players(player0name, player0type, player1name, player1type, player2name, player2type, player3name, player3type);
    g.set_points_to_win(pointsnumber); 
  
    if ((argv[5] || argv[7] || argv[9] || argv [11]) != ("Simple" || "Human")) {
        g.errorMessage();
        return 1;
    }
    
    while (!game_over) {
        if (shuffle == "shuffle") {
            g.shufflePack();
        }
        g.deal();
        g.make_trump();
        g.play();
        g.printMarch();
    }
}




