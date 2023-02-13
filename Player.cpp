// Project UID 1d9f47bfc76643019cfbf037641defe1
//  Player.cpp
//  p3-euchre
#include <stdio.h>
#include "Player.h"
#include <algorithm>
#include <cassert>


//EFFECTS returns player's name
virtual const std::string & get_name() const = 0;

//REQUIRES player has less than MAX_HAND_SIZE cards
//EFFECTS  adds Card c to Player's hand
virtual void add_card(const Card& c) {
    if (hand.size() < MAX_HAND_SIZE) {
        hand.push_back(c);
    }
    std::sort(hand.begin(), hand.end());
}

//REQUIRES round is 1 or 2
//MODIFIES order_up_suit
//EFFECTS If Player wishes to order up a trump suit then return true and
//  change order_up_suit to desired suit.  If Player wishes to pass, then do
//  not modify order_up_suit and return false.
virtual bool make_trump(const Card& upcard, bool is_dealer,int round, std::string& order_up_suit) const {
    int trumps = 0;
    int size = static_cast <int>(hand.size());
    if (round == 1) {
        for (int i = 0; i < size; ++i) {
            if (hand[i].is_face() && hand[i].is_trump(upcard.get_suit())) {
                ++trumps;
            }
        }
        if (trumps >= 2) {
            order_up_suit = upcard.get_suit();
            return true;
        }
    }
    if (round == 2) {
        std::string nextSuit = Suit_next(upcard.get_suit());
        for (int i = 0; i < size; ++i) {
            if (hand[i].is_face() && hand[i].is_trump(nextSuit)) {
                ++trumps;
            }
        }
        if (trumps >= 1) {
            order_up_suit = nextSuit;
            return true;
        }
        if (is_dealer) {
            order_up_suit = nextSuit;
        }
    }
}
return false;
}

//REQUIRES Player has at least one card
//EFFECTS  Player adds one card to hand and removes one card from hand.
virtual void add_and_discard(const Card &upcard) = 0;

//REQUIRES Player has at least one card
//EFFECTS  Leads one Card from Player's hand according to their strategy
//  "Lead" means to play the first Card in a trick.  The card
//  is removed the player's hand.
virtual Card lead_card(Suit trump) = 0;

//REQUIRES Player has at least one card
//EFFECTS  Plays one Card from Player's hand according to their strategy.
//  The card is removed from the player's hand.
virtual Card play_card(const Card &led_card, Suit trump) = 0;

//EFFECTS: Returns a pointer to a player with the given name and strategy
//To create an object that won't go out of scope when the function returns,
//use "return new Simple(name)" or "return new Human(name)"
//Don't forget to call "delete" on each Player* after the game is over
Player * Player_factory(const std::string &name, const std::string &strategy);

//EFFECTS: Prints player's name to os
std::ostream & operator<<(std::ostream &os, const Player &p);