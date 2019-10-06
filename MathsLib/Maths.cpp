#include "Maths.h"


namespace MathsLib
{
	// Some important mathematical constants and numbers
	// needs to be initialized here as they were declared static
	Maths::ANGLE_UNIT Maths::s_AngleUnit = Maths::ANGLE_RADIAN;

	bool Maths::m_bUseTables = true;
	bool Maths::m_bUseSSE = false;

}