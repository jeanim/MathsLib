#include "pch.h"
#include "CppUnitTest.h"
#include "..//MathsLib/Maths.h"
#include "..//MathsLib/Vector3.h"
#include "..//MathsLib/Plane.h"

using std::string;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MathsLib;


namespace Tests
{
	TEST_CLASS(TestVector3)
	{
	public:
		static constexpr float eps = 0.0001f;


		TEST_METHOD(testNormalize)
		{
			Vector3 test;

			test = Vector3::UNIT_X;
			test.normalize();
			Assert::IsTrue(std::fabs(test.getLength() - eps) < 1.0f);

			test = Vector3::NEGATIVE_UNIT_Y;
			test.normalize();
			Assert::IsTrue(std::fabs(test.getLength() - eps) < 1.0f);

			test = Vector3(1.0f, 1.0f, 1.0f);
			test.normalize();
			Assert::IsTrue(std::fabs(test.getLength() - eps) < 1.0f);

			test.set(1.0f, 2.0f, 1.0f);
			test.normalize();
			Assert::IsTrue(std::fabs(test.getLength() - eps) < 1.0f);

			test.set(3.0f, 0.0f, 1.0f);
			test.normalize();
			Assert::IsTrue(std::fabs(test.getLength() - eps) < 1.0f);
		}

		TEST_METHOD(testNormalize_ZeroVector_Expected_NoChange)
		{
			Vector3 vec{ 0, 0, 0 };
			vec.normalize();

			Assert::AreEqual(0.0f, vec.x);
			Assert::AreEqual(0.0f, vec.y);
			Assert::AreEqual(0.0f, vec.z);
		}

		TEST_METHOD(addVectorVector)
		{
			Vector3 vec1{ 1.0f, 2.0f, 3.0f };
			Vector3 vec2{ 4.0f, 5.0f, 6.0f };

			Vector3 vec3 = vec1 + vec2;
			Assert::AreEqual(5.0f, vec3.x);
			Assert::AreEqual(7.0f, vec3.y);
			Assert::AreEqual(9.0f, vec3.z);

			vec1 += vec2;
			Assert::AreEqual(5.0f, vec1.x);
			Assert::AreEqual(7.0f, vec1.y);
			Assert::AreEqual(9.0f, vec1.z);

			vec1 = { 1.0f, 2.0f, 3.0f };
			vec1.add(vec2);
			Assert::AreEqual(5.0f, vec1.x);
			Assert::AreEqual(7.0f, vec1.y);
			Assert::AreEqual(9.0f, vec1.z);
		}

		TEST_METHOD(addVectorNumber)
		{
			Vector3 vec1{ 1.0f, 2.0f, 3.0f };

			vec1.add(1.5f);
			Assert::AreEqual(2.5f, vec1.x);
			Assert::AreEqual(3.5f, vec1.y);
			Assert::AreEqual(4.5f, vec1.z);
		}

		TEST_METHOD(subtractVectorVector)
		{
			Vector3 vec1{ 1.0f, 2.0f, 3.0f };
			Vector3 vec2{ 4.0f, 6.0f, 8.0f };

			Vector3 vec3 = vec1 - vec2;
			Assert::AreEqual(-3.0f, vec3.x);
			Assert::AreEqual(-4.0f, vec3.y);
			Assert::AreEqual(-5.0f, vec3.z);

			vec1 -= vec2;
			Assert::AreEqual(-3.0f, vec1.x);
			Assert::AreEqual(-4.0f, vec1.y);
			Assert::AreEqual(-5.0f, vec1.z);

			vec1 = { 1.0f, 2.0f, 3.0f };
			vec1.subtract(vec2);
			Assert::AreEqual(-3.0f, vec1.x);
			Assert::AreEqual(-4.0f, vec1.y);
			Assert::AreEqual(-5.0f, vec1.z);
		}

		TEST_METHOD(subscriptOperator)
		{
			Vector3 vec1{ 1.0f, 2.0f, 3.0f };

			Assert::AreEqual(1.0f, vec1[0]);
			Assert::AreEqual(2.0f, vec1[1]);
			Assert::AreEqual(3.0f, vec1[2]);
		}

		TEST_METHOD(testDotProduct)
		{
			Vector3 test1;
			Vector3 test2;

			test1 = Vector3::UNIT_X;
			test2 = Vector3::UNIT_Y;
			Assert::IsTrue(std::fabs(test1.dotProduct(test2)) - eps < 0.0f);

			test2 = Vector3::NEGATIVE_UNIT_Y;
			Assert::IsTrue(std::fabs(test1.dotProduct(test2)) - eps < 0.0f);

			test1 = Vector3::UNIT_X;
			test2 = Vector3::UNIT_Z;
			Assert::IsTrue(std::fabs(test1.dotProduct(test2)) - eps < 0.0f);

			test1 = Vector3::UNIT_X;
			test2 = Vector3::UNIT_X;
			Assert::IsTrue(std::fabs(test1.dotProduct(test2)) + eps > 1.0f);
		}

		TEST_METHOD(testCrossProduct)
		{
			Vector3 test1;
			Vector3 test2;

			test1 = Vector3::UNIT_X;
			test2 = Vector3::UNIT_Y;
			Assert::IsTrue(test1.crossProduct(test2) == Vector3::UNIT_Z);
			Assert::IsTrue(test2.crossProduct(test1) == Vector3::NEGATIVE_UNIT_Z);

			test1 = Vector3::UNIT_X;
			test2 = Vector3::UNIT_Z;
			Assert::IsTrue(test1.crossProduct(test2) == Vector3::NEGATIVE_UNIT_Y);
			Assert::IsTrue(test2.crossProduct(test1) == Vector3::UNIT_Y);
		}

		TEST_METHOD(testReflect)
		{
			Plane plane{ Vector3::UNIT_Y, 0.0f };
			Vector3 vec{ 1.0f, -2.0f, 3.0f };

			Vector3 reflected = vec.reflect(plane);

			Assert::IsTrue(reflected == Vector3{1.0f, 2.0f, 3.0f});
		}
	};
}