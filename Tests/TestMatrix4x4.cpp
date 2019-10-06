#include "pch.h"
#include "CppUnitTest.h"
#include "..//MathsLib/Maths.h"
#include "..//MathsLib/Matrix4x4.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MathsLib;

namespace Tests
{
	TEST_CLASS(TestMatrix4x4)
	{
		TEST_METHOD(testToString)
		{
			Matrix4x4 matrix{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };

			std::string expected = "1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16";
			std::string actual = matrix.toString();
			Assert::AreEqual(expected, actual);
		}

		TEST_METHOD(testIdentity)
		{
			Matrix4x4 matrix;
			matrix.identity();

			for (int i = 0; i < 16; ++i) {
				if (i == 0 || i == 5 || i == 10 || i == 15)
					Assert::AreEqual(1.0f, matrix.m[i]);
				else
					Assert::AreEqual(0.0f, matrix.m[i]);
			}

			Assert::IsTrue(matrix.isIdentity());
		}

		TEST_METHOD(testCreation)
		{
			Matrix4x4 mat(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
			for (int i = 0; i < 16; ++i)
				Assert::AreEqual((float)(i + 1), mat.m[i]);

			mat.zero();
			Assert::IsTrue(mat._m11 == 0 && mat._m12 == 0 && mat._m13 == 0 && mat._m14 == 0 &&
				mat._m21 == 0 && mat._m22 == 0 && mat._m23 == 0 && mat._m24 == 0 &&
				mat._m31 == 0 && mat._m32 == 0 && mat._m33 == 0 && mat._m34 == 0 &&
				mat._m41 == 0 && mat._m42 == 0 && mat._m43 == 0 && mat._m44 == 0);
			Assert::IsTrue(mat.isZero());
		}

		TEST_METHOD(testEquality_Expected_True)
		{
			Matrix4x4 mat1{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
			Matrix4x4 mat2{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };

			Assert::IsTrue(mat1 == mat2);
			mat1 = mat2;
			Assert::IsTrue(mat1 == mat2);
		}

		TEST_METHOD(testEquality_Expected_False)
		{
			Matrix4x4 mat1{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
			Matrix4x4 mat2{ 2, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };

			Assert::IsFalse(mat1 == mat2);
			mat2.identity();
			Assert::IsFalse(mat1 == mat2);
		}

		TEST_METHOD(testNegate)
		{
			Matrix4x4 mat(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
			for (int i = 0; i < 16; ++i)
				Assert::AreEqual((float)(i + 1), mat.m[i]);

			mat.negate();
			for (int i = 0; i < 16; ++i)
				Assert::AreEqual(-(float)(i + 1), mat.m[i]);
			Assert::IsTrue(!mat.isZero());
		}

		TEST_METHOD(testInvert)
		{
			Matrix4x4 mat(1, 1, 1, 1, 1, 1, -1, -1, 1, -1, 1, -1, 1, -1, -1, 1);
			mat.invert();
			Assert::IsTrue(mat == Matrix4x4(0.25, 0.25, 0.25, 0.25,
				0.25, 0.25, -0.25, -0.25,
				0.25, -0.25, 0.25, -0.25,
				0.25, -0.25, -0.25, 0.25));

			mat.set(1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1);
			mat.invert();
			Assert::IsTrue(mat == Matrix4x4(1, 0, 0, 0,
				1, 1, 1, -1,
				-1, -1, 0, 1,
				0, 1, 0, 0));

			Matrix4x4 mat2(0, 0, 0, 0, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
			mat = mat2;
			mat.invert();
			Assert::IsTrue(mat == mat2);
		}

		TEST_METHOD(testDeterminant)
		{
			Matrix4x4 mat(2, -2, 0, 1, 0, -1, 0, 2, 0, 0, 3, 0, 0, 0, 0, 1);
			Assert::AreEqual(-6.0f, mat.determinant());

			mat.set(1, -2, 0, 1, 0, 0, 0, 2, -1, 0, 3, 0, 0, -1, 2, 0);
			Assert::AreEqual(-2.0f, mat.determinant());

			mat.set(0, 0, 0, 0, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
			Assert::AreEqual(0.0f, mat.determinant());
		}

		TEST_METHOD(testTranspose)
		{
			Matrix4x4 mat(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
			mat.transpose();
			Assert::IsTrue(mat == Matrix4x4(1, 5, 9, 13,
				2, 6, 10, 14,
				3, 7, 11, 15,
				4, 8, 12, 16));

			Maths::setUseSSE(true);
			mat = Matrix4x4{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
			mat.transpose();
			Assert::IsTrue(mat == Matrix4x4(1, 5, 9, 13,
				2, 6, 10, 14,
				3, 7, 11, 15,
				4, 8, 12, 16));
		}

		TEST_METHOD(testAddition)
		{
			Matrix4x4 mat1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
			Matrix4x4 mat2(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

			Matrix4x4 mat0 = mat1;
			mat0.add(mat2);
			Assert::IsTrue(mat0 == 2 * mat1);

			mat0 = add(mat1, mat2);
			Assert::IsTrue(mat0 == 2 * mat1);

			mat0 = mat1;
			mat0 += mat1;
			Assert::IsTrue(mat0 == 2 * mat1);

			mat0 = mat1 + mat2;
			Assert::IsTrue(mat0 == 2 * mat1);
		}

		TEST_METHOD(testSubtraction)
		{
			Matrix4x4 mat1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
			Matrix4x4 mat2(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
			Matrix4x4 mat0;

			mat0.zero();
			mat0.subtract(mat2);
			Assert::IsTrue(mat0 == -mat1);

			mat0 = subtract(mat1, mat2);
			Assert::IsTrue(mat0.isZero());

			mat0.zero();
			mat0 -= mat1;
			Assert::IsTrue(mat0 == -mat1);

			mat0 = mat1 - mat2;
			Assert::IsTrue(mat0.isZero());
		}

		TEST_METHOD(testMultiplicationByIdentityMatrix_Expected_Same)
		{
			Matrix4x4 mat1{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
			Matrix4x4 mat2;
			Matrix4x4 mat0;

			mat2.identity();
			mat0 = mat1;
			mat0.multiply(mat2);
			Assert::IsTrue(mat0 == mat1);
		}

		TEST_METHOD(testMultiplicationByOtherMatrix)
		{
			Matrix4x4 mat1{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
			Matrix4x4 mat2;
			Matrix4x4 mat0;

			mat0 = mat2;
			mat0.multiply(mat1);
			Assert::IsTrue(mat0 == mat1);
		}

		TEST_METHOD(testMultiplicationByNumber)
		{
			Matrix4x4 mat1{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
			Matrix4x4 mat2;
			Matrix4x4 mat0;

			mat0 = mat1;
			mat0.multiply(2);
			Assert::IsTrue(mat0 == 2 * mat1);

			mat0 = mat1;
			mat0 *= 2.0f;
			Assert::IsTrue(mat0 == 2 * mat1);
		}

		TEST_METHOD(testMultiplicationByZero_Expected_ZeroMatrix)
		{
			Matrix4x4 mat1(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
			Matrix4x4 mat2;
			Matrix4x4 mat0;

			mat0 = mat1;
			mat0.multiply(0);
			Assert::IsTrue(mat0.isZero());

			mat0 = mat1;
			mat0 *= 0.0f;
			Assert::IsTrue(mat0.isZero());
		}

		TEST_METHOD(testVector4MatMultiplication)
		{
			Matrix4x4 mat;
			Vector4 vec;
			Vector4 res;

			mat.identity();
			vec.set(1.0f, 2.0f, 3.0f, 4.0f);
			res = mat.multiply(vec);
			Assert::IsTrue(res == vec);

			mat.set(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
			res = mat * vec;
			Assert::IsTrue(res == Vector4(1 * 1 + 2 * 2 + 3 * 3 + 4 * 4,
				5 * 1 + 6 * 2 + 7 * 3 + 8 * 4,
				9 * 1 + 10 * 2 + 11 * 3 + 12 * 4,
				13 * 1 + 14 * 2 + 15 * 3 + 16 * 4));

			vec.set(17.0f, 18.0f, 19.0f, 20.0f);
			res = mat * vec;
			Assert::IsTrue(res == Vector4(1 * 17 + 2 * 18 + 3 * 19 + 4 * 20,
				5 * 17 + 6 * 18 + 7 * 19 + 8 * 20,
				9 * 17 + 10 * 18 + 11 * 19 + 12 * 20,
				13 * 17 + 14 * 18 + 15 * 19 + 16 * 20));
		}
	};
}