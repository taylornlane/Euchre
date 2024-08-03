#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <string>

#include "Card.hpp"
#include "Player.hpp"
#include "Pack.hpp"

using namespace std;

class Game {
public:
  // Pack pack, String shuffle, 4x(String Playername, String playertype)
   Game(Pack pack, string shuffle, int winPoints,
       string playerName1, string playerType1,
       string playerName2, string playerType2,
       string playerName3, string playerType3,
       string playerName4, string playerType4) {


       this->pack = pack;
       this->shuffle = shuffle;
       this->winPoints = winPoints;
      
        

       Player *player1 = Player_factory(playerName1, playerType1);
       Player *player2 = Player_factory(playerName2, playerType2);
       Player *player3 = Player_factory(playerName3, playerType3);
       Player *player4 = Player_factory(playerName4, playerType4);

       players.push_back(player1);
       players.push_back(player2);
       players.push_back(player3);
       players.push_back(player4);

       
   }


void play(){
   playerOneName = players[0]->get_name();
   playerTwoName = players[1]->get_name();
   playerThreeName = players[2]->get_name();
   playerFourName = players[3]->get_name();
  
    playerTeams.push_back(1);
    playerTeams.push_back(2);
    playerTeams.push_back(1);
    playerTeams.push_back(2);
   shuffle_reset();

   int handNumber = 0;
   
   while (team1Points <= winPoints && team2Points <= winPoints) {
       cout << "Hand " << handNumber << endl;
       cout << players[0]->get_name() << " deals" << endl;


       play_hand();
       ++handNumber;
      
   }
   if (team1Points > team2Points) {
      cout << playerOneName << " and " << playerThreeName << " win!" << endl;
   } else {
     cout << playerTwoName << " and " << playerFourName << " win!" << endl;
   }

   for (size_t i = 0; i < players.size(); ++i) {
    delete players[i];
   }
}




   private:
   string playerOneName;
   string playerTwoName;
   string playerThreeName;
   string playerFourName;


   vector<Player*> players;
   Pack pack;
   string shuffle;
   int winPoints;
  
   vector<int> playerTeams;


   int tricksWonTeam1;
   int tricksWonTeam2;




   int teamOrderedUp;


   int team1Points;
   int team2Points;


   Card led_card;
   Card upcard;


   vector<Player*> playersTrick;
   vector<int> teamsTrick;

   Suit order_up_suit;
   
//const Card &upcard, Suit &order_up_suit
void play_hand() { // need to change inputs after deal
   deal();
   rotateDeal();
   upcard = pack.deal_one();
   cout << upcard << " turned up" << endl;
   make_trump();


   playersTrick = players;
   teamsTrick = playerTeams;
   //making copies of our vectors to use in trick
 
   for (int i = 0; i < 5; i++) {
       play_trick(order_up_suit);
   }
   

   if (tricksWonTeam1 > tricksWonTeam2) {
       cout << playerOneName << " and " <<  playerThreeName << " win the hand " << endl;
       if (teamOrderedUp == 1) {
           if (tricksWonTeam1 == 3 || tricksWonTeam1 == 4) {
               team1Points += 1;
              } else { //march
               team1Points += 2;
               cout << "march!" << endl;
           }
       } else { //euchred
           team1Points += 2;
           cout << "euchred!" << endl;
       }
   } else {
       cout << playerTwoName << " and " <<  playerFourName << " win the hand " << endl;
       if (teamOrderedUp == 2) {
           if (tricksWonTeam2 == 3 || tricksWonTeam2 == 4) {
               team2Points += 1;
              } else { //march
               team2Points += 2;
               cout << "march!" << endl;
           }
          } else { //euchred
           team2Points += 2;
           cout << "euchred!" << endl;
       }
   }
   cout << playerOneName << " and " <<  playerThreeName << " have " << team1Points << " points" << endl;
   cout << playerTwoName << " and " <<  playerFourName << " have " << team1Points << " points" << endl;


}

void shuffle_reset(){
   if (strcmp(shuffle.c_str(), "shuffle") == 0){
       pack.shuffle();
       pack.reset();
   } else {
       pack.reset();
   } 
}

void deal(){
   players[1]->add_card(pack.deal_one());
   players[1]->add_card(pack.deal_one());
   players[1]->add_card(pack.deal_one());

   players[2]->add_card(pack.deal_one());
   players[2]->add_card(pack.deal_one());

   players[3]->add_card(pack.deal_one());
   players[3]->add_card(pack.deal_one());
   players[3]->add_card(pack.deal_one());

   players[0]->add_card(pack.deal_one());
   players[0]->add_card(pack.deal_one());

   players[1]->add_card(pack.deal_one());
   players[1]->add_card(pack.deal_one());

   players[2]->add_card(pack.deal_one());
   players[2]->add_card(pack.deal_one());
   players[2]->add_card(pack.deal_one());

   players[3]->add_card(pack.deal_one());
   players[3]->add_card(pack.deal_one());

   players[0]->add_card(pack.deal_one());
   players[0]->add_card(pack.deal_one());
   players[0]->add_card(pack.deal_one());
}
//shift the vector to make dealer last


//const Card &upcard, Suit &order_up_suit, int teamOrderedUp
void make_trump() {
    // Are we passing in whether or not they are dealer
  
   for (int i = 0; i < players.size(); i++) { // Starts with the second player bc the first is the dealer
       if (players[i]->make_trump(upcard, false, 1, order_up_suit)) {
           cout << players[i]->get_name() << " orders up " << order_up_suit << endl << endl;
           teamOrderedUp = playerTeams[i];
           return;
       } else {
           cout << players[i]->get_name() << " passes " << endl;
       }
   }
   for (int j = 0; j < players.size(); j++) {
       if (j == players.size()-1) {
           players[j]->make_trump(upcard, true, 2, order_up_suit);
       }
       if (players[j]->make_trump(upcard, false, 2, order_up_suit)) {
           cout << players[j]->get_name() << " orders up " << order_up_suit << endl << endl;
           teamOrderedUp = playerTeams[j];
           return;
       } else {
           cout << players[j]->get_name() << " passes " << endl;
       }
   }
   //need to add something that tracks what team players are on in order to say which team ordered up for scoring
}
//vector<Player*> playersTrick
void play_trick(Suit trump) {

   Card cardPlayed;
   vector<Card> cards1;
   
   for (int i = 0; i < playersTrick.size(); i ++) {
       if (i == 0) {
           cardPlayed = playersTrick[i]->lead_card(trump);
           cout << cardPlayed << " led by " << playersTrick[i]->get_name() << endl;
           led_card = cardPlayed;
       } else {
           cardPlayed = playersTrick[i]->play_card(led_card, trump);
           cout << cardPlayed << " played by " << playersTrick[i]->get_name() << endl;
       }
       cards1.push_back(cardPlayed);
   }

   int playerHighest = 0;
  
   Card highestCard = cards1[0]; // need to change the suit to be dependent on led card i think
   for (int j= 1; j < cards1.size(); j++) {
       if (Card_less(highestCard, cards1[j], cards1[0],trump)) {
           highestCard = cards1[j];
           playerHighest = j;
       }
   }

   cout << playersTrick[playerHighest]->get_name() << " takes the trick" << endl << endl;
   if (teamsTrick[playerHighest] == 1) {
       tricksWonTeam1++;
   } else {
       tricksWonTeam2++;
   }


   vector<Player*> rotatePlayer;
   vector<int> rotateTeams;
  
    for (int i = 0; i < 4; i++){
    cout << playersTrick[i]->get_name() << ", " << teamsTrick[i] << "   ";
   }
   cout << endl;
   
   for (int k = playerHighest; k < playersTrick.size() + playerHighest; k++) {
       rotatePlayer.push_back(playersTrick[k % playersTrick.size()]);
       rotateTeams.push_back(playerTeams[k % playersTrick.size()]);
   }




   playersTrick = rotatePlayer;
   playerTeams = rotateTeams;
}




void rotateDeal() {
   vector<Player*> storePlayer = players;
   players[0] = storePlayer[1];
   players[1] = storePlayer[2];
   players[2] = storePlayer[3];
   players[3] = storePlayer[0];


   for (int i = 0; i < playerTeams.size(); i ++) {
       if (playerTeams[i] == 1) {
           playerTeams[i] = 2;
       } else {
           playerTeams[i] = 1;
       }
   }
}
};




int main(int argc, char **argv) {
   // Read command line args and check for errors
   if (   !(argc == 12)
       || (stoi(argv[3]) < 1 || stoi(argv[3]) > 100)
       || !(strcmp(argv[2], "shuffle") == 0 || strcmp(argv[2], "noshuffle") == 0)
       || !(strcmp(argv[5], "Simple") == 0 || strcmp(argv[5], "Human") == 0)
       || !(strcmp(argv[7], "Simple") == 0 || strcmp(argv[7], "Human") == 0)
       || !(strcmp(argv[9], "Simple") == 0 || strcmp(argv[9], "Human") == 0)
       || !(strcmp(argv[11], "Simple") == 0 || strcmp(argv[11], "Human") == 0)
   )
   {
   cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
       << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
       << "NAME4 TYPE4" << endl;
       return 1;
   }
  
   ifstream packFile(argv[1]);
   if (!packFile.is_open()) {
       cout << "Error opening " << argv[1] << endl;
       return 1;
   }


   Pack pack(packFile);
   Game game(pack, argv[2], stoi(argv[3]), argv[4], argv[5], argv[6],
           argv[7], argv[8], argv[9], argv[10], argv[11]);


   game.play();
}







