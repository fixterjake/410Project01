/*
 * main.cpp
 *
 *  Created on: Aug 28, 2019
 *      Author: fixterjake
 */

#include <iostream>
#include "utilities.h"
//defaults
const char* 		source = "TestData.txt";
using namespace std;

int main() {
	int points = 100;
	int iRet = FAIL;
	iRet = loadData(source);
	if (iRet != SUCCESS) {
		points -=10;
		std::cout << "Failed to load data." << std::endl;
	}
	std::cout << "Total points: " << points << std::endl;
	return iRet;
}


