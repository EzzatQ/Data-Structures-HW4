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
#include "hash_table.hpp"
#include "unionFind.hpp"
#include "Course.hpp"
#include "Exceptions.hpp"

namespace DataStructures {
	class modSchedule{
		int courseNum;
		unionFind<course>* courses;
		hashTable<lecture>** schedule;// hour and then room
		
	public:
		
		modSchedule(int n): courseNum(n), courses(nullptr), schedule(nullptr){
			try{
				schedule = new hashTable<lecture>*[10];
				for (int j = 0; j < 10; j++) {
					schedule[j] = new hashTable<lecture>;
				}
				course** arr = new course*[n];
				for (int i = 1; i <= n; i++) {
					course* temp = new course(i);
					arr[i-1] = temp;
//                    delete temp; what?
				}
				courses = new unionFind<course>(n,arr);
                for (int i = 1; i <= n; i++) {
                    delete arr[i-1];
                }
				delete [] arr;
			} catch(std::bad_alloc e){ throw OutOfMemory();}
		}
		
		~modSchedule(){
			for (int i = 0; i < 10; i++) {
				delete schedule[i];
			}
			delete [] schedule;
			delete courses;
		}
		
		void addRoom(int roomId){
			if(roomId <= 0) throw InvalidInput();
			lecture* temp;
			try{
				for (int i = 0; i < 10; i++) {
					temp = new lecture();
					schedule[i]->insert(roomId, *temp);
					delete temp;
				}
			} catch(AlreadyExists e){ delete temp; throw Failure();}
			
		}
		void deleteRoom(int roomId){
			if(roomId <= 0) throw InvalidInput();
			int flag = 0;
			for (int i = 0; i < 10; i++) {
				if(schedule[i]->find(roomId) == lecture()) flag++;
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
			lecture booked = schedule[hour - 1]->find(roomId);
			if(booked != lecture()) throw Failure();
			try{
				lecture newLect = lecture(courseId, groupId, roomId, hour, numStudents);
				try{
					course* CRS = courses->getData(courses->find(courseId));
					try{
						CRS->addLecture(newLect);
					} catch(AlreadyExists e){ throw Failure();}
					schedule[hour - 1]->setData(roomId, newLect);//////// check this and change it
				} catch (DoesNotExist e){ throw Failure();}
			} catch (std::bad_alloc e) {throw OutOfMemory();}
		}
		
		void deleteLecture(int hour, int roomId){
			if(roomId <= 0 || hour < 1 || hour > 10) throw InvalidInput();
			lecture booked = schedule[hour - 1]->find(roomId);
			if(booked == lecture()) throw Failure();
			course* CRS = courses->getData(courses->find(booked.getCourse()));
			lecture* temp = new lecture();
			schedule[hour - 1]->setData(roomId, *temp);
			delete temp;
			CRS->removeLecture(booked);
			
		}
		
		void mergeCourses(int course1, int course2){
			if(course1 < 1 || course1 > courseNum || course2 < 1 || course2 > courseNum) throw InvalidInput();
			if(courses->find(course1) == courses->find(course2)) throw Failure();
			course* C1 = courses->getData(courses->find(course1));
			course* C2 = courses->getData(courses->find(course2));
			if(courses->getSize(course1) < courses->getSize(course2)) C2->merge(*C1);
			else C1->merge(*C2);
			courses->unite(course1, course2);
		}
		
		int competition(int courseID1, int courseID2, int numGroups) const {
			if(numGroups <= 0 || courseID1 < 1 || courseID1 > courseNum ||courseID2 < 1 || courseID2 > courseNum) throw InvalidInput();
			course* C1 = courses->getData(courses->find(courseID1));
			course* C2 = courses->getData(courses->find(courseID2));
			return C1->competition(*C2, numGroups) == C1->getCourseID() ? courseID1 : courseID2;
		}
		
		float getAverageStudent(int hour, int roomId) const {
			if(roomId<= 0 || hour < 1 || hour > 10) throw InvalidInput();
			lecture booked = schedule[hour - 1]->find(roomId);
			if(booked == lecture()) throw Failure();
			course* C = courses->getData(courses->find(booked.getCourse()));
			return C->getAverageStudents();
		}
		
	};
}
#endif /* modSched_hpp */
