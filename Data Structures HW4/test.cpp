#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;
#include "library2.h"


void Test_Init_And_Quit(){
    void* DS = Init(-1);
    assert(DS == nullptr);
    Quit(&DS);
    assert(DS == nullptr);
    DS = Init(0);
    assert(DS == nullptr);
    Quit(&DS);
    DS = Init(40);
    assert(DS != nullptr);
    Quit(&DS);
    DS = Init(1000);
    assert(DS != nullptr);
    Quit(&DS);
}
void Sagal_Test(){
    float avrage=0;
    void* DS = Init(2);
    assert(DS != nullptr);
    assert(addRoom(DS,5)==SUCCESS);
    assert(addRoom(DS,10)==SUCCESS);
    assert(deleteRoom(DS,10)==SUCCESS);
    assert(addLecture(DS,2,1,10,2,5)==FAILURE);
    assert(addLecture(DS,1,5,5,1,30)==SUCCESS);
    assert(addLecture(DS,2,3,5,2,20)==SUCCESS);
    assert(addRoom(DS,6)==SUCCESS);
    assert(addLecture(DS,2,1,6,5,5)==SUCCESS);
    assert(deleteLecture(DS,5,6)==SUCCESS);
    assert(mergeCourses(DS,1,2)==SUCCESS);
    assert(getAverageStudentsInCourse(DS,2,5,&avrage)==SUCCESS);
    assert(avrage==25);
    assert(getAverageStudentsInCourse(DS,1,5,&avrage)==SUCCESS);
    assert(avrage==25);
    Quit(&DS);
}

void Test_AddLecture(){

    void* DS = Init(5);
    assert(DS != nullptr);
    assert(addRoom(DS,5)==SUCCESS);
    assert(addRoom(DS,10)==SUCCESS);
    assert(addRoom(DS,12)==SUCCESS);
    assert(addRoom(DS,13)==SUCCESS);
    assert(addRoom(DS,2)==SUCCESS);
    assert(addRoom(DS,8)==SUCCESS);
    assert(addRoom(DS,7)==SUCCESS);
    assert(addRoom(DS,1)==SUCCESS);
    assert(addRoom(DS,11)==SUCCESS);
    assert(addRoom(DS,1)==FAILURE);
    assert(deleteRoom(DS,10)==SUCCESS);
    assert(deleteRoom(DS,11)==SUCCESS);
    assert(deleteRoom(DS,1)==SUCCESS);

    assert(addLecture(DS,2,1,10,2,5)==FAILURE);
    assert(addLecture(DS,2,1,1,2,5)==FAILURE);
    assert(addLecture(DS,2,1,11,2,5)==FAILURE);

    assert(addLecture(DS,1,5,5,1,30)==SUCCESS);
    assert(addLecture(DS,2,5,5,7,0)==SUCCESS);
    assert(addLecture(DS,2,5,5,1,-2)==INVALID_INPUT);
    assert(addLecture(DS,2,5,5,12,30)==INVALID_INPUT);
    assert(addLecture(DS,2,5,0,1,30)==INVALID_INPUT);
    assert(addLecture(DS,9,5,0,1,30)==INVALID_INPUT);
    assert(addLecture(DS,9,-1,0,1,30)==INVALID_INPUT);

    assert(addLecture(DS,1,5,2,1,25)==FAILURE);
    assert(addLecture(DS,1,5,2,1,10)==FAILURE);

    assert(addLecture(DS,2,3,5,2,20)==SUCCESS);
    assert(addLecture(DS,1,2,5,2,10)==FAILURE);
    assert(addLecture(DS,1,5,5,2,10)==FAILURE);
    assert(addLecture(DS,4,5,5,1,7)==FAILURE);
    assert(addLecture(DS,4,1,13,7,7)==SUCCESS);
    assert(addLecture(DS,4,1,13,7,7)==FAILURE);
    assert(addLecture(DS,4,1,12,7,7)==FAILURE);
    assert(addLecture(DS,4,7,8,6,7)==SUCCESS);
    assert(addLecture(DS,3,5,8,6,5)==FAILURE);
    assert(addLecture(DS,3,5,8,4,9)==SUCCESS);
    assert(addLecture(DS,4,7,12,5,43)==SUCCESS);
    assert(addLecture(DS,3,2,12,2,14)==SUCCESS);
    assert(addLecture(DS,3,41,12,3,5)==SUCCESS);
    assert(addLecture(DS,3,42,12,4,5)==SUCCESS);
    assert(addLecture(DS,2,8,13,9,12)==SUCCESS);

    Quit(&DS);
}

void Test_DeleteLecture(){
    void* DS = Init(20);
    assert(DS != nullptr);
    for(int i=1;i<=20;i++)
    {
        addRoom(DS,i);
    }
    assert(addLecture(DS,2,1,10,1,5)==SUCCESS);
    assert(addLecture(DS,2,1,10,2,5)==SUCCESS);
    assert(addLecture(DS,2,1,10,3,5)==SUCCESS);
    assert(addLecture(DS,2,1,10,4,10)==SUCCESS);
    assert(addLecture(DS,2,1,10,5,10)==SUCCESS);
    assert(addLecture(DS,2,3,9,3,5)==SUCCESS);
    assert(addLecture(DS,2,3,9,4,10)==SUCCESS);
    assert(addLecture(DS,2,3,9,5,10)==SUCCESS);
    assert(deleteLecture(DS,11,10)==INVALID_INPUT);
    assert(deleteLecture(nullptr,11,10)==INVALID_INPUT);
    assert(deleteLecture(DS,5,0)==INVALID_INPUT);
    assert(deleteLecture(DS,4,21)==FAILURE);
    assert(deleteLecture(DS,4,19)==FAILURE);
    assert(deleteRoom(DS,10)==FAILURE);
    for(int i=1;i<=4;i++)
    {
        assert(deleteLecture(DS,i,10)==SUCCESS);
    }
    assert(deleteRoom(DS,10)== FAILURE);
    assert(deleteLecture(DS,5,10)==SUCCESS);
    assert(deleteRoom(DS,10)==SUCCESS);
    assert(deleteLecture(DS,4,10)==FAILURE);
    addRoom(DS,21);
    for(int i=1;i<=5;i++)
    {
        assert(addLecture(DS,9,1,21,i,i+5)==SUCCESS);
    }
    Quit(&DS);
}
void Test_merge_courses(){

    void* DS = Init(20);
    assert(DS != nullptr);
    for(int i=1;i<=20;i++)
    {
        addRoom(DS,i);
    }

    for (int j = 1; j < 7; j++) {
        assert(addLecture(DS,2,1,1,j,5+j)==SUCCESS);
        assert(addLecture(DS,2,4,2,j,4+j)==SUCCESS);
    }

    for (int j = 7; j <= 10; j++) {
        assert(addLecture(DS,3,1,3,j,5+j)==SUCCESS);
        assert(addLecture(DS,3,4,2,j,4+j)==SUCCESS);
         }

    assert(mergeCourses(DS,21,3)==INVALID_INPUT);
    assert(mergeCourses(DS,2,0)==INVALID_INPUT);
    assert(mergeCourses(nullptr,2,3)==INVALID_INPUT);

    assert(addLecture(DS,3,1,3,2,5)==SUCCESS);
    assert(mergeCourses(DS,2,3)==FAILURE);
    assert(deleteLecture(DS,2,3)==SUCCESS);
    assert(mergeCourses(DS,2,3)==SUCCESS);
    assert(mergeCourses(DS,2,3)==FAILURE);
    assert(addLecture(DS,3,1,3,7,12)==FAILURE);
    assert(addLecture(DS,2,4,2,1,5)==FAILURE);

    for (int j = 1; j < 7; j++) {
        assert(addLecture(DS,4,2,6,j,5+j)==SUCCESS);
        assert(addLecture(DS,4,3,7,j,4+j)==SUCCESS);
    }

    for (int j = 7; j <= 10; j++) {
        assert(addLecture(DS,5,2,6,j,5+j)==SUCCESS);
        assert(addLecture(DS,5,3,7,j,4+j)==SUCCESS);
    }
    assert(mergeCourses(DS,4,5)==SUCCESS);
    assert(addLecture(DS,4,1,8,3,9)==SUCCESS);
    assert(mergeCourses(DS,4,3)==FAILURE);
    assert(deleteLecture(DS,3,8)==SUCCESS);
    assert(mergeCourses(DS,2,5)==SUCCESS);
    assert(mergeCourses(DS,5,3)==FAILURE);
    assert(addLecture(DS,5,1,8,7,12)==FAILURE);

    for(int i=40;i<=400;i++)
    {
        addRoom(DS,i);
    }
    for(int i=40;i<150;i++){
        for(int j=1;j<=10;j++){
            if(j<=5)
            assert(addLecture(DS,6,i,i,j,i+j)==SUCCESS);
            else
                assert(addLecture(DS,6,i,i,j,i)==SUCCESS);
        }
    }
    for(int i=150;i<300;i++){
        for(int j=1;j<=10;j++){
            if(j<=5)
            assert(addLecture(DS,7,i,i,j,i+j)==SUCCESS);
            else
                assert(addLecture(DS,7,i,i,j,i)==SUCCESS);
        }
    }
    assert(mergeCourses(DS,6,7)==SUCCESS);
    for(int i=300;i<400;i++) {
        assert(addLecture(DS, 7, i, i,4 , i / 5) == SUCCESS);
    }
    Quit(&DS);
}
void Test_competition_And_Average(){
    void* DS = Init(20);
    assert(DS != nullptr);
    int winner=0;
    int x=0;
    int y=0;
    float average;
    float check;
    float check2=0;
    float check3=0;
    for(int i=1;i<=301;i++)
    {
        addRoom(DS,i);
    }
    for(int i=1;i<200;i++){
        for(int j=1;j<=10;j++){
            if(j<=5) {
                assert(addLecture(DS, 6, i, i, j, i + j) == SUCCESS);
                x+=i+j;
            }
            else {
                assert(addLecture(DS, 6, i, i, j, i) == SUCCESS);
                x+=i;
            }

           y++;
        }
    }
    check=(float)x / y;
    assert(getAverageStudentsInCourse(DS,1,1,&average)== SUCCESS);
    assert(average==check);
    deleteLecture(DS,1,1);
    x-=2;
    y--;
    check=(float)x / y;
    check2+=x;
    check3+=y;
    assert(getAverageStudentsInCourse(DS,1,1,&average)== FAILURE);
    assert(getAverageStudentsInCourse(DS,2,1,&average)== SUCCESS);
    assert(average==check);
    assert(getAverageStudentsInCourse(nullptr,1,1,&average)== INVALID_INPUT);
    assert(getAverageStudentsInCourse(DS,20,1,&average)== INVALID_INPUT);
    assert(getAverageStudentsInCourse(DS,1,0,&average)== INVALID_INPUT);
    assert(getAverageStudentsInCourse(DS,0,5,&average)== INVALID_INPUT);
    assert(getAverageStudentsInCourse(DS,2,500,&average)== FAILURE);
    assert(getAverageStudentsInCourse(DS,2,301,&average)== FAILURE);
    x=0;
    y=0;
    for(int i=200;i<300;i++){
        for(int j=1;j<=10;j++){
            if(j<=5){
                assert(addLecture(DS,7,i,i,j,i+j)==SUCCESS);
                x+=i+j;
            }
            else {
                assert(addLecture(DS, 7, i, i, j, i) == SUCCESS);
                x+=i;
            }
            y++;
        }
    }
    check=(float)x / y;
    check2+=x;
    check3+=y;
    assert(getAverageStudentsInCourse(DS,1,200,&average)== SUCCESS);
    assert(average==check);
    assert(competition(DS,6,22,8,&winner)==INVALID_INPUT);
    assert(competition(DS,32,7,6,&winner)==INVALID_INPUT);
    assert(competition(nullptr,6,7,5,&winner)==INVALID_INPUT);
    assert(competition(nullptr,0,7,6,&winner)==INVALID_INPUT);
    assert(competition(nullptr,6,0,6,&winner)==INVALID_INPUT);
    assert(competition(nullptr,6,7,0,&winner)==INVALID_INPUT);
    for(int i=1;i<500;i++){
        assert(competition(DS,6,7,i,&winner)==SUCCESS);
        assert(winner==7);
    }
    assert(mergeCourses(DS,6,7)==SUCCESS);
    check= (float)check2/ check3;
    assert(getAverageStudentsInCourse(DS,1,200,&average)== SUCCESS);
    assert(average==check);
    assert(competition(DS,6,7,8,&winner)==FAILURE);
    Quit(&DS);

}
void Final_test(){
    void* DS = Init(20);
    assert(DS != nullptr);
    for(int i=1;i<=20;i++)
    {
        addRoom(DS,i);
    }
    assert(addLecture(DS,1,5,5,1,30)==SUCCESS);
    assert(addLecture(DS,2,3,5,2,20)==SUCCESS);
    assert(addLecture(DS,4,1,13,7,7)==SUCCESS);
    assert(addLecture(DS,4,7,8,6,7)==SUCCESS);
    assert(addLecture(DS,3,5,8,4,9)==SUCCESS);
    assert(addLecture(DS,4,7,12,5,43)==SUCCESS);
    assert(addLecture(DS,3,2,12,2,14)==SUCCESS);
    assert(addLecture(DS,3,41,12,3,5)==SUCCESS);
    assert(addLecture(DS,3,42,12,4,5)==SUCCESS);
    assert(addLecture(DS,2,8,13,9,12)==SUCCESS);
    int winner=0;
    competition(DS,4,2,2,&winner);
    assert(winner==4);
    competition(DS,3,2,3,&winner);
    assert(winner==2);
    competition(DS,3,2,4,&winner);
    assert(winner==3);
    competition(DS,3,2,3,&winner);
    assert(winner==2);
    deleteLecture(DS,13,12);
    competition(DS,3,2,4,&winner);
    assert(winner==3);
    assert(addLecture(DS,4,19,16,7,3)==SUCCESS);
    assert(mergeCourses(DS,3,2)==SUCCESS);
    competition(DS,3,4,5,&winner);
    assert(winner==4);
    assert(mergeCourses(DS,1,2)==SUCCESS);
    competition(DS,3,4,5,&winner);
    assert(winner==3);
    assert(competition(DS,1,3,5,&winner)==FAILURE);
    Quit(&DS);
}




int main(int argc, const char**argv) {

    void* d = Init(17);
    float res = 0;
    int winner = 0;
    deleteLecture(d, 3, 6);
    addRoom(d, 5);
    addRoom(d, -4);
    addLecture(d, 2, 5, 20, 8, 42);
    addRoom(d, 10);
    deleteRoom(d, 16);
    addRoom(d, 0);
    deleteRoom(d, 7);
    getAverageStudentsInCourse(d, 10, 7, &res);
    mergeCourses(d, 11, 15);
    deleteRoom(d, 4);
    getAverageStudentsInCourse(d, 4, 19, &res);
    addLecture(d, 3, 7, 17, 6, 37);
    deleteRoom(d, -5);
    addRoom(d, 2);
    addLecture(d, 40, 8, 12, 0, 35);
    getAverageStudentsInCourse(d, 8, 10, &res);
    competition(d, 26, 18, 1, &winner);
    addRoom(d, 4);
    deleteLecture(d, 5, -3);
    addLecture(d, 25, 5, 19, 4, 41);
    mergeCourses(d, 33, 4);
    addRoom(d, 6);
    addLecture(d, 4, 9, 2, 5, 1);
    addRoom(d, 6);
    addRoom(d, 1);
    mergeCourses(d, 28, 19);
    competition(d, 26, 23, 3, &winner);
    deleteLecture(d, 12, 0);
    addLecture(d, 26, 3, 9, 6, 5);
    deleteLecture(d, 4, 4);
    deleteLecture(d, 12, 19);
    addLecture(d, 24, 15, 13, 12, 22);
    deleteLecture(d, 1, 11);
    addRoom(d, 18);
    addRoom(d, 6);
    addLecture(d, 12, 6, 3, 12, 14);
    competition(d, 12, 7, 5, &winner);
    deleteLecture(d, 10, 7);
    deleteLecture(d, 1, -1);
    deleteRoom(d, 17);
    competition(d, 11, 16, 3, &winner);
    addLecture(d, 13, -1, 0, 3, 6);
    getAverageStudentsInCourse(d, 9, 3, &res);
    deleteRoom(d, 7);
    addRoom(d, 5);
    getAverageStudentsInCourse(d, 11, 15, &res);
    deleteRoom(d, 15);
    competition(d, 37, 34, 4, &winner);
    getAverageStudentsInCourse(d, 8, 9, &res);
    getAverageStudentsInCourse(d, 9, 13, &res);
    deleteRoom(d, 17);
    addRoom(d, 12);
    mergeCourses(d, 36, 25);
    addLecture(d, 1, -1, 3, 5, 7);
    competition(d, 24, 16, -1, &winner);
    addLecture(d, 7, 5, 0, 3, 20);
    addLecture(d, 31, 2, 18, 1, 30);
    addRoom(d, 7);
    addRoom(d, 0);
    addRoom(d, 13);
    addRoom(d, 7);
    deleteLecture(d, 3, 13);
    getAverageStudentsInCourse(d, 12, 4, &res);
    competition(d, 0, 35, 1, &winner);
    addRoom(d, 4);
    mergeCourses(d, 18, 0);
    addLecture(d, 4, 13, 18, 12, 24);
    addLecture(d, 22, 14, -1, 2, 50);
    deleteLecture(d, 12, 6);
    addLecture(d, 29, 4, 14, 4, 2);
    deleteRoom(d, 16);
    addRoom(d, 5);
    addLecture(d, 19, 3, 6, 8, 38);
    getAverageStudentsInCourse(d, 6, 16, &res);
    getAverageStudentsInCourse(d, 9, 20, &res);
    deleteLecture(d, 3, 15);
    addLecture(d, 21, 0, -1, 10, 8);
    addRoom(d, 2);
    getAverageStudentsInCourse(d, 3, -1, &res);
    addLecture(d, 23, 8, 13, 3, 0);
    deleteLecture(d, 5, 0);
    deleteLecture(d, 5, 14);
    mergeCourses(d, 32, 2);
    addRoom(d, 11);
    mergeCourses(d, 9, 40);
    getAverageStudentsInCourse(d, 3, 14, &res);
    addRoom(d, 19);
    mergeCourses(d, 38, 4);
    addRoom(d, -5);
    deleteLecture(d, 9, 19);
    getAverageStudentsInCourse(d, 7, 1, &res);
    addLecture(d, 33, 15, 2, 1, 13);
    addRoom(d, 16);
    addRoom(d, 5);
    addRoom(d, 19);
    deleteLecture(d, 6, -1);
    addLecture(d, 40, 11, 5, 11, 49);
    addLecture(d, 24, 4, 3, 11, 17);
    addLecture(d, 2, 10, 0, 7, 29);
    addLecture(d, 1, 10, 6, 5, 34);
    deleteRoom(d, 10);
    addLecture(d, 2, 13, 5, 7, 17);
    addLecture(d, 21, -1, 9, 4, 26);
    addLecture(d, -1, -1, 8, 3, 8);
    addLecture(d, 17, 4, 18, 7, 35);
    addRoom(d, 20);
    addLecture(d, 12, 6, 12, 1, 0);
    competition(d, 31, 13, 5, &winner);
    competition(d, 23, 19, 1, &winner);
    addLecture(d, 9, 13, 20, 8, 14);
    addLecture(d, 14, 12, 10, 8, 16);
    addLecture(d, 27, 9, 3, 9, 50);
    addRoom(d, 20);
    addLecture(d, 33, 3, 9, 8, 19);
    addRoom(d, 4);
    competition(d, 9, 40, 4, &winner);
    deleteRoom(d, -2);
    addLecture(d, 25, 7, 1, 4, 16);
    addRoom(d, -1);
    getAverageStudentsInCourse(d, 0, 6, &res);
    deleteRoom(d, 12);
    addLecture(d, 37, 14, 2, 11, 16);
    addLecture(d, 26, 12, -1, 7, 32);
    addLecture(d, 4, 14, 9, 9, 50);
    addRoom(d, -5);
    addLecture(d, 5, 14, 16, 3, 11);
    addLecture(d, 4, 15, 1, 1, 34);
    addLecture(d, 35, 5, 9, 8, 20);
    addLecture(d, 35, 12, 5, 10, 40);
    addRoom(d, 3);
    deleteRoom(d, 3);
    addLecture(d, 28, 2, -1, 1, 25);
    addRoom(d, -3);
    addRoom(d, -1);
    deleteRoom(d, 12);
    addLecture(d, -1, 5, 12, 7, 48);
    addRoom(d, -5);
    mergeCourses(d, 26, 12);
    addRoom(d, 15);
    addRoom(d, -3);
    addRoom(d, 17);
    getAverageStudentsInCourse(d, 3, 7, &res);
    addRoom(d, 17);
    addLecture(d, 0, 7, 0, 8, 26);
    competition(d, 30, 5, 2, &winner);
    addRoom(d, 14);
    deleteRoom(d, 6);
    addLecture(d, 25, 3, 20, 2, 4);
    getAverageStudentsInCourse(d, 10, -1, &res);
    mergeCourses(d, 32, 22);
    deleteLecture(d, 9, -2);
    addRoom(d, 15);
    addLecture(d, 32, 11, 13, 5, 6);
    mergeCourses(d, 13, 19);
    addRoom(d, 17);
    addRoom(d, 19);
    deleteRoom(d, 5);
    deleteLecture(d, 1, 2);
    addRoom(d, -3);
    addRoom(d, 8);
    addRoom(d, 12);
    addLecture(d, 21, 5, -1, 11, 16);
    mergeCourses(d, 29, 13);
    deleteRoom(d, -1);
    deleteLecture(d, 2, 16);
    addRoom(d, 13);
    addRoom(d, 17);
    deleteLecture(d, 2, 13);
    getAverageStudentsInCourse(d, 10, 4, &res);
    getAverageStudentsInCourse(d, 1, -4, &res);
    addRoom(d, -3);
    addRoom(d, 9);
    mergeCourses(d, 6, 24);
    addRoom(d, 2);
    getAverageStudentsInCourse(d, 0, 15, &res);
    deleteLecture(d, 1, 14);
    addLecture(d, 32, 3, 18, 0, 42);
    addLecture(d, 1, 0, 3, -1, 15);
    addLecture(d, 24, 10, 5, 12, 25);
    deleteLecture(d, 5, 4);
    addRoom(d, 12);
    deleteLecture(d, 1, 18);
    addRoom(d, 18);
    addRoom(d, 11);
    addRoom(d, 5);
    mergeCourses(d, 19, 39);
    getAverageStudentsInCourse(d, 12, 18, &res);
    addLecture(d, 13, 7, 20, 4, 44);
    addLecture(d, 28, 5, 9, 0, 45);
    addLecture(d, 14, 7, 11, 12, 5);
    addRoom(d, 11);
    competition(d, 38, 36, 4, &winner);
    addRoom(d, 1);
    deleteRoom(d, 15);
    addLecture(d, 34, 4, 18, 9, 29);
    addRoom(d, -3);
    deleteLecture(d, 4, 5);
    mergeCourses(d, 20, 20);
    competition(d, 9, 6, 0, &winner);
    mergeCourses(d, 21, 5);
    addLecture(d, 29, 11, 19, 0, 8);
    deleteRoom(d, 16);
    mergeCourses(d, 31, 11);
    addRoom(d, 8);
    deleteLecture(d, -1, -3);
    addRoom(d, 0);
    addLecture(d, 34, 9, 5, 9, 28);
    addRoom(d, 3);
    deleteLecture(d, 5, 15);
    getAverageStudentsInCourse(d, 11, 11, &res);
    addRoom(d, 11);
    competition(d, 26, 10, 1, &winner);
    competition(d, 28, 8, 1, &winner);
    deleteRoom(d, -5);
    addLecture(d, 25, 9, 8, 8, 28);
    addRoom(d, 11);
    deleteRoom(d, 16);
    addLecture(d, 29, 15, -1, -1, 39);
    getAverageStudentsInCourse(d, 3, 16, &res);
    addLecture(d, 33, 5, -1, 2, 13);
    deleteLecture(d, 8, -3);
    addRoom(d, 20);
    deleteLecture(d, 2, 11);
    addRoom(d, 9);
    mergeCourses(d, 14, 22);
    addRoom(d, 13);
    addLecture(d, 14, 5, 14, -1, 11);
    addRoom(d, 18);
    addLecture(d, 28, 6, 14, 7, 11);
    addLecture(d, 38, 13, -1, 10, 13);
    addRoom(d, 17);
    deleteLecture(d, 1, 12);
    addLecture(d, 20, 2, 2, 5, 42);
    addRoom(d, 18);
    addRoom(d, 13);
    addLecture(d, 31, 5, 6, 3, 48);
    deleteLecture(d, 1, 3);
    deleteLecture(d, -1, 6);
    mergeCourses(d, 12, 4);
    deleteLecture(d, 12, -4);
    deleteRoom(d, 7);
    addLecture(d, 14, -1, 14, 8, 45);
    addLecture(d, 35, 3, 20, 3, -1);
    addLecture(d, 0, 7, 2, -1, 10);
    addLecture(d, 18, 11, 4, 4, 19);
    mergeCourses(d, 36, 14);
    addLecture(d, 27, 11, 8, 2, 36);
    addRoom(d, 5);
    competition(d, 39, 32, 3, &winner);
    addLecture(d, -1, 3, 1, 10, 38);
    deleteLecture(d, 10, 12);
    addLecture(d, 33, 2, 8, 12, 14);
    addLecture(d, 22, 12, 3, -1, 41);
    addRoom(d, 17);
    addRoom(d, 0);
    addRoom(d, 15);
    addLecture(d, 26, 7, 4, 10, 26);
    deleteLecture(d, 5, -4);
    addLecture(d, 32, 9, 14, 2, 14);
    addRoom(d, 20);
    deleteLecture(d, 6, 16);
    deleteLecture(d, 6, -2);
    addRoom(d, 19);
    mergeCourses(d, 2, 31);
    addRoom(d, 20);
    addLecture(d, 13, 13, 10, 10, 32);
    addLecture(d, 26, 13, 9, 5, 8);
    addLecture(d, 25, 13, 8, 0, 0);
    addLecture(d, 35, 10, 8, 2, 10);
    addRoom(d, -1);
    addRoom(d, 15);
    addRoom(d, -5);
    mergeCourses(d, 27, 38);
    addRoom(d, -2);
    addRoom(d, 1);
    addRoom(d, 5);
    addLecture(d, 15, 15, 15, 9, -1);
    addRoom(d, -1);
    addLecture(d, 6, 3, 13, 5, 5);
    competition(d, 30, 36, 3, &winner);
    addLecture(d, 8, 11, 16, 1, 8);
    getAverageStudentsInCourse(d, 5, 13, &res);
    addRoom(d, 9);
    getAverageStudentsInCourse(d, 8, -2, &res);
    addLecture(d, 27, 9, 8, 12, 15);
    mergeCourses(d, 17, 19);
    addRoom(d, 10);
    addLecture(d, 4, 4, 6, 12, 48);
    addRoom(d, 11);
    addRoom(d, 4);
    addRoom(d, -5);
    competition(d, 1, 10, 0, &winner);
    addLecture(d, 14, -1, 13, 5, 16);
    mergeCourses(d, 25, 24);
    addLecture(d, 21, 6, 9, 7, 30);
    addRoom(d, 20);
    addRoom(d, 13);
    addRoom(d, -2);
    deleteLecture(d, 12, 11);
    addLecture(d, -1, 10, 10, -1, 4);
    mergeCourses(d, 9, 0);
    addRoom(d, 17);
    addRoom(d, 13);
    getAverageStudentsInCourse(d, 8, 19, &res);
    addLecture(d, 9, 12, 16, 12, 10);
    deleteRoom(d, 14);
    mergeCourses(d, 4, 26);
    deleteLecture(d, 0, 15);
    mergeCourses(d, 16, 1);
    deleteLecture(d, 11, 20);
    deleteRoom(d, 14);
    getAverageStudentsInCourse(d, 3, -4, &res);
    getAverageStudentsInCourse(d, 0, 7, &res);
    addRoom(d, -5);
    deleteRoom(d, 16);
    addLecture(d, 35, 1, 8, 5, 22);
    deleteRoom(d, 18);
    addRoom(d, 8);
    getAverageStudentsInCourse(d, 12, 1, &res);
    addRoom(d, 5);
    competition(d, 22, 8, 4, &winner);
    addRoom(d, -1);
    addRoom(d, 14);
    competition(d, 21, 40, 2, &winner);
    competition(d, 24, 29, 7, &winner);
    addLecture(d, 27, 1, 2, 10, 21);
    mergeCourses(d, 35, 11);
    addLecture(d, 34, 9, 3, 11, 35);
    addLecture(d, 30, 15, 12, 9, 32);
    addLecture(d, 34, 5, 9, 5, 49);
    addLecture(d, 30, 3, 19, 12, 26);
    getAverageStudentsInCourse(d, 2, 4, &res);
    deleteRoom(d, 6);
    competition(d, 8, 9, 2, &winner);
    addLecture(d, 7, 11, 2, 1, 17);
    getAverageStudentsInCourse(d, 4, -1, &res);
    addLecture(d, 15, 13, 13, 7, 39);
    getAverageStudentsInCourse(d, 1, -5, &res);
    competition(d, 5, 1, 3, &winner);
    addRoom(d, 20);
    addLecture(d, 6, -1, 5, 3, 20);
    addLecture(d, 26, 8, -1, 12, 32);
    addLecture(d, 3, 4, 9, 8, 43);
    competition(d, 22, 11, 3, &winner);
    addRoom(d, 9);
    deleteLecture(d, 10, 18);
    addLecture(d, 16, 14, 18, 3, 25);
    addRoom(d, 7);
    addRoom(d, 7);
    deleteRoom(d, 2);
    competition(d, 9, 29, 3, &winner);
    competition(d, 12, 23, -1, &winner);
    addLecture(d, 22, 7, 12, 7, 10);
    addLecture(d, 20, 5, 19, 9, 18);
    deleteRoom(d, 0);
    competition(d, 26, 12, 3, &winner);
    addRoom(d, -4);
    getAverageStudentsInCourse(d, 1, 10, &res);
    addLecture(d, 32, 14, 8, 8, 1);
    deleteRoom(d, 4);
    addLecture(d, 28, 8, 6, -1, 9);
    deleteRoom(d, 1);
    deleteRoom(d, 17);
    addRoom(d, 7);
    addLecture(d, 32, 8, 10, 10, 20);
    addRoom(d, 4);
    getAverageStudentsInCourse(d, 10, 0, &res);
    addLecture(d, 19, 4, 16, 0, 37);
    addRoom(d, -3);
    addRoom(d, 16);
    deleteRoom(d, 8);
    competition(d, 34, 11, 3, &winner);
    mergeCourses(d, 30, 16);
    deleteRoom(d, 13);
    addLecture(d, 16, 1, 17, 1, 42);
    mergeCourses(d, 4, 7);
    addLecture(d, 13, 15, 18, 1, 0);
    addLecture(d, 26, 14, 0, 9, 4);
    addLecture(d, 28, 14, 15, 6, 11);
    addLecture(d, 37, 6, 15, 3, 35);
    addRoom(d, -5);
    addLecture(d, 39, 14, 8, 7, 27);
    addRoom(d, 2);
    getAverageStudentsInCourse(d, 11, 12, &res);
    addLecture(d, 28, 15, 15, 4, 45);
    addRoom(d, 7);
    addLecture(d, 9, 2, 3, 8, 49);
    addLecture(d, 25, 12, 4, 10, 13);
    mergeCourses(d, 9, 18);
    addRoom(d, 5);
    addRoom(d, 4);
    mergeCourses(d, 14, 37);
    mergeCourses(d, 7, 5);
    addLecture(d, 30, 10, 11, 8, 20);
    deleteRoom(d, -3);
    addLecture(d, 23, 5, 2, 5, 44);
    deleteLecture(d, 0, 1);
    addLecture(d, 31, 0, 3, 5, 18);
    mergeCourses(d, 35, 31);
    addRoom(d, 15);
    deleteLecture(d, 2, 14);
    addLecture(d, 30, 3, 6, 1, 32);
    getAverageStudentsInCourse(d, 3, 5, &res);
    addLecture(d, 7, 12, 1, -1, 11);
    addRoom(d, 3);
    mergeCourses(d, 0, 33);
    addLecture(d, 3, 5, 4, 1, 5);
    deleteRoom(d, 18);
    getAverageStudentsInCourse(d, 12, 8, &res);
    addRoom(d, 9);
    addLecture(d, 4, 12, 12, 6, 40);
    deleteLecture(d, 7, -2);
    addLecture(d, 29, 11, 17, 3, 44);
    addRoom(d, 4);
    addLecture(d, 24, 13, 4, 11, 13);
    addLecture(d, 10, 5, 2, 12, 0);
    addRoom(d, 20);
    deleteRoom(d, 15);
    mergeCourses(d, 32, 28);
    addLecture(d, 28, 8, 19, 1, 38);
    addRoom(d, 6);
    addRoom(d, 7);
    addLecture(d, 25, 9, 19, 4, 25);
    addRoom(d, 12);
    addRoom(d, 5);
    getAverageStudentsInCourse(d, 2, 4, &res);
    getAverageStudentsInCourse(d, 12, 11, &res);
    addLecture(d, 2, 10, 20, 5, 2);
    getAverageStudentsInCourse(d, 9, 9, &res);
    getAverageStudentsInCourse(d, 4, 1, &res);
    deleteRoom(d, 6);
    addLecture(d, 34, 11, 19, 9, 48);
    addLecture(d, 17, 15, 0, 7, 19);
    competition(d, 2, 4, 6, &winner);
    addLecture(d, 1, 0, 3, 8, 30);
    competition(d, 33, 2, 2, &winner);
    getAverageStudentsInCourse(d, 10, 18, &res);
    deleteLecture(d, 5, 12);
    competition(d, 32, 34, -1, &winner);
    addRoom(d, -4);
    getAverageStudentsInCourse(d, 6, 16, &res);
    addLecture(d, 13, 11, 11, 7, 4);
    addRoom(d, 16);
    addLecture(d, 32, 8, 12, 6, 19);
    addRoom(d, 10);
    addLecture(d, 6, 9, 17, 0, 12);
    deleteRoom(d, 18);
    getAverageStudentsInCourse(d, 11, -5, &res);
    mergeCourses(d, 19, 33);
    addLecture(d, 24, 6, 19, 10, 26);
    addLecture(d, 37, 3, 8, -1, 21);
    addLecture(d, 20, 4, 19, 11, 19);
    addRoom(d, 20);
    addRoom(d, 16);
    deleteLecture(d, 1, -2);
    getAverageStudentsInCourse(d, 1, 0, &res);
    addRoom(d, 0);
    deleteRoom(d, 9);
    getAverageStudentsInCourse(d, 0, 4, &res);
    competition(d, 1, 22, -1, &winner);
    getAverageStudentsInCourse(d, 4, 19, &res);
    deleteLecture(d, 6, -5);
    addRoom(d, -2);
    addLecture(d, 40, 3, 2, 3, 40);
    deleteRoom(d, 19);
    mergeCourses(d, 11, 18);
    deleteRoom(d, 12);
    getAverageStudentsInCourse(d, 0, 8, &res);
    mergeCourses(d, 8, 32);
    getAverageStudentsInCourse(d, 7, -4, &res);
    deleteRoom(d, 8);
    competition(d, 37, 26, -1, &winner);
    addLecture(d, 30, 9, 19, 11, 43);
    addLecture(d, 9, 12, 19, 11, 44);
    addRoom(d, 19);
    competition(d, 8, 7, 3, &winner);
    deleteLecture(d, 11, 5);
    deleteLecture(d, 9, 20);
    competition(d, 40, 11, 6, &winner);
    deleteLecture(d, 5, 6);
    addLecture(d, 25, 15, 11, -1, 13);
    competition(d, 5, 1, 4, &winner);
    deleteRoom(d, 5);
    mergeCourses(d, 24, 6);
    addLecture(d, 18, 11, 3, 4, 19);
    deleteLecture(d, 2, -4);
    addLecture(d, 34, 2, 8, 0, 48);
    addLecture(d, 39, 15, 18, 7, 2);
    deleteLecture(d, 0, 10);
    addRoom(d, 5);
    deleteRoom(d, 9);
    addRoom(d, 7);
    mergeCourses(d, 31, 11);
    getAverageStudentsInCourse(d, 1, -5, &res);
    addRoom(d, 6);
    addRoom(d, 15);
    addRoom(d, -5);
    mergeCourses(d, 38, 40);
    addRoom(d, 9);
    Quit(&d);
    
    
    cout << "Welcome to the tests for wet2" << endl;
    cout << " Good Luck." << endl;

    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
         << endl;

    cout << "Testing sagal_test" << endl;
    Sagal_Test();
    cout << "PASSED!!!" << endl;

    cout << "." << endl;
    cout << "." << endl;
    cout << "." << endl;

    cout << "Testing Init And Quit" << endl;
    Test_Init_And_Quit();
    cout << "PASSED!!!" << endl;

    cout << "." << endl;
    cout << "." << endl;
    cout << "." << endl;

    cout << "Testing AddLecture" << endl;
    Test_AddLecture();
    cout << "PASSED!!!" << endl;

    cout << "." << endl;
    cout << "." << endl;
    cout << "." << endl;

    cout << "Testing DeleteLecture" << endl;
    Test_DeleteLecture();
    cout << "PASSED!!!" << endl;

    cout << "." << endl;
    cout << "." << endl;
    cout << "." << endl;

    cout << "Testing merge_courses" << endl;
    Test_merge_courses();
    cout << "PASSED!!!" << endl;

    cout << "." << endl;
    cout << "." << endl;
    cout << "." << endl;

    cout << "Testing competition_And_Average" << endl;
    Test_competition_And_Average();
    cout << "PASSED!!!" << endl;

    cout << "." << endl;
    cout << "." << endl;
    cout << "." << endl;

    cout << "FINAL TEST!!" << endl;
    Final_test();
    cout << "PASSED!!!" << endl;

    cout << "." << endl;
    cout << "." << endl;
    cout << "." << endl;



    cout << "well done! you did it!" << endl;

    cout << "." << endl;
    cout << "." << endl;
    cout << "." << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
         << endl;
//

    return 0;
}
