// Project UID 1d9f47bfc76643019cfbf037641defe1
#include <iostream>
#include <fstream>
#include <array>
#include <string>
#include "Player.h"
#include "Pack.h"
#include "Card.h"
#include <vector>
#include "unit_test_framework.h"
using namespace std;

// INSERT Ten of Diamonds
//TEST HUMAN PLAYER PLAY CARD led suit
TEST(test_human_player_play_card_one) {
      // Bob's hand
    Player * bob = Player_factory("Bob", "Human");
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

//INSERT Nine of Spades
//TEST Human PLAYER PLAY CARD, has no led suit
TEST(test_human_player_play_card_two) {
      // Bob's hand
      Player * bob = Player_factory("Bob", "Human");
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
//INSERT Jack of Diamonds
//TEST HUMAN PLAYER PLAY CARD, all led suit with right bower
TEST(test_human_player_play_card_three) {
      // Bob's hand
      Player * bob = Player_factory("Bob", "Human");
      bob->add_card(Card(NINE, DIAMONDS));
      bob->add_card(Card(TEN, DIAMONDS));
      bob->add_card(Card(JACK, DIAMONDS));
      bob->add_card(Card(KING, DIAMONDS));
      bob->add_card(Card(FIVE, DIAMONDS));

      // Bob plays a card
      Card seven_diamonds(SEVEN, DIAMONDS);
      Card card_played = bob->play_card(
        seven_diamonds,  // seven of diamonds is led
        DIAMONDS       // Trump suit
      );

      // Verify the card Bob played
      ASSERT_EQUAL(card_played, Card(JACK, DIAMONDS));
      delete bob;
    }


//INSERT King of Diamonds
//TEST HUMAN PLAYER PLAY CARD, all led suit
TEST(test_human_player_play_card_four) {
      // Bob's hand
      Player * bob = Player_factory("Bob", "Human");
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

//INSERT Queen of Hearts
//TEST HUMAN PLAYER PLAY CARD, none of led suit, right bower
TEST(test_human_player_play_card_five) {
      // Bob's hand
      Player * bob = Player_factory("Bob", "Human");
      bob->add_card(Card(JACK, SPADES));
      bob->add_card(Card(QUEEN, HEARTS));
      bob->add_card(Card(QUEEN, DIAMONDS));
      bob->add_card(Card(KING, HEARTS));
      bob->add_card(Card(ACE, DIAMONDS));

      // Bob plays a card
      Card seven_clubs(SEVEN, CLUBS);
      Card card_played = bob->play_card(
        seven_clubs,  // seven of clubs is led
        CLUBS       // Trump suit
      );

      // Verify the card Bob played
      ASSERT_EQUAL(card_played, Card(JACK, SPADES));
      delete bob;
    }

// INSERT Ace of Spades
// play highest non trump card (all non trump cards)
TEST(test_human_player_lead_card_one) {
    // Bob's hand
    Player * bob = Player_factory("Bob", "Human");
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

// INSERT Ten of Hearts
// play highest non trump card
TEST(test_human_player_lead_card_two) {
    // Bob's hand
    Player * bob = Player_factory("Bob", "Human");
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
TEST(test_human_player_lead_card_three) {
    // Bob's hand
    Player * bob = Player_factory("Bob", "Human");
    bob->add_card(Card(FIVE, SPADES));
    bob->add_card(Card(TEN, SPADES));
    bob->add_card(Card(QUEEN, SPADES));
    bob->add_card(Card(ACE, SPADES));
    bob->add_card(Card(KING, SPADES));

    // Bob adds a card to his hand and discards one card
    bob->add_and_discard(Card(NINE, SPADES));

    // Bob leads
    Card card_led = bob->lead_card(SPADES);

    // Verify the card Bob selected to lead
    Card ace_spades(ACE, SPADES);
    ASSERT_EQUAL(card_led, ace_spades); //check led card

    delete bob;
}


TEST(test_player_get_name_human) {
    Player * alice = Player_factory("Alice", "Human");
    ASSERT_EQUAL("Alice", alice->get_name());
    delete alice;
}

// INSERT PASS
// human hand bob has to pass round 1
TEST(test_human_player_make_trump_one) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Human");
  bob->add_card(Card(FOUR, DIAMONDS));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(KING, HEARTS));
  bob->add_card(Card(FIVE, HEARTS));

  // Bob doesn't make trump
  Card king_hearts(KING, HEARTS);
    Suit trump = HEARTS;
  bool orderup = bob->make_trump(
    king_hearts,    // Upcard
    false,           // Bob is also the dealer
    1,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_FALSE(orderup);
  ASSERT_EQUAL(trump, HEARTS);

  delete bob;
}

// INSERT Hearts
// human hand bob makes trump round 1
TEST(test_human_player_make_trump_two) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Human");
  bob->add_card(Card(FOUR, DIAMONDS));
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(KING, HEARTS));
  bob->add_card(Card(QUEEN, HEARTS));

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

// INSERT Diamonds
// test human hand round 2 makes trump
TEST(test_human_player_make_trump_three) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Human");
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(QUEEN, DIAMONDS));
  bob->add_card(Card(KING, CLUBS));
  bob->add_card(Card(FIVE, CLUBS));

  // Bob makes trump
  Card king_hearts(KING, HEARTS);
    Suit trump = HEARTS;
  bool orderup = bob->make_trump(
    king_hearts,    // Upcard
    false,           // Bob is also the dealer
    2,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, DIAMONDS);

  delete bob;
}

// INSERT PASS
// human hand bob doesn't make trump round 2
TEST(test_human_player_make_trump_four) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Human");
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(FOUR, DIAMONDS));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(QUEEN, CLUBS));

  // Bob makes trump
  Card king_hearts(KING, HEARTS);
    Suit trump = HEARTS;
  bool orderup = bob->make_trump(
    king_hearts,    // Upcard
    false,           // Bob is also the dealer
    2,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_FALSE(orderup);
  ASSERT_EQUAL(trump, HEARTS);

  delete bob;
}

// INSERT PASS
// human hand doesn't make trump round 1, dealer
TEST(test_human_player_make_trump_five) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Human");
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(FOUR, DIAMONDS));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(QUEEN, CLUBS));

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

// INSERT Diamonds
// human hand round 2, dealer
TEST(test_human_player_make_trump_six) {
  // Bob's hand
  Player * bob = Player_factory("Bob", "Human");
  bob->add_card(Card(TEN, SPADES));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(FOUR, DIAMONDS));
  bob->add_card(Card(KING, SPADES));
  bob->add_card(Card(QUEEN, CLUBS));

  // Bob makes trump
  Card king_hearts(KING, HEARTS);
    Suit trump = HEARTS;
  bool orderup = bob->make_trump(
    king_hearts,    // Upcard
    true,           // Bob is also the dealer
    2,              // First round
    trump           // Suit ordered up (if any)
  );

  // Verify Bob's order up and trump suit
  ASSERT_TRUE(orderup);
  ASSERT_EQUAL(trump, DIAMONDS);

  delete bob;
}

TEST_MAIN()

