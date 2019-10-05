#include "BrownianTree.h"


namespace MathsLib
{
	bool* BrownianTree::operator()(const std::vector <BrownianTreeSeed>& _seeds, size_t _width, size_t _height,
		size_t _iterations)
	{
		// If no seeds are defined, return NULL
		if(!_seeds.size())
			return nullptr;

		int i, j, x, y, xNew, yNew;
		bool found;

		size_t arrSize = _width * _height;
		bool* pData = new bool[arrSize];
		memset(pData, false, sizeof(bool) * arrSize);

		// Put starting seeds
		for(size_t k = 0; k < _seeds.size(); ++k)
			pData[_seeds[k].second * _width + _seeds[k].first] = true;

		for(size_t n = 0; n < _iterations; ++n)
		{
			// Put new walker
			x = rand() % (_width - 2) + 1;
			y = rand() % (_height - 2) + 1;

			// Repeat until we find another seed
			while(true)
			{
				// Move in a random direction
				xNew = x + (rand() % 3) - 1;
				if(xNew > 0 && xNew < static_cast<int>(_width) - 1)
					x = xNew;
				yNew = y + (rand() % 3) - 1;
				if(yNew > 0 && yNew < static_cast<int>(_height) - 1)
					y = yNew;

				// Have we struck an existing point?
				found = false;
				for(i = -1; i <= 1; ++i)
				{
					for(j = -1; j <= 1; ++j)
					{
						if(pData[(y + j) * _width + (x + i)] == true)
						{
							found = true;
							break;
						}
					}
					
					if(found)
						break;
				}

				if(found)
					break;
			}
			
			if(y * _width + x < arrSize)
				pData[y * _width + x] = true;
		}

		return pData;
	}

}