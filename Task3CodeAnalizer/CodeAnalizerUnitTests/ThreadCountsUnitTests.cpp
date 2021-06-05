#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CodeAnalizerUnitTests
{
	TEST_CLASS(ThreadCountsUnitTests)
	{
	public:
		TEST_METHOD(Queue_With_Five_Files)
		{
			unsigned int expectedProcessedFiles = std::thread::hardware_concurrency();
			analizer.AddFilePathsToQueue(directoryWithFiveFilesPath);
			analizer.SpawnThreads();
			Assert::AreEqual(expectedProcessedFiles, analizer.GetTheadsAmountUsed());
		}
		TEST_METHOD(Queue_With_Two_Files)
		{
			unsigned int expectedProcessedFiles = 2;
			analizer.AddFilePathsToQueue(directoryWithTwoFilesPath);
			analizer.SpawnThreads();
			Assert::AreEqual(expectedProcessedFiles, analizer.GetTheadsAmountUsed());
		}
	private:
		CodeAnalyzer analizer;
		const fs::path solutionPath = fs::current_path();
		fs::path directoryWithTwoFilesPath = solutionPath.parent_path().parent_path()
			+= "/Task3CodeAnalizer/CodeAnalizerUnitTests/DirectoryWithTwoFiles";
		fs::path directoryWithFiveFilesPath = solutionPath.parent_path().parent_path()
			+= "/Task3CodeAnalizer/CodeAnalizerUnitTests/DirectoryWithFiveFiles";
	};
}