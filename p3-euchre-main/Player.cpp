#include <cassert>
#include <iostream>
#include <array>
#include "Player.hpp"
#include <vector>
#include "Card.hpp"
#include <algorithm>

using namespace std;

class HumanPlayer : public Player
{
private:
    string name;
    vector<Card> hand;
    void print_hand() const {
        for (size_t i=0; i < hand.size(); ++i) {
            cout << "Human player " << name << "'s hand: " << "[" << i << "] " << hand[i] << "\n";
        }
    }
public:
    HumanPlayer(const string &name)
    {
        this->name = name;
    }
    const string &get_name() const 
    {
        return name;
    }

    void add_card(const Card &c)
    {
        if (hand.size() <= MAX_HAND_SIZE)
        {
            hand.push_back(c);
        }
        std::sort(hand.begin(), hand.end());
    }

    bool make_trump(const Card &upcard, bool is_dealer,
                    int round, Suit &order_up_suit) const
    {
        print_hand();
        cout << "Human player " << name << ", please enter a suit, or \"pass\":\n";
        string decision;
        cin >> decision;
        

        if (decision != "pass") {
            Suit ordered_up = string_to_suit(decision);
            /*while (ordered_up != upcard.get_suit()) {
                cout << "Invalid Suit! Please re-enter the suit of the upcard." << endl;
                string decision2;
                cin >> decision2;
                ordered_up = string_to_suit(decision);
            } */
            order_up_suit = ordered_up;
            return true;
        
        order_up_suit = ordered_up;
        return true;
        
        }
        else {
            return false;
        }

    }

    void add_and_discard(const Card &upcard)
    {
        std::sort(hand.begin(), hand.end());
        print_hand();
        cout << "Discard upcard: [-1]\n";
        cout << "Human player " << name << ", please select a card to discard:\n";
        int cardNumber;
        cin >> cardNumber;
        if (cardNumber == -1) {
            return;
        } else {
            hand.erase(hand.begin() + cardNumber);
            hand.push_back(upcard);    
            std::sort(hand.begin(), hand.end());
        }

    }

    Card lead_card(Suit trump)
    {
        print_hand();

        int cardNum;
        Card chosenCard;
        
        cout << "Human player " << name << ", please select a card:\n";
        cin >> cardNum;
        
        chosenCard = hand[cardNum];
        hand.erase(hand.begin() + cardNum);
        
        return(chosenCard);
    }

    Card play_card(const Card &led_card, Suit trump)
    {
        print_hand();

        int cardNum;
        Card chosenCard;
        
        cout << "Human player " << name << ", please select a card:\n";
        cin >> cardNum;
        
        chosenCard = hand[cardNum];
        hand.erase(hand.begin() + cardNum);
        
        return(chosenCard);
    }
};

class SimplePlayer : public Player
{
private:
    string name;
    // int points;
    vector<Card> hand;

public:
    SimplePlayer(const string &name)
    {
        this->name = name;
    }
    const string &get_name() const
    {
        return name;
    }

    void add_card(const Card &c)
    {
        if (hand.size() <= MAX_HAND_SIZE)
        {
            hand.push_back(c);
        }
    }

    bool make_trump(const Card &upcard, bool is_dealer,
                    int round, Suit &order_up_suit) const
    {
        int count = 0;
        if (round == 1)
        {
            Suit newSuit = upcard.get_suit();
            for (int i = 0; i < hand.size(); i++)
            {
                if ((hand[i].get_suit() == newSuit && hand[i].is_face_or_ace()) || hand[i].is_left_bower(newSuit))
                {
                    count++;
                }
            }
            if (count >= 2)
            {
                order_up_suit = newSuit;
                return true;
            }
            return false;
        }
        else
        {
            Suit newSuit = Suit_next(upcard.get_suit());
            if (is_dealer)
            {
                order_up_suit = newSuit;
                return true;
            }
            else
            {
                for (int i = 0; i < hand.size(); i++)
                {
                    if (hand[i].get_suit() == newSuit && (hand[i].is_face_or_ace() || hand[i].is_left_bower(newSuit)))
                    {
                        count++;
                    }
                }
                if (count >= 1)
                {
                    order_up_suit = newSuit;
                    return true;
                }
                return false;
            }
        }
    }

    void add_and_discard(const Card &upcard)
    {
        hand.push_back(upcard);
        int lowestCard;
        Card lowestCard1 (JACK, upcard.get_suit());
        for (int i = 0; i < hand.size(); i++)
        {
            if (Card_less(hand[i], lowestCard1, upcard.get_suit()))
            {
                lowestCard = i;
                lowestCard1 = hand[i];
            }
        }
        hand.erase(hand.begin() + lowestCard);
    }

    Card lead_card(Suit trump)
    {
        Card highestCard;
        int highestCardNum = 0;
        bool hasNonTrump = false;
        
        const int HAND_SIZE = hand.size();
        for (int i = 0; i < HAND_SIZE; i++)
        {
            if (!hand[i].is_trump(trump))
            {
                hasNonTrump = true;
            }
        }
        if (hasNonTrump)
        {
            for (int j = 0; j < HAND_SIZE; j++)
            {
                if (!hand[j].is_trump(trump) && Card_less(highestCard, hand[j], trump))
                {
                    highestCard = hand[j];
                    highestCardNum = j;
                }
            }
        }
        else
        {
            for (int k = 0; k < HAND_SIZE; k++)
            {
                if (hand[k].is_trump(trump) && Card_less(highestCard, hand[k], trump))
                {
                    highestCard = hand[k];
                    highestCardNum = k;
                }
            }
        }
        hand.erase(hand.begin() + highestCardNum);
        return highestCard;
    }

    Card play_card(const Card &led_card, Suit trump)
    {
        int chosenCardNum = 0;
        bool hasSuit = false;
        for (int i = 0; i < hand.size(); i++)
        {
            if (hand[i].get_suit() == led_card.get_suit())
            {
                hasSuit = true;
            }
        }
        if (!hasSuit)
        {
            Card chosenCard(JACK, led_card.get_suit());
            for (int j = 0; j < hand.size(); j++)
            {
                if (Card_less(hand[j], chosenCard, led_card, trump))
                {
                    chosenCard = hand[j];
                    chosenCardNum = j;
                }
            }
            hand.erase(hand.begin() + chosenCardNum);
            return chosenCard;
        }
        else
        {
            Card chosenCard(NINE, led_card.get_suit());
            for (int j = 0; j < hand.size(); j++)
            {
                if (hand[j].get_suit() == led_card.get_suit() && hand[j].get_rank() > chosenCard.get_rank())
                {
                    chosenCard = hand[j];
                    chosenCardNum = j;
                }
            }
            hand.erase(hand.begin() + chosenCardNum);
            return chosenCard;
        }
    }
};

Player *Player_factory(const std::string &name, const std::string &strategy)
{
    if (strategy == "Simple")
    {
        // The "new" keyword dynamically allocates an object.
        return new SimplePlayer(name);
    }
    else if (strategy == "Human")
    {
        return new HumanPlayer(name);
    }
    // Repeat for each other type of Player
    // Invalid strategy if we get here
    assert(false);
    return nullptr;
}

std::ostream &
operator<<(std::ostream &os, const Player &p)
{
    os << p.get_name();
    return os;
}