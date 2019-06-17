//
//  hash_table.hpp
//  hash_table
//
//  Created by Hasan Egbarie on 14/06/2019.
//  Copyright © 2019 Hasan Egbarie. All rights reserved.
//

#ifndef hash_table_hpp
#define hash_table_hpp

#include <stdio.h>
#include "DataNode.hpp"
#include "Exceptions.hpp"
namespace DataStructures{
    template <class D>
    class hashTable{
        dataNode<int, D> **array;
        int size;
        int items;

        void shrinkOrExpand(int t){
            dataNode<int, D> ** old_array = array;
            int old_size = size;
            if(t == 1) size = size * 2;
            else    size = size / 2;
            array = new (std::nothrow) dataNode<int, D>*[size];
            if(!array) {throw OutOfMemory();}
            for (int i = 0; i < size; i++) {
                array[i] = nullptr;
            }
            
            items = 0;
            
            //// moving the data to the new array
            for(int i = 0; i < old_size ; i++){
                if(old_array[i]){
                    dataNode<int, D> * curr = old_array[i];
                    while(curr){
                        try{
                            insert(curr->getKey(), &(curr->getData()));
                        }catch(OutOfMemory a){
                            emptyAnArray(old_array, old_size);
                            delete [] old_array;
                        }
                        curr = curr->getNext();
                    }
                }
            }
            emptyAnArray(old_array, old_size);
            delete [] old_array;
        }
        
        void emptyAnArray(dataNode<int, D> ** array, int old_size){
            for (int i = 0; i < old_size; i++) {
                if(array[i]){
                    dataNode<int, D> * curr = array[i];
                    while(curr){
                        dataNode<int, D> * tmp = curr->getNext();
                        delete curr;
                        curr = tmp;
                    }
                }
            }
        }
    public:
        hashTable(int n = 10): size(n){
            array = new (std::nothrow) dataNode<int, D>*[n];
            if(!array) throw OutOfMemory();
            for (int i = 0; i < size; i++) {
                array[i] = nullptr;
            }
            items = 0;

        }
        D find(int key){
            int place = (key % size);
            if(array[place]){
                dataNode<int, D>* ptr = array[place];
                while(ptr){
                    if(ptr->getKey() == key) return ptr->getData();
                    else ptr = ptr->getNext();
                }
                return nullptr;
            }else{return nullptr;}
        }
        void insert(int key, D* data){
            if(size == items) shrinkOrExpand(1);
            int place = (key % size);
            dataNode<int, D>* new_n = new (std::nothrow) dataNode<int, D>(key, data);
            if(!new_n) throw OutOfMemory();
                new_n->setNext(array[place]);
                array[place] = new_n;
            items++;
        }
        void remove(int key){
            if( size/4 >= items) shrinkOrExpand(0);
            int place = (key % size);
            if(array[place]){
                if(array[place]->getKey() == key){
					dataNode<int, D>* tmp = array[place]->getNext();
                    delete array[place];
                    items--;
                    array[place] = tmp;
                }else{
                    for (dataNode<int, D>* prev = array[place] ,* curr = prev; prev; prev = prev->getNext()) {
                        curr = prev->getNext();
                        if(curr->getKey() == key){
                            prev->setNext(curr->getNext());
                            delete curr;
                            items--;
                            break;
                        }
                    }
                }
            }
            
        }

        ~hashTable(){
            
            delete [] array;
        }
    };
};


#endif /* hash_table_hpp */





