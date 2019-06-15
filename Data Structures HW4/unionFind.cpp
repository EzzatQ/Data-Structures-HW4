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


using namespace DataStructures;
int main(){
//	hashTable<unionFind<int, int>> hash = hashTable<unionFind<int, int>>(10);
//	int arr[] = {1,2,3,4,5,6,7,8,9,10};
//	unionFind<int,int> uf = unionFind<int,int>(10, arr);
//	for(int i = 0; i < 20; i++){
//		unionFind<int,int> temp(uf);
//		hash.insert(i, uf);
//	}
	hashTable<int> hash = hashTable<int>(10);
	for(int i = 0; i < 8; i++){
		hash.insert(i, i);
	}
	hashTable<int> hash2(hash);
	
}
