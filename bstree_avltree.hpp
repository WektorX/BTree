#ifndef bstree_avltree_hpp
#define bstree_avltree_hpp
#include <iostream>

class BSTNode{
    private:
        int value;
        BSTNode* left;
        BSTNode* right;
        BSTNode* parent;
    public:
        BSTNode(int v, BSTNode* l, BSTNode* r, BSTNode* p);
        int getValue();
        BSTNode* getLeft();
        BSTNode* getRight();
        BSTNode* getParent();
        void setValue(int v);
        void setLeft(BSTNode* l);
        void setRight(BSTNode* r);
        void setParent(BSTNode* p);
};

class BSTree{
    private:
        BSTNode* root;
    public:
        BSTree();                        //tworzy puste drzewo
        BSTNode* getRoot();            //zwraca wska�nik do root - metoda pomocnicza w testowaniu
        bool empty(BSTNode* p);        //zwraca prawd� gdy drzewo jest puste
        void inorder(BSTNode* p);
    //BST   
        void insert(int x);            //wstawia w�ze� z warto�ci� x
        BSTNode* search(int x);         //zwraca wska�nik do w�z�a z warto�ci� x (lub NULL je�li nie istnieje)
        BSTNode* minimum();            //zwraca wska�nik do w�z�a z minimaln� warto�ci�
        BSTNode* maximum();            //zwraca wska�nik do w�z�a z maksymaln� warto�ci�
        BSTNode* successor(BSTNode* p);    //zwraca wska�nik do nast�nika p
        BSTNode* predecessor(BSTNode* p);    //zwraca wska�nik do poprzednika p
        void del(BSTNode* p);            //usuwa w�ze� wskazywany przez p
        
        //Zadanie 7.2

		int size(BSTNode* p);                  //zwraca rozmiar drzewa
		int height(BSTNode* p);              //zwraca wysoko�� drzewa
		void clear(BSTNode* p);           //usuwa wszystkie w�z�y z drzewa
};

class avlNode{
    private:
        int bf;
        int value;
        avlNode* left;
        avlNode* right;
        avlNode* parent;
    public:
        avlNode(int v, int bf);
        int getBf();
        void setBf(int bf);
        int getValue();
        avlNode* getLeft();
        avlNode* getRight();
        avlNode* getParent();
        void setValue(int v);
        void setLeft(avlNode* l);
        void setRight(avlNode* r);
        void setParent(avlNode* p);
};

class AVLTree{
    private:
        avlNode* root;
    public:
       AVLTree();
       avlNode* getRoot();
       bool empty(avlNode* p);
       int height(avlNode* p);
       void inorder(avlNode* p);
       avlNode* search(int x);
        void RR(avlNode* a, avlNode* b);
        void LL(avlNode* a, avlNode* b);
        void RL(avlNode* a, avlNode* b, avlNode* c);
        void LR(avlNode* a, avlNode* b, avlNode* c);
        void insert(int x);
};

#endif
