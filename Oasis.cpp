//
// Created by Maher San on 09/05/2018.
//

#include "Oasis.h"
#include <stdlib.h>
#include "math.h"


StatusType Oasis::Init(int n, int* clanIDs)
{
    if(n<2) return FAILURE;
//    this->HashOfClans = Hash();
//    this->HeapOfClans = Heap<Clan>(n);
//    this->Players = AVL<int>();

    Clan** clans = new Clan*[n];
    if (!HashOfClans.MakeHeap(n, clanIDs, clans)) return FAILURE;
    HeapOfClans.make(clans,clanIDs,n); // makeheap
    //    for(int i=0; i<n; i++)
//    {
//        HeapOfClans.Insert(HashOfClans.member(clanIDs[i]),clanIDs[i]);
//    }
    delete[](clans);
    return SUCCESS;

}


StatusType Oasis::addClan(int clanID){
    if(clanID<0) return INVALID_INPUT;

    if(HashOfClans.isExistH(clanID)) return FAILURE;
    HashOfClans.insert(clanID);
    HeapOfClans.Insert(HashOfClans.member(clanID),clanID);
        return SUCCESS;
}


StatusType Oasis::addPlayer( int playerID, int score, int clan) {
    if (playerID < 0 || score < 0 || clan < 0) {
        return INVALID_INPUT;
    }
    if(Players.isExist(playerID) || !HashOfClans.isExistH(clan))   return FAILURE;

    Players.insertData(playerID,playerID);
    Player player(playerID,score);
    HashOfClans.member(clan)->addPlayer(player);

    return SUCCESS;
}

StatusType Oasis::clanFight(int clan1, int clan2, int k1, int k2)
{
    if(clan1<0 || clan2<0 || k1<=0 || k2<=0) return INVALID_INPUT;
    if(!HashOfClans.isExistH(clan1)
            || !HashOfClans.isExistH(clan2)
       || HashOfClans.member(clan1)->getWinner()==0
            || HashOfClans.member(clan2)->getWinner()==0 ||
       HashOfClans.member(clan1)->getNumOfPlayers()<k1
            || HashOfClans.member(clan2)->getNumOfPlayers()<k2
       || clan1==clan2) return  FAILURE;

    if(HashOfClans.member(clan1)->getPlayers().SelectKTotal(k1) < HashOfClans.member(clan2)->getPlayers().SelectKTotal(k2) )
    {
        HashOfClans.member(clan1)->updateWinner();
        HeapOfClans.delElementByData(HashOfClans.member(clan1));

    }
    else if(HashOfClans.member(clan1)->getPlayers().SelectKTotal(k1) > HashOfClans.member(clan2)->getPlayers().SelectKTotal(k2) )
    {
        HashOfClans.member(clan2)->updateWinner();
        HeapOfClans.delElementByData(HashOfClans.member(clan2));

    }
    else if (HashOfClans.member(clan1)->getPlayers().SelectKTotal(k1) == HashOfClans.member(clan2)->getPlayers().SelectKTotal(k2))
    {
        if(clan1<clan2)
        {
            HashOfClans.member(clan2)->updateWinner();
            HeapOfClans.delElementByData(HashOfClans.member(clan2));
        }
        else
        {
            HashOfClans.member(clan1)->updateWinner();
            HeapOfClans.delElementByData(HashOfClans.member(clan1));
        }
    }
//    HeapOfClans.printHeap();
    return SUCCESS;

}

StatusType Oasis::getMinClan (int* clan)
{   if(!clan)
        return INVALID_INPUT;
        if (HeapOfClans.getSize()==0)
            return FAILURE;
    *clan = HeapOfClans.getMin().Key;
    return SUCCESS;
}


void Oasis::Quit()
{
 //   HeapOfClans.destroy();

//    HashOfClans.destroyHash();
    HeapOfClans.destroyHeap();

    return;
}



