#pragma once
#ifndef __INC_QUATERNION_H_
#define __INC_QUATERNION_H_


#include "FastFloat.h"

#include <string>


namespace MathsLib
{
	class Vector3;
	class Matrix4x4;

	/** Quaternion is a class useful when smooth rotations are required
		as in this case gimbal lock does not occur.
		@remarks
			From Mathematics point of view, a quaternion is more generalized
			form of complex number having interpretation in 4D space as axis
			and rotation around it.
	*/
	class Quaternion
	{
	public:
		union {
			struct {
				float x;
				float y;
				float z;
				float w;
			};
			float q[4];
		};

	public:
		Quaternion(float _x=0.0f, float _y=0.0f, float _z=0.0f, float _w=1.0f);
		explicit Quaternion(const Vector3& _axis, const float _angle);
		~Quaternion();

		Quaternion& operator=(const Quaternion& _quat);

		/// Sets quaternion value.
		void set(float _x, float _y, float _z, float _w);
		/// Sets quaternion value.
		void set(const Vector3& _axis, const float _angle);
		/// Sets quaternion value from Euler angles.
		void set(float _yaw, float _pitch, float _roll);

		/** Builds identity quaternion.
			@remarks
				Identity quaternion is a quaternion with x, y, z (complex part)
				being equal to 0.0 and w (real part) to 1.0.
		*/
		void identity();

		/** Conjugates the quaternion.
			@remarks
				Conjugated quaternion has x, y, z negated, whereas w stays the
				same.
		*/
		void conjugate();
		/** Conjugates the quaternion.
			@remarks
			Conjugated quaternion has x, y, z negated, whereas w stays the
			same.
		*/
		friend Quaternion conjugate(const Quaternion& _quat);

		/// Returns the length of the quaternion.
		float getLength() const;
		/// Returns the length of the quaternion.
		float length() const;

		/** Normalizes the quaternion (computes an unit length quaternion).
		*/
		void normalize();
		
		/** Calculates inverse quaternion.
			@remarks
				Quaternion has to be of non-zero length.
		*/
		void invert();

		/// Multiplies quaternion by another quaternion.
		void multiply(const Quaternion& _quat);
		/// Multiplies quaternion by 3D Vector resulting in a 3D Vector.
		Vector3 multiply(const Vector3& _vec) const;

		/** Interpolates between two quaternions using spherical linear interpolation	.
			@param
				_quat1 source quaternion.
			@param
				_quat2 destination quaternion.
			@param
				_t indicates how far to interpolate between given quaternions.
				It ranges 0 to 1, where 0 indicates that the interpolation
				result equals to source quaternion and 1 - that the results
				is equal to the destination quaternion.
		*/
		friend Quaternion slerp(const Quaternion& _quat1, const Quaternion& _quat2, float _t);

		/** Converts the quaternion to Matrix4x4.
			@par
				This way you actually extract rotation matrix from the
				quaternion.
		*/
		Matrix4x4 toMatrix() const;
		/** Builds quaternion from rotation matrix.
			@par
				Based on the algorithm described in Ken Shoemake's article
				from SIGGRAPH 1987: "Quaternion Calculus and Fast Animation".
		*/
		void fromMatrix(const Matrix4x4& _mat);

		/// Builds quaternion from Euler angles.
		void fromEulerAngles(float _yaw, float _pitch, float _roll);
		/// Builds quaternion from Euler angles.
		void fromEulerAngles(const Vector3& _angles);

		/// Convert the quaternion to Euler representation.
		Vector3 toEuler() const;


		/** Finds a quaternion rotating one vector onto another.
			@param _vec1 first vector. Can be of arbitrary length.
			@param _vec2 first vector. Can be of arbitrary length.
			@returns
				Quaternion resulting quaternion. The result will be different
				if _vec1 and _vec2 were switched. The result is not necessarily
				an unit quaternion.
			@remarks
				As there might be more than one quaternion transforming one vector
				onto another this function finds only one of the solutions -
				rotation by the shortest arc.
		*/
		friend Quaternion quaternionBetweenVectors(const Vector3& _vec1, const Vector3& _vec2);
		/** Finds a quaternion rotating one vector onto another.
			@param _vec1 first vector. Can be of arbitrary length.
			@param _vec2 first vector. Can be of arbitrary length.
			@returns
				Quaternion resulting quaternion. The result will be different
				if _vec1 and _vec2 were switched. The result is an unit quaternion.
			@remarks
				As there might be more than one quaternion transforming one vector
				onto another this function finds only one of the solutions -
				rotation by the shortest arc.
			*/
		friend Quaternion quaternionBetweenVectorsNormalized(const Vector3& _vec1, const Vector3& _vec2);


		// Below are overloaded operators.


		Quaternion& operator*=(const Quaternion& _quat);
		
		Vector3 operator*(const Vector3& _vec) const;
		friend const Quaternion operator*(const Quaternion& lhs, const Quaternion& rhs);


		bool operator==(const Quaternion& _quat);
		bool operator!=(const Quaternion& _quat);

		float operator[](unsigned int i);
		float operator[](unsigned int i) const;


		/** Creates Quaternion from string.
			@param
				_string keeping data of quaternion. Three formats are accepted:
				"x y z w", "x;y;z;w" and "x,y,z,w".
		*/
		void fromString(const std::string& _string);
		/// Writes quaternion to string as "x y z w".
		std::string toString();
	};
}


#endif