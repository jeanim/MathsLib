#include "FastFloat.h"
#include "Maths.h"


namespace MathsLib
{
	// There is quite a lot of static members in this class
	// so we need to initialize them.
	unsigned int FastFloat::s_knSinTableSize = 512;
	int FastFloat::s_nMask = 511;
	float* FastFloat::s_pSinTable = NULL;
	float FastFloat::s_fModifier = 511.0f / (2.0f * Maths::PI);
	float FastFloat::s_fQuarter = 128.0f;
	const float FastFloat::FTOIBIAS = 12582912.0f;
	

	FastFloat::FastFloat(unsigned int _sinTableSize)
	{
		s_knSinTableSize = _sinTableSize;
		s_nMask = s_knSinTableSize - 1;
		s_fModifier = static_cast<float>((s_knSinTableSize) / (2.0f * Maths::PI));
		s_fQuarter = static_cast<float>((s_knSinTableSize) * 0.25f);

		initSinTable();
	}

	FastFloat::~FastFloat()
	{
		cleanup();
	}

	void FastFloat::initSinTable()
	{
		s_pSinTable = new float[s_knSinTableSize];
		for(unsigned int i = 0; i < s_knSinTableSize; ++i)
			s_pSinTable[i] = (float)sin((double)i * 2.0 * Maths::PI / double(s_knSinTableSize));
	}

	unsigned int FastFloat::getSinTableSize()
	{
		return s_knSinTableSize;
	}

	void FastFloat::cleanup()
	{
		delete[] s_pSinTable;
	}

}
