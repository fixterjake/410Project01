/*
 * main.cpp
 *
 *  Created on: Aug 28, 2019
 *      Author: fixterjake
 */

#include <iostream>
#include "utilities.h"
//defaults
const char* 		data = "data.txt";
const char* 		badData = "badData.txt";
const char*		 	result = "results.txt";
using namespace std;

int main() {
	int points = 100;
	int iRet = FAIL;
	iRet = loadData(data);
	if (iRet != SUCCESS) {
		points -=10;
		std::cout << "Failed to load data." << std::endl;
	}
	else {
		std::cout<< "Success 1"<< std::endl;
	}

	iRet = FAIL;
	iRet = saveData(result);
	if (iRet != SUCCESS) {
		points -=10;
		std::cout << "Failed to save data." << std::endl;
	}
	else {
		std::cout<< "Success 2"<< std::endl;
	}

	process_stats myStats = getNext();
	if (myStats.process_number != 1 && myStats.start_time != 2 && myStats.cpu_time != 3) {
		points -= 20;
		std::cout << "-20 failed getnext after sort, expected 10,10,200 got "  <<  std::to_string(myStats.process_number)
			<< "," << std::to_string(myStats.start_time) << "," << std::to_string(myStats.cpu_time) << endl;
	}
	else {
		std::cout << "Success 3" << std::endl;
	}

	iRet = FAIL;
	iRet = loadData(badData);
	if (iRet != SUCCESS) {
		points -= 10;
		std::cout << "Failed to load data" << std::endl;
	}
	else{
		std::cout << "Success 4" << std::endl;
	}

	std::cout << "Total points: " << points << std::endl;
	return iRet;
}


