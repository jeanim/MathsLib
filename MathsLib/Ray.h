#pragma once
#ifndef __INC_RAY_H_
#define __INC_RAY_H_


#include "Point.h"
#include "Vector3.h"


namespace MathsLib
{
	class AABB;
	class Point;
	class Matrix4x4;

	/** Ray mathematical object.
		@remarks
			Ray is a line having beginning specified and ending in
			infinity.
		@par
			In case all intersection tests assumption is made, that
			intersection occurs only if the ray points in an opposite
			direction as the normal of the surface.
	*/
	class Ray
	{
	private:
		Point m_ptOrigin;						///< Beginning of the ray
		Vector3 m_vecDirection;					///< Direction of the ray
		float m_fTMin;							///< Minimum t-value found during intersection test

		Point m_ptIntersectionPoint;			///< Point of last intersection

	public:
		Ray();
		explicit Ray(Point& _origin, Vector3& _direction);
		~Ray();

		/// Sets up ray.
		void set(Point& _origin, Vector3& _direction);

		/// Does ray intersect AABB?
		bool intersectAABB(AABB& _aabb);
		/// Does ray intersect plane?
		bool intersectPlane(const Plane& _plane);
		/// Does ray intersect triangle?
		bool intersectTriangle(const Vector3& _vec0,
							   const Vector3& _vec1,
							   const Vector3& _vec2);

		/// Moves ray to the given space.
		void moveToObjectSpace(const Matrix4x4& _mat);

		void setOrigin(const Point& _origin) { m_ptOrigin = _origin; }
		Point& getOrigin() { return m_ptOrigin; }

		void setDirection(const Vector3& _direction) { m_vecDirection = _direction; }
		Vector3& getDirection() { return m_vecDirection; }

		/** Returns intersection point.
			@returns
				Point& if intersection test has been carried then
				result is point of this intersection test or (0, 0, 0)
				otherwise.
		*/
		Point& getIntersectionPoint() { return m_ptIntersectionPoint; }

		/// Returns t-value.
		float getTValue() const { return m_fTMin; }
	};

}


#endif