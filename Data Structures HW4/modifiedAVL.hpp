

#ifndef AVL_hpp
#define AVL_hpp

#include <string>
#include <exception>
#include <iostream>
#include <stdbool.h>
#include "Exceptions.hpp"
#include "lectureInfo.hpp"
namespace DataStructures{
	
	template < class K >
	class node{
		K* key;
        int data; /// num of students
        int studentsOntheRight;
        int lecturesOntheRight;
		node* parent;
		node* left;
		node* right;
		int kids;
        
        
		
	public:
		
		int BF;
		int height;
        void setHeight(int newh){if(newh > 0) height = newh;}
        node(const K& key, int data): key(nullptr), data(0), parent(nullptr), left(nullptr), right(nullptr),studentsOntheRight(0),lecturesOntheRight(0) ,kids(0), BF(0), height(0){
			try{
				this->key = new K(key);
                this->data = data;
			} catch (std::bad_alloc e){ throw OutOfMemory();}
		}
		

        node(node& n){
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
		node& operator=(const node& n){
			if(*this == n) return &this;
			if(this->key) delete this->key;
			this(n);
			return &this;
		}

		~node(){
			delete key;
		}
		
		bool operator==(node* n){
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
		node* getLeft(){ return left;}
		node* getRight(){ return right;}
		node* getParent(){ return parent;}
		
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
		
		void setLeft(node* n){
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
		
		void setRight(node* n){
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
		
		void setParent(node* n){ this->parent = n;}
		
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
		
		void removeParent(node* n){
			if(!parent) return;
			this->parent = nullptr;
		}
		
		void update(){
			int lheight = left ? (left->height +1) : 0;
			int rheight = right ? (right->height + 1) : 0;
			height = lheight > rheight ? lheight : rheight;
//            height++;
			BF = lheight - rheight;
            //if(parent) parent->update();
		}
		
	};
	
    
	//Assuming class K has comparing operators
	class modifiedAVLTree {
		node<lecture>* root;
		int nodeCount;
		
		void deleteSubTree(node<lecture>* root);
		void insert_aux(node<lecture>* n, node<lecture>* in);
		int remove_aux(const lecture& key, node<lecture>* n);
		void balance(node<lecture>* n);
		void balanceAll(node<lecture>* son);
		node<lecture>* copyNodes(node<lecture>* head, node<lecture>* parent);
		node<lecture>* getData_aux(const lecture& key, node<lecture>* node);
		void swapNodes(node<lecture>* a, node<lecture>* b);
        int findMaxStudentsAux(int numLect, int collected, int studentSum, node<lecture>* curr);
		
	public:
		modifiedAVLTree(): root(nullptr), nodeCount(0){}
        modifiedAVLTree(node<lecture>* newRoot, int nodeCount):root(nullptr), nodeCount(nodeCount){
            root = copyNodes(newRoot, nullptr); 
        }
        ~modifiedAVLTree();
        modifiedAVLTree(modifiedAVLTree& avl){
            root = copyNodes(avl.root, nullptr);
            nodeCount = avl.nodeCount;
        }
		
        // this is not working :/
//        modifiedAVLTree& operator=(const modifiedAVLTree& avl){
//            if((*this) == avl) return this;
//            this(avl);
//            return this;
//        }
        
		node<lecture>* getRoot(){ return root;}
		
		int getData(const lecture& key){
			node<lecture>* n = getData_aux(key, root);
            if(!n) throw DoesNotExist();
			return n->getData();
		}

        int getNodeCount(){return nodeCount;}

		bool contains(const lecture& key);
        void fillAnArray(node<lecture>** array);
		void insert(const lecture& key, int data);
		void remove(const lecture& key);
		
		void rotateLeft(node<lecture>* node);
		void rotateRight(node<lecture>* node);
		
		bool isBalanced(){return isBalanced_aux(root);}
		bool isBalanced_aux(node<lecture>* n){
			if(!n) return true;
			if(n->getBF() < -1 || n->getBF() > 1) return false;
			else return isBalanced_aux(n->getLeft()) && isBalanced_aux(n->getRight());
		}
        int findMaxStudents(int numLect);
	};
	
	
	modifiedAVLTree::~modifiedAVLTree(){
		if(root) deleteSubTree(root);
	}

    void fillAnArray_aux(node<lecture>** array,node<lecture>* curr,int* i){
        if(!curr) return;
        if(!curr->getLeft()){
            array[*i] = new node<lecture>(*curr);
          ++(*i);
            if(curr->getRight())  fillAnArray_aux(array, curr->getRight(), i);
            return;
        }
        fillAnArray_aux(array, curr->getLeft(), i);
        array[*i] = new node<lecture>(*curr);
        ++(*i);
        fillAnArray_aux(array, curr->getRight(), i);
    }

    void modifiedAVLTree::fillAnArray(node<lecture>** array){
        int * a= new int(0);
        fillAnArray_aux(array, this->root, a);
        delete a;
    }
    
	//Copies all subtree of given head (parent pointer is for setting the heads parent node)

	node<lecture>* modifiedAVLTree::copyNodes(node<lecture>* head, node<lecture>* parent){
		if(!head) return nullptr;
        node<lecture>* new_n = new (std::nothrow) node<lecture>(*head);
		if(!new_n) throw OutOfMemory();
		new_n->setParent(parent);
		new_n->setLeft(modifiedAVLTree::copyNodes(head->getLeft(), new_n));
		new_n->setRight(modifiedAVLTree::copyNodes(head->getRight(), new_n));
		return new_n;
	}
	
	//Swaps location of two given nodes (this is used for a special case in the remove function)
	
	void modifiedAVLTree::swapNodes(node<lecture>* a, node<lecture>* b){
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

	void modifiedAVLTree::deleteSubTree(node<lecture>* root){
		if(root){
			deleteSubTree(root->getLeft());
			deleteSubTree(root->getRight());
			delete root;
		}
	}
	
	//Function looks if the key exists in the current tree.
	bool modifiedAVLTree::contains(const lecture& key){ return modifiedAVLTree::getData_aux(key, root);}
	

	node<lecture>* modifiedAVLTree::getData_aux(const lecture& key, node<lecture>* node){
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
		node<lecture>* new_n = new (std::nothrow) node<lecture>(key, data);
		if(!new_n) throw OutOfMemory();
		if(!this->root){
			root = new_n;
			nodeCount++;
		}
		else insert_aux(this->root, new_n);
	}
	
	//recursive algorithm to find and insert a key and data in the correct place
	
	void modifiedAVLTree::insert_aux(node<lecture>* n, node<lecture>* in){
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
            n->setStudentsOnTheRight((n->getStudentsOnTheRight() + in->getData()));
			modifiedAVLTree::insert_aux(n->getRight(), in);
		}
		else {
            n->setLecturesOnTheRight((n->getLecturesOnTheRight() + 1));
            n->setStudentsOnTheRight((n->getStudentsOnTheRight() + in->getData()));
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
	
	
	int modifiedAVLTree::remove_aux(const lecture& key, node<lecture>* n){
		if(!n) return 0;
		node<lecture>* parent = n->getParent();
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
				node<lecture>* son = nullptr;
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
				node<lecture>* itr = n->getRight();
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
	void modifiedAVLTree::balance(node<lecture>* n){
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
	void modifiedAVLTree::balanceAll(node<lecture>* son){
		if(!son) return;
		son->update();
		balance(son);
		balanceAll(son->getParent());
	}
	
	//Does a right rotation on the passed node
	void modifiedAVLTree::rotateRight(node<lecture>* n){
		node<lecture>* pivot = n->getLeft();
		node<lecture>* pivRight = pivot ? pivot->getRight() : nullptr;
		node<lecture>* nParent = n->getParent();
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
	
	void modifiedAVLTree::rotateLeft(node<lecture>* n){
		node<lecture>* pivot = n->getRight();
		node<lecture>* pivLeft = pivot ? pivot->getLeft() : nullptr;
		node<lecture>* nParent = n->getParent();
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
	
    int modifiedAVLTree::findMaxStudentsAux(int numLect, int collected, int studentSum, node<lecture>* curr){
        if(numLect == collected) return studentSum;
        if(curr->getLecturesOnTheRight() > numLect - collected) return findMaxStudentsAux(numLect, collected, studentSum, curr->getRight());
        if(curr->getLecturesOnTheRight() == numLect - collected) return studentSum + curr->getStudentsOnTheRight();
        if(!curr->getLeft() && collected <= numLect) return studentSum + curr->getData();
        if(curr->getLecturesOnTheRight() < numLect - collected) return findMaxStudentsAux(numLect, collected + curr->getLecturesOnTheRight() + 1, studentSum + curr->getStudentsOnTheRight() + curr->getData(), curr->getLeft());
        return studentSum;
    }
	
    int modifiedAVLTree::findMaxStudents(int numLect){
        return findMaxStudentsAux(numLect, 0, 0,this->getRoot());
    }
    
	
}

#endif /* AVL_hpp */
