
// Created by wormi on 5/6/2018.
//
#ifndef HW1_TREEAVL_H
#define HW1_TREEAVL_H

#include <iostream>



template <class T>
class AVL {

    struct Node {
        T data;
        int key1;
        int key2;
        int balance;
        int rank;
        int sum;

        Node *left, *right, *parent;
    };

    Node *root;

    Node *rotateLeft(Node *a) {
        Node *b = a->right;
        b->parent = a->parent;
        a->right = b->left;

        if (a->right != NULL)
            a->right->parent = a;

        b->left = a;
        a->parent = b;

        if (b->parent != NULL) {
            if (b->parent->right == a) {
                b->parent->right = b;
            } else {
                b->parent->left = b;
            }

        }
        setBalance(a);
        setBalance(b);
        setRanks(a);
        setSums(a);
        return b;
    }

    Node *rotateRight(Node *a) {
        Node *b = a->left;
        b->parent = a->parent;
        a->left = b->right;

        if (a->left != NULL)
            a->left->parent = a;

        b->right = a;
        a->parent = b;

        if (b->parent != NULL) {
            if (b->parent->right == a) {
                b->parent->right = b;
            } else {
                b->parent->left = b;
            }
        }

        setBalance(a);
        setBalance(b);
        setRanks(a);
        setSums(a);
        return b;
    }

    Node *rotateLeftRight(Node *n) {
        n->left = rotateLeft(n->left);
        return rotateRight(n);
    }

    Node *rotateRightLeft(Node *n) {
        n->right = rotateRight(n->right);
        return rotateLeft(n);
    }

    void rebalance(Node *n) {
        setBalance(n);

        if (n->balance == 2) {
            if (getHeight(n->left->left) >= getHeight(n->left->right))
                n = rotateRight(n);
            else
                n = rotateLeftRight(n);
        } else if (n->balance == -2) {
            if (getHeight(n->right->right) >= getHeight(n->right->left))
                n = rotateLeft(n);
            else
                n = rotateRightLeft(n);
        }

        if (n->parent != NULL) {
            rebalance(n->parent);
        } else {
            root = n;
        }
    }
    Node* Select(int k){
        return Select(root,k);
    }
    Node* Select(Node* node,int k){
        if(!node)
            return NULL;
        int wLeft=0;
        if(node->left){
            wLeft=node->left->rank;
        }
        else{
            wLeft=0;
        }
        if(wLeft== k-1)
            return node;
        if(wLeft > k-1)
            return Select(node->left,k);
        else
            return   Select(node->right,k-1-(wLeft));
    }


    int getHeight(Node *n) {
        if (n == NULL) return -1;
        return 1 + std::max(getHeight(n->left), getHeight(n->right));
    }

    void setBalance(Node *n) {
        n->balance = getHeight(n->left) - getHeight(n->right);
    //    int rleft=0,rRight=0;
//        if(n->left)
//            rleft=n->left->rank;
//        if(n->right)
//            rRight=n->right->rank;
//        n->rank=rleft+rRight;
    }

    void printKeys(Node *n) {
        if (n != NULL) {
            printKeys(n->left);
            std::cout << n->key1 << "-" << n->sum << ". ";
            printKeys(n->right);
        }
    }




    void updateArray(int** array, int* key, int* i)
    {
        (*array)[*i]=*key;
//        array=array+1;
        (*i)++;
    }
    void updatePArray(T* array, T key, int* i)
    {
        (array)[*i]=key;
//        array=array+1;
        (*i)++;
    }
    void transferData(int** array, Node* n, int* i)
    {
//        int i=0;
        if (n != NULL)
        {

            transferData(array, n->left,i);
//            array[i]=&(n->key2);
            updateArray(array,&(n->key2),i);

//            i++;// CHECK THE POINTER OF THIS FUCKING ARRAY!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//            std::cout << i << "----" << array[i] << std::endl;
            transferData(array,n->right,i);
        }
    }
    bool updateTree(T* array,int* i,int* keys1,int* keys2,Node* n,int size){
        if(*i>=size){
            n->data=NULL;
            n->key1=-1;
            n->key2=-1;
            *i=*i+1;
            return true;
        }
        n->data=(array[*i]);
        n->key1=keys1[*i];
        n->key2=keys2[*i];
        *i=*i+1;
        return false;
    }
    void inputData(T* array,Node* n,int* i,int* keys1,int* keys2,int size){
        if(n!=NULL)
        {
            inputData(array,n->left,i,keys1,keys2,size);
            if(updateTree(array,i,keys1,keys2,n,size))
                return;
            inputData(array,n->right,i,keys1,keys2,size);
        }

    }
    void fillingTreePrv(T* array, Node* n, int* i)
    {
        if (n != NULL)
        {
            fillingTreePrv(array,n->right,i);
            n->data=array[*i];
            n->key1=array[*i];
            n->key2=array[*i];
            (*i)++;
            fillingTreePrv(array,n->left,i);
        }
    }

    void transferPlayers(T** array, Node* n)
    {   int i=0;
        if (n != NULL)
        {
            transferPlayers(array, n->left);
            *array[i]=n->data; // CHECK THE POINTER OF THIS FUCKING ARRAY!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            transferData(array+1,n->right,&i);
        }
    }
    void transferPlz(T* arr,Node* n,int* i){
        if (n != NULL)
        {

            transferPlz(arr, n->left,i);
            updatePArray(arr,(n->data),i);

//            i++;// CHECK THE POINTER OF THIS FUCKING ARRAY!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//            std::cout << i << "----" << array[i] << std::endl;
            transferPlz(arr,n->right,i);
        }
    }



//    void transferPlayers(T** array, Node* n)
//    {   int i=0;
//        if (n != NULL)
//        {
//            transferPlayers(array, n->left);
//            *array[i]=n->data; // CHECK THE POINTER OF THIS FUCKING ARRAY!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//            transferData(array+1,n->right,&i);
//        }
//    }

    void printBalance(Node *n) {
        if (n != NULL) {
            printBalance(n->left);
            std::cout << n->balance << " ";
            printBalance(n->right);
        }
    }

    Node* emptyAVL(int n, Node* parent){

        if (n <= 0)
            return NULL;
        Node *a = new Node;
        a->right = NULL;
        a->left = NULL;
//        a->data = NULL;
        a->key1 = -1;
        a->key2 = -1;
        a->parent = parent;
        a->balance=0;
        a->left = emptyAVL(n-1,a);
        a->right = emptyAVL(n-1,a);
        return a;

    }

    void killingLeavesPrv(Node* node, int* n)
    {
        if(node != NULL)
        {
            killingLeavesPrv(node->right,n);
            if(node->left == NULL && node->right == NULL) {
                if(*n==0) return;
                else {
//                node = node->parent;
                    if(node->parent->left == node) node->parent->left=NULL;
                    if(node->parent->right == node) node->parent->right=NULL;

                    Node *t = node;
                    node=node->parent;
                    delete t;
                    t = NULL;
//                    node = t;
                    (*n)--;
                }
            }
            killingLeavesPrv(node->left,n);

        }
    }


//    void assign(Node* n)
//    {
//        if(n != NULL)
//        {
//            assign(n->left);
//
//            assign(n->right);
//        }
//    }
public:
    T& getData(int key);
    Node* getRoot(){
        return root;
    }
    bool isExist(int key)
    {
        if(root == NULL) return false;
        if(root->key1==key) return true;
        Node* n = root;
        while(true) {
            bool goLeft = n->key1 > key;
            if (goLeft == 1) n = n->left;
            else n = n->right;
            if((n != NULL) && (n->key1 == key))
            {
                return true;
            }
            if (n == NULL)
                return false;
        }


    }
//    void operator=(AVL<T> tree)
//    {
//        assign(root,);
//    }


    AVL() : root(NULL) {};

    ~AVL() {
        destroyAVL(root);
    };

    AVL<T>& buildEmptyTree(int n)
    {   Node* root = new Node;
        root->parent=NULL;
        root->balance=0;
        root->key1=-1;
        root->key2=-1;
        root->left=emptyAVL(n,root);
        root->right=emptyAVL(n,root);
        this->root=root;
        return *this;
    }


    void killingLeaves(int* n)
    {
        killingLeavesPrv(root,n);
    }


    void printBalance() {
        printBalance(root);
        std::cout << std::endl;
    }

    void transferData(int** array)
    {   int i=0;

        transferData(array,root,&i);
    }
    void transferPlayers(T* array){
        int i=0;
        transferPlz(array,root,&i);
    }
    void inputData(T* array,int* keys1,int* keys2,int size) {
        int i=0;
        inputData(array,root,&i,keys1,keys2,size);
    }

        void fillingTree(T* array,int* i)
    {
        fillingTreePrv(array,root,i);
    }

    void printKeys() {
        printKeys(root);
        std::cout << std::endl;
    }

    int getHeightTest() {
        getHeight(this->root);
        return 0;
    }
    void destroyAVLWithoutRoot(){
        Node* p=root;
        destroyAVL(p);
    }
    void destroyAVL(Node *p) {
        if (p == NULL) return;
        destroyAVL(p->left);
        destroyAVL(p->right);
        //std::cout << "deleting " << p->key << std::endl;
        delete(p);
        //delete(p->data);
    }

    void destroy()
    {
//        Node* root;
        destroyAVL(root);
    }



//    void deleteKey(int delKey, int key2) {
//        if (root == NULL)
//            return;
//
//        Node *n = root;
//        Node* parent  = root;
//        Node* delNode = NULL;
//        Node* child   = root;
//
//        while (child != NULL) {
//            parent = n;
//            n = child;
//            if(n->key1 < delKey) child=n->left;
//            else if (n->key1 > delKey) child=n->right;
//            if(n->key1 == delKey && n->key2 != key2)
//            {
//                if(n->key2>key2) child = n->left;
//                else child=n->right;
//            }
//
//
//            if (delKey == n->key1 && key2 == n->key2)
//            {
//                delNode = n;
//                if(n->key1 < delKey) child=n->left;
//                else child=n->right;
//            }
//
//        }
//
//        // not sure about the next piece of code
//        if (delNode != NULL) {
//            delNode->key1 = n->key1;
//            delNode->key2 = n->key2;
//            delNode->data = n->data;
//
//            if (n->left != NULL)
//                child = n->left;
//            else child = n->right;
//
//            if (root->key1 == delKey && root->key2 == key2) {
//                root = child;
//            }
//            else {
//                if (parent->left == n) {
//                    parent->left = child;
//                }
//                else {
//                    parent->right = child;
//                }
//
//                rebalance(parent);
//            }
//        }
//        if(n){
//            if(n->data)
//                delete n;
//        }
//
//    }
//
//
//    void deleteOneKey(int key)
//    {
//        if (root == NULL)
//            return;
//
//                Node* n       = root;
//                Node* parent  = root;
//                Node* delNode = NULL;
//                Node* child   = root;
//
//        while (child != NULL) {
//            parent = n;
//            n = child;
//            child = key >= n->key1 ? n->right : n->left;
//            if (key == n->key1)
//                delNode = n;
//        }
//
//        if (delNode != NULL) {
//            delNode->key1 = n->key1;
//            delNode->key2 = n->key2;
//            delNode->data = n->data; // ?????????????????????????????????????
//
//            child = n->left != NULL ? n->left : n->right;
//
//            if (root->key1 == key) {
//                root = child;
//            }
//            else {
//                if (parent->left == n) {
//                    parent->left = child;
//                }
//                else {
//                    parent->right = child;
//                }
//
//                rebalance(parent);
//            }
//        }
//    }
//

    bool insertData(T data, int key) {
        if (root == NULL) {
            Node *a = new Node;
            {
                if (a == NULL) return false;
            }
            a->right = NULL;
            a->left = NULL;
            a->data = data;
            a->rank=1;
            a->sum=0;
            a->key1 = key;
            a->key2 = -1;
            a->parent = NULL;
            a->balance=0;
            root = a;
            setRanks(a);
            setSums(a);
            } else {
            Node *n = root;
            Node *parent;

            while (true) {
                if (n->key1 == key)
                    return false;

                parent = n;

                bool goLeft = n->key1 > key;
                if (goLeft == 1) n = n->left;
                else n = n->right;

                if (n == NULL) {
                    Node *a = new Node;
                    if (goLeft) {

                        {
                            if (a == NULL) return false;
                        }
                        a->right = NULL;
                        a->left = NULL;
                        a->data = data;
                        a->key1 = key;
                        a->key2 = -1;
                        a->rank=1;
                        a->sum=0;
                        a->parent = parent;
                        a->balance=0;
                        parent->left = a;
                       // setRanks(a);
                    } else {
                        {
                            if (a == NULL) return false;
                        }
                        a->right = NULL;
                        a->left = NULL;
                        a->data = data;
                        a->key1 = key;
                        a->rank=1;
                        a->sum=0;
                        a->key2 = -1;
                        a->parent = parent;
                        a->balance=0;
                        parent->right = a;

                    }

                    rebalance(parent);
                    setRanks(a);
                    setSums(a);
                    break;
                }
            }

        }

        return true;
    }
    int sonsSum(Node* node){ //Only for 1 key
        return node->sum - node->key1;
    }
    void setSums(Node* node){
        if(!node)
            return;
        while(node!=NULL){
            Node *rightN = node->right;
            Node *leftN = node->left;
            int sumLeft = 0, sumRight = 0;
            if (leftN) {
                sumLeft = leftN->sum;
            }
            if (rightN) {
                sumRight = rightN->sum;
            }
            node->sum = sumRight+ sumLeft + node->key1;
            node = node->parent;
        }
    }
    void setRanks(Node* node){
        if(!node)
            return;
       // Node* rightN,leftN;
        while(node!=NULL) {
            Node *rightN = node->right;
            Node *leftN = node->left;
            int rLeft = 0, rRight = 0;
            if (leftN) {
                rLeft = leftN->rank;
            }
            if (rightN) {
                rRight = rightN->rank;
            }
            node->rank = rRight + rLeft + 1;
            node = node->parent;
        }
    }

    int Rank(T val){
        return Rank(root,val);
    }
    int Rank(Node* node,T val){
        if(!node)
            return NULL;
        int r=0;
        while(node!=NULL){
            if(node->key1==val){
                //we found val;
                if(node->left){
                    r=r+(node->left->rank)+1;
                }
                else{
                    r=r+1;
                }
                return r;
            }
            if(node->left){
                if(node->left->key1 < val && node->key1 > val){
                    node=node->left;
                    continue;
                }
                else{
                    r=r+(1+(node->left->rank));
                    node=node->right;
                    continue;
                }
            }
//            else{
//                r+=1;
//                node=node->right;
//                continue;
//            }
        }
        return r;

    }

    int SelectKTotal(int k)
    {   int total = 0;
        Node* our = Select(root->rank-k+1);
        Node* run = root;
//        while(our->key1 != run->key1)
        while(true)
        {
            if(run->key1 == our->key1)
            {
                total += run->key1;
                if(our->right != NULL)
                {
                    total += our->right->sum;
                }
                return total;
            }
            else if( our->key1 < run->key1 )
            {
                total = total + run->sum - run->left->sum;
                run = run->left;
            }

            else if(our->key1 > run->key1 )
            {
                run = run->right;
            }


        }

    }


    bool insertDataTwoKeys(T data, int key1, int key2) {
        if (root == NULL) {
            Node *a = new Node;
            {
                if (a == NULL) return false;
            }
            a->right = NULL;
            a->left = NULL;
            a->data = data;
            a->key1 = key1;
            a->sum=0;
            a->key2 = key2;
            a->rank=1;
            a->parent = NULL;
            a->balance=0;
            root = a;
            setRanks(a);
            setSums(a);
        } else {
            Node *n = root;
            Node *parent;

            while (true) {
                if (n->key2 == key2)
                    return false;

                parent = n;
                bool goLeft;
//                bool goLeft = n->key1 > key;
                if(n->key1 < key1) goLeft=1;
                if(n->key1 > key1) goLeft=0;

                if(n->key1 == key1 && n->key2>key2) goLeft=1;
                if(n->key1 == key1 && n->key2<key2) goLeft=0;

                if (goLeft == 1) n = n->left;
                else n = n->right;

                if (n == NULL) {
                    if (goLeft) {
                        Node *a = new Node;
                        {
                            if (a == NULL) return false;
                        }
                        a->right = NULL;
                        a->left = NULL;
                        a->data = data;
                        a->key1 = key1;
                        a->rank=1;
                        a->sum=0;
                        a->key2 = key2;
                        a->parent = parent;
                        a->balance=0;
                        parent->left = a;
                        setRanks(a);
                        setSums(a);
                    } else {
                        Node *a = new Node;
                        {
                            if (a == NULL) return false;
                        }
                        a->right = NULL;
                        a->left = NULL;
                        a->data = data;
                        a->key1 = key1;
                        a->rank=1;
                        a->sum=0;
                        a->key2 = key2;
                        a->parent = parent;
                        a->balance=0;
                        parent->right = a;
                        setRanks(a);
                        setSums(a);
                    }
                    rebalance(parent);
                    break;
                }
            }

        }

        return true;
    }

};
//template <class T>


// using this function only after "isExist", we must be sure that element does exist in our tree
template <class T>
T& AVL<T>::getData(int key)
{
    if(root->key1==key) return (root->data);
    Node* n = root;
    while(true) {
        bool goLeft;
        goLeft= n->key1 > key;
        if (goLeft == 1) n = n->left;
        else n = n->right;
        if ((n!= NULL) && (n->key1==key))
        {
            return (n->data);
            break;
        }

    }
}


#endif //HW1_TREEAVL_H