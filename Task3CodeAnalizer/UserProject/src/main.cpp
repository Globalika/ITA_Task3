#include "../../CodeAnalizer/src/CodeAnalizer.h"
#include <iostream>
#include <filesystem>
#include <regex>
#include <string>

int main()
{
	std::string pathLnu = "C:/Users/volod/source/Lnu_VS";
	std::string path = "C:/Users/volod/source/IT_Academy_Tasks/Task2_AnyType";
	std::string test = "C:/Users/Test";
	std::string test2 = "C:/Users/Test/T1";

	std::string result = "C:/Users/volod/source/ITA_Task3/Task3CodeAnalizer/UserProject/src";

	CodeAnalyzer analyzer;
	analyzer.Analize(pathLnu, result);
	return 0;
}
