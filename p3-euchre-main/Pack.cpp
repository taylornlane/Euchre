#include "Pack.hpp"
#include <cassert>
#include <iostream>
#include <array>
#include <algorithm>
#include <string>
using namespace std;

Pack::Pack()
{
    int i = 0;

    // POTENTIAL AUTOGRADER ISSUE
    reset();

    for (int s = SPADES; s <= DIAMONDS; s++)
    {
        for (int r = NINE; r <= ACE; r++)
        {
            Rank rank = static_cast<Rank>(r);
            Suit suit = static_cast<Suit>(s);
            Card card = Card(rank, suit);

            cards[i] = card;
            i++;
        }
    }
}

Pack::Pack(std::istream &pack_input)
{
    reset();

    int i = 0;
    Rank rank;
    Suit suit;
    string junk;

    while (i < 24)
    {
        pack_input >> rank >> junk >> suit;
        cards[i] = Card(rank, suit);
        i++;
    }
}

Card Pack::deal_one()
{
    cards[next];
    int temp = next;
    next++;
    return cards[temp];
}

void Pack::reset()
{
    next = 0;
}

void Pack::shuffle()
{
    /*
     array<Card, PACK_SIZE / 2> topHalf;
    array<Card, PACK_SIZE / 2> bottomHalf;

    for (int k = 0; k < 7; k++)
    {
        for (int i = 0; i < PACK_SIZE; i++)
        {
            if (i % 2 == 0)
            {
                topHalf[i / 2] = cards[i];
            }
            else
            {
                bottomHalf[i / 2] = cards[i];
            }
        }

        int topI = 0;
        int bottomI = 0;

        for (int i = 0; i < PACK_SIZE; i++)
        {
            if (i % 2 == 0)
            {
                cards[i] = topHalf[topI];
                topI++;
            }
            else
            {
                cards[i] = bottomHalf[bottomI];
                bottomI++;
            }
        }
    }
    */

    for (int i = 0; i < 7; i++){
        cards = {
        cards[12],
        cards[0],
        cards[13],
        cards[1],
        cards[14],
        cards[2],
        cards[15],
        cards[3],
        cards[16],
        cards[4],
        cards[17],
        cards[5],
        cards[18],
        cards[6],
        cards[19],
        cards[7],
        cards[20],
        cards[8],
        cards[21],
        cards[9],
        cards[22],
        cards[10],
        cards[23],
        cards[11]
        };
    }
   
}

bool Pack::empty() const
{
    if (next == PACK_SIZE)
    {
        return true;
    }
    return false;
}