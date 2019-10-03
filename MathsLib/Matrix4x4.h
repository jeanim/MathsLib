#pragma once
#ifndef __INC_MATRIX4X4_H_
#define __INC_MATRIX4X4_H_


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
		@par
			Matrix4x4 class takes advantage of SIMD extensions if they are
			available on the platform the engine is being run on. This can
			greatly speed up complex calculations.
		@par
			In case of rotation matrix functions note that following convention
			is used in nGENE: yaw stands for rotation around z axis, pitch - x
			and roll - y axis.
		@par
			Matrix4x4 is a set of 16-bytes aligned floating point values.
	*/
	class  Matrix4x4
	{
	private:
		/// Helper function used for inverse matrix calculation.
		Matrix4x4 adjoint() const;

	public:
		/// Matrix's members
		union {
			struct {
				float _m11, _m12, _m13, _m14;
				float _m21, _m22, _m23, _m24;
				float _m31, _m32, _m33, _m34;
				float _m41, _m42, _m43, _m44;
			};
			float _m[4][4];
			float m[16];
		};

		static const Matrix4x4 IDENTITY;

	public:
		Matrix4x4();
		explicit Matrix4x4(float _m11, float _m12, float _m13, float _m14,
						   float _m21, float _m22, float _m23, float _m24,
						   float _m31, float _m32, float _m33, float _m34,
						   float _m41, float _m42, float _m43, float _m44);
		~Matrix4x4();

		/// Sets all members at once.
		void set(float _m11, float _m12, float _m13, float _m14,
			     float _m21, float _m22, float _m23, float _m24,
			     float _m31, float _m32, float _m33, float _m34,
			     float _m41, float _m42, float _m43, float _m44);

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
				r0 through r2 are rows, and c0 to c2 - columns.
		*/
		float minor(unsigned int r0, unsigned int r1, unsigned int r2,
				   unsigned int c0, unsigned int c1, unsigned int c2) const;

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
		void add(const Matrix4x4& _mat);
		friend Matrix4x4 add(const Matrix4x4& _mat1, const Matrix4x4& _mat2);

		void subtract(const Matrix4x4& _matrix);
		friend Matrix4x4 subtract(const Matrix4x4& _mat1, const Matrix4x4& _mat2);

		/** Multiplies current matrix by given matrix
			@remarks
				Note that in case of 4x4 matrices multiplication is
				always possible. However, order of performing this
				operation is not arbitrary.
			@todo
				Provide SSE optimized version.
		*/
		void multiply(const Matrix4x4& _matrix);
		/// Multiplies all matrix members by a given number.
		void multiply(const float& _number);
		/** Multiplies matrix by 4D vector.
			@par
				This method multiplies matrix M and vector V in the following way:
				|m11 m12 m13 m14|    |x|   |result.x|
				|m21 m22 m23 m24| \/ |y|   |result.y|
				|m31 m32 m33 m34| /\ |z| = |result.z|
				|m41 m42 m43 m44|    |w|   |result.w|
		*/
		Vector4 multiply(const Vector4& _vec);
		friend Matrix4x4 multiply(const Matrix4x4& _mat1, const Matrix4x4& _mat2);

		/** Divides all cells by a real number.
			@param _number a divider - cannot be 0.
		*/
		void divide(const float& _number);


		/// Builds translation matrix from the Vector3.
		void translate(const Vector3& _translate);
		/// Builds translation matrix from 3 float values.
		void translate(float _x, float _y, float _z);
		/** Sets translation.
			@remarks
				This function does not turn matrix into identity matrix
				before proceeding.
		*/
		void setTranslation(const Vector3& _translate);
		/** Sets translation.
			@remarks
				This function does not turn matrix into identity matrix
				before proceeding.
		*/
		void setTranslation(float _x, float _y, float _z);
		/// Returns part of the matrix holding translation.
		Vector3 getTranslation() const;

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

		/** Builds view matrix.
			@param _eyePos position of the eye.
			@param _target direction which observer faces.
			@param _up vector pointing up.
		*/
		void lookAt(const Vector3& _eyePos, const Vector3& _target, const Vector3& _up);

		/** Builds orthogonal projection matrix.
			@param _width width of the screen.
			@param _height of the screen.
			@param _near near plane.
			@param _far far plane.
		*/
		void orthogonal(float _width, float _height, float _near, float _far);
		/** Builds perspective projection matrix.
			@param _fov field of view angle
			@param _aspect width to height ratio.
			@param _near near plane.
			@param _far far plane.
		*/
		void perspective(float _fov, float _aspect, float _near, float _far);

		/// Checks if this matrix is an identity matrix.
		bool isIdentity();
		/// Checks if this matrix contains zeros in all cells.
		bool isZero();


		// Below are overloaded operators.


		Matrix4x4& operator+=(const Matrix4x4& rhs);
		Matrix4x4& operator-=(const Matrix4x4& rhs);
		Matrix4x4& operator*=(const Matrix4x4& rhs);
		Vector4 operator*=(const Vector4& rhs);
		Matrix4x4& operator*=(const float& rhs);

		friend const Matrix4x4 operator+(const Matrix4x4& lhs, const Matrix4x4& rhs);
		friend const Matrix4x4 operator*(const Matrix4x4& lhs, const Matrix4x4& rhs);
		friend const Matrix4x4 operator*(const Matrix4x4& lhs, const float& rhs);
		friend const Matrix4x4 operator*(const float& lhs, const Matrix4x4& rhs);
		friend const Vector4   operator*(const Matrix4x4& lhs, const Vector4& rhs);
		friend const Vector4   operator*(const Vector4& lhs, const Matrix4x4& rhs);
		friend const Matrix4x4 operator-(const Matrix4x4& lhs, const Matrix4x4& rhs);

		const Matrix4x4 operator-();

		bool operator==(const Matrix4x4& _mat);

		float* operator[](unsigned int i);
		const float* const operator[](unsigned int i) const;

		/// Returns array of data.
		float* getData();

		/** Creates Matrix4x4 from string.
			@param
				_string keeping data of matrix.
		*/
		void fromString(const std::string& _string);
		/// Writes Matrix4x4 to string as "_m11 _m12 ... _m44".
		std::string toString();
	};
}


#endif