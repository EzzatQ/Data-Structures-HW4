//
//  library2.cpp
//  Data Structures HW4
//
//  Created by Ezzat Qupty on 11/06/2019.
//  Copyright © 2019 Ezzat Qupty. All rights reserved.
//

#include <stdio.h>
#include "modSched.hpp"
#include "library2.h"

void* Init(int n){
	
}

StatusType addRoom(void *DS, int roomID);

StatusType deleteRoom(void *DS, int roomID);

StatusType addLecture(void *DS, int courseID, int groupID, int roomID, int hour, int numStudents);

StatusType deleteLecture(void *DS, int hour, int roomID);

StatusType mergeCourses(void *DS, int courseID1, int courseID2);

StatusType competition(void *DS, int courseID1, int courseID2, int numGroups, int * winner);

StatusType getAverageStudentsInCourse(void *DS, int hour, int roomID, float * average);

void Quit(void** DS);

