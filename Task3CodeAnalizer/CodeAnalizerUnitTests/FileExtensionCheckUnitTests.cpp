#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CodeAnalizerUnitTests
{
	TEST_CLASS(FileExtensionCheckUnitTests)
	{
	public:
		TEST_METHOD(Extensions_That_Are_accepted)
		{
			fs::path f1 = "f1.c";
			Assert::IsTrue(analizer.CheckFileExtension(f1));
			fs::path f2 = "f2.h";
			Assert::IsTrue(analizer.CheckFileExtension(f2));
			fs::path f3 = "f3.cpp";
			Assert::IsTrue(analizer.CheckFileExtension(f3));
			fs::path f4 = "f4.hpp";
			Assert::IsTrue(analizer.CheckFileExtension(f4));
		}
		TEST_METHOD(Extensions_That_Are_Not_accepted)
		{
			fs::path txt = "text.txt";
			Assert::IsFalse(analizer.CheckFileExtension(txt));
			fs::path log = "log.txt";
			Assert::IsFalse(analizer.CheckFileExtension(log));
			fs::path obj = "obj.txt";
			Assert::IsFalse(analizer.CheckFileExtension(obj));
			fs::path lib = "text.lib";
			Assert::IsFalse(analizer.CheckFileExtension(lib));
		}
	private:
		CodeAnalyzer analizer;
	};
}