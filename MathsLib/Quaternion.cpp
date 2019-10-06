// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "Quaternion.h"
#include "FuncSplit.h"
#include "Matrix4x4.h"

#include <sstream>


namespace MathsLib
{
	Quaternion::Quaternion(float _x, float _y, float _z, float _w)
	{
		set(_x, _y, _z, _w);
	}

	Quaternion::Quaternion(const Vector3& _axis, const float _angle)
	{
		set(_axis, _angle);
	}

	Quaternion::~Quaternion()
	{
	}

	Matrix4x4 Quaternion::toMatrix() const
	{
		Matrix4x4 result;

		// Some auxiliary variables
		float wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2;

		x2=x+x;		y2=y+y;		z2=z+z;
		xx=x*x2;	yy=y*y2;	zz=z*z2;

		xy=x*y2;
		xz=x*z2;
		yz=y*z2;

		wx=w*x2;
		wy=w*y2;
		wz=w*z2;

		result._m11=1.0f-yy-zz;
		result._m12=xy+wz;
		result._m13=xz-wy;

		result._m21=xy-wz;
		result._m22=1.0f-xx-zz;
		result._m23=yz+wx;

		result._m31=xz+wy;
		result._m32=yz-wx;
		result._m33=1.0f-xx-yy;


		return result;
	}

	void Quaternion::fromEulerAngles(float _yaw, float _pitch, float _roll)
	{
		set(_yaw, _pitch, _roll);
	}

	void Quaternion::fromEulerAngles(const Vector3& _angles)
	{
		set(_angles.x, _angles.y, _angles.z);
	}

	void Quaternion::fromMatrix(const Matrix4x4& _mat)
	{
		float trace = _mat._m11 + _mat._m22 + _mat._m33;
		float root;

		if(trace > 0.0f)
		{
			root = Maths::fsqrt(trace + 1.0f);

			this->w = 0.5f * root;
			root = 0.5f / root;
			this->x = -(_mat._m32 - _mat._m23) * root;
			this->y = -(_mat._m13 - _mat._m31) * root;
			this->z = -(_mat._m21 - _mat._m12) * root;
		}
		else
		{
			unsigned int next[3] = {1, 2, 0};
			unsigned int i = 0;
			if(_mat[1][1] > _mat[0][0])
				i = 1;
			if(_mat[2][2] > _mat[i][i])
				i = 2;
			unsigned int j = next[i];
			unsigned int k = next[j];

			root = Maths::fsqrt(_mat[i][i] - _mat[j][j] - _mat[k][k] + 1.0f);
			float* pQuat[3] = {&this->x, &this->y, &this->z};
			*pQuat[i] = -0.5f * root;
			root = 0.5f / root;
			this->w = (_mat[k][j] - _mat[j][k]) * root;
			*pQuat[j] = -(_mat[j][i] + _mat[i][j]) * root;
			*pQuat[k] = -(_mat[k][i] + _mat[i][k]) * root;
		}
	}

	void Quaternion::fromString(const std::string& _string)
	{
		std::vector <std::string> vecValues;
		FuncSplit <std::string> tokenizer;
		tokenizer(_string, vecValues, " ,;");

		if(vecValues.size() == 4) //-V112
		{
			auto iter = vecValues.begin();
			x = atof((iter++)->c_str());
			y = atof((iter++)->c_str());
			z = atof((iter++)->c_str());
			w = atof((iter++)->c_str());
		}
	}

	std::string Quaternion::toString()
	{
		std::stringstream buffer;
		buffer << x << " " << y << " " << z << " " << w;

		return buffer.str();
	}

	Quaternion& Quaternion::operator=(const Quaternion& _quat)
	{
		x = _quat.x;
		y = _quat.y;
		z = _quat.z;
		w = _quat.w;

		return (*this);
	}

	void Quaternion::set(float _x, float _y, float _z, float _w)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}

	void Quaternion::set(const Vector3& _axis, const float _angle)
	{
		float halfAngle = _angle * 0.5f;
		x = Maths::fsin(halfAngle) * _axis.x;
		y = Maths::fsin(halfAngle) * _axis.y;
		z = Maths::fsin(halfAngle) * _axis.z;
		w = Maths::fcos(halfAngle);
	}

	void Quaternion::set(float _yaw, float _pitch, float _roll)
	{
		float halfYaw = _yaw * 0.5f;
		float halfPitch = _pitch * 0.5f;
		float halfRoll = _roll * 0.5f;

		float sinHY = Maths::fsin(halfYaw);
		float cosHY = Maths::fcos(halfYaw);

		float sinHP = Maths::fsin(halfPitch);
		float cosHP = Maths::fcos(halfPitch);

		float sinHR = Maths::fsin(halfRoll);
		float cosHR = Maths::fcos(halfRoll);

		x = cosHY * cosHP * sinHR - sinHY * sinHP * cosHR;
		y = cosHY * sinHP * cosHR + sinHY * cosHP * sinHR;
		z = sinHY * cosHP * cosHR - cosHY * sinHP * sinHR;
		w = cosHY * cosHP * cosHR + sinHY * sinHP * sinHR;
	}

	void Quaternion::identity()
	{
		x = y = z = 0.0f;
		w = 1.0f;
	}

	void Quaternion::conjugate()
	{
		x = -x;
		y = -y;
		z = -z;
	}

	Quaternion conjugate(const Quaternion& _quat)
	{
		Quaternion result = _quat;
		result.conjugate();

		return result;
	}

	float Quaternion::getLength() const
	{
		return (Maths::fsqrt(x * x + y * y + z * z + w * w));
	}

	float Quaternion::length() const
	{
		return (Maths::fsqrt(x * x + y * y + z * z + w * w));
	}

	void Quaternion::normalize()
	{
		float inv = 1.0f / length();
		x *= inv;
		y *= inv;
		z *= inv;
		w *= inv;
	}

	void Quaternion::invert()
	{
		float len = length();

		// Zero-length quaternion cannot be inverted
		if (Maths::floatEquals(len, 0.0f))
			return;

		Quaternion conj = (*this);
		conj.conjugate();
		float invSqrLen = 1.0f / len * len;

		(*this) = conj * invSqrLen;
	}

	void Quaternion::multiply(const Quaternion& _quat)
	{
		float X, Y, Z, W;

		X = w * _quat.x + x * _quat.w + y * _quat.z - z * _quat.y;
		Y = w * _quat.y + y * _quat.w + z * _quat.x - x * _quat.z;
		Z = w * _quat.z + z * _quat.w + x * _quat.y - y * _quat.x;
		W = w * _quat.w - x * _quat.x - y * _quat.y - z * _quat.z;

		(*this) = Quaternion(X, Y, Z, W);
	}

	Vector3 Quaternion::multiply(const Vector3& _vec) const
	{
		// nVidia SDK implementation
		Vector3 uv, uuv;
		Vector3 qvec(x, y, z);
		uv = qvec.crossProduct(_vec);
		uuv = qvec.crossProduct(uv);
		uv *= (2.0f * w);
		uuv *= 2.0f;

		return (_vec + uv + uuv);
	}

	Quaternion quaternionBetweenVectorsNormalized(const Vector3& _vec1, const Vector3& _vec2)
	{
		Vector3 axis = _vec1 * _vec2;
		axis.normalize();
		float angle = acosf((_vec1.dotProduct(_vec2)) / (_vec1.length() * _vec2.length()));

		Quaternion quat(axis, angle);
		quat.normalize();

		return quat;
	}

	Quaternion quaternionBetweenVectors(const Vector3& _vec1, const Vector3& _vec2)
	{
		Vector3 axis = _vec1 * _vec2;
		axis.normalize();
		float angle = acosf((_vec1.dotProduct(_vec2)) / (_vec1.length() * _vec2.length()));

		return Quaternion(axis, angle);
	}

	Quaternion& Quaternion::operator*=(const Quaternion& _quat)
	{
		multiply(_quat);
		return (*this);
	}

	Vector3 Quaternion::operator*(const Vector3& _vec) const
	{
		return (multiply(_vec));
	}

	const Quaternion operator*(const Quaternion& lhs, const Quaternion& rhs)
	{
		Quaternion result = lhs;
		result *= rhs;

		return result;
	}

	bool Quaternion::operator==(const Quaternion& _quat)
	{
		return (Maths::floatEquals(x, _quat.x) && Maths::floatEquals(y, _quat.y) &&
			Maths::floatEquals(z, _quat.z) && Maths::floatEquals(w, _quat.w));
	}

	bool Quaternion::operator!=(const Quaternion& _quat)
	{
		return (!Maths::floatEquals(x, _quat.x) || !Maths::floatEquals(y, _quat.y) ||
			!Maths::floatEquals(z, _quat.z) || !Maths::floatEquals(w, _quat.w));
	}

	Quaternion slerp(const Quaternion& _quat1, const Quaternion& _quat2, float _t)
	{
		Quaternion quat1 = _quat1;
		Quaternion quat2 = _quat2;

		float dot = quat1.x * quat2.x +
			quat1.y * quat2.y +
			quat1.z * quat2.z +
			quat1.w * quat2.w;

		if (dot < 0.0f)
		{
			quat2.conjugate();
			quat2.w = -quat2.w;
			dot = FastFloat::fabs(dot);
		}

		float factor1, factor2;
		if (dot > 0.9999f)
		{
			// Too close - we apply linear interpolation
			factor1 = 1.0f - _t;
			factor2 = _t;
		}
		else
		{
			float sin = sqrt(1.0f - dot * dot);
			float omega = atan2(sin, dot);

			float oneOverSin = 1.0f / sin;

			factor1 = sinf((1.0f - _t) * omega) * oneOverSin;
			factor2 = sinf(_t * omega) * oneOverSin;
		}

		Quaternion result(quat1.x * factor1 + quat2.x * factor2,
			quat1.y * factor1 + quat2.y * factor2,
			quat1.z * factor1 + quat2.z * factor2,
			quat1.w * factor1 + quat2.w * factor2);

		return result;
	}

	Vector3 Quaternion::toEuler() const
	{
		float sqw = w * w;
		float sqx = x * x;
		float sqy = y * y;
		float sqz = z * z;

		float rotx = atan2f(2.0f * (y * z + x * w), (-sqx - sqy + sqz + sqw));
		float roty = asinf(-2.0f * (x * z - y * w));
		float rotz = atan2f(2.0f * (x * y + z * w), (sqx - sqy - sqz + sqw));

		return Vector3(rotx, roty, rotz);
	}

	float Quaternion::operator[](size_t i)
	{
		Assert(i < 4, "Quaternion dimension index not allowed"); //-V112
		return (q[i]);
	}

	float Quaternion::operator[](size_t i) const
	{
		Assert(i < 4, "Quaternion dimension index not allowed"); //-V112
		return (q[i]);
	}

}