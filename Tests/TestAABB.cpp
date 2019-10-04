#include "pch.h"
#include "CppUnitTest.h"
#include "../MathsLib/Maths.h"
#include "../MathsLib/AABB.h"
#include "../MathsLib/Vector3.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MathsLib;

namespace Tests
{
	TEST_CLASS(TestAABB)
	{
		TEST_METHOD(TestCreation)
		{
			Vector3 minimum{ -1, -1, -1 };
			Vector3 maximum{ 1, 1, 1 };
			AABB aabb{ minimum, maximum };

			Vector3 val = aabb.getMinimum();
			Assert::AreEqual(-1.0f, val.x);
			Assert::AreEqual(-1.0f, val.y);
			Assert::AreEqual(-1.0f, val.z);

			val = aabb.getMaximum();
			Assert::AreEqual(1.0f, val.x);
			Assert::AreEqual(1.0f, val.y);
			Assert::AreEqual(1.0f, val.z);

			val = aabb.getCentre();
			Assert::AreEqual(0.0f, val.x);
			Assert::AreEqual(0.0f, val.y);
			Assert::AreEqual(0.0f, val.z);
		}

		TEST_METHOD(TestFits_Smaller_Inside_Larger_Expected_True)
		{
			AABB aabb1{ Vector3{ -1, -1, -1 }, Vector3{ 1, 1, 1 } };
			AABB aabb2{ Vector3{-0.5f, -0.5f, -0.5f}, Vector3{0.5f, 0.5f, 0.5f} };

			Assert::IsTrue(aabb1.fits(aabb2));
		}

		TEST_METHOD(TestFits_Larger_Inside_Smaller_Expected_False)
		{
			AABB aabb1{ Vector3{ -1, -1, -1 }, Vector3{ 1, 1, 1 } };
			AABB aabb2{ Vector3{-0.5f, -0.5f, -0.5f}, Vector3{0.5f, 0.5f, 0.5f} };

			Assert::IsFalse(aabb2.fits(aabb1));
		}

		TEST_METHOD(TestFits_Same_Size_Expected_False)
		{
			AABB aabb1{ Vector3{ -1, -1, -1 }, Vector3{ 1, 1, 1 } };
			AABB aabb2{ Vector3{ -1, -1, -1 }, Vector3{ 1, 1, 1 } };

			Assert::IsFalse(aabb1.fits(aabb2));
			Assert::IsFalse(aabb2.fits(aabb1));
		}
	};
}