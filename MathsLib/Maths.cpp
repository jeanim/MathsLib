// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "Maths.h"


namespace MathsLib
{
	// Some important mathematical constants and numbers
	// needs to be initialized here as they were declared static
	Maths::AngleUnits Maths::s_AngleUnit = Maths::AngleUnits::Radian;

	bool Maths::m_bUseTables = true;
	bool Maths::m_bUseSSE = false;

}