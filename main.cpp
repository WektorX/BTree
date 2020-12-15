#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Node
{
    int howManyKeys; // licznik ile kluczy zawiera dany wierzcho³ek -> ka¿dy wierzcho³ek mo¿e posiadaæ howManyKeys + 1 dzieci
    int maxKeys;     // maksymalna iloœæ kluczy
    int *keys;       // tablica z kluczami (wartoœciami) przechowywanymi w danym wierzcho³ku
    Node *children;  // tablica ze wskaŸnikami do dzieci danego wierzcho³ka
    Node *parent;    // wskaŸnik do rodzica wierzcho³ka

public:
    Node();                                      // domyœlny konstruktor
    Node(int *k, int sizeK, int maxK);           // konstruktor z przekazan¹ tablic¹ kluczy
    Node(int howManyK, bool insertKeysManually, int maxK); // konstruktor z przekazan¹ liczb¹ kluczy do wpisania rêcznie (bool == true)/wylosowania (bool == false)
    int getKeysNumber();                         // zwraca liczbê kluczy w wierzcho³ku
    int getMaxKeysNumber();                      // zwraca maksymaln¹ liczbê kluczy w wierzcho³ku
    void setKeysNumber(int x);                   // ustawia licznik kluczy
    int getKeyValue(int pos);                    // zwraca wartoœæ klucza z pozycji pos
    void setKeyValue(int pos, int x);            // ustawia wartoœæ x klucza na pozycji pos
    Node *getChild(int pos);                     // zwraca dziecko z pozycji pos
    void setChild(int pos, Node *n);             // ustawia wskaŸnik do dziecka n na pozysji pos
    void setParent(Node *n);                     // ustawia rodzica n
    Node *getParent();                           // zwraca rodzica
    bool full();
};
//konstruktor domyœlny
Node::Node() {}

//konstruktor tworz¹cy wêze³ na podstawie tablicy kluczy
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
//konstruuktor tworz¹cy wêze³ z iloœci¹ kluczy przekazan¹ i mo¿liwoœci¹ wprowadzenia wartoœci rêcznie lub wylosowania
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

//zwraca iloœæ
int Node::getKeysNumber()
{
    return this->howManyKeys;
}

int Node::getMaxKeysNumber()
{
    return this->maxKeys;
}

//ustawia iloœæ kluczy wêz³a
void Node::setKeysNumber(int x)
{
    this->howManyKeys = x;
}

//zwaraca wartoœæ klucza na danej pozycji
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

//ustawia now¹ wartoœæ wskazanego przez nas klucza
void Node::setKeyValue(int pos, int x)
{
    if (pos >= 0 && pos < this->howManyKeys)
    {
        this->keys[pos] = x;
        cout<<"dodaj"<<endl;
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

//ustawia ojca dla wêz³a
void Node::setParent(Node *n)
{
    this->parent = n;
}

//zwraca ojca
Node *Node::getParent()
{
    return this->parent;
}

//sprawdza czy wêze³ ma maksymaln¹ iloœæ kluczy
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
    int minKeys; // minimalna liczba kluczy przechowywana w jednym wierzcho³ku
    int maxKeys; // maksymalna liczba kluczy przechowywana w jednym wierzcho³ku
    Node *root;  // korzeñ drzewa

public:
    BTree(int min, int max);           // konstruktor tworz¹cy puste drzewo
    bool empty();                      // zwraca wartoœæ true dla drzewa pustego, false dla niepustego
    Node *getRoot();                   // zwraca wskaŸnik do korzenia
    void inorderTraversal(Node *n);    // wypisuje wartoœci kluczy w porz¹dku rosn¹cym
    Node *search(int x);               // zwraca wskaŸnik do wierzcho³ka zawieraj¹cego klucz x
    void splitNode(Node *n);           // dzieli wierzcho³ek n na dwa wierzcho³ki
    void mergeNodes(Node *n, Node *m); // ³¹czy wierzcho³ki n i m o wspólnym rodzicu
    void insertKey(int x);             // wstawia klucz x do drzewa
    void deleteKey(int x);             // usuwa klucz x z drzewa

    int size(Node *n);   // zwraca rozmiar poddrzewa o korzeniu n
    int height(Node *n); // zwraca wysokoœæ poddrzewa o korzeniu n
    int minimum();       // zwraca wartoœæ minimaln¹ drzewa
    int maximum();       // zwraca wartoœæ maksymaln¹ drzewa
    void clear();        // usuwa wszystkie wierzcho³ki drzewa
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

//W bloku znajduje siê 2m+1 elementów indeksu – nadmiar, przepe³nienie wiec trzeba go podzieliæ :)
void BTree::splitNode(Node* n) {
    if( !n->getParent()->full() ) //za³o¿enie: rodzic wêz³a n nie jest pe³ny
    {
        int medianNum = (n->getMaxKeysNumber() - 1) / 2;    //wyznaczam œrodek liczac od 0 np. dla 2 stopnia: (5 - 1) / 2 = 2;

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

        //szukam w tablicy dzieci wez³a n by z prawej strony wstawic tam nowo utworzony wezel
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


// dane poprawnie zapisywane, ale zle wypisywane

 // ³¹czy wierzcho³ki n i m o wspólnym rodzicu
void BTree::mergeNodes(Node *n, Node *m){

    if(n->getKeysNumber() + m->getKeysNumber() < n->getMaxKeysNumber() ){           // sprawdzenie czy mozemy dodac m do n

        for(int i=0; i < m->getKeysNumber(); i++){                              // kopiowanie kluczy z m do n
            n->setKeysNumber(n->getKeysNumber() + 1);
//            cout<<n->getKeysNumber()<<endl;
            n->setKeyValue(n->getKeysNumber() - 1, m->getKeyValue(i));
//            cout<<n->getKeyValue(2)<<endl;
        }

        for(int i=0; i < n->getKeysNumber(); i++){
            cout<<n->getKeyValue(i)<<endl;
        }

//        for(int i=0; i < m->getKeysNumber()+1; i++){                                // kopiowanie dzieci z m do n
//            n->setChild(m->getKeyValue(i), n->getChild(n->getKeysNumber()+i+1));
//        }

//        n->setKeysNumber(n->getKeysNumber() + m->getKeysNumber());                  // ustawienie liczby kluczy - m+n

        Node* parent = n->getParent();

//        for(int i=0; i < parent->getKeysNumber()+1; i++){
//            if(parent->getChild(i)->getKeyValue(0) == m->getKeyValue(0)){           // znalezienie dziecka m
//                for(int j=i; j < parent->getKeysNumber()+1; j++){                   // jezeli tak to
//                    parent->setChild(j, parent->getChild(j+1));                     // usuniecie m i przesuniecie w tablicy
//                }
//            }
//        }

        delete m;

    }
}


// // wstawia klucz x do drzewa
// void BTree::insertKey(int x){
//     if(root == NULL){
//         root = new Node(this->getKeysNumber(), false, this->getMaxKeysNumber());
//         root->keys[0] = x;
//         root->howManyKeys = 1;
//     }

//     else{
//         if(root->howManyKeys == 2*minKeys-1){
//             Node *n = new Node(this->getKeysNumber(), false, this->getMaxKeysNumber());
//             n->children[0] = root;
//             n->splitNode(n);
//             int i = 0;
//             if(n->keys[0] < k)
//                 i++
//             n->children[i]->

//         }
//     }
// }



int main()
{

    {   //test splita
        int tab[] {3,6};
        Node *root = new Node( tab, 2, 3);

        int tab1[] {1,2};
        Node *child1 = new Node( tab1, 2, 5);
        child1->setParent( root );
        root->setChild(0, child1);

        int tab2[] {4,5};
        Node *child2 = new Node( tab2, 2, 5);
        child2->setParent( root);
        root->setChild(1, child2);

        int tab3[] {7,8};
        Node *child3 = new Node( tab3, 2, 5);
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

        // btree->splitNode( child3 );
        btree->mergeNodes(child1, child2);

        cout << "root keys: ";
        for(int i = 0; i < root->getMaxKeysNumber(); i++ ) cout << root->getKeyValue(i) << ", ";
        cout << endl;

        for(int i = 0; i < root->getKeysNumber() + 1; i++ ) {
            cout << "child " << i << endl;
            Node *child = root->getChild(i);
            for(int j = 0; j < child->getKeysNumber(); j++ ) cout << child->getKeyValue(j) << ", ";
            cout << endl;
        }
        cout << endl;
    }

    return 0;
}

