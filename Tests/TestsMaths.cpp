#include "pch.h"
#include "CppUnitTest.h"
#include "../MathsLib/Maths.h"
#include "../MathsLib/Vector2.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MathsLib;

namespace Tests
{
	TEST_CLASS(TestMaths)
	{
	public:
		static constexpr float eps = 0.00001f;

		TEST_METHOD(testSine)
		{
			float sineEps = 0.01f;
			Maths::setAngleUnit(Maths::AngleUnits::Radian);

			Assert::IsTrue(fabs(Maths::fsin(0.0f)) < sineEps);
			Assert::IsTrue(Maths::fsin(Maths::PI / 2) == 1.0f);
			Assert::IsTrue(fabs(Maths::fsin(Maths::PI)) < sineEps);
			Assert::IsTrue(fabs(Maths::fsin(Maths::PI * 3 / 2) + 1.0f) < sineEps);
			Assert::IsTrue(fabs(Maths::fsin(Maths::PI * 2)) < sineEps);
			Assert::IsTrue(fabs(Maths::fsin(Maths::PI * 4)) < sineEps);
		}

		TEST_METHOD(testCosine)
		{
			float sineEps = 0.01f;
			Maths::setAngleUnit(Maths::AngleUnits::Radian);

			Assert::IsTrue(fabs(Maths::fcos(0.0f) - 1.0f) < sineEps);
			Assert::IsTrue(fabs(Maths::fcos(Maths::PI / 2)) < sineEps);
			Assert::IsTrue(fabs(Maths::fcos(Maths::PI) + 1.0f) < sineEps);
			Assert::IsTrue(fabs(Maths::fcos(Maths::PI * 3 / 2)) < sineEps);
			Assert::IsTrue(fabs(Maths::fcos(Maths::PI * 2) - 1.0f) < sineEps);
			Assert::IsTrue(fabs(Maths::fcos(Maths::PI * 4) - 1.0f) < sineEps);
		}

		TEST_METHOD(testSqrt_Smaller_Than_1)
		{
			Assert::AreEqual(0.5f, Maths::fsqrt(0.25f));
		}

		TEST_METHOD(testSqrt_Greater_Than_1)
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

		TEST_METHOD(testLerp_IncorrectT)
		{
			Assert::AreEqual(0.0f, Maths::lerp<float>(0.0f, 1.0f, -1.0f));
			Assert::AreEqual(1.0f, Maths::lerp<float>(0.0f, 1.0f, 2.0f));
		}

		TEST_METHOD(testLerp_Correct_Float)
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

		TEST_METHOD(testLerp_Correct_Vector2)
		{
			Vector2 p1{ 1, 2 };
			Vector2 p2{ 3, 4 };

			Vector2 result = Maths::lerp<Vector2>(p1, p2, 0.0f);
			Assert::AreEqual(1.0f, result.x);
			Assert::AreEqual(2.0f, result.y);

			result = Maths::lerp<Vector2>(p1, p2, 0.5f);
			Assert::AreEqual(2.0f, result.x);
			Assert::AreEqual(3.0f, result.y);

			result = Maths::lerp<Vector2>(p1, p2, 1.0f);
			Assert::AreEqual(3.0f, result.x);
			Assert::AreEqual(4.0f, result.y);
		}

		TEST_METHOD(testIsPowerOfTwo_Expected_False)
		{
			Assert::IsFalse(Maths::isPowerOfTwo(0));
			Assert::IsFalse(Maths::isPowerOfTwo(3));
			Assert::IsFalse(Maths::isPowerOfTwo(5));
			Assert::IsFalse(Maths::isPowerOfTwo(17));
		}

		TEST_METHOD(testIsPowerOfTwo_Expected_True)
		{
			Assert::IsTrue(Maths::isPowerOfTwo(1));
			Assert::IsTrue(Maths::isPowerOfTwo(2));
			Assert::IsTrue(Maths::isPowerOfTwo(4));
			Assert::IsTrue(Maths::isPowerOfTwo(128));
		}

		TEST_METHOD(testNextPowerOfTwo)
		{
			Assert::AreEqual(1u, Maths::roundUpToPowerOfTwo(1));
			Assert::AreEqual(2u, Maths::roundUpToPowerOfTwo(2));
			Assert::AreEqual(4u, Maths::roundUpToPowerOfTwo(3));
			Assert::AreEqual(4u, Maths::roundUpToPowerOfTwo(4));
			Assert::AreEqual(8u, Maths::roundUpToPowerOfTwo(5));
			Assert::AreEqual(16u, Maths::roundUpToPowerOfTwo(10));
			Assert::AreEqual(16u, Maths::roundUpToPowerOfTwo(16));
		}

		TEST_METHOD(testCatmullRomInterpolation_InvalidT)
		{
			float result = Maths::catmullRomInterpolation<float>({ 0, 1, 2, 3 }, -1.0f);
			Assert::AreEqual(0.0f, result);

			result = Maths::catmullRomInterpolation<float>({ 0, 1, 2, 3 }, 1.5f);
			Assert::AreEqual(0.0f, result);
		}

		TEST_METHOD(testCatmullRomInterpolation_InvalidNumberOfPoints)
		{
			float result = Maths::catmullRomInterpolation<float>({ }, 0.5f);
			Assert::AreEqual(0.0f, result);

			result = Maths::catmullRomInterpolation<float>({ 0, 1, 2 }, 0.5f);
			Assert::AreEqual(0.0f, result);

			result = Maths::catmullRomInterpolation<float>({ 0, 1, 2, 3, 4 }, 0.5f);
			Assert::AreEqual(0.0f, result);
		}

		TEST_METHOD(testCatmullRomInterpolation_Correct_Float)
		{
			float result = Maths::catmullRomInterpolation<float>({ 0, 1, 2, 3 }, 0.0f);
			Assert::AreEqual(1.0f, result);

			result = Maths::catmullRomInterpolation<float>({ 0, 1, 2, 3 }, 0.25f);
			Assert::AreEqual(1.25f, result);

			result = Maths::catmullRomInterpolation<float>({0, 1, 2, 3 }, 0.5f);
			Assert::AreEqual(1.5f, result);

			result = Maths::catmullRomInterpolation<float>({ 0, 1, 2, 3 }, 0.75f);
			Assert::AreEqual(1.75f, result);

			result = Maths::catmullRomInterpolation<float>({ 0, 1, 2, 3 }, 1.0f);
			Assert::AreEqual(2.0f, result);
		}

		TEST_METHOD(testCatmullRomInterpolation_Correct_Vector2)
		{
			Vector2 p1{ 0, 1 };
			Vector2 p2{ 1, 2 };
			Vector2 p3{ 2, 2 };
			Vector2 p4{ 3, 1 };

			Vector2 result = Maths::catmullRomInterpolation<Vector2>({ p1, p2, p3, p4 }, 0.0f);
			Assert::AreEqual(1.0f, result.x);
			Assert::AreEqual(2.0f, result.y);

			result = Maths::catmullRomInterpolation<Vector2>({ p1, p2, p3, p4 }, 0.25f);
			Assert::AreEqual(1.25f, result.x);
			Assert::IsTrue(fabs(result.y - 2.09375f) < eps);

			result = Maths::catmullRomInterpolation<Vector2>({ p1, p2, p3, p4 }, 0.5f);
			Assert::AreEqual(1.5f, result.x);
			Assert::IsTrue(fabs(result.y - 2.125f) < eps);

			result = Maths::catmullRomInterpolation<Vector2>({ p1, p2, p3, p4 }, 0.75f);
			Assert::AreEqual(1.75f, result.x);
			Assert::IsTrue(fabs(result.y - 2.09375f) < eps);

			result = Maths::catmullRomInterpolation<Vector2>({ p1, p2, p3, p4 }, 1.0f);
			Assert::AreEqual(2.0f, result.x);
			Assert::AreEqual(2.0f, result.y);
		}

		TEST_METHOD(testCatmullRomInterpolation_Correct_Vector2_Different_Curve)
		{
			Vector2 p1{ 0, 1 };
			Vector2 p2{ 1, 2 };
			Vector2 p3{ 3, 3 };
			Vector2 p4{ 6, 8 };

			Vector2 result = Maths::catmullRomInterpolation<Vector2>({ p1, p2, p3, p4 }, 0.0f);
			Assert::AreEqual(1.0f, result.x);
			Assert::AreEqual(2.0f, result.y);

			result = Maths::catmullRomInterpolation<Vector2>({ p1, p2, p3, p4 }, 0.15f);
			Assert::IsTrue(fabs(result.x - 1.23625f) < eps);
			Assert::IsTrue(fabs(result.y - 2.11175f) < eps);

			result = Maths::catmullRomInterpolation<Vector2>({ p1, p2, p3, p4 }, 0.25f);
			Assert::IsTrue(fabs(result.x - 1.40625f) < eps);
			Assert::IsTrue(fabs(result.y - 2.15625f) < eps);

			result = Maths::catmullRomInterpolation<Vector2>({ p1, p2, p3, p4 }, 0.5f);
			Assert::IsTrue(fabs(result.x - 1.875f) < eps);
			Assert::IsTrue(fabs(result.y - 2.25f) < eps);

			result = Maths::catmullRomInterpolation<Vector2>({ p1, p2, p3, p4 }, 0.75f);
			Assert::IsTrue(fabs(result.x - 2.40625f) < eps);
			Assert::IsTrue(fabs(result.y - 2.46875f) < eps);

			result = Maths::catmullRomInterpolation<Vector2>({ p1, p2, p3, p4 }, 1.0f);
			Assert::AreEqual(3.0f, result.x);
			Assert::AreEqual(3.0f, result.y);
		}
	};
}
