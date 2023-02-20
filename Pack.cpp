/// Project UID 1d9f47bfc76643019cfbf037641defe1
//  Pack.cpp
//  p3-euchre
//
//  Created by Anastasia Kazanas on 2/12/23.
//
#include "Pack.h"
#include "Card.h"
#include <array>
#include <string>

using namespace std;
// EFFECTS: Initializes the Pack to be in the following standard order:
//          the cards of the lowest suit arranged from lowest rank to
//          highest rank, followed by the cards of the next lowest suit
//          in order from lowest to highest rank, and so on.
// NOTE: The standard order is the same as that in pack.in.
// NOTE: Do NOT use pack.in in your implementation of this function

Pack::Pack() {
    cards.at(0) = Card(NINE, SPADES);
    cards.at(1) = Card(TEN, SPADES);
    cards.at(2) = Card(JACK, SPADES);
    cards.at(3) = Card(QUEEN, SPADES);
    cards.at(4) = Card(KING, SPADES);
    cards.at(5) = Card(ACE, SPADES);
    cards.at(6) = Card(NINE, HEARTS);
    cards.at(7) = Card(TEN, HEARTS);
    cards.at(8) = Card(JACK, HEARTS);
    cards.at(9) = Card(QUEEN, HEARTS);
    cards.at(10) = Card(KING, HEARTS);
    cards.at(11) = Card(ACE, HEARTS);
    cards.at(12) = Card(NINE, CLUBS);
    cards.at(13) = Card(TEN, CLUBS);
    cards.at(14) = Card(JACK, CLUBS);
    cards.at(15) = Card(QUEEN, CLUBS);
    cards.at(16) = Card(KING, CLUBS);
    cards.at(17) = Card(ACE, CLUBS);
    cards.at(18) = Card(NINE, DIAMONDS);
    cards.at(19) = Card(TEN, DIAMONDS);
    cards.at(20) = Card(JACK, DIAMONDS);
    cards.at(21) = Card(QUEEN, DIAMONDS);
    cards.at(22) = Card(KING, DIAMONDS);
    cards.at(23) = Card(ACE, DIAMONDS);
    next = 0;
}

// REQUIRES: pack_input contains a representation of a
//Pack in the format required by the project specification
// MODIFIES: pack_input
// EFFECTS: Initializes Pack by reading from pack_input.
Pack::Pack(std::istream& pack_input) {
    for (int i = 0; i < PACK_SIZE; i++) {
        std::string discard;
        Rank rank;
        Suit suit;
        pack_input >> rank >> discard >> suit;
        cards.at(i) = Card(rank, suit);
    }
    next = 0;
}
   

// REQUIRES: cards remain in the Pack
// EFFECTS: Returns the next card in the pack and increments the next index
Card Pack::deal_one() {
    int i = next;
    ++next;
    return cards.at(i);
}

// EFFECTS: Resets next index to first card in the Pack
void Pack::reset() {
    next = 0;
}

// EFFECTS: Shuffles the Pack and resets the next index. This
//          performs an in shuffle seven times. See
//          https://en.wikipedia.org/wiki/In_shuffle.
void Pack::shuffle() {
    int shuffleTimes = 7;
    int halfDeck = PACK_SIZE / 2;
    std::array<Card, PACK_SIZE> cards2;
    for (int i = 0; i < shuffleTimes; ++i) {
        for (int shuffleOne = 0; shuffleOne < halfDeck; ++shuffleOne) {
            cards2[shuffleOne] = cards[shuffleOne];
        }
        for (int shuffleTwo = halfDeck; shuffleTwo < PACK_SIZE; ++shuffleTwo) {
            cards2[shuffleTwo] = cards[shuffleTwo];
        }
        for (int i = 0; i < halfDeck; ++i) {
            cards[(2 * i) + 1] = cards2[i];
        }
        for (int j = halfDeck; j < PACK_SIZE; ++j) {
            cards[(2 * (j - halfDeck))] = cards2[j];
        }
    }
}

// EFFECTS: returns true if there are no more cards left in the pack
bool Pack::empty() const {
    if (next == PACK_SIZE) {
        return true;
    }
    return false;
}

