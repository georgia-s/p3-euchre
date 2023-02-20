// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
        Player * alice = Player_factory("Alice", "Simple");
        ASSERT_EQUAL("Alice", alice->get_name());
        delete alice;
    }

//TEST SIMPLE PLAYER PLAY CARD FAILING
TEST(test_simple_player_play_card) {
      // Bob's hand
      Player * bob = Player_factory("Bob", "Simple");
      bob->add_card(Card(NINE, SPADES));
      bob->add_card(Card(TEN, DIAMONDS));
      bob->add_card(Card(QUEEN, HEARTS));
      bob->add_card(Card(KING, HEARTS));
      bob->add_card(Card(ACE, CLUBS));

      // Bob plays a card
      Card nine_diamonds(NINE, DIAMONDS);
      Card card_played = bob->play_card(
        nine_diamonds,  // Nine of Diamonds is led
        HEARTS    // Trump suit
      );

      // Verify the card Bob played
      ASSERT_EQUAL(card_played, Card(NINE, SPADES));
      delete bob;
    }

//MAKE TRUMP TEST CASES
// round 1, not dealer, has two face cards 
TEST(test_simple_player_make_trump_one) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(FOUR, DIAMONDS));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(KING, HEARTS));
  bob->add_card(Card(ACE, HEARTS));

  // Bob makes trump
  Card king_hearts(KING, HEARTS);
    Suit trump = HEARTS;
  bool orderup = bob->make_trump(
    king_hearts,    // Upcard
    false,           // Bob is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, HEARTS);

  delete bob;
}

// round 1 dont take trump PASSED 
TEST(test_simple_player_make_trump_two) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(FOUR, DIAMONDS));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(KING, HEARTS));
  bob->add_card(Card(FIVE, HEARTS));

  // Bob makes trump
  Card king_hearts(KING, HEARTS);
    Suit trump = HEARTS;
  bool orderup = bob->make_trump(
    king_hearts,    // Upcard
    true,           // Bob is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_FALSE(orderup);
  ASSERT_EQUAL(trump, HEARTS);

  delete bob;
}


    // round 1,dealer PASSED 
TEST(test_simple_player_make_trump_three) {
    // Bob's hand
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(FOUR, DIAMONDS));
    bob->add_card(Card(TEN, SPADES));
    bob->add_card(Card(KING, SPADES));
    bob->add_card(Card(KING, HEARTS));
    bob->add_card(Card(THREE, SPADES));

      // Bob makes trump
    Card king_diamonds(KING, DIAMONDS);
    Suit trump = DIAMONDS;
    bool orderup = bob->make_trump(
    king_diamonds,    // Upcard
    true,           // Bob is also the dealer
    1,              // second round
    trump           // Suit ordered up (if any)
    );

    // Verify Bob's order up and trump suit
    ASSERT_FALSE(orderup);
    delete bob;
}

// round 2, screw the dealer 
TEST(test_simple_player_make_trump_four) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Simple");
  bob->add_card(Card(FOUR, DIAMONDS));
  bob->add_card(Card(QUEEN, HEARTS));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(TEN, HEARTS));
  bob->add_card(Card(THREE, SPADES));

  // Bob makes trump
  Card king_diamonds(KING, DIAMONDS);
  
    Suit trump = HEARTS;
  bool orderup = bob->make_trump(
    king_diamonds,     // Upcard
    true,           // Bob is also the dealer
    2,              // second round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, HEARTS);

  delete bob;
}

// round 2 dont take trump two PASSED 
TEST(test_simple_player_make_trump_five) {
    // Bob's hand
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(FOUR, DIAMONDS));
    bob->add_card(Card(QUEEN, DIAMONDS));
    bob->add_card(Card(KING, SPADES));
    bob->add_card(Card(TEN, HEARTS));
    bob->add_card(Card(THREE, SPADES));
    
    // Bob makes trump
    Card king_diamonds(KING, DIAMONDS);
    Suit trump = DIAMONDS;
    bool orderup = bob->make_trump(
    king_diamonds,    // Upcard
    true,           // Bob is also the dealer
    1,              // FIRST round
    trump           // Suit ordered up (if any)
    );

  // Verify Bob's order up and trump suit
  ASSERT_FALSE(orderup);
  ASSERT_EQUAL(trump, DIAMONDS);

  delete bob;
}

// round 2, not a dealer 
TEST(test_simple_player_make_trump_six) {
    // Bob's hand
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(FOUR, DIAMONDS));
    bob->add_card(Card(QUEEN, DIAMONDS));
    bob->add_card(Card(KING, SPADES));
    bob->add_card(Card(TEN, HEARTS));
    bob->add_card(Card(THREE, SPADES));
    
    // Bob makes trump
    Card king_clubs(KING, CLUBS);
    Suit trump = CLUBS;
    bool orderup = bob->make_trump(
    king_clubs,    // Upcard
    false,           // Bob is also the dealer
    2,              // round 2
    trump           // Suit ordered up (if any)
    );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, SPADES)  ;

  delete bob;
}
//ROUND 2, no same color in hand
TEST(test_simple_player_make_trump_seven) {
    // Bob's hand
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(FOUR, DIAMONDS));
    bob->add_card(Card(QUEEN, DIAMONDS));
    bob->add_card(Card(KING, DIAMONDS));
    bob->add_card(Card(TEN, HEARTS));
    bob->add_card(Card(THREE, SPADES));
    
    // Bob makes trump
    Card king_clubs(KING, CLUBS);
    Suit trump = CLUBS;
    bool orderup = bob->make_trump(
    king_clubs,    // Upcard
    true,           // Bob is also the dealer
    2,              // round 2
    trump           // Suit ordered up (if any)
    );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup);

  delete bob;
}

TEST(test_simple_player_lead_card) {
    // Bob's hand
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(NINE, SPADES));
    bob->add_card(Card(TEN, SPADES));
    bob->add_card(Card(QUEEN, SPADES));
    bob->add_card(Card(KING, SPADES));
    bob->add_card(Card(ACE, SPADES));

    // Bob adds a card to his hand and discards one card
    bob->add_and_discard(Card(NINE, HEARTS));

    // Bob leads
    Card card_led = bob->lead_card(HEARTS);

    // Verify the card Bob selected to lead
    Card ace_spades(ACE, SPADES);
    ASSERT_EQUAL(card_led, ace_spades); //check led card

    delete bob;
}

TEST_MAIN()

