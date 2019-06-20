//
//  DataNode.hpp
//  hash_table
//
//  Created by Hasan Egbarie on 14/06/2019.
//  Copyright © 2019 Hasan Egbarie. All rights reserved.
//

#ifndef DataNode_hpp
#define DataNode_hpp

#include <stdio.h>
#include <iostream>
#include <exception>
#include "Exceptions.hpp"


namespace DataStructures{
	
	template< class K, class D>
    class dataNode{
        K* key;
        D* data;
        dataNode* next;
    public:
        dataNode(const K& k, D& dat): key(nullptr), data(nullptr),next(nullptr){
			int counter = 0;
			try{
				if(k) {key = new K(k); counter++;}
				else key = nullptr;
				data = new D(dat);
            } catch (std::bad_alloc e){
				if(counter == 1) delete key;
				throw OutOfMemory();}
        }
		
        dataNode(dataNode& n){
			int counter = 0;
			try{
				if(this->key){ this->key = new K(*n.key); counter++;}
				else this->key = nullptr;
                if(this->data) this->data = new D(*n.data);
				else this->data = nullptr;
                next = n->next;
            } catch (std::bad_alloc e){
				if(counter == 1) delete this->key;
				throw OutOfMemory();}
        }
        dataNode& operator=(const dataNode& n){
            if(*this == n) return &this;
            if(this->key) delete this->key;
            if(this->data) delete this->data;
            *this(n);
            return &this;
        }
        ~dataNode(){
            if(key) delete key;
            if(data) delete data;
        }
        
        bool operator==(dataNode* n){
            return n->key == key && n->data == data && n->next == next;
        }
        
        K& getKey() { return *key;}
        D& getData() {return *data;}
        D* getDataPtr(){return data;}
        K* getKeyPtr(){return key;}
		dataNode* getNext(){return next;}
		
        void setKey(K& k){
			if(key) delete key;
            try{
                if(k) key = new K(k);
				else key = nullptr;
            } catch (std::bad_alloc e){ throw OutOfMemory();}
        }
        
        void setData(D& dat){
            if(data) delete data;
            try{
                this->data = new D(dat);///////////////////////////////
            } catch (std::bad_alloc e){ throw OutOfMemory();}
        }
		
        void setNext(dataNode* n){next = n;}
    };
};
#endif /* DataNode_hpp */
