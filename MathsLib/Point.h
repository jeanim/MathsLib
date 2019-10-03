#pragma once
#ifndef __INC_POINT_H_
#define __INC_POINT_H_

#include <string>

#include "Maths.h"
#include "Vector3.h"


namespace MathsLib
{
	/** In terms of linear algebra a point is just
		a free vector.
		@remarks
			The class is much poorer than regular Vector3
			class as in case of points such functionality
			is not necessary.
	*/
	class  Point
	{
	public:
		/// Position of the point in 3D space
		union {
			struct {float x, y, z;};
			float point[3];
		};

		// Some important constants
		static const Point ZERO_POINT;

	public:
		Point();
		Point(const Vector3& _point);
		explicit Point(float _x, float _y, float _z);
		~Point();

		Point& operator=(const Point& _point);

		/// Sets the new member values.
		void set(float _x, float _y, float _z);
		/// Sets the new member values.
		void set(const Vector3& _point);

		/** Calculates the distance between the Point and the Point
			given.
		*/
		float distanceToPoint(const Point& _a);
		/** Calculates the distance between two given points.
		*/
		friend float distanceBetweenPoints(const Point& _a, const Point& _b);

		/// Translates the point.
		void translate(float _x, float _y, float _z);
		/// Translates the point.
		void translate(const Vector3& _vec);


		// Below are overloaded operators.


		Point& operator+=(const Vector3& rhs);

		friend const Vector3 operator-(const Point& lhs, const Point& rhs);

		bool operator==(const Point& _a);
		friend bool operator==(const Point& _a, const Point& _b);

		bool operator!=(const Point& _a);
		friend bool operator!=(const Point& _a, const Point& _b);

		operator Vector3() const;

		float operator[](unsigned int i);
		float operator[](unsigned int i) const;

		/** Creates Vector3 from string.
		@param
		_string keeping data of vector. Three formats are accepted:
		"x y z", "x;y;z" and "x,y,z".
		*/
		void fromString(const std::string& _string);
		/// Writes vector to string as "x y z".
		std::string toString();
	};
}


#endif