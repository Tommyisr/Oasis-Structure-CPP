//
// Created by Tommyisr on 5/7/2018.
//
#ifndef HW1_CLAN_H
#define HW1_CLAN_H
#include <iostream>
#include "treeAVL.h"
#include <stdlib.h>
#include "Player.h"
class Player;

    class Clan {

        int id;
        int numOfPlayers;
        int Winner;
        int challengesOfBestPlayer;
        int indexInHeap;

        AVL<class Player>* Players;


    public:
        Clan() : id(-1), numOfPlayers(0), Winner(1), challengesOfBestPlayer(-1), indexInHeap(0), Players(NULL) {};

        Clan(int id) {


            this->id=id;
            numOfPlayers = 0;
            Winner = 1;
            challengesOfBestPlayer= -1;
            Players = new AVL<Player>;
            indexInHeap = 0;

        }
        ~Clan() {
            delete Players;
            //Players.destroyAVLWithoutRoot();
        };

        bool isPlayerExist(Player& p);

        void addPlayer(Player& p);

        AVL<Player > &getPlayers();


        void printKeys();

//        void deleteKey(int key1, int key2);

        int getBestPlayer();

        int getID(){ return id;};

        void setIndexInHeap(int i);

        int getIndexInHeap();

        int getNumOfPlayers();

//        void substituteTree(AVL<class Players > subTree) {
//            (*Players).destroyAVLWithoutRoot();
//            //Players=subTree;
//        }

    int getWinner();
        void updateWinner();








//        void fillPlayersInArray(Player **arr) {
//            *arr = (Player *) malloc(numOfPlayers * sizeof(Player *));
////            if(numOfPlayers==0)
////                arr[0]= nullptr;
//            (*Players).transferPlayers(arr);
//        }
//
//
//        void updatePlayers(AVL<Player *> plr) {
//            *(this->Players) = plr;
//        }

        Player& getPlayerByID(int ID) {
//            if(!Players.isExist(ID))
//                return nullptr;
            return (*Players).getData(ID);
        }

        void decreaseNumPlayers();
//        void getBestPlayer(int* PlayerID);

    void destroyClan() {

        (*Players).destroyAVLWithoutRoot();
    }

    void updateNumPlayers(int n) {
        this->numOfPlayers = n;
    }

//    void updateBestPlayer(int n) {
//        this->bestPlayer = n;
//    }



    void updateNumofChal(int n) {
        this->challengesOfBestPlayer = n;
    }

    void printID()
    {
        std::cout << "clan ID is " << this->id << std::endl;
    }


};

//    bool operator<(int x, Clan clan)
//    {
//        if(x<clan.getID()) return  true;
//    }


//void  operator=(Clan& clan1,Clan& clan2)
//{
//    clan1.numOfPlayers=clan2.numOfPlayers;
//    clan1.id=clan2.id;
//    clan1.Players=clan2.Players;
//}

#endif //HW1_CLAN_H
