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
		AVLTree<LectureInfo, int>* lectures;
		modifiedAVLTree* students;
		
	public:
        course() :courseID(0), lectures(nullptr){}
		course(int number): StudentNum(0), LectureNum(0), courseID(number), lectures(nullptr){
			lectures = new (std::nothrow) AVLTree<LectureInfo, int>();
			if(!lectures) throw OutOfMemory();
			try{ students = new modifiedAVLTree();} catch (std::bad_alloc e){throw OutOfMemory();}
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
			if(courseID == newCourse.courseID) return *this;
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
		
        void addLecture(int groupID, int roomID, int hour, int numStudents){///////////
            lectures->insert(LectureInfo(hour,roomID),courseID);
			students->insert(lecture(courseID, groupID, roomID, hour, numStudents), <#int data#>);
			StudentNum += numStudents;
			LectureNum++;
			
        }
		
		void removeLecture(int hour, int room){////////
            // should check if it throws and exception
            lectures->remove(LectureInfo(hour,room));
        }
		
		void mergeCourses(course& other);///////////
		
		int competition(course& other);/////////////
		
		int getAverageStudents() const;/////////////
		
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
