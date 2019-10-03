#include "pch.h"
#include "CppUnitTest.h"
#include "..//MathsLib/Maths.h"
#include "..//MathsLib/Vector4.h"

using std::string;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MathsLib;


namespace Tests
{
	TEST_CLASS(TestVector4)
	{
	public:
		static constexpr float eps = 0.0001f;

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
	};
}