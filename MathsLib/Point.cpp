// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "Point.h"
#include "FuncSplit.h"

#include <sstream>


namespace MathsLib
{
	// Statics initialization
	const Point Point::ZERO_POINT(0.0f, 0.0f, 0.0f);


	Point::Point()
	{
		(*this)=ZERO_POINT;
	}

	Point::Point(float _x, float _y, float _z):
		x(_x),
		y(_y),
		z(_z)
	{
	}

	Point::Point(const MathsLib::Vector3& _point):
		x(_point.x),
		y(_point.y),
		z(_point.z)
	{
	}

	Point::~Point()
	{
	}

	std::string Point::toString()
	{
		std::stringstream buffer;
		buffer << x << " " << y << " " << z;

		return buffer.str();
	}

	void Point::fromString(const std::string& _string)
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

	void Point::set(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	void Point::set(const Vector3& _point)
	{
		x = _point.x;
		y = _point.y;
		z = _point.z;
	}

	float Point::distanceToPoint(const Point& _a)
	{
		float dx = x - _a.x;
		float dy = y - _a.y;
		float dz = z - _a.z;

		return (Maths::fsqrt(dx * dx + dy * dy + dz * dz));
	}

	float distanceBetweenPoints(const Point& _a, const Point& _b)
	{
		Point temp = _a;
		return temp.distanceToPoint(_b);
	}

	void Point::translate(float _x, float _y, float _z)
	{
		x += _x;
		y += _y;
		z += _z;
	}

	void Point::translate(const Vector3& _vec)
	{
		x += _vec.x;
		y += _vec.y;
		z += _vec.z;
	}

	Point& Point::operator+=(const Vector3& rhs)
	{
		translate(rhs);
		return (*this);
	}

	const Vector3 operator-(const Point& lhs, const Point& rhs)
	{
		return Vector3(lhs.x - rhs.x,
			lhs.y - rhs.y,
			lhs.z - rhs.z);
	}

	bool Point::operator==(const Point& _a)
	{
		return (!Maths::floatCompare(x, _a.x) &&
			!Maths::floatCompare(y, _a.y) &&
			!Maths::floatCompare(z, _a.z));
	}

	bool Point::operator!=(const Point& _a)
	{
		return (Maths::floatCompare(x, _a.x) ||
			Maths::floatCompare(y, _a.y) ||
			Maths::floatCompare(z, _a.z));
	}

	bool operator==(const Point& _a, const Point& _b)
	{
		return (!Maths::floatCompare(_a.x, _b.x) &&
			!Maths::floatCompare(_a.y, _b.y) &&
			!Maths::floatCompare(_a.z, _b.z));
	}

	bool operator!=(const Point& _a, const Point& _b)
	{
		return (Maths::floatCompare(_a.x, _b.x) ||
			Maths::floatCompare(_a.y, _b.y) ||
			Maths::floatCompare(_a.z, _b.z));
	}

	Point::operator Vector3() const
	{
		return (Vector3(x, y, z));
	}

	float Point::operator[](size_t i)
	{
		Assert(i < 3, "Point dimension index not allowed");
		return (point[i]);
	}

	float Point::operator[](size_t i) const
	{
		Assert(i < 3, "Point dimension index not allowed");
		return (point[i]);
	}

}