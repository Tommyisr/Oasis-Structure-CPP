//
// Created by Tommyisr on 5/7/2018.
//

#include "Clan.h"

    bool Clan::isPlayerExist(Player& p) {
        if ((this->Players)->isExist(p.getID()) == 1) return true;
        return false;
    }

    void Clan::addPlayer(Player& p) {
//         if (this->isPlayerExist(p) == 0) {
        (*this->Players).insertData(p,p.getCoins());

//            p.putClan(this);
            this->numOfPlayers++;
//            if(bestPlayer==-1)
//            {
//                bestPlayer=p.getID();
//                challengesOfBestPlayer=p.getNumOfChallenges();
//            }
//            else if(bestPlayer != -1 && challengesOfBestPlayer < p.getNumOfChallenges())
//            {
//                bestPlayer=p.getID();
//                challengesOfBestPlayer=p.getNumOfChallenges();
//            }
//            else if (challengesOfBestPlayer == p.getNumOfChallenges() && bestPlayer > p.getID())
//            {
//                bestPlayer=p.getID();
//                challengesOfBestPlayer=p.getNumOfChallenges();
//            }


//        }
        //else throw PlayerAlreadyExists();
    }

    AVL<Player>& Clan::getPlayers() {
//        AVL<Player>* players = this->Players;
//        return players;
        return (*this->Players);
    }

    void Clan::printKeys() {
        (*this->Players).printKeys();
    }

//    void Clan::deleteKey(int key1, int key2)
//    {
//        (*this->Players).deleteKey(key1,key2);
//    }

    int Clan::getWinner()
    {
        return Winner;
    }

void Clan::updateWinner()
{
    Winner=0;
}


void Clan::setIndexInHeap(int i){
    indexInHeap=i;}

int Clan::getIndexInHeap(){
    return indexInHeap;}

int Clan::getNumOfPlayers()
    {
        return numOfPlayers;
    }
//    void Clan::decreaseNumPlayers()
//    {
//        numOfPlayers--;
//    }

//    int Clan::getChallBestPlayer()
//    {   return challengesOfBestPlayer;
//
//    }

//    void Clan::getBestPlayer(int* PlayerID) {
//        if(numOfPlayers<=0){
//            *PlayerID=-1;
//            return;
//        }
//        // Search in AVL tree for player with maximum Challenges completed
//        // then return its ID...
//
//    }
