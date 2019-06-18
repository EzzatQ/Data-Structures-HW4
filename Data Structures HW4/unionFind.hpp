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
#include "Exceptions.hpp"


namespace DataStructures{
	template<class T>
	class UFNode{
		int key;
		T* data;
		UFNode* parent;
		int unionSize;
		

	public:
		UFNode(int k, T* dat = nullptr, UFNode* par = nullptr):key(k), data(nullptr), parent(par), unionSize(1){
			try { data = new T(*dat);} catch (std::bad_alloc e){ throw OutOfMemory();}
		}
		explicit UFNode() { *this = nullptr;}

		UFNode(UFNode& uf){
			this->key = uf.key;
			this->parent = uf.parent;
			try {this->data = new T(*uf.data);} catch (std::bad_alloc e){ throw OutOfMemory();}
			this->unionSize = uf.unionSize;
		}
		UFNode& operator=(UFNode& uf){
			if(*this == uf) return;
			if(this->data) delete this->data;
			*this(uf);
			return *this;
		}
		
		bool operator==(UFNode& uf){
			return this->key == uf.key && this->data == uf.data && this->parent == uf.parent && this->unionSize == uf.unionSize;
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
			if(data) delete data;
			if(!dat) data = nullptr;
			else data = new T(dat);
		}

	};

	class UFinfo{
	public:
		int groupSize;

		UFinfo(int grSize): groupSize(grSize){}
	};

	template<class T>
	class unionFind{
		UFNode<T>** arr;
		int size;

	public:
		unionFind(int n, T data[]): size(n){
			try {
				arr = new UFNode<T>*[size];
				for(int i = 0; i < size; i++){
					UFNode<T>* tempNode = new UFNode<T>(i + 1, &data[i]);
					arr[i] = tempNode;
				}
			} catch (std::bad_alloc e){ throw OutOfMemory();}
		}

		unionFind(const unionFind& uf){
			try {
				this->size = uf.size;
				this->arr = new UFNode<T>*[size];
				for(int i = 0; i < size ; i++){
					UFNode<T>* tempNode = new UFNode<T>(*uf.arr[i]);
					this->arr[i] = tempNode;
				}
			} catch (std::bad_alloc e){ throw OutOfMemory();}
		}

		unionFind& operator=(const unionFind& uf){
			*this(uf);
			return *this;
		}

		~unionFind(){
			for(int i = 0; i < size; i++){
				delete arr[i];
			}
			delete arr;
		}

		int find(int x){
			if(x > size) return -1;
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
			if(sizeX >= sizeY){
				arr[rootY - 1]->setParent(arr[rootX - 1]);
			} else {
				arr[rootX - 1]->setParent(arr[rootY - 1]);
			}
		}

		T* getData(int i){
			return arr[i - 1]->getData();
		}
		
		int getSize(int i){
			int x = find(i);
			return arr[x-1]->getSize();
		}
	};
}

#endif /* unionFind_hpp */
