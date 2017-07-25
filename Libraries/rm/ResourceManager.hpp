#pragma once
#include <Texture.h>
#include <Font.h>
#include <Audio.h>
#include <string>
#include <tuple>         //Getting specific variadic parameter
#include <memory>
#include "ErrorManager.hpp"

///Co-written by Sebastian Toy and Jack McCall
class ResourceManager
{
public:
	///Template methods
	//Load any kind of resource from computer and handle errors so the user knows what isn't being loaded properly
	template <typename T, typename... Args>      //typename... Args = expect any number of typenames
	static std::unique_ptr<T> loadResource(Args... args) {       //Work with any resource parameters, variable number of arguments and typenames. args = any number of variables 
	    //Using first parameter which is always assumed to be filename, check if its a valid directory - if not crash with warning.
		auto tuple = std::tuple<Args...>(args...);       //Create tuple from variadic list. Tuple = parameter pack.
		std::tuple_element<0, decltype(tuple)>::type fileName = std::get<0>(tuple); /*Assign first datatype and element (0) of tuple to variable to test its directory.
																					<dataType from tuple index> variable = <variable from tuple Index>
																					decltype = expression of tuple.*/
		std::fstream test(fileName, std::ios::in); //Test if the file directory is valid (returns boolean)
		if (!test) {
			char errorMsg[256];
			sprintf_s(errorMsg, "[ERROR] File not found: \"%s\"", fileName);  //Use escape characters to use quotation marks
			ErrorManager::PrintSystemFail(errorMsg);
		}
		return std::unique_ptr<T>(new T(args...));               //Construct with provided arguments and return unique pointer to new valid resource
	}
};

