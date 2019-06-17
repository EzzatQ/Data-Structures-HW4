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
		AVLTree<LectureInfo, int>* lectures;
		modifiedAVLTree* students;
		
	public:
        course() :courseID(0), lectures(nullptr){}
		course(int number): courseID(number), lectures(nullptr){
			lectures = new (std::nothrow) AVLTree<LectureInfo, int>();
			if(!lectures) throw OutOfMemory();
			try{ students = new modifiedAVLTree();} catch (std::bad_alloc e){throw OutOfMemory();}
		}
        course(course& newCourse){
            courseID = newCourse.getCourseID();
			try {
				lectures = new AVLTree<LectureInfo, int>(*newCourse.getlectures());
				students = new modifiedAVLTree(*newCourse.getStudents());
			} catch (std::bad_alloc e){throw OutOfMemory();}
		}
			
		course& operator=(course& newCourse){
			if(lectures) delete lectures;
			if(students) delete students;
			this->course::course(newCourse);
			return *this;
        }
		
        void addLecture(int hour, int room){
            lectures->insert(LectureInfo(hour,room),courseID);
        }
		
        void removeLecture(int hour, int room){
            // should check if it throws and exception
            lectures->remove(LectureInfo(hour,room));
        }
		int getCourseID()const{ return courseID; }
        void setCourseID(int newID){courseID = newID; }
        AVLTree<LectureInfo, int>* getlectures()const{ return lectures; }
        void setlectures(AVLTree<LectureInfo, int>* newSchedule){
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
