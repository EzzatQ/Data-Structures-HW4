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

using namespace DataStructures;

void* Init(int n){
	if(n < 1) return NULL;
	try{
		modSchedule* DS = new (std::nothrow) modSchedule(n);
		return (void*)DS;
	} catch(OutOfMemory e){
		return NULL;
	}
}

StatusType addRoom(void *DS, int roomID){
	if(!DS || roomID <= 0) return INVALID_INPUT;
	try{
		((modSchedule*)DS)->addRoom(roomID);
	}
	catch(InvalidInput e){ return INVALID_INPUT;}
	catch(OutOfMemory e){return ALLOCATION_ERROR;}
	catch(Failure e){return FAILURE;}
	return SUCCESS;
}

StatusType deleteRoom(void *DS, int roomID){
	if(!DS) return INVALID_INPUT;
	try{
		((modSchedule*)DS)->deleteRoom(roomID);
	}
	catch(InvalidInput e){ return INVALID_INPUT;}
	catch(Failure e){return FAILURE;}
	return SUCCESS;
}

StatusType addLecture(void *DS, int courseID, int groupID, int roomID, int hour, int numStudents){
	if(!DS) return INVALID_INPUT;
	try{
		((modSchedule*)DS)->addLecture(courseID, groupID, roomID, hour, numStudents);
	}
	catch(InvalidInput e){ return INVALID_INPUT;}
	catch(OutOfMemory e){return ALLOCATION_ERROR;}
	catch(Failure e){return FAILURE;}
	return SUCCESS;
}

StatusType deleteLecture(void *DS, int hour, int roomID){
	if(!DS) return INVALID_INPUT;
	try{
		((modSchedule*)DS)->deleteLecture(hour, roomID);
	}
	catch(InvalidInput e){ return INVALID_INPUT;}
	catch(Failure e){return FAILURE;}
	return SUCCESS;
}

StatusType mergeCourses(void *DS, int courseID1, int courseID2){
	if(!DS) return INVALID_INPUT;
	try{
		((modSchedule*)DS)->mergeCourses(courseID1, courseID2);
	}
	catch(InvalidInput e){ return INVALID_INPUT;}
	catch(OutOfMemory e){return ALLOCATION_ERROR;}
	catch(Failure e){return FAILURE;}
	return SUCCESS;
}

StatusType competition(void *DS, int courseID1, int courseID2, int numGroups, int * winner){
	if(!DS) return INVALID_INPUT;
	try{
		*winner = ((modSchedule*)DS)->competition(courseID1, courseID2, numGroups);
	}
	catch(InvalidInput e){ return INVALID_INPUT;}
	catch(OutOfMemory e){return ALLOCATION_ERROR;}
	catch(Failure e){return FAILURE;}
	return SUCCESS;
}

StatusType getAverageStudentsInCourse(void *DS, int hour, int roomID, float * average){
	if(!DS) return INVALID_INPUT;
	try{
		*average = ((modSchedule*)DS)->getAverageStudent(hour, roomID);
	}
	catch(InvalidInput e){ return INVALID_INPUT;}
	catch(OutOfMemory e){return ALLOCATION_ERROR;}
	catch(Failure e){return FAILURE;}
	return SUCCESS;
}

void Quit(void** DS){
	if(*DS){
		delete (modSchedule*)(*DS);
	}
}
