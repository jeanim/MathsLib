#include "pch.h"
#include "CppUnitTest.h"
#include "..//MathsLib/Maths.h"
#include "..//MathsLib/Vector3.h"

using std::string;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MathsLib;


namespace Tests
{
	TEST_CLASS(TestVector3)
	{
	public:
		static constexpr float eps = 0.0001f;


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
	};
}