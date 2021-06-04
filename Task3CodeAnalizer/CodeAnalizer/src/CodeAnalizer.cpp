#include "CodeAnalizer.h"

bool Analyzer::Analize(std::string rootPath, std::string resultPath)
{
	m_rootPath = rootPath;
	m_resultPath = resultPath;
	if (!fs::exists(rootPath) || !fs::exists(resultPath)) {
		return false;
	}
	else 
	{
		const auto start = time.now();
		if (!AddFilePathsToQueue()) {
			return false;
		}
		else {
			SpawnThreads();
			const auto end = time.now();
			elapsedTime = static_cast<std::chrono::duration<double>>(end - start);
			if (!WriteInfoInFile(resultPath)) {
				return false;
			}
			else {
				return true;
			}
		}
	}
}

bool Analyzer::AddFilePathsToQueue()
{
	if (!exists(m_rootPath)) {
		return false;
	}
	else {
		for (auto& x : fs::recursive_directory_iterator(m_rootPath))
		{
			if (CheckFileExtension(x.path()) == true) {
				pathsQueue.push(x);
				processedFiles++;
			}
		}
		return true;
	}
}

bool Analyzer::CheckFileExtension(fs::path path)
{
	if (path.extension() == ".c" || path.extension() == ".h" ||
		path.extension() == ".cpp" || path.extension() == ".hpp")
	{
		return true;
	}
	return false;
}

void Analyzer::SpawnThreads()
{
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

void Analyzer::ProcessFiles()
{
	while (!pathsQueue.empty())
	{
		fs::path path = GetPathFromQueue();
		auto info = fileAnalizer.CountFileLines(path);
		RecordAnalysisResult(info);
	}
}

fs::path Analyzer::GetPathFromQueue()
{
	if (!pathsQueue.empty())
	{
		std::lock_guard<std::mutex> lockQ(mQueue);
		if (!pathsQueue.empty())
		{
			fs::path path = pathsQueue.front();
			pathsQueue.pop();
			return path;
		}
	}
	return "";
}

void Analyzer::RecordAnalysisResult(std::tuple<int, int, int> info)
{
	std::lock_guard<std::mutex> lockL(mLines);
	blankLines += std::get<0>(info);
	commentLines += std::get<1>(info);
	codeLines += std::get<2>(info);
}

bool Analyzer::WriteInfoInFile(std::filesystem::path path)
{
	if (!std::filesystem::exists(path)) {
		return false;
	}
	else {
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