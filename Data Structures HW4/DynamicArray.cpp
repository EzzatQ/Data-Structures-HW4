//
//  DynamicArray.cpp
//  Data Structures HW4
//
//  Created by Ezzat Qupty on 11/06/2019.
//  Copyright © 2019 Ezzat Qupty. All rights reserved.
//

#include "DynamicArray.hpp"

template <class T>
void printDyn(dynamicArray<T>& d){
	for(int i = 0; i < d.getSize(); i++){
		std::cout << d[i] << " ";
	}
	std::cout << std::endl;
}

template <class T>
void fill(dynamicArray<T>& d, int to){
	for(int i = 0; i <= to; i++){
		if(i < d.getSize()) d[i] = i;
		else d.insert(i);
	}
}

int main(){
	dynamicArray<int> a = dynamicArray<int>(0);
	dynamicArray<int> b(a);
	dynamicArray<int> c = dynamicArray<int>(15);
	printDyn(a);
	printDyn(b);
	printDyn(c);
	c = b;
	printDyn(c);
	fill(a,5);
	printDyn(a);
	fill(b, 20);
	printDyn(b);
	b.remove();
	b.remove();
	b.remove();
	b.remove();
	b.remove();
	b.remove();
	b.remove();
	b.remove();
	b.remove();
	b.remove();
	b.remove();
	b.remove();
	b.remove();
	printDyn(b);
	b[0] = 10000;
	printDyn(b);
}
