#include "pch.h"
#include "CppUnitTest.h"
#include "..//MathsLib/Maths.h"
#include "..//MathsLib/Matrix3x3.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MathsLib;

namespace Tests
{
	TEST_CLASS(TestMatrix3x3)
	{
		TEST_METHOD(TestToString)
		{
			Matrix3x3 matrix{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

			std::string expected = "1 2 3 4 5 6 7 8 9";
			std::string actual = matrix.toString();
			Assert::AreEqual(expected, actual);
		}
	};
}