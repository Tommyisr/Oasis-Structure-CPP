//
// Created by Tommyisr on 5/7/2018.
//
#ifndef HW1_PLAYER_H
#define HW1_PLAYER_H
#include <iostream>
//#include "Clan.h"

    class Player {
//        struct Noder{
        int id;
        int clanID;
        int Coins;
        int numOfChallenges;
        class Clan* clan;
//        Clan clan;
//        AVL<Player> playersOfClan;
//        };
//        Noder* n;

    public:
        Player() : id(-1), clanID(-1), Coins(0),numOfChallenges(0), clan(NULL) {};

        Player(int id, int coins) : id(id), clanID(-1), Coins(coins), numOfChallenges(0), clan(NULL) {};
//        {
//            Noder *n = new Noder;
//            n->id=id;
//            n->clanID=-1;
//            n->Coins=coins;
//            n->numOfChallenges=0;
////            n->playersOfClan = AVL<Player>();
//            this->n = n;
//        };

        ~Player(){
//            delete this->n; // WHAT THE FUCKK!!!!!!????????????????????
             // std::cout << "player deleted is " << id << std::endl;
        };

        int getID() ;

        void changeClan(Clan* newClan){
            this->clan=newClan;
        }

        int getCoins();


        int getClanID();

        int getNumOfChallenges();

        int wonChallenge(int newCoins);

         void testEditId(int id);

//        Player& operator=(const Player& X)
//        {
//            delete this->n;
////            Noder* n = new Noder;
//            this->n=X.n;
//            return (*this);
//
//
//
//        }
         Clan* getClan();
//
        void putClan(Clan* plr);



    };




#endif //HW1_PLAYER_H
