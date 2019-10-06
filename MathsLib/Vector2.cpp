// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "Vector2.h"
#include "FuncSplit.h"

#include <sstream>


namespace MathsLib
{
	// Static members initialization
	const Vector2 Vector2::UNIT_X(1.0f, 0.0f);
	const Vector2 Vector2::UNIT_Y(0.0f, 1.0f);
	const Vector2 Vector2::NEGATIVE_UNIT_X(-1.0f, 0.0f);
	const Vector2 Vector2::NEGATIVE_UNIT_Y(0.0f, -1.0f);

	const Vector2 Vector2::ZERO_VECTOR(0.0f, 0.0f);
	const Vector2 Vector2::ONE_VECTOR(1.0f, 1.0f);

	const Vector2 Vector2::INFINITY_VECTOR(1e9, 1e9);
	const Vector2 Vector2::NEGATIVE_INFINITY_VECTOR(-1e9, -1e9);



	Vector2::Vector2(float _x, float _y):
		x(_x),
		y(_y)
	{
	}

	Vector2::~Vector2()
	{
	}

	void Vector2::fromString(const std::string& _string)
	{
		std::vector <std::string> vecValues;
		FuncSplit <std::string> tokenizer;
		tokenizer(_string, vecValues, " ,;");

		if(vecValues.size() == 2)
		{
			auto iter = vecValues.begin();
			x = atof((iter++)->c_str());
			y = atof((iter++)->c_str());
		}
	}

	std::string Vector2::toString()
	{
		std::stringstream buffer;
		buffer << x << " " << y;

		return buffer.str();
	}

	void Vector2::set(float _x, float _y)
	{
		x = _x;
		y = _y;
	}

	void Vector2::set(const Vector2& _vec)
	{
		x = _vec.x;
		y = _vec.y;
	}

	void Vector2::add(const Vector2& _vec)
	{
		x += _vec.x;
		y += _vec.y;
	}

	void Vector2::add(float _x, float _y)
	{
		x += _x;
		y += _y;
	}

	void Vector2::add(float _num)
	{
		x += _num;
		y += _num;
	}

	void Vector2::subtract(const Vector2& _vec)
	{
		x -= _vec.x;
		y -= _vec.y;
	}

	void Vector2::multiplyByNumber(const float& _num)
	{
		x *= _num;
		y *= _num;
	}

	void Vector2::normalize()
	{
		float length = Maths::fsqrt(x * x + y * y);
		if (Maths::floatCompare(0.0f, length))
		{
			float inv = 1.0f / length;
			x *= inv;
			y *= inv;
		}
	}

	void Vector2::negate()
	{
		x = -x;
		y = -y;
	}

	float Vector2::getLength() const
	{
		return (Maths::fsqrt(x * x + y * y));
	}

	float Vector2::length() const
	{
		return (Maths::fsqrt(x * x + y * y));
	}

	float Vector2::dotProduct(const Vector2& vec) const
	{
		return (x * vec.x + y * vec.y);
	}

	Vector2 normalize(const Vector2& _vec)
	{
		Vector2 result = _vec;

		float length = result.getLength();
		if (Maths::floatCompare(0.0f, length))
		{
			float inv = 1.0f / length;
			result.x *= inv;
			result.y *= inv;
		}

		return result;
	}

	Vector2& Vector2::operator+=(const Vector2& rhs)
	{
		add(rhs);
		return (*this);
	}

	Vector2& Vector2::operator-=(const Vector2& rhs)
	{
		subtract(rhs);
		return (*this);
	}

	Vector2& Vector2::operator*=(const float& rhs)
	{
		multiplyByNumber(rhs);
		return (*this);
	}

	const Vector2 operator+(const Vector2& lhs, const Vector2& rhs)
	{
		return Vector2(lhs.x + rhs.x, lhs.y + rhs.y);
	}

	const Vector2 operator-(const Vector2& lhs, const Vector2& rhs)
	{
		return Vector2(lhs.x - rhs.x,
			lhs.y - rhs.y);
	}

	const Vector2 operator*(const Vector2& lhs, const float& rhs)
	{
		Vector2 result = lhs;
		result.multiplyByNumber(rhs);

		return result;
	}

	const Vector2 operator*(const float& lhs, const Vector2& rhs)
	{
		Vector2 result = rhs;
		result.multiplyByNumber(lhs);

		return result;
	}

	const Vector2 Vector2::operator-()
	{
		Vector2 newVector(*this);
		newVector.negate();

		return (newVector);
	}

	float Vector2::operator[](size_t i)
	{
		Assert(i < 2, "Vector dimension index not allowed");
		return (vals[i]);
	}

	float Vector2::operator[](size_t i) const
	{
		Assert(i < 2, "Vector dimension index not allowed");
		return (vals[i]);
	}

	float* Vector2::getData()
	{
		return &vals[0];
	}

	bool Vector2::operator==(const Vector2& _vec)
	{
		return (!Maths::floatCompare(x, _vec.x) &&
			!Maths::floatCompare(y, _vec.y));
	}

	bool Vector2::operator!=(const Vector2& _vec)
	{
		return (Maths::floatCompare(x, _vec.x) ||
			Maths::floatCompare(y, _vec.y));
	}

	bool operator==(const Vector2& _vec1, const Vector2& _vec2)
	{
		return (!Maths::floatCompare(_vec1.x, _vec2.x) &&
			!Maths::floatCompare(_vec1.y, _vec2.y));
	}

	bool operator!=(const Vector2& _vec1, const Vector2& _vec2)
	{
		return (Maths::floatCompare(_vec1.x, _vec2.x) ||
			Maths::floatCompare(_vec1.y, _vec2.y));
	}

}