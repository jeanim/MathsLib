#include "pch.h"
#include "CppUnitTest.h"
#include "..//MathsLib/Maths.h"
#include "..//MathsLib/Vector4.h"
#include "..//MathsLib/Vector2.h"

using std::string;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MathsLib;


namespace Tests
{
	TEST_CLASS(TestVector4)
	{
	public:
		static constexpr float eps = 0.0001f;

		TEST_METHOD(testNormalize)
		{
			Vector4 test;

			test = Vector4::UNIT_X;
			test.normalize();
			Assert::IsTrue(std::fabs(test.getLength() - eps) < 1.0f);

			test = Vector4::NEGATIVE_UNIT_Y;
			test.normalize();
			Assert::IsTrue(std::fabs(test.getLength() - eps) < 1.0f);

			test = Vector4(1.0f, 1.0f, 0.5f, -0.2f);
			test.normalize();
			Assert::IsTrue(std::fabs(test.getLength() - eps) < 1.0f);

			test.set(1.0f, 2.0f, 3.0f, 0.0f);
			test.normalize();
			Assert::IsTrue(std::fabs(test.getLength() - eps) < 1.0f);

			test.set(3.0f, 0.0f, 0.0f, 5.0f);
			test.normalize();
			Assert::IsTrue(std::fabs(test.getLength() - eps) < 1.0f);

			test.set(-3.0f, 0.5f, 1.0f, 1.0f);
			test.normalize();
			Assert::IsTrue(std::fabs(test.getLength() - eps) < 1.0f);
		}

		TEST_METHOD(testNormalize_ZeroVector_Expected_NoChange)
		{
			Vector4 vec{ 0, 0, 0, 0 };
			vec.normalize();

			Assert::AreEqual(0.0f, vec.x);
			Assert::AreEqual(0.0f, vec.y);
			Assert::AreEqual(0.0f, vec.z);
			Assert::AreEqual(0.0f, vec.w);
		}
		
		TEST_METHOD(addVectorVector)
		{
			Vector4 vec1{ 1.0f, 2.0f, 3.0f, 4.0f };
			Vector4 vec2{ 5.0f, 6.0f, 7.0f, 8.0f };

			Vector4 vec3 = vec1 + vec2;
			Assert::AreEqual(6.0f, vec3.x);
			Assert::AreEqual(8.0f, vec3.y);
			Assert::AreEqual(10.0f, vec3.z);
			Assert::AreEqual(12.0f, vec3.w);

			vec1 += vec2;
			Assert::AreEqual(6.0f, vec1.x);
			Assert::AreEqual(8.0f, vec1.y);
			Assert::AreEqual(10.0f, vec1.z);
			Assert::AreEqual(12.0f, vec1.w);

			vec1 = { 1.0f, 2.0f, 3.0f, 4.0f };
			vec1.add(vec2);
			Assert::AreEqual(6.0f, vec1.x);
			Assert::AreEqual(8.0f, vec1.y);
			Assert::AreEqual(10.0f, vec1.z);
			Assert::AreEqual(12.0f, vec1.w);
		}

		TEST_METHOD(addVectorNumber)
		{
			Vector4 vec1{ 1.0f, 2.0f, 3.0f, 4.0f };

			vec1.add(1.5f);
			Assert::AreEqual(2.5f, vec1.x);
			Assert::AreEqual(3.5f, vec1.y);
			Assert::AreEqual(4.5f, vec1.z);
			Assert::AreEqual(5.5f, vec1.w);
		}

		TEST_METHOD(subtractVectorVector)
		{
			Vector4 vec1{ 1.0f, 2.0f, 3.0f, 4.0f };
			Vector4 vec2{ 5.0f, 7.0f, 9.0f, 11.0f };

			Vector4 vec3 = vec1 - vec2;
			Assert::AreEqual(-4.0f, vec3.x);
			Assert::AreEqual(-5.0f, vec3.y);
			Assert::AreEqual(-6.0f, vec3.z);
			Assert::AreEqual(-7.0f, vec3.w);

			vec1 -= vec2;
			Assert::AreEqual(-4.0f, vec1.x);
			Assert::AreEqual(-5.0f, vec1.y);
			Assert::AreEqual(-6.0f, vec1.z);
			Assert::AreEqual(-7.0f, vec1.w);

			vec1 = { 1.0f, 2.0f, 3.0f, 4.0f };
			vec1.subtract(vec2);
			Assert::AreEqual(-4.0f, vec1.x);
			Assert::AreEqual(-5.0f, vec1.y);
			Assert::AreEqual(-6.0f, vec1.z);
			Assert::AreEqual(-7.0f, vec1.w);
		}

		TEST_METHOD(subscriptOperator)
		{
			Vector4 vec1{ 1.0f, 2.0f, 3.0f, 4.0f };

			Assert::AreEqual(1.0f, vec1[0]);
			Assert::AreEqual(2.0f, vec1[1]);
			Assert::AreEqual(3.0f, vec1[2]);
			Assert::AreEqual(4.0f, vec1[3]);
		}

		TEST_METHOD(testDotProduct)
		{
			Vector4 test1;
			Vector4 test2;

			test1 = Vector4::UNIT_X;
			test2 = Vector4::UNIT_Y;
			Assert::IsTrue(std::fabs(test1.dotProduct(test2)) - eps < 0.0f);

			test2 = Vector4::NEGATIVE_UNIT_Y;
			Assert::IsTrue(std::fabs(test1.dotProduct(test2)) - eps < 0.0f);

			test1 = Vector4(Vector2::UNIT_X);
			test2 = Vector4::UNIT_X;
			Assert::IsTrue(std::fabs(test1.dotProduct(test2)) + eps > 1.0f);

			test1 = Vector4::UNIT_Z;
			test2 = Vector4::UNIT_W;
			Assert::IsTrue(test1.dotProduct(test2) == (test1.z * test2.z + test1.w * test2.w));
		}
	};
}