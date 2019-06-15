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
        dataNode(const K& key, D& data): key(nullptr), data(nullptr),next(nullptr){
            try{
                this->key = new K(key);
                this->data = new D(data);
            } catch (std::bad_alloc e){ throw OutOfMemory();}
        }
        dataNode(dataNode& n){
            try{
                this->key = new K(*n.key);
                this->data = new D(*n.data);
                next = n->next;
            } catch (std::bad_alloc e){ throw OutOfMemory();}
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
        D& getData() { return *data;}
        D* getDataPtr(){return data;}
        K* getKeyPtr(){return key;}
		dataNode* getNext(){return next;}
        void setKey(K& k){
			if(key) delete key;
            try{
                key = new K(k);
            } catch (std::bad_alloc e){ throw OutOfMemory();}
        }
        
        void setData(D& dat){
            if(data) delete data;
            try{
                this->data = new D(data);
            } catch (std::bad_alloc e){ throw OutOfMemory();}
        }
        void setNext(dataNode* n){next = n;}
    };
};
#endif /* DataNode_hpp */
