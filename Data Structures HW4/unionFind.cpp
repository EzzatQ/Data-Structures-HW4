//
//  unionFind.cpp
//  Data Structures HW4
//
//  Created by Ezzat Qupty on 11/06/2019.
//  Copyright © 2019 Ezzat Qupty. All rights reserved.
//

#include "unionFind.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "hash_table.hpp"
#include "modifiedAVL.hpp"



using namespace DataStructures;
using namespace std;
int main1(){
	int* arr = new int[100000];
	for(int i = 1; i <= 100000; i++){
		arr[i - 1] = i;
	}
	unionFind<int> a = unionFind<int>(100000, arr);
	for(int i = 1; i <= 100000; i += 2){
		a.unite(i, i + 1);
	}
	for(int i = 1; i <= (100000 - 3) / 2; i += 4){
		a.find(i);
	}
	for(int i = 1; i <= (100000 - 3) / 2; i += 4){
		a.unite(i + 1, i + 3);
	}
	for(int i = 1; i <= (100000 - 3) / 2; i += 4){
		a.find(i);
	}
	for(int i = 1; i <= (100000 - 3) ; i ++){
		a.unite(i , i + 1);
	}
	for(int i = 1; i <= (100000 - 3); i ++){
		a.find(i);
	}
	cout<< "test done";
	delete[] arr;
}
