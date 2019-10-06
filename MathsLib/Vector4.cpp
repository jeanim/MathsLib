// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "Vector4.h"
#include "Maths.h"
#include "Vector2.h"
#include "Vector3.h"
#include "FuncSplit.h"
#include "Matrix4x4.h"
#include "Quaternion.h"

#include <sstream>


namespace MathsLib
{
	// Initialize static members
	const Vector4 Vector4::UNIT_X(1.0f, 0.0f, 0.0f, 0.0f);
	const Vector4 Vector4::UNIT_Y(0.0f, 1.0f, 0.0f, 0.0f);
	const Vector4 Vector4::UNIT_Z(0.0f, 0.0f, 1.0f, 0.0f);
	const Vector4 Vector4::UNIT_W(0.0f, 0.0f, 0.0f, 1.0f);

	const Vector4 Vector4::NEGATIVE_UNIT_X(-1.0f, 0.0f, 0.0f, 0.0f);
	const Vector4 Vector4::NEGATIVE_UNIT_Y(0.0f, -1.0f, 0.0f, 0.0f);
	const Vector4 Vector4::NEGATIVE_UNIT_Z(0.0f, 0.0f, -1.0f, 0.0f);
	const Vector4 Vector4::NEGATIVE_UNIT_W(0.0f, 0.0f, 0.0f, -1.0f);

	const Vector4 Vector4::ZERO_VECTOR(0.0f, 0.0f, 0.0f, 0.0f);
	const Vector4 Vector4::ONE_VECTOR(1.0f, 1.0f, 1.0f, 1.0f);

	const Vector4 Vector4::INFINITY_VECTOR(1e9, 1e9, 1e9, 1e9);
	const Vector4 Vector4::NEGATIVE_INFINITY_VECTOR(-1e9, -1e9, -1e9, -1e9);


	Vector4::Vector4():
		x(0.0f),
		y(0.0f),
		z(0.0f),
		w(0.0f)
	{
	}

	Vector4::Vector4(float _x, float _y, float _z, float _w):
		x(_x),
		y(_y),
		z(_z),
		w(_w)
	{
	}

	Vector4::Vector4(const Vector2& _vec):
		x(_vec.x),
		y(_vec.y),
		z(0.0f),
		w(0.0f)
	{
	}

	Vector4::Vector4(const Vector2& _vec, float _z, float _w):
		x(_vec.x),
		y(_vec.y),
		z(_z),
		w(_w)
	{
	}

	Vector4::Vector4(const Vector3& _vec):
		x(_vec.x),
		y(_vec.y),
		z(_vec.z),
		w(0.0f)
	{
	}

	Vector4::Vector4(const Vector3& _vec, float _w):
		x(_vec.x),
		y(_vec.y),
		z(_vec.z),
		w(_w)
	{
	}

	Vector4::Vector4(const Quaternion& _quat):
		x(_quat.x),
		y(_quat.y),
		z(_quat.z),
		w(_quat.w)
	{
	}

	Vector4::~Vector4()
	{
	}

	Vector4& Vector4::operator*=(const Matrix4x4& rhs)
	{
		multiply(rhs);
		return (*this);
	}

	void Vector4::multiply(const Matrix4x4& _mat)
	{
		/// @todo Implement SSE version
		if(Maths::isUsingSSE())
		{
		}
		else
		{
		}

		float X, Y, Z, W;

		X = x * _mat._m11 + y * _mat._m21 + z * _mat._m31 + w * _mat._m41;
		Y = x * _mat._m12 + y * _mat._m22 + z * _mat._m32 + w * _mat._m42;
		Z = x * _mat._m13 + y * _mat._m23 + z * _mat._m33 + w * _mat._m43;
		W = x * _mat._m14 + y * _mat._m24 + z * _mat._m34 + w * _mat._m44;

		this->x = X;
		this->y = Y;
		this->z = Z;
		this->w = W;
	}

	void Vector4::fromString(const std::string& _string)
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

	std::string Vector4::toString()
	{
		std::stringstream buffer;
		buffer << x << " " << y << " " << z << " " << w;

		return buffer.str();
	}

	void Vector4::set(float _x, float _y, float _z, float _w)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}

	void Vector4::set(const Vector4& _vec)
	{
		x = _vec.x;
		y = _vec.y;
		z = _vec.z;
		w = _vec.w;
	}

	void Vector4::add(const Vector4& _vec)
	{
		x += _vec.x;
		y += _vec.y;
		z += _vec.z;
		w += _vec.w;
	}

	void Vector4::add(float _x, float _y, float _z, float _w)
	{
		x += _x;
		y += _y;
		z += _z;
		w += _w;
	}

	void Vector4::add(float _num)
	{
		x += _num;
		y += _num;
		z += _num;
		w += _num;
	}

	void Vector4::subtract(const Vector4& _vec)
	{
		x -= _vec.x;
		y -= _vec.y;
		z -= _vec.z;
		w -= _vec.w;
	}

	void Vector4::multiplyByNumber(const float& _num)
	{
		x *= _num;
		y *= _num;
		z *= _num;
		w *= _num;
	}

	void Vector4::divideByNumber(const float& _num)
	{
		x /= _num;
		y /= _num;
		z /= _num;
		w /= _num;
	}

	void Vector4::normalize()
	{
		float length = Maths::fsqrt((x * x) + (y * y) + (z * z) + (w * w));
		if (!Maths::floatCompare(0.0f, length))
			return;

		float inv = 1.0f / length;
		x *= inv;
		y *= inv;
		z *= inv;
		w *= inv;
	}

	void Vector4::negate()
	{
		x = -x;
		y = -y;
		z = -z;
		w = -w;
	}

	float Vector4::getLength() const
	{
		float length;

		length = Maths::fsqrt(x * x + y * y + z * z + w * w);

		return length;
	}

	float Vector4::length() const
	{
		return getLength();
	}

	float Vector4::dotProduct(const Vector4& vec) const
	{
		return (x * vec.x + y * vec.y + z * vec.z + w * vec.w);
	}

	Vector4 normalize(const Vector4& _vec)
	{
		float length = _vec.getLength();
		if (!Maths::floatCompare(0.0f, length))
			return Vector4(_vec);

		Vector4 result = _vec;

		float inv = 1.0f / length;
		result.x *= inv;
		result.y *= inv;
		result.z *= inv;

		return result;
	}

	Vector4& Vector4::operator+=(const Vector4& rhs)
	{
		add(rhs);
		return (*this);
	}

	Vector4& Vector4::operator-=(const Vector4& rhs)
	{
		subtract(rhs);
		return (*this);
	}

	Vector4& Vector4::operator*=(const float& rhs)
	{
		multiplyByNumber(rhs);
		return (*this);
	}

	Vector4& Vector4::operator/=(const float& rhs)
	{
		divideByNumber(rhs);
		return (*this);
	}

	const Vector4 Vector4::operator-()
	{
		Vector4 newVector(*this);
		newVector.negate();

		return (newVector);
	}

	bool Vector4::operator==(const Vector4& _vec)
	{
		return (!Maths::floatCompare(x, _vec.x) &&
			!Maths::floatCompare(y, _vec.y) &&
			!Maths::floatCompare(z, _vec.z) &&
			!Maths::floatCompare(w, _vec.w));
	}

	bool Vector4::operator!=(const Vector4& _vec)
	{
		return (Maths::floatCompare(x, _vec.x) ||
			Maths::floatCompare(y, _vec.y) ||
			Maths::floatCompare(z, _vec.z) ||
			Maths::floatCompare(w, _vec.w));
	}

	const Vector4 operator+(const Vector4& lhs, const Vector4& rhs)
	{
		return Vector4(lhs.x + rhs.x,
			lhs.y + rhs.y,
			lhs.z + rhs.z,
			lhs.w + rhs.w);
	}

	const Vector4 operator-(const Vector4& lhs, const Vector4& rhs)
	{
		return Vector4(lhs.x - rhs.x,
			lhs.y - rhs.y,
			lhs.z - rhs.z,
			lhs.w - rhs.w);
	}

	const Vector4 operator/(const Vector4& lhs, const float& rhs)
	{
		Vector4 result = lhs;
		result.divideByNumber(rhs);

		return result;
	}

	const Vector4 operator*(const Vector4& lhs, const float& rhs)
	{
		Vector4 result = lhs;
		result.multiplyByNumber(rhs);

		return result;
	}

	const Vector4 operator*(const float& lhs, const Vector4& rhs)
	{
		Vector4 result = rhs;
		result.multiplyByNumber(lhs);

		return result;
	}

	bool operator==(const Vector4& _vec1, const Vector4& _vec2)
	{
		return (!Maths::floatCompare(_vec1.x, _vec2.x) &&
			!Maths::floatCompare(_vec1.y, _vec2.y) &&
			!Maths::floatCompare(_vec1.z, _vec2.z) &&
			!Maths::floatCompare(_vec1.w, _vec2.w));
	}

	bool operator!=(const Vector4& _vec1, const Vector4& _vec2)
	{
		return (Maths::floatCompare(_vec1.x, _vec2.x) ||
			Maths::floatCompare(_vec1.y, _vec2.y) ||
			Maths::floatCompare(_vec1.z, _vec2.z) ||
			Maths::floatCompare(_vec1.w, _vec2.w));
	}

	float Vector4::operator[](size_t i)
	{
		Assert(i < 4, "Vector dimension index not allowed"); //-V112
		return (vals[i]);
	}

	float Vector4::operator[](size_t i) const
	{
		Assert(i < 4, "Vector dimension index not allowed"); //-V112
		return (vals[i]);
	}

	float* Vector4::getData()
	{
		return &vals[0];
	}

}