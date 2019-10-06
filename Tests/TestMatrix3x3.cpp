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
		TEST_METHOD(testToString)
		{
			Matrix3x3 matrix{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

			std::string expected = "1 2 3 4 5 6 7 8 9";
			std::string actual = matrix.toString();
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(testIdentity)
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

		TEST_METHOD(testCreation)
		{
			Matrix3x3 mat(1, 2, 3, 4, 5, 6, 7, 8, 9);
			for (int i = 0; i < 9; ++i)
				Assert::AreEqual((float)(i + 1), mat.m[i]);

			mat.zero();
			Assert::IsTrue(mat._m11 == 0 && mat._m12 == 0 && mat._m13 == 0 && 
				mat._m21 == 0 && mat._m22 == 0 && mat._m23 == 0 && 
				mat._m31 == 0 && mat._m32 == 0 && mat._m33 == 0);
			Assert::IsTrue(mat.isZero());
		}

		TEST_METHOD(testNegate)
		{
			Matrix3x3 mat(1, 2, 3, 4, 5, 6, 7, 8, 9);
			for (int i = 0; i < 9; ++i)
				Assert::AreEqual((float)(i + 1), mat.m[i]);

			mat.negate();
			for (int i = 0; i < 9; ++i)
				Assert::AreEqual(-(float)(i + 1), mat.m[i]);
			Assert::IsTrue(!mat.isZero());
		}

		TEST_METHOD(testEquality_Expected_True)
		{
			Matrix3x3 mat1{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
			Matrix3x3 mat2{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

			Assert::IsTrue(mat1 == mat2);
			mat1 = mat2;
			Assert::IsTrue(mat1 == mat2);
		}

		TEST_METHOD(testEquality_Expected_False)
		{
			Matrix3x3 mat1{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
			Matrix3x3 mat2{ 2, 2, 3, 4, 5, 6, 7, 8, 9 };

			Assert::IsFalse(mat1 == mat2);
			mat2.identity();
			Assert::IsFalse(mat1 == mat2);
		}

		TEST_METHOD(testTranspose)
		{
			Matrix3x3 mat{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
			mat.transpose();
			Assert::IsTrue(mat == Matrix3x3{ 1, 4, 7, 2, 5, 8, 3, 6, 9 });
		}

		TEST_METHOD(testMultiplicationByIdentityMatrix_Expected_Same)
		{
			Matrix3x3 mat1{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
			Matrix3x3 mat2{ 10,11,12,13,14,15,16,17,18 };
			Matrix3x3 mat0;

			mat2.identity();
			mat0 = mat1;
			mat0.multiply(mat2);
			Assert::IsTrue(mat0 == mat1);
		}

		TEST_METHOD(testMultiplicationByOtherMatrix)
		{
			Matrix3x3 mat1{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
			Matrix3x3 mat2{ 10,11,12,13,14,15,16,17,18 };
			Matrix3x3 mat0;
			Matrix3x3 result{ 84,90,96,201,216,231,318,342,366 };

			mat0 = mat1;
			mat0.multiply(mat2);
			Assert::IsTrue(mat0 == result);
		}

		TEST_METHOD(testMultiplicationByNumber)
		{
			Matrix3x3 mat1{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
			Matrix3x3 mat0;

			mat0 = mat1;
			mat0.multiply(2);
			Assert::IsTrue(mat0 == 2 * mat1);

			mat0 = mat1;
			mat0 *= 2.0f;
			Assert::IsTrue(mat0 == 2 * mat1);
		}

		TEST_METHOD(testMultiplicationByZero_Expected_ZeroMatrix)
		{
			Matrix3x3 mat1{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
			Matrix3x3 mat0;

			mat0 = mat1;
			mat0.multiply(0);
			Assert::IsTrue(mat0.isZero());

			mat0 = mat1;
			mat0 *= 0.0f;
			Assert::IsTrue(mat0.isZero());
		}
	};
}