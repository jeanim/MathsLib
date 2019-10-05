#include "FastFloat.h"
#include "Maths.h"


namespace MathsLib
{
	// There is quite a lot of static members in this class
	// so we need to initialize them.
	int FastFloat::s_nMask = sineTableSize - 1;
	std::vector <float> FastFloat::s_pSinTable;
	float FastFloat::s_fModifier = (float)(sineTableSize - 1) / (2.0f * Maths::PI);
	float FastFloat::s_fQuarter = (float)(sineTableSize) * 0.25f;
	const float FastFloat::FTOIBIAS = 12582912.0f;

	void FastFloat::initLookupTable()
	{
		s_pSinTable.resize(sineTableSize);
		for(unsigned int i = 0; i < sineTableSize; ++i)
			s_pSinTable[i] = (float)sin((double)i * 2.0 * Maths::PI / double(sineTableSize));
	}

	unsigned int FastFloat::getSinTableSize()
	{
		if (s_pSinTable.empty()) initLookupTable();

		return s_pSinTable.size();
	}
}
