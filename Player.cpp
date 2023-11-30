// Project UID 1d9f47bfc76643019cfbf037641defe1
//  Player.cpp
//  p3-euchre
//
//  Created by Anastasia Kazanas on 2/12/23.
//
#include "Card.h"
#include <string>
#include <vector>
#include "Player.h"
#include <iostream>
#include <algorithm>
#include <cassert>
#include <iostream>

using namespace std;

class SimplePlayer : public Player {
public:
    // default constructor
    SimplePlayer(std::string name) : simple_name(name) {
    }
   
    //EFFECTS returns player's name
    const std::string & get_name() const{
        return simple_name;
    }
    
    //REQUIRES player has less than MAX_HAND_SIZE cards
    //EFFECTS adds Card c to Player's hand
    void add_card(const Card &c){
        if (simple_hand.size() < MAX_HAND_SIZE) {
            simple_hand.push_back(c);
        }
        std::sort(simple_hand.begin(), simple_hand.end());
    }
    //SIMPLE PLAYER MAKE TRUMP 
   bool make_trump(const Card &upcard, bool is_dealer,
                            int round, Suit &order_up_suit) const{
        Suit trump_suit = upcard.get_suit();
        Suit other_color = Suit_next(trump_suit);
        int ace_or_face_same_as_trump_count = 0;
        if (round == 1) {
            for (size_t i=0; i < simple_hand.size(); ++i) {
                if (simple_hand[i].get_suit() == trump_suit
                    && simple_hand[i].is_face_or_ace()) {
                    ace_or_face_same_as_trump_count++;
                } if (simple_hand[i].is_left_bower(trump_suit)) {
                    ace_or_face_same_as_trump_count++;
                }
            } if (ace_or_face_same_as_trump_count >= 2) {
              order_up_suit = trump_suit;
                return true;
            } else {
                return false;
            }
        } if (round == 2) {
            if (is_dealer == true) {
                order_up_suit = other_color;
                return true;
            }
            for (size_t i=0; i < simple_hand.size(); ++i) {
                if (simple_hand[i].get_suit() == other_color
                     && simple_hand[i].is_left_bower(trump_suit)) {
                    ace_or_face_same_as_trump_count++;
                } if (simple_hand[i].get_suit() == other_color
                    && simple_hand[i].is_face_or_ace()
                    && !simple_hand[i].is_left_bower(trump_suit)) {
                    ace_or_face_same_as_trump_count++;
                }
            } if (ace_or_face_same_as_trump_count >= 1) {
                order_up_suit = other_color;
                return true;
            } else {
                return false;
            }
        } return false;
    }
    
    void add_and_discard(const Card &upcard) {
        Suit trump = upcard.get_suit();
        int lowest = 0;
        Card min = simple_hand[0];
        simple_hand.push_back(upcard);
        for(size_t i = 0; i < simple_hand.size(); i++){
            if(Card_less(simple_hand[i], min, trump)){
                min = simple_hand[i];
                lowest = (int)i;
            }
        }
        simple_hand.erase(simple_hand.begin() + lowest);
    }
    
    
    //REQUIRES Player has at least one card
    //EFFECTS  Leads one Card from Player's hand
    //according to their strategy
    //"Lead" means to play the first Card in a trick.
    //The card is removed the player's hand.
     Card lead_card(Suit trump) {
        Card max = simple_hand[0];
         int start = 0;
         bool done = false;
        // num trump cards  before non trump
         while (done == false) {
             if ((simple_hand[start].get_suit() == trump
                 || simple_hand[start].is_left_bower(trump)) && done == false) {
                 start++;
             } else {
                 done = true;
             }
             if (start == simple_hand.size()) {
                 done = true;
             }
        }
         // if there is a mix of trump and non trump cards
         // sets max equal to first non trump card
        if (start != 0 && start != (simple_hand.size())) {
            max = simple_hand[start];
        }
        int trump_count = 0; //counts total trump cards
        for (int i = 0; i < simple_hand.size(); i++) {
            if (simple_hand[i].get_suit() == trump
                || simple_hand[i].is_left_bower(trump)) {
                trump_count++;
            }
        }
         // if not all trump cards
         // max is greatest of non trump cards
         // excludes left bower bc its cosidered trump card
         if (trump_count < simple_hand.size()) {
             for (int i = 0; i < simple_hand.size(); i++) {
                 max = trump_count_less_test(max, trump);
             }
         }
         // if all trump cards, play highest trump
          // right bower is highest, then left
         if (trump_count >= simple_hand.size()) {
             max = trump_count_equal_test(max, trump, start);
         }
         for (int i = 0; i < simple_hand.size(); i++) {
             if (simple_hand[i] == max) {
                 simple_hand.erase (simple_hand.begin() + i);
             }
         }
         return max;
    }
    
    
    Card trump_count_less_test(Card max, Suit trump) {
        for (int i = 0; i < simple_hand.size(); i++) {
            if ((Card_less(max, simple_hand[i], trump))
                && (!simple_hand[i].is_left_bower(trump))
                && (simple_hand[i].get_suit() != trump)) {
                max = simple_hand[i];
            }
        }
        return max;
    }
    
    Card trump_count_equal_test(Card max, Suit trump, int start) {
        //finds out of there is a left and/or right bower present
        Card right_bower;
        Card left_bower;
        bool right_bower_present = false;
        bool left_bower_present = false;
        
        for (int i = 0; i < simple_hand.size(); i++) {
           if (simple_hand[i].is_left_bower(trump)) {
               left_bower_present = true;
               left_bower = simple_hand[i];
           }
           if (simple_hand[i].is_right_bower(trump)) {
               right_bower_present = true;
               right_bower = simple_hand[i];
           }
       }
        for (int i = 0; i < simple_hand.size(); i++) {
            if (right_bower_present == true) {
                max = right_bower;
            }
            if (left_bower_present == true && right_bower_present == false) {
                max = left_bower;
            }
            if(((start == simple_hand.size()))
               && (Card_less(max, simple_hand[i], trump))
               && (right_bower_present == false)
               && (left_bower_present == false)) {
                max = simple_hand[i];
            }
        }
        return max;
    }

    
    
    //REQUIRES Player has at least one card
    //EFFECTS Plays one Card from Player's hand
    //according to their strategy.
    //The card is removed from the player's hand.
    Card play_card(const Card &led_card, Suit trump){
        Suit ledcard_suit = led_card.get_suit();
        if (led_card.is_left_bower(trump)) {
            ledcard_suit = trump;
        }
        Card played = simple_hand[0], max = simple_hand[0], min = simple_hand[0];
        int count = 0; // dont set lowest to leftbower or trump
        bool done = false;
       // num trump cards  before non trump
        while (done == false) {
            if ((simple_hand[count].get_suit() == trump
                || simple_hand[count].is_left_bower(trump)) && done == false) {
                count++;
            } else {
                done = true;
            }
            if (count == simple_hand.size()) {
                done = true;
            }
       }
        
        // if all trump suit, make sure not set to left/right bower
        if (count == simple_hand.size()) {
            count = 0;
            done = false;
            
            while (done == false) {
                if ((simple_hand[count].is_left_bower(trump)
                    || simple_hand[count].is_right_bower(trump))
                    && done == false) {
                    count++;
                } else {
                    done = true;
                }
                if (count == simple_hand.size()) {
                    done = true;
                }
           }
            
            if (count < simple_hand.size()) { //if one bower found
                min = simple_hand[count];
            } else {
                min  = simple_hand[0];
            }
        } else {
            min = simple_hand[count];
        }
        bool same_suit = false;
        same_suit = find_out_if_same_suit(led_card, ledcard_suit,
                                          same_suit, trump);
        if (same_suit == true) {  // can follow suit, plays highest
            max = same_suit_testing(max, trump, led_card, ledcard_suit);
            played = erase_card(max, played);
        }
        else { // cant follow suit, so plays lowest
            min = play_lowest_testing(min, trump);
            played = erase_card(min, played);
        }
        return played;
    }
    
    Card erase_card(Card junk, Card played) {
        for (int i = 0; i < simple_hand.size(); i++) {
            if (simple_hand[i] == junk) {
                played = junk;
                simple_hand.erase (simple_hand.begin() + i);
                return played;
            }
        }
        return played;
    }
    
    bool find_out_if_same_suit(Card led_card, Suit ledcard_suit,
                               bool same_suit, Suit trump) {
        for (int i = 0; i < simple_hand.size(); i++) {
            if (simple_hand[i].get_suit() == ledcard_suit
                && !simple_hand[i].is_left_bower(trump)) {
                same_suit = true;
            }
            if (ledcard_suit == trump
                && simple_hand[i].is_left_bower(trump)) {
                same_suit = true;
            }
            if (led_card.is_left_bower(trump)
                && simple_hand[i].get_suit() == trump) {
                same_suit = true;
            }
        }
        return same_suit;
    }
    
    
    Card play_lowest_testing(Card min, Suit trump) {
        int trump_suit_count = 0;
        for (int i = 0; i < simple_hand.size(); i++) {
            if (simple_hand[i].get_suit() == trump
                || simple_hand[i].is_left_bower(trump) == true) {
                trump_suit_count++;
            }
        }
        // all non led suit cards are trump suit cards
        if (trump_suit_count >= simple_hand.size()) {
            min = trump_suit_count_equal(min, trump);

        }
        else if (trump_suit_count < simple_hand.size()) {
            min = trump_suit_count_less(min, trump);
        }
        return min;
    }
    
    Card trump_suit_count_equal(Card min, Suit trump){
        bool notReached = true;
        for (int i = 0; i < simple_hand.size(); i++) {
            if (simple_hand[i] <= min && !simple_hand[i].is_left_bower(trump)
                && !simple_hand[i].is_right_bower(trump)) {
                min = simple_hand[i];
                notReached = false;
            }
        }
        if (notReached == true){
            for (int i = 0; i < simple_hand.size(); i++) {
                if (simple_hand[i].is_left_bower(trump)) {
                    min = simple_hand[i];
                } else if (simple_hand[i].is_right_bower(trump)) {
                    min = simple_hand[i];
                }
            }
        }
        return min;
    }
    
    Card trump_suit_count_less(Card min, Suit trump){
        for (int i = 0; i < simple_hand.size(); i++) {
            if (simple_hand[i].get_rank() < min.get_rank()
                && !simple_hand[i].is_left_bower(trump)
                && simple_hand[i].get_suit() != trump) {
                min = simple_hand[i];
            } else if (simple_hand[i].get_rank() == min.get_rank()
                       && simple_hand[i].get_suit() < min.get_suit()
                       && !simple_hand[i].is_left_bower(trump)
                       && simple_hand[i].get_suit() != trump) {
                min = simple_hand[i];
            }
        }
        return min;
    }
        
    
    
    Card same_suit_testing(Card max, Suit trump, Card led_card,
                           Suit ledcard_suit) {
        bool right_bower_present = false;
        bool left_bower_present = false;
        int count2 = 0;
        while (simple_hand[count2].get_suit() != ledcard_suit
               && !simple_hand[count2].is_left_bower(trump)) {
            count2++;
        }
        max = simple_hand[count2];
        for (int i = 0; i < simple_hand.size(); i++) {
            if (ledcard_suit == trump) {
                if (simple_hand[i].is_right_bower(trump)) {
                    max = simple_hand[i];
                    right_bower_present = true;
                }
                if (simple_hand[i].is_left_bower(trump)
                                  && right_bower_present == false) {
                    max = simple_hand[i];
                    left_bower_present = true;
                }
                if (simple_hand[i].get_suit() == ledcard_suit
                && simple_hand[i] > max && left_bower_present == false
                    && right_bower_present == false) {
                    max = simple_hand[i];
                }
                
            } else if (led_card.is_left_bower(trump)
                     && simple_hand[i].get_suit() == trump) {
                max = simple_hand[i];
            } else if (simple_hand[i].get_suit() == ledcard_suit
                && simple_hand[i] > max
                && !simple_hand[i].is_left_bower(trump)) {
                    max = simple_hand[i];
            }
        }
        return max;
    }
    
    private:
        std::vector <Card> simple_hand;
        std::string simple_name;
};
    //HUMAN PLAYER
class HumanPlayer : public Player {
public:
    // default constructor
    HumanPlayer(std::string name) : human_name(name) {}
    //EFFECTS returns player's name
    const std::string & get_name() const{
        return human_name;
    }
    void add_card(const Card &c){
        if (human_hand.size() <= MAX_HAND_SIZE) {
            human_hand.push_back(c);
        }
        std::sort(human_hand.begin(), human_hand.end());
    }
   
    
    void add_and_discard(const Card &upcard) {
        for (size_t i=0; i < human_hand.size(); ++i) {
            std::cout << "Human player " << human_name << "'s hand: "
                 << "[" << i << "] " << human_hand[i] << "\n";
        }
        std::cout << "Discard upcard: [-1]" << std::endl;
        
        
        std::cout << "Human player " << human_name
        << ", please select a card to discard:" << std::endl << std::endl;

        int index;
        std::cin >> index;
        
        if (index != -1) {
            human_hand.erase(human_hand.begin() + index);
            add_card(upcard);
        }
    }
    
    // need to make specific to human
    //EFFECTS If Player wishes to order
    //up a trump suit then return true and
    //change order_up_suit to desired suit.
    //If Player wishes to pass, then do
    //not modify order_up_suit and return false.
    bool make_trump(const Card &upcard, bool is_dealer,
                            int round, Suit &order_up_suit) const{
        for (size_t i=0; i < human_hand.size(); ++i) {
            std::cout << "Human player " << human_name << "'s hand: "
                 << "[" << i << "] " << human_hand[i] << "\n";
        }
        std::cout << "Human player " << human_name
                  << ", please enter a suit, or \"pass\":\n";
        
        std::string decision;
        std::cin >> decision;
        
        if (decision != "pass") {
            order_up_suit = string_to_suit(decision);
            return true;
        }
        else {
            return false;
        }
    }
    
    
    
    Card lead_card(Suit trump) {
        for (size_t i=0; i < human_hand.size(); ++i) {
            std::cout << "Human player " << human_name << "'s hand: "
            << "[" << i << "] " << human_hand[i] << "\n";
        }
        std::cout << "Human player " << human_name
                  << ", please select a card:\n";

        int index;
        std::cin >> index;
        Card decision = human_hand[index];
        human_hand.erase (human_hand.begin() + index);
        return decision;
    }

    Card play_card(const Card &led_card, Suit trump){
        for (size_t i=0; i < human_hand.size(); ++i) {
            std::cout << "Human player " << human_name << "'s hand: "
            << "[" << i << "] " << human_hand[i] << "\n";
        }
        std::cout << "Human player " << human_name
                  << ", please select a card:\n";
        
        int index;
        std::cin >> index;
        Card decision = human_hand[index];
        human_hand.erase (human_hand.begin() + index);
        return decision;
    }
    
    private:
    std::vector <Card> human_hand;
    std::string human_name;
};

Player * Player_factory(const std::string &name,
                        const std::string &strategy){
    if(strategy == "Simple"){
        return new SimplePlayer(name);
    }
    if(strategy == "Human"){
        return new HumanPlayer(name);
    }
    assert(false);
    return nullptr;
}
//EFFECTS: Prints player's name to os
    ostream & operator<<(ostream &os,
                          const Player &p){
    os << p.get_name();
    return os;
}
