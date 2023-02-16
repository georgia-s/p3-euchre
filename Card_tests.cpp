// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <iostream>

using namespace std;

TEST(test_card_ctor) {
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());
}

//TEST suit_next 
TEST(test_suit_next) {
    Suit suit = Suit_next(HEARTS);
    ASSERT_EQUAL(suit, DIAMONDS);
}
TEST(test_suit_next2) {
    Suit suit = Suit_next(SPADES);
    ASSERT_EQUAL(suit, CLUBS);
}
TEST(test_suit_next3) {
    Suit suit = Suit_next(DIAMONDS);
    ASSERT_EQUAL(suit, HEARTS);
}
//TEST card initialization 
TEST(test_card_initilized_default) {
    Card card;
    ASSERT_EQUAL(card.get_rank(), TWO);
    ASSERT_EQUAL(card.get_suit(), SPADES);
}

TEST(test_card_initilized_specific_one) {
    Card card = {JACK, HEARTS};
    ASSERT_EQUAL(card.get_rank(), JACK);
    ASSERT_EQUAL(card.get_suit(), HEARTS);
    Suit trump = DIAMONDS;
    ASSERT_EQUAL(card.get_suit(trump), DIAMONDS);
}

TEST(test_card_initilized_specific_two) {
    Card card = {FIVE, HEARTS};
    ASSERT_EQUAL(card.get_rank(), FIVE);
    ASSERT_EQUAL(card.get_suit(), HEARTS);
    Suit trump = DIAMONDS;
    ASSERT_EQUAL(card.get_suit(trump), HEARTS);
}
//TEST card_type
TEST(test_card_type_one) {
    Card three_spades = Card(FIVE, SPADES);
    ASSERT_FALSE(three_spades.is_face_or_ace());
    ASSERT_FALSE(three_spades.is_right_bower(CLUBS));
    ASSERT_FALSE(three_spades.is_left_bower(CLUBS));
    ASSERT_FALSE(three_spades.is_trump(CLUBS));
}

TEST(test_card_type_two) {
    Card Jack_spades = Card(JACK, SPADES);
    ASSERT_TRUE(Jack_spades.is_face_or_ace());
    ASSERT_TRUE(Jack_spades.is_right_bower(SPADES));
    ASSERT_TRUE(Jack_spades.is_left_bower(CLUBS));
    ASSERT_TRUE(Jack_spades.is_trump(SPADES));
}
//TEST card comparisons 

TEST(test_card_comparisons_one) {
    Card three_spades = Card(THREE, SPADES);
    Card king_spades = Card(KING, SPADES);
    ASSERT_FALSE(king_spades < three_spades);
    ASSERT_FALSE(three_spades > king_spades);
    ASSERT_FALSE(king_spades == three_spades);
    ASSERT_TRUE(king_spades != three_spades);
    ASSERT_TRUE(three_spades <= king_spades);
    ASSERT_TRUE(king_spades >= three_spades);
}

TEST(test_card_comparisons_two) {
    Card three_spades = Card(THREE, SPADES);
    ASSERT_FALSE(three_spades < three_spades);
    ASSERT_FALSE(three_spades > three_spades);
    ASSERT_TRUE(three_spades == three_spades);
    ASSERT_FALSE(three_spades != three_spades);
    ASSERT_TRUE(three_spades <= three_spades);
    ASSERT_TRUE(three_spades >= three_spades);
}

TEST(test_card_comparisons_three) {
    Card five_hearts = Card(FIVE, HEARTS);
    Card five_spades = Card(FIVE, SPADES);
    ASSERT_FALSE(five_hearts < five_spades);
    ASSERT_FALSE(five_spades > five_hearts);
    ASSERT_FALSE(five_hearts == five_spades);
    ASSERT_TRUE(five_spades != five_hearts);

}
//TEST getting_card
TEST(test_getting_card) {
    std::string three_of_spades = "Three of Spades";
    Card three_spades = Card(THREE, SPADES);
    ostringstream oss;
    oss << three_spades;
    ASSERT_EQUAL(oss.str(), three_of_spades);
}
//TEST string to suit
//String to suit Normal
TEST(test_string_to_suit_one) {
    std::string string = "Hearts";
    Suit suit = string_to_suit(string);
    ASSERT_EQUAL(suit, HEARTS);
}
//String to suit EDGE
TEST(test_string_to_suit_two) {
    std::string string = "Spades";
    Suit suit = string_to_suit(string);
    ASSERT_EQUAL(suit, SPADES);
}

//String to suit EDGE
TEST(test_string_to_suit_three) {
    std::string string = "Diamonds";
    Suit suit = string_to_suit(string);
    ASSERT_EQUAL(suit, DIAMONDS);
}
//TEST string to rank
//String to rank NORMAL
TEST(test_string_to_rank_one) {
    std::string string = "Five";
    Rank rank = string_to_rank(string);
    ASSERT_EQUAL(rank, FIVE);
}

//String to rank EDGE
TEST(test_string_to_rank_two) {
    std::string string = "Two";
    Rank rank = string_to_rank(string);
    ASSERT_EQUAL(rank, TWO);
}
//String to rank EDGE
TEST(test_string_to_rank_three) {
    std::string string = "Ace";
    Rank rank = string_to_rank(string);
    ASSERT_EQUAL(rank, ACE);
}
TEST_MAIN()
