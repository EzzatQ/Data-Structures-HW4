//
//  modSched.hpp
//  Data Structures HW4
//
//  Created by Hasan Egbarie on 16/06/2019.
//  Copyright © 2019 Ezzat Qupty. All rights reserved.
//

#ifndef modSched_hpp
#define modSched_hpp

#include <stdio.h>
#include <iostream>
#include "modifiedAVL.hpp"
#include "hash_table.hpp"
#include "unionFind.hpp"

namespace DataStructures {
    class modSchedule{
        unionFind<modifiedAVLTree>* courses;
        hashTable<lecture*>** lectures; // hour and then room
    public:
        modSchedule(int n):courses(nullptr),lectures(nullptr){
            lectures = new hashTable<lecture*>*[10];
            for (int j = 0; j < 10; j++) {
                lectures[j] = new hashTable<lecture*>;
            }
            modifiedAVLTree * arr = new modifiedAVLTree[n];
            for (int i = 0; i < n; i++) {
                arr[i] = modifiedAVLTree();
            }
            courses = new unionFind<modifiedAVLTree>(n,arr);
            delete [] arr;
        }
        ~modSchedule(){
            for (int i = 0; i < 10; i++) {
                delete lectures[i];
            }
            delete lectures;
            delete courses;
        }
        void addRoom(int roomId){
            if(roomId <= 0) throw InvalidInput();
            for (int i = 0; i < 10; i++) {
                lectures[i]->insert(roomId, nullptr);
            }
        }
        void deleteRoom(int roomId){
            if(roomId <= 0) throw InvalidInput();
            int flag =0;
            for (int i = 0; i < 10; i++) {
                if(!lectures[i]->find(roomId)->getData()) flag++;
            }
            if (flag != 10) {
                throw Failure();
            }
            for (int i = 0; i < 10; i++) {
                lectures[i]->remove(roomId);
            }
        }
        void addLecture(int courseId, int groupId, int roomId, int hour, int numStudents){
            lectures[hour]->find(roomId);
            courses->find(courseId);
        }
    };
}
#endif /* modSched_hpp */
