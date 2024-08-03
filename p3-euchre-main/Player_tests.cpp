#include "Player.hpp"
#include "unit_test_framework.hpp"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

TEST (test_add_card) {
    Player * bob = Player_factory("Bob", "Simple");
    Card card_add(ACE, HEARTS);
    bob->add_card(card_add);
    Suit lead_suit = HEARTS;
    Card lead_card = bob->lead_card(lead_suit);
    ASSERT_EQUAL(lead_card, card_add);
    delete bob;
}
TEST(test_add_and_discard) {
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(NINE, SPADES));
    bob->add_card(Card(TEN, SPADES));
    bob->add_card(Card(QUEEN, SPADES));
    bob->add_card(Card(KING, SPADES));
    bob->add_card(Card(ACE, SPADES));

    Card upcard(KING, DIAMONDS);
    bob->add_and_discard(upcard);
    
    Card led_card(NINE, HEARTS);
    
    Card card_played = bob->play_card(
        led_card,  // Nine of Diamonds is led
        DIAMONDS   // Trump suit
    ); 

   
    ASSERT_EQUAL(card_played, Card(TEN, SPADES));
    delete bob;

     /*
    Player * bob2 = Player_factory("Bob", "Simple");
    bob2->add_card(Card(JACK, DIAMONDS));
    bob2->add_card(Card(TEN, DIAMONDS));
    bob2->add_card(Card(QUEEN, DIAMONDS));
    bob2->add_card(Card(KING, DIAMONDS));
    bob2->add_card(Card(ACE, DIAMONDS));

    Card upcard2(NINE, DIAMONDS);
    bob2->add_and_discard(upcard);
    
    // Verify the card Bob played
    Card card_played2 = bob2->play_card(
        led_card,  
        DIAMONDS   // Trump suit
    );
    ASSERT_EQUAL(card_played2, Card(TEN, DIAMONDS));
    delete bob2;
    */

}
TEST (test_make_trump) {
    Player * bob1 = Player_factory("Bob", "Simple");
    bob1->add_card(Card(NINE, SPADES));
    bob1->add_card(Card(TEN, SPADES));
    bob1->add_card(Card(QUEEN, SPADES));
    bob1->add_card(Card(NINE, HEARTS));
    bob1->add_card(Card(NINE, CLUBS));

    // Bob makes tump
    Card king_spades(KING, SPADES);
    Suit trump1;
    bool orderup = bob1->make_trump(
        king_spades,    // Upcard
        true,           // Bob is also the dealer
        1,              // First round
        trump1           // Suit ordered up (if any)
    );

    // Verify Bob's order up and trump suit
    ASSERT_TRUE(!orderup);
    //ASSERT_EQUAL(trump, SPADES);
    Player * bob6 = Player_factory("Bob", "Simple");
    bob6->add_card(Card(JACK, CLUBS));
    bob6->add_card(Card(NINE, SPADES));
    bob6->add_card(Card(QUEEN, SPADES));
    bob6->add_card(Card(NINE, HEARTS));
    bob6->add_card(Card(NINE, CLUBS));

    // Bob makes trump
    
    Suit trump6;
    bool orderup6 = bob6->make_trump(
        king_spades,    // Upcard
        true,           // Bob is also the dealer
        1,              // First round
        trump6           // Suit ordered up (if any)
    );

    // Verify Bob's order up and trump suit
    ASSERT_TRUE(orderup6);
    ASSERT_EQUAL(trump6, SPADES);
    delete bob6;
    
    Player * bob7 = Player_factory("Bob", "Simple");
    bob7->add_card(Card(NINE, SPADES));
    bob7->add_card(Card(ACE, SPADES));
    bob7->add_card(Card(QUEEN, SPADES));
    bob7->add_card(Card(NINE, HEARTS));
    bob7->add_card(Card(NINE, CLUBS));

    // Bob makes tump
    
    Suit trump7;
    bool orderup7 = bob7->make_trump(
        king_spades,    // Upcard
        true,           // Bob is also the dealer
        1,              // First round
        trump7           // Suit ordered up (if any)
    );

    // Verify Bob's order up and trump suit
    ASSERT_TRUE(orderup7);
    ASSERT_EQUAL(trump7, SPADES);
    delete bob7;

    bool orderup2 = bob1->make_trump(
        king_spades,    // Upcard
        true,           // Bob is also the dealer
        2,              // First round
        trump1           // Suit ordered up (if any)
    );
    ASSERT_TRUE(orderup2);
    ASSERT_EQUAL(trump1, CLUBS);
    delete bob1;

    Player * bob2 = Player_factory("Bob", "Simple");
    bob2->add_card(Card(NINE, SPADES));
    bob2->add_card(Card(TEN, SPADES));
    bob2->add_card(Card(QUEEN, SPADES));
    bob2->add_card(Card(NINE, HEARTS));
    bob2->add_card(Card(JACK, CLUBS));

    // Bob makes tump
    
    Suit trump2;
    bool orderup3 = bob2->make_trump(
        king_spades,    // Upcard
        false,           // Bob is also the dealer
        2,              // First round
        trump2           // Suit ordered up (if any)
    );

    // Verify Bob's order up and trump suit
    ASSERT_TRUE(orderup3);
    
    Card king_diamonds(KING, DIAMONDS);
    Suit trump3;
    bool orderup4 = bob2->make_trump(
        king_diamonds,    // Upcard
        false,           // Bob is also the dealer
        2,              // First round
        trump3           // Suit ordered up (if any)
    );
    ASSERT_TRUE(!orderup4);
    
    delete bob2;

    Player * bob3 = Player_factory("Bob", "Simple");
    bob3->add_card(Card(NINE, SPADES));
    bob3->add_card(Card(TEN, SPADES));
    bob3->add_card(Card(QUEEN, SPADES));
    bob3->add_card(Card(ACE, HEARTS));
    bob3->add_card(Card(JACK, CLUBS));

    // Bob makes tump
    
    Suit trump4;
    bool orderup5 = bob3->make_trump(
        king_diamonds,    // Upcard
        false,           // Bob is also the dealer
        2,              // First round
        trump4          // Suit ordered up (if any)
    );
    ASSERT_TRUE(orderup5);
    ASSERT_EQUAL(trump4, HEARTS);
    delete bob3;
    
    Player * bob8 = Player_factory("Bob", "Simple");
    bob8->add_card(Card(NINE, SPADES));
    bob8->add_card(Card(TEN, SPADES));
    bob8->add_card(Card(QUEEN, SPADES));
    bob8->add_card(Card(ACE, HEARTS));
    bob8->add_card(Card(JACK, HEARTS));

    // Bob makes tump
    
    Suit trump8;
    bool orderup8 = bob8->make_trump(
        king_diamonds,    // Upcard
        false,           // Bob is also the dealer
        2,              // First round
        trump8          // Suit ordered up (if any)
    );
    ASSERT_TRUE(orderup8);
    ASSERT_EQUAL(trump8, HEARTS);
    delete bob8;

    

}

TEST (test_lead_card) {
 // Bob's hand
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(NINE, SPADES));
    bob->add_card(Card(TEN, SPADES));
    bob->add_card(Card(QUEEN, SPADES));
    bob->add_card(Card(KING, SPADES));
    bob->add_card(Card(ACE, SPADES));

    // Bob adds a card to his hand and discards one card
    bob->add_and_discard(
        Card(NINE, HEARTS) // upcard
    );

    // Bob leads
    Card card_led = bob->lead_card(HEARTS);

    // Verify the card Bob selected to lead
    Card ace_spades(ACE, SPADES);
    ASSERT_EQUAL(card_led, ace_spades); //check led card
    delete bob;
    //new case
    Player * bob2 = Player_factory("Bob", "Simple");
    bob2->add_card(Card(NINE, HEARTS));
    bob2->add_card(Card(TEN, SPADES));
    bob2->add_card(Card(QUEEN, SPADES));
    bob2->add_card(Card(KING, SPADES));
    bob2->add_card(Card(ACE, SPADES));
    bob2->add_and_discard(
        Card(NINE, SPADES) // upcard
    );
    

    // Bob leads
    Card card_led2 = bob2->lead_card(SPADES);

    // Verify the card Bob selected to lead
    
    ASSERT_EQUAL(card_led2, ace_spades); //check led card

    delete bob2;
}

TEST(test_play_card) {
    Player * bob = Player_factory("Bob", "Simple");
    bob->add_card(Card(NINE, SPADES));
    bob->add_card(Card(TEN, SPADES));
    bob->add_card(Card(QUEEN, SPADES));
    bob->add_card(Card(KING, SPADES));
    bob->add_card(Card(ACE, SPADES));

    // Bob plays a card
    Card nine_diamonds(NINE, DIAMONDS);
    Card card_played = bob->play_card(
        nine_diamonds,  // Nine of Diamonds is led
        HEARTS    // Trump suit
    ); 

    // Verify the card Bob played
    ASSERT_EQUAL(card_played, Card(NINE, SPADES));
    delete bob;

    Player * bob2 = Player_factory("Bob", "Simple");
    bob2->add_card(Card(NINE, HEARTS));
    bob2->add_card(Card(TEN, SPADES));
    bob2->add_card(Card(QUEEN, SPADES));
    bob2->add_card(Card(KING, SPADES));
    bob2->add_card(Card(ACE, SPADES));

    // Bob plays a card
    Card nine_spades(NINE, SPADES);
    Card card_played2 = bob2->play_card(
        nine_spades,  // Nine of Diamonds is led
        CLUBS    // Trump suit
    ); 

    // Verify the card Bob played
    ASSERT_EQUAL(card_played2, Card(ACE, SPADES));
    delete bob2;

    Player * bob3 = Player_factory("Bob", "Simple");
    bob3->add_card(Card(NINE, SPADES));
    bob3->add_card(Card(TEN, SPADES));
    bob3->add_card(Card(QUEEN, SPADES));
    bob3->add_card(Card(JACK, SPADES));
    bob3->add_card(Card(JACK, CLUBS));

    // Bob plays a card
    
    Card card_played3 = bob->play_card(
        nine_spades,  // Nine of Diamonds is led
        CLUBS   // Trump suit
    ); 

    // Verify the card Bob played
    ASSERT_EQUAL(card_played3, Card(QUEEN, SPADES));
    delete bob3;

    Player * bob4 = Player_factory("Bob", "Simple");
    bob4->add_card(Card(NINE, HEARTS));
    bob4->add_card(Card(TEN, HEARTS));
    bob4->add_card(Card(QUEEN, SPADES));
    bob4->add_card(Card(KING, HEARTS));
    bob4->add_card(Card(ACE, SPADES));

    // Bob plays a card
    Card card_played4 = bob4->play_card(
        nine_diamonds,  // Nine of Diamonds is led
        HEARTS    // Trump suit
    ); 

    // Verify the card Bob played
    ASSERT_EQUAL(card_played4, Card(QUEEN, SPADES));
    delete bob4;
}


// Add more tests here

TEST_MAIN()
