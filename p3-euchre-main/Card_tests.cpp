#include "Card.hpp"
#include "unit_test_framework.hpp"
#include <iostream>

using namespace std;

TEST(test_card_ctor)
{
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
    ASSERT_EQUAL(HEARTS, c.get_suit());
}

TEST(test_def_card_ctor)
{
    Card c;
    ASSERT_EQUAL(TWO, c.get_rank());
    ASSERT_EQUAL(SPADES, c.get_suit());
}

TEST(test_get_rank)
{
    Card c(ACE, HEARTS);
    ASSERT_EQUAL(ACE, c.get_rank());
}

TEST(test_get_suit_trump)
{
    Card c(JACK, HEARTS);
    ASSERT_EQUAL(DIAMONDS, c.get_suit(DIAMONDS));

    Card c1(JACK, SPADES);
    ASSERT_EQUAL(CLUBS, c1.get_suit(CLUBS));

    Card c2(JACK, DIAMONDS);
    ASSERT_EQUAL(HEARTS, c2.get_suit(HEARTS));

    Card c3(JACK, CLUBS);
    ASSERT_EQUAL(SPADES, c3.get_suit(SPADES));
}

TEST(test_is_face_or_ace)
{
    Card c1(JACK, HEARTS);
    ASSERT_EQUAL(true, c1.is_face_or_ace());
    Card c3(QUEEN, HEARTS);
    ASSERT_EQUAL(true, c3.is_face_or_ace());
    Card c4(KING, SPADES);
    ASSERT_EQUAL(true, c4.is_face_or_ace());
    Card c5(ACE, CLUBS);
    ASSERT_EQUAL(true, c5.is_face_or_ace());
    Card c2(TWO, HEARTS);
    ASSERT_EQUAL(false, c2.is_face_or_ace());

}

TEST(test_is_right_bower)
{
    Card c(JACK, HEARTS);
    ASSERT_EQUAL(true, c.is_right_bower(HEARTS))

    Card c1(JACK, SPADES);
    ASSERT_EQUAL(false, c1.is_right_bower(HEARTS))

    Card c2(KING, HEARTS);
    ASSERT_EQUAL(false, c2.is_right_bower(HEARTS))
}

TEST(test_is_left_bower)
{
    Card c(JACK, HEARTS);
    ASSERT_EQUAL(true, c.is_left_bower(DIAMONDS))

    Card c1(JACK, DIAMONDS);
    ASSERT_EQUAL(true, c1.is_left_bower(HEARTS))

    Card c2(JACK, CLUBS);
    ASSERT_EQUAL(true, c2.is_left_bower(SPADES))

    Card c3(JACK, SPADES);
    ASSERT_EQUAL(true, c3.is_left_bower(CLUBS))

    Card c4(JACK, SPADES);
    ASSERT_EQUAL(false, c4.is_left_bower(DIAMONDS))

    Card c5(KING, HEARTS);
    ASSERT_EQUAL(false, c5.is_left_bower(DIAMONDS))
}

TEST(test_is_trump)
{
    Card c1(TWO, HEARTS);
    ASSERT_EQUAL(true, c1.is_trump(HEARTS));

    Card c2(TWO, CLUBS);
    ASSERT_EQUAL(false, c2.is_trump(HEARTS));

    Card c3(JACK, SPADES);
    ASSERT_EQUAL(true, c3.is_trump(CLUBS));

    Card c4(JACK, HEARTS);
    ASSERT_EQUAL(false, c4.is_trump(SPADES))
}

TEST(test_suit_next)
{
    ASSERT_EQUAL(DIAMONDS, Suit_next(HEARTS));
    ASSERT_EQUAL(CLUBS, Suit_next(SPADES));
    ASSERT_EQUAL(SPADES, Suit_next(CLUBS));
    ASSERT_EQUAL(HEARTS, Suit_next(DIAMONDS));
}

TEST(test_operator_less_than)
{
    Card c1(TWO, HEARTS);
    Card c2(THREE, HEARTS);

    Card c3(QUEEN, HEARTS);
    Card c4(KING, HEARTS);

    ASSERT_EQUAL(true, (c1 < c2));
    ASSERT_EQUAL(false, (c2 < c1));
    ASSERT_EQUAL(true, (c3 < c4));
    ASSERT_EQUAL(false, (c4 < c3));
    ASSERT_EQUAL(false, (c4 < c4));
}

TEST(test_operator_less_than_equal)
{
    Card c1(TWO, HEARTS);
    Card c2(THREE, HEARTS);

    Card c3(QUEEN, HEARTS);
    Card c4(KING, HEARTS);

    ASSERT_EQUAL(true, (c1 <= c2));
    ASSERT_EQUAL(false, (c2 <= c1));
    ASSERT_EQUAL(true, (c3 <= c4));
    ASSERT_EQUAL(false, (c4 <= c3));
    ASSERT_EQUAL(true, (c4 <= c4));
}

TEST(test_operator_more_than)
{
    Card c1(TWO, HEARTS);
    Card c2(THREE, HEARTS);

    Card c3(QUEEN, HEARTS);
    Card c4(KING, HEARTS);

    ASSERT_EQUAL(false, (c1 > c2));
    ASSERT_EQUAL(true, (c2 > c1));
    ASSERT_EQUAL(false, (c3 > c4));
    ASSERT_EQUAL(true, (c4 > c3));
    ASSERT_EQUAL(false, (c4 > c4));
}

TEST(test_operator_more_than_equal)
{
    Card c1(TWO, HEARTS);
    Card c2(THREE, HEARTS);

    Card c3(QUEEN, HEARTS);
    Card c4(KING, HEARTS);

    ASSERT_EQUAL(false, (c1 >= c2));
    ASSERT_EQUAL(true, (c2 >= c1));
    ASSERT_EQUAL(false, (c3 >= c4));
    ASSERT_EQUAL(true, (c4 >= c3));
    ASSERT_EQUAL(true, (c4 >= c4));
}

TEST(test_operator_equal)
{
    Card c1(FOUR, SPADES);
    Card c2(FOUR, SPADES);
    Card c3(FIVE, SPADES);
    Card c4(FOUR, DIAMONDS);

    ASSERT_EQUAL(true, c1 == c2);
    ASSERT_EQUAL(false, c1 == c3);
    ASSERT_EQUAL(false, c1 == c4);
}

TEST(test_operator_not_equal)
{
    Card c1(FOUR, SPADES);
    Card c2(FOUR, SPADES);
    Card c3(FIVE, SPADES);
    Card c4(FOUR, DIAMONDS);

    ASSERT_EQUAL(false, c1 != c2);
    ASSERT_EQUAL(true, c1 != c3);
    ASSERT_EQUAL(true, c1 != c4);
}

TEST(test_card_less)
{
    Card c(TWO, HEARTS);
    Card c1(THREE, HEARTS);
    ASSERT_EQUAL(true, Card_less(c, c1, HEARTS));

    Card c2(TWO, HEARTS);
    Card c3(THREE, CLUBS);
    ASSERT_EQUAL(false, Card_less(c2, c3, HEARTS));

    Card c4(TWO, HEARTS);
    Card c5(TWO, HEARTS);
    ASSERT_EQUAL(false, Card_less(c4, c5, HEARTS));

    Card c6(TWO, CLUBS);
    Card c7(THREE, DIAMONDS);
    ASSERT_EQUAL(true, Card_less(c6, c7, HEARTS));
    ASSERT_EQUAL(false, Card_less(c7, c6, HEARTS));

    Card c8(TWO, CLUBS);
    Card c9(TWO, DIAMONDS);
    ASSERT_EQUAL(true, Card_less(c8, c9, HEARTS));

    Card c10(JACK, DIAMONDS);
    Card c11(THREE, HEARTS);
    ASSERT_EQUAL(false, Card_less(c10, c11, HEARTS));

    Card c12(JACK, HEARTS);
    Card c13(KING, HEARTS);
    ASSERT_EQUAL(false, Card_less(c12, c13, HEARTS));
    ASSERT_EQUAL(true, Card_less(c13, c12, HEARTS));
}

TEST(test_card_less_led)
{
    Card ledCard(QUEEN, SPADES);
    Card c(TWO, HEARTS);
    Card c1(THREE, HEARTS);
    ASSERT_EQUAL(true, Card_less(c, c1, ledCard, HEARTS));

    Card c2(TWO, HEARTS);
    Card c3(THREE, CLUBS);
    ASSERT_EQUAL(false, Card_less(c2, c3, ledCard, HEARTS));

    Card c4(TWO, HEARTS);
    Card c5(TWO, HEARTS);
    ASSERT_EQUAL(false, Card_less(c4, c5, ledCard, HEARTS));

    Card c6(TWO, CLUBS);
    Card c7(THREE, DIAMONDS);
    ASSERT_EQUAL(true, Card_less(c6, c7, ledCard, HEARTS));
    ASSERT_EQUAL(false, Card_less(c7, c6, ledCard, HEARTS));

    Card c8(TWO, CLUBS);
    Card c9(TWO, DIAMONDS);
    ASSERT_EQUAL(true, Card_less(c8, c9, ledCard, HEARTS));

    Card c10(JACK, DIAMONDS);
    Card c11(THREE, HEARTS);
    ASSERT_EQUAL(false, Card_less(c10, c11, ledCard, HEARTS));

    Card c12(JACK, HEARTS);
    Card c13(KING, HEARTS);
    ASSERT_EQUAL(false, Card_less(c12, c13, ledCard, HEARTS));
    ASSERT_EQUAL(true, Card_less(c13, c12, ledCard, HEARTS));

    Card c14(KING, SPADES);
    Card c15(THREE, SPADES);
    ASSERT_EQUAL(false, Card_less(c14, c15, ledCard, HEARTS));

    Card c16(FOUR, SPADES);
    Card c17(KING, CLUBS);
    ASSERT_EQUAL(false, Card_less(c16, c17, ledCard, HEARTS));
}

TEST_MAIN()
