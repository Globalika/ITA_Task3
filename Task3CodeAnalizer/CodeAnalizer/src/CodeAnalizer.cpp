#include "CodeAnalizer.h"

bool CodeAnalyzer::Analize(std::string& rootPath, std::string& resultPath)
{
	m_rootPath = rootPath;
	m_resultPath = resultPath;
	if (!fs::exists(rootPath) || !fs::exists(resultPath)) {
		return false;
	}
	else 
	{
		const auto start = time.now();
		if (!AddFilePathsToQueue(m_rootPath)) {
			return false;
		}
		else {
			SpawnThreads();
			const auto end = time.now();
			elapsedTime = static_cast<std::chrono::duration<double>>(end - start);
			if (!WriteInfoInFile(m_resultPath)) {
				return false;
			}
			else {
				return true;
			}
		}
	}
}

bool CodeAnalyzer::AddFilePathsToQueue(fs::path& path)
{
	if (!exists(path)) {
		return false;
	}
	else {
		if (fs::is_regular_file(path))
		{
			if (CheckFileExtension(path) == true) {
				pathsQueue.push(path);
				processedFiles++;
			}
		}
		else
		{
			for (auto& x : fs::recursive_directory_iterator(path))
			{
				fs::path path = x.path();
				if (CheckFileExtension(path) == true) {
					pathsQueue.push(x);
					processedFiles++;
				}
			}
		}
		return true;
	}
}

bool CodeAnalyzer::CheckFileExtension(fs::path& p)
{
	auto path = p.extension();
	if (path == c || path == h ||
		path == cpp || path == hpp)
	{
		return true;
	}
	return false;
}

void CodeAnalyzer::SpawnThreads()
{
	unsigned int threadsCount = (processedFiles < std::thread::hardware_concurrency()) ? (processedFiles) : (std::thread::hardware_concurrency());
	for (unsigned int i = 0; i < threadsCount; i++)
	{
		threadsVector.push_back(std::thread([this]
			{
				ProcessFiles();
			}));
	}
	for (auto& it : threadsVector)
	{
		if (it.joinable())
			it.join();
	}
}

void CodeAnalyzer::ProcessFiles()
{
	do
	{
		fs::path path = GetPathFromQueue();
		if (path.empty()) 
		{
			break;
		}
		auto info = fileAnalizer.CountFileLines(path);
		RecordAnalysisResult(info);
	} while (true);
}

fs::path CodeAnalyzer::GetPathFromQueue()
{
	std::lock_guard<std::mutex> lockQ(mQueue);
	fs::path path;
	if (!pathsQueue.empty())
	{
		path = pathsQueue.front();
		pathsQueue.pop();
		return path;
	}
	return path;
}

void CodeAnalyzer::RecordAnalysisResult(std::tuple<int, int, int> info)
{
	std::lock_guard<std::mutex> lockL(mLines);
	blankLines += std::get<0>(info);
	commentLines += std::get<1>(info);
	codeLines += std::get<2>(info);
}



bool CodeAnalyzer::WriteInfoInFile(fs::path& path)
{
	if (!fs::exists(path)) {
		return false;
	}
	else 
	{
		fs::path result = m_resultPath.append("result.txt");
		std::fstream out(result, std::ios::out, std::ios::trunc);
		out << "Directory path : " << m_rootPath << '\n';
		out << "Processed files : " << processedFiles << '\n';
		out << "Blank lines : " << blankLines << '\n';
		out << "Comment lines : " << commentLines << '\n';
		out << "Code lines : " << codeLines << '\n';
		out << "Elapsed time : " << elapsedTime.count() << " seconds";
		out.close();
		return true;
	}
}