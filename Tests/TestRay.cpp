#include "pch.h"
#include "CppUnitTest.h"
#include "..//MathsLib/Maths.h"
#include "..//MathsLib/Ray.h"
#include "..//MathsLib/Plane.h"
#include "..//MathsLib/Point.h"
#include "..//MathsLib/Vector3.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MathsLib;

namespace Tests
{
	TEST_CLASS(TestRay)
	{
	public:
		static constexpr float eps = 0.0001f;


		TEST_METHOD(testValidIntersectPlane)
		{
			Plane plane(Vector3::UNIT_Y, 0);
			Point origin(0, 10, 0);
			Vector3 direction(0, -1, 0);
			Ray ray;
			ray.set(origin, direction);
			Assert::IsTrue(ray.intersectPlane(plane));

			origin.set(10, 10, 0);
			Assert::IsTrue(ray.intersectPlane(plane));

			origin.set(0, 10, 0);
			direction.set(1, -1, 1);
			Assert::IsTrue(ray.intersectPlane(plane));

			origin.set(0, 0, 0);
			Assert::IsTrue(ray.intersectPlane(plane));
		}

		TEST_METHOD(testInvalidIntersectPlane)
		{
			Plane plane(Vector3::UNIT_Y, 0);
			Point origin(0, -10, 0);
			Vector3 direction(0, 1, 0);
			Ray ray;
			ray.set(origin, direction);
			Assert::IsFalse(ray.intersectPlane(plane));

			origin.set(0, 10, 0);
			direction.set(0, 1, 0);
			Assert::IsFalse(ray.intersectPlane(plane));

			origin.set(1, 0, 0);
			direction.set(0, 1, 0);
			Assert::IsFalse(ray.intersectPlane(plane));
		}
	};
}