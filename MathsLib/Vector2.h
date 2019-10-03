#pragma once
#ifndef __INC_VECTOR2_H_
#define __INC_VECTOR2_H_


#include "Maths.h"
#include "Assertion.h"
#include <string>


namespace MathsLib
{
	/** 2-dimensional vector class.
		@par
			Although many overloaded operators are available for clients
			convenience, in sake of efficiency it is better not to use
			them as some of them (eg. +, -, *) result in temporary object
			creation. It is better to use member functions instead.
			They provide the same functionality but are much faster due
			to lack of aforementioned drawback.
	*/
	class Vector2
	{
	public:
		union {
			struct {
				float x;
				float y;
			};
			float vals[2];
		};

		// Some static members. They make up the standard base
		// in euclidean 2-dimensional space. Also negated version
		// of them is provided.
		static const Vector2 UNIT_X;
		static const Vector2 UNIT_Y;
		static const Vector2 NEGATIVE_UNIT_X;
		static const Vector2 NEGATIVE_UNIT_Y;

		static const Vector2 ZERO_VECTOR;
		static const Vector2 ONE_VECTOR;

		static const Vector2 INFINITY_VECTOR;
		static const Vector2 NEGATIVE_INFINITY_VECTOR;

	public:
		explicit Vector2(float _x=0.0f, float _y=0.0f);
		~Vector2();

		Vector2& operator=(const Vector2& _vec);

		/// Lets you set new members' values.
		void set(float _x, float _y);
		/// Lets you set new members' values.
		void set(const Vector2& _vec);


		/// Adds given vector to the current one.
		void add(const Vector2& _vec);
		/// Adds given vector to the current one.
		void add(float _x, float _y);
		/// Adds real number to all components.
		void add(float _num);

		/// Subtract given vector from the current one.
		void subtract(const Vector2& _vec);

		/** Vector by scalar multiplication.
			@remarks
				Each vector's member is multiplied by a given
				number.
		*/
		void multiplyByNumber(const float& _num);

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
		friend Vector2 normalize(const Vector2& _vec);

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
		float dotProduct(const Vector2& vec) const;


		// Below are overloaded operators.


		Vector2& operator+=(const Vector2& rhs);
		Vector2& operator-=(const Vector2& rhs);
		Vector2& operator*=(const float& rhs);
		
		friend const Vector2 operator+(const Vector2& lhs, const Vector2& rhs);
		friend const Vector2 operator-(const Vector2& lhs, const Vector2& rhs);
		friend const Vector2 operator*(const Vector2& lhs, const float& rhs);
		friend const Vector2 operator*(const float& lhs, const Vector2& rhs);

		friend const float operator%(const Vector2& lhs, const Vector2& rhs);

		const Vector2 operator-();

		bool operator==(const Vector2& _vec);
		friend bool operator==(const Vector2& _vec1, const Vector2& _vec2);

		bool operator!=(const Vector2& _vec);
		friend bool operator!=(const Vector2& _vec1, const Vector2& _vec2);

		float operator[](unsigned int i);
		float operator[](unsigned int i) const;

		/// Returns array of data.
		float* getData();

		/** Creates Vector2 from string.
			@param
				_string keeping data of vector. Three formats are accepted:
				"x y", "x;y" and "x,y".
		*/
		void fromString(const std::string& _string);
		/// Writes vector to string as "x y".
		std::string toString();
	};
}


#endif