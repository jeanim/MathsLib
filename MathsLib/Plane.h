#pragma once
#ifndef __INC_PLANE_H_
#define __INC_PLANE_H_


#include "Point.h"

#include <string>


namespace MathsLib
{
	class Matrix4x4;
	class Vector3;

	/** A plane is mathematical set of points in 3-dimensional
		euclidean space. Points satisfy the equation:
		A*x + B*y + C*z + D = 0.
		@par
			The plane is described by the normal vector (perpendicular
			to the plane) and the point belonging to this plane.
	*/
	class Plane
	{
	protected:
		Vector3 m_vecNormal;				///< Plane's normal vector
		float D;							///< D = - A*x0 - B*y0 - C*z0
		Point m_ptPoint;					///< Point lying on the plane


		void calculatePoint(const Vector3& _normal, float _d);

	public:
		/// Some static constants
		static const Plane UNIT_X;
		static const Plane UNIT_Y;
		static const Plane UNIT_Z;
		static const Plane NEGATIVE_UNIT_X;
		static const Plane NEGATIVE_UNIT_Y;
		static const Plane NEGATIVE_UNIT_Z;
	
	public:
		Plane();
		explicit Plane(float _a, float _b, float _c, float _d);
		explicit Plane(const Vector3& _normal, float _d);
		explicit Plane(const Vector3& _normal, const Point& _pt);
		/** The plane can be also made of 2 vectors. Normal vector
			is than equal to their cross product.
		*/
		explicit Plane(const Vector3& _vec1, const Vector3& _vec2, const Point& _pt);
		/// Plane can be also constructed from 3 points which lay on it.
		explicit Plane(const Vector3& _vec1, const Vector3& _vec2, const Vector3& _vec3);
		~Plane();

		/// Returns plane normal.
		const Vector3& getPlaneNormal() const;
		/// Returns plane D parameter.
		float getPlaneD() const;
		/// Returns point P0 belonging to the plane.
		const Point& getPlanePoint() const;

		/** Sets plane.
			@param _normal normal vector of the plane
			@param _d d parameter of the plane.
		*/
		void setPlane(const Vector3& _normal, float _d);
		/** Sets plane.
			@param _normal normal vector of the plane
			@param _pt point P0 laying on the plane.
		*/
		void setPlane(const Vector3& _normal, const Point& _pt);
		/// Sets plane.
		void setPlane(float _a, float _b, float _c, float _d);
		/// Constructs a plane from 3 points belonging to it.
		void setPlane(const Vector3& _vec1, const Vector3& _vec2, const Vector3& _vec3);

		/** Transforms the plane by the matrix.
			@param
				_transform transformation matrix has to be inverse transpose
				of the actual matrix to properly transform both normal and point
				of the plane.
		*/
		void transform(const Matrix4x4& _transform);

		/// Calculates distance from the plane for a given point.
		float getDistanceFromPlane(const Vector3& _vec) const;

		/** Creates Plane from string.
			@param
				_string keeping data of plane. Three formats are accepted:
				"a b c d", "a;b;c;d" and "a,b,c,d".
		*/
		void fromString(const std::string& _string);
		/// Writes Plane to string as "a b c d".
		std::string toString();
	};
}


#endif