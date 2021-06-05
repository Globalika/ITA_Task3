#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CodeAnalizerUnitTests
{
	TEST_CLASS(FilesLineCheckUnitTests)
	{
	public:
		TEST_METHOD(File_With_Blank_Lines_Check)
		{
			expectedBlankLines = 3;
			expectedCommentLines = 0;
			expectedCodeLines = 0;
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
			expectedBlankLines = 0;
			expectedCommentLines = 0;
			expectedCodeLines = 6;
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
			expectedBlankLines = 0;
			expectedCommentLines = 8;
			expectedCodeLines = 0;
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
			expectedBlankLines = 3;
			expectedCommentLines = 5;
			expectedCodeLines = 7;
			auto info = analyzer.CountFileLines(fileWithMixLinesPath);
			actualBlankLines = std::get<0>(info);
			actualCommentLines = std::get<1>(info);
			actualCodeLines = std::get<2>(info);
			Assert::AreEqual(expectedBlankLines, actualBlankLines);
			Assert::AreEqual(expectedCommentLines, actualCommentLines);
			Assert::AreEqual(expectedCodeLines, actualCodeLines);
		}
		TEST_METHOD(File_With_Code_And_Comment_Lines_Only_Check)
		{
			expectedBlankLines = 0;
			expectedCommentLines = 6;
			expectedCodeLines = 6;
			auto info = analyzer.CountFileLines(fileWithCodeAndCommentLinesPath);
			actualBlankLines = std::get<0>(info);
			actualCommentLines = std::get<1>(info);
			actualCodeLines = std::get<2>(info);
			Assert::AreEqual(expectedBlankLines, actualBlankLines);
			Assert::AreEqual(expectedCommentLines, actualCommentLines);
			Assert::AreEqual(expectedCodeLines, actualCodeLines);
		}
	private:
		FileAnalizer analyzer;
		const fs::path solutionPath = fs::current_path();
		fs::path emptyFilepath = solutionPath.parent_path().parent_path()
			+= "/Task3CodeAnalizer/CodeAnalizerUnitTests/FilesExamples/emptyFile.cpp";
		fs::path fileWithCodeOnlypath = solutionPath.parent_path().parent_path()
			+= "/Task3CodeAnalizer/CodeAnalizerUnitTests/FilesExamples/fileWithCodeOnly.cpp";
		fs::path fileWithCommentOnlyPath = solutionPath.parent_path().parent_path()
			+= "/Task3CodeAnalizer/CodeAnalizerUnitTests/FilesExamples/fileWithCommentOnly.cpp";
		fs::path fileWithMixLinesPath = solutionPath.parent_path().parent_path()
			+= "/Task3CodeAnalizer/CodeAnalizerUnitTests/FilesExamples/fileWithMixLines.cpp";
		fs::path fileWithCodeAndCommentLinesPath = solutionPath.parent_path().parent_path()
			+= "/Task3CodeAnalizer/CodeAnalizerUnitTests/FilesExamples/fileWithCodeAndCommentLinesPath.cpp";
		int expectedBlankLines = 0;
		int expectedCommentLines = 0;
		int expectedCodeLines = 0;
		int actualBlankLines = 0;
		int actualCommentLines = 0;
		int actualCodeLines = 0;
	};
}