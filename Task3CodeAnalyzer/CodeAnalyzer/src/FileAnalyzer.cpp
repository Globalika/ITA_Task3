#include "FileAnalyzer.h"

std::tuple<int, int, int> FileAnalyzer::CountFileLines(fs::path& path)
{
	CheckType type = CheckType::NO_CHECK;
	std::string line;
	int blankLines = 0;
	int comLines = 0;
	int codeLines = 0;

	std::ifstream f(path);
	if (f.is_open())
	{
		while (!f.eof()) {
			getline(f, line);
			DefineLineType(line, type);
			switch (type)
			{
			case CheckType::CODE_LINE:
				codeLines++;
				break;
			case CheckType::CODE_AND_COMMENT_OPEN:
				codeLines++;
				comLines++;
				break;
			case CheckType::CODE_AND_COMMENT_CLOSE:
				codeLines++;
				comLines++;
				break;
			case CheckType::COMMENT_OPEN:
				comLines++;
				break;
			case CheckType::COMMENT_CLOSE:
				comLines++;
				break;
			case CheckType::BLANK_LINE:
				blankLines++;
				break;
			default:
				break;
			}
		}
		f.close();
		return std::make_tuple(blankLines, comLines, codeLines);
	}
	return std::make_tuple(0, 0, 0);
}

void FileAnalyzer::DefineLineType(std::string& line, CheckType& type)
{
	if (std::regex_match(line, blank_line_regex) &&
		((type != CheckType::COMMENT_OPEN) && (type != CheckType::CODE_AND_COMMENT_OPEN))) {
		type = CheckType::BLANK_LINE;
	}
	else if (line.size() == 1) {
		type = CheckType::CODE_LINE;
	}
	else if (std::regex_match(line, single_line_comment_regex)) {
		type = CheckType::COMMENT_CLOSE;
	}
	else {
		if (type == CheckType::CODE_AND_COMMENT_OPEN) {
			type = CheckType::COMMENT_OPEN;
		}
		DefineLineTypeRecursive(line, type);
	}
}

void FileAnalyzer::DefineLineTypeRecursive(std::string& line, CheckType& type, bool quotesOpen)
{
	if (line.size() < 2) {
		return;
	}
	for (int i = 0; i < line.size() - 1; i++)
	{
		std::string subLine2 = line.substr(i + 2, line.size());
		std::string subLine = line.substr(0, i);
		if ((line.at(i) != '\\') && (line.at(i + 1) == '"')) {
			quotesOpen = !quotesOpen;
			DefineLineTypeRecursive(subLine2, type, quotesOpen);
		}
		if ((line.at(i) == '/' && line.at(i + 1) == '/'))
		{
			if (!quotesOpen)
			{
				if (std::regex_match(subLine, blank_line_regex)) {
					type = CheckType::COMMENT_CLOSE;
				}
				else {
					type = CheckType::CODE_AND_COMMENT_CLOSE;
				}
				return;
			}
			else {
				continue;
			}
		}
		else if ((line.at(i) == '/' && line.at(i + 1) == '*'))
		{
			if (!quotesOpen)
			{
				if (std::regex_match(subLine, blank_line_regex)) {
					type = CheckType::COMMENT_OPEN;
				}
				else {
					type = CheckType::CODE_AND_COMMENT_OPEN;
				}
				DefineLineTypeRecursive(subLine2, type, quotesOpen);
				return;
			}
			else {
				continue;
			}
		}
		else if ((line.at(i) == '*' && line.at(i + 1) == '/'))
		{
			if (!quotesOpen)
			{
				std::string subLine = line.substr(i + 2, line.size());
				if ((std::regex_match(subLine, blank_line_regex)) &&
					(type == CheckType::COMMENT_OPEN))
				{
					type = CheckType::COMMENT_CLOSE;
				}
				else {
					type = CheckType::CODE_AND_COMMENT_CLOSE;
				}
				return;
			}
			else {
				continue;
			}
		}
	}
	if ((type != CheckType::COMMENT_OPEN) && (type != CheckType::CODE_AND_COMMENT_OPEN)) {
		type = CheckType::CODE_LINE;
	}
}