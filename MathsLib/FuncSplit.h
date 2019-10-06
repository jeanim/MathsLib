#pragma once
#ifndef __INC_FUNCSPLIT_H_
#define __INC_FUNCSPLIT_H_

#include <vector>


namespace MathsLib
{
	/** It is a functor object letting you split the strings/wstrings/anything
		similar to them into set of strings based on the delimiter.
	*/
	template <typename T>
	class FuncSplit
	{
	public:
		FuncSplit() {}
		virtual ~FuncSplit() {}

		void operator()(const T& t, std::vector <T>& vec, const T& delim, size_t limit=0);
	};



//----------------------------------------------------------------------
	template <typename T>
	void FuncSplit<typename T>::operator()(const T& t, std::vector <T>& vec, const T& delim, size_t limit)
	{
		// Skip delimiters at beginning.
		size_t lastPos = t.find_first_not_of(delim);
		// Find first "non-delimiter".
		size_t pos     = t.find_first_of(delim, lastPos);

		unsigned int count = 1;
		while(T::npos != pos || T::npos != lastPos)
		{
			vec.push_back(t.substr(lastPos, pos - lastPos));
			lastPos = t.find_first_not_of(delim, pos);
			pos = t.find_first_of(delim, lastPos);
			if(limit)
			{
				if(limit == count++)
					return;
			}
		}
	}
}


#endif