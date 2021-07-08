#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CodeAnalyzerUnitTests
{
	TEST_CLASS(FileExtensionUnitTests)
	{
	public:
		TEST_METHOD(Check_Extension_c)
		{
			fs::path f1 = "f1.c";
			Assert::IsTrue(analyzer.CheckFileExtension(f1));
		}
		TEST_METHOD(Check_Extension_h)
		{
			fs::path f2 = "f2.h";
			Assert::IsTrue(analyzer.CheckFileExtension(f2));
		}
		TEST_METHOD(Check_Extension_cpp)
		{
			fs::path f3 = "f3.cpp";
			Assert::IsTrue(analyzer.CheckFileExtension(f3));
		}
		TEST_METHOD(Check_Extension_hpp)
		{
			fs::path f4 = "f4.hpp";
			Assert::IsTrue(analyzer.CheckFileExtension(f4));
		}
		TEST_METHOD(Check_Extension_txt)
		{
			fs::path f4 = "f5.txt";
			Assert::IsFalse(analyzer.CheckFileExtension(f4));
		}
		TEST_METHOD(Check_Extension_lib)
		{
			fs::path f4 = "f6.lib";
			Assert::IsFalse(analyzer.CheckFileExtension(f4));
		}
		TEST_METHOD(Check_Extension_obj)
		{
			fs::path f4 = "f7.obj";
			Assert::IsFalse(analyzer.CheckFileExtension(f4));
		}
		TEST_METHOD(Check_Extension_log)
		{
			fs::path f4 = "f8.log";
			Assert::IsFalse(analyzer.CheckFileExtension(f4));
		}
	private:
		CodeAnalyzer analyzer;
	};
}
