// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "Plane.h"
#include "FuncSplit.h"
#include "Matrix4x4.h"

#include <sstream>


namespace MathsLib
{
	// Initialize static members
	const Plane Plane::UNIT_X(1.0f, 0.0f, 0.0f, 0.0f);
	const Plane Plane::UNIT_Y(0.0f, 1.0f, 0.0f, 0.0f);
	const Plane Plane::UNIT_Z(0.0f, 0.0f, 1.0f, 0.0f);

	const Plane Plane::NEGATIVE_UNIT_X(-1.0f, 0.0f, 0.0f, 0.0f);
	const Plane Plane::NEGATIVE_UNIT_Y(0.0f, -1.0f, 0.0f, 0.0f);
	const Plane Plane::NEGATIVE_UNIT_Z(0.0f, 0.0f, -1.0f, 0.0f);


	Plane::Plane() : D(0.0f)
	{
	}

	Plane::Plane(float _a, float _b, float _c, float _d):
		m_vecNormal(_a, _b, _c),
		D(_d)
	{
		calculatePoint(m_vecNormal, D);
	}

	Plane::Plane(const Vector3& _normal, float _d):
		m_vecNormal(_normal),
		D(_d)
	{
		calculatePoint(_normal, _d);
	}

	Plane::Plane(const Vector3& _normal, const Point& _pt):
		m_vecNormal(_normal),
		m_ptPoint(_pt)
	{
		D = - _normal.x * _pt.x - _normal.y * _pt.y - _normal.z * _pt.z;
	}

	Plane::Plane(const Vector3& _vec1, const Vector3& _vec2, const Point& _pt)
	{
		setPlane(_vec1.crossProduct(_vec2), _pt);
	}

	Plane::Plane(const Vector3& _vec1, const Vector3& _vec2, const Vector3& _vec3)
	{
		Vector3 vec12 = _vec2 - _vec1;
		Vector3 vec13 = _vec3 - _vec1;

		Vector3 normal = vec12.crossProduct(vec13);
		Point A(_vec1);

		setPlane(normal, A);
	}

	Plane::~Plane()
	{
	}

	void Plane::calculatePoint(const Vector3& _normal, float _d)
	{
		float sum = _normal.dotProduct(_normal);
		float factor = -_d / sum;

		m_ptPoint.set(_normal.x * factor,
					  _normal.y * factor,
					  _normal.z * factor);
	}

	void Plane::setPlane(const Vector3& _normal, float _d)
	{
		m_vecNormal = _normal;
		D = _d;
		calculatePoint(_normal, _d);
	}

	void Plane::setPlane(const Vector3& _normal, const Point& _pt)
	{
		m_vecNormal = _normal;
		m_ptPoint = _pt;
		D = - _normal.x * _pt.x - _normal.y * _pt.y - _normal.z * _pt.z;
	}

	void Plane::setPlane(float _a, float _b, float _c, float _d)
	{
		m_vecNormal.set(_a, _b, _c);
		D = _d;
		calculatePoint(m_vecNormal, D);
	}

	void Plane::setPlane(const Vector3& _vec1, const Vector3& _vec2, const Vector3& _vec3)
	{
		Vector3 vec12 = _vec2 - _vec1;
		Vector3 vec13 = _vec3 - _vec1;

		Vector3 normal = vec12.crossProduct(vec13);
		Point A(_vec1);

		setPlane(normal, A);
	}

	void Plane::transform(const Matrix4x4& _transform)
	{
		float a, b, c, d;

		a = m_vecNormal.x * _transform._m11 + m_vecNormal.y * _transform._m21 + m_vecNormal.z * _transform._m31 + D * _transform._m41;
		b = m_vecNormal.x * _transform._m12 + m_vecNormal.y * _transform._m22 + m_vecNormal.z * _transform._m32 + D * _transform._m42;
		c = m_vecNormal.x * _transform._m13 + m_vecNormal.y * _transform._m23 + m_vecNormal.z * _transform._m33 + D * _transform._m43;
		d = m_vecNormal.x * _transform._m14 + m_vecNormal.y * _transform._m24 + m_vecNormal.z * _transform._m34 + D * _transform._m44;

		m_vecNormal.set(a, b, c);
		D = d;
		calculatePoint(m_vecNormal, D);
	}

	float Plane::getDistanceFromPlane(const Vector3& _vec) const
	{
		return (m_vecNormal.dotProduct(_vec) + D) / m_vecNormal.getLength();
	}

	void Plane::fromString(const std::string& _string)
	{
		std::vector <std::string> vecValues;
		FuncSplit <std::string> tokenizer;
		tokenizer(_string, vecValues, " ,;");

		if(vecValues.size() == 4)
		{
			auto iter = vecValues.begin();
			m_vecNormal.x = atof((iter++)->c_str());
			m_vecNormal.y = atof((iter++)->c_str());
			m_vecNormal.z = atof((iter++)->c_str());
			D = atof((iter++)->c_str());
		}

		setPlane(m_vecNormal, D);
	}

	std::string Plane::toString()
	{
		std::stringstream buffer;
		buffer << m_vecNormal.toString() << " " << D;

		return buffer.str();
	}

	const Vector3& Plane::getPlaneNormal() const
	{
		return m_vecNormal;
	}

	float Plane::getPlaneD() const
	{
		return D;
	}

	const Point& Plane::getPlanePoint() const
	{
		return m_ptPoint;
	}

}