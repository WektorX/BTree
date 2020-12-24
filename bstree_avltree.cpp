#include <iostream>
#include <cstdlib>
#include <ctime>
#include "bstree_avltree.hpp"

using namespace std;

BSTNode::BSTNode(int v, BSTNode* l, BSTNode* r, BSTNode* p){
	this->value = v;
	this->left = l;
	this->right = r;
	this->parent = p;
}

int BSTNode::getValue(){
	if(this == nullptr){
		return NULL;
	}
	else{
		return this->value;
	}
}

BSTNode* BSTNode::getLeft(){
	return this->left;	
}

BSTNode* BSTNode::getRight(){
	return this->right;
}

BSTNode* BSTNode::getParent(){
	return this->parent;
}

void BSTNode::setValue(int v){
	this->value = v;
}

void BSTNode::setLeft(BSTNode* l){
	this->left = l;
}

void BSTNode::setRight(BSTNode* r){
	this->right = r;
}

void BSTNode::setParent(BSTNode* p){
	this->parent = p;
}

BSTree::BSTree(){
	this->root = nullptr;
}

BSTNode* BSTree::getRoot(){
	return this->root;
}

bool BSTree::empty(BSTNode* p){
	if(p == nullptr){
		return true;
	}
	else{
		return false;
	}
}

void BSTree::inorder(BSTNode* p){
	if(!empty(p)){
		this->inorder(p->getLeft());
		cout << p->getValue() << " ";
		this->inorder(p->getRight());
	}
	else if(p == this->root){
		cout << "Drzewo BST puste";
	}
}

void BSTree::insert(int x){
	if(this->empty(this->root)){
		BSTNode* n = new BSTNode(x, nullptr, nullptr, nullptr);
		this->root = n;
	}
	else{
		BSTNode* tmp = this->root;
		bool left = true;
		while(true){
			if(x < tmp->getValue()){
				if(!this->empty(tmp->getLeft())){
					tmp = tmp->getLeft();
				}
				else{
					left = true;
					break;
				}
			}
			else{
				if(!this->empty(tmp->getRight())){
					tmp = tmp->getRight();
				}
				else{
					left = false;
					break;
				}
			}
		}
		BSTNode* n = new BSTNode(x, nullptr, nullptr, tmp);
		if(left){
			tmp->setLeft(n);
		}
		else{
			tmp->setRight(n);
		}
	}
}

BSTNode* BSTree::search(int x){
	BSTNode* tmp = this->root;
	while(tmp != nullptr){
		if(tmp->getValue() == x){
			return tmp;
		}
		else if(tmp->getValue() > x){
			tmp = tmp->getLeft();
		}
		else if(tmp->getValue() < x){
			tmp = tmp->getRight();
		}
	}
	delete tmp;
	return nullptr;
}

BSTNode* BSTree::minimum(){
	BSTNode* tmp = this->root;
	while(tmp->getLeft() != nullptr){
		tmp = tmp->getLeft();
	}
	return tmp;
}

BSTNode* BSTree::maximum(){
	BSTNode* tmp = this->root;
	while(tmp->getRight() != nullptr){
		tmp = tmp->getRight();
	}
	return tmp;
}

BSTNode* BSTree::successor(BSTNode* p){
	if(!this->empty(p)){
		if(!this->empty(p->getRight())){
			BSTNode* tmp = p->getRight();
			while(!this->empty(tmp->getLeft())){
				tmp = tmp->getLeft();
			}
			return tmp;
		}
		else{
			BSTNode* tmp = p->getParent();
			while(!this->empty(tmp) && p==tmp->getRight()){
				p = tmp;
				tmp = tmp->getParent();
			}
			return tmp;
		}
	}
	else{
		return nullptr;
	}
}

BSTNode* BSTree::predecessor(BSTNode* p){
	if(!this->empty(p) && this->minimum() != p){
		if(!this->empty(p->getLeft())){
			BSTNode* tmp = p->getLeft();
			while(!this->empty(tmp->getRight())){
				tmp = tmp->getRight();
			}
			return tmp;
		}
		else{
			BSTNode* tmp = p->getParent();
			while(!this->empty(tmp) && p==tmp->getLeft()){
				tmp = tmp->getParent();
			}
			return tmp;
		}
	}
	else{
		return nullptr;
	}
}

void BSTree::del(BSTNode* p){
	if(!this->empty(p)){
		if(this->empty(p->getLeft()) && this->empty(p->getRight())){
			if(this->root == p){
				delete p;
				this->root = nullptr;
			}
			else{
				if(p->getParent()->getLeft() == p){
					p->getParent()->setLeft(nullptr);
				}
				else{
					p->getParent()->setRight(nullptr);
				}
				delete p;
			}
		}
		else if(!this->empty(p->getLeft()) && this->empty(p->getRight())){
			if(this->root == p){
				this->root = p->getLeft();
				this->root->setParent(nullptr);
				delete p;
			}
			else{
				if(p == p->getParent()->getLeft()){
					p->getParent()->setLeft(p->getLeft());
				}
				else{
					p->getParent()->setRight(p->getLeft());
				}
				delete p;
			}
		}
		else if(this->empty(p->getLeft()) && !this->empty(p->getRight())){
			if(this->root == p){
				this->root = p->getRight();
				this->root->setParent(nullptr);
				delete p;
			}
			else{
				if(p == p->getParent()->getLeft()){
					p->getParent()->setLeft(p->getRight());
				}
				else{
					p->getParent()->setRight(p->getRight());
				}
				delete p;
			}
		}
		else{
			BSTNode* tmp = this->successor(p);
			p->setValue(tmp->getValue());
			if(tmp == tmp->getParent()->getLeft()){
				tmp->getParent()->setLeft(tmp->getRight());
			}
			else{
				tmp->getParent()->setRight(tmp->getRight());
			}
			delete tmp;
		}
	}
}

int BSTree::size(BSTNode* p){
	if(!this->empty(p)){
		return this->size(p->getLeft()) + this->size(p->getRight()) + 1;
	}
	else{
		return 0;
	}
}

int BSTree::height(BSTNode* p){
	if(!this->empty(p)){
		int heightLeft = this->height(p->getLeft());
		int heightRight = this->height(p->getRight());
		
		if(heightLeft > heightRight){
			return heightLeft + 1;
		}
		else{
			return heightRight + 1;
		}
	}
	else{
		return 0;
	}
}

void BSTree::clear(BSTNode* p){
	if(!this->empty(p)){
		this->clear(p->getLeft());
		this->clear(p->getRight());
		this->del(p);
	}
}

//Zadanie 8.1


avlNode::avlNode(int v, int bf){
	this->value = v;
	this->bf = bf;
	this->left = nullptr;
	this->right = nullptr;
	this->parent = nullptr;
}

int avlNode::getBf(){
	return this->bf;
}

void avlNode::setBf(int bf){
	this->bf = bf;
}

int avlNode::getValue(){
	if(this == nullptr){
		return NULL;
	}
	else{
		return this->value;
	}
}

avlNode* avlNode::getLeft(){
	return this->left;	
}

avlNode* avlNode::getRight(){
	return this->right;
}

avlNode* avlNode::getParent(){
	return this->parent;
}

void avlNode::setValue(int v){
	this->value = v;
}

void avlNode::setLeft(avlNode* l){
	this->left = l;
}

void avlNode::setRight(avlNode* r){
	this->right = r;
}

void avlNode::setParent(avlNode* p){
	this->parent = p;
}

AVLTree::AVLTree(){
	this->root = nullptr;
}


avlNode* AVLTree::getRoot(){
	return this->root;
}

bool AVLTree::empty(avlNode* p){
	if(p == nullptr){
		return true;
	}
	else{
		return false;
	}
}

int AVLTree::height(avlNode* p){
	if(!this->empty(p)){
		int heightLeft = this->height(p->getLeft());
		int heightRight = this->height(p->getRight());
		
		if(heightLeft > heightRight){
			return heightLeft + 1;
		}
		else{
			return heightRight + 1;
		}
	}
	else{
		return 0;
	}
}

void AVLTree::inorder(avlNode* p){
	if(!empty(p)){
		this->inorder(p->getLeft());
		cout << p->getValue() << " [bf:" << p->getBf() << "] ";
		this->inorder(p->getRight());
	}
	else if(p == this->root){
		cout << "Drzewo AVL puste";
	}
}

avlNode* AVLTree::search(int x){
	avlNode* tmp = this->root;
	while(tmp != nullptr){
		if(tmp->getValue() == x){
			return tmp;
		}
		else if(tmp->getValue() > x){
			tmp = tmp->getLeft();
		}
		else if(tmp->getValue() < x){
			tmp = tmp->getRight();
		}
	}
	delete tmp;
	return nullptr;
}

void AVLTree::RR(avlNode* a, avlNode* b){
	if(!this->empty(a) && !this->empty(b)){
		//cout<<"\n\tRotacja RR na elementach: " << a->getValue() << " i " << b->getValue() << endl;
		a->setRight(b->getLeft());
		if(!this->empty(a->getRight())){
			a->getRight()->setParent(a);
		}
		b->setParent(a->getParent());
		if(b->getParent() != nullptr){
			if(b->getParent()->getRight() == a){
				b->getParent()->setRight(b);
			}
			else if(b->getParent()->getLeft() == a){
				b->getParent()->setLeft(b);
			}
		}
		if(this->root == a){
			this->root = b;
		}
		a->setParent(b);
		b->setLeft(a);
		a->setBf(this->height(a->getLeft()) - this->height(a->getRight()));
		b->setBf(this->height(b->getLeft()) - this->height(b->getRight()));
	}	
}

void AVLTree::LL(avlNode* a, avlNode* b){
	if(!this->empty(a) && !this->empty(b)){
		//cout<<"\n\tRotacja LL na elementach: " << a->getValue() << " i " << b->getValue() << endl;
		a->setLeft(b->getRight());
		if(!this->empty(a->getLeft())){
			a->getLeft()->setParent(a);	
		}
		b->setParent(a->getParent());
		if(this->root == a){
			this->root = b;
		}
		if(b->getParent() != nullptr){
			if(b->getParent()->getRight() == a){
				b->getParent()->setRight(b);
			}
			else if(b->getParent()->getLeft() == a){
				b->getParent()->setLeft(b);
			}
		}
		a->setParent(b);
		b->setRight(a);
		a->setBf(this->height(a->getLeft()) - this->height(a->getRight()));
		b->setBf(this->height(b->getLeft()) - this->height(b->getRight()));
	}
}

void AVLTree::RL(avlNode* a, avlNode* b, avlNode* c){
	if(!this->empty(a) && !this->empty(b) && !this->empty(c)){
		this->LL(b,c);
		this->RR(a,c);
	}
}

void AVLTree::LR(avlNode* a, avlNode* b, avlNode* c){
	if(!this->empty(a) && !this->empty(b) && !this->empty(c)){
		this->RR(b,c);
		this->LL(a,c);
	}
}

void AVLTree::insert(int x){
	avlNode* n = new avlNode(x, 0);
	if(this->root == nullptr){
		this->root = n;
	}
	else{
		avlNode* tmp = this->root;
		bool left = true;
		while(true){
			if(x < tmp->getValue()){
				if(!this->empty(tmp->getLeft())){
					tmp = tmp->getLeft();
				}
				else{
					left = true;
					break;
				}
			}
			else{
				if(!this->empty(tmp->getRight())){
					tmp = tmp->getRight();
				}
				else{
					left = false;
					break;
				}
			}
		}
		n->setParent(tmp);
		if(left){
			tmp->setLeft(n);
		}
		else{
			tmp->setRight(n);
		}
		while(tmp != nullptr){
			tmp->setBf(this->height(tmp->getLeft()) - this->height(tmp->getRight()));
			tmp = tmp->getParent();
		}
				
		///// Rotacje po standardowym insercie BST
		tmp = n->getParent();
		while(tmp != nullptr){
			if(tmp->getBf() <= 1 && tmp->getBf() >= -1){
				tmp = tmp->getParent();
			}
			else{
				break;
			}
		}
		
		if(tmp != nullptr){
			if(tmp->getBf() < -1){
				if(tmp->getRight()->getBf() != 1){
					this->RR(tmp, tmp->getRight());
				}
				else{
					this->RL(tmp, tmp->getRight(), tmp->getRight()->getLeft());
				}
			}
			else if(tmp->getBf() > 1){
				if(tmp->getLeft()->getBf() != -1){
					this->LL(tmp, tmp->getLeft());
				}
				else{
					this->LR(tmp, tmp->getLeft(), tmp->getLeft()->getRight());
				}
			}
		}
	}
}
