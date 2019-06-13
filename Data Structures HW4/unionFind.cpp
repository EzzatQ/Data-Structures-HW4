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

int main(){
	int arr[] = {1,2,3,4,5,6,7,8,9,10};
	unionFind<int,int> uf = unionFind<int,int>(10, arr);
	uf.unite(1, 3);
	uf.unite(3, 3);
	uf.unite(4, 3);
	uf.unite(5,2);
	uf.unite(2, 1);
	std::cout << uf.find(2) << std::endl;
	
	std::cout << uf.find(6) << std::endl;
	std::cout << uf.find(7) << std::endl;
	uf.unite(8, 9);
	std::cout << uf.find(9) << std::endl;
	uf.unite(4, 10);
	std::cout << uf.find(10) << std::endl;
	std::cout << (*uf.getData(10)) << std::endl;
}
