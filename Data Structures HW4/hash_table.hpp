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
        int * a;
        int * b;
        int btop;
        int size;
        int items;
        
        bool isInit(int m){
            if(a[m] < size && a[m] >= 0){
                if(b[a[m]] == m) return true;
                else return false;
            }else return false;
        }
        void toInit(int m){
            a[m] = btop;
            b[btop] = m;
            btop = btop + 1;
        }
        void shrinkOrExpand(int t){
            dataNode<int, D> ** old_array = array;
            int old_size = size;
            int * old_a = a;
            int * old_b = b;
            if(t == 1) size = size * 2;
            else if(size >= 20) size = size / 2;
            a = new (std::nothrow) int[size];
            if(!a) throw OutOfMemory();
            b = new (std::nothrow) int[size];
            if(!b){
                delete [] old_a;
                throw OutOfMemory();
            }
            array = new (std::nothrow) dataNode<int, D>*[size];
            if(!array) {
                delete [] old_a;
                delete [] old_b;
                throw OutOfMemory();
            }
            items = 0;
            
            //// moving the data to the new array
            for(int i = 0; i < old_size ; i++){
                if((old_a[i] < old_size && old_b[old_a[i]] == i)){
                    dataNode<int, D> * curr = old_array[i];
                    while(curr){
                        try{
                            insert(curr->getKey(), curr->getData());
                        }catch(OutOfMemory a){
                            emptyAnArray(old_a, old_b, old_array, old_size);
                            delete [] old_a;
                            delete [] old_b;
                            delete [] old_array;
                        }
                        curr = curr->getNext();
                    }
                }
            }
            emptyAnArray(old_a, old_b, old_array, old_size);
            delete [] old_a;
            delete [] old_b;
            delete [] old_array;
        }
        
        void emptyAnArray(int * a, int * b, dataNode<int, D> ** array, int old_size){
            for (int i = 0; i < old_size; i++) {
                if((a[i] < old_size  && a[i]>=0 && b[a[i]] == i)){
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
            a = new int[n];
            b = new int[n];
            items = 0;
            btop = 0;
        }
        dataNode<int, D> * find(int key){
            int place = (key % size);
            if(isInit(place)){
                dataNode<int, D>* ptr = array[place];
                while(ptr){
                    if(ptr->getKey() == key) return ptr;
                    else ptr = ptr->getNext();
                }
                return nullptr;
            }else{return nullptr;}
        }
        void insert(int key, D& data){
            if(size == items) shrinkOrExpand(1);
            int place = (key % size);
            dataNode<int, D>* new_n = new (std::nothrow) dataNode<int, D>(key, data);
            if(!new_n) throw OutOfMemory();
            if(isInit(place)){
                new_n->setNext(array[place]);
                array[place] = new_n;
            } else{
                toInit(place);
                array[place] = new_n;
            }
            items++;
        }
        void remove(int key){
            if( size/4 >= items) shrinkOrExpand(0);
            int place = (key % size);
            if(isInit(place)){
                if(array[place]->getKey() == key){
                    dataNode<int, D>* tmp = array[place]->getNext;
                    delete array[place];
                    items--;
                    array[place] = tmp;
                }else{
                    for (dataNode<int, D>* prev = array[place] , curr; prev; prev = prev->getNext()) {
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
            emptyAnArray(a, b, array, size);
            delete [] a;
            delete [] b;
            delete [] array;
        }
    };
};





#endif /* hash_table_hpp */

