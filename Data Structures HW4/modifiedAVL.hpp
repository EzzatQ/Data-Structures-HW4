//
//  AVL.hpp
//  Data Structures HW2
//
//  Created by Ezzat Qupty on 16/04/2019.
//  Copyright © 2019 Ezzat Qupty. All rights reserved.
//

#ifndef modAVL_hpp
#define modAVL_hpp

#include <string>
#include <exception>
#include <iostream>
#include <stdbool.h>
#include "Exceptions.hpp"
#include "lectureInfo.hpp"


namespace DataStructures{

	template < class K >
	class modifiedNode{
		K* key;
        int data; /// num of students
        int studentsOntheRight;
        int lecturesOntheRight;
		modifiedNode* parent;
		modifiedNode* left;
		modifiedNode* right;
		int kids;

	public:

		int BF;
		int height;
        void setHeight(int newh){if(newh > 0) height = newh;}
        modifiedNode(const K& key, int data): key(nullptr), data(0), parent(nullptr), left(nullptr), right(nullptr),studentsOntheRight(0),lecturesOntheRight(0) ,kids(0), BF(0), height(0){
			try{
				this->key = new K(key);
                this->data = data;
			} catch (std::bad_alloc e){ throw OutOfMemory();}
		}


        modifiedNode(modifiedNode& n){
            try{
                this->key = new K(*n.key);
                this->data = n.data;
            } catch (std::bad_alloc e){ throw OutOfMemory();}
            this->parent = n.parent;
            this->left = n.left;
            this->right = n.right;
            this->kids = n.kids;
            this->BF = n.BF;
            this->height = n.height;
            this->studentsOntheRight = n.studentsOntheRight;
            this->lecturesOntheRight = n.lecturesOntheRight;
		}
		modifiedNode& operator=(const modifiedNode& n){
			if(*this == n) return &this;
			if(this->key) delete this->key;
			this(n);
			return &this;
		}

		~modifiedNode(){
			delete key;
		}

		bool operator==(modifiedNode* n){
			return n->key == key && n->data == data && n->left == left && n->right == right && n->parent == parent;
		}

		K& getKey() { return *key;}
		int getData() { return data;}
		K* getKeyPtr(){return key;}
		int getKids() { return kids;}
		int getBF() { return BF;}
		int getHeight() { return height;}
        int getLecturesOnTheRight(){return lecturesOntheRight;}
        int getStudentsOnTheRight(){return studentsOntheRight;}
		modifiedNode* getLeft(){ return left;}
		modifiedNode* getRight(){ return right;}
		modifiedNode* getParent(){ return parent;}

        void setLecturesOnTheRight(int n){lecturesOntheRight = n;}
        void setStudentsOnTheRight(int n){studentsOntheRight = n;}
		void setKeyPtr(K* key){this->key = key;}
		void setKey(K& key){
			if(this->key){
				delete this->key;
			}
			try{
				this->key = new K(key);
			} catch (std::bad_alloc e){ throw OutOfMemory();}
		}

		void setData(int data){
            this->data = data;
		}

		void setLeft(modifiedNode* n){
			if(!n && !left){
			}
			if(!n && left){
				left = nullptr;
				kids--;
			}
			if(n && !left){
				left = n;
				kids++;
			}
			if(n && left){
				left = n;
			}
			update();
		}

		void setRight(modifiedNode* n){
			if(!n && !right){
			}
			else if(!n && right){
				right = nullptr;
				kids--;
			}
			else if(n && !right){
				right = n;
				kids++;
			}
			else {
				right = n;
			}
			update();
		}

		void setParent(modifiedNode* n){ this->parent = n;}

		void removeLeft(){
			if(!left) return;
			left = nullptr;
			kids--;
			update();
		}

		void removeRight(){
			if(!right) return;
			right = nullptr;
			kids--;
			update();
		}

		void removeParent(modifiedNode* n){
			if(!parent) return;
			this->parent = nullptr;
		}

		void update(){
			int lheight = left ? (left->height + 1) : 0;
			int rheight = right ? (right->height + 1) : 0;
			height = lheight > rheight ? lheight : rheight;
			BF = lheight - rheight;
		}

	};


	//Assuming class K has comparing operators
	class modifiedAVLTree {
		modifiedNode<lecture>* root;
		int nodeCount;

		void deleteSubTree(modifiedNode<lecture>* root);
		void insert_aux(modifiedNode<lecture>* n, modifiedNode<lecture>* in);
		int remove_aux(const lecture& key, modifiedNode<lecture>* n);
		void balance(modifiedNode<lecture>* n);
		void balanceAll(modifiedNode<lecture>* son);
		modifiedNode<lecture>* copyNodes(modifiedNode<lecture>* head, modifiedNode<lecture>* parent);
		modifiedNode<lecture>* getData_aux(const lecture& key, modifiedNode<lecture>* node);
		void swapNodes(modifiedNode<lecture>* a, modifiedNode<lecture>* b);

	public:
		modifiedAVLTree(): root(nullptr), nodeCount(0){}
        modifiedAVLTree(modifiedNode<lecture>* newRoot, int nodeCount):root(nullptr), nodeCount(nodeCount){
            root = copyNodes(newRoot, nullptr);
        }
        ~modifiedAVLTree();
        modifiedAVLTree(modifiedAVLTree& avl){
            root = copyNodes(avl.root, nullptr);
            nodeCount = avl.nodeCount;
        }

		modifiedNode<lecture>* getRoot(){ return root;}

		int getData(const lecture& key){
			modifiedNode<lecture>* n = getData_aux(key, root);
            if(!n) throw DoesNotExist();
			return n->getData();
		}

        int getNodeCount(){return nodeCount;}

		bool contains(const lecture& key);
        void fillAnArray(modifiedNode<lecture>** array);
		void insert(const lecture& key, int data);
		void remove(const lecture& key);

		void rotateLeft(modifiedNode<lecture>* node);
		void rotateRight(modifiedNode<lecture>* node);

		bool isBalanced(){return isBalanced_aux(root);}
		bool isBalanced_aux(modifiedNode<lecture>* n){
			if(!n) return true;
			if(n->getBF() < -1 || n->getBF() > 1) return false;
			else return isBalanced_aux(n->getLeft()) && isBalanced_aux(n->getRight());
		}
	};


	modifiedAVLTree::~modifiedAVLTree(){
		if(root) deleteSubTree(root);
	}

    void fillAnArray_aux(modifiedNode<lecture>** array,modifiedNode<lecture>* curr,int* i){
        if(!curr) return;
        if(!curr->getLeft()){
            array[*i] = new modifiedNode<lecture>(*curr);
          ++(*i);
            if(curr->getRight())  fillAnArray_aux(array, curr->getRight(), i);
            return;
        }
        fillAnArray_aux(array, curr->getLeft(), i);
        array[*i] = new modifiedNode<lecture>(*curr);
        ++(*i);
        fillAnArray_aux(array, curr->getRight(), i);
    }

    void modifiedAVLTree::fillAnArray(modifiedNode<lecture>** array){
        int * a= new int(0);
        fillAnArray_aux(array, this->root, a);
        delete a;
    }

	//Copies all subtree of given head (parent pointer is for setting the heads parent node)

	modifiedNode<lecture>* modifiedAVLTree::copyNodes(modifiedNode<lecture>* head, modifiedNode<lecture>* parent){
		if(!head) return nullptr;
        modifiedNode<lecture>* new_n = new (std::nothrow) modifiedNode<lecture>(*head);
		if(!new_n) throw OutOfMemory();
		new_n->setParent(parent);
		new_n->setLeft(modifiedAVLTree::copyNodes(head->getLeft(), new_n));
		new_n->setRight(modifiedAVLTree::copyNodes(head->getRight(), new_n));
		return new_n;
	}

	//Swaps location of two given nodes (this is used for a special case in the remove function)

	void modifiedAVLTree::swapNodes(modifiedNode<lecture>* a, modifiedNode<lecture>* b){
        if(!a || !b)return;
		lecture* tempKey = a->getKeyPtr();
		int tempData = a->getData();
        int tmpStudentsRight = a->getStudentsOnTheRight();
        int tmpLecturesRight = a->getLecturesOnTheRight();
		a->setKeyPtr(b->getKeyPtr());
		a->setData(b->getData());
        a->setStudentsOnTheRight(b->getStudentsOnTheRight());
        a->setLecturesOnTheRight(b->getLecturesOnTheRight());
		b->setKeyPtr(tempKey);
		b->setData(tempData);
        b->setStudentsOnTheRight(tmpStudentsRight);
        b->setLecturesOnTheRight(tmpLecturesRight);
	}

	//deletes passed noode and all its children.

	void modifiedAVLTree::deleteSubTree(modifiedNode<lecture>* root){
		if(root){
			deleteSubTree(root->getLeft());
			deleteSubTree(root->getRight());
			delete root;
		}
	}

	//Function looks if the key exists in the current tree.
	bool modifiedAVLTree::contains(const lecture& key){ return modifiedAVLTree::getData_aux(key, root);}


	modifiedNode<lecture>* modifiedAVLTree::getData_aux(const lecture& key, modifiedNode<lecture>* node){
		if(!node) return nullptr;
		lecture node_key = node->getKey();
		if(key == node_key) return node;
		if(key < node_key) return getData_aux(key, node->getLeft());
		if(key > node_key) return getData_aux(key, node->getRight());
		return nullptr;
	}

	//inserts new node in its right place
	//throws OUtOfMemory if there is an allocatiion problem
	//throws Already Exists if Key exists.0

	void modifiedAVLTree::insert(const lecture& key, int data){
		modifiedNode<lecture>* new_n = new (std::nothrow) modifiedNode<lecture>(key, data);
		if(!new_n) throw OutOfMemory();
		if(!this->root){
			root = new_n;
			nodeCount++;
		}
		else insert_aux(this->root, new_n);
	}

	//recursive algorithm to find and insert a key and data in the correct place

	void modifiedAVLTree::insert_aux(modifiedNode<lecture>* n, modifiedNode<lecture>* in){
		if(n->getKey() == in->getKey()) throw AlreadyExists();
		if(n->getKey() > in->getKey()){
			if(n->getLeft()){
				modifiedAVLTree::insert_aux(n->getLeft(),in);
			}
			else {
				n->setLeft(in);
				in->setParent(n);
				n->update();
				nodeCount++;
                balanceAll(n);
			}
		}
		else if(n->getRight()){
            n->setLecturesOnTheRight((n->getLecturesOnTheRight() + 1));
            n->setStudentsOnTheRight((n->getLecturesOnTheRight() + in->getData()));
			modifiedAVLTree::insert_aux(n->getRight(), in);
		}
		else {
            n->setLecturesOnTheRight((n->getLecturesOnTheRight() + 1));
            n->setStudentsOnTheRight((n->getLecturesOnTheRight() + in->getData()));
			n->setRight(in);
			in->setParent(n);
			n->update();
			nodeCount++;
            balanceAll(n);
		}

	}

	//Removes node  of given key while maintaining balance of the tree

	void modifiedAVLTree::remove(const lecture& key){
		remove_aux(key, root);
	}


	int modifiedAVLTree::remove_aux(const lecture& key, modifiedNode<lecture>* n){
		if(!n) return 0;
		modifiedNode<lecture>* parent = n->getParent();
		if(n->getKey() == key){
			if(n->getKids() == 0){
				if(n == root) root = nullptr;
				else if(parent->getLeft() == n) parent->setLeft(nullptr);
				else if(parent->getRight() == n) parent->setRight(nullptr);
				nodeCount--;
                int students = n->getData();
				delete n;
				balanceAll(parent);
				return students;
			}
			else if(n->getKids() == 1){
				modifiedNode<lecture>* son = nullptr;
				if(n->getLeft()) son = n->getLeft();
				else son = n->getRight();
				if(n == root) root = son;
				else if(parent->getLeft() == n) parent->setLeft(son);
				else if(parent->getRight() == n) parent->setRight(son);
                son->setParent(parent);
				nodeCount--;
                int students = n->getData();
				delete n;
				balanceAll(parent);
				return students;
			}
			else {////
				modifiedNode<lecture>* itr = n->getRight();
				while(itr && itr->getLeft()){
					itr = itr->getLeft();
				}
				swapNodes(n, itr);
				return modifiedAVLTree::remove_aux(key, itr);
			}
		}
		else if(n->getKey() > key) return modifiedAVLTree::remove_aux(key, n->getLeft());
        else {
            int res = modifiedAVLTree::remove_aux(key, n->getRight());
            n->setLecturesOnTheRight(n->getLecturesOnTheRight() - 1);
            n->setStudentsOnTheRight(n->getStudentsOnTheRight() - res);
            return res;
        }

	}

	//Depending on which situation the tree is in, performs needed rotations to
	// keep tree balanced
	void modifiedAVLTree::balance(modifiedNode<lecture>* n){
		if(!n) return;
		if(n->getLeft()){
			if(n->BF == 2 && n->getLeft()->BF == -1){    //LR
				rotateLeft(n->getLeft());
				rotateRight(n);
			}
			if(n->BF == 2 && n->getLeft()->BF >= 0){     //LL
				rotateRight(n);
			}
		}
		if(n->getRight()){
			if(n->BF == -2 && n->getRight()->BF <= 0){   //RR
				rotateLeft(n);
			}
			if(n->BF == -2 && n->getRight()->BF == 1){    //RL
				rotateRight(n->getRight());
				rotateLeft(n);
			}
		}
	}

	//Balances all nodes in path from son to root
	void modifiedAVLTree::balanceAll(modifiedNode<lecture>* son){
		if(!son) return;
		son->update();
		balance(son);
		balanceAll(son->getParent());
	}

	//Does a right rotation on the passed node
	void modifiedAVLTree::rotateRight(modifiedNode<lecture>* n){
		modifiedNode<lecture>* pivot = n->getLeft();
		modifiedNode<lecture>* pivRight = pivot ? pivot->getRight() : nullptr;
		modifiedNode<lecture>* nParent = n->getParent();
		n->setLeft(pivRight);
        if(pivRight)pivRight->setParent(n);
		pivot->setRight(n);
		if(n == root) root = pivot;
		else if(nParent->getLeft() == n) nParent->setLeft(pivot);
		else if(nParent->getRight() == n) nParent->setRight(pivot);
		pivot->setParent(n->getParent());
		n->setParent(pivot);
		if(pivot->getLeft()) pivot->getLeft()->setParent(pivot);
		if(pivot->getRight()) pivot->getRight()->setParent(pivot);
        pivot->setStudentsOnTheRight(pivot->getStudentsOnTheRight() + n->getStudentsOnTheRight() + n->getData());
        pivot->setLecturesOnTheRight(pivot->getLecturesOnTheRight() + n->getLecturesOnTheRight()+1);
		n->update();
		pivot->update();
	}

	//Does a left rotation on the passed node

	void modifiedAVLTree::rotateLeft(modifiedNode<lecture>* n){
		modifiedNode<lecture>* pivot = n->getRight();
		modifiedNode<lecture>* pivLeft = pivot ? pivot->getLeft() : nullptr;
		modifiedNode<lecture>* nParent = n->getParent();
		n->setRight(pivLeft);
        if(pivLeft)pivLeft->setParent(n);
		pivot->setLeft(n);
		if(n == root) root = pivot;
		else if(nParent->getLeft() == n) nParent->setLeft(pivot);
		else if(nParent->getRight() == n) nParent->setRight(pivot);
		pivot->setParent(nParent); //
		n->setParent(pivot);
		if(pivot->getLeft()) pivot->getLeft()->setParent(pivot);
		if(pivot->getRight()) pivot->getRight()->setParent(pivot);
        n->setStudentsOnTheRight(n->getStudentsOnTheRight() - pivot->getStudentsOnTheRight() - pivot->getData());
        n->setLecturesOnTheRight(n->getLecturesOnTheRight() - pivot->getLecturesOnTheRight() - 1);
		n->update();
		pivot->update();
	}




}

#endif /* modAVL_hpp */
