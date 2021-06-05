#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CodeAnalizerUnitTests
{
	TEST_CLASS(PathExistUnitTests)
	{
	public:
		TEST_METHOD(Incorrrect_Root_Path_Test)
		{
			root = "incorectRootPath";
			result = resultPath.u8string();
			Assert::IsFalse(analizer.Analize(root, result));
		}
		TEST_METHOD(Incorrrect_Result_Path_Test)
		{
			root = emptyFilepath.u8string();
			result = "incorectResultPath";
			Assert::IsFalse(analizer.Analize(root, result));
		}
		TEST_METHOD(Corrrect_Paths_Test)
		{
			root = emptyFilepath.u8string();
			result = resultPath.u8string();
			Assert::IsTrue(analizer.Analize(root, result));
		}
	private:
		CodeAnalyzer analizer;
		const fs::path solutionPath = fs::current_path();
		fs::path emptyFilepath = solutionPath.parent_path().parent_path()
			+= "/Task3CodeAnalizer/CodeAnalizerUnitTests/FilesExamples/emptyFile.cpp";
		fs::path resultPath = solutionPath.parent_path().parent_path()
			+= "/Task3CodeAnalizer/CodeAnalizerUnitTests/FilesExamples";
		std::string root;
		std::string result;
	};
}