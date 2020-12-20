#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

class Node
{
    int numberOfKeys; // licznik ile kluczy zawiera dany wierzchołek
    int maxKeys;      // maksymalna iliczba kluczy
    int *keys;        // tablica z kluczami (wartościami) przechowywanymi w danym węźle
    Node **children;  // tablica ze wskaźnikami do dzieci danego węzła
    Node *parent;     // wskaznik do rodzica węzła

public:
    Node();                                                // domyslny konstruktor
    Node(int *k, int numberOfKeys, int maxKeys);           // konstruktor z przekazaniem tablicy kluczy
    Node(int howManyK, bool insertKeysManually, int maxK); // konstruktor z przekazaniem liczby kluczy do wpisania recznie (bool == true)/wylosowania (bool == false)

    bool full();              // czy wezel jest pełen
    int getKeysNumber();      // zwraca liczbę kluczy w wierzchołku
    int getMaxKeysNumber();   // zwraca maksymalną liczbę kluczy w wierzchołku
    int getKeyValue(int pos); // zwraca wartość klucza z pozycji pos
    Node *getChild(int pos);  // zwraca dziecko z pozycji pos
    Node *getParent();        // zwraca rodzica

    void setKeyValue(int pos, int x); // ustawia wartość x klucza na pozycji pos
    void setChild(int pos, Node *n);  // ustawia wskaźnik do dziecka n na pozysji pos
    void setParent(Node *n);          // ustawia rodzica n
    void setKeysNumber(int x);        // ustawia licznik kluczy
    int getKeyIndex(int x);
};
//konstruktor domyœlny
Node::Node()
{
    this->numberOfKeys = 0;
    this->maxKeys = 0;
    this->keys = nullptr;
    this->children = nullptr;
    this->parent = nullptr;
}

//konstruktor tworzący wezel na podstawie tablicy kluczy
Node::Node(int *k, int numberOfKeys, int maxKeys)
{
    if (numberOfKeys <= maxKeys)
    {
        this->numberOfKeys = numberOfKeys;
        this->maxKeys = maxKeys;
        children = new Node *[maxKeys + 1];

        keys = new int[maxKeys];
        for (int i = 0; i < maxKeys; i++)
        {
            if (i < numberOfKeys)
                keys[i] = k[i];
            else
                keys[i] = -1;
        }

        for (int i = 0; i < maxKeys + 1; i++)
        {
            children[i] = nullptr;
        }
        parent = nullptr;
    }
}

//konstruuktor tworzący węzeł z ilością kluczy przekazaną i możliwością wprowadzenia wartoœci ręcznie lub wylosowania
Node::Node(int numberOfKeys, bool insertKeysManually, int maxKeys)
{
    if (numberOfKeys <= maxKeys)
    {
        this->maxKeys = maxKeys;
        this->numberOfKeys = numberOfKeys;
        this->keys = new int[maxKeys];
        children = new Node *[maxKeys + 1];
        this->parent = nullptr;

        srand(time(NULL));
        if (insertKeysManually)
        {
            for (int i = 0; i < maxKeys; i++)
            {
                if (i < numberOfKeys)
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
                if (i < numberOfKeys)
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
    if (pos >= 0 && pos < maxKeys)
        return keys[pos];
}

void Node::setKeyValue(int pos, int x)
{
    if (pos >= 0 && pos < maxKeys)
        keys[pos] = x;
}

Node *Node::getChild(int pos)
{
    if (pos >= 0 && pos < numberOfKeys + 1)
        return children[pos];
    else
        return nullptr;
}

void Node::setChild(int pos, Node *n)
{
    if (pos >= 0 && pos < maxKeys + 1)
    {
        children[pos] = n;
    }
}

void Node::setParent(Node *n)
{
    parent = n;
}

Node *Node::getParent()
{
    return parent;
}

bool Node::full()
{
    if (numberOfKeys == maxKeys)
        return true;
    return false;
}

int Node::getKeyIndex(int x)
{

    for (int i = 0; i < this->getKeysNumber(); i++)
    {
        if (x == this->getKeyValue(i))
        {
            return i;
        }
    }
    return -1;
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
    void clear(Node *n);               // usuwa wszystkie wierzcho³ki drzewa
    Node *getRoot();                   // zwraca wskaznik do roota
    int getSize(Node *n);              // zwraca rozmiar poddrzewa o korzeniu n
    int getHeight(Node *n);            // zwraca wysokosc poddrzewa o korzeniu n
    int getMinKeys();                  //zwraca dozwolona minimalna ilosc kluczy w kazdym wezle drzewa
    int getMaxKeys();                  //zwraca dozwolona maxymalna ilosc kluczy w kazdym wezle drzewa
    int getMaxChildren();              //zwraca dozwolona maxymalna ilosc dzieci w kazdym wezle drzewa
    int getMinChildren();              //zwraca dozwolona minimalna ilosc dzieci w kazdym wezle drzewa
    bool empty();                      // zwraca wartoœæ true dla drzewa pustego, false dla niepustego
};

//konstruktor
BTree::BTree(int M)
{
    maxChildren = M;
    minChildren = M / 2;
    maxKeys = M - 1;
    minKeys = minChildren - 1;
    root = nullptr;
}
//sparwdza czy drzewo jest puste
bool BTree::empty()
{
    if (root == nullptr)
        return true;
    else
        return false;
}
//zwraca dozwolona maxymalna ilosc kluczy w kazdym wezle drzewa
int BTree::getMaxKeys()
{
    return maxKeys;
}
//zwraca dozwolona minimalna ilosc kluczy w kazdym wezle drzewa
int BTree::getMinKeys()
{
    return minKeys;
}
//zwraca dozwolona maxymalna ilosc dzieci w kazdym wezle drzewa
int BTree::getMaxChildren()
{
    return maxChildren;
}
//zwraca dozwolona minimalna ilosc dzieci w kazdym wezle drzewa
int BTree::getMinChildren()
{
    return minChildren;
}
//zwraca roota
Node *BTree::getRoot()
{
    return root;
}

//W bloku znajduje sie 2m+1 elementów indeksu – nadmiar, przepelnienie wiec trzeba go podzielic :)
void BTree::splitNode(Node *n)
{
    if (n->getParent() != nullptr)
    {
        if (!n->getParent()->full()) //zalozenie ze rodzic nie moze byc pelen
        {
            int medianNum = (n->getMaxKeysNumber() - 1) / 2; //wyznaczam srodek liczac od 0 np. dla 2 stopnia: (5 - 1) / 2 = 2;
            int *copyKeys = new int[n->getMaxKeysNumber()];  //tworze tablice z wartosciami od mediany w prawo ktora pomoze mi stworzyc nowy wezel
            for (int i = medianNum + 1, j = 0; i < n->getMaxKeysNumber(); i++, j++)
            {
                copyKeys[j] = n->getKeyValue(i);
                n->setKeyValue(i, -1); //ustawiam -1 na warosciach od mediany w prawo
            }
            Node *parent = n->getParent();
            Node *newN = new Node(copyKeys, medianNum, n->getMaxKeysNumber()); //tworze nowy wezel na podstawie utworzonej tablicy

            for (int i = medianNum + 1, j = 0; i < n->getMaxKeysNumber() + 1; i++, j++)
            {
                newN->setChild(j, n->getChild(i));
                if (newN->getChild(j) != nullptr)
                    newN->getChild(j)->setParent(newN);
                n->setChild(i, nullptr);
            }

            newN->setParent(parent);
            parent->setKeysNumber(parent->getKeysNumber() + 1); //zwiekszam ilosc kluczy w prodzicu
            for (int i = 0; i < parent->getKeysNumber(); i++)
            {
                if (parent->getKeyValue(i) == -1) //wstawiam nowy klucz na koncu
                {
                    parent->setKeyValue(i, n->getKeyValue(medianNum));
                    break;
                }
                else if (n->getKeyValue(medianNum) < parent->getKeyValue(i)) // przesuwam klucze by wstawic nowy
                {
                    for (int j = parent->getKeysNumber() - 1; j > i; j--)
                        parent->setKeyValue(j, parent->getKeyValue(j - 1));
                    parent->setKeyValue(i, n->getKeyValue(medianNum));
                    break;
                }
            }

            //szukam w tablicy dzieci wez³a n by z prawej strony wstawic tam nowo utworzony wezel
            for (int i = 0; i < parent->getKeysNumber() + 1; i++)
            {
                if (parent->getChild(i)->getKeyValue(0) == n->getKeyValue(0))
                {
                    //przesuwam dzieci by zrobic miejsce dla nowego dziecka
                    for (int j = parent->getKeysNumber() + 1; j > i + 1; j--)
                        parent->setChild(j, parent->getChild(j - 1));
                    parent->setChild(i + 1, newN); // wstawiam nowy wezel do rodzica
                }
            }
            n->setKeyValue(medianNum, -1); //wstawiam -1 w miejsce keys[mediana]
            n->setKeysNumber(medianNum);   //zmniejszam ilosc kluczy w wezle (powstawialem tam -1)
        }
        else
        {
            splitNode(n->getParent());
        }
    }
    else
    {
        if (n->getParent() == nullptr) // pelen korzen
        {
            int medianNum = (n->getMaxKeysNumber() - 1) / 2; //wyznaczam œrodek liczac od 0 np. dla 2 stopnia: (5 - 1) / 2 = 2;

            int *copyKeys = new int[n->getMaxKeysNumber()]; //tworze tablice z wartosciami od mediany w prawo ktora pomoze mi stworzyc nowy wezel
            for (int i = medianNum + 1, j = 0; i < n->getMaxKeysNumber(); i++, j++)
            {
                copyKeys[j] = n->getKeyValue(i);
                n->setKeyValue(i, -1); //ustawiam -1 na warosciach od mediany w prawo
            }
            Node *newN = new Node(copyKeys, medianNum, n->getMaxKeysNumber()); //tworze nowy wezel na podstawie utworzonej tablicy

            for (int i = medianNum + 1, j = 0; i < n->getMaxKeysNumber() + 1; i++, j++)
            {
                newN->setChild(j, n->getChild(i));
                if (newN->getChild(j) != nullptr)
                    newN->getChild(j)->setParent(newN);
                n->setChild(i, nullptr);
            }

            int *rootKeys = new int[1]{n->getKeyValue(medianNum)};
            Node *newRoot = new Node(rootKeys, 1, n->getMaxKeysNumber());
            this->root = newRoot;
            newN->setParent(root);
            n->setParent(root);
            n->setKeyValue(medianNum, -1); //wstawiam -1 w miejsce keys[mediana]
            n->setKeysNumber(medianNum);   //zmniejszam ilosc kluczy w wezle (powstawialem tam -1)

            root->setChild(0, n);
            root->setChild(1, newN);
        }
    }
}

// laczy wezly o n i m o wpsolnym rodzicu
void BTree::mergeNodes(Node *n, Node *m)
{
    if (n->getKeysNumber() + m->getKeysNumber() < n->getMaxKeysNumber()) // sprawdzenie czy mozemy dodac m do n
    {
        Node *parent = n->getParent();
        if (n->getKeyValue(0) > m->getKeyValue(0)) //jeżeli węzeł n jest z prawej srony zamienimy miejscami wskaźniki aby kod był uniwersalny
        {
            Node *temp = n;
            n = m;
            m = n;
        }

        int nIndex; //index węzła n i klucza dzielącego oba węzły
        for (int i = 0; i <= parent->getKeysNumber(); i++)
        {
            if (n == n->getParent()->getChild(i))
            {
                nIndex = i;
            }
        }

        int tempIndex = n->getKeysNumber(); //index dla klucza który zostanie przeniesiony z rodzica
        n->setKeysNumber(n->getKeysNumber() + 1);
        for (int i = 0; i < m->getKeysNumber(); i++) // kopiowanie kluczy i dzieci z m do n
        {
            n->setKeysNumber(n->getKeysNumber() + 1);
            n->setKeyValue(n->getKeysNumber() - 1, m->getKeyValue(i));
            if (m->getChild(i) != nullptr)
            {
                m->getChild(i)->setParent(n);
                n->setChild(n->getKeysNumber() - 1, m->getChild(i));
            }
        }


        n->setKeyValue(tempIndex, parent->getKeyValue(nIndex)); //wstawiamy do wezla n wartosc klucza z rodzica - graniczna wartosc pomiedzy n i m
        //przesuwamy dzieci i klucze w rodzicu
        for (int i = nIndex; i < parent->getKeysNumber() - 1; i++)
        {
            parent->setKeyValue(i, parent->getKeyValue(i + 1));
            parent->setChild(i + 1, parent->getChild(i + 2));
        }
        //usuwamy krancowe dzieci i klucze gdyz sie zduplikowaly
        for (int i = parent->getKeysNumber(); i <= this->maxKeys; i++)
        {
            parent->setKeyValue(i - 1, -1);
            parent->setChild(i, nullptr);
        }
        //zmniejszamy ilosc kluczy w rodzicu
        parent->setKeysNumber(parent->getKeysNumber() - 1);
    }
}

void BTree::insertKey(int x)
{
    if (empty()) //sprawdzamy czy drzewo jest puste jesli tak tworzymy nowy wezel i ustawiamy jako root z wartoscia X
    {
        int *arr = new int[maxKeys]{x};
        Node *n = new Node(arr, 1, maxKeys);
        root = n;
    }
    else //jesli nie wstawiamy x w odpowiednie miejsce
    {
        Node *n = root;
        bool stop = false;
        while (!stop)
        {
            //wyszukujemy wezla do ktorego nalezy dodac X na podstawie wartosci kluczy i wartosci X
            bool nextFlag = false;
            if (n->getKeyValue(n->getKeysNumber() - 1) < x && n->getChild(n->getKeysNumber()) != nullptr)
            {
                nextFlag = true;
                n = n->getChild(n->getKeysNumber());
            }
            else
            {
                for (int i = 0; i < n->getKeysNumber(); i++)
                {
                    if (x < n->getKeyValue(i) && n->getChild(i) != nullptr)
                    {
                        nextFlag = true;
                        n = n->getChild(i);
                        break;
                    }
                }
            }
            if (!nextFlag)
                stop = true;
        }
        //jezeli wezel nie jest pewlen
        if (!n->full()) // dodanie klucza do wybranego węzła
        {
            int index;
            for (int i = 0; i <= n->getKeysNumber(); i++) //znalezienie miejsca dla x w kluczach
            {
                if (x < n->getKeyValue(i) || n->getKeyValue(i) == -1)
                {
                    index = i;
                    break;
                }
            }
            if (index < n->getKeysNumber()) //przesuniecie kluczy
            {
                for (int i = n->getKeysNumber(); i >= index; i--)
                    n->setKeyValue(i, n->getKeyValue(i - 1));
            }
            n->setKeyValue(index, x);
            n->setKeysNumber(n->getKeysNumber() + 1);
        }
        else //jezeli wezel jest pelen
        {
            splitNode(n); //wykonujemy operacje spli dzielimy wezel
            insertKey(x); //nastepnie na nowo dodajemy wartosc X do drzewa
        }
    }
}

void BTree::deleteKey(int x)
{
    //sprawdzam czy drzewo nie puste
    if (!this->empty())
    {
        Node *n = this->search(x); //znajduje wezel w ktorym jest klucz ktory usuwamy
        if (n != this->getRoot())  //jesli wezel nie jest rootem
        {
            if (n->getChild(0) != nullptr) //jesli wezel jest wezlem wewnetrznym
            {

                int keyIndex = n->getKeyIndex(x);               //pobieramy index klucza ktory ma zostac usuniety

                Node *leftChild = n->getChild(keyIndex);        //dziecko na lewo od klucza
                Node *rightChild = n->getChild(keyIndex + 1);   //pobieramy dziecko na prawo od klucza
                if (leftChild->getKeysNumber() > this->minKeys) //jezeli lewy syn ma wiecej kluczy niż minimum wybieramy go
                {

                    int temp = leftChild->getKeyValue(leftChild->getKeysNumber() - 1);       //pobieramy poprzednika
                    this->deleteKey(temp); //usuwamy porzednika
                    //znajdujemy ponownie wezel w ktorym jest nasz x ktory chcemy usnac
                    n = this->search(x);
                    //zastepujemy X wartosca poprzednika
                    n->setKeyValue(n->getKeyIndex(x), temp);
                }
                else if (leftChild->getKeysNumber() <= this->minKeys && rightChild->getKeysNumber() > this->minKeys)
                {
                    //jeżeli lewy syn ma mniej kluczy niż minimum wybieramy prawego syna
                    //pobieramy następnika i go usuwamy
                    int temp = rightChild->getKeyValue(0);
                    this->deleteKey(temp);
                    //ustawiamy na usuwanym elemencie wartośc następnika
                    n = this->search(x);
                    n->setKeyValue(n->getKeyIndex(x), temp);
                    //ustawiamy na miejscu usuwanego klucza wartosc następnika
                }
                else if (leftChild->getKeysNumber() <= this->minKeys && rightChild->getKeysNumber() <= this->minKeys)
                {
                    //jeżeli prawy i lewy syn mają mniej kluczy niż min
                    //wykonujemy merge na lewym i prawy synu
                    this->mergeNodes(leftChild, rightChild);
                    this->deleteKey(x);
                }
            }
            else //jeśli węzeł jest liściem
            {
                if (n->getKeysNumber() <= this->minKeys) //jeżeli węzeł jest liściem i ma minimalną ilość kluczy
                {

                    int keyIndex = n->getKeyIndex(x);
                    int nodeIndex = 0;
                    for (int i = 0; i < this->maxChildren; i++) //znajdujemy index naszego wezła w tablicy rodzica
                    {
                        if (n == n->getParent()->getChild(i))
                        {
                            nodeIndex = i;
                        }
                    }
                    //jeżeli nasz węzeł jest ostatnim synem ojca - nie ma następnika a poprzednik ma więcej niż minKey
                    if (nodeIndex == n->getParent()->getKeysNumber() && n->getParent()->getChild(nodeIndex - 1)->getKeysNumber() > this->minKeys)
                    {

                        for (int i = keyIndex; i < n->getKeysNumber() - 1; i++) //usuwamy klucz i przesuwamy wszystkie elementy w lewo
                        {
                            n->setKeyValue(i, i + 1);
                        }
                        n->setKeysNumber(n->getKeysNumber() - 1);

                        Node *leftSibling = n->getParent()->getChild(nodeIndex - 1); //pobieramy lewego brata
                        Node *parent = n->getParent();                               //pobieramy ojca
                        //zabieramy największy klucz z lewego brata
                        int borrow = leftSibling->getKeyValue(leftSibling->getKeysNumber() - 1);
                        leftSibling->setKeyValue(leftSibling->getKeysNumber() - 1, -1); // usuwamy go z lewego brata
                        leftSibling->setKeysNumber(leftSibling->getKeysNumber() - 1);
                        int temp;
                        temp = parent->getKeyValue(parent->getKeysNumber() - 1);
                        parent->setKeyValue(parent->getKeysNumber() - 1, borrow);
                        for (int i = n->getKeysNumber(); i > 0; i--) //przesuwamy wszystkie elementy w prawo o jedną pozycję
                        {
                            n->setKeyValue(i, n->getKeyValue(i));
                        }
                        n->setKeyValue(0, temp); //wstawiamy klucz pożyczony od rodzica
                        n->setKeysNumber(n->getKeysNumber() + 1);
                    }
                    //jeżeli ma następnika który posiada więcej niż minKeys
                    else if (nodeIndex < n->getParent()->getKeysNumber() && n->getParent()->getChild(nodeIndex + 1)->getKeysNumber() > this->minKeys)
                    {
                        for (int i = keyIndex; i < n->getKeysNumber(); i++) //usuwamy klucz i przesuwamy wszystkie elementy w lewo
                        {
                            if( i > n->getKeysNumber() -1){
                                n->setKeyValue(i,-1);
                            }
                            else{
                                 n->setKeyValue(i, i + 1);
                            }

                        }
                        n->setKeysNumber(n->getKeysNumber() - 1);
                        Node *rightSibling = n->getParent()->getChild(nodeIndex + 1); //pobieramy prawego brata
                        Node *parent = n->getParent();                                //pobieramy ojca
                        int borrow = rightSibling->getKeyValue(0);//pobieramy następnik
                        rightSibling->setKeysNumber(rightSibling->getKeysNumber() - 1);
                        for (int i = 0; i < rightSibling->getMaxKeysNumber(); i++) //porządkujemy klucze w tablicy i usuwamy pożyczony
                        {
                            rightSibling->setKeyValue(i, rightSibling->getKeyValue(i + 1));
                            if (i > rightSibling->getKeysNumber() - 1)
                            {
                                rightSibling->setKeyValue(i, -1);
                            }
                        }
                       // rightSibling->setKeysNumber(rightSibling->getKeysNumber() - 1);
                        int temp = parent->getKeyValue(nodeIndex);                //pobieramy klucz o indexie takim jaki ma nasz węzeł w rodzicu
                        parent->setKeyValue(nodeIndex, borrow); // ustawiamyna miejscu zabranego klucza od rodzica klucz z następnika
                        n->setKeyValue(n->getKeysNumber(), temp);
                        n->setKeysNumber(n->getKeysNumber() + 1);
                    }
                    else //przypadek gdzie nie może pożyczyć od żadnego z braci
                    {
                        Node *paren = n->getParent();
                        //usuwamy klucz i przesuwamy reszte kluczy
                        for (int i = keyIndex; i < this->maxKeys; i++)
                        {
                            if (i > n->getKeysNumber() - 1)
                            {
                                n->setKeyValue(i, -1);
                            }
                            else
                            {
                                n->setKeyValue(i, n->getKeyValue(i + 1));
                            }
                        }
                        n->setKeysNumber(n->getKeysNumber() - 1);

                        if (nodeIndex == paren->getKeysNumber()) //będziemy robić merge z bratem z lewej
                        {
                            this->mergeNodes(paren->getChild(nodeIndex - 1), n);
                        }
                        else //będziemy robić merge z bratem z prawej
                        {
                            this->mergeNodes(n, paren->getChild(nodeIndex + 1));
                        }
                    }
                }
                else // jeżeli jest liściem i ma więcej kluczy niż minimalna ilość usuwamy klucz i przesuwamy resztę kluczy
                {
                    cout<<endl<<"lisc z wieksza iloscia kjluczy :"<<x<<endl;
                    int index = n->getKeyIndex(x);              //pobieramy index klucza w węźle
                    for (int i = index; i < this->maxKeys; i++) //przesuwamy wszystkie większe klucze w lewo
                    {

                        if (i < n->getKeysNumber() - 1)
                        {
                            n->setKeyValue(i, n->getKeyValue(i + 1));
                        }
                        else
                        {
                            n->setKeyValue(i, -1);
                        }
                    }
                    n->setKeysNumber(n->getKeysNumber() - 1); //zmniejszamy ilosc kluczy

                }
            }
        }
        else if (n == this->getRoot()) //jesli klucz jest w korzeniu
        {

            int keyIndex = n->getKeyIndex(x);
            n = this->getRoot();
            if (n->getChild(0) != nullptr) //jesli korzen ma dzieci
            {
                Node *leftChild = n->getChild(keyIndex);
                while(leftChild->getChild(leftChild->getKeysNumber()) != nullptr){
                    leftChild = leftChild->getChild(leftChild->getKeysNumber());
                }
                //pobieramy wartosc klucza poprzednika
                int temp = leftChild->getKeyValue(leftChild->getKeysNumber() - 1);
                //usuwamy poprzednika
                this->deleteKey(temp);
                //znajdujemy jeszcze raz nasz element ktory chcemy usunac
                n = this->search(x);
                //ustawiamy wartosc pobrana z poprzednika na miejscu klucza ktory usuwamy
                n->setKeyValue(n->getKeyIndex(x), temp);
            }
            else //jeśli korzeń nie ma dzieci usuwamy klucz i przesuwamy resztę kluczy
            {
                for (int i = keyIndex; i < n->getKeysNumber(); i++)
                {
                    if (i < n->getKeysNumber() - 1)
                    {
                        n->setKeyValue(i, n->getKeyValue(i + 1));
                    }
                    else
                    {
                        n->setKeyValue(i, -1);
                    }
                }
                n->setKeysNumber(n->getKeysNumber() - 1);
            }
        }
        else
        {
            cout << "Nie można usunąć klucza gdzyż nie występuje w dzrewie" << endl;
        }
    }
    else
        cout << endl
             << "Nie mozna usunac klucza - puste drzewo" << endl;
}
//wyszukiwanie klucza o wartosci x
Node *BTree::search(int x)
{
    Node *n = this->getRoot();
    bool found = false;
    int i = 0;
    while (!found)
    {
        bool increment = true;
        if (x < n->getKeyValue(i)) //sprawdzamy czy wartosc x jest mniejsza od klucza na pozycji x w danym wezle
        {
            if (n->getChild(i) != nullptr)
            {
                n = n->getChild(i); //wtedy przechodzimy do wezla o indexie tym samym ktory ma klucz o wartosci wiekszej od szukanego x
                i = 0;              //ustawiamy i na 0 bo bedziemy przesuzkiwac nowy wezel od poczatku
                increment = false;  //nie zwiekszamy wartosci i
            }
            else
            {
                cout << "nie znaleziono klucza" << endl;
                return nullptr;
            }
        }
        if (x == n->getKeyValue(i)) //jesli znalezlismy odpowiedni klucz zwracamy wezel w ktorym jest on zawarty
        {
            return n;
        }
        //jezeli x wieksze od ostatiego klucza wezla oznacza to ze muslimy isc do ostatniego dziecka wezla
        if (x > n->getKeyValue(i) && i == n->getKeysNumber() - 1)
        {
            if (n->getChild(i + 1) != nullptr)
            {
                n = n->getChild(i + 1);
                i = 0;
                increment = false;
            }
            else
            {
                cout << "nie znaleziono klucza" << endl;
                return nullptr;
            }
        }
        if (increment)
        {
            i++;
        }
        if (i > this->maxKeys)
        {
            return nullptr;
        }
    }
}

//przejście przez drzewo w porządku rosnącym
void BTree::inorderTraversal(Node *n)
{
    //przechodzimy po drzewie kolejno na pczatku do dziecka o indexie i wyswietamy rekurencyjnie jego dzieci i klucze
    //następnie wyświetlamy klucz i wezla i zwiekszamy i
    for (int i = 0; i < this->maxKeys + 1; i++)
    {

        if (n->getChild(i) != nullptr)
        {
            this->inorderTraversal(n->getChild(i));
        }

        if (i != this->maxKeys && n->getKeyValue(i) != -1)
            cout << n->getKeyValue(i) << " ";
    }
}

//zwaraca najmniejsza wartosc w drzewie
int BTree::minimum()
{

    Node *n = this->getRoot();
    while (n->getChild(0) != nullptr)
    {
        n = n->getChild(0);
    }
    return n->getKeyValue(0);
}
//zwraca najwieszka weartosc w drzewie
int BTree::maximum()
{
    Node *n = this->getRoot();
    while (n->getChild(n->getKeysNumber()) != nullptr)
    {
        n = n->getChild(n->getKeysNumber());
    }
    return n->getKeyValue(n->getKeysNumber() - 1);
}
//czysci poddrzewo o korzeniu wskazanym n
void BTree::clear(Node *n)
{

    if (n->getChild(0) != nullptr)
    {
        for (int i = 0; i <= n->getKeysNumber(); i++)
        {
            this->clear(n->getChild(i));
        }
    }
    if (n == this->getRoot())
    {
        this->root = nullptr;
    }

    delete n;
}

//zwraca ilosc kluczy zawartych w drzewie
int BTree::getSize(Node *n)
{
    if (n == nullptr)
    {
        return 0;
    }

    if (n->getChild(0) != nullptr)
    {
        int sum = n->getKeysNumber();
        for (int i = 0; i <= n->getKeysNumber(); i++)
        {
            sum += this->getSize(n->getChild(i));
        }
        return sum;
    }
    else
    {
        return n->getKeysNumber();
    }
}
//zwraca wysokosc poddrzewa o korzeniu n
int BTree::getHeight(Node *n)
{
    if (n == nullptr)
    {
        return 0;
    }
    if (n->getChild(0) != nullptr)
    {
        int rozmiar = 0;
        for (int i = 0; i <= n->getKeysNumber(); i++)
        {
            if (this->getHeight(n->getChild(i)))
            {
                rozmiar = this->getHeight(n->getChild(i));
            }
        }
        return rozmiar + 1;
    }
    else
    {
        return 1;
    }
}

int main()
{
    {
        srand(time(NULL));
        BTree *tree = new BTree(4);

        ////// TESTING //////

        // metody klasy Node //
        cout << "-----------------------------------------\nTesty dla danych wprowadzanych manualnie\n-----------------------------------------\n\n";
        cout << "\t\tTesty klasy Node\n"
             << endl;
        Node *testEmptyNode = new Node();
        cout << "Domyslny konstruktor tworzacy pusty wierzcholek:" << endl;
        cout << "full(): 1 - " << testEmptyNode->full() << endl;
        cout << "getKeysNumber(): 0 - " << testEmptyNode->getKeysNumber() << endl;
        cout << "getMaxKeysNumber(): 0 - " << testEmptyNode->getMaxKeysNumber() << endl;
        delete testEmptyNode;
        cout << "\nKonstruktor tworzacy wierzcholek na podstawie tablicy kluczy [pusta tablica kluczy, maksymalna liczba kluczy = 5]:" << endl;
        int maxKeys = 5;
        int *keysArray = new int[maxKeys];
        Node *testInitializedNode = new Node(keysArray, 0, maxKeys);
        cout << "full(): 0 - " << testInitializedNode->full() << endl;
        cout << "getKeysNumber(): 0 - " << testInitializedNode->getKeysNumber() << endl;
        cout << "getMaxKeysNumber(): 5 - " << testInitializedNode->getMaxKeysNumber() << endl;
        cout << "setKeyValue(0,100): 100 - ";
        testInitializedNode->setKeyValue(0, 100);
        testInitializedNode->setKeysNumber(testInitializedNode->getKeysNumber() + 1);
        cout << testInitializedNode->getKeyValue(0) << endl;
        cout << "getKeyIndex(100): 0 - " << testInitializedNode->getKeyIndex(100) << endl;
        cout << "setKeyValue(1,200): 200 - ";
        testInitializedNode->setKeyValue(1, 200);
        testInitializedNode->setKeysNumber(testInitializedNode->getKeysNumber() + 1);
        cout << testInitializedNode->getKeyValue(1) << endl;
        cout << "setKeyValue(2,300): 300 - ";
        testInitializedNode->setKeyValue(2, 300);
        testInitializedNode->setKeysNumber(testInitializedNode->getKeysNumber() + 1);
        cout << testInitializedNode->getKeyValue(2) << endl;
        cout << "setKeyValue(3,400): 400 - ";
        testInitializedNode->setKeyValue(3, 400);
        testInitializedNode->setKeysNumber(testInitializedNode->getKeysNumber() + 1);
        cout << testInitializedNode->getKeyValue(3) << endl;
        cout << "setKeyValue(4,500): 500 - ";
        testInitializedNode->setKeyValue(4, 500);
        testInitializedNode->setKeysNumber(testInitializedNode->getKeysNumber() + 1);
        cout << testInitializedNode->getKeyValue(4) << endl;
        cout << "full(): 1 - " << testInitializedNode->full() << endl;
        cout << "Skonstruowanie nowego wierzcholka zawierajacego jeden klucz = 150, ktory bedzie dzieckiem pierwszego obiektu:" << endl;
        keysArray[0] = 150;
        Node *testInitializedNode2 = new Node(keysArray, 1, maxKeys);
        cout << "setChild(1, node2), getChild(1)->getKeyIndex(150): 0 - ";
        testInitializedNode->setChild(1, testInitializedNode2);
        cout << testInitializedNode->getChild(1)->getKeyIndex(150) << endl;
        cout << "setParent(node1), getParent()->getKeyIndex(400): 3 - ";
        testInitializedNode2->setParent(testInitializedNode);
        cout << testInitializedNode2->getParent()->getKeyIndex(400) << endl;
        delete testInitializedNode2;
        delete testInitializedNode;
        delete keysArray;
        cout << "\t\t------------------\n"
             << endl;

        cout << "\t\tTesty klasy BTree\n"
             << endl;
        cout << "Skonstruowanie nowego pustego drzewa o maxChildren = 6, minChildren = 3, maxKeys = 5, minKeys = 2" << endl;
        BTree *testTree = new BTree(6);
        cout << "empty(): 1 - " << testTree->empty() << endl;
        cout << "getSize(root): 0 - " << testTree->getSize(testTree->getRoot()) << endl;
        cout << "getHeight(root): 0 - " << testTree->getHeight(testTree->getRoot()) << endl;
        cout << "getMinKeys(): 2 - " << testTree->getMinKeys() << endl;
        cout << "getMaxKeys(): 5 - " << testTree->getMaxKeys() << endl;
        cout << "getMinChildren(): 3 - " << testTree->getMinChildren() << endl;
        cout << "getMaxChildren(): 6 - " << testTree->getMaxChildren() << endl;
        cout << "insertKey(100): 100 - ";
        testTree->insertKey(100);
        testTree->inorderTraversal(testTree->getRoot());


        cout << endl;
        cout << "empty(): 0 - " << testTree->empty() << endl;
        cout << "insertKey(50): 50 100 - ";
        testTree->insertKey(50);
        testTree->inorderTraversal(testTree->getRoot());
        cout << endl;
        cout << "insertKey(75):  50 75 100- ";
        testTree->insertKey(75);
        testTree->inorderTraversal(testTree->getRoot());
        cout << endl;
        cout << "insertKey(90): 50 75 90 100 - ";
        testTree->insertKey(90);
        testTree->inorderTraversal(testTree->getRoot());
        cout << endl;
        cout << "insertKey(250): 50 75 90 100 250 - ";
        testTree->insertKey(250);
        testTree->inorderTraversal(testTree->getRoot());
        cout << endl;
        cout << "insertKey(300): 50 75 90 100 250 300 - ";
        testTree->insertKey(300);
        testTree->inorderTraversal(testTree->getRoot());
        cout << endl;
        cout << "getSize(root): 6 - " << testTree->getSize(testTree->getRoot()) << endl;
        cout << "getHeight(root): 2 - " << testTree->getHeight(testTree->getRoot()) << endl;
        cout << "getRoot->getKeysNumber(): 1 - " << testTree->getRoot()->getKeysNumber() << endl;
        cout << "getRoot->getKeyValue(getKeyIndex(90)): 90 - " << testTree->getRoot()->getKeyValue(testTree->getRoot()->getKeyIndex(90)) << endl;
        cout << "getRoot->getKeyIndex(100): -1 - " << testTree->getRoot()->getKeyIndex(100) << endl;
        cout << "insertKey(10): 10 50 75 90 100 250 300 - ";
        testTree->insertKey(10);
        testTree->inorderTraversal(testTree->getRoot());
        cout << endl;
        cout << "insertKey(20): 10 20 50 75 90 100 250 300 - ";
        testTree->insertKey(20);
        testTree->inorderTraversal(testTree->getRoot());
        cout << endl;
        cout << "insertKey(80): 10 20 50 75 80 90 100 250 300 - ";
        testTree->insertKey(80);
        testTree->inorderTraversal(testTree->getRoot());
        cout << endl;
        cout << "insertKey(150): 10 20 50 75 80 90 100 150 250 300 - ";
        testTree->insertKey(150);
        testTree->inorderTraversal(testTree->getRoot());
        cout << endl;
        cout << "insertKey(500): 10 20 50 75 80 90 100 150 250 300 500 - ";
        testTree->insertKey(500);
        testTree->inorderTraversal(testTree->getRoot());
        cout << endl;
        cout << "insertKey(95): 10 20 50 75 80 90 95 100 150 250 300 500 - ";
        testTree->insertKey(95);
        testTree->inorderTraversal(testTree->getRoot());
        cout << endl;
        cout << "insertKey(5): 5 10 20 50 75 80 90 95 100 150 250 300 500 - ";
        testTree->insertKey(5);
        testTree->inorderTraversal(testTree->getRoot());
        cout << endl;
        cout << "insertKey(15): 5 10 15 20 50 75 80 90 95 100 150 250 300 500 - ";
        testTree->insertKey(15);
        testTree->inorderTraversal(testTree->getRoot());
        cout << endl;
        cout << "insertKey(30): 5 10 15 20 30 50 75 80 90 95 100 150 250 300 500 - ";
        testTree->insertKey(30);
        testTree->inorderTraversal(testTree->getRoot());
        cout << endl;
        cout << "insertKey(60): 5 10 15 20 30 50 60 75 80 90 95 100 150 250 300 500 - ";
        testTree->insertKey(60);
        testTree->inorderTraversal(testTree->getRoot());
        cout << endl;
        cout << "insertKey(110): 5 10 15 20 30 50 60 75 80 90 95 100 110 150 250 300 500 - ";
        testTree->insertKey(110);
        testTree->inorderTraversal(testTree->getRoot());
        cout << endl;
        cout << "insertKey(180): 5 10 15 20 30 50 60 75 80 90 95 100 110 150 180 250 300 500 - ";
        testTree->insertKey(180);
        testTree->inorderTraversal(testTree->getRoot());
        cout << endl;
        cout << "insertKey(25): 5 10 15 20 25 30 50 60 75 80 90 95 100 110 150 180 250 300 500 - ";
        testTree->insertKey(25);
        testTree->inorderTraversal(testTree->getRoot());
        cout << endl;
        cout << "insertKey(200): 5 10 15 20 25 30 50 60 75 80 90 95 100 110 150 180 200 250 300 500 - ";
        testTree->insertKey(200);
        testTree->inorderTraversal(testTree->getRoot());
        cout << endl;
        cout << "insertKey(160): 5 10 15 20 25 30 50 60 75 80 90 95 100 110 150 160 180 200 250 300 500 - ";
        testTree->insertKey(160);
        testTree->inorderTraversal(testTree->getRoot());
        cout << endl;
        cout << "insertKey(170): 5 10 15 20 25 30 50 60 75 80 90 95 100 110 150 160 170 180 200 250 300 500 - ";
        testTree->insertKey(170);
        testTree->inorderTraversal(testTree->getRoot());
        cout<<endl;
        //cout << "delete(90): 5 10 15 20 25 30 50 60 75 80 95 100 110 120 150 160 170 180 200 250 300 500 - "; testTree->deleteKey(90); testTree->inorderTraversal(testTree->getRoot()); cout << endl;
        //cout << "getSize(root): 21 - " << testTree->getSize(testTree->getRoot()) << endl;

    	cout << "insertKey(120): 5 10 15 20 25 30 50 60 75 80 90 95 100 110 120 150 160 170 180 200 250 300 500 - "; testTree->insertKey(120); testTree->inorderTraversal(testTree->getRoot()); cout << endl;
        cout << "getSize(root): 23 - " << testTree->getSize(testTree->getRoot()) << endl;
        cout << "getHeight(root): 3 - " << testTree->getHeight(testTree->getRoot()) << endl;
        cout << "getRoot->getKeysNumber(): 1 - " << testTree->getRoot()->getKeysNumber() << endl;
        cout << "getRoot->getKeyValue(getKeyIndex(90)): 90 - " << testTree->getRoot()->getKeyValue(testTree->getRoot()->getKeyIndex(90)) << endl;
        cout << "getRoot->getKeyIndex(50): -1 - " << testTree->getRoot()->getKeyIndex(50) << endl;
		cout << "minimum(): 5 - " << testTree->minimum() << endl;
		cout << "maximum(): 500 - " << testTree->maximum() << endl;
		cout << "search(90): 90 - " << testTree->search(90)->getKeyValue(testTree->search(90)->getKeyIndex(90)) << endl;
		cout << "search(10): 10 - " << testTree->search(10)->getKeyValue(testTree->search(10)->getKeyIndex(10)) << endl;
		cout << "search(100): 100 - " << testTree->search(100)->getKeyValue(testTree->search(100)->getKeyIndex(100)) << endl;
		cout << "search(300): 300 - " << testTree->search(300)->getKeyValue(testTree->search(300)->getKeyIndex(300)) << endl;
		cout << "search(1): nie znaleziono klucza - "; testTree->search(1);
		cout << "search(99): nie znaleziono klucza - "; testTree->search(99);
		cout << "search(125): nie znaleziono klucza - "; testTree->search(125);
		cout << "search(600): nie znaleziono klucza - "; testTree->search(600);
		cout << "delete(300): 5 10 15 20 25 30 50 60 75 80 90 95 100 110 120 150 160 170 180 200 250 500 - "; testTree->deleteKey(300); testTree->inorderTraversal(testTree->getRoot()); cout << endl;
		cout << "search(300): nie znaleziono klucza - "; testTree->search(300);
		cout << "delete(100): 5 10 15 20 25 30 50 60 75 80 90 95 110 120 150 160 170 180 200 250 500 - "; testTree->deleteKey(100); testTree->inorderTraversal(testTree->getRoot()); cout << endl;
		cout << "search(100): nie znaleziono klucza - "; testTree->search(100);
		cout << "delete(110): 5 10 15 20 25 30 50 60 75 80 90 95 120 150 160 170 180 200 250 500 - "; testTree->deleteKey(110); testTree->inorderTraversal(testTree->getRoot()); cout << endl;
		cout << "delete(90): 5 10 15 20 25 30 50 60 75 80 95 120 150 160 170 180 200 250 500 - "; testTree->deleteKey(90); testTree->inorderTraversal(testTree->getRoot()); cout << endl;
		cout << "getSize(root): 19 - " << testTree->getSize(testTree->getRoot()) << endl;
        cout << "getHeight(root): 3 - " << testTree->getHeight(testTree->getRoot()) << endl;


        /*for(int i=1; i<14; i++)
        {
            int random = rand()%50;
            tree->insertKey(random);
            cout<<random<<endl;
        }


        tree->inorderTraversal(tree->getRoot());

        cout << endl<< "root" << endl;
        Node *k = tree->getRoot();
        for (int i = 0; i < 3; i++)
        {
            cout << k->getKeyValue(i) << ",";
        }
        cout<<endl;


        for (int i = 0; i < 4; i++)
        {
            Node *f = tree->getRoot()->getChild(i);
            if (f != nullptr)
            {
                cout << endl
                     << "kid " << i << endl;
                for (int j = 0; j < 3; j++)
                {
                    cout << f->getKeyValue(j) << " ";
                }
            }
        }
        cout<<endl<<"minimum "<<tree->minimum();
        cout<<endl<<"maximum "<<tree->maximum();
        cout<<endl<<"size :"<<tree->getSize(tree->getRoot());
        cout<<endl<<"height :"<<tree->getHeight(tree->getRoot());
        tree->clear(tree->getRoot());
        cout<<endl<<"empty ?:"<<tree->empty();*/
        /* tree->deleteKey(15);




         //  tree->deleteKey(6);
         cout<<endl<<"root"<<endl;
         Node* k = tree->getRoot();
         for(int i=0; i<3; i++)
         {
             cout<<k->getKeyValue(i)<<",";
         }

           Node* km = k->getChild(0);

           cout<<endl<<"lewy"<<endl;
           for(int i=0; i<3; i++)
           {
               cout<<km->getKeyValue(i)<<",";
           }

           Node* kr = k->getChild(1);

           cout<<endl<<"prawy"<<endl;
           for(int i=0; i<3; i++)
           {
               cout<<kr->getKeyValue(i)<<",";
           }
         /*   cout << endl << "root: ";
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
            }*/
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
    //    }*/

    return 0;
}
