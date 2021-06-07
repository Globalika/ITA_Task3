#pragma once
#ifndef FILE_ANALIZER
#define FILE_ANALIZER

#include <tuple>
#include <string>
#include <filesystem>
#include <fstream>
#include <regex>

namespace fs = std::filesystem;

class FileAnalyzer
{
public:
	/*Count lines. return tuple (blank, comment and code lines)*/
	std::tuple<int, int, int> CountFileLines(fs::path& path);
private:
	enum class CheckType;
	void DefineLineType(std::string& line, CheckType& type);
	void DefineLineTypeRecursive(
		std::string& line,
		CheckType& type,
		bool quotesOpen = false
	);
	enum class CheckType
	{
		NO_CHECK,
		BLANK_LINE,
		CODE_LINE,
		COMMENT_OPEN,
		COMMENT_CLOSE,
		CODE_AND_COMMENT_OPEN,
		CODE_AND_COMMENT_CLOSE
	};

	const std::regex blank_line_regex{ "[\t ]*" };
	const std::regex single_line_comment_regex{ "[\t ]*\/\/(.*)" };
};

#endif // FILE_ANALIZER