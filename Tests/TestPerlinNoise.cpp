#include "pch.h"
#include "CppUnitTest.h"
#include "..//MathsLib/Maths.h"
#include "..//MathsLib/PerlinNoise.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace MathsLib;

namespace Tests
{
	TEST_CLASS(TestPerlinNoise)
	{
		TEST_METHOD(TestCreation)
		{
			PerlinNoise<1> perlin(32);

			Assert::AreEqual(32u, perlin.size());
		}
	};
}