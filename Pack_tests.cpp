// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Pack.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;

TEST(test_pack_default_ctor) {
    Pack pack;
    Card first = pack.deal_one();
    ASSERT_EQUAL(NINE, first.get_rank());
    ASSERT_EQUAL(SPADES, first.get_suit());
}

// Add more tests here
TEST(test_pack_next) {
    Pack pack;
    Card first = pack.deal_one();
    ASSERT_EQUAL(NINE, first.get_rank());
    ASSERT_EQUAL(SPADES, first.get_suit());
    Card second = pack.deal_one();
    ASSERT_EQUAL(TEN, second.get_rank());
    ASSERT_EQUAL(SPADES, second.get_suit());
   

}
//MOVING TO NEXT SUITE IN DECK
TEST(test_pack_next2) {
    Pack pack;
    Card test = Card(ACE, SPADES);
    test = pack.deal_one();
    test = pack.deal_one();
    test = pack.deal_one();
    test = pack.deal_one();
    test = pack.deal_one();
    test = pack.deal_one();
    test = pack.deal_one();
  
 

    ASSERT_EQUAL(NINE, test.get_rank());
    ASSERT_EQUAL(HEARTS, test.get_suit());
}
TEST(test_pack_shuffle) {
    Pack pack; 
}
TEST(test_pack_empty) {
    Card c;
    Card b; 
    //Pack cards.at(23) = c(JACK,SPADES);

    //Pack cards.at(22) = b(JACK,HEARTS);  
    //Pack next = 24; 
    //cards.at(24)
}
TEST_MAIN()
