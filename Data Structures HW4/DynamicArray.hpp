//
//  DynamicArray.hpp
//  Data Structures HW4
//
//  Created by Ezzat Qupty on 11/06/2019.
//  Copyright © 2019 Ezzat Qupty. All rights reserved.
//

#ifndef DynamicArray_hpp
#define DynamicArray_hpp

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

template <class T>
class dynamicArray {
	T* root;
	int size;
	int maxSize;
	int expandFactor;
	const T& initialValue;
public:
	explicit dynamicArray(int n = 10, int max = 10 , int factor = 2, const T& init = T()): maxSize (max), size(n), initialValue(init), expandFactor(factor){
		if(maxSize < size) maxSize = size + 10;
		root = new T[maxSize];
		for(int i = 0; i < maxSize; i++){
			root[i] = initialValue;
		}
	}
	dynamicArray(const dynamicArray& DA): initialValue(DA.initialValue) {
		this->maxSize = DA.maxSize;
		this->size = DA.size;
		this->expandFactor = DA.expandFactor;
		this->root = new T[this->maxSize];
		for(int i = 0; i < this->maxSize; i++){
			(this->root)[i] = DA.root[i];
		}
	}
	dynamicArray& operator=(const dynamicArray& DA){
		if(this->maxSize != DA.maxSize){
			this->maxSize = DA.maxSize;
			delete[] this->root;
			this->root = new T[this->maxSize];
		}
		if(this->size > DA.size){
			for(int i = this->size; i < this->maxSize; i++){
				this->root[i] = initialValue;
			}
		}
		this->expandFactor = DA.expandFactor;
		this->size = DA.size;
		for(int i = 0; i < size; i++){
			(this->root)[i] = DA.root[i];
		}
		return *this;
	}
	~dynamicArray(){
		delete[] root;
	}
	
	class OutOfBounds : std::exception{};
	class ArrayEmpty : std::exception{};
	
	void insert(T& elem){
		if(size == maxSize){
			T* temp = new T[maxSize * expandFactor];
			maxSize *= expandFactor;
			for(int i = 0; i < maxSize; i++){
				if(i < size) temp[i] = root[i];
				else temp[i] = initialValue;
			}
			delete[] root;
			root = temp;
		}
		size++;
		root[size-1] = elem;
	}
	void remove(){
		if(size == 0)
			throw ArrayEmpty();
		root[--size] = initialValue;
		if(size <= (maxSize/(expandFactor*2))){
			T* temp = new T[maxSize / expandFactor];
			if(maxSize > expandFactor) maxSize = (maxSize/expandFactor);
			for(int i = 0; i < maxSize; i++){
				temp[i] = root[i];
			}
			delete[] root;
			root = temp;
		}
	}
	T& operator[](int i){
		if(i < 0 || i > size - 1) throw OutOfBounds();
		return root[i];
	}
	const T& operator[](int i) const {
		if(i < 0 || i > size - 1) throw OutOfBounds();
		return root[i];
	}
		   
	T* getRoot() const { return root;}
	int getSize() const { return size;}

};


#endif /* DynamicArray_hpp */
