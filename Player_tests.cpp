// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;

TEST(test_player_get_name_simple) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());
    delete alice;
}

//TEST SIMPLE PLAYER PLAY CARD led suit
TEST(test_simple_player_play_card_one) {
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
    DIAMONDS       // Trump suit
    );

      // Verify the card Bob played
    ASSERT_EQUAL(card_played, Card(TEN, DIAMONDS));
    delete bob;
}

//TEST SIMPLE PLAYER PLAY CARD, has no led suit
TEST(test_simple_player_play_card_two) {
      // Bob's hand
      Player * bob = Player_factory("Bob", "Simple");
      bob->add_card(Card(NINE, SPADES));
      bob->add_card(Card(TEN, DIAMONDS));
      bob->add_card(Card(QUEEN, HEARTS));
      bob->add_card(Card(KING, HEARTS));
      bob->add_card(Card(ACE, DIAMONDS));

      // Bob plays a card
      Card nine_clubs(NINE, CLUBS);
      Card card_played = bob->play_card(
        nine_clubs,  // Nine of clubs is led
        CLUBS       // Trump suit
      );

      // Verify the card Bob played
      ASSERT_EQUAL(card_played, Card(NINE, SPADES));
      delete bob;
    }
//FALSE POSITIVE 
//TEST SIMPLE PLAYER PLAY CARD, all led suit with right bower
TEST(test_simple_player_play_card_three) {
      // Bob's hand
      Player * bob = Player_factory("Bob", "Simple");
      bob->add_card(Card(NINE, SPADES));
      bob->add_card(Card(TEN, DIAMONDS));
      bob->add_card(Card(JACK, DIAMONDS));
      bob->add_card(Card(KING, DIAMONDS));
      bob->add_card(Card(NINE, CLUBS));

      // Bob plays a card
      Card nine_diamonds(NINE, DIAMONDS);
      Card card_played = bob->play_card(
        nine_diamonds,  // seven of diamonds is led
        DIAMONDS       // Trump suit
      );

      // Verify the card Bob played
      ASSERT_EQUAL(card_played, Card(JACK, DIAMONDS));
      delete bob;
    }

//TEST SIMPLE PLAYER PLAY CARD, all led suit
TEST(test_simple_player_play_card_four) {
      // Bob's hand
      Player * bob = Player_factory("Bob", "Simple");
      bob->add_card(Card(NINE, DIAMONDS));
      bob->add_card(Card(TEN, DIAMONDS));
      bob->add_card(Card(QUEEN, DIAMONDS));
      bob->add_card(Card(KING, DIAMONDS));
      bob->add_card(Card(FIVE, DIAMONDS));

      // Bob plays a card
      Card seven_diamonds(SEVEN, DIAMONDS);
      Card card_played = bob->play_card(
        seven_diamonds,  // seven of diamonds is led
        DIAMONDS       // Trump suit
      );

      // Verify the card Bob played
      ASSERT_EQUAL(card_played, Card(KING, DIAMONDS));
      delete bob;
    }

//TEST SIMPLE PLAYER PLAY CARD, none of led suit, left bower
TEST(test_simple_player_play_card_five) {
      // Bob's hand
      Player * bob = Player_factory("Bob", "Simple");
      bob->add_card(Card(JACK, SPADES));
      bob->add_card(Card(QUEEN, HEARTS));
      bob->add_card(Card(QUEEN, DIAMONDS));
      bob->add_card(Card(KING, HEARTS));
      bob->add_card(Card(ACE, DIAMONDS));

      // Bob plays a card
      Card nine_clubs(NINE, CLUBS);
      Card card_played = bob->play_card(
        nine_clubs,  // seven of clubs is led
        CLUBS       // Trump suit
      );

      // Verify the card Bob played
      ASSERT_EQUAL(card_played, Card(JACK, SPADES));
      delete bob;
    }


//MAKE TRUMP TEST CASES
// round 1, not dealer, makes trump
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

// round 1, dealer, doesn't make trump
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


// round 1, dealer. makes trump
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

// round 2, screw the dealer works
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

// round 2, dealer, gets screwed
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

// round 2, not a dealer PASSED
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
//ROUND 2, no same color in hand PASSED
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

// round 1, not dealer, doesn’t make trump
TEST(test_simple_player_make_trump_eight) {
    // Bob's hand
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(FOUR, DIAMONDS));
    bob->add_card(Card(QUEEN, DIAMONDS));
    bob->add_card(Card(KING, SPADES));
    bob->add_card(Card(TEN, HEARTS));
    bob->add_card(Card(QUEEN, CLUBS));
    
    // Bob doesn’t make trump
    Card king_clubs(KING, CLUBS);
    Suit trump = CLUBS;
    bool orderup = bob->make_trump(
    king_clubs,    // Upcard
    false,           // Bob is not the dealer
    1,              // round 1
    trump           // Suit ordered up (if any)
    );

  // Verify Bob's order up and trump suit
  ASSERT_FALSE(orderup);

  delete bob;
}

// play highest non trump card
TEST(test_simple_player_lead_card_one) {
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

// play highest non trump card
TEST(test_simple_player_lead_card_two) {
    // Bob's hand
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(NINE, HEARTS));
    bob->add_card(Card(TEN, HEARTS));
    bob->add_card(Card(QUEEN, SPADES));
    bob->add_card(Card(KING, SPADES));
    bob->add_card(Card(ACE, SPADES));

    // Bob adds a card to his hand and discards one card
    bob->add_and_discard(Card(NINE, SPADES));

    // Bob leads
    Card card_led = bob->lead_card(SPADES);

    // Verify the card Bob selected to lead
    Card ten_hearts(TEN, HEARTS);
    ASSERT_EQUAL(card_led, ten_hearts); //check led card

    delete bob;
}


// INSERT Ace of Spades
// play highest trump card (all trump cards)
TEST(test_simple_player_lead_card_three) {
    // Bob's hand
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(JACK, SPADES));
    bob->add_card(Card(TEN, SPADES));
    bob->add_card(Card(QUEEN, SPADES));
    bob->add_card(Card(ACE, SPADES));
    bob->add_card(Card(KING, SPADES));

    // Bob adds a card to his hand and discards one card
    bob->add_and_discard(Card(NINE, SPADES));

    // Bob leads
    Card card_led = bob->lead_card(SPADES);

    // Verify the card Bob selected to lead
    Card jack_spades(JACK, SPADES);
    ASSERT_EQUAL(card_led, jack_spades); //check led card

    delete bob;
}



TEST_MAIN()

