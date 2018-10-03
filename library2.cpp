#include "Oasis.h"
//#include "Clan.h"
//#include "Player.h"
#include "library2.h"

//typedef struct Oasis* DT;
void* init(int n, int *clanIDs)
{
    if(n<0 || clanIDs==NULL)
        return  NULL;
    Oasis* os=new Oasis(n);
    void* DS=os;

    if(os->Init(n,clanIDs)==FAILURE) DS=NULL;
    return DS;
}
StatusType addPlayer(void *DS, int playerID, int score, int clan){
    if(!DS) return INVALID_INPUT;
    return ((Oasis*)DS)->addPlayer(playerID, score, clan);
}
StatusType addClan(void *DS, int clanID){
    if(!DS) return INVALID_INPUT;
    return ((Oasis*)DS)->addClan(clanID);
}
StatusType clanFight(void *DS, int clan1, int clan2, int k1, int k2){
    if(!DS || clan1<0 || clan2<0 || k1<=0 || k2<=0) return INVALID_INPUT;
    return ((Oasis*)DS)->clanFight(clan1, clan2, k1, k2);

}
StatusType getMinClan(void *DS, int *clan){
    if(!DS || !clan) return INVALID_INPUT;
    return ((Oasis*)DS)->getMinClan(clan);
}

void quit(void** DS)
{
    if(!DS || !(*DS))
        return;
    ((Oasis*)*DS)->Quit();
    delete ((Oasis*)*DS);
    (*DS) = NULL;
}