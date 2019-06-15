//
//  unionFind.hpp
//  Data Structures HW4
//
//  Created by Ezzat Qupty on 11/06/2019.
//  Copyright © 2019 Ezzat Qupty. All rights reserved.
//

#ifndef unionFind_hpp
#define unionFind_hpp

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "DynamicArray.hpp"

template<class T>
class UFNode{
	int key;
	T* data;
	UFNode* parent;
	int unionSize;
	
public:
	UFNode(int k, T* dat, UFNode* par = NULL):key(k), parent(par), unionSize(1){
		data = new T(*dat);
	}
	explicit UFNode() { *this = NULL;}
	
	UFNode(UFNode& uf){
		this->key = uf.key;
		this->parent = uf.parent;
		T temp(*uf.data);
        // should delete old data
		this->data = &temp;
		this->unionSize = uf.unionSize;
	}
	UFNode& operator=(UFNode& uf){
        //check if its already the same
		*this(uf);
		return *this;
	}
    
	~UFNode(){
		delete data;
	}
	
	int getKey() {return key;}
	
	int getSize() const {return unionSize;}
	
	UFNode* getParent() const {return parent;}
	
	void setParent(UFNode* uf){
		if(this->parent){
			this->parent->unionSize -= this->unionSize;
		}
		this->parent = uf;
		if(uf) uf->unionSize += this->unionSize;
	}
	
	T* getData() const {return data;}
	void setData(T* dat){
		T temp(*dat);
		data = &temp;
	}
	
};

class UFinfo{
public:
	int groupSize;
	
	UFinfo(int grSize): groupSize(grSize){}
};

template<class K,class T>
class unionFind{
	UFNode<T>** arr;
	int size;
	
public:
	unionFind(int n, T data[]): size(n){
		arr = new UFNode<T>*[size];
		for(int i = 0; i < size; i++){
			UFNode<T>* tempNode = new UFNode<T>(i + 1, &data[i]);
			arr[i] = tempNode;

		}
	}
	
	unionFind(const unionFind& uf){
		this->size = uf.size;
		this->arr = new UFNode<T>*[size];
		for(int i = 0; i < size ; i++){
			UFNode<T>* tempNode = new UFNode<T>(*uf.arr[i]);
			this->arr[i] = tempNode;
		}
	}
	
	unionFind& operator=(const unionFind& uf){
		*this(uf);
		return *this;
	}
	
	~unionFind(){
		for(int i = 0; i < size; i++){
			delete arr[i];
		}
	}
	
	int find(int x){
		UFNode<T>* parentX = arr[x - 1];
		UFNode<T>* next = arr[x - 1]->getParent();
		while(next){
			parentX = next;
			next = next->getParent();
		}
		UFNode<T>* prev = arr[x - 1];
		next = arr[x - 1]->getParent();
		while(next){
			prev->setParent(parentX);
			prev= next;
			next = next->getParent();
		}
		return parentX->getKey();
	}
	
	void unite(int x, int y){
		int rootX = find(x);
		int rootY = find(y);
		if(rootX == rootY) return;
		int sizeX = arr[rootX - 1]->getSize();
		int sizeY = arr[rootY - 1]->getSize();
        //sizes should be updated in the new united group
		if(sizeX >= sizeY){
			arr[rootY - 1]->setParent(arr[rootX - 1]);
		} else {
			arr[rootX - 1]->setParent(arr[rootY - 1]);
		}
	}
	
	T* getData(int i){
		return arr[i - 1]->getData();
	}
};



#endif /* unionFind_hpp */
