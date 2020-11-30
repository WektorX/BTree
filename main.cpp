#include <iostream>
 
using namespace std;
 
class Node{
    int howManyKeys; // licznik ile kluczy zawiera dany wierzchołek -> każdy wierzchołek może posiadać howManyKeys + 1 dzieci
    int* keys; // tablica z kluczami (wartościami) przechowywanymi w danym wierzchołku
    Node* children; // tablica ze wskaźnikami do dzieci danego wierzchołka
    Node* parent; // wskaźnik do rodzica wierzchołka
    
    public:
        Node(int* k); // konstruktor z przekazaną tablicą kluczy
        Node(int howManyK, bool insertKeysManually); // konstruktor z przekazaną liczbą kluczy do wpisania ręcznie (bool == true)/wylosowania (bool == false)
        int getKeysNumber(); // zwraca liczbę kluczy w wierzchołku
        void setKeysNumber(int x); // ustawia licznik kluczy
        int getKeyValue(int pos); // zwraca wartość klucza z pozycji pos
        void setKeyValue(int pos, int x); // ustawia wartość x klucza na pozycji pos
        int getChild(int pos); // zwraca dziecko z pozycji pos
        void setChild(int pos, Node* n); // ustawia wskaźnik do dziecka n na pozysji pos
        void setParent(Node* n); // ustawia rodzica n
};
 
class BTree{
    int minKeys; // minimalna liczba kluczy przechowywana w jednym wierzchołku
    int maxKeys; // maksymalna liczba kluczy przechowywana w jednym wierzchołku
    Node* root; // korzeń drzewa
    
    public:
        BTree(); // konstruktor tworzący puste drzewo
        bool empty(); // zwraca wartość true dla drzewa pustego, false dla niepustego
        Node* getRoot(); // zwraca wskaźnik do korzenia
        void inorderTraversal(Node* n); // wypisuje wartości kluczy w porządku rosnącym
        Node* search(int x); // zwraca wskaźnik do wierzchołka zawierającego klucz x
        void splitNode(Node* n); // dzieli wierzchołek n na dwa wierzchołki
        void mergeNodes(Node* n, Node* m); // łączy wierzchołki n i m o wspólnym rodzicu
        void insertKey(int x); // wstawia klucz x do drzewa
        void deleteKey(int x); // usuwa klucz x z drzewa
        
        int size(Node* n); // zwraca rozmiar poddrzewa o korzeniu n
        int height(Node* n); // zwraca wysokość poddrzewa o korzeniu n
        int minimum(); // zwraca wartość minimalną drzewa
        int maximum(); // zwraca wartość maksymalną drzewa
        void clear(); // usuwa wszystkie wierzchołki drzewa
};
 
 
int main() {
    return 0;
}