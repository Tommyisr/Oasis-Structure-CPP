//
// Created by Maher San on 09/05/2018.
//
#include <iostream>
#include "treeAVL.h"
#include "Player.h"
#include "Clan.h"
#include "library2.h"
#include "Hash.h"
#include "Heap.h"

#ifndef MVNE_OASIS_H
#define MVNE_OASIS_H
//typedef enum{
//    ALLOCATION_ERROR,
//    INVALID_INPUT,
//    FAILURE,
//    SUCCESS
//}StatusType;

    class Oasis {
//        int bestPlayer;
//        int numOfAllPlayers;
//        AVL<Player*> Players;
        Hash HashOfClans; // data structure of all the Clans
        Heap<Clan> HeapOfClans; // winners sorted from min to max
        AVL<int> Players;

    public:
        Oasis(): HashOfClans(), HeapOfClans(), Players(){};
        Oasis(int n): HashOfClans(), HeapOfClans(n), Players() {};
//        Oasis(): HashOfClans(), Players(){};
//        Oasis(int n): HashOfClans(), Players() {};

        StatusType Init(int n, int* clanIDs);

        StatusType addClan(int clanID);

        StatusType addPlayer( int playerID, int score, int clan);

        StatusType clanFight(int clan1, int clan2, int k1, int k2);

        StatusType getMinClan (int* clan);

//        ~Oasis()= default;
    ~Oasis(){

    };

        void Quit();

    };



#endif //MVNE_OASIS_H
