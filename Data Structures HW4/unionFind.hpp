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
	T* data;
	UFNode* parent;
	int unionSize;
	
public:
	UFNode(T* dat, UFNode* par = NULL): parent(par), unionSize(1){
		T temp(*dat);
		data = &temp;
	}
	explicit UFNode() { *this = NULL;}
	
	UFNode(UFNode& uf){
		this->parent = uf.parent;
		T temp(*uf.data);
		this->data = &temp;
		this->unionSize = uf.unionSize;
	}
	UFNode& operator=(UFNode& uf){
		*this(uf);
		return *this;
	}
	~UFNode(){
		delete data;
	}
	
	UFNode* getParent() const {return parent;}
	void setParent(UFNode& uf){
		this->parent = &uf;
		uf.unionSize += this->unionSize;
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

template<class T>
class unionFind{
	dynamicArray<UFNode<T>*> arr;
	
public:
	unionFind(int n, T vals[]){
		arr = dynamicArray<UFNode<T>*>(0);
		for(int i = 0; i < n; i++){
			UFNode<T>* tempNode = new UFNode<T>(vals[i]);
			arr.insert(tempNode);

		}
	}
	
	unionFind(const unionFind& uf){
		this->arr = dynamicArray<UFNode<T>*>(0);
		for(int i = 0; i < uf.arr.getSize() ; i++){
			UFNode<T>* tempNode = new UFNode<T>(uf.arr[i]);
			this->arr.insert(tempNode);
		}
	}
	
	unionFind& operator=(const unionFind& uf){
		*this(uf);
		return *this;
	}
	
	~unionFind(){
		for(int i = 0; i < arr.getSize(); i++){
			delete arr[i];
		}
	}
	
	//how do i deal with the key? the course numbers arent gonna be from 1 to n (hashing?)
	int find(int x){
		while(true){
			
		}
	}
	
	void unite(int x, int y){
		
	}
	
	//func add another element to the structure.
	
	//func that removes an element.
	
	
	
};



#endif /* unionFind_hpp */
