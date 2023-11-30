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
//Game(string fileName,int number, string const arr[8]) {
    Game(string fileName,int number, string const arr[8]) {
        Init_pack(fileName);
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
        checkpointstowin(number);
        points_to_win = number;
    }
    
    void print_score() {
        cout << *Players[0] << " and " << *Players[2]
        << " have " << teamOneScore << " points" << endl;
        cout << *Players[1] << " and " << *Players[3]
        << " have " << teamTwoScore << " points" << endl << endl;
    }
    
    void Init_pack(string file) {
        ifstream packf;
        packf.open(file);
        if (!packf.is_open()) {
            cout << "Error opening " << file << endl;
        }
        pack = Pack(packf);
    }
    
    void print_win(int set_points_to_win) {
        if (teamOneScore >= set_points_to_win) {
            cout << *Players[0] << " and "
            << *Players[2] << " win!" << endl;
        }
        else {
         cout << *Players[1] << " and "
          << *Players[3] << " win!" << endl;
        }
    }
    
    void deal(){
        //cout << "Hand" << hand;
        //deals three cards to player 1
        Players[(dealer + 1) % 4]->add_card(pack.deal_one());
        Players[(dealer + 1) % 4]->add_card(pack.deal_one());
        Players[(dealer + 1) % 4]->add_card(pack.deal_one());
        //deals two cards to player 2
        Players[(dealer + 2) % 4]->add_card(pack.deal_one());
        Players[(dealer + 2) % 4]->add_card(pack.deal_one());
        //deals three cards to player 3
        Players[(dealer + 3) % 4]->add_card(pack.deal_one());
        Players[(dealer + 3) % 4]->add_card(pack.deal_one());
        Players[(dealer + 3) % 4]->add_card(pack.deal_one());
        //deals two cards to player 0
        Players[dealer]->add_card(pack.deal_one());
        Players[dealer]->add_card(pack.deal_one());
        //deals two cards to player 1
        Players[(dealer + 1) % 4]->add_card(pack.deal_one());
        Players[(dealer + 1) % 4]->add_card(pack.deal_one());
        //deals three cards to player 2
        Players[(dealer + 2) % 4]->add_card(pack.deal_one());
        Players[(dealer + 2) % 4]->add_card(pack.deal_one());
        Players[(dealer + 2) % 4]->add_card(pack.deal_one());
        //deals two cards to player 3
        Players[(dealer + 3) % 4]->add_card(pack.deal_one());
        Players[(dealer + 3) % 4]->add_card(pack.deal_one());
        //deals three cards to player 0
        Players[dealer]->add_card(pack.deal_one());
        Players[dealer]->add_card(pack.deal_one());
        Players[dealer]->add_card(pack.deal_one());
        
        upcard = pack.deal_one();
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
        if (dealer < 3) {
            dealer = dealer + 1;
        }
        else if (dealer == 3) {
          dealer = 0;
        }
    }
    
    void shufflePack () {
        pack.shuffle();
        shuffled = true;
    }
    
    void make_trump() {
        order_up_suit = upcard.get_suit();
        bool trump_made = false;
        index = dealer + 1;
        int times = 0;
        while (trump_made == false && times < 8) {
            if (times == 4) {
                round = 2;
                order_up_suit = Suit_next(order_up_suit);
            }
            if (index == 4){
                index = 0;
            }
            trump_made = Players[index]->make_trump(upcard,
                                                      is_dealer(), round, order_up_suit);
            
            if (trump_made == true) {
                cout << *Players[index] << " orders up "
                << order_up_suit << endl << endl;
            } else {
                cout << *Players[index] << " passes" << endl;
                index++;
                times++;
            }
            
            if  (trump_made == true && round == 1) {
                Players[dealer]->add_and_discard(upcard);
            }
        }
        person_who_ordered_up = index;
    }
    
    void del_players() {
        for(int i = 0; i < int(4); ++i) {
            delete Players[i];
        }
    }
    
    void trickIncrementer(int playernumber) {
        if(playernumber == 0 || playernumber == 2) {
            trickteam1++;
            cout << Players[playernumber]->get_name()
            << " takes the trick" << endl << endl;
        }
        if(playernumber == 1 || playernumber == 3) {
            trickteam2++;
            cout << Players[playernumber]->get_name()
            << " takes the trick" << endl << endl;
        }
    }
    
    
    void pointIncrementer(int playernumber) {
        if(playernumber == 0 || playernumber == 2) {
              teamOneScore++;
          }
          if(playernumber == 1 || playernumber == 3) {
              teamTwoScore++;
          }
          //increment team 1 score
          //increment team 2 score
    }
    
    
    void scoring(int winner){ // team one wins
        if ((trickteam1 > trickteam2) && ((trickteam1 + trickteam2) == 5)) {
            cout << *Players[0] << " and " << *Players[2] << " win the hand" << endl;
            playernumber = 0;
            if (person_who_ordered_up == 0 || person_who_ordered_up == 2) {
                if (trickteam1 == 3 || trickteam1 == 4) {
                    pointIncrementer(0);
                } else if (trickteam1 == 5) {
                    pointIncrementer(0);
                    pointIncrementer(0);
                    printMarch();
                }
            } else if (trickteam1 == 3 || trickteam1 == 4 || trickteam1 == 5) {
                pointIncrementer(0);
                pointIncrementer(0);
                printeuchre();
            }
            print_score();
        } else if ((trickteam1 < trickteam2) // team two wins
                   && ((trickteam1 + trickteam2) % 5 == 0)) {
            cout << *Players[1] << " and " << *Players[3]
            << " win the hand" << endl;
            playernumber = 1;
            if (person_who_ordered_up == 1
                || person_who_ordered_up == 3) {
                if (trickteam2 == 3 || trickteam2 == 4) {
                    pointIncrementer(1);
                } else if (trickteam2 == 5) {
                    pointIncrementer(1);
                    pointIncrementer(1);
                    printMarch();
                }
            } else if (trickteam2 == 3 || trickteam2 == 4
                    || trickteam2 == 5) {
                pointIncrementer(1);
                pointIncrementer(1);
                printeuchre();
            }
            print_score();
        }
    }
    
    void playFull() {
        while (teamOneScore < points_to_win && teamTwoScore < points_to_win) {
            pack.reset();
            deal();
            make_trump();
            play();
            hand++;
            trick = 0;
            updateDealer();
            round = 1;
            trickteam1 = 0;
            trickteam2 = 0;
            if (shuffled) {
                shufflePack();
            }
        }
        print_win(points_to_win);
    }

    void play() {
        setLeader(playernumber); //pass in a trump suit
        while (trick < 5){
            ledcard = Players[(leader + 0)  % 4]->lead_card(order_up_suit);
            cout << ledcard << " led by " << *Players[(leader + 0)  % 4] << endl;
            Card a = Players[(leader + 1) % 4]->play_card(ledcard,order_up_suit);
            cout << a << " played by " << *Players[(leader + 1) % 4] << endl;
            Card b = Players[(leader + 2) % 4]->play_card(ledcard,order_up_suit);
            cout << b << " played by " << *Players[(leader + 2) % 4] << endl;
            Card c = Players[(leader + 3) % 4]->play_card(ledcard,order_up_suit);
            cout << c << " played by " << *Players[(leader + 3) % 4] << endl;
            Card trick_winner;
            if (Card_less(a,b,ledcard,order_up_suit) == true) {
                if (Card_less(c,b,ledcard,order_up_suit) == true) {
                    playernumber = (leader + 2) % 4;
                    trick_winner = b;
                } else if (Card_less(c,b,ledcard,order_up_suit) == false) {
                    playernumber = (leader + 3) % 4;
                    trick_winner = c;
                }
            } else if (Card_less(a,b,ledcard,order_up_suit) == false) {
                if (Card_less(c,a,ledcard,order_up_suit) == true) {
                    playernumber = (leader + 1) % 4;
                    trick_winner = a;
                } else if (Card_less(c,a,ledcard,order_up_suit) == false) {
                    playernumber = (leader + 3) % 4;
                    trick_winner = c;
                }
            }
            if (Card_less(trick_winner,ledcard,ledcard,order_up_suit)) {
                playernumber = (leader) % 4;
                trick_winner = ledcard;
            }
            trickIncrementer(playernumber);
            leader = playernumber;
            scoring(playernumber);
            trick++;
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
  if ((Players[playernum] == Players[0])
      || (Players[playernum] == Players[2])){
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
    if (trick == 0) {
        leader = dealer + 1;
    } else {
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
    if (index == dealer) {
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
    int index = 0;
int trick = 0;
  int person_who_ordered_up;
  int upcardplayer;
  int playernumber = 1;
  Card upcard;
  int dealernumber;
  Card ledcard;
  int round = 1;
  Suit order_up_suit;
  int count = 0;
  vector<Card*> Table;
  vector<Player*> Players;
  Pack pack;
    bool shuffled = false;
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
  string array[8];
};

int main(int argc, char *argv[]) {
  // sets players to input
    for(int i = 0; i < argc; ++i) {
        cout << argv[i] << " ";
    }
    cout << endl;

  //CHECK ARRAY
    const string peoplelist[] =
    {argv[4],argv[5],argv[6],argv[7],argv[8],argv[9],argv[10],argv[11]};
    Game g = Game(argv[1],atoi(argv[3]),peoplelist);
   
    if (std::string(argv[2]) == "shuffle") {
        g.shufflePack();
    }
    
    g.playFull();
    g.del_players();
    return 0;
  }

