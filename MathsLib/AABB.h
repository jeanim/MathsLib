#pragma once
#ifndef __INC_AABB_H_
#define __INC_AABB_H_


#include "Vector3.h"


namespace MathsLib
{
	class Point;

	/** AABB stands for axis-aligned bounding box, meaning
		each AABB's face is parallel to one of coordinate system
		axes.
		@par
			AABBs are especially useful when checking for
			collisions or testing objects visibility against
			viewing frustum.
		@par
			Thanks to axis-alignment only three points are
			necessary to describe AABB in the 3D space: its
			two corners and the centre.
		@par
			You can also add two AABBs to each other. All the coordinates
			will be maximum of both factors.
	*/
	class AABB
	{
	private:
		Vector3 m_vecMinimum;							///< Minimum corner of the AABB
		Vector3 m_vecMaximum;							///< Maximum corner of the AABB
		Vector3 m_vecCentre;							///< Centre point of the AABB


		void computeCentre();

	public:
		AABB();
		AABB(const Vector3& _min, const Vector3& _max);
		virtual ~AABB();

		/// Returns minimum vector.
		Vector3& getMinimum() {return m_vecMinimum;}
		/// Returns maximum vector.
		Vector3& getMaximum() {return m_vecMaximum;}
		/// Returns AABB centre point.
		Vector3& getCentre() {return m_vecCentre;}

		/// Checks whether another AABB lies completely inside this one.
		bool fits(AABB& _aabb);

		/// Sets AABB minimum and maximum vectors.
		void setAABB(const Vector3& _min, const Vector3& _max);
		/// Sets AABB minimum vector.
		void setMinimum(const Vector3& _min);
		/// Sets AABB maximum vector.
		void setMaximum(const Vector3& _max);


		/// Returns distance from this AABB to a given vector.
		float distanceToVector(const Vector3& _vec);
		/// Returns distance from this AABB to a given point.
		float distanceToPoint(const Point& _pt);


		AABB& operator+=(const AABB& rhs);

		friend const AABB operator+(const AABB& lhs, const AABB& rhs);
	};
}


#endif