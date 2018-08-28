// fstream_demo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdio.h>

using namespace std;

#define MAX_CHAR 1024


void fstream_test(){
	std::string filename("D:\\YunLin\\Documents\\Visual Studio 2013\\Projects\\CPPLearning\\Debug\\demo.txt");

	std::ifstream input(filename);

	if (input){

		char con[MAX_CHAR];
		std::vector<std::string> contents;


		while (input.getline(con, MAX_CHAR)){
			std::cout << con << std::endl;
			contents.push_back(con);

		}

		input.close();
		std::cout << "read finished." << std::endl;

		std::cout << "contents: " << "\n";
		for (const auto &pstr : contents){

			std::cout << pstr << "\n";
		}

		std::cout << std::endl;
	}
	else {

	}
}

struct PersonInfo{
	std::string name;
	std::vector<std::string> phones;
};

void stringstream_test(){

	/*string line;
	while (getline(cin, line))
	{
		PersonInfo inf;
		istringstream record(line);

	}*/
}

int _tmain(int argc, _TCHAR* argv[])
{
	

	getchar();
	return 0;
}

