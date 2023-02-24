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

//one of led suit present
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

// left bower is only led suit present
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

//some led suit with right bower present
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

//all led suits with no bowers present
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

// left bower is only led suit present
TEST(test_simple_player_play_card_five) {
      // Bob's hand
      Player * bob = Player_factory("Bob", "Simple");
      bob->add_card(Card(JACK, SPADES));
      bob->add_card(Card(QUEEN, HEARTS));
      bob->add_card(Card(QUEEN, DIAMONDS));
      bob->add_card(Card(KING, HEARTS));
      bob->add_card(Card(NINE, DIAMONDS));

      // Bob plays a card
      Card nine_clubs(NINE, CLUBS);
      Card card_played = bob->play_card(
        nine_clubs,  // seven of clubs is led
        DIAMONDS       // Trump suit
      );

      // Verify the card Bob played
      ASSERT_EQUAL(card_played, Card(NINE, DIAMONDS));
      delete bob;
    }



//no led suits or bowers so plays lowest card
TEST(test_simple_player_play_card_seven) {
      // Bob's hand
      Player * bob = Player_factory("Bob", "Simple");
      bob->add_card(Card(NINE, CLUBS));
      bob->add_card(Card(TEN, HEARTS));
      bob->add_card(Card(QUEEN, DIAMONDS));
      bob->add_card(Card(KING, DIAMONDS));
      bob->add_card(Card(JACK, HEARTS));

      // Bob plays a card
      Card ace_spades(ACE, SPADES);
      Card card_played = bob->play_card(
        ace_spades,  // seven of diamonds is led
        SPADES       // Trump suit
      );

      // Verify the card Bob played
      ASSERT_EQUAL(card_played, Card(NINE, CLUBS));
      delete bob;
    }

//all led suit with left and right bowers present
TEST(test_simple_player_play_card_eight) {
      // Bob's hand
      Player * bob = Player_factory("Bob", "Simple");
      bob->add_card(Card(NINE, DIAMONDS));
      bob->add_card(Card(TEN, DIAMONDS));
      bob->add_card(Card(JACK, DIAMONDS));
      bob->add_card(Card(KING, DIAMONDS));
      bob->add_card(Card(JACK, HEARTS));

      // Bob plays a card
      Card ace_diamonds(ACE, DIAMONDS);
      Card card_played = bob->play_card(
        ace_diamonds,  // seven of diamonds is led
        DIAMONDS       // Trump suit
      );

      // Verify the card Bob played
      ASSERT_EQUAL(card_played, Card(JACK, DIAMONDS));
      delete bob;
    }

//all led suit with  right bower present
TEST(test_simple_player_play_card_nine) {
      // Bob's hand
      Player * bob = Player_factory("Bob", "Simple");
      bob->add_card(Card(NINE, DIAMONDS));
      bob->add_card(Card(TEN, DIAMONDS));
      bob->add_card(Card(JACK, DIAMONDS));
      bob->add_card(Card(KING, DIAMONDS));
      bob->add_card(Card(QUEEN, DIAMONDS));

      // Bob plays a card
      Card ace_diamonds(ACE, DIAMONDS);
      Card card_played = bob->play_card(
        ace_diamonds,  // seven of diamonds is led
        DIAMONDS       // Trump suit
      );

      // Verify the card Bob played
      ASSERT_EQUAL(card_played, Card(JACK, DIAMONDS));
      delete bob;
    }


// right bower is only led suit present
TEST(test_simple_player_play_card_ten) {
      // Bob's hand
      Player * bob = Player_factory("Bob", "Simple");
      bob->add_card(Card(JACK, CLUBS));
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
      ASSERT_EQUAL(card_played, Card(JACK, CLUBS));
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


// round 1, dealer, makes trump
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

// round 2, not a dealer, makes trump
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
//round 2, screw the dealer
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

// round 1, not dealer, makes trump with left bower
TEST(test_simple_player_make_trump_nine) {
    // Bob's hand
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(FOUR, DIAMONDS));
    bob->add_card(Card(QUEEN, DIAMONDS));
    bob->add_card(Card(JACK, SPADES));
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
  ASSERT_TRUE(orderup);
ASSERT_EQUAL(trump, CLUBS);

  delete bob;
}

// round 2, not dealer, makes trump with left bower
TEST(test_simple_player_make_trump_ten) {
    // Bob's hand
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(FOUR, DIAMONDS));
    bob->add_card(Card(QUEEN, DIAMONDS));
    bob->add_card(Card(JACK, SPADES));
    bob->add_card(Card(TEN, HEARTS));
    bob->add_card(Card(QUEEN, HEARTS));
    
    // Bob doesn’t make trump
    Card king_clubs(KING, CLUBS);
    Suit trump = CLUBS;
    bool orderup = bob->make_trump(
    king_clubs,    // Upcard
    false,           // Bob is not the dealer
    2,              // round 1
    trump           // Suit ordered up (if any)
    );
    
    // Verify Bob's order up and trump suit
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, SPADES);

  delete bob;
}

// round 2, not dealer, makes trump with right bower
TEST(test_simple_player_make_trump_eleven) {
    // Bob's hand
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(FOUR, DIAMONDS));
    bob->add_card(Card(QUEEN, DIAMONDS));
    bob->add_card(Card(JACK, CLUBS));
    bob->add_card(Card(TEN, HEARTS));
    bob->add_card(Card(QUEEN, HEARTS));
    
    // Bob makes trump
    Card king_clubs(KING, CLUBS);
    Suit trump = CLUBS;
    bool orderup = bob->make_trump(
    king_clubs,    // Upcard
    false,           // Bob is not the dealer
    2,              // round 2
    trump           // Suit ordered up (if any)
    );
    
    // Verify Bob's order up and trump suit
    ASSERT_TRUE(orderup);
    ASSERT_EQUAL(trump, SPADES);

  delete bob;
}

// all not trump, play highest non trump card
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

// mixed cards, plays highest non trump card
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

// play highest non trump card (not left bower)
TEST(test_simple_player_lead_card_four) {
    // Bob's hand
    Player * bob = Player_factory("Bob", "Simple");
    // jack of diamonds is considered trump suit so not played
    bob->add_card(Card(JACK, DIAMONDS));
    bob->add_card(Card(NINE, SPADES));
    bob->add_card(Card(NINE, CLUBS));
    // jack of clubs is highest none trump
    bob->add_card(Card(JACK, CLUBS));
    bob->add_card(Card(JACK, SPADES));

    // Bob adds a card to his hand and discards one card
    bob->add_and_discard(Card(NINE, HEARTS));

    // Bob leads
    Card card_led = bob->lead_card(HEARTS);

    // Verify the card Bob selected to lead
    Card jack_clubs(JACK, CLUBS);
    ASSERT_EQUAL(card_led, jack_clubs); //check led card

    delete bob;
}


// play highest non trump card (left bower first)
TEST(test_simple_player_lead_card_five) {
    // Bob's hand
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(JACK, SPADES));
    bob->add_card(Card(QUEEN, CLUBS));
    bob->add_card(Card(TEN, HEARTS));
    bob->add_card(Card(QUEEN, HEARTS));
    bob->add_card(Card(KING, CLUBS));

    // Bob adds a card to his hand and discards one card
    bob->add_and_discard(Card(ACE, CLUBS));

    // Bob leads
    Card card_led = bob->lead_card(CLUBS);

    // Verify the card Bob selected to lead
    Card queen_hearts(QUEEN, HEARTS);
    ASSERT_EQUAL(card_led, queen_hearts); //check led card

    delete bob;
}

// play highest non trump card (right and left bower present)
TEST(test_simple_player_lead_card_six) {
    // Bob's hand
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(JACK, SPADES));
    bob->add_card(Card(QUEEN, CLUBS));
    bob->add_card(Card(TEN, HEARTS));
    bob->add_card(Card(QUEEN, HEARTS));
    bob->add_card(Card(JACK, CLUBS));

    // Bob adds a card to his hand and discards one card
    bob->add_and_discard(Card(ACE, CLUBS));

    // Bob leads
    Card card_led = bob->lead_card(CLUBS);

    // Verify the card Bob selected to lead
    Card queen_hearts(QUEEN, HEARTS);
    ASSERT_EQUAL(card_led, queen_hearts); //check led card

    delete bob;
}

// all trump cards so play highest trump
// left and right bowers present
//play right bower
TEST(test_simple_player_lead_card_seven) {
    // Bob's hand
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(QUEEN, HEARTS));
    bob->add_card(Card(JACK, HEARTS));
    bob->add_card(Card(TEN, HEARTS));
    bob->add_card(Card(JACK, DIAMONDS));
    bob->add_card(Card(KING, HEARTS));

    // Bob adds a card to his hand and discards one card
    bob->add_and_discard(Card(ACE, HEARTS));

    // Bob leads
    Card card_led = bob->lead_card(HEARTS);

    // Verify the card Bob selected to lead
    Card jack_hearts(JACK, HEARTS);
    ASSERT_EQUAL(card_led, jack_hearts); //check led card

    delete bob;
}

// all trump cards so play highest trump
// left bower present
TEST(test_simple_player_lead_card_eight) {
    // Bob's hand
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(QUEEN, HEARTS));
    bob->add_card(Card(NINE, HEARTS));
    bob->add_card(Card(TEN, HEARTS));
    bob->add_card(Card(JACK, DIAMONDS));
    bob->add_card(Card(KING, HEARTS));

    // Bob adds a card to his hand and discards one card
    bob->add_and_discard(Card(ACE, HEARTS));

    // Bob leads
    Card card_led = bob->lead_card(HEARTS);

    // Verify the card Bob selected to lead
    Card jack_diamonds(JACK, DIAMONDS);
    ASSERT_EQUAL(card_led, jack_diamonds); //check led card

    delete bob;
}

TEST_MAIN()