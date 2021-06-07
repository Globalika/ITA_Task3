#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CodeAnalyzerUnitTests
{
	TEST_CLASS(FileExtensionUnitTests)
	{
	public:
		TEST_METHOD(Extensions_That_Are_Accepted)
		{
			fs::path f1 = "f1.c";
			Assert::IsTrue(analyzer.CheckFileExtension(f1));
			fs::path f2 = "f2.h";
			Assert::IsTrue(analyzer.CheckFileExtension(f2));
			fs::path f3 = "f3.cpp";
			Assert::IsTrue(analyzer.CheckFileExtension(f3));
			fs::path f4 = "f4.hpp";
			Assert::IsTrue(analyzer.CheckFileExtension(f4));
		}
		TEST_METHOD(Extensions_That_Are_Not_Accepted)
		{
			fs::path txt = "text.txt";
			Assert::IsFalse(analyzer.CheckFileExtension(txt));
			fs::path log = "log.txt";
			Assert::IsFalse(analyzer.CheckFileExtension(log));
			fs::path obj = "obj.txt";
			Assert::IsFalse(analyzer.CheckFileExtension(obj));
			fs::path lib = "text.lib";
			Assert::IsFalse(analyzer.CheckFileExtension(lib));
		}
	private:
		CodeAnalyzer analyzer;
	};
}
