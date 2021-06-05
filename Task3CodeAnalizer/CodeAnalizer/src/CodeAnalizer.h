#pragma once
#ifndef CODE_ANALIZER
#define CODE_ANALIZER

#include "FileAnalizer.h"

#include <queue>
#include <tuple>
#include <vector>
#include <string>
#include <thread>
#include <fstream>
#include <mutex>
#include <filesystem>
#include <chrono>

namespace fs = std::filesystem;

class CodeAnalyzer
{
public:
	CodeAnalyzer() {}
	~CodeAnalyzer() {}
	[[nodiscard]] bool Analize(std::string& rootPath, std::string& resultPath);
	[[nodiscard]] bool AddFilePathsToQueue(fs::path& path);
	bool CheckFileExtension(fs::path& path);
	void SpawnThreads();
	// function for every threads for work to be done
	void ProcessFiles();
	// have lock quard for every thread taking path from queue
	fs::path GetPathFromQueue();	
	void RecordAnalysisResult(std::tuple<int, int, int> info);
	[[nodiscard]] bool WriteInfoInFile(fs::path& path);
	unsigned int GetTheadsAmountUsed() { return threadsVector.size(); }
private:
	unsigned int processedFiles = 0;
	unsigned int blankLines = 0;
	unsigned int commentLines = 0;
	unsigned int codeLines = 0;
	FileAnalizer fileAnalizer;
	std::filesystem::path m_rootPath;
	std::filesystem::path m_resultPath;
	const std::chrono::steady_clock time {};
	std::chrono::duration<double> elapsedTime {};
	std::queue<std::filesystem::path> pathsQueue;
	std::vector<std::thread> threadsVector;
	std::mutex mLines;
	std::mutex mQueue;
	const std::string c = ".c";
	const std::string h = ".h";
	const std::string cpp = ".cpp";
	const std::string hpp = ".hpp";
};

#endif // CODE_ANALIZER