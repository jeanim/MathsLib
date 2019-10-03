#include "AABB.h"
#include "Point.h"


namespace MathsLib
{
	AABB::AABB()
	{
	}

	AABB::AABB(const Vector3& _min, const Vector3& _max):
		m_vecMinimum(_min),
		m_vecMaximum(_max)
	{
		computeCentre();
	}

	AABB::~AABB()
	{
	}

	void AABB::computeCentre()
	{
		m_vecCentre = 0.5f * (m_vecMinimum + m_vecMaximum);
	}

	void AABB::setAABB(const Vector3& _min, const Vector3& _max)
	{
		m_vecMinimum = _min;
		m_vecMaximum = _max;
		computeCentre();
	}

	void AABB::setMinimum(const Vector3& _min)
	{
		m_vecMinimum = _min;
		computeCentre();
	}

	void AABB::setMaximum(const Vector3& _max)
	{
		m_vecMaximum = _max;
		computeCentre();
	}

	bool AABB::fits(AABB& _aabb)
	{
		Vector3& min = _aabb.getMinimum();
		Vector3& max = _aabb.getMaximum();

		if(m_vecMinimum.x < min.x && m_vecMinimum.y < min.y && m_vecMinimum.z < min.z &&
		   m_vecMaximum.x > max.x && m_vecMaximum.y > max.y && m_vecMaximum.z > max.z)
		{
			return true;
		}

		return false;
	}

	float AABB::distanceToVector(const Vector3& _vec)
	{
		float dist = 0.0f;

		for(unsigned int i = 0; i < 3; ++i)
		{
			float v = _vec[i];
			float min = m_vecMinimum[i];
			float max = m_vecMaximum[i];

			if(v < min)
				dist += (min - v) * (min - v);
			if(v > max)
				dist += (max - v) * (max - v);
		}

		return Maths::fsqrt(dist);
	}

	float AABB::distanceToPoint(const Point& _pt)
	{
		float dist = 0.0f;

		for(unsigned int i = 0; i < 3; ++i)
		{
			float p = _pt[i];
			float min = m_vecMinimum[i];
			float max = m_vecMaximum[i];

			if(p < min)
				dist += (min - p) * (min - p);
			if(p > max)
				dist += (max - p) * (max - p);
		}

		return Maths::fsqrt(dist);
	}

	AABB& AABB::operator+=(const AABB& rhs)
	{
		m_vecMinimum.x = (m_vecMinimum.x <= rhs.m_vecMinimum.x ? m_vecMinimum.x : rhs.m_vecMinimum.x);
		m_vecMinimum.y = (m_vecMinimum.y <= rhs.m_vecMinimum.y ? m_vecMinimum.y : rhs.m_vecMinimum.y);
		m_vecMinimum.z = (m_vecMinimum.z <= rhs.m_vecMinimum.z ? m_vecMinimum.z : rhs.m_vecMinimum.z);

		m_vecMaximum.x = (m_vecMaximum.x >= rhs.m_vecMaximum.x ? m_vecMaximum.x : rhs.m_vecMaximum.x);
		m_vecMaximum.y = (m_vecMaximum.y >= rhs.m_vecMaximum.y ? m_vecMaximum.y : rhs.m_vecMaximum.y);
		m_vecMaximum.z = (m_vecMaximum.z >= rhs.m_vecMaximum.z ? m_vecMaximum.z : rhs.m_vecMaximum.z);

		computeCentre();

		return (*this);
	}

	const AABB operator+(const AABB& lhs, const AABB& rhs)
	{
		AABB result;

		result.m_vecMinimum.x = (lhs.m_vecMinimum.x <= rhs.m_vecMinimum.x ? lhs.m_vecMinimum.x : rhs.m_vecMinimum.x);
		result.m_vecMinimum.y = (lhs.m_vecMinimum.y <= rhs.m_vecMinimum.y ? lhs.m_vecMinimum.y : rhs.m_vecMinimum.y);
		result.m_vecMinimum.z = (lhs.m_vecMinimum.z <= rhs.m_vecMinimum.z ? lhs.m_vecMinimum.z : rhs.m_vecMinimum.z);

		result.m_vecMaximum.x = (lhs.m_vecMaximum.x >= rhs.m_vecMaximum.x ? lhs.m_vecMaximum.x : rhs.m_vecMaximum.x);
		result.m_vecMaximum.y = (lhs.m_vecMaximum.y >= rhs.m_vecMaximum.y ? lhs.m_vecMaximum.y : rhs.m_vecMaximum.y);
		result.m_vecMaximum.z = (lhs.m_vecMaximum.z >= rhs.m_vecMaximum.z ? lhs.m_vecMaximum.z : rhs.m_vecMaximum.z);

		result.computeCentre();

		return result;
	}

}