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
        lecture(int courseId, int groupId, int roomId, int hour, int numStudents):courseId(courseId), groupId(groupId), roomId(roomId), hour(hour), numStudents(numStudents){
            if(courseId < 0 || groupId < 0 || roomId < 0 || hour < 0 || numStudents <=0)
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
        bool operator==(const lecture& li) const {
<<<<<<< HEAD
            return (courseId == li.courseId && groupId == li.groupId && roomId == li.roomId && hour == li.hour && numStudents == li.numStudents);
=======
            return (groupId == li.groupId && roomId == li.roomId && hour == li.hour && numStudents == li.numStudents);
>>>>>>> 75753f2cf557e91294dbdc321f60551ef5b087e6
        }
        bool operator>(const lecture& li) const {
            if(numStudents > li.numStudents) return true;
            if(numStudents == li.numStudents && courseId > li.courseId) return true;
<<<<<<< HEAD
            if(numStudents == li.numStudents && courseId == li.courseId && groupId > li.groupId) return true;
            if(numStudents == li.numStudents && courseId == li.courseId && groupId == li.groupId && roomId > li.roomId) return true;
            if(numStudents == li.numStudents && courseId == li.courseId && groupId == li.groupId && roomId == li.roomId && hour > li.hour) return true;
=======
            if(numStudents == li.numStudents && groupId == li.groupId && roomId > li.roomId) return true;
            if(numStudents == li.numStudents && groupId == li.groupId && roomId == li.roomId && hour > li.hour) return true;
>>>>>>> 75753f2cf557e91294dbdc321f60551ef5b087e6
            return false;
        }
        bool operator<(const lecture& li) const {
            if(numStudents < li.numStudents) return true;
            if(numStudents == li.numStudents && courseId < li.courseId) return true;
<<<<<<< HEAD
            if(numStudents == li.numStudents && courseId == li.courseId && groupId < li.groupId) return true;
            if(numStudents == li.numStudents && courseId == li.courseId && groupId == li.groupId && roomId < li.roomId) return true;
            if(numStudents == li.numStudents && courseId == li.courseId && groupId == li.groupId && roomId == li.roomId && hour < li.hour) return true;
=======
            if(numStudents == li.numStudents && groupId == li.groupId && roomId < li.roomId) return true;
            if(numStudents == li.numStudents && groupId == li.groupId && roomId == li.roomId && hour < li.hour) return true;
>>>>>>> 75753f2cf557e91294dbdc321f60551ef5b087e6
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
