#ifndef DSW2D_HEAP_H
#define DSW2D_HEAP_H
#include <iostream>
#include "Clan.h"

template<class T>
class Heap{
    struct HNode{
        int Key;
        T* element;
    };

    int size;
    HNode* data;
    int capacity;



    void swapClanIndexes(Clan* c1,Clan* c2)
    {
        int id1=c1->getIndexInHeap();
        int id2=c2->getIndexInHeap();
        c1->setIndexInHeap(id2);
        c2->setIndexInHeap(id1);


    }
    void updateClanIndex(Clan* c1,int i)
    {
        c1->setIndexInHeap(i);
    }

public:
    Heap():size(0),data(NULL),capacity(0){};
    Heap(int capacity);
    int getSize(){ return size;};
    int getCapacity(){ return capacity;};
    HNode& getData(int i){
        //if(i<0 || i>size) return NULL;
        return data[i];
    };

    void make(Clan** clans,int* Ids, int n)
    {
        for(int i=0; i<n; i++)
        {
            data[i].Key=Ids[i];
            data[i].element=clans[i];
            size++;
            updateClanIndex(clans[i],i);
        }

        for(int i=n/2; i>=0; i--)
        {
            SiftDown(i);
        }
//        printHeap();
    }
    int getParent(int i){ return (i-1)/2;};
    int getLeftSon(int i){ return 2*i+1;};
    int getRightSon(int i){ return 2*i+2;};
    bool Insert(T* Data,int key);
    bool Insert(const HNode& val);
    void deleteMin();
    void delKey(const int& i);

    void delElementByData(T* val){
        Clan* c1=(Clan*)val;
        int index=c1->getIndexInHeap();
        if(index<0 || index>size){
            return;
        }
        delKey(index);
        c1->setIndexInHeap(-1);
//        printHeap();
    }

    HNode& getMin(){
        return data[0];
    };
    void decKey(const int& i,int x);
    void SiftUp(int i);
    void SiftDown(int i);
    void printHeap();
    void destroyHeap(){
//        std::cout<<"\nHEEEEUHEPPEE";

        if(size<=0)
            return;
//        for(int i=0;i<size;i++){
//         //   if(data[i].element)
//                free(&(data[i]));
//        }
        delete[] data;
    }
    ~Heap(){

    }
};
template<class T>
Heap<T>::Heap(int capacity){
    (*this).capacity=capacity*2;
    data=new HNode[capacity*2];

    size=0;
}
template<class T>
void swap(T *x, T *y)
{
    T temp = *x;
    *x = *y;
    *y = temp;
}




template<class T>
bool Heap<T>::Insert(const HNode& val){

    if(size==capacity){
        return false;
    }
    if(size>=capacity/2){
        HNode* newArr=new HNode[capacity*2];
        for(int i=0;i<size;i++){
            newArr[i]=data[i];
        }
        HNode* arrToDel=data;
        data=newArr;
        capacity=2*capacity;
        delete[] arrToDel;
    }
    data[size]=val;
    updateClanIndex((val.element),size);
    int i=size;
    size++;
    //Now lets make sure that the heap qualities are still valid
    SiftUp(i);
    return true;
}
template<class T>
bool Heap<T>::Insert(T* Data,int key){
    HNode node;
    node.element=Data;
    node.Key=key;
    return Insert(node);
}
template<class T>
void Heap<T>::decKey(const int& i,int x){
    if(i>size || i<0)
        return;
    if(getData(i).Key<x)
        return;
    data[i].Key=x;
    SiftUp(i);
}
template<class T>
void Heap<T>::SiftUp(int i){
    while(i>0 && (getData(getParent(i)).Key > getData(i).Key) )
    {
        swap(&data[i],&data[getParent(i)]);
        //swapper(data[i],data[getParent(i)]);
        swapClanIndexes((data[i].element),(data[getParent(i)].element));
        i=getParent(i);
    }
}
template<class T>
void Heap<T>::deleteMin(){
    if(size<=0)
        return;
    size--;
//    int a = data[0].Key;
//    int b = data[1].Key;
//    int c = data[2].Key;
//    int d = data[3].Key;

    updateClanIndex(data[0].element,-1);
    data[0]=data[size]; //Replacing the minimum with the last leaf
    updateClanIndex(data[0].element,0);

    SiftDown(0);
}
template<class T>
void Heap<T>::SiftDown(int i){
    int lson=getLeftSon(i);
    int rson=getRightSon(i);
    int minimum=i;
    if(rson<size && data[rson].Key<data[i].Key){
        if(data[rson].Key<data[minimum].Key)                  //the minimum must be the parent
            minimum=rson;
    }
    if(lson<size && data[lson].Key<data[i].Key){
        if(data[lson].Key<data[minimum].Key)                  //the minimum must be the parent
        minimum=lson;
    }
    if(minimum==i) {   // That means we are done;
        return;
    }
    swap(&data[i],&data[minimum]);
    swapClanIndexes((data[i].element),(data[minimum].element));
    SiftDown(minimum);
}
template<class T>
void Heap<T>::delKey(const int& i){
    decKey(i,-10000); //Now this key turns to be minimum
    deleteMin(); // Now we delete it;:)
}


template<class T>
void Heap<T>::printHeap(){
    int i=0;
    std::cout<<"Heap:";
    for(i=0;i<size;i++){
        std::cout<<" "<<getData(i).Key;
    }
    std::cout<<"\n";
}


#endif //DSW2D_HEAP_H