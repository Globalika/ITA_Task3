#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CodeAnalizerUnitTests
{
	TEST_CLASS(FilesCheckUnitTests)
	{
	public:
		TEST_METHOD(File_With_Blank_Lines_Check)
		{
			int expectedBlankLines = 3;
			int expectedCommentLines = 0;
			int expectedCodeLines = 0;
			auto info = analyzer.CountFileLines(emptyFilepath);
			actualBlankLines = std::get<0>(info);
			actualCommentLines = std::get<1>(info);
			actualCodeLines = std::get<2>(info);
			Assert::AreEqual(expectedBlankLines, actualBlankLines);
			Assert::AreEqual(expectedCommentLines, actualCommentLines);
			Assert::AreEqual(expectedCodeLines, actualCodeLines);
		}
		TEST_METHOD(File_With_Code_Only_Lines_Check)
		{
			int expectedBlankLines = 0;
			int expectedCommentLines = 0;
			int expectedCodeLines = 6;
			auto info = analyzer.CountFileLines(fileWithCodeOnlypath);
			actualBlankLines = std::get<0>(info);
			actualCommentLines = std::get<1>(info);
			actualCodeLines = std::get<2>(info);
			Assert::AreEqual(expectedBlankLines, actualBlankLines);
			Assert::AreEqual(expectedCommentLines, actualCommentLines);
			Assert::AreEqual(expectedCodeLines, actualCodeLines);

		}
		TEST_METHOD(File_With_Comment_Only_Lines_Check)
		{
			int expectedBlankLines = 0;
			int expectedCommentLines = 8;
			int expectedCodeLines = 0;
			auto info = analyzer.CountFileLines(fileWithCommentOnlyPath);
			actualBlankLines = std::get<0>(info);
			actualCommentLines = std::get<1>(info);
			actualCodeLines = std::get<2>(info);
			Assert::AreEqual(expectedBlankLines, actualBlankLines);
			Assert::AreEqual(expectedCommentLines, actualCommentLines);
			Assert::AreEqual(expectedCodeLines, actualCodeLines);
		}
		TEST_METHOD(File_With_Mix_Lines_Check)
		{
			int expectedBlankLines = 3;
			int expectedCommentLines = 5;
			int expectedCodeLines = 7;
			auto info = analyzer.CountFileLines(fileWithMixLinesPath);
			actualBlankLines = std::get<0>(info);
			actualCommentLines = std::get<1>(info);
			actualCodeLines = std::get<2>(info);
			Assert::AreEqual(expectedBlankLines, actualBlankLines);
			Assert::AreEqual(expectedCommentLines, actualCommentLines);
			Assert::AreEqual(expectedCodeLines, actualCodeLines);
		}
	private:
		FileAnalizer analyzer;
		fs::path projectPath = fs::current_path();
		fs::path emptyFilepath = projectPath.parent_path().parent_path() 
			+= "/Task3CodeAnalizer/CodeAnalizerUnitTests/FilesExamples/emptyFile.cpp";
		fs::path fileWithCodeOnlypath = projectPath.parent_path().parent_path() 
			+= "/Task3CodeAnalizer/CodeAnalizerUnitTests/FilesExamples/fileWithCodeOnly.cpp";
		fs::path fileWithCommentOnlyPath = projectPath.parent_path().parent_path() 
			+= "/Task3CodeAnalizer/CodeAnalizerUnitTests/FilesExamples/fileWithCommentOnly.cpp";
		fs::path fileWithMixLinesPath = projectPath.parent_path().parent_path() 
			+= "/Task3CodeAnalizer/CodeAnalizerUnitTests/FilesExamples/fileWithMixLines.cpp";
		int actualBlankLines = 0;
		int actualCommentLines = 0;
		int actualCodeLines = 0;
	};
}
