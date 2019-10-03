#include "pch.h"
#include "CppUnitTest.h"
#include "..//MathsLib/Maths.h"
#include "..//MathsLib/Vector2.h"

using std::string;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MathsLib;


namespace Tests
{
	TEST_CLASS(TestVector2)
	{
	public:
		static constexpr float eps = 0.0001f;


		TEST_METHOD(testNormalize)
		{
			Vector2 test;

			test = Vector2::UNIT_X;
			test.normalize();
			Assert::IsTrue(std::fabs(test.getLength() - eps) < 1.0f);

			test = Vector2::NEGATIVE_UNIT_Y;
			test.normalize();
			Assert::IsTrue(std::fabs(test.getLength() - eps) < 1.0f);

			test = Vector2(1.0f, 1.0f);
			test.normalize();
			Assert::IsTrue(std::fabs(test.getLength() - eps) < 1.0f);

			test.set(1.0f, 2.0f);
			test.normalize();
			Assert::IsTrue(std::fabs(test.getLength() - eps) < 1.0f);

			test.set(3.0f, 0.0f);
			test.normalize();
			Assert::IsTrue(std::fabs(test.getLength() - eps) < 1.0f);

			test.set(-3.0f, 0.5f);
			test.normalize();
			Assert::IsTrue(std::fabs(test.getLength() - eps) < 1.0f);
		}

		TEST_METHOD(testDotProduct)
		{
			Vector2 test1;
			Vector2 test2;

			test1 = Vector2::UNIT_X;
			test2 = Vector2::UNIT_Y;
			Assert::IsTrue(std::fabs(test1.dotProduct(test2)) - eps < 0.0f);

			test2 = Vector2::NEGATIVE_UNIT_Y;
			Assert::IsTrue(std::fabs(test1.dotProduct(test2)) - eps < 0.0f);

			test1 = Vector2::UNIT_X;
			test2 = Vector2::UNIT_X;
			Assert::IsTrue(std::fabs(test1.dotProduct(test2)) + eps > 1.0f);

			test1 = Vector2::UNIT_Y;
			test2 = Vector2::UNIT_Y;
			Assert::IsTrue(test1.dotProduct(test2) == (test1.x * test2.x + test1.y * test2.y));
		}

		TEST_METHOD(addVectorVector)
		{
			Vector2 vec1{ 1.0f, 2.0f };
			Vector2 vec2{ 3.0f, 4.0f };

			Vector2 vec3 = vec1 + vec2;
			Assert::AreEqual(4.0f, vec3.x);
			Assert::AreEqual(6.0f, vec3.y);

			vec1 += vec2;
			Assert::AreEqual(4.0f, vec1.x);
			Assert::AreEqual(6.0f, vec1.y);

			vec1 = { 1.0f, 2.0f };
			vec1.add(vec2);
			Assert::AreEqual(4.0f, vec1.x);
			Assert::AreEqual(6.0f, vec1.y);
		}

		TEST_METHOD(addVectorNumber)
		{
			Vector2 vec1{ 1.0f, 2.0f };

			vec1.add(1.5f);
			Assert::AreEqual(2.5f, vec1.x);
			Assert::AreEqual(3.5f, vec1.y);
		}

		TEST_METHOD(subtractVectorVector)
		{
			Vector2 vec1{ 1.0f, 2.0f };
			Vector2 vec2{ 3.0f, 5.0f };

			Vector2 vec3 = vec1 - vec2;
			Assert::AreEqual(-2.0f, vec3.x);
			Assert::AreEqual(-3.0f, vec3.y);

			vec1 -= vec2;
			Assert::AreEqual(-2.0f, vec1.x);
			Assert::AreEqual(-3.0f, vec1.y);

			vec1 = { 1.0f, 2.0f };
			vec1.subtract(vec2);
			Assert::AreEqual(-2.0f, vec1.x);
			Assert::AreEqual(-3.0f, vec1.y);
		}

		TEST_METHOD(subscriptOperator)
		{
			Vector2 vec1{ 1.0f, 2.0f };

			Assert::AreEqual(1.0f, vec1[0]);
			Assert::AreEqual(2.0f, vec1[1]);
		}
	};
}