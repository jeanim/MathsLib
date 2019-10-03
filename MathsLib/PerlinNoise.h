#pragma once
#ifndef __INC_PERLINNOISE_H_
#define __INC_PERLINNOISE_H_


namespace MathsLib
{
	/** This class defines n-dimensional Perlin noise.
		@remarks
			To achieve "multi-dimensolity" of the noise template
			recusion is used extensively.
	*/
	template <unsigned int N=1>
	class PerlinNoise
	{
	protected:
		PerlinNoise <N-1>* m_pElements;
		unsigned int m_nSize;

		void copyFrom(const PerlinNoise <N>& src);

	public:
		PerlinNoise(unsigned int _size=32);
		PerlinNoise(const PerlinNoise <N>& src);
		~PerlinNoise();

		PerlinNoise <N>& operator=(const PerlinNoise <N>& rhs);

		/// Setups perlin noise.
		void setup();
		double smooth(vector <unsigned int>& _indices);
		float& get(vector <unsigned int>& _indices);

		void resize(unsigned int _size);
		unsigned int getSize() const;

		PerlinNoise <N-1>& operator[](int _index);
		const PerlinNoise <N-1>& operator[](int _index) const;
	};

	template <>
	class PerlinNoise <1>
	{
	protected:
		float* m_pElements;
		unsigned int m_nSize;

		void copyFrom(const PerlinNoise <1>& src);

	public:
		PerlinNoise(unsigned int _size=32);
		PerlinNoise(const PerlinNoise <1>& src);
		~PerlinNoise();

		PerlinNoise <1>& operator=(const PerlinNoise <1>& rhs);

		void setup();
		double smooth(vector <unsigned int>& _indices);

		void resize(unsigned int _size);
		unsigned int getSize() const;

		float& get(vector <unsigned int>& _indices);

		float& operator[](int _index);
		const float& operator[](int _index) const;
	};



	template <unsigned int N>
	PerlinNoise <N>::PerlinNoise(unsigned int _size):
		m_nSize(_size)
	{
		m_pElements = new PerlinNoise <N-1>[m_nSize];
		for(unsigned int i = 0; i < m_nSize; ++i)
			m_pElements[i].resize(_size);
	}

	template <unsigned int N>
	PerlinNoise <N>::PerlinNoise(const PerlinNoise <N>& src)
	{
		copyFrom(src);
	}

	template <unsigned int N>
	PerlinNoise <N>::~PerlinNoise()
	{
		NGENE_DELETE_ARRAY(m_pElements);
	}

	template <unsigned int N>
	PerlinNoise <N>& PerlinNoise <N>::operator=(const PerlinNoise <N>& rhs)
	{
		if(this == &rhs)
			return (*this);

		delete[] m_pElements;
		copyFrom(rhs);

		return (*this);
	}

	template <unsigned int N>
	void PerlinNoise <N>::copyFrom(const PerlinNoise <N>& src)
	{
		m_nSize = src.m_nSize;
		m_pElements = new PerlinNoise <N-1>[m_nSize];
		for(unsigned int i = 0; i < m_nSize; ++i)
			m_pElements[i] = src.m_pElements[i];
	}

	template <unsigned int N>
	void PerlinNoise <N>::resize(unsigned int _size)
	{
		PerlinNoise <N-1>* newElements = new PerlinNoise <N-1>[_size];
		for(unsigned int i = 0; i < _size && i < m_nSize; ++i)
		{
			newElements[i] = m_pElements[i];
			newElements[i].resize(_size);
		}

		m_nSize = _size;
		delete[] m_pElements;
		m_pElements = newElements;
	}

	template <unsigned int N>
	unsigned int PerlinNoise <N>::getSize() const
	{
		return m_nSize;
	}

	template <unsigned int N>
	void PerlinNoise <N>::setup()
	{
		for(unsigned int i = 0; i < m_nSize; ++i)
			m_pElements[i].setup();
	}

	template <unsigned int N>
	double PerlinNoise <N>::smooth(vector <unsigned int>& _indices)
	{
		unsigned int index = _indices.front();
		_indices.erase(_indices.begin());

		vector <unsigned int> inds1 = _indices;
		vector <unsigned int> inds2 = _indices;
		vector <unsigned int> inds3 = _indices;

		double result = (m_pElements[index + 0].smooth(inds1) +
						 m_pElements[index + 1].smooth(inds2) +
						 m_pElements[index - 1].smooth(inds3)) / 3.0f;

		return result;
	}

	template <unsigned int N>
	float& PerlinNoise <N>::get(vector <unsigned int>& _indices)
	{
		unsigned int index = _indices.front();
		_indices.erase(_indices.begin());

		float& result = m_pElements[index].get(_indices);

		return result;
	}

	template <unsigned int N>
	PerlinNoise <N-1>& PerlinNoise <N>::operator[](int _index)
	{
		return m_pElements[_index];
	}

	template <unsigned int N>
	const PerlinNoise <N-1>& PerlinNoise <N>::operator[](int _index) const
	{
		return m_pElements[_index];
	}



	inline PerlinNoise <1>::PerlinNoise(unsigned int _size):
		m_nSize(_size)
	{
		m_pElements = new float[m_nSize];
	}

	inline PerlinNoise <1>::PerlinNoise(const PerlinNoise <1>& src)
	{
		copyFrom(src);
	}

	inline PerlinNoise <1>::~PerlinNoise()
	{
		NGENE_DELETE_ARRAY(m_pElements);
	}

	inline PerlinNoise <1>& PerlinNoise <1>::operator=(const PerlinNoise <1>& rhs)
	{
		if(this == &rhs)
			return (*this);

		delete[] m_pElements;
		copyFrom(rhs);

		return (*this);
	}

	inline void PerlinNoise <1>::copyFrom(const PerlinNoise <1>& src)
	{
		m_nSize = src.m_nSize;
		m_pElements = new float[m_nSize];
		for(unsigned int i = 0; i < m_nSize; ++i)
			m_pElements[i] = src.m_pElements[i];
	}

	inline void PerlinNoise <1>::resize(unsigned int _size)
	{
		float* newElements = new float[_size];
		for(unsigned int i = 0; i < _size && i < m_nSize; ++i)
			newElements[i] = m_pElements[i];
		
		m_nSize = _size;
		delete m_pElements;
		m_pElements = newElements;
	}

	inline unsigned int PerlinNoise <1>::getSize() const
	{
		return m_nSize;
	}

	inline void PerlinNoise <1>::setup()
	{
		for(unsigned int i = 0; i < m_nSize; ++i)
		{
			m_pElements[i] = Maths::perlinNoiseGenerator(i, 0, rand());
		}
	}

	inline double PerlinNoise <1>::smooth(vector <unsigned int>& _indices)
	{
		unsigned int index = _indices[0];
		_indices.erase(_indices.begin());

		double result = 0.0f;
		result = (m_pElements[index + 0] +
				  m_pElements[index + 1] +
				  m_pElements[index - 1]) / 3.0f;

		return result;
	}

	inline float& PerlinNoise <1>::get(vector <unsigned int>& _indices)
	{
		unsigned int index = _indices.front();
		_indices.erase(_indices.begin());

		float& result = m_pElements[index];

		return result;
	}

	inline float& PerlinNoise <1>::operator[](int _index)
	{
		return m_pElements[_index];
	}

	inline const float& PerlinNoise <1>::operator[](int _index) const
	{
		return m_pElements[_index];
	}

}


#endif