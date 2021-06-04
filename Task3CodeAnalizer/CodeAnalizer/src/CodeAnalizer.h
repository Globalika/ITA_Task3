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
#include <regex>

namespace fs = std::filesystem;

class Analyzer
{
public:
	Analyzer() {}
	~Analyzer() {}
	[[nodiscard]] bool Analize(std::string rootPath, std::string resultPath);
	[[nodiscard]] bool AddFilePathsToQueue();
	bool CheckFileExtension(fs::path path);
	void SpawnThreads();
	void ProcessFiles();
	fs::path GetPathFromQueue();	
	void RecordAnalysisResult(std::tuple<int, int, int> info);
	[[nodiscard]] bool WriteInfoInFile(fs::path path);
private:	
	FileAnalizer fileAnalizer {};
	unsigned int processedFiles = 0;
	unsigned int blankLines = 0;
	unsigned int commentLines = 0;
	unsigned int codeLines = 0;
	const unsigned int threadsCount = std::thread::hardware_concurrency();
	std::filesystem::path m_rootPath;
	std::filesystem::path m_resultPath;
	const std::chrono::steady_clock time {};
	std::chrono::duration<double> elapsedTime {};
	std::queue<std::filesystem::path> pathsQueue;
	std::vector<std::thread> threadsVector;
	std::mutex mLines;
	std::mutex mQueue;
};

#endif // CODE_ANALIZER