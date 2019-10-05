#include "Maths.h"


namespace MathsLib
{
	// Some important mathematical constants and numbers
	// needs to be initialized here as they were declared static
	Maths::ANGLE_UNIT Maths::s_AngleUnit = Maths::ANGLE_RADIAN;

	const float Maths::PI = 3.14159265f;
	const float Maths::PI_DOUBLE = 6.28318853f;
	const float Maths::PI_HALF = 1.570796325f;

	const float Maths::Infinity = 1e9;
	const float Maths::MinusInfinity = -Maths::Infinity;
	const float Maths::FloatEpsilon = 0.000001f;

	bool Maths::m_bUseTables = true;
	bool Maths::m_bUseSSE = false;

	const float Maths::m_kDegToRad = PI_DOUBLE / 360.0f;
	const float Maths::m_kRadToDeg = 180.0f / PI;


	Maths::Maths()
	{
	}
	
	Maths::~Maths()
	{
	}

	float Maths::catmullRomInterpolation(const std::vector<float>& points, float t)
	{
		if(t < 0.0f || t > 1.0f || points.size() != 4)
			return 0.0f;

		float P0 = points[0];
		float P1 = points[1];
		float P2 = points[2];
		float P3 = points[3];

		float result = 0.5f * ((2.0f * P1) +
			(-P0 + P2) * t +
			(2.0f * P0 - 5.0f * P1 + 4.0f * P2 - P3) * t * t +
			(-P0 + 3.0f * P1 - 3.0f * P2 + P3) * t * t * t);

		return result;
	}
	
}