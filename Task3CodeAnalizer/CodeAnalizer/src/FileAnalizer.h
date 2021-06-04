#pragma once
#include <tuple>
#include <string>
#include <filesystem>
#include <fstream>
#include <regex>

namespace fs = std::filesystem;

class FileAnalizer
{
public:
	//Count lines// return tuple (blank, comment, code lines)
	std::tuple<int, int, int> CountFileLines(fs::path);
	enum class CheckType;
	void DefineLineTypeRecursive(std::string line, CheckType& type, bool quotesOpen = false);
	void DefineLineType(std::string& line, CheckType& type);
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
private:
	const std::regex blank_line_regex { "[\t ]*" };
	const std::regex single_line_comment_regex{ "[\t ]*\/\/(.*)" };
};