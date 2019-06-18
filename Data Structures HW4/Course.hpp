//
//  Course.hpp
//  Data Structures HW2
//
//  Created by Ezzat Qupty on 05/05/2019.
//  Copyright © 2019 Ezzat Qupty. All rights reserved.
//

#ifndef Course_hpp
#define Course_hpp

#include "AVL.hpp"
#include "modifiedAVL.hpp"
#include "Lecture_Info.hpp"

namespace DataStructures{

	class course{
		int courseID;
		int StudentNum;
		int LectureNum;
		AVLTree<LectureInfo, int>* lectures; //the 2nd int is the groupID;
		modifiedAVLTree* students;
		
	public:
        course() : StudentNum(0), LectureNum(0), courseID(0), lectures(nullptr), students(nullptr){}
		course(int number): StudentNum(0), LectureNum(0), courseID(number), lectures(nullptr), students(nullptr){
			try{
			lectures = new AVLTree<LectureInfo, int>();
			students = new modifiedAVLTree();
			} catch (std::bad_alloc e){throw OutOfMemory();}
		}
        course(course& newCourse){
            this->courseID = newCourse.courseID;
			this->StudentNum = newCourse.StudentNum;
			this->LectureNum = newCourse.LectureNum;
			try {
				lectures = new AVLTree<LectureInfo, int>(*newCourse.getLectures());
				students = new modifiedAVLTree(*newCourse.getStudents());
			} catch (std::bad_alloc e){throw OutOfMemory();}
		}
			
		course& operator=(course& newCourse){
			if(*this == newCourse) return *this;
			if(lectures) delete lectures;
			if(students) delete students;
			this->courseID = newCourse.courseID;
			this->StudentNum = newCourse.StudentNum;
			this->LectureNum = newCourse.LectureNum;
			try {
				lectures = new AVLTree<LectureInfo, int>(*newCourse.getLectures());
				students = new modifiedAVLTree(*newCourse.getStudents());
			} catch (std::bad_alloc e){throw OutOfMemory();}
			return *this;
        }
		
        void addLecture(const lecture& lect){
			try{
				lectures->insert(LectureInfo(lect.getGroup(), lect.getHour()),courseID);
				students->insert(lect, lect.getNumStudents());
			} catch(AlreadyExists e) {throw Failure();}
			StudentNum += lect.getNumStudents();
			LectureNum++;
        }
		
		void removeLecture(const lecture& lect){
			if(students->remove(lect) == 0) throw Failure();
			lectures->remove(LectureInfo(lect.getGroup(), lect.getHour()));
			StudentNum -= lect.getNumStudents();
			LectureNum--;
			
        }
		
		void mergeCourses(course& other);///////////
		
		int competition(course& other, int numGroups){
			int thisMax = students->findMaxStudents(numGroups);
			int otherMax = other.students->findMaxStudents(numGroups);
			if(thisMax < otherMax) return other.courseID;
			else return this->courseID;
		}
		
		float getAverageStudents() const{
			return static_cast<float>(StudentNum)/static_cast<float>(LectureNum);
		}
		
		int getCourseID()const{ return courseID; }
		
        void setCourseID(int newID){courseID = newID; }
		
        AVLTree<LectureInfo, int>* getLectures() const { return lectures; }
		
		modifiedAVLTree* getStudents() const {return students;}
		
        void setLectures(AVLTree<LectureInfo, int>* newSchedule){
            delete lectures;
            //lectures = new  AVLTree<LectureInfo, int>(*newSchedule);
            lectures = newSchedule;
        }
        int getLecNum(){return lectures->getNodeCount();};
		
		bool operator==(const course& c){
			return (courseID == c.courseID);
		}
		bool operator>(const course& c){
			return (courseID > c.courseID);
		}
		bool operator<(const course& c){
			return (courseID < c.courseID);
		}
		bool operator>=(const course& c){
			return (courseID >= c.courseID);
		}
		bool operator<=(const course& c){
			return (courseID <= c.courseID);
		}
        ~course(){delete lectures;}
	};
	
}


#endif /* Course_hpp */
