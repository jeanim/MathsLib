#pragma once
#ifndef __INC_MATRIX3X3_H_
#define __INC_MATRIX3X3_H_


#include "Vector3.h"
#include "Vector4.h"

#include <string>


namespace MathsLib
{
	/** 4x4 matrix.
		@par
			Matrix is a mathematical object especially useful in linear
			transformations in vector spaces (eg. 2- or 3-dimensional
			euclidean space). Each vector of a space (point is also a
			vector) has to be simply multiplied by the transformation
			matrix to make transformation take place.
		@par
			Although many overloaded operators are available for clients
			convenience, in sake of efficiency it is better not to use
			them as many of them result in temporary object creation.
			It is better to use member functions instead. They provide
			the same functionality but are much faster due to lack of
			aforementioned drawback.
	*/
	class Matrix3x3
	{
	private:
		/// Helper function used for inverse matrix calculation.
		Matrix3x3 adjoint() const;

	public:
		/// Matrix's members
		union {
			struct {
				float _m11, _m12, _m13;
				float _m21, _m22, _m23;
				float _m31, _m32, _m33;
			};
			float _m[3][3];
			float m[9];
		};

		static const Matrix3x3 IDENTITY;

	public:
		Matrix3x3();
		explicit Matrix3x3(float _m11, float _m12, float _m13,
						   float _m21, float _m22, float _m23,
						   float _m31, float _m32, float _m33);
		~Matrix3x3();

		/// Sets all members at once.
		void set(float _m11, float _m12, float _m13,
			     float _m21, float _m22, float _m23,
			     float _m31, float _m32, float _m33);

		/** Matrix is turned into identity matrix.
			@remarks
				Identity matrix is a special kind of matrix
				which has 1s on its diagonal and 0s elsewhere.
		*/
		void identity();

		/** Matrix is turned into zero matrix.
			@remarks
				Zero matrix consists of 0s only.
		*/
		void zero();

		/** All members are negated.
		*/
		void negate();

		/** Calculates inverse matrix.
			@remarks
				Inverse matrix to the given matrix is matrix
				which multiplied by given matrix produces the
				identity one. In this special case, multiplication
				is alternate.
		*/
		void invert();
		/** Calculates the matrix determinant.
			@remarks
				Determinant is a number telling many things about
				the matrix eg. if it is zero, the matrix cannot be
				inverted.
		*/
		float determinant() const;
		/** Calculates determinant of the given minor.
			@remarks
				A minor is a square matrix constructed by leaving
				out some of the columns and rows of the base matrix.
			@remarks
				r0 through r1 are rows, and c0 to c1 - columns.
		*/
		float minor(unsigned int r0, unsigned int r1, unsigned int c0, unsigned int c1) const;

		/** Transposes the matrix.
			@remarks
				The rows of the matrix become columns of the
				transposed matrix. Analogous for columns.
		*/
		void transpose();

		/** Adds given matrix to the current one.
			@remarks
				Unlike multiplication, matrix addition is alternate.
		*/
		void add(const Matrix3x3& _mat);
		friend Matrix3x3 add(const Matrix3x3& _mat1, const Matrix3x3& _mat2);

		void subtract(const Matrix3x3& _matrix);
		friend Matrix3x3 subtract(const Matrix3x3& _mat1, const Matrix3x3& _mat2);

		/** Multiplies current matrix by given matrix
			@remarks
				Note that in case of 4x4 matrices multiplication is
				always possible. However, order of performing this
				operation is not arbitrary.
			@todo
				Provide SSE optimized version.
		*/
		void multiply(const Matrix3x3& _matrix);
		/// Multiplies all matrix members by a given number.
		void multiply(const float& _number);
		/** Multiplies matrix by 3D vector.
			@par
				This method multiplies matrix M and vector V in the following way:
				|m11 m12 m13|    |x|   |result.x|
				|m21 m22 m23| \/ |y| = |result.y|
				|m31 m32 m33| /\ |z|   |result.z|
		*/
		Vector3 multiply(const Vector3& _vec);
		friend Matrix3x3 multiply(const Matrix3x3& _mat1, const Matrix3x3& _mat2);

		/** Divides all cells by a real number.
			@param _number a divider - cannot be 0.
		*/
		void divide(const float& _number);


		/// Builds rotation matrix around the x-axis.
		void rotateAroundXAxis(float _angle);
		/// Builds rotation matrix around the y-axis.
		void rotateAroundYAxis(float _angle);
		/// Builds rotation matrix around the z-axis.
		void rotateAroundZAxis(float _angle);

		/** Builds a rotation matrix around specified arbitrary axis.
			@remarks
				Vector has to be normalized prior to calling this function.
			@param
				_axis axis to rotate around.
			@param
				_angle angle to rotate.
		*/
		void rotate(const Vector3& _axis, float _angle);

		/** Builds a rotation matrix from Euler angles.
			@par
				This function build rotation matrix from Euler angles, namely
				yaw, pitch and roll.
			@param
				_euler Euler angles. x - stands for Pitch, y - for Roll,
				z - for	Yaw.
		*/
		void rotateYawPitchRoll(const Vector3& _euler);
		/** Builds a rotation matrix from Euler angles.
			@par
				This function build rotation matrix from Euler angles, namely
				yaw, pitch and roll.
			@param _yaw yaw
			@param _pitch pitch
			@param _roll roll
		*/
		void rotateYawPitchRoll(float _yaw, float _pitch, float _roll);

		/// Builds non-uniform scaling matrix.
		void scale(const Vector3& _scale);
		/// Builds non-uniform scaling matrix.
		void scale(float _x, float _y, float _z);
		/// Builds uniform scaling matrix.
		void scale(float _s);

		/// Checks if matrix is an identity matrix.
		bool isIdentity();
		/// Checks if matrix contains only zeros.
		bool isZero();


		// Below are overloaded operators.


		Matrix3x3& operator+=(const Matrix3x3& rhs);
		Matrix3x3& operator-=(const Matrix3x3& rhs);
		Matrix3x3& operator*=(const Matrix3x3& rhs);
		Vector3 operator*=(const Vector3& rhs);
		Matrix3x3& operator*=(const float& rhs);

		friend const Matrix3x3 operator+(const Matrix3x3& lhs, const Matrix3x3& rhs);
		friend const Matrix3x3 operator*(const Matrix3x3& lhs, const Matrix3x3& rhs);
		friend const Matrix3x3 operator*(const Matrix3x3& lhs, const float& rhs);
		friend const Matrix3x3 operator*(const float& lhs, const Matrix3x3& rhs);
		friend const Vector3   operator*(const Matrix3x3& lhs, const Vector3& rhs);
		friend const Vector3   operator*(const Vector3& lhs, const Matrix3x3& rhs);
		friend const Matrix3x3 operator-(const Matrix3x3& lhs, const Matrix3x3& rhs);

		const Matrix3x3 operator-();

		bool operator==(const Matrix3x3& _mat);

		float* operator[](unsigned int i);
		const float* const operator[](unsigned int i) const;

		/// Returns array of data.
		float* getData();

		/** Creates Matrix3x3 from string.
			@param
				_string keeping data of matrix.
		*/
		void fromString(const std::string& _string);
		/// Writes Matrix3x3 to string as "_m11 _m12 ... _m44".
		std::string toString();
	};
}


#endif