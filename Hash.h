//
// Created by Tommyisr on 6/11/2018.
//

#ifndef HW2_HASH_H
#define HW2_HASH_H
#include <iostream>
#include <stdlib.h>
#include "Clan.h"
typedef enum  {Busy, Empty}Entry;

//template <class Clan>
class Hash {


struct Node {
Clan* clan;
Entry entry;
int key;
Node* next;
};

int size;
//mod for r(x)
int secondMod;
int numberOfElements;
Node** table;


// finding a prime number to be a size of table or r(x)
int findPrime(int n, int flag)
{
if(flag==1) n--;
bool prime = false;

    while(true) {
        for (int i = 2; i <= n / 2; ++i) {
            if (n % i == 0) {
                prime = false;
                break;
            }
            prime = true;
        }
if(prime == true) break;
       else    n = stepping(n,flag);

    }



    return n;
}
int stepping(int n, int flag)
{
    if(flag == 0) n++;
    if (flag == 1) n--;
    return n;
}

int firstHashing(int id, int mod)
{
    return id % mod;
}

//int secondHashing(int id, int mod, int k)
//{
//    int pos = firstHashing(id,size) + k + k*(id % mod);
//    return pos % size;
//}


void resize()
{
    int oldSize = size;
    size = 2*size;
    size = findPrime(size,0);
    secondMod = findPrime(size,1);

    Node** newTable = (Node**)malloc(size * sizeof(Node*));

    for(int i=0; i<size; i++)

    {    newTable[i] = (Node*)malloc(sizeof(Node));
        newTable[i]->entry=Empty;
        newTable[i]->key=-1;
        newTable[i]->clan=NULL;
        newTable[i]->next=NULL;
    }
    numberOfElements=0;

    //copying
    for(int i=0; i<oldSize; i++) {
        if (table[i]->entry == Busy) {
            int pos = firstHashing(table[i]->key, size);
            if (newTable[pos]->entry == Empty) {
                newTable[pos]->entry = Busy;
                newTable[pos]->clan = table[i]->clan;
                newTable[pos]->key = table[i]->key;
                numberOfElements++;
            } else {
                Node* nxt = newTable[i]->next;

                if(nxt == NULL){
                nxt = (Node*)malloc(sizeof(Node));
                nxt->entry = Busy;
                nxt->clan = table[i]->clan;
                nxt->key = table[i]->key;
//                numberOfElements++;
                nxt->next=NULL;
                    newTable[i]->next = nxt;
                }
                else {
                    newTable[i]->next = (Node*)malloc(sizeof(Node));
                    newTable[i]->next->entry = Busy;
                    newTable[i]->next->clan = table[i]->clan;
                    newTable[i]->next->key = table[i]->key;
                    newTable[i]->next->next=nxt;

                }
            }
            Node* nxt = table[i]->next;
            while(nxt != NULL)
            {
                pos = firstHashing(nxt->key, size);
                if (newTable[pos]->entry == Empty) {
                    newTable[pos]->entry = Busy;
                    newTable[pos]->clan = nxt->clan;
                    newTable[pos]->key = nxt->key;
                    newTable[pos]->next = NULL;
                    numberOfElements++;
                } else {
                    Node* nxtnew = newTable[pos]->next;

                    if(nxtnew == NULL){
                        nxtnew = (Node*)malloc(sizeof(Node));
                        nxtnew->entry = Busy;
                        nxtnew->clan = nxt->clan;
                        nxtnew->key = nxt->key;
                        nxtnew->next=NULL;
                        newTable[pos]->next = nxtnew;
                    }
                    else {
                        newTable[pos]->next->next = (Node*)malloc(sizeof(Node));
                        newTable[pos]->next->next->entry = Busy;
                        newTable[pos]->next->next->clan = table[i]->clan;
                        newTable[pos]->next->next->key = table[i]->key;
                        newTable[pos]->next->next->next=nxtnew;

                    }
                }
                nxt = nxt->next;
            }
        }
    }
//    delete[] table;
//        free(table);
    for(int i=0; i<oldSize; i++)
    {
        Node* nxt = table[i]->next;
        while(nxt!=NULL)
        {
            Node* del = nxt;
            nxt = nxt->next;
            free(del);
        }
        free(table[i]);
    }
    free(table);
    this->table = newTable;
}

public:

    Hash():size(0),secondMod(0),numberOfElements(0),table(NULL){};

    void destroyHash(){
//        std::cout<<"HEEEEU";
        for(int i=0; i<size; i++)
        {    Node* nxt = table[i]->next;
            while(nxt!=NULL)
            {
                Node* del = nxt;
                nxt = nxt->next;
                delete (nxt->clan);
                free(del);
            }

            free(table[i]);
        }
        free(table);
    }
    ~Hash() {
//        std::cout<<"HEEEEU";
        for(int i=0; i<size; i++)
        {
            Node* nxt = table[i]->next;
            while(nxt!=NULL)
            {
                Node* del = nxt;
                nxt = nxt->next;
                delete (del->clan);
                free(del);
            }
            delete(table[i]->clan);
            free(table[i]);
        }
        free(table);
//        delete[] table;
//        for (int i=0; i<size; i++)
//        {
//            if(table[i].entry==Busy)
//            {
//                if(table[i].clan!=NULL){
//                    Clan* clan = table[i].clan;
//                delete table[i].clan;}
//            }
//        }
//        }
//        delete[] table;
    }

// creating a new table with n elements
bool MakeHeap(int n, int* IDs, Clan** clans)
    {   if(IDs == NULL) return false;
        int newsize = 3*n;
        this->size = findPrime(newsize,0);
//        this->secondMod = findPrime(newsize,1);
        table =  (Node**)malloc(size * sizeof(Node*));
        for(int i=0; i<size; i++)
        {   table[i] = (Node*)malloc(sizeof(Node));
            table[i]->entry=Empty;
            table[i]->key=-1;
            table[i]->clan=NULL;
            table[i]->next=NULL;
        }
        for(int i=0; i<n; i++)
        {
            if(IDs[i]<0) return false;
            int pos = firstHashing(IDs[i],size);
            if(table[pos]->entry==Empty)
            {
                table[pos]->entry = Busy;
                table[pos]->clan  = new Clan(IDs[i]);
                table[pos]->key = IDs[i];
                clans[i]=table[pos]->clan;
                numberOfElements++;
            }
            else {  Node* nxt = table[pos]->next;

                if(nxt == NULL){
                    nxt = (Node*)malloc(sizeof(Node));
                    nxt->entry = Busy;
                    nxt->clan = new Clan(IDs[i]);
                    clans[i]=nxt->clan;
                    nxt->key = IDs[i];
                    nxt->next=NULL;
                    table[i]->next = nxt;
                }
                else {
                    table[pos]->next = (Node*)malloc(sizeof(Node));
                    table[pos]->next->entry = Busy;
                    table[pos]->next->clan = new Clan(IDs[i]);
                    clans[i]=table[pos]->next->clan;
                    table[pos]->next->key = IDs[i];
                    table[pos]->next->next=nxt;

                }
            }
        }
            return true;

    }

void insert(int id)
{
    int pos = firstHashing(id,size);
    if(table[pos]->entry==Empty)
    {
        table[pos]->entry = Busy;
//        table[pos].clan = Clan(id);

//        free(table[pos]->clan);
        table[pos]->clan  = new Clan(id);

        table[pos]->key = id;

        numberOfElements++;
    }
    else {  Node* nxt = table[pos]->next;

        if(nxt == NULL){
            nxt = (Node*)malloc(sizeof(Node));
            nxt->entry = Busy;
            nxt->clan = new Clan(id);
            nxt->key = id;
            nxt->next=NULL;
            table[pos]->next = nxt;
        }
        else {
            table[pos]->next = (Node*)malloc(sizeof(Node));
            table[pos]->next->entry = Busy;
            table[pos]->next->clan = new Clan(id);
            table[pos]->next->key = id;
            table[pos]->next->next=nxt;

        }
    }

    if(size/2 == numberOfElements) resize();

}

Clan* member(int ID) {
    int pos = firstHashing(ID, size);
    if (table[pos]->key == ID) {
        return (table[pos]->clan);
    } else {
        Node *nxt = table[pos]->next;
        while (nxt != NULL) {
            if (nxt->key == ID) {
                return nxt->clan;
            } else nxt = nxt->next;
        }
        return table[pos]->clan; // not neccesssary
    }

}
//    if (table[pos].entry == Busy)
//    {
//        Clan clan = table[pos].clan;
//        return table[pos].clan;
//    }
//    else
//    {
//        int k=0;
//        while(table[pos].entry==Busy)
//        {
//            pos = secondHashing(ID,secondMod,k);
//            k++;
//        }
//        return table[pos].clan;
//    }
//}

    bool isExistH(int ID) {
        if(size<=0)
            return FAILURE;
        int pos = firstHashing(ID, size);
        if (table[pos]->key == ID) {
            return true;
        } else { Node* nxt = table[pos]->next;
            while(nxt != NULL)
            {
                if(nxt->key == ID)
                {
                    return true;
                }
                else nxt = nxt->next;
            }
            return false;
            }

        }
//        return  false;
//    }






};







#endif //HW2_HASH_H
