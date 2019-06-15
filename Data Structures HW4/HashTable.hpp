//
//  HashTable.hpp
//  Data Structures HW4
//
//  Created by Ezzat Qupty on 14/06/2019.
//  Copyright © 2019 Ezzat Qupty. All rights reserved.
//

#ifndef HashTable_hpp
#define HashTable_hpp

#include <stdio.h>
#include "DynamicArray.hpp"

template<class T>
class HashNode{
	int key;
	T* data;
	HashNode* next;
public:
	HashNode(int k, T* dat, HashNode* hn = nullptr): key(k), next(hn){
		if(!dat){
			data = nullptr;
			return;
		}
		data = new T(*dat);
	}
	
	HashNode(const HashNode& hn){
		this->key = hn.key;
		this->next = hn.next;
		data = new T(hn.data);
	}
	
	HashNode& operator=(const HashNode& hn){
		if(this->data) delete data;
		*this(hn);
		return *this;
	}
	
	int getKey() const {return key;}
	void setKey(int k) {key = k;}
	T* getData() const {return data;}
	void setData(T* dat){
		if(dat != data){
			delete data;
			data = dat;
		}
	}
	HashNode* getNext() const {return next;}
	void setNext(HashNode* hn) { next = hn;}
};

template< class T>
class HashTable{
	dynamicArray<HashNode<T>*> arr;
	int size;
	
public:
	HashTable(int n): size(n){
		arr = dynamicArray<HashNode<T>*>(size, nullptr);
	}
	HashTable(const HashTable& ht){
		this->size = ht.size;
		this->arr = ht.arr;
	}
	HashTable& operator=(const HashTable& ht){
		*this(ht);
		return *this;
	}
	
	void insert(int i, T* data){
		if(search(i) != nullptr) return;
		HashNode<T>* next = arr[i%size];
		HashNode<T> newNode(i, data, next);
		arr[i%size] = &newNode;
	}
	
	T* search(int i){
		HashNode<T>* list = arr[i%size];
		while(list){
			if(list->getKey() == i) return list->getData();
			list = list->getNext();
		}
		return nullptr;
	}
	
	void remove(int i){
		HashNode<T>* prev = arr[i%size];
		HashNode<T>* curr = prev;
		HashNode<T>* next = curr->getNext();
		if(curr->getKey() == i){
			arr[i%size] = next;
			delete curr;
			return;
		}
		curr = next;
		next = next->getNext();
		while(curr){
			if(curr->getKey() == i){
				prev->setNext(next);
				delete curr;
				return;
			}
			prev = curr;
			curr = next;
			next = next->getNext();
		}
	}
	
	void print(){
		std::cout << "--------------------" << std::endl;
		for(int i = 0; i < size; i++){
			std::cout << i << ") ";
			HashNode<T>* itr = arr[i];
			while(itr != nullptr){
				std::cout << itr->getKey() << " -> ";
				itr = itr->getNext();
			}
			std::cout << std::endl;
		}
		std::cout << "--------------------" << std::endl;
	}
	
};

#endif /* HashTable_hpp */
