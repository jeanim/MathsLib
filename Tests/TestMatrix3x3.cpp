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

		TEST_METHOD(TestIdentity)
		{
			Matrix3x3 matrix;
			matrix.identity();

			Assert::AreEqual(1.0f, matrix.m[0]);
			Assert::AreEqual(0.0f, matrix.m[1]);
			Assert::AreEqual(0.0f, matrix.m[2]);
			Assert::AreEqual(0.0f, matrix.m[3]);
			Assert::AreEqual(1.0f, matrix.m[4]);
			Assert::AreEqual(0.0f, matrix.m[5]);
			Assert::AreEqual(0.0f, matrix.m[6]);
			Assert::AreEqual(0.0f, matrix.m[7]);
			Assert::AreEqual(1.0f, matrix.m[8]);
		}
	};
}