#include "Ray.h"
#include "AABB.h"
#include "Plane.h"
#include "Vector4.h"
#include "Matrix4x4.h"


namespace MathsLib
{
	Ray::Ray(): m_fTMin(1e9)
	{
	}

	Ray::Ray(Point& _origin, Vector3& _direction):
		m_ptOrigin(_origin),
		m_vecDirection(_direction),
		m_fTMin(1e9)
	{
	}

	Ray::~Ray()
	{
	}

	bool Ray::intersectAABB(AABB& _aabb)
	{
		float t = 0.0f;
		float tmax = 1e9;

		Vector3& vecMin = _aabb.getMinimum();
		Vector3& vecMax = _aabb.getMaximum();

		for(unsigned int i = 0; i < 3; ++i)
		{
			if(!Maths::floatCompare(m_vecDirection[i], 0.0f))
			{
				if(m_ptOrigin[i] < vecMin[i] || m_ptOrigin[i] > vecMax[i])
					return false;
			}
			else
			{
				float inv = 1.0f / m_vecDirection[i];
				float t1 = (vecMin[i] - m_ptOrigin[i]) * inv;
				float t2 = (vecMax[i] - m_ptOrigin[i]) * inv;

				if(t1 > t2)
					Maths::swap(t1, t2);
				if(t1 > t)
					t = t1;
				if(t2 < tmax)
					tmax = t2;

				if(t > tmax)
					return false;
			}
		}

		m_ptIntersectionPoint = m_ptOrigin + m_vecDirection * t;

		if(t < m_fTMin)
			m_fTMin = t;

		return true;
	}

	bool Ray::intersectPlane(const Plane& _plane)
	{
		const Vector3& normal = _plane.getPlaneNormal();
		float dot = m_vecDirection.dotProduct(normal);
		if(dot >= 0.0f)
			return false;
		float t = (-_plane.getPlaneD() - normal.dotProduct(m_ptOrigin)) / dot;

		m_ptIntersectionPoint = m_ptOrigin + m_vecDirection * t;

		if(t < m_fTMin)
			m_fTMin = t;

		return true;
	}

	bool Ray::intersectTriangle(const Vector3& _vec0,
								const Vector3& _vec1,
								const Vector3& _vec2)
	{
		Vector3 vec1 = _vec1 - _vec0;
		Vector3 vec2 = _vec2 - _vec0;

		Vector3 normal = vec2 * vec1;
		float dot = normal.dotProduct(m_vecDirection);

		if(dot >= 0.0f)
			return false;

		float d = normal.dotProduct(_vec0);
		float t = d - normal.dotProduct(m_ptOrigin);

		if(t > 0.0f || t < dot)
			return false;

		t /= dot;
		Vector3 intersectPt = m_ptOrigin + m_vecDirection * t;

		float u0, u1, u2;
		float v0, v1, v2;
		if(Maths::abs(normal.x) > Maths::abs(normal.y))
		{
			if(Maths::abs(normal.x) > Maths::abs(normal.z))
			{
				u0 = intersectPt.y - _vec0.y;
				u1 = _vec1.y - _vec0.y;
				u2 = _vec2.y - _vec0.y;

				v0 = intersectPt.z - _vec0.z;
				v1 = _vec1.z - _vec0.z;
				v2 = _vec2.z - _vec0.z;
			}
			else
			{
				u0 = intersectPt.x - _vec0.x;
				u1 = _vec1.x - _vec0.x;
				u2 = _vec2.x - _vec0.x;

				v0 = intersectPt.y - _vec0.y;
				v1 = _vec1.y - _vec0.y;
				v2 = _vec2.y - _vec0.y;
			}
		}
		else
		{
			if(Maths::abs(normal.y) > Maths::abs(normal.z))
			{
				u0 = intersectPt.x - _vec0.x;
				u1 = _vec1.x - _vec0.x;
				u2 = _vec2.x - _vec0.x;

				v0 = intersectPt.z - _vec0.z;
				v1 = _vec1.z - _vec0.z;
				v2 = _vec2.z - _vec0.z;
			}
			else
			{
				u0 = intersectPt.x - _vec0.x;
				u1 = _vec1.x - _vec0.x;
				u2 = _vec2.x - _vec0.x;

				v0 = intersectPt.y - _vec0.y;
				v1 = _vec1.y - _vec0.y;
				v2 = _vec2.y - _vec0.y;
			}
		}

		float temp = u1 * v2 - v1 * u2;
		if(!Maths::floatCompare(temp, 0.0f))
			return false;

		temp = 1.0f / temp;

		float alpha = (u0 * v2 - v0 * u2) * temp;
		if(alpha < 0.0f)
			return false;

		float beta = (u1 * v0 - v1 * u0) * temp;
		if(beta < 0.0f)
			return false;

		float gamma = 1.0f - alpha - beta;
		if(gamma < 0.0f)
			return false;

		m_ptIntersectionPoint = m_ptOrigin + m_vecDirection * t;
		
		if(t < m_fTMin)
			m_fTMin = t;

		return true;
	}

	void Ray::moveToObjectSpace(const Matrix4x4& _mat)
	{
		Matrix4x4 m = _mat;

		m.invert();

		Vector4 temp;
		temp.set(m_ptOrigin.x, m_ptOrigin.y, m_ptOrigin.z, 1.0f);
		temp = temp * m;
		m_ptOrigin = Point(temp.x, temp.y, temp.z);

		temp.set(m_vecDirection.x, m_vecDirection.y, m_vecDirection.z, 0.0f);
		temp = temp * m;
		m_vecDirection = Vector3(temp.x, temp.y, temp.z);
	}

	void Ray::set(Point& _origin, Vector3& _direction)
	{
		m_ptOrigin = _origin;
		m_vecDirection = _direction;
	}
}