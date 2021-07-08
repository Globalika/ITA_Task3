#include "../../CodeAnalyzer/src/CodeAnalyzer.h"
#include <string>

int main()
{
	std::string pathLnu = "C:/Users/volod/source/Lnu_VS";

	std::string result = "C:/Users/volod/source/ITA/ITA_Task3/Task3CodeAnalyzer/UserProject/src";

	CodeAnalyzer analyzer;

	//analyzer.Analize(pathLnu, result);

	analyzer.Analize(pathLnu, result);

	return 0;
}