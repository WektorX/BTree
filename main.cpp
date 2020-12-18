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
Node::Node() {}

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
    BTree(int M); // konstruktor tworzacy puste Btree gdzie: M MAKSYMALNA LICZBA DZIECI; M/2 MINIMALNA LICZBA DZIECI; M-1 MAKSYMALNA LICZBA KLUCZY

    void insertKey(int x);             // wstawia klucz x do drzewa - mozna utworzyc nowy wezel tylko w przypadku gdy obecny jest wypelniony do polowy M/2
    void deleteKey(int x);             // usuwa klucz x z drzewa
    void splitNode(Node *n);           // dzieli wierzcho³ek n na dwa wierzcho³ki
    void mergeNodes(Node *n, Node *m); // ³¹czy wierzcho³ki n i m o wspólnym rodzicu
    void inorderTraversal(Node *n);    // wypisuje wartoœci kluczy w porz¹dku rosn¹cym
    int minimum();                     // zwraca wartoœæ minimaln¹ drzewa
    int maximum();                     // zwraca wartoœæ maksymaln¹ drzewa
    Node *search(int x);               // zwraca wskaŸnik do wierzcho³ka zawieraj¹cego klucz x
    void clear();                      // usuwa wszystkie wierzcho³ki drzewa

    Node *getRoot();        // zwraca wskaznik do roota
    int getSize(Node *n);   // zwraca rozmiar poddrzewa o korzeniu n
    int getHeight(Node *n); // zwraca wysokoœæ poddrzewa o korzeniu n
    int getMinKeys();
    int getMaxKeys();
    int getMaxChildren();
    int getMinChildren();
    bool empty(); // zwraca wartoœæ true dla drzewa pustego, false dla niepustego
};

BTree::BTree(int M)
{
    maxChildren = M;
    minChildren = M / 2;
    maxKeys = M - 1;
    minKeys = minChildren - 1;
}

bool BTree::empty()
{
    if (root == nullptr)
        return true;
    else
        return false;
}

int BTree::getMaxKeys()
{
    return maxKeys;
}

Node *BTree::getRoot()
{
    return root;
}

//W bloku znajduje siê 2m+1 elementów indeksu – nadmiar, przepe³nienie wiec trzeba go podzieliæ :)
void BTree::splitNode(Node *n)
{
    if (n->getParent() != nullptr)
    {
        if (!n->getParent()->full()) //zalozenie ze rodzic nie moze byc pelen
        {
            int medianNum = (n->getMaxKeysNumber() - 1) / 2; //wyznaczam œrodek liczac od 0 np. dla 2 stopnia: (5 - 1) / 2 = 2;
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

// dane poprawnie zapisywane, ale zle wypisywane

// ³¹czy wierzcho³ki n i m o wspólnym rodzicu
void BTree::mergeNodes(Node *n, Node *m)
{
    //

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

        /* for(int i=0; i < m->getKeysNumber()+1; i++)                                 // kopiowanie dzieci z m do n
         {
             n->setChild(m->getKeyValue(i), n->getChild(n->getKeysNumber()+i+1));
         }

         n->setKeysNumber(n->getKeysNumber() + m->getKeysNumber());       */
        // ustawienie liczby kluczy - m+n

        n->setKeyValue(tempIndex, parent->getKeyValue(nIndex));

        for (int i = nIndex; i < parent->getKeysNumber() - 1; i++)
        {
            parent->setKeyValue(i, parent->getKeyValue(i + 1));
            parent->setChild(i + 1, parent->getChild(i + 2));

            /*if(parent->getChild(i)->getKeyValue(0) == m->getKeyValue(0))            // znalezienie dziecka m
            {
                for(int j=i; j < parent->getKeysNumber()+1; j++)                    // jezeli tak to
                {
                    parent->setChild(j, parent->getChild(j+1));                     // usuniecie m i przesuniecie w tablicy
                }
            }*/
        }

        for (int i = parent->getKeysNumber(); i <= this->maxKeys ; i++)
        {
            parent->setKeyValue(i - 1, -1);
            parent->setChild(i, nullptr);

        }
        parent->setKeysNumber(parent->getKeysNumber() - 1);

        // delete m;
    }
}

void BTree::insertKey(int x)
{
    if (empty())
    {
        int *arr = new int[maxKeys]{x};
        Node *n = new Node(arr, 1, maxKeys);
        root = n;
    }
    else
    {
        Node *n = root;
        bool stop = false;
        while (!stop)
        {
            int nextFlag = false;

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
                for (int i = n->getKeysNumber(); i > 0; i--)
                    n->setKeyValue(i, n->getKeyValue(i - 1));
            }
            n->setKeyValue(index, x);
            n->setKeysNumber(n->getKeysNumber() + 1);
        }
        else
        {
            splitNode(n);
            insertKey(x);
        }
    }
}

void BTree::deleteKey(int x)
{
    //sprawdzam czy drzewo nie puste
    if (!this->empty())
    {

        Node *n = this->search(x); //znajduję węzełw którym jest klucz
        if (n != this->getRoot())  //jeśli nie jest rootem
        {
            if (n->getChild(0) != nullptr) //jeśeli węzeł nie jest liście
                {


                int keyIndex = n->getKeyIndex(x);       //pobieramy index klucza który ma zostać usunięty
                Node* leftChild= n->getChild(keyIndex) ;    //dziecko na lewo od klucza
                Node* rightChild= n->getChild(keyIndex + 1) ;    //pobieramy dziecko na prawo od klucza
                if(leftChild->getKeysNumber() > this->minKeys ){    //jeżeli lewy syn ma więcej kluczy niż minimum wybieramy go
                   int temp = leftChild->getKeyValue(leftChild->getKeysNumber()-1); //pobieramy poprzednika
                    this->deleteKey(leftChild->getKeyValue(leftChild->getKeysNumber()-1));  //usuwamy porzednika
                    n = this->search(x);
                    //ustawiamy nasz usuwany element na wartość poprzednika
                    n->setKeyValue(n->getKeyIndex(x),temp);


                 //  n->setKeyValue(keyIndex, leftChild->getKeyValue(leftChild->getKeysNumber()-1)); //pobieramy poprzednika i ustawiamy go w miejsce usuwanego kluczas
                  // leftChild->setKeyValue(leftChild->getKeysNumber()-1, leftChild->getKeyValue(leftChild->getKeysNumber()-1)-1);
                   //w lewym synu ustawiamy wartość ostatnią na o 1 mniejszą a następnie ją usuwamy


                }
                else if(leftChild->getKeysNumber() <= this->minKeys  && rightChild->getKeysNumber() > this->minKeys ){
                    //jeżeli lewy syn ma mniej kluczy niż minimum wybieramy prawego syna
                    //pobieramy następnika i go usuwamy
                    int temp = rightChild->getKeyValue(0);
                    this->deleteKey(temp);
                    //ustawiamy na usuwanym elemencie wartośc następnika
                    n = this->search(x);
                    n->setKeyValue(n->getKeyIndex(x),temp);
                    //ustawiamy na miejscu usuwanego klucza następnika
                    //n->setKeyValue(keyIndex, rightChild->getKeyValue(0));
                    //zmniejszamy wartość pierwszego klucza w prawym synu o 1 i usuwamgy go
                   // rightChild->setKeyValue(0, rightChild->getKeyValue(0)-1);
                    //this->deleteKey(rightChild->getKeyValue(0));



                }
                else if(leftChild->getKeysNumber() <= this->minKeys && rightChild->getKeysNumber() <= this->minKeys){
                    //jeżeli prawy i lewy syn mają mniej kluczy niż min
                    //wykonujemy merge na lewym i prawy synu
                    this->mergeNodes(leftChild,rightChild);
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
                        for (int i = keyIndex; i < n->getKeysNumber() - 1; i++) //usuwamy klucz i przesuwamy wszystkie elementy w lewo
                        {
                            n->setKeyValue(i, i + 1);
                        }

                        n->setKeysNumber(n->getKeysNumber() - 1);

                        Node *rightSibling = n->getParent()->getChild(nodeIndex + 1); //pobieramy prawego brata

                        Node *parent = n->getParent();             //pobieramy ojca
                        int borrow = rightSibling->getKeyValue(0); //pobieramy następnik
                        rightSibling->setKeysNumber(rightSibling->getKeysNumber() - 1);
                        for (int i = 0; i < rightSibling->getMaxKeysNumber(); i++) //porządkujemy klucze w tablicy i usuwamy pożyczony
                        {
                            rightSibling->setKeyValue(i, rightSibling->getKeyValue(i + 1));
                            if (i > rightSibling->getKeysNumber() - 1)
                            {
                                rightSibling->setKeyValue(i, -1);
                            }
                        }
                        rightSibling->setKeysNumber(rightSibling->getKeysNumber() - 1);

                        int temp = parent->getKeyValue(nodeIndex); //pobieramy klucz o indexie takim jaki ma nasz węzeł w rodzicu

                        for (int i = nodeIndex; i < parent->getKeysNumber(); i++) //porządkujemy klucze
                        {
                            if (i < parent->getKeysNumber() - 1)
                            {
                                parent->setKeyValue(i, parent->getKeyValue(i + 1));
                            }
                            else
                            {
                                parent->setKeyValue(i, -1);
                            }
                        }
                        parent->setKeyValue(parent->getKeysNumber() - 1, borrow); // ustawiamy jako ostatni klucz ten pożyczony od prawego brata
                        n->setKeyValue(n->getKeysNumber(), temp);
                        n->setKeysNumber(n->getKeysNumber() + 1);
                    }
                    else //przypadek gdzie nie może pożyczyć od żadnego z braci
                    {
                        Node *paren = n->getParent();
                        if (nodeIndex == paren->getKeysNumber()) //będziemy robić merge z bratem z lewej
                        {
                        }
                        else //będziemy robić merge z bratem z prawej
                        {

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
                            this->mergeNodes(n, paren->getChild(nodeIndex + 1));
                        }
                    }
                }
                else // jeżeli jest liściem i ma więcej kluczy niż minimalna ilość usuwamy klucz i przesuwamy resztę kluczy
                {
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
                    n->setKeysNumber(n->getKeysNumber() - 1); //zmniejszamy ilość kluczy
                }
            }
        }
        else if (n == this->getRoot()) //jeśli klucz jest w korzeniu
        {

            int keyIndex = n->getKeyIndex(x);

            if (n->getChild(0) != nullptr) //jeśli korzeń ma dzieci
            {
                Node *leftChild = n->getChild(keyIndex);
                int temp = leftChild->getKeyValue(leftChild->getKeysNumber()-1);
                this->deleteKey(temp);
                n = this->search(x);
                n->setKeyValue(n->getKeyIndex(x),temp);
               // n->setKeyValue(keyIndex, leftChild->getKeyValue(leftChild->getKeysNumber() - 1)); //ustawiamy na usuwanym kluczy poprzednia
                                                                                                  //wartość największego klucza zawartego w poprzedzającym nasz klucz synu

                //zmniejszamy wartość poprzednika o 1 a następnie wywołujemy funkcje usuwania dla niego
                // wynika to z tego że jeśli byśmy nie zmniejszyli wartości zapętlilibbyśmy program który chciałby ushunąc jego wartość
                //ale natrafiałby na korzeń z taką wartością i stworzyłaby się nieskończona pętla
               // leftChild->setKeyValue(leftChild->getKeysNumber() - 1, leftChild->getKeyValue(leftChild->getKeysNumber() - 1) - 1);
                //this->deleteKey(leftChild->getKeyValue(leftChild->getKeysNumber() - 1));
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

Node *BTree::search(int x)
{

    Node *n = this->getRoot();
    bool found = false;
    int i = 0;
    while (!found)
    {
        bool increment = true;
        if (x < n->getKeyValue(i))
        {
            n = n->getChild(i);
            i = 0;
            increment = false;
        }
        if (x == n->getKeyValue(i))
        {
            return n;
        }

        if (x > n->getKeyValue(i) && i == n->getKeysNumber() - 1)
        {
            n = n->getChild(i + 1);
            i = 0;
            increment = false;
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

int main()
{
    {
        BTree *tree = new BTree(4);


        for(int i=0;i<10;i++){
            tree->insertKey(i);
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
