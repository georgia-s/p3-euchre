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

  Game(int number, string const arr[8]) {
    Player *player0 = Player_factory(arr[0], arr[1]);
    Player *player1 = Player_factory(arr[2], arr[3]);
    Player *player2 = Player_factory(arr[4], arr[5]);
    Player *player3 = Player_factory(arr[6], arr[7]);
     Players.push_back(player0);
    Players.push_back(player1);
    Players.push_back(player2);
    Players.push_back(player3);
    checkpointstowin(number); 
    points_to_win = number;
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
    //cout << "Hand" << hand; 
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
  void make_trump() {
    bool trump_made = false;
    while (trump_made == false && count < 4) {
      trump_made = Players[count]->make_trump(upcard, is_dealer(),
       round, order_up_suit);
           if (trump_made == false) {
               count++;
           }
       }
       upcardplayer = count; 
       updateRound();
  }
void trickIncrementer(int playernumber) {
    if(playernumber == 0 || playernumber == 2) {
      
      trickteam1++; 
      cout << Players[playernumber]->get_name() <<" takes the trick" << endl << endl;
    }
    if(playernumber == 2 || playernumber == 3) {
     
      trickteam2++; 
       cout << Players[playernumber]->get_name() <<" takes the trick" << endl << endl; 
    }


  }

void pointIncrementer(int playernumber) {
    if(playernumber == 0 || playernumber == 2) {
      
      teamOneScore++; 
    }
    if(playernumber == 2 || playernumber == 3) {
     
      teamTwoScore++; 
    }
    //increment team 1 score
    //increment team 2 score 

  }

void scoring(int winner){
    
      if (((trickteam1 > trickteam2) && (trickteam1 + trickteam2 == 5) 
      && (team_one_ordered_up(winner) == true)) 
 ||       ((trickteam1 < trickteam2) && (trickteam1 + trickteam2 == 5) 
 && (team_one_ordered_up(winner) == false))) {
        if((trickteam1 == 3 || trickteam1 == 4) || (trickteam2 == 3
         || trickteam2 == 4)){
          pointIncrementer(winner);
        }
        else {
          pointIncrementer(winner);
          pointIncrementer(winner);
          printMarch(); 
        }
        
 }
 else if (((trickteam1 > trickteam2) && (trickteam1 + trickteam2 == 5) 
 && (team_one_ordered_up(winner) == false)) 
 || ((trickteam1 < trickteam2) && (trickteam1 + trickteam2 == 5) 
 && (team_one_ordered_up(winner) == true))) {
  pointIncrementer(winner);
  pointIncrementer(winner);
  printeuchre();
 }

 }
void play() {
    if (round == 1) {
      setLeader(playernumber);
    }
  //pass in a trump suit
    while (teamOneScore + teamTwoScore < points_to_win){
      Players[leader]->lead_card(order_up_suit);       
      Card a = Players[(leader + 1) % 4]->play_card(upcard,order_up_suit);
      Card b = Players[(leader + 2) % 4]->play_card(upcard,order_up_suit);
      Card c = Players[(leader + 3) % 4]->play_card(upcard,order_up_suit);
      if (Card_less(a,b,ledcard,order_up_suit) == true && Card_less(c,b,ledcard,order_up_suit) == true) {
        trickIncrementer(playernumber);
         setLeader(playernumber);
         scoring(playernumber);
         round++; 
        
        //Card b wins
            //Player b wins trick   
            //set winner to next leader
      }
          //card a wins
      else if (Card_less(b,a,ledcard,order_up_suit) == true
       && Card_less(c,a,ledcard,order_up_suit) == true) {
        //players i and i+2 get a score
        //pointIncrementer(playernumber);
        trickIncrementer(playernumber);
        setLeader(playernumber);
        scoring(playernumber);
        round++; 
          //card a wins trick
          
      }
      else {
        //pointIncrementer(playernumber);
        trickIncrementer(playernumber);
         setLeader(playernumber);
         scoring(playernumber);
         round++; 
        //card c wins trick 
      }
    }
}
//HELPER FUNCTIONS 
bool team_one_ordered_up(int playernum){
  Players[upcardplayer];
  if (isTeam1(playernum)) {
    return true; 
  }
  else {
    return false; 
  }
  
}
bool isTeam1(int playernum) {
  if ((Players[playernum] == Players[0]) || (Players[playernum] == Players[2])){
    return true; 
  }
  else {
    return false;
  }

}
bool team_1_wins() {
  if ((isTeam1(playernumber) == true) && (Players[playernumber] 
  == Players[leader]))  {
    return true;

  }
  else {
    return false; 
  }
}
int checkpointstowin(int points) {
  if(points < 1 || points > 100) {
    errorMessage();
    return 1; 
  }
  else {
    return 0;
  }

}

void setLeader(int plyrnumber){
  int counter = 0; 
  if (round == 1) {
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
  else {
    leader = plyrnumber; 
  }
}
void printMarch(){
    cout << "march!" << endl;
 }
void printeuchre(){
    cout << "euchred!" << endl;
 }
void updateRound() {
  round++; 
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
void errorMessage() {
  cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
      << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
      << "NAME4 TYPE4" << endl;
}
//GETTER, RETURNS PRIVATE MEMBERS OF TEAM ONE AND TWO SCORES
    
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
  int upcardplayer;
  int playernumber = 0; 
  Card upcard;
  int dealernumber; 
  Card ledcard; 
  int round = 1;
  Suit order_up_suit;
  int count = 0;
  vector<Card*> Table;
  vector<Player*> Players;
  Pack pack;
  int dealer = 0;
  int hand = 0;
  int trickteam1 = 0; 
  int trickteam2 = 0; 
  int leader; 
  string shuffle;
  string peopleArray[9];
  int teamOneScore = 0;
  int teamTwoScore = 0;
  int points_to_win;
  //int ptstowin = stoi(points_to_win);
};

int main(int argc, char *argv[]) {
    // sets players to input
  ifstream is;
  is.open(argv[1]);
  if (!is.is_open()) {
    cout << "Error opening " << argv[1] << endl;
  }
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
  string peoplelist[8] ={player0name,player0type,player1name,player1type,player2name,
    player2type,player3name,player3type};
    // opens pack
  Game g = Game(pointsnumber,peoplelist);
    
    Pack p(is);
    // creates the players
   
    //g.set_players(player0name, player0type, player1name, player1type, 
    //player2name, player2type, player3name, player3type);
    //g.set_points_to_win(pointsnumber); 
  
    //if ((argv[5] || argv[7] || argv[9] || argv [11]) != ("Simple" || "Human")) {
      //  g.errorMessage();
   //     return 1;
    //}
    
    
  if (shuffle == "shuffle") {
    g.shufflePack();
  }

  
  
        g.deal();
        g.make_trump();
        g.play();
        
    return 0; 
}




