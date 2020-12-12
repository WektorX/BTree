#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Node
{
    int howManyKeys; // licznik ile kluczy zawiera dany wierzchołek -> każdy wierzchołek może posiadać howManyKeys + 1 dzieci
    int maxKeys;     // maksymalna ilość kluczy
    int *keys;       // tablica z kluczami (wartościami) przechowywanymi w danym wierzchołku
    Node *children;  // tablica ze wskaźnikami do dzieci danego wierzchołka
    Node *parent;    // wskaźnik do rodzica wierzchołka

public:
    Node();                                      // domyślny konstruktor
    Node(int *k, int sizeK, int maxK);           // konstruktor z przekazaną tablicą kluczy
    Node(int howManyK, bool insertKeysManually, int maxK); // konstruktor z przekazaną liczbą kluczy do wpisania ręcznie (bool == true)/wylosowania (bool == false)
    int getKeysNumber();                         // zwraca liczbę kluczy w wierzchołku
    int getMaxKeysNumber();                      // zwraca maksymalną liczbę kluczy w wierzchołku
    void setKeysNumber(int x);                   // ustawia licznik kluczy
    int getKeyValue(int pos);                    // zwraca wartość klucza z pozycji pos
    void setKeyValue(int pos, int x);            // ustawia wartość x klucza na pozycji pos
    Node *getChild(int pos);                     // zwraca dziecko z pozycji pos
    void setChild(int pos, Node *n);             // ustawia wskaźnik do dziecka n na pozysji pos
    void setParent(Node *n);                     // ustawia rodzica n
    Node *getParent();                           // zwraca rodzica
    bool full();
};
//konstruktor domyślny
Node::Node() {}

//konstruktor tworzący węzeł na podstawie tablicy kluczy
Node::Node(int *k, int sizeK, int maxK)
{
    if(sizeK <= maxK)
    {
        this->howManyKeys = sizeK;
        this->maxKeys = maxK;
        this->keys = new int[maxK];
        for (int i = 0; i < maxK; i++)
        {
            if(i < sizeK) this->keys[i] = k[i];
            else this->keys[i] = -1;
        }
        this->children = new Node[maxK + 1] {};
        this->parent = nullptr;
    }

}
//konstruuktor tworzący węzeł z ilością kluczy przekazaną i możliwością wprowadzenia wartości ręcznie lub wylosowania
Node::Node(int howManyK, bool insertKeysManually,  int maxK)
{
    if(howManyK <= maxK)
    {
        this->maxKeys = maxK;
        this->howManyKeys = howManyK;
        this->keys = new int[maxK];
        this->children = new Node[maxK + 1] {};
        this->parent = nullptr;
        srand(time(NULL));
        if (insertKeysManually)
        {
            for (int i = 0; i < maxK; i++)
            {
                if(i < howManyK)
                {
                    cin >> this->keys[i];
                }
                else
                {
                    this->keys[i] = -1;
                }
            }
        }
        else
        {
            for (int i = 0; i < maxK; i++)
            {
                if(i < howManyK)
                {
                    this->keys[i] = rand() % 100 + 1;
                }
                else
                {
                    this->keys[i] = -1;
                }
            }
        }
    }
}

//zwraca ilość
int Node::getKeysNumber()
{
    return this->howManyKeys;
}

int Node::getMaxKeysNumber()
{
    return this->maxKeys;
}

//ustawia ilość kluczy węzła
void Node::setKeysNumber(int x)
{
    this->howManyKeys = x;
}

//zwaraca wartość klucza na danej pozycji
int Node::getKeyValue(int pos)
{
    if (pos >= 0 && pos < this->howManyKeys)
    {
        return this->keys[pos];
    }
    else
    {
        return -1;
    }
}

//ustawia nową wartość wskazanego przez nas klucza
void Node::setKeyValue(int pos, int x)
{
    if (pos >= 0 && pos < this->howManyKeys)
    {
        this->keys[pos] = x;
    }
}

//zwraca dziecko z podanej pozycji
Node *Node::getChild(int pos)
{
    if (pos >= 0 && pos < this->howManyKeys + 1)
    {
        return &this->children[pos];
    }
    else
    {
        return nullptr;
    }
}

//ustawia dziecko na wskazanej pozycji
void Node::setChild(int pos, Node *n)
{
    if (pos >= 0 && pos < this->howManyKeys + 1)
    {
        this->children[pos] = *n;
    }
}

//ustawia ojca dla węzła
void Node::setParent(Node *n)
{
    this->parent = n;
}

//zwraca ojca
Node *Node::getParent()
{
    return this->parent;
}

//sprawdza czy węzeł ma maksymalną ilość kluczy
bool Node::full()
{


    for(int i=0; i<this->maxKeys; i++)
    {
        if( this->keys[i] == -1)
        {
            return false;
        }
    }

    return true;
}

class BTree
{
    int minKeys; // minimalna liczba kluczy przechowywana w jednym wierzchołku
    int maxKeys; // maksymalna liczba kluczy przechowywana w jednym wierzchołku
    Node *root;  // korzeń drzewa

public:
    BTree(int min, int max);           // konstruktor tworzący puste drzewo
    bool empty();                      // zwraca wartość true dla drzewa pustego, false dla niepustego
    Node *getRoot();                   // zwraca wskaźnik do korzenia
    void inorderTraversal(Node *n);    // wypisuje wartości kluczy w porządku rosnącym
    Node *search(int x);               // zwraca wskaźnik do wierzchołka zawierającego klucz x
    void splitNode(Node *n);           // dzieli wierzchołek n na dwa wierzchołki
    void mergeNodes(Node *n, Node *m); // łączy wierzchołki n i m o wspólnym rodzicu
    void insertKey(int x);             // wstawia klucz x do drzewa
    void deleteKey(int x);             // usuwa klucz x z drzewa

    int size(Node *n);   // zwraca rozmiar poddrzewa o korzeniu n
    int height(Node *n); // zwraca wysokość poddrzewa o korzeniu n
    int minimum();       // zwraca wartość minimalną drzewa
    int maximum();       // zwraca wartość maksymalną drzewa
    void clear();        // usuwa wszystkie wierzchołki drzewa
};

BTree::BTree(int min, int max){
    this->minKeys = min;
    this->maxKeys = max;
    this->root = nullptr;
}


bool BTree::empty(){
    if(this->root == nullptr){
        return true;
    }
    else{
        return false;
    }
}

Node* BTree::getRoot(){
    return this->root;
}

//W bloku znajduje się 2m+1 elementów indeksu – nadmiar, przepełnienie wiec trzeba go podzielić :)
void BTree::splitNode(Node* n) {
    if( !n->getParent()->full() ) //założenie: rodzic węzła n nie jest pełny
    {
        int medianNum = (n->getMaxKeysNumber() - 1) / 2;    //wyznaczam środek liczac od 0 np. dla 2 stopnia: (5 - 1) / 2 = 2;

        int* copyKeys = new int[ n->getMaxKeysNumber() ]; //tworze tablice z wartosciami od mediany w prawo ktora pomoze mi stworzyc nowy wezel
        for(int i = medianNum + 1, j = 0; i < n->getMaxKeysNumber(); i++, j++) {
            copyKeys[j] = n->getKeyValue(i);
            n->setKeyValue(i, -1); //ustawiam -1 na warosciach od mediany w prawo
        }
        Node* parent = n->getParent();
        Node* newN = new Node(copyKeys, medianNum, n->getMaxKeysNumber()); //tworze nowy wezel na podstawie utworzonej tablicy
        newN->setParent( parent );

        parent->setKeysNumber( parent->getKeysNumber() + 1 );   //zwiekszam ilosc kluczy w prodzicu

        for(int i = 0; i < parent->getMaxKeysNumber(); i++) {               //dodawania wartosci keys[mediana] do rodzica w odpowiednie miejsce
            if( n->getKeyValue(medianNum) < parent->getKeyValue(i) ) {
                //przesuwam klucze by zrobic miejsce dla mediany
                for(int j = parent->getMaxKeysNumber() - 1; j > i; j--) parent->setKeyValue(j, parent->getKeyValue(j - 1));
                parent->setKeyValue(i, n->getKeyValue(medianNum) );
                break;
            }
            else if(parent->getKeyValue(i) == -1) {
                //wstawiam klucz i nowe dzeicko na ostatnia pozycje, nie trzeba przesuwac
                parent->setKeyValue(i, n->getKeyValue(medianNum) );
                break;
            }
        }

        //szukam w tablicy dzieci wezła n by z prawej strony wstawic tam nowo utworzony wezel
        for(int i = 0; i < parent->getMaxKeysNumber() + 1; i++) {
            if(parent->getChild(i)->getKeyValue(0) == n->getKeyValue(0)) {
                //przesuwam dzieci by zrobic miejsce dla nowego dziecka
                for(int j = parent->getMaxKeysNumber() + 1; j > i+1; j--) parent->setChild(j, parent->getChild(j-1) );
                parent->setChild(i+1, newN); // wstawiam nowy wezel do rodzica
            }
        }

        n->setKeyValue(medianNum, -1);  //wstawiam -1 w miejsce keys[mediana]
        n->setKeysNumber(medianNum);    //zmniejszam ilosc kluczy w wezle (powstawialem tam -1)

    }
}



int main()
{

    {   //test splita
        int tab[] {7,13};
        Node *root = new Node( tab, 2, 3);

        int tab1[] {1,2,3,4,5};
        Node *child1 = new Node( tab1, 5, 5);
        child1->setParent( root );
        root->setChild(0, child1);

        int tab2[] {8, 9, 10, 11, 12};
        Node *child2 = new Node( tab2, 5, 5);
        child2->setParent( root);
        root->setChild(1, child2);

        int tab3[] {16, 17,18,19,20};
        Node *child3 = new Node( tab3, 5, 5);
        child3->setParent( root);
        root->setChild(2, child3);

        cout << "root keys: ";
        for(int i = 0; i < root->getMaxKeysNumber(); i++ ) cout << root->getKeyValue(i) << ", ";
        cout << endl;

        for(int i = 0; i < root->getKeysNumber() + 1; i++ ) {
            cout << "child " << i << endl;
            Node *child = root->getChild(i);
            for(int j = 0; j < child->getMaxKeysNumber(); j++ ) cout << child->getKeyValue(j) << ", ";
            cout << endl;
        }
        cout << endl;

        BTree *btree= new BTree(10, 20);

        btree->splitNode( child3 );

        cout << "root keys: ";
        for(int i = 0; i < root->getMaxKeysNumber(); i++ ) cout << root->getKeyValue(i) << ", ";
        cout << endl;

        for(int i = 0; i < root->getKeysNumber() + 1; i++ ) {
            cout << "child " << i << endl;
            Node *child = root->getChild(i);
            for(int j = 0; j < child->getMaxKeysNumber(); j++ ) cout << child->getKeyValue(j) << ", ";
            cout << endl;
        }
        cout << endl;
    }

    return 0;
}
