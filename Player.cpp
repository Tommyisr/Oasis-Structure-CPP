//
// Created by Tommyisr on 5/7/2018.
//

#include "Player.h"


    int Player::getID() {
        return this->id;
    }

    int Player::getClanID() {
        return clanID;
    }

    int Player::getCoins() {
        return Coins;
    }

    int Player::getNumOfChallenges() {
        return numOfChallenges;
    }

    int Player::wonChallenge(int newCoins) {
        numOfChallenges++;
        Coins += newCoins; // this *this
        return 0;
    }

    void Player::testEditId(int id)
    {
        this->id = id;
    }



//    AVL<Player>& Player::getClan()
//{
//    return n->playersOfClan;
//}
//
    void Player::putClan(Clan* plr)
    { this->clan=plr;

    }

    Clan* Player::getClan()
    {
        return this->clan;
    }




