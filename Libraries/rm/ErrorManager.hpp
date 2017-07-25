#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <ios>

///Co-written by Sebastian Toy and Jack McCall
class ErrorManager
{
public:
	//Methods
	static void PrintSystemFail(const char* a_error) {
		//Print the error
		std::cout << a_error << std::endl;
		system("pause");
		//Write the error
		std::fstream errorFile("error.log", std::ios::out);
		errorFile << a_error << "\n";
		//Exit with a crash
		exit(EXIT_FAILURE);
	}
};

