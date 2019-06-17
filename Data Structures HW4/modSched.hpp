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
#include "Course.hpp"

namespace DataStructures {
    class modSchedule{
		
        unionFind<course>* courses;
        hashTable<lecture*>** schedule;// hour and then room
		int courseNum;
		
    public:
		
        modSchedule(int n): courseNum(n), courses(nullptr), schedule(nullptr){
			try{
				schedule = new hashTable<lecture*>*[10];
				for (int j = 0; j < 10; j++) {
					schedule[j] = new hashTable<lecture*>;
				}
				
				course * arr = new modifiedAVLTree[n];
				for (int i = 0; i < n; i++) {
					arr[i] = modifiedAVLTree();
				}
				courses = new unionFind<course>(n,arr);
				delete [] arr;
			} catch(std::bad_alloc e){ throw OutOfMemory();}
        }
        ~modSchedule(){
            for (int i = 0; i < 10; i++) {
                delete schedule[i];
            }
            delete schedule;
            delete courses;
        }
        void addRoom(int roomId){
            if(roomId <= 0) throw InvalidInput();
            for (int i = 0; i < 10; i++) {
                schedule[i]->insert(roomId, nullptr);
            }
        }
        void deleteRoom(int roomId){
            if(roomId <= 0) throw InvalidInput();
            int flag = 0;
            for (int i = 0; i < 10; i++) {
                if(!schedule[i]->find(roomId)) flag++;
            }
            if (flag != 10) {
                throw Failure();
            }
            for (int i = 0; i < 10; i++) {
                schedule[i]->remove(roomId);
            }
        }
        void addLecture(int courseId, int groupId, int roomId, int hour, int numStudents){
			if(groupId < 0 || courseId > courseNum || courseId < 1 || numStudents < 0 || roomId <= 0 || hour < 1 || hour > 10) throw InvalidInput();
			
			lecture* booking = schedule[hour]->find(roomId);
			if(booking) throw Failure();
			lecture* newLect = new lecture(courseId, groupId, roomId, hour, numStudents);
            modifiedAVLTree* courseTree = courses->getData(courses->find(courseId));
			if(courseTree->contains(*newLect)) 
        }
    };
}
#endif /* modSched_hpp */
