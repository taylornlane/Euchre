#include "Pack.hpp"
#include "unit_test_framework.hpp"

#include <iostream>
#include <fstream>

using namespace std;

TEST(test_pack_default_ctor)
{
    Pack pack;
    Card first = pack.deal_one();
    ASSERT_EQUAL(NINE, first.get_rank());
    ASSERT_EQUAL(SPADES, first.get_suit());
}

TEST(test_pack_file_ctor)
{
    ifstream infile("pack.in");
    Pack pack(infile);

    Card first = pack.deal_one();
    ASSERT_EQUAL(NINE, first.get_rank());
    ASSERT_EQUAL(SPADES, first.get_suit());
}

TEST(test_pack_deal_one)
{
    Pack pack;
    Card card = pack.deal_one();
    ASSERT_EQUAL(NINE, card.get_rank());
    ASSERT_EQUAL(SPADES, card.get_suit());
}

TEST_MAIN()
