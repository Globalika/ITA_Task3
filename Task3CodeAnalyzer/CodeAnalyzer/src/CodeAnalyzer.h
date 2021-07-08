#pragma once
#ifndef CODE_ANALIZER
#define CODE_ANALIZER

#include "FileAnalyzer.h"

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
	[[nodiscard]] bool Analize(
		std::string& rootPath,
		std::string& resultPath
	);
	bool CheckFileExtension(fs::path& path);
private:
	void ClearUp();
	[[nodiscard]] bool AddFilePathsToQueue(fs::path& path);
	void SpawnThreads();
	// thread begin analizing files in queue in loop
	void ProcessFiles();
	// thread taking path from queue with lock guard
	fs::path GetPathFromQueue();
	void RecordAnalysisResult(std::tuple<int, int, int> info);
	[[nodiscard]] bool WriteInfoInFile(fs::path& path);

	FileAnalyzer fileAnalyzer;
	unsigned int m_processedFiles = 0;
	unsigned int m_blankLines = 0;
	unsigned int m_commentLines = 0;
	unsigned int m_codeLines = 0;
	std::filesystem::path m_rootPath;
	std::filesystem::path m_resultPath;
	const std::chrono::steady_clock time{};
	std::chrono::duration<double> elapsedTime{};
	std::queue<std::filesystem::path> pathsQueue;
	std::vector<std::thread> threadsVector;
	std::mutex mLines;
	std::mutex mQueue;
};

#endif // CODE_ANALIZER