#include "pch.h"
#include "CppUnitTest.h"
#include "..//MathsLib/Maths.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MathsLib;

namespace Tests
{
	TEST_CLASS(TestMaths)
	{
	public:
		static constexpr float eps = 0.01f;

		TEST_METHOD(testSine)
		{
			Maths::setAngleUnit(Maths::ANGLE_RADIAN);

			Assert::IsTrue(fabs(Maths::fsin(0.0f)) < eps);
			Assert::IsTrue(Maths::fsin(Maths::PI / 2) == 1.0f);
			Assert::IsTrue(fabs(Maths::fsin(Maths::PI)) < eps);
			Assert::IsTrue(fabs(Maths::fsin(Maths::PI * 3 / 2) + 1.0f) < eps);
			Assert::IsTrue(fabs(Maths::fsin(Maths::PI * 2)) < eps);
			Assert::IsTrue(fabs(Maths::fsin(Maths::PI * 4)) < eps);
		}

		TEST_METHOD(testCosine)
		{
			Maths::setAngleUnit(Maths::ANGLE_RADIAN);

			Assert::IsTrue(fabs(Maths::fcos(0.0f) - 1.0f) < eps);
			Assert::IsTrue(fabs(Maths::fcos(Maths::PI / 2)) < eps);
			Assert::IsTrue(fabs(Maths::fcos(Maths::PI) + 1.0f) < eps);
			Assert::IsTrue(fabs(Maths::fcos(Maths::PI * 3 / 2)) < eps);
			Assert::IsTrue(fabs(Maths::fcos(Maths::PI * 2) - 1.0f) < eps);
			Assert::IsTrue(fabs(Maths::fcos(Maths::PI * 4) - 1.0f) < eps);
		}

		TEST_METHOD(testSqrt)
		{
			Assert::AreEqual(1.0f, Maths::fsqrt(1.0f));
			Assert::AreEqual(2.0f, Maths::fsqrt(4.0f));
			Assert::AreEqual(3.0f, Maths::fsqrt(9.0f));
		}

		TEST_METHOD(testClamp)
		{
			int nValue;
			float fValue;

			nValue = 10;
			Maths::clamp <int>(nValue, 5, 7);
			Assert::AreEqual(7, nValue);

			fValue = 10.0f;
			Maths::clamp <float>(fValue, 15.0f, 20.0f);
			Assert::AreEqual(15.0f, fValue);

			nValue = 10;
			Maths::clamp <int>(nValue, 7, 5);
			Assert::AreEqual(10, nValue);
		}

		TEST_METHOD(testClampRoll)
		{
			int nValue;
			float fValue;

			nValue = 10;
			Maths::clamp_roll <int>(nValue, 5, 7);
			Assert::AreEqual(5, nValue);

			fValue = 10.0f;
			Maths::clamp_roll <float>(fValue, 15.0f, 20.0f);
			Assert::AreEqual(20.0f, fValue);

			nValue = 10;
			Maths::clamp_roll <int>(nValue, 7, 5);
			Assert::AreEqual(10, nValue);
		}

		TEST_METHOD(testRoll)
		{
			int nValue;

			nValue = 10;
			Maths::roll <int>(nValue, 0, 8);
			Assert::AreEqual(1, nValue);

			nValue = 10;
			Maths::roll <int>(nValue, 1, 8);
			Assert::AreEqual(2, nValue);

			nValue = 10;
			Maths::roll <int>(nValue, -1, 8);
			Assert::AreEqual(0, nValue);

			nValue = 20;
			Maths::roll <int>(nValue, 0, 10);
			Assert::AreEqual(9, nValue);

			nValue = 30;
			Maths::roll <int>(nValue, 0, 10);
			Assert::AreEqual(8, nValue);

			nValue = -1;
			Maths::roll <int>(nValue, 0, 8);
			Assert::AreEqual(8, nValue);

			nValue = -10;
			Maths::roll <int>(nValue, 0, 8);
			Assert::AreEqual(8, nValue);

			nValue = -10;
			Maths::roll <int>(nValue, 1, 8);
			Assert::AreEqual(6, nValue);

			nValue = -10;
			Maths::roll <int>(nValue, -1, 8);
			Assert::AreEqual(0, nValue);
		}
		
		TEST_METHOD(testFloatToInt)
		{
			Assert::AreEqual(0, FastFloat::floatToInt(0.0f));
			Assert::AreEqual(0, FastFloat::floatToInt(0.5f));
			Assert::AreEqual(1, FastFloat::floatToInt(0.501f));
			Assert::AreEqual(1, FastFloat::floatToInt(0.999f));
			Assert::AreEqual(1, FastFloat::floatToInt(1.0f));
			Assert::AreEqual(1, FastFloat::floatToInt(1.001f));
			Assert::AreEqual(2, FastFloat::floatToInt(1.999f));
		}
		
		TEST_METHOD(testPerlinNoiseGen)
		{
			for (unsigned int i = 0; i < 1000; ++i)
			{
				float result = Maths::perlinNoiseGenerator(rand(), rand(), rand());
				Assert::IsTrue(result >= -1.0f);
				Assert::IsTrue(result <= 1.0f);
			}
		}

		TEST_METHOD(testLerp)
		{
			// Tests for float
			Assert::AreEqual(0.0f, Maths::lerp <float>(0.0f, 10.0f, 0.0f));
			Assert::AreEqual(10.0f, Maths::lerp <float>(0.0f, 10.0f, 1.0f));
			Assert::AreEqual(2.5f, Maths::lerp <float>(0.0f, 10.0f, 0.25f));
			Assert::AreEqual(-10.0f, Maths::lerp <float>(-10.0f, 10.0f, 0.0f));
			Assert::AreEqual(0.0f, Maths::lerp <float>(-10.0f, 10.0f, 0.5f));
			Assert::AreEqual(7.5f, Maths::lerp <float>(5.0f, 10.0f, 0.5f));

			// Tests for int
			Assert::AreEqual(0, Maths::lerp <int>(0, 10, 0.0f));
			Assert::AreEqual(10, Maths::lerp <int>(0, 10, 1.0f));
			Assert::AreEqual(2, Maths::lerp <int>(0, 10, 0.25f));
			Assert::AreEqual(2, Maths::lerp <int>(0, 10, 0.28f));
		}

		TEST_METHOD(testIsPowerOfTwo)
		{
			Assert::IsFalse(Maths::isPowerOfTwo(0));
			Assert::IsTrue(Maths::isPowerOfTwo(1));
			Assert::IsTrue(Maths::isPowerOfTwo(2));
			Assert::IsFalse(Maths::isPowerOfTwo(3));
			Assert::IsTrue(Maths::isPowerOfTwo(4));
			Assert::IsFalse(Maths::isPowerOfTwo(17));
			Assert::IsTrue(Maths::isPowerOfTwo(128));
		}

		TEST_METHOD(testNextPowerOfTwo)
		{
			Assert::AreEqual(1u, Maths::roundUpToPowerOfTwo(1));
			Assert::AreEqual(2u, Maths::roundUpToPowerOfTwo(2));
			Assert::AreEqual(4u, Maths::roundUpToPowerOfTwo(3));
			Assert::AreEqual(16u, Maths::roundUpToPowerOfTwo(10));
		}

		TEST_METHOD(testCatmullRomInterpolation_Invalid_T)
		{
			float result = Maths::catmullRomInterpolation({ 0, 1, 2, 3 }, -1.0f);
			Assert::AreEqual(0.0f, result);
		}
	};
}
