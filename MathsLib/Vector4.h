#pragma once
#ifndef __INC_VECTOR4_H_
#define __INC_VECTOR4_H_


#include "Assertion.h"
#include <string>


namespace MathsLib
{
	class Vector2;
	class Vector3;
	class Quaternion;
	class Matrix4x4;

	/** 4-dimensional vector class.
		@par
			Although many overloaded operators are available for clients
			convenience, in sake of efficiency it is better not to use
			them as some of them (eg. +, -, *) result in temporary object
			creation. It is better to use member functions instead.
			They provide the same functionality but are much faster due
			to lack of aforementioned drawback.
		@par
			Vector4 class takes advantage of SIMD extensions if they are
			available on the platform the engine is being run on. This can
			greatly speed up complex calculations.
	*/
	class Vector4
	{
	public:
		union {
			struct {
				float x;
				float y;
				float z;
				float w;
			};
			float vals[4];
		};

		// Some static members. They make up the standard base
		// in euclidean 4-dimensional space. Also negated version
		// of them is provided.
		static const Vector4 UNIT_X;
		static const Vector4 UNIT_Y;
		static const Vector4 UNIT_Z;
		static const Vector4 UNIT_W;
		static const Vector4 NEGATIVE_UNIT_X;
		static const Vector4 NEGATIVE_UNIT_Y;
		static const Vector4 NEGATIVE_UNIT_Z;
		static const Vector4 NEGATIVE_UNIT_W;

		static const Vector4 ZERO_VECTOR;
		static const Vector4 ONE_VECTOR;

		static const Vector4 INFINITY_VECTOR;
		static const Vector4 NEGATIVE_INFINITY_VECTOR;

	public:
		Vector4();
		explicit Vector4(float _x, float _y, float _z, float _w);
		explicit Vector4(const Vector2& _vec);
		explicit Vector4(const Vector2& _vec, float _z, float _w);
		explicit Vector4(const Vector3& _vec);
		explicit Vector4(const Vector3& _vec, float _w);
		explicit Vector4(const Quaternion& _quat);
		~Vector4();

		/// Lets you set new members' values.
		void set(float _x, float _y, float _z, float _w);
		/// Lets you set new members' values.
		void set(const Vector4& _vec);

		/// Adds given vector to the current one.
		void add(const Vector4& _vec);
		/// Adds given vector to the current one.
		void add(float _x, float _y, float _z, float _w);
		/// Adds real number to all components.
		void add(float _num);

		/// Subtract given vector from the current one.
		void subtract(const Vector4& _vec);

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
		friend Vector4 normalize(const Vector4& _vec);

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
		float dotProduct(const Vector4& _vec) const;

		/** Multiplies vector by 4x4 matrix.
			@par
				This method multiplies matrix M and vector V in the following way:
				             |m11 m12 m13 m14|
				          \/ |m21 m22 m23 m24|
				|x y z w| /\ |m31 m32 m33 m34| = |result.x result.y result.z result.w|
				             |m41 m42 m43 m44|
		*/
		void multiply(const Matrix4x4& _mat);


		// Below are overloaded operators.


		Vector4& operator+=(const Vector4& rhs);
		Vector4& operator-=(const Vector4& rhs);
		Vector4& operator*=(const float& rhs);
		Vector4& operator*=(const Matrix4x4& rhs);
		Vector4& operator/=(const float& rhs);
		
		friend const Vector4 operator+(const Vector4& lhs, const Vector4& rhs);
		friend const Vector4 operator-(const Vector4& lhs, const Vector4& rhs);

		friend const Vector4 operator/(const Vector4& lhs, const float& rhs);

		friend const Vector4 operator*(const Vector4& lhs, const float& rhs);
		friend const Vector4 operator*(const float& lhs, const Vector4& rhs);

		const Vector4 operator-();

		bool operator==(const Vector4& _vec);
		friend bool operator==(const Vector4& _vec1, const Vector4& _vec2);

		bool operator!=(const Vector4& _vec);
		friend bool operator!=(const Vector4& _vec1, const Vector4& _vec2);

		float operator[](size_t i);
		float operator[](size_t i) const;

		/// Returns array of data.
		float* getData();

		/** Creates Vector4 from string.
			@param
				_string keeping data of vector. Three formats are accepted:
				"x y z w", "x;y;z;w" and "x,y,z,w".
		*/
		void fromString(const std::string& _string);
		/// Writes vector to string as "x y z w".
		std::string toString();
	};
}


#endif