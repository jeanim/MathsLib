// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "Vector3.h"
#include "FuncSplit.h"
#include "Matrix3x3.h"
#include "Plane.h"
#include "FuncSplit.h"

#include <sstream>


namespace MathsLib
{
	// Static members initialization
	const Vector3 Vector3::UNIT_X(1.0f, 0.0f, 0.0f);
	const Vector3 Vector3::UNIT_Y(0.0f, 1.0f, 0.0f);
	const Vector3 Vector3::UNIT_Z(0.0f, 0.0f, 1.0f);
	const Vector3 Vector3::NEGATIVE_UNIT_X(-1.0f, 0.0f, 0.0f);
	const Vector3 Vector3::NEGATIVE_UNIT_Y(0.0f, -1.0f, 0.0f);
	const Vector3 Vector3::NEGATIVE_UNIT_Z(0.0f, 0.0f, -1.0f);

	const Vector3 Vector3::ZERO_VECTOR(0.0f, 0.0f, 0.0f);
	const Vector3 Vector3::ONE_VECTOR(1.0f, 1.0f, 1.0f);

	const Vector3 Vector3::INFINITY_VECTOR(1e9, 1e9, 1e9);
	const Vector3 Vector3::NEGATIVE_INFINITY_VECTOR(-1e9, -1e9, -1e9);


	Vector3::Vector3() :
		x(0.0f),
		y(0.0f),
		z(0.0f)
	{
	}

	Vector3::Vector3(float _x, float _y, float _z) :
		x(_x),
		y(_y),
		z(_z)
	{
	}

	Vector3::Vector3(const Vector2& _vec) :
		x(_vec.x),
		y(_vec.y),
		z(0.0f)
	{
	}

	Vector3::Vector3(const Vector2& _vec, float _z) :
		x(_vec.x),
		y(_vec.y),
		z(_z)
	{
	}

	Vector3::~Vector3()
	{
	}

	Vector3 Vector3::reflect(const Plane& _pl)
	{
		float distance = _pl.getDistanceFromPlane(*this);
		Vector3 normal = _pl.getPlaneNormal();

		return ((*this) - normal * (2.0f * distance));
	}

	Vector3 Vector3::deflect(const Plane& _pl)
	{
		Vector3 normal = _pl.getPlaneNormal();
		float dot = this->dotProduct(normal);

		return ((*this) - normal * (2.0f * dot));
	}

	Vector3& Vector3::operator*=(const Matrix3x3& rhs)
	{
		multiply(rhs);
		return (*this);
	}

	void Vector3::multiply(const Matrix3x3& _mat)
	{
		/// @todo Implement SSE version
		if(Maths::isUsingSSE())
		{
		}
		else
		{
		}

		float X, Y, Z;

		X = x * _mat._m11 + y * _mat._m21 + z * _mat._m31;
		Y = x * _mat._m12 + y * _mat._m22 + z * _mat._m32;
		Z = x * _mat._m13 + y * _mat._m23 + z * _mat._m33;

		this->x = X;
		this->y = Y;
		this->z = Z;
	}

	void Vector3::fromString(const std::string& _string)
	{
		std::vector <std::string> vecValues;
		FuncSplit <std::string> tokenizer;
		tokenizer(_string, vecValues, " ,;");

		if(vecValues.size() == 3)
		{
			auto iter = vecValues.begin();
			x = atof((iter++)->c_str());
			y = atof((iter++)->c_str());
			z = atof((iter++)->c_str());
		}
	}

	std::string Vector3::toString()
	{
		std::stringstream buffer;
		buffer << x << " " << y << " " << z;

		return buffer.str();
	}

	void Vector3::set(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	void Vector3::set(const Vector3& _vec)
	{
		x = _vec.x;
		y = _vec.y;
		z = _vec.z;
	}

	void Vector3::add(const Vector3& _vec)
	{
		x += _vec.x;
		y += _vec.y;
		z += _vec.z;
	}

	void Vector3::add(float _x, float _y, float _z)
	{
		x += _x;
		y += _y;
		z += _z;
	}

	void Vector3::add(float _num)
	{
		x += _num;
		y += _num;
		z += _num;
	}

	void Vector3::subtract(const Vector3& _vec)
	{
		x -= _vec.x;
		y -= _vec.y;
		z -= _vec.z;
	}

	void Vector3::multiplyByNumber(const float& _num)
	{
		x *= _num;
		y *= _num;
		z *= _num;
	}

	void Vector3::divideByNumber(const float& _num)
	{
		x /= _num;
		y /= _num;
		z /= _num;
	}

	void Vector3::normalize()
	{
		float length = Maths::fsqrt((x * x) + (y * y) + (z * z));
		if (!Maths::floatCompare(0.0f, length))
			return;

		float inv = 1.0f / length;
		x *= inv;
		y *= inv;
		z *= inv;
	}

	void Vector3::negate()
	{
		x = -x;
		y = -y;
		z = -z;
	}

	float Vector3::getLength() const
	{
		float length;

		length = Maths::fsqrt(x * x + y * y + z * z);

		return length;
	}

	float Vector3::length() const
	{
		return getLength();
	}

	float Vector3::dotProduct(const Vector3& vec) const
	{
		return (x * vec.x + y * vec.y + z * vec.z);
	}

	Vector3 Vector3::crossProduct(const Vector3& vec) const
	{
		Vector3 res;

		
		res.x = (y * vec.z) - (z * vec.y);
		res.y = (z * vec.x) - (x * vec.z);
		res.z = (x * vec.y) - (y * vec.x);

		return res;
	}

	Vector3 normalize(const Vector3& _vec)
	{
		float length = _vec.getLength();
		if (!Maths::floatCompare(0.0f, length))
			return Vector3(_vec);

		Vector3 result = _vec;

		float inv = 1.0f / length;
		result.x *= inv;
		result.y *= inv;
		result.z *= inv;

		return result;
	}

	Vector3& Vector3::operator+=(const Vector3& rhs)
	{
		add(rhs);
		return (*this);
	}

	Vector3& Vector3::operator-=(const Vector3& rhs)
	{
		subtract(rhs);
		return (*this);
	}

	Vector3& Vector3::operator*=(const float& rhs)
	{
		multiplyByNumber(rhs);
		return (*this);
	}

	Vector3& Vector3::operator/=(const float& rhs)
	{
		divideByNumber(rhs);
		return (*this);
	}

	const Vector3 Vector3::operator-()
	{
		Vector3 newVector(*this);
		newVector.negate();

		return (newVector);
	}

	bool Vector3::operator==(const Vector3& _vec)
	{
		return (!Maths::floatCompare(x, _vec.x) &&
			!Maths::floatCompare(y, _vec.y) &&
			!Maths::floatCompare(z, _vec.z));
	}

	bool Vector3::operator!=(const Vector3& _vec)
	{
		return (Maths::floatCompare(x, _vec.x) ||
			Maths::floatCompare(y, _vec.y) ||
			Maths::floatCompare(z, _vec.z));
	}

	const Vector3 operator+(const Vector3& lhs, const Vector3& rhs)
	{
		return Vector3(lhs.x + rhs.x,
			lhs.y + rhs.y,
			lhs.z + rhs.z);
	}

	const Vector3 operator-(const Vector3& lhs, const Vector3& rhs)
	{
		return Vector3(lhs.x - rhs.x,
			lhs.y - rhs.y,
			lhs.z - rhs.z);
	}

	const Vector3 operator/(const Vector3& lhs, const float& rhs)
	{
		Vector3 result = lhs;
		result.divideByNumber(rhs);

		return result;
	}

	const Vector3 operator*(const Vector3& lhs, const float& rhs)
	{
		Vector3 result = lhs;
		result.multiplyByNumber(rhs);

		return result;
	}

	const Vector3 operator*(const float& lhs, const Vector3& rhs)
	{
		Vector3 result = rhs;
		result.multiplyByNumber(lhs);

		return result;
	}

	const Vector3 operator*(const Vector3& lhs, const Vector3& rhs)
	{
		return (lhs.crossProduct(rhs));
	}

	bool operator==(const Vector3& _vec1, const Vector3& _vec2)
	{
		return (!Maths::floatCompare(_vec1.x, _vec2.x) &&
			!Maths::floatCompare(_vec1.y, _vec2.y) &&
			!Maths::floatCompare(_vec1.z, _vec2.z));
	}

	bool operator!=(const Vector3& _vec1, const Vector3& _vec2)
	{
		return (Maths::floatCompare(_vec1.x, _vec2.x) ||
			Maths::floatCompare(_vec1.y, _vec2.y) ||
			Maths::floatCompare(_vec1.z, _vec2.z));
	}

	float* Vector3::getData()
	{
		return &vals[0];
	}

	float Vector3::operator[](size_t i)
	{
		Assert(i < 3, "Vector dimension index not allowed");
		return (vals[i]);
	}

	float Vector3::operator[](size_t i) const
	{
		Assert(i < 3, "Vector dimension index not allowed");
		return (vals[i]);
	}
}