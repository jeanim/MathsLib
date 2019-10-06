#pragma once
#ifndef __INC_VECTOR3_H_
#define __INC_VECTOR3_H_


#include "Maths.h"
#include "Assertion.h"
#include "Vector2.h"

#include <string>


namespace MathsLib
{
	class Plane;
	class Matrix3x3;

	/** 3-dimensional vector class.
		@par
			Although many overloaded operators are available for clients
			convenience, in sake of efficiency it is better not to use
			them as some of them (eg. +, -, *) result in temporary object
			creation. It is better to use member functions instead.
			They provide the same functionality but are much faster due
			to lack of aforementioned drawback.
		@par
			Vector3 class takes advantage of SIMD extensions if they are
			available on the platform the engine is being run on. This can
			greatly speed up complex calculations.
	*/
	class Vector3
	{
	public:
		union {
			struct {
				float x;
				float y;
				float z;
			};
			float vals[3];
		};

		// Some static members. They make up the standard base
		// in euclidean 3-dimensional space. Also negated version
		// of them is provided.
		static const Vector3 UNIT_X;
		static const Vector3 UNIT_Y;
		static const Vector3 UNIT_Z;
		static const Vector3 NEGATIVE_UNIT_X;
		static const Vector3 NEGATIVE_UNIT_Y;
		static const Vector3 NEGATIVE_UNIT_Z;

		static const Vector3 ZERO_VECTOR;
		static const Vector3 ONE_VECTOR;

		static const Vector3 INFINITY_VECTOR;
		static const Vector3 NEGATIVE_INFINITY_VECTOR;

	public:
		Vector3();
		explicit Vector3(float _x, float _y, float _z);
		explicit Vector3(const Vector2& _vec);
		explicit Vector3(const Vector2& _vec, float _z);
		~Vector3();

		/// Lets you set new members' values.
		void set(float _x, float _y, float _z);
		/// Lets you set new members' values.
		void set(const Vector3& _vec);

		/// Adds given vector to the current one.
		void add(const Vector3& _vec);
		/// Adds given vector to the current one.
		void add(float _x, float _y, float _z);
		/// Adds real number to all components.
		void add(float _num);

		/// Subtract given vector from the current one.
		void subtract(const Vector3& _vec);

		/** Vector by scalar multiplication.
			@remarks
				Each vector's member is multiplied by a given
				number.
		*/
		void multiplyByNumber(const float& _num);
		/** Vector by scalar divide.
			@remarks
				Each vector's member is divided by a given
				number.
		*/
		void divideByNumber(const float& _num);

		/** Normalizes current vector.
			@par
				If the vector length is 0 it does nothing.
			@remarks
				The new vector has the same direction as it had, but
				its	length is equal to 1. Therefore it is usually
				called unit	vector.
		*/
		void normalize();
		/** Normalizes current vector.
			@par
				If the vector length is 0 it does nothing.
			@remarks
				The new vector has the same direction as it had, but
				its	length is equal to 1. Therefore it is usually
				called unit	vector.
		*/
		friend Vector3 normalize(const Vector3& _vec);

		/** Negates current vector.
			@remarks
				The negated vector has the same length as it has
				before negating operation took place but all its
				members are opposite.
		*/
		void negate();

		/// Calculates the length (magnitude) of the vector.
		float getLength() const;
		/// Calculates the length (magnitude) of the vector.
		float length() const;

		/** Calculates dot product of the current vector and the
			vector given.
			@remarks
				Dot product, also called scalar product is especially
				useful when you need to obtain the angle between two
				vectors. Dot product of two unit vectors equals cosine
				of the angle between them, so calculating the angle is
				straightforward. For vectors of different lengths to
				get cosine you only need to divide result of this
				function by product of the given vectors' length.
			@return
				float dot product value
		*/
		float dotProduct(const Vector3& vec) const;

		/** Calculates cross product of the current vector and the
			vector given.
			@return
				Vector3 a vector which is perpendicular to the vectors
				given.
		*/
		Vector3 crossProduct(const Vector3& vec) const;

		/// Deflects a vector against given plane.
		Vector3 deflect(const Plane& _pl);

		/// Reflects a vector against given plane.
		Vector3 reflect(const Plane& _pl);

		/** Multiplies vector by 4x4 matrix.
			@par
				This method multiplies matrix M and vector V in the following way:
				             |m11 m12 m13 m14|
				          \/ |m21 m22 m23 m24|
				|x y z w| /\ |m31 m32 m33 m34| = |result.x result.y result.z result.w|
				             |m41 m42 m43 m44|
		*/
		void multiply(const Matrix3x3& _mat);


		// Below are overloaded operators.


		Vector3& operator+=(const Vector3& rhs);
		Vector3& operator-=(const Vector3& rhs);
		Vector3& operator*=(const Matrix3x3& rhs);
		Vector3& operator*=(const float& rhs);
		Vector3& operator/=(const float& rhs);
		
		friend const Vector3 operator+(const Vector3& lhs, const Vector3& rhs);
		friend const Vector3 operator-(const Vector3& lhs, const Vector3& rhs);

		friend const Vector3 operator/(const Vector3& lhs, const float& rhs);

		friend const Vector3 operator*(const Vector3& lhs, const float& rhs);
		friend const Vector3 operator*(const float& lhs, const Vector3& rhs);
		friend const Vector3 operator*(const Vector3& lhs, const Vector3& rhs);

		const Vector3 operator-();

		bool operator==(const Vector3& _vec);
		friend bool operator==(const Vector3& _vec1, const Vector3& _vec2);

		bool operator!=(const Vector3& _vec);
		friend bool operator!=(const Vector3& _vec1, const Vector3& _vec2);


		float operator[](size_t i);
		float operator[](size_t i) const;


		/// Returns array of data.
		float* getData();

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