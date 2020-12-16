#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Node
{
    int numberOfKeys;   // licznik ile kluczy zawiera dany wierzchołek
    int maxKeys;        // maksymalna iliczba kluczy
    int* keys;          // tablica z kluczami (wartościami) przechowywanymi w danym węźle
    Node** children;     // tablica ze wskaźnikami do dzieci danego węzła
    Node* parent;       // wskaznik do rodzica węzła

public:
    Node();                                                     // domyslny konstruktor
    Node(int* k, int numberOfKeys, int maxKeys);                // konstruktor z przekazaniem tablicy kluczy
    Node(int howManyK, bool insertKeysManually, int maxK);      // konstruktor z przekazaniem liczby kluczy do wpisania recznie (bool == true)/wylosowania (bool == false)

    bool full();                                                // czy wezel jest pełen
    int getKeysNumber();                                        // zwraca liczbę kluczy w wierzchołku
    int getMaxKeysNumber();                                     // zwraca maksymalną liczbę kluczy w wierzchołku
    int getKeyValue(int pos);                                   // zwraca wartość klucza z pozycji pos
    Node* getChild(int pos);                                    // zwraca dziecko z pozycji pos
    Node* getParent();                                          // zwraca rodzica

    void setKeyValue(int pos, int x);                           // ustawia wartość x klucza na pozycji pos
    void setChild(int pos, Node *n);                            // ustawia wskaźnik do dziecka n na pozysji pos
    void setParent(Node *n);                                    // ustawia rodzica n
    void setKeysNumber(int x);                                  // ustawia licznik kluczy

};
//konstruktor domyœlny
Node::Node() {}

//konstruktor tworzący wezel na podstawie tablicy kluczy
Node::Node(int* k, int numberOfKeys, int maxKeys)
{
    if(numberOfKeys <= maxKeys)
    {
        this->numberOfKeys = numberOfKeys;
        this->maxKeys = maxKeys;
        children = new Node* [maxKeys + 1];

        keys = new int[maxKeys];
        for (int i = 0; i < maxKeys; i++)
        {
            if(i < numberOfKeys) keys[i] = k[i];
            else keys[i] = -1;
        }

        for (int i = 0; i < maxKeys + 1; i++)
        {
            children[i] = nullptr;
        }
        parent = nullptr;
    }
}

//konstruuktor tworzący węzeł z ilością kluczy przekazaną i możliwością wprowadzenia wartoœci ręcznie lub wylosowania
Node::Node(int numberOfKeys, bool insertKeysManually,  int maxKeys)
{
    if(numberOfKeys <= maxKeys)
    {
        this->maxKeys = maxKeys;
        this->numberOfKeys = numberOfKeys;
        this->keys = new int[maxKeys];
        children = new Node* [maxKeys + 1];
        this->parent = nullptr;

        srand(time(NULL));
        if (insertKeysManually)
        {
            for (int i = 0; i < maxKeys; i++)
            {
                if(i < numberOfKeys)
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
            for (int i = 0; i < maxKeys; i++)
            {
                if(i < numberOfKeys)
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

int Node::getKeysNumber()
{
    return numberOfKeys;
}

int Node::getMaxKeysNumber()
{
    return maxKeys;
}

void Node::setKeysNumber(int x)
{
    numberOfKeys = x;
}

int Node::getKeyValue(int pos)
{
    if (pos >= 0 && pos < maxKeys) return keys[pos];
}

void Node::setKeyValue(int pos, int x)
{
    if (pos >= 0 && pos < maxKeys) keys[pos] = x;
}

Node* Node::getChild(int pos)
{
    if (pos >= 0 && pos < numberOfKeys + 1) return children[pos];
    else return nullptr;
}

void Node::setChild(int pos, Node *n)
{
    if (pos >= 0 && pos < maxKeys + 1) {
        children[pos] = n;
    }
}

void Node::setParent(Node *n)
{
    parent = n;
}

Node* Node::getParent()
{
    return parent;
}

bool Node::full()
{
    if(numberOfKeys == maxKeys) return true;
    return false;
}

class BTree
{
    int minKeys;     // minimalna liczba kluczy przechowywana w jednym wezle
    int maxKeys;     // maksymalna liczba kluczy przechowywana w jednym wezle
    int maxChildren; // maksymalna liczba dzieci
    int minChildren; // minimalna liczba dzieci
    Node *root;      // korzen drzewa; MINIMUM 2 DZIECI - TO ZNACZY ZE MOZE ZAWIERAC NP TYLKO 1 KLUCZ

public:
    BTree(int M);                      // konstruktor tworzacy puste Btree gdzie: M MAKSYMALNA LICZBA DZIECI; M/2 MINIMALNA LICZBA DZIECI; M-1 MAKSYMALNA LICZBA KLUCZY

    void insertKey(int x);             // wstawia klucz x do drzewa - mozna utworzyc nowy wezel tylko w przypadku gdy obecny jest wypelniony do polowy M/2
    void deleteKey(int x);             // usuwa klucz x z drzewa
    void splitNode(Node *n);           // dzieli wierzcho³ek n na dwa wierzcho³ki
    void mergeNodes(Node *n, Node *m); // ³¹czy wierzcho³ki n i m o wspólnym rodzicu
    void inorderTraversal(Node *n);    // wypisuje wartoœci kluczy w porz¹dku rosn¹cym
    int minimum();                     // zwraca wartoœæ minimaln¹ drzewa
    int maximum();                     // zwraca wartoœæ maksymaln¹ drzewa
    Node *search(int x);               // zwraca wskaŸnik do wierzcho³ka zawieraj¹cego klucz x
    void clear();                      // usuwa wszystkie wierzcho³ki drzewa

    Node* getRoot();                   // zwraca wskaznik do roota
    int getSize(Node *n);              // zwraca rozmiar poddrzewa o korzeniu n
    int getHeight(Node *n);            // zwraca wysokoœæ poddrzewa o korzeniu n
    int getMinKeys();
    int getMaxKeys();
    int getMaxChildren();
    int getMinChildren();
    bool empty();                      // zwraca wartoœæ true dla drzewa pustego, false dla niepustego


};

BTree::BTree(int M){
    maxChildren = M;
    minChildren = M / 2;
    maxKeys = M - 1;
    minKeys = minChildren - 1;
}

bool BTree::empty(){
    if(root == nullptr)return true;
    else return false;
}

int BTree::getMaxKeys() {
    return maxKeys;
}

Node* BTree::getRoot(){
    return root;
}

//W bloku znajduje siê 2m+1 elementów indeksu – nadmiar, przepe³nienie wiec trzeba go podzieliæ :)
void BTree::splitNode(Node* n) {
    if( n->getParent() != nullptr ) {
        if( !n->getParent()->full() ) //zalozenie ze rodzic nie moze byc pelen
        {
            int medianNum = (n->getMaxKeysNumber() - 1) / 2;    //wyznaczam œrodek liczac od 0 np. dla 2 stopnia: (5 - 1) / 2 = 2;
            int* copyKeys = new int[ n->getMaxKeysNumber() ]; //tworze tablice z wartosciami od mediany w prawo ktora pomoze mi stworzyc nowy wezel
            for(int i = medianNum + 1, j = 0; i < n->getMaxKeysNumber(); i++, j++) {
                copyKeys[j] = n->getKeyValue(i);
                n->setKeyValue(i, -1); //ustawiam -1 na warosciach od mediany w prawo
            }
            Node* parent = n->getParent();
            Node* newN = new Node(copyKeys, medianNum, n->getMaxKeysNumber()); //tworze nowy wezel na podstawie utworzonej tablicy

            for(int i = medianNum + 1, j = 0; i < n->getMaxKeysNumber() + 1; i++, j++) {
                newN->setChild(j, n->getChild(i));
                if(newN->getChild(j) != nullptr) newN->getChild(j)->setParent(newN);
                n->setChild(i, nullptr);
            }

            newN->setParent( parent );
            parent->setKeysNumber( parent->getKeysNumber() + 1 );   //zwiekszam ilosc kluczy w prodzicu
            for(int i = 0; i < parent->getKeysNumber(); i++) {
                if(parent->getKeyValue(i) == -1) {  //wstawiam nowy klucz na koncu
                    parent->setKeyValue(i, n->getKeyValue(medianNum) );
                    break;
                }
                else if( n->getKeyValue(medianNum) < parent->getKeyValue(i) ) { // przesuwam klucze by wstawic nowy
                    for(int j = parent->getKeysNumber() - 1; j > i; j--) parent->setKeyValue(j, parent->getKeyValue(j - 1));
                    parent->setKeyValue(i, n->getKeyValue(medianNum) );
                    break;
                }
            }

            //szukam w tablicy dzieci wez³a n by z prawej strony wstawic tam nowo utworzony wezel
            for(int i = 0; i < parent->getKeysNumber() + 1; i++) {
                if(parent->getChild(i)->getKeyValue(0) == n->getKeyValue(0)) {
                    //przesuwam dzieci by zrobic miejsce dla nowego dziecka
                    for(int j = parent->getKeysNumber() + 1; j > i+1; j--) parent->setChild(j, parent->getChild(j-1) );
                    parent->setChild(i+1, newN); // wstawiam nowy wezel do rodzica
                }
            }

            n->setKeyValue(medianNum, -1);  //wstawiam -1 w miejsce keys[mediana]
            n->setKeysNumber(medianNum);    //zmniejszam ilosc kluczy w wezle (powstawialem tam -1)
        }
        else {
            splitNode( n->getParent() );
        }
    }
    else {
        if( n->getParent() == nullptr) { // pelen korzen
            int medianNum = (n->getMaxKeysNumber() - 1) / 2;    //wyznaczam œrodek liczac od 0 np. dla 2 stopnia: (5 - 1) / 2 = 2;
            int* copyKeys = new int[ n->getMaxKeysNumber() ]; //tworze tablice z wartosciami od mediany w prawo ktora pomoze mi stworzyc nowy wezel
            for(int i = medianNum + 1, j = 0; i < n->getMaxKeysNumber(); i++, j++) {
                copyKeys[j] = n->getKeyValue(i);
                n->setKeyValue(i, -1); //ustawiam -1 na warosciach od mediany w prawo
            }
            Node* newN = new Node(copyKeys, medianNum, n->getMaxKeysNumber()); //tworze nowy wezel na podstawie utworzonej tablicy

            for(int i = medianNum + 1, j = 0; i < n->getMaxKeysNumber() + 1; i++, j++) {
                newN->setChild(j, n->getChild(i));
                if(newN->getChild(j) != nullptr) newN->getChild(j)->setParent(newN);
                n->setChild(i, nullptr);
            }

            int* rootKeys = new int{ n->getKeyValue(medianNum) };
            Node* newRoot = new Node(rootKeys, 1, n->getMaxKeysNumber());
            root = newRoot;
            newN->setParent( root );
            n->setParent( root );
            n->setKeyValue(medianNum, -1);  //wstawiam -1 w miejsce keys[mediana]
            n->setKeysNumber(medianNum);    //zmniejszam ilosc kluczy w wezle (powstawialem tam -1)

            root->setChild(0, n);
            root->setChild(1, newN);
        }
    }
}


// dane poprawnie zapisywane, ale zle wypisywane

 // ³¹czy wierzcho³ki n i m o wspólnym rodzicu
void BTree::mergeNodes(Node *n, Node *m){
//
//    if(n->getKeysNumber() + m->getKeysNumber() < n->getMaxKeysNumber() ){           // sprawdzenie czy mozemy dodac m do n
//
//        for(int i=0; i < m->getKeysNumber(); i++){                              // kopiowanie kluczy z m do n
//            n->setKeysNumber(n->getKeysNumber() + 1);
////            cout<<n->getKeysNumber()<<endl;
//            n->setKeyValue(n->getKeysNumber() - 1, m->getKeyValue(i));
////            cout<<n->getKeyValue(2)<<endl;
//        }
//
//        for(int i=0; i < n->getKeysNumber(); i++){
//            cout<<n->getKeyValue(i)<<endl;
//        }
//
////        for(int i=0; i < m->getKeysNumber()+1; i++){                                // kopiowanie dzieci z m do n
////            n->setChild(m->getKeyValue(i), n->getChild(n->getKeysNumber()+i+1));
////        }
//
////        n->setKeysNumber(n->getKeysNumber() + m->getKeysNumber());                  // ustawienie liczby kluczy - m+n
//
//        Node* parent = n->getParent();
//
////        for(int i=0; i < parent->getKeysNumber()+1; i++){
////            if(parent->getChild(i)->getKeyValue(0) == m->getKeyValue(0)){           // znalezienie dziecka m
////                for(int j=i; j < parent->getKeysNumber()+1; j++){                   // jezeli tak to
////                    parent->setChild(j, parent->getChild(j+1));                     // usuniecie m i przesuniecie w tablicy
////                }
////            }
////        }
//
//        delete m;

//    }
}



 void BTree::insertKey(int x){
    if( empty() ) {
        int* arr = new int[maxKeys] {x};
        Node* n = new Node(arr, 1, maxKeys);
        root = n;
    }
    else {
        Node* n = root;
        bool stop = false;
        while(!stop) {
                int nextFlag = false;

                if( n->getKeyValue( n->getKeysNumber() - 1 ) < x && n->getChild( n->getKeysNumber() ) != nullptr) {
                    nextFlag = true;
                    n = n->getChild( n->getKeysNumber());
                }
                else {
                     for(int i = 0; i < n->getKeysNumber(); i++) {
                        if(x < n->getKeyValue(i) && n->getChild(i) != nullptr ){
                            nextFlag = true;
                            n = n->getChild(i);
                            break;
                        }
                    }
                }
                if( !nextFlag ) stop = true;
        }

        if( !n->full() ) { // dodanie klucza do wybranego węzła
            int index;
            for(int i = 0; i <= n->getKeysNumber(); i++) {   //znalezienie miejsca dla x w kluczach
                if(x < n->getKeyValue(i) || n->getKeyValue(i) == -1 ){
                    index = i;
                    break;
                }
            }
            if(index < n->getKeysNumber()) {    //przesuniecie kluczy
                for(int i = n->getKeysNumber(); i > 0; i--) n->setKeyValue(i, n->getKeyValue(i-1));
            }
            n->setKeyValue(index, x);
            n->setKeysNumber( n->getKeysNumber() + 1 );
        }
        else {
            splitNode(n);
            insertKey(x);
        }
    }
 }



int main()
{
    {
        BTree* tree = new BTree(4);

        tree->insertKey(5);
        tree->insertKey(2);
        tree->insertKey(10);

        for(int i = 0; i < tree->getRoot()->getMaxKeysNumber(); i++) {
            cout << tree->getRoot()->getKeyValue(i) << ", ";
        }
        tree->insertKey(1);
        tree->insertKey(6);
        tree->insertKey(11);
        tree->insertKey(9);
        tree->insertKey(3);
        tree->insertKey(4);
        tree->insertKey(7);
        tree->insertKey(8);

        cout << endl << "root: ";
        for(int i = 0; i < tree->getRoot()->getMaxKeysNumber(); i++) {
            cout << tree->getRoot()->getKeyValue(i) << ", ";
        }
        cout << endl << "left: ";
        for(int i = 0; i < tree->getRoot()->getMaxKeysNumber(); i++) {
            cout << tree->getRoot()->getChild(0)->getKeyValue(i) << ", ";
        }
        cout << endl << "mid: ";
        for(int i = 0; i < tree->getRoot()->getMaxKeysNumber(); i++) {
            cout << tree->getRoot()->getChild(1)->getKeyValue(i) << ", ";
        }
        cout << endl << "r r: ";
        for(int i = 0; i < tree->getRoot()->getMaxKeysNumber(); i++) {
            cout << tree->getRoot()->getChild(1)->getChild(1)->getKeyValue(i) << ", ";
        }
        cout << endl << "r l: ";
        for(int i = 0; i < tree->getRoot()->getMaxKeysNumber(); i++) {
            cout << tree->getRoot()->getChild(1)->getChild(0)->getKeyValue(i) << ", ";
        }
    }

//    {   //test splita
//        int tab[] {3,6};
//        Node *root = new Node( tab, 2, 3);
//
//        int tab1[] {1,2};
//        Node *child1 = new Node( tab1, 2, 5);
//        child1->setParent( root );
//        root->setChild(0, child1);
//
//        int tab2[] {4,5};
//        Node *child2 = new Node( tab2, 2, 5);
//        child2->setParent( root);
//        root->setChild(1, child2);
//
//        int tab3[] {7,8};
//        Node *child3 = new Node( tab3, 2, 5);
//        child3->setParent( root);
//        root->setChild(2, child3);
//
//        cout << "root keys: ";
//        for(int i = 0; i < root->getMaxKeysNumber(); i++ ) cout << root->getKeyValue(i) << ", ";
//        cout << endl;
//
//        for(int i = 0; i < root->getKeysNumber() + 1; i++ ) {
//            cout << "child " << i << endl;
//            Node *child = root->getChild(i);
//            for(int j = 0; j < child->getMaxKeysNumber(); j++ ) cout << child->getKeyValue(j) << ", ";
//            cout << endl;
//        }
//        cout << endl;
//
//        BTree *btree= new BTree(10, 20);
//
//        // btree->splitNode( child3 );
//        btree->mergeNodes(child1, child2);
//
//        cout << "root keys: ";
//        for(int i = 0; i < root->getMaxKeysNumber(); i++ ) cout << root->getKeyValue(i) << ", ";
//        cout << endl;
//
//        for(int i = 0; i < root->getKeysNumber() + 1; i++ ) {
//            cout << "child " << i << endl;
//            Node *child = root->getChild(i);
//            for(int j = 0; j < child->getKeysNumber(); j++ ) cout << child->getKeyValue(j) << ", ";
//            cout << endl;
//        }
//        cout << endl;
//    }

    return 0;
}

