#include "pch.h"
#include "CppUnitTest.h"
#include "../MathsLib/Maths.h"
#include "../MathsLib/FuncSplit.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MathsLib;

namespace Tests
{
	TEST_CLASS(TestFuncSplit)
	{
	public:
		TEST_METHOD(testSplitting)
		{
			FuncSplit <std::string> splitter;
			std::vector <std::string> vecValues;
			splitter("test string,at;test", vecValues, " ,;");

			Assert::AreEqual(4, (int)vecValues.size());
			Assert::AreEqual(std::string{ "test" }, vecValues[0]);
			Assert::AreEqual(std::string{ "string" }, vecValues[1]);
			Assert::AreEqual(std::string{ "at" }, vecValues[2]);
			Assert::AreEqual(std::string{ "test" }, vecValues[3]);
		}

		TEST_METHOD(testSplitting_2)
		{
			FuncSplit <std::string> splitter;
			std::vector <std::string> vecValues;
			splitter("test string,at;test", vecValues, ",");

			Assert::AreEqual(2, (int)vecValues.size());
			Assert::AreEqual(std::string{ "test string" }, vecValues[0]);
			Assert::AreEqual(std::string{ "at;test" }, vecValues[1]);
		}

		TEST_METHOD(testSplitting_Extra_Spaces)
		{
			FuncSplit <std::string> splitter;
			std::vector <std::string> vecValues;
			splitter(" test  string,at; test  ", vecValues, " ,;");

			Assert::AreEqual(4, (int)vecValues.size());
			Assert::AreEqual(std::string{ "test" }, vecValues[0]);
			Assert::AreEqual(std::string{ "string" }, vecValues[1]);
			Assert::AreEqual(std::string{ "at" }, vecValues[2]);
			Assert::AreEqual(std::string{ "test" }, vecValues[3]);
		}
	};
}