/*
 * utilities.cpp
 * Created on: Aug 26, 2019
 * Author: Jacob Boyles
 */

#include <string>
#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "utilities.h"

//Global list of process_stats structs
std::vector<process_stats> processStats;

//Parse row into integers
//Create new struct based on parsed integers & add to vector
void processRow(std::string row) {
	std::stringstream ss(row);
	std::vector<std::string> parsed;
	while (ss.good()) {
		std::string substr;
		std::getline(ss, substr, CHAR_TO_SEARCH_FOR);
		if (substr.length() > 0) {
			parsed.push_back(substr);
		}
	}
	process_stats entry;
	entry.process_number = std::stoi(parsed[0]);
	entry.start_time = std::stoi(parsed[1]);
	entry.cpu_time = std::stoi(parsed[2]);
	processStats.push_back(entry);
}

//clears vector holding process_stats structs
//attempt to open file 'filename' to read, parse its rows
//into process_stats structs and add these structs to a vector
//
//returns SUCCESS if all goes well or COULD_NOT_OPEN_FILE
int loadData(const char* filename) {
	processStats.clear();
	std::ifstream myfile;
	myfile.open(filename);
	if (!myfile.is_open()) {
		myfile.close();
		return COULD_NOT_OPEN_FILE;
	}

	std::string row;
	while (std::getline(myfile, row)) {
		processRow(row);
	}
	myfile.close();
	return SUCCESS;
}

//Serialize each vector entry into strings with correct comma separated format
//Returns given string to be written to the file
std::string serializeVector(process_stats entry) {
	std::string serialzedEntry =
			std::to_string(entry.process_number) + "," +
			std::to_string(entry.start_time) + "," +
			std::to_string(entry.cpu_time);
	return serialzedEntry;
}

//attempt to open file 'filename' to write, and serialize a
//vector full of process_stats structs to it.  Should be in the same
//format as original file but not necessarily the same order or length
//if the file exists, overwrite its contents.
//returns SUCCESS if all goes well or COULD_NOT_OPEN_FILE
int saveData(const char* filename) {
	std::ofstream myfile;
	myfile.open(filename, std::ofstream::trunc);
	if (!myfile.is_open()) {
		myfile.close();
		return COULD_NOT_OPEN_FILE;
	}

	std::string row;
	for (process_stats entry : processStats) {
		row = serializeVector(entry);
		myfile << row << std::endl;
	}
	myfile.close();
	return SUCCESS;
}

//Compare process_stats structs by process number
bool compareProcessStatsNumber(process_stats a, process_stats b) {
	return a.process_number < b.process_number;
}

//Compare process_stats structs by start time
bool compareProcessStatsStart(process_stats a, process_stats b) {
	return a.start_time < b.start_time;
}

//Compare process_stats structs by cpu time
bool compareProcessStatsCpu(process_stats a, process_stats b) {
	return a.cpu_time < b.cpu_time;
}

//sorts the vector, returns nothing (thats what void means)
//sorts low to high
void sortData(SORT_ORDER mySortOrder) {
	switch(mySortOrder) {
		case SORT_ORDER::PROCESS_NUMBER:
			std::sort(processStats.begin(), processStats.end(), compareProcessStatsNumber);
			break;
		case SORT_ORDER::CPU_TIME:
			std::sort(processStats.begin(), processStats.end(), compareProcessStatsCpu);
			break;
		case SORT_ORDER::START_TIME:
			std::sort(processStats.begin(), processStats.end(), compareProcessStatsStart);
			break;
	}
}

//return the first struct in the vector
//then deletes it from the vector
process_stats getNext() {
	process_stats value;
	if (processStats.size() > 0) {
		value = processStats.front();
		processStats.erase(processStats.begin());
		return value;
	}
	return value;
}


