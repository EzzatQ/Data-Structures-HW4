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
#include "hash_table.hpp"

namespace DataStructures{
	
	class course{
		int courseID;
		int StudentNum;
		int LectureNum;
		AVLTree<LectureInfo, int>* lectures; //the 2nd int is the groupID;
		modifiedAVLTree* students;
       
	public:
		course() : courseID(0), StudentNum(0), LectureNum(0), lectures(nullptr), students(nullptr){}
		course(int number): courseID(number), StudentNum(0), LectureNum(0), lectures(nullptr), students(nullptr){
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
		
		
		
		int competition(course& other, int numGroups){
            if(*this == other) throw Failure();
			int thisMax = students->findMaxStudents(numGroups);
			int otherMax = other.students->findMaxStudents(numGroups);
			if(thisMax < otherMax) return other.courseID;
            else {
                if(thisMax == otherMax) return other.courseID > this->courseID ? other.courseID : this->courseID;
                else
                return this->courseID;
            }
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
        ~course(){delete lectures; delete students;}
		
		//// fills a new tree from a sorted array
		void treeFill_aux(node<LectureInfo, int> * root,node<LectureInfo, int> ** array,int start,int finish){
			root->setLeft(nullptr);
			root->setRight(nullptr);
			int middle = start+(finish - start)/2;
			if(middle-start>1 || (start == 0 && middle-start == 1)){
				root->setLeft(array[start+(middle-start)/2]);
				treeFill_aux(root->getLeft(),array,start,middle);
			}
			if(finish-middle>1){
				root->setRight(array[middle+(finish-middle)/2]);
				treeFill_aux(root->getRight(),array,middle,finish);
			}
		}
		AVLTree<LectureInfo, int>* treeFill(node<LectureInfo, int> ** array, int m){
            if(m==0) return nullptr;
			node<LectureInfo, int> *root = array[m/2];
			treeFill_aux(root, array, 0, m);
			return new AVLTree<LectureInfo, int>(root,m);
		}
		
		int modTreeFill_aux(modifiedNode<lecture>* root, modifiedNode<lecture> ** array,int start, int finish){
			root->setLeft(nullptr);
			root->setRight(nullptr);
			int middle = start+(finish - start)/2;
			int x1 = 0, x2 = 0;
            root->setStudentsOnTheRight(0);
			if(middle - start > 1 || (start == 0 && middle - start == 1)){
				root->setLeft(array[start+(middle-start)/2]);
				x1 = modTreeFill_aux(root->getLeft(),array,start,middle);
			}
			if(finish-middle>1){
				root->setRight(array[middle+(finish-middle)/2]);
				x2 = modTreeFill_aux(root->getRight(),array,middle,finish);
                root->setStudentsOnTheRight(x2);
			}
			root->setLecturesOnTheRight(finish - (start+(finish - start)/2)-1);
			return x1 + x2 + root->getKey().getNumStudents();
		}
		
		
		modifiedAVLTree* modTreeFill(modifiedNode<lecture> ** array, int m){
			modifiedNode<lecture> *root = array[m/2];
			modTreeFill_aux(root, array, 0 , m);
			return new modifiedAVLTree(root,m);
		}
        void deleteSubTree1(node<LectureInfo, int>* root){
            if(root){
                deleteSubTree1(root->getLeft());
                deleteSubTree1(root->getRight());
                delete root;
            }
        }
        void deleteSubTree2(modifiedNode<lecture>* root){
            if(root){
                deleteSubTree2(root->getLeft());
                deleteSubTree2(root->getRight());
                delete root;
            }
        }
		void merge(course& other){
			this->StudentNum += other.StudentNum;
			this->LectureNum += other.LectureNum;
			AVLTree<LectureInfo, int>* AVL1 = this->lectures;
			AVLTree<LectureInfo, int>* AVL2 = other.lectures;
			modifiedAVLTree* MOD1 = this->students;
			modifiedAVLTree* MOD2 = other.students;
			int A1 = AVL1->getNodeCount();
			int A2 = AVL2->getNodeCount();
			int M1 = MOD1->getNodeCount();
			int M2 = MOD2->getNodeCount();
            if(A1 + A2 ==0) return;
			int count1 = 0;
			node<LectureInfo, int> ** arrayA1;
			node<LectureInfo, int> ** arrayA2;
			node<LectureInfo, int> ** arrayA3;
			
			try{
				arrayA1 = new node<LectureInfo, int> *[A1];
				arrayA2 = new node<LectureInfo, int> *[A2];
				arrayA3 = new node<LectureInfo, int> *[A1+A2];
				AVL1->fillAnArray(arrayA1);
				AVL2->fillAnArray(arrayA2);
				node<LectureInfo, int> ** p1 = arrayA1;
				node<LectureInfo, int> ** p2 = arrayA2;
				
				int x=0, y=0;
				while(x+y < A1+A2){
					if(x < A1 && y < A2){
						if(p1[x]->getKey() < p2[y]->getKey()){
							arrayA3[x+y] = p1[x];
							x++;
						} else {
							if(p1[x]->getKey() == p2[y]->getKey()){
                                delete[] arrayA1;
                                delete[] arrayA2;
                                delete[] arrayA3;
                            
								throw Failure();
							}
							arrayA3[x+y] = p2[y];
							y++;
						}
					} else if(x == A1){
						arrayA3[x+y] = p2[y];
						y++;
					} else{
						arrayA3[x+y] = p1[x];
						x++;
					}
				}
				delete[] arrayA1;
				delete[] arrayA2;
				if(this->lectures)delete this->lectures;
				if(other.lectures)delete other.lectures;
				other.lectures = nullptr;
				this->lectures = treeFill(arrayA3, A1+A2);
				for (int i = 0; i < A1+A2; i++) {
					delete arrayA3[i];
				}
				delete []arrayA3;
			} catch(std::bad_alloc e){
				if(count1 == 1) delete[] arrayA1;
				if(count1 == 2){ delete[] arrayA1; delete[] arrayA2;}
				throw OutOfMemory();
			}
			int count2 = 0;
			modifiedNode<lecture> ** arrayM1;
			modifiedNode<lecture> ** arrayM2;
			modifiedNode<lecture> ** arrayM3;
			try{
				arrayM1 = new modifiedNode<lecture> *[M1]; count2++;
				arrayM2 = new modifiedNode<lecture> *[M2]; count2++;
				arrayM3 = new modifiedNode<lecture> *[M1+M2];
				MOD1->fillAnArray(arrayM1);
				MOD2->fillAnArray(arrayM2);
				modifiedNode<lecture> ** q1 = arrayM1;
				modifiedNode<lecture> ** q2 = arrayM2;
				
				int z = 0, w = 0;
				while(z+w < M1+M2){
					if(z < M1 && w < M2){
						if(q1[z]->getKey() < q2[w]->getKey()){
							arrayM3[z+w] = q1[z];
							z++;
						}else{
							arrayM3[z+w] = q2[w];
							w++;
						}
					}else if(z == M1){
						arrayM3[z+w] = q2[w];
						w++;
					}else{
						arrayM3[z+w] = q1[z];
						z++;
					}
				}
				delete[] arrayM1;
				delete[] arrayM2;
				delete this->students;
				delete other.students;
				other.students = nullptr;
				this->students = modTreeFill(arrayM3, M1+M2);
				for (int i = 0; i < M1+M2; i++) {
					delete arrayM3[i];
				}
				delete [] arrayM3;
			} catch(std::bad_alloc e){
				if(count2 == 1) delete[] arrayM1;
				if(count2 == 2){ delete[] arrayM1; delete[] arrayM2;}
				throw OutOfMemory();
			}
		}
		///////////////////////
	};
	
}


#endif /* Course_hpp */
