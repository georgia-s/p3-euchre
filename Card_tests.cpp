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

TEST(test_card_insertion) {
    Card three_spades = Card(THREE, SPADES);
    ostringstream oss;
    oss << three_spades;
    ASSERT_EQUAL(oss.str(), "Three of Spades");
}

TEST(test_card_insertion_as_a_string) {
    string six_hearts = "Six of Hearts";
    ostringstream oss;
    oss << six_hearts;
    ASSERT_EQUAL(oss.str(), "Six of Hearts");
}

TEST(test_card_extract) {
    istringstream iss("Three of Spades");
    Card c;
    iss >> c;
    ASSERT_EQUAL(c, Card(THREE, SPADES));
}

TEST(test_card_get_suit_and_rank) {
    Card six_diamonds = Card(SIX, DIAMONDS);
    ASSERT_EQUAL(six_diamonds.get_rank(), SIX);
    ASSERT_EQUAL(six_diamonds.get_suit(), DIAMONDS);

    Card three_spades = Card(THREE, SPADES);
    ASSERT_EQUAL(three_spades.get_rank(), THREE);
    ASSERT_EQUAL(three_spades.get_suit(), SPADES);
    ASSERT_EQUAL(three_spades.get_suit(CLUBS), SPADES);
    
    Card jack_diamonds = Card(JACK, DIAMONDS);
    ASSERT_EQUAL(jack_diamonds.get_rank(), JACK);
    ASSERT_EQUAL(jack_diamonds.get_suit(), DIAMONDS);
    ASSERT_EQUAL(jack_diamonds.get_suit(HEARTS), HEARTS);
    
    Card jack_hearts = Card(JACK, HEARTS);
    ASSERT_EQUAL(jack_hearts.get_rank(), JACK);
    ASSERT_EQUAL(jack_hearts.get_suit(), HEARTS);
    ASSERT_EQUAL(jack_hearts.get_suit(DIAMONDS), DIAMONDS);
    
    Card jack_spades = Card(JACK, SPADES);
    ASSERT_EQUAL(jack_spades.get_rank(), JACK);
    ASSERT_EQUAL(jack_spades.get_suit(), SPADES);
    ASSERT_EQUAL(jack_spades.get_suit(CLUBS), CLUBS);
    
    Card jack_clubs = Card(JACK, CLUBS);
    ASSERT_EQUAL(jack_clubs.get_rank(), JACK);
    ASSERT_EQUAL(jack_clubs.get_suit(), CLUBS);
    ASSERT_EQUAL(jack_clubs.get_suit(SPADES), SPADES);
}

TEST (test_is_face_or_ace) {
    Card jack_diamonds = Card(JACK, DIAMONDS);
    ASSERT_TRUE(jack_diamonds.is_face_or_ace());
    
    Card ace_hearts = Card(ACE, HEARTS);
    ASSERT_TRUE(ace_hearts.is_face_or_ace());
    
    Card two_clubs = Card(TWO, CLUBS);
    ASSERT_FALSE(two_clubs.is_face_or_ace());
}

TEST (test_is_right_or_left_bower) {
    Card jack_diamonds = Card(JACK, DIAMONDS);
    ASSERT_TRUE(jack_diamonds.is_right_bower(DIAMONDS));
    ASSERT_FALSE(jack_diamonds.is_left_bower(DIAMONDS));
    ASSERT_TRUE(jack_diamonds.is_trump(DIAMONDS));
    ASSERT_TRUE(jack_diamonds.is_trump(HEARTS));
    ASSERT_FALSE(jack_diamonds.is_trump(SPADES));
    
    
    Card jack_hearts = Card(JACK, HEARTS);
    ASSERT_FALSE(jack_hearts.is_right_bower(DIAMONDS));
    ASSERT_TRUE(jack_hearts.is_left_bower(DIAMONDS));
    ASSERT_TRUE(jack_hearts.is_trump(HEARTS));
    ASSERT_TRUE(jack_hearts.is_trump(DIAMONDS));
    ASSERT_FALSE(jack_hearts.is_trump(SPADES));
    
    Card jack_spades = Card(JACK, SPADES);
    ASSERT_TRUE(jack_spades.is_left_bower(CLUBS));
    ASSERT_TRUE(jack_spades.is_trump(SPADES));
    ASSERT_TRUE(jack_spades.is_trump(CLUBS));
    ASSERT_FALSE(jack_spades.is_trump(HEARTS));
    
    Card jack_clubs = Card(JACK, CLUBS);
    ASSERT_TRUE(jack_clubs.is_left_bower(SPADES));
    ASSERT_TRUE(jack_clubs.is_trump(SPADES));
    ASSERT_TRUE(jack_clubs.is_trump(CLUBS));
    ASSERT_FALSE(jack_clubs.is_trump(HEARTS));
}

TEST(test_card_comparisons_four) {
    Card five_hearts = Card(FIVE, HEARTS);
    Card jack_diamonds = Card(JACK, DIAMONDS);
    ASSERT_FALSE(jack_diamonds < five_hearts);
    ASSERT_FALSE(five_hearts > jack_diamonds);
    ASSERT_FALSE(jack_diamonds <= five_hearts);
    ASSERT_FALSE(five_hearts >= jack_diamonds);
    ASSERT_FALSE(jack_diamonds == five_hearts);
    ASSERT_TRUE(five_hearts != jack_diamonds);
    ASSERT_TRUE(five_hearts < jack_diamonds);
    ASSERT_TRUE(jack_diamonds > five_hearts);
    ASSERT_TRUE(five_hearts <= jack_diamonds);
    ASSERT_TRUE(jack_diamonds >= five_hearts);
}

TEST(test_card_less_one) {
    Card three_diamonds = Card(THREE, DIAMONDS);
    ASSERT_FALSE(Card_less(three_diamonds, three_diamonds, HEARTS));
    ASSERT_FALSE(Card_less(three_diamonds, three_diamonds, three_diamonds, DIAMONDS));
}

TEST(test_card_less_two) {
    Card three_clubs = Card(THREE, CLUBS);
    Card jack_clubs = Card(JACK, CLUBS);
    Card ace_clubs = Card(ACE, CLUBS);
    Card king_clubs = Card(KING, CLUBS);
    ASSERT_TRUE(Card_less(three_clubs, jack_clubs, CLUBS));
    ASSERT_TRUE(Card_less(jack_clubs, king_clubs, three_clubs, CLUBS));
    ASSERT_FALSE(Card_less(king_clubs, jack_clubs, three_clubs, CLUBS));
}

TEST(test_Card_less_three) {
    Card queen_spades = Card(QUEEN, SPADES);
    Card jack_hearts = Card(JACK, HEARTS);
    Card ace_diamonds = Card(ACE, DIAMONDS);
    Card king_clubs = Card(KING, CLUBS);
    ASSERT_FALSE(Card_less(king_clubs, jack_hearts, CLUBS));
    ASSERT_TRUE(Card_less(king_clubs, jack_hearts, ace_diamonds,HEARTS));
}

TEST(test_card_extract) {
    istringstream iss("Three of Spades");
    Card c;
    iss >> c;
    ASSERT_EQUAL(c, Card(THREE, SPADES));
}TEST(test_card_insertion) {
    Card three_spades = Card(THREE, SPADES);
    ostringstream oss;
    oss << three_spades;
    ASSERT_EQUAL(oss.str(), "Three of Spades");
}

TEST(test_card_insertion_as_a_string) {
    string six_hearts = "Six of Hearts";
    ostringstream oss;
    oss << six_hearts;
    ASSERT_EQUAL(oss.str(), "Six of Hearts");
}

TEST(test_card_get_suit_and_rank) {
    Card six_diamonds = Card(SIX, DIAMONDS);
    ASSERT_EQUAL(six_diamonds.get_rank(), SIX);
    ASSERT_EQUAL(six_diamonds.get_suit(), DIAMONDS);

    Card three_spades = Card(THREE, SPADES);
    ASSERT_EQUAL(three_spades.get_rank(), THREE);
    ASSERT_EQUAL(three_spades.get_suit(), SPADES);
    ASSERT_EQUAL(three_spades.get_suit(CLUBS), SPADES);
    
    Card jack_diamonds = Card(JACK, DIAMONDS);
    ASSERT_EQUAL(jack_diamonds.get_rank(), JACK);
    ASSERT_EQUAL(jack_diamonds.get_suit(), DIAMONDS);
    ASSERT_EQUAL(jack_diamonds.get_suit(HEARTS), HEARTS);
    
    Card jack_hearts = Card(JACK, HEARTS);
    ASSERT_EQUAL(jack_hearts.get_rank(), JACK);
    ASSERT_EQUAL(jack_hearts.get_suit(), HEARTS);
    ASSERT_EQUAL(jack_hearts.get_suit(DIAMONDS), DIAMONDS);
    
    Card jack_spades = Card(JACK, SPADES);
    ASSERT_EQUAL(jack_spades.get_rank(), JACK);
    ASSERT_EQUAL(jack_spades.get_suit(), SPADES);
    ASSERT_EQUAL(jack_spades.get_suit(CLUBS), CLUBS);
    
    Card jack_clubs = Card(JACK, CLUBS);
    ASSERT_EQUAL(jack_clubs.get_rank(), JACK);
    ASSERT_EQUAL(jack_clubs.get_suit(), CLUBS);
    ASSERT_EQUAL(jack_clubs.get_suit(SPADES), SPADES);
}

TEST (test_is_face_or_ace) {
    Card jack_diamonds = Card(JACK, DIAMONDS);
    ASSERT_TRUE(jack_diamonds.is_face_or_ace());
    
    Card ace_hearts = Card(ACE, HEARTS);
    ASSERT_TRUE(ace_hearts.is_face_or_ace());
    
    Card two_clubs = Card(TWO, CLUBS);
    ASSERT_FALSE(two_clubs.is_face_or_ace());
}

TEST (test_is_right_or_left_bower) {
    Card jack_diamonds = Card(JACK, DIAMONDS);
    ASSERT_TRUE(jack_diamonds.is_right_bower(DIAMONDS));
    ASSERT_FALSE(jack_diamonds.is_left_bower(DIAMONDS));
    
    Card jack_hearts = Card(JACK, HEARTS);
    ASSERT_FALSE(jack_hearts.is_right_bower(DIAMONDS));
    ASSERT_TRUE(jack_hearts.is_left_bower(DIAMONDS));
    
    Card jack_spades = Card(JACK, SPADES);
    ASSERT_TRUE(jack_spades.is_left_bower(CLUBS));
    
    Card jack_clubs = Card(JACK, CLUBS);
    ASSERT_TRUE(jack_clubs.is_left_bower(SPADES));
}
TEST_MAIN()
