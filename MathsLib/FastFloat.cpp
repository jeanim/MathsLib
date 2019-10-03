#include "FastFloat.h"
#include "Maths.h"


namespace MathsLib
{
	// There is quite a lot of static members in this class
	// so we need to initialize them.
	int FastFloat::s_nMask = 511;
	std::vector <float> FastFloat::s_pSinTable;
	float FastFloat::s_fModifier = 511.0f / (2.0f * Maths::PI);
	float FastFloat::s_fQuarter = 128.0f;
	const float FastFloat::FTOIBIAS = 12582912.0f;
	

	FastFloat::FastFloat(size_t _sinTableSize)
	{
		s_pSinTable.resize(_sinTableSize);
		s_nMask = _sinTableSize - 1;
		s_fModifier = static_cast<float>((_sinTableSize) / (2.0f * Maths::PI));
		s_fQuarter = static_cast<float>((_sinTableSize) * 0.25f);

		initLookupTable();
	}

	FastFloat::~FastFloat()
	{
	}

	void FastFloat::initLookupTable()
	{
		size_t tableSize = s_pSinTable.size();
		for(unsigned int i = 0; i < tableSize; ++i)
			s_pSinTable[i] = (float)sin((double)i * 2.0 * Maths::PI / double(tableSize));
	}

	unsigned int FastFloat::getSinTableSize()
	{
		return s_pSinTable.size();
	}
}
