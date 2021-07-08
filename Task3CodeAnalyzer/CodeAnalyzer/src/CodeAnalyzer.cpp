#include "CodeAnalyzer.h"


bool CodeAnalyzer::Analize(std::string& rootPath, std::string& resultPath)
{
	ClearUp();
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
		else 
		{
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

void CodeAnalyzer::ClearUp()
{
	if (!threadsVector.empty()) {
		threadsVector.clear();
	}
	if (m_commentLines != 0) {
		m_commentLines = 0;
	}
	if (m_codeLines != 0) {
		m_codeLines = 0;
	}
	if (m_blankLines != 0) {
		m_blankLines = 0;
	}
	if (!m_rootPath.empty()) {
		m_rootPath.clear();
	}
	if (!m_resultPath.empty()) {
		m_resultPath.clear();
	}
	if (m_processedFiles != 0) {
		m_processedFiles = 0;
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
			if (CheckFileExtension(path) == true)
			{
				pathsQueue.push(path);
				m_processedFiles++;
			}
		}
		else
		{
			for (auto& x : fs::recursive_directory_iterator(path))
			{
				fs::path path = x.path();
				if (CheckFileExtension(path) == true) {
					pathsQueue.push(x);
					m_processedFiles++;
				}
			}
		}
		return true;
	}
}

bool CodeAnalyzer::CheckFileExtension(fs::path& p)
{
	const std::string c = ".c";
	const std::string h = ".h";
	const std::string cpp = ".cpp";
	const std::string hpp = ".hpp";

	auto extension = p.extension();
	if (extension == c || extension == h ||
		extension == cpp || extension == hpp)
	{
		return true;
	}
	return false;
}

void CodeAnalyzer::SpawnThreads()
{
	unsigned int threadsCount = (m_processedFiles < std::thread::hardware_concurrency())
		? (m_processedFiles)
		: (std::thread::hardware_concurrency());
	for (unsigned int i = 0; i < threadsCount; i++)
	{
		threadsVector.push_back(std::thread([this]
			{
				ProcessFiles();
			}));
	}
	for (auto& it : threadsVector)
	{
		if (it.joinable()) {
			it.join();
		}
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
		auto info = fileAnalyzer.CountFileLines(path);
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
	m_blankLines += std::get<0>(info);
	m_commentLines += std::get<1>(info);
	m_codeLines += std::get<2>(info);
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
		out << "Processed files : " << m_processedFiles << '\n';
		out << "Blank lines : " << m_blankLines << '\n';
		out << "Comment lines : " << m_commentLines << '\n';
		out << "Code lines : " << m_codeLines << '\n';
		out << "Elapsed time : " << elapsedTime.count() << " seconds";
		out.close();
		return true;
	}
}