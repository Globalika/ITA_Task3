#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CodeAnalyzerUnitTests
{
	TEST_CLASS(FilesLineUnitTests)
	{
	public:
		TEST_METHOD(File_With_Blank_Lines_Check)
		{
			expectedBlankLines = 3;
			auto info = analyzer.CountFileLines(emptyFilepath);
			actualBlankLines = std::get<0>(info);
			Assert::AreEqual(expectedBlankLines, actualBlankLines);
		}
		TEST_METHOD(File_With_Code_Only_Lines_Check)
		{
			expectedCodeLines = 6;
			auto info = analyzer.CountFileLines(fileWithCodeOnlypath);
			actualCodeLines = std::get<2>(info);
			Assert::AreEqual(expectedCodeLines, actualCodeLines);

		}
		TEST_METHOD(File_With_Comment_Only_Lines_Check)
		{
			expectedCommentLines = 8;
			auto info = analyzer.CountFileLines(fileWithCommentOnlyPath);
			actualCommentLines = std::get<1>(info);
			Assert::AreEqual(expectedCommentLines, actualCommentLines);
		}
		TEST_METHOD(File_With_Mix_Lines_Check)
		{
			expectedCodeLines = 7;
			auto info = analyzer.CountFileLines(fileWithMixLinesPath);
			actualCodeLines = std::get<2>(info);
			Assert::AreEqual(expectedCodeLines, actualCodeLines);
		}
		TEST_METHOD(File_With_Code_And_Comment_Lines_Only_Check)
		{
			expectedCommentLines = 6;
			auto info = analyzer.CountFileLines(fileWithCodeAndCommentLinesPath);
			actualCommentLines = std::get<1>(info);
			Assert::AreEqual(expectedCommentLines, actualCommentLines);
		}
	private:
		FileAnalyzer analyzer;
		const fs::path solutionPath = fs::current_path();
		fs::path emptyFilepath = solutionPath.parent_path().parent_path()
			+= "/Task3CodeAnalyzer/CodeAnalyzerUnitTests/FileExamples/emptyFile.cpp";
		fs::path fileWithCodeOnlypath = solutionPath.parent_path().parent_path()
			+= "/Task3CodeAnalyzer/CodeAnalyzerUnitTests/FileExamples/fileWithCodeOnly.cpp";
		fs::path fileWithCommentOnlyPath = solutionPath.parent_path().parent_path()
			+= "/Task3CodeAnalyzer/CodeAnalyzerUnitTests/FileExamples/fileWithCommentOnly.cpp";
		fs::path fileWithMixLinesPath = solutionPath.parent_path().parent_path()
			+= "/Task3CodeAnalyzer/CodeAnalyzerUnitTests/FileExamples/fileWithMixLines.cpp";
		fs::path fileWithCodeAndCommentLinesPath = solutionPath.parent_path().parent_path()
			+= "/Task3CodeAnalyzer/CodeAnalyzerUnitTests/FileExamples/fileWithCodeAndCommentLinesPath.cpp";
		int expectedBlankLines = 0;
		int expectedCommentLines = 0;
		int expectedCodeLines = 0;
		int actualBlankLines = 0;
		int actualCommentLines = 0;
		int actualCodeLines = 0;
	};
}