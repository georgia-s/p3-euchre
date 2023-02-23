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
#include <vector>
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
        for (size_t i=0; i < simple_hand.size(); ++i) {
            std::cout << "Simple player " << simple_name << "'s hand: "
            << "[" << i << "] " << simple_hand[i] << "\n";
        }
        
        Suit trump_suit = upcard.get_suit();
        Suit other_color = Suit_next(trump_suit);
        int ace_or_face_same_as_trump_count = 0;
        int ace_or_face_same_as_other_color = 0;
    
        if (round == 1) {
            for (size_t i=0; i < simple_hand.size(); ++i) {
                if (simple_hand[i].get_suit() == trump_suit
                && simple_hand[i].is_face_or_ace()) {
                    ace_or_face_same_as_trump_count++;
                }
                if (simple_hand[i].is_left_bower(trump_suit)) {
                    ace_or_face_same_as_trump_count++;
                }
            }
                    
            if (ace_or_face_same_as_trump_count >= 2) {
                order_up_suit = trump_suit;
                std::cout << simple_name << " orders up "
                << order_up_suit << std::endl << std::endl;
                return true;
            }
            else {
                std::cout << simple_name << " passes" << std::endl;
                return false;
            }
        }

        if (round == 2) {
            if (is_dealer == true) {
                order_up_suit = other_color;
                std::cout << simple_name << " orders up "
                << order_up_suit << std::endl << std::endl;
                return true;
            }
            for (size_t i=0; i < simple_hand.size(); ++i) {
                if (simple_hand[i].get_suit() == trump_suit
                     && simple_hand[i].is_face_or_ace()) {
                    ace_or_face_same_as_trump_count++;
                }
                if (simple_hand[i].get_suit() == other_color
                     && simple_hand[i].is_left_bower(trump_suit)) {
                    ace_or_face_same_as_trump_count++;
                }
                if (simple_hand[i].get_suit() == other_color
                    && simple_hand[i].is_face_or_ace() && !simple_hand[i].is_left_bower(trump_suit)) {
                    ace_or_face_same_as_other_color++;
                }
            }
            if (ace_or_face_same_as_trump_count >= 1) {
                order_up_suit = trump_suit;
                std::cout << simple_name << " orders up "
                << order_up_suit << std::endl << std::endl;
                return true;
            } else if (ace_or_face_same_as_other_color >= 1) {
                order_up_suit = other_color;
                std::cout << simple_name << " orders up "
                << order_up_suit << std::endl << std::endl;
                return true;
            }
            else {
                std::cout << simple_name << " passes" << std::endl;
                return false;
            }
            
        }
       std::cout << simple_name << " passes" << std::endl;
       return false;
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
        add_card(upcard);
    }
    
    
    //REQUIRES Player has at least one card
    //EFFECTS  Leads one Card from Player's hand
    //according to their strategy
    //"Lead" means to play the first Card in a trick.
    //The card is removed the player's hand.
     Card lead_card(Suit trump) {
        Card max = simple_hand[0];
        int start = 0;

         // sees how many trump cards there are before reaching
         // a non trump card
        while ((simple_hand[start].get_suit() == trump || simple_hand[start].is_left_bower(trump)) && start != simple_hand.size()) {
            start++;
        }
        
         // if there is a mix of trump and non trump cards
         // sets max equal to first non trump card
        if (start != 0 && start != simple_hand.size()) {
            max = simple_hand[start];
        }
        
        bool right_bower_present = false;
        bool left_bower_present = false;
        
        Card right_bower;
        Card left_bower;
        
         //finds out of there is a left and/or right bower present
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
        
        //counts total trump cards
        int trump_count = 0;
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
                if ((simple_hand[i] > max) && (!simple_hand[i].is_left_bower(trump))
                    && (simple_hand[i].get_suit() != trump)) {
                    max = simple_hand[i];
                }
            }
        }
        // if all trump cards, play highest trump
         // right bower is highest, then left 
        if (trump_count >= simple_hand.size()) {
            for (int i = 0; i < simple_hand.size(); i++) {
                if (right_bower_present == true) {
                    max = right_bower;
                }
                if (left_bower_present == true && right_bower_present == false) {
                    max = left_bower;
                }
                if(((start == simple_hand.size()))
                   && (simple_hand[i] > max) && (right_bower_present == false)
                   && (left_bower_present == false)) {
                    max = simple_hand[i];
                }
                
            }
        }
        std::cout << max << " led by " << simple_name << std::endl;
        return max;
    }
    
    //REQUIRES Player has at least one card
    //EFFECTS Plays one Card from Player's hand
    //according to their strategy.
    //The card is removed from the player's hand.
    Card play_card(const Card &led_card, Suit trump){
        Card max = simple_hand[0];
        int count = 0;
        // makes sure that left bower isn't set to lowest
        while(simple_hand[count].is_left_bower(led_card.get_suit())) {
            count++;
        }
        Card min = simple_hand[count];

        bool same_suit = false;
        for (int i = 0; i < simple_hand.size(); i++) {
            if (simple_hand[i].get_suit() == led_card.get_suit()) {
                same_suit = true;
            }
            if (simple_hand[i].is_left_bower(led_card.get_suit())) {
                same_suit = true;
            }
        }

        bool right_bower_present = false;
        bool left_bower_present = false;
        
        // can follow suit, so plays highest
        if (same_suit == true){
            for (int i = 0; i < simple_hand.size(); i++) {
                if(simple_hand[i].is_right_bower(led_card.get_suit())) {
                    max = simple_hand[i];
                    right_bower_present = true;
                }
                if(simple_hand[i].is_left_bower(led_card.get_suit())
                   && right_bower_present == false) {
                    max = simple_hand[i];
                    left_bower_present = true;
                }
                
                if (simple_hand[i].get_suit() == led_card.get_suit()
                    && simple_hand[i] > max && right_bower_present == false
                    && left_bower_present == false) {
                    max = simple_hand[i];
                }
            }
            std::cout << max << " played by " << simple_name << std::endl;
            return max;
        }
        // cant follow suit, so plays lowest
        else {
            for (int i = 0; i < simple_hand.size(); i++) {
                if (simple_hand[i] < min && !simple_hand[i].is_left_bower(led_card.get_suit())) {
                    min = simple_hand[i];
                }
            }
            std::cout << min << " played by " << simple_name << std::endl;
            return min;
        }
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
        if (human_hand.size() < MAX_HAND_SIZE) {
            human_hand.push_back(c);
        }
        std::sort(human_hand.begin(), human_hand.end());
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
            std::cout << human_name << " orders up "
            << order_up_suit << std::endl << std::endl;
            return true;
        }
        else {
            std::cout << human_name << " passes" << std::endl;
            return false;
        }
    }
    
    void add_and_discard(const Card &upcard) {
        Suit trump = upcard.get_suit();
        int lowest = 0;
        Card min = human_hand[0];
        human_hand.push_back(upcard);
        for(size_t i = 0; i < human_hand.size(); i++){
            if(Card_less(human_hand[i], min, trump)){
                min = human_hand[i];
                lowest = (int)i;
            }
        }
        human_hand.erase(human_hand.begin() + lowest);
        add_card(upcard);
    }
    
    
    Card lead_card(Suit trump) {
        for (size_t i=0; i < human_hand.size(); ++i) {
            std::cout << "Human player " << human_name << "'s hand: "
            << "[" << i << "] " << human_hand[i] << "\n";
        }
        std::cout << "Human player " << human_name
                  << ", please select a card:\n";
        Rank rank;
        std::string junk;
        Suit suit;
        std::cin >> rank >> junk >> suit;
        Card decision(rank, suit);
        std::cout << decision << " led by " << human_name << std::endl;
        return decision;
    }

    Card play_card(const Card &led_card, Suit trump){
        for (size_t i=0; i < human_hand.size(); ++i) {
            std::cout << "Human player " << human_name << "'s hand: "
            << "[" << i << "] " << human_hand[i] << "\n";
        }
        std::cout << "Human player " << human_name
                  << ", please select a card:\n";
        Rank rank;
        std::string junk;
        Suit suit;
        std::cin >> rank >> junk >> suit;
        Card decision(rank, suit);
        std::cout << decision << " played by " << human_name << std::endl;
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
