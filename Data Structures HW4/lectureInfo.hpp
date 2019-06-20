//
//  lectureInfo.hpp
//  modified_AVL
//
//  Created by Hasan Egbarie on 15/06/2019.
//  Copyright © 2019 Hasan Egbarie. All rights reserved.
//

#ifndef lectureInfo_hpp
#define lectureInfo_hpp

#include <stdio.h>

namespace DataStructures{
    class lecture{
        int courseId;
        int groupId;
        int roomId;
        int hour;
        int numStudents;
    public:
		lecture(): courseId(-1), groupId(-1), roomId(-1), hour(-1), numStudents(-1){}
		
        lecture(int courseId, int groupId, int roomId, int hour, int numStudents):courseId(courseId), groupId(groupId), roomId(roomId), hour(hour), numStudents(numStudents){
            if(courseId < 0 || groupId < 0 || roomId <= 0 || hour < 0 || numStudents < 0)
                throw IllegalInitialization();
        }
        lecture(const lecture& a){
            courseId = a.courseId;
            groupId = a.groupId;
            roomId = a.roomId;
            hour = a.hour;
            numStudents = a.numStudents;
        }
        lecture& operator=(lecture& li){
            courseId = li.courseId;
            groupId = li.groupId;
            roomId = li.roomId;
            hour = li.hour;
            numStudents = li.numStudents;
            return *this;
        }
		
		int getCourse() const {return courseId;}
		int getGroup() const {return groupId;}
		int getRoom() const {return roomId;}
		int getHour() const {return hour;}
		int getNumStudents() const {return numStudents;}
		
        bool operator==(const lecture& li) const {
            return (groupId == li.groupId && roomId == li.roomId && hour == li.hour && numStudents == li.numStudents);
        }
		
		bool operator!=(const lecture& li) const {
			return !(this->operator==(li));
		}
		
        bool operator>(const lecture& li) const {
            if(numStudents > li.numStudents) return true;
            if(numStudents == li.numStudents && groupId > li.groupId) return true;
            if(numStudents == li.numStudents && groupId == li.groupId && roomId > li.roomId) return true;
            if(numStudents == li.numStudents && groupId == li.groupId && roomId == li.roomId && hour > li.hour) return true;
            if(numStudents == li.numStudents && groupId == li.groupId && roomId == li.roomId && hour == li.hour && courseId > li.courseId) return true;
            return false;
        }
        bool operator<(const lecture& li) const {
            if(numStudents < li.numStudents) return true;
            if(numStudents == li.numStudents && courseId < li.courseId) return true;
            if(numStudents == li.numStudents && groupId == li.groupId && roomId < li.roomId) return true;
            if(numStudents == li.numStudents && groupId == li.groupId && roomId == li.roomId && hour < li.hour) return true;
            if(numStudents == li.numStudents && groupId == li.groupId && roomId == li.roomId && hour == li.hour && courseId < li.courseId) return true;
            return false;
        }
        bool operator>=(const lecture& li) const {
            return operator>(li) || operator==(li);
        }
        bool operator<=(const lecture& li) const {
            return operator<(li) || operator==(li);
        }
        ~lecture(){}
    };
}


#endif /* lectureInfo_hpp */
