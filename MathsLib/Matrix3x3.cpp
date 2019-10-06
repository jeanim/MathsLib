// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "Matrix3x3.h"
#include "FuncSplit.h"

#include <sstream>


namespace MathsLib
{
	// Initialize static members
	const Matrix3x3 Matrix3x3::IDENTITY(1.0f, 0.0f, 0.0f,
										0.0f, 1.0f, 0.0f,
										0.0f, 0.0f, 1.0f);


	Matrix3x3::Matrix3x3()
	{
		identity();
	}

	Matrix3x3::Matrix3x3(float _m11, float _m12, float _m13,
						 float _m21, float _m22, float _m23,
						 float _m31, float _m32, float _m33)
	{
		set(_m11, _m12, _m13,
			_m21, _m22, _m23,
			_m31, _m32, _m33);
	}

	Matrix3x3::~Matrix3x3()
	{
	}

	void Matrix3x3::fromString(const std::string& _string)
	{
		std::vector <std::string> vecValues;
		FuncSplit <std::string> tokenizer;
		tokenizer(_string, vecValues, " ,;");

		if(vecValues.size() == 9)
		{
			auto iter = vecValues.begin();
			for(unsigned int i = 0; i < 9; ++i)
				m[i] = atof((iter++)->c_str());
		}
	}

	std::string Matrix3x3::toString()
	{
		std::stringstream buffer;
		for (unsigned int i = 0; i < 9; ++i) {
			buffer << m[i];
			if (i < 8) buffer << " ";
		}

		return buffer.str();
	}

	void Matrix3x3::set(float _m11, float _m12, float _m13,
		float _m21, float _m22, float _m23,
		float _m31, float _m32, float _m33)
	{
		_m[0][0] = _m11; _m[0][1] = _m12; _m[0][2] = _m13;
		_m[1][0] = _m21; _m[1][1] = _m22; _m[1][2] = _m23;
		_m[2][0] = _m31; _m[2][1] = _m32; _m[2][2] = _m33;
	}

	void Matrix3x3::identity()
	{
		float* f = &(this->_m[0][0]);
		memset(f, 0, sizeof(Matrix3x3));
		_m[0][0] = _m[1][1] = _m[2][2] = 1.0f;
	}

	void Matrix3x3::zero()
	{
		float* f = &(this->_m[0][0]);
		memset(f, 0, sizeof(Matrix3x3));
	}

	void Matrix3x3::negate()
	{
		// Boring stuff... it is better however not to
		// use loop in this case as it will be slower
		_m[0][0] = -_m[0][0];
		_m[1][0] = -_m[1][0];
		_m[2][0] = -_m[2][0];

		_m[0][1] = -_m[0][1];
		_m[1][1] = -_m[1][1];
		_m[2][1] = -_m[2][1];

		_m[0][2] = -_m[0][2];
		_m[1][2] = -_m[1][2];
		_m[2][2] = -_m[2][2];
	}

	void Matrix3x3::invert()
	{
		float det = determinant();

		// If cannot be inverted, exit
		if (Maths::floatEquals(det, 0.0f))
			return;

		Matrix3x3 adjoin = adjoint();
		adjoin.transpose();

		(*this) = adjoin * (1.0f / det);
	}

	float Matrix3x3::determinant() const
	{
		return (_m11 * (_m22 * _m33 - _m23 * _m32) +
			_m12 * (_m23 * _m31 - _m21 * _m33) +
			_m13 * (_m21 * _m32 - _m22 * _m31));
	}

	float Matrix3x3::minor(unsigned int r0, unsigned int r1, unsigned int c0, unsigned int c1) const
	{
		// We use Sarrus method here
		return (_m[r0][c0] * _m[r1][c1] - _m[r0][c1] * _m[r1][c0]);
	}

	Matrix3x3 Matrix3x3::adjoint() const
	{
		return Matrix3x3(minor(1, 2, 1, 2),
			-minor(1, 2, 0, 2),
			minor(1, 2, 0, 1),

			-minor(0, 2, 1, 2),
			minor(0, 2, 0, 2),
			-minor(0, 2, 0, 1),

			minor(0, 1, 1, 2),
			-minor(0, 1, 0, 2),
			minor(0, 1, 0, 1));
	}

	void Matrix3x3::transpose()
	{
		Matrix3x3 mat = (*this);
		mat._m[0][0] = _m[0][0];
		mat._m[0][1] = _m[1][0];
		mat._m[0][2] = _m[2][0];

		mat._m[1][0] = _m[0][1];
		mat._m[1][1] = _m[1][1];
		mat._m[1][2] = _m[2][1];

		mat._m[2][0] = _m[0][2];
		mat._m[2][1] = _m[1][2];
		mat._m[2][2] = _m[2][2];

		(*this) = mat;
	}

	void Matrix3x3::add(const Matrix3x3& _mat)
	{
		_m11 += _mat._m11; _m12 += _mat._m12; _m13 += _mat._m13;
		_m21 += _mat._m21; _m22 += _mat._m22; _m23 += _mat._m23;
		_m31 += _mat._m31; _m32 += _mat._m32; _m33 += _mat._m33;
	}

	Matrix3x3 add(const Matrix3x3& _mat1, const Matrix3x3& _mat2)
	{
		Matrix3x3 result = _mat1;
		result.add(_mat2);

		return result;
	}

	void Matrix3x3::subtract(const Matrix3x3& _mat)
	{
		_m11 -= _mat._m11; _m12 -= _mat._m12; _m13 -= _mat._m13;
		_m21 -= _mat._m21; _m22 -= _mat._m22; _m23 -= _mat._m23;
		_m31 -= _mat._m31; _m32 -= _mat._m32; _m33 -= _mat._m33;
	}

	Matrix3x3 subtract(const Matrix3x3& _mat1, const Matrix3x3& _mat2)
	{
		Matrix3x3 result = _mat1;
		result.subtract(_mat2);

		return result;
	}

	void Matrix3x3::multiply(const Matrix3x3& _matrix)
	{
		Matrix3x3 mat;

		mat[0][0] = _m[0][0] * _matrix[0][0] + _m[0][1] * _matrix[1][0] +
			_m[0][2] * _matrix[2][0];
		mat[0][1] = _m[0][0] * _matrix[0][1] + _m[0][1] * _matrix[1][1] +
			_m[0][2] * _matrix[2][1];
		mat[0][2] = _m[0][0] * _matrix[0][2] + _m[0][1] * _matrix[1][2] +
			_m[0][2] * _matrix[2][2];

		mat[1][0] = _m[1][0] * _matrix[0][0] + _m[1][1] * _matrix[1][0] +
			_m[1][2] * _matrix[2][0];
		mat[1][1] = _m[1][0] * _matrix[0][1] + _m[1][1] * _matrix[1][1] +
			_m[1][2] * _matrix[2][1];
		mat[1][2] = _m[1][0] * _matrix[0][2] + _m[1][1] * _matrix[1][2] +
			_m[1][2] * _matrix[2][2];

		mat[2][0] = _m[2][0] * _matrix[0][0] + _m[2][1] * _matrix[1][0] +
			_m[2][2] * _matrix[2][0];
		mat[2][1] = _m[2][0] * _matrix[0][1] + _m[2][1] * _matrix[1][1] +
			_m[2][2] * _matrix[2][1];
		mat[2][2] = _m[2][0] * _matrix[0][2] + _m[2][1] * _matrix[1][2] +
			_m[2][2] * _matrix[2][2];

		(*this) = mat;
	}
	//---------------------------------------------------------------------
	void Matrix3x3::multiply(const float& _number)
	{
		_m11 *= _number; _m12 *= _number; _m13 *= _number;
		_m21 *= _number; _m22 *= _number; _m23 *= _number;
		_m31 *= _number; _m32 *= _number; _m33 *= _number;
	}
	//---------------------------------------------------------------------
	Vector3 Matrix3x3::multiply(const Vector3& _vec)
	{
		Vector3 vecResult;

		vecResult.set(_m11 * _vec.x + _m12 * _vec.y + _m13 * _vec.z,
			_m21 * _vec.x + _m22 * _vec.y + _m23 * _vec.z,
			_m31 * _vec.x + _m32 * _vec.y + _m33 * _vec.z);

		return vecResult;
	}
	//---------------------------------------------------------------------
	Matrix3x3 multiply(const Matrix3x3& _mat1, const Matrix3x3& _mat2)
	{
		Matrix3x3 temp = _mat1;
		temp.multiply(_mat2);
		return (temp);
	}
	//---------------------------------------------------------------------
	void Matrix3x3::divide(const float& _number)
	{
		_m11 /= _number; _m12 /= _number; _m13 /= _number;
		_m21 /= _number; _m22 /= _number; _m23 /= _number;
		_m31 /= _number; _m32 /= _number; _m33 /= _number;
	}

	void Matrix3x3::rotateAroundXAxis(float _angle)
	{
		identity();
		float cs = Maths::fcos(_angle);
		float sn = Maths::fsin(_angle);

		_m[1][1] = cs;
		_m[1][2] = sn;
		_m[2][1] = -sn;
		_m[2][2] = cs;
	}

	void Matrix3x3::rotateAroundYAxis(float _angle)
	{
		identity();
		float cs = Maths::fcos(_angle);
		float sn = Maths::fsin(_angle);

		_m[0][0] = cs;
		_m[0][2] = -sn;
		_m[2][0] = sn;
		_m[2][2] = cs;
	}

	void Matrix3x3::rotateAroundZAxis(float _angle)
	{
		identity();
		float cs = Maths::fcos(_angle);
		float sn = Maths::fsin(_angle);

		_m[0][0] = cs;
		_m[0][1] = sn;
		_m[1][0] = -sn;
		_m[1][1] = cs;
	}

	void Matrix3x3::rotate(const Vector3& _axis, float _angle)
	{
		identity();
		float fCos = Maths::fcos(_angle);
		float fSin = Maths::fsin(_angle);
		float fSum = 1.0f - fCos;

		_m[0][0] = (_axis.x * _axis.x) * fSum + fCos;
		_m[0][1] = (_axis.x * _axis.y) * fSum - _axis.z * fSin;
		_m[0][2] = (_axis.x * _axis.z) * fSum + _axis.y * fSin;

		_m[1][0] = (_axis.y * _axis.x) * fSum + _axis.z * fSin;
		_m[1][1] = (_axis.y * _axis.y) * fSum + fCos;
		_m[1][2] = (_axis.y * _axis.z) * fSum - _axis.x * fSin;

		_m[2][0] = (_axis.z * _axis.x) * fSum - _axis.y * fSin;
		_m[2][1] = (_axis.z * _axis.y) * fSum + _axis.x * fSin;
		_m[2][2] = (_axis.z * _axis.z) * fSum + fCos;
	}

	void Matrix3x3::rotateYawPitchRoll(const Vector3& _euler)
	{
		float sy = Maths::fsin(_euler.z), cy = Maths::fcos(_euler.z);
		float sp = Maths::fsin(_euler.x), cp = Maths::fcos(_euler.x);
		float sr = Maths::fsin(_euler.y), cr = Maths::fcos(_euler.y);

		_m11 = cy * cr + sy * sp * sr;  _m12 = sr * cp; _m13 = -sy * cr + cy * sp * sr;
		_m21 = -cy * sr + sy * sp * cr; _m22 = cr * cp; _m23 = sr * sy + cy * sp * cr;
		_m31 = sy * cp;             _m32 = -sp;   _m33 = cy * cp;
	}

	void Matrix3x3::rotateYawPitchRoll(float _yaw, float _pitch, float _roll)
	{
		float sy = Maths::fsin(_yaw), cy = Maths::fcos(_yaw);
		float sp = Maths::fsin(_pitch), cp = Maths::fcos(_pitch);
		float sr = Maths::fsin(_roll), cr = Maths::fcos(_roll);

		_m11 = cy * cr + sy * sp * sr;  _m12 = sr * cp; _m13 = -sy * cr + cy * sp * sr;
		_m21 = -cy * sr + sy * sp * cr; _m22 = cr * cp; _m23 = sr * sy + cy * sp * cr;
		_m31 = sy * cp;             _m32 = -sp;   _m33 = cy * cp;
	}

	void Matrix3x3::scale(const Vector3& _scale)
	{
		identity();
		_m11 = _scale.x;
		_m22 = _scale.y;
		_m33 = _scale.z;
	}

	void Matrix3x3::scale(float _x, float _y, float _z)
	{
		identity();
		_m11 = _x;
		_m22 = _y;
		_m33 = _z;
	}

	void Matrix3x3::scale(float _s)
	{
		identity();
		_m11 = _s;
		_m22 = _s;
		_m33 = _s;
	}

	bool Matrix3x3::isIdentity()
	{
		return ((*this) == Matrix3x3(1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f));
	}

	bool Matrix3x3::isZero()
	{
		return ((*this) == Matrix3x3(0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f));
	}

	const Matrix3x3 Matrix3x3::operator-()
	{
		Matrix3x3 newMatrix(*this);
		newMatrix.negate();

		return newMatrix;
	}

	const Matrix3x3 operator+(const Matrix3x3& lhs, const Matrix3x3& rhs)
	{
		Matrix3x3 result = lhs;
		result.add(rhs);

		return result;
	}

	const Matrix3x3 operator-(const Matrix3x3& lhs, const Matrix3x3& rhs)
	{
		Matrix3x3 result = lhs;
		result.subtract(rhs);

		return result;
	}

	const Matrix3x3 operator*(const Matrix3x3& lhs, const float& rhs)
	{
		Matrix3x3 result = lhs;
		result.multiply(rhs);

		return result;
	}

	const Matrix3x3 operator*(const float& lhs, const Matrix3x3& rhs)
	{
		Matrix3x3 result = rhs;
		result.multiply(lhs);

		return result;
	}

	const Matrix3x3 operator*(const Matrix3x3& lhs, const Matrix3x3& rhs)
	{
		Matrix3x3 result = lhs;
		result.multiply(rhs);

		return result;
	}

	const Vector3 operator*(const Matrix3x3& lhs, const Vector3& rhs)
	{
		Matrix3x3 mat = lhs;

		return mat.multiply(rhs);
	}

	const Vector3 operator*(const Vector3& lhs, const Matrix3x3& rhs)
	{
		Vector3 vec = lhs;
		vec.multiply(rhs);

		return vec;
	}

	float* Matrix3x3::operator[](unsigned int i)
	{
		Assert(i < 3, "Matrix row index not allowed");
		return (_m[i]);
	}

	const float* const Matrix3x3::operator[](unsigned int i) const
	{
		Assert(i < 3, "Matrix row index not allowed");
		return (_m[i]);
	}

	Matrix3x3& Matrix3x3::operator*=(const Matrix3x3& rhs)
	{
		multiply(rhs);
		return (*this);
	}

	Vector3 Matrix3x3::operator*=(const Vector3& rhs)
	{
		return multiply(rhs);
	}

	Matrix3x3& Matrix3x3::operator*=(const float& rhs)
	{
		multiply(rhs);
		return (*this);
	}

	Matrix3x3& Matrix3x3::operator+=(const Matrix3x3& rhs)
	{
		add(rhs);
		return (*this);
	}

	Matrix3x3& Matrix3x3::operator-=(const Matrix3x3& rhs)
	{
		subtract(rhs);
		return (*this);
	}

	bool Matrix3x3::operator==(const Matrix3x3& _mat)
	{
		for (int i = 0; i < 9; ++i)
			if (!Maths::floatEquals(this->m[i], _mat.m[i])) return false;

		return true;
	}

	float* Matrix3x3::getData()
	{
		return (&_m[0][0]);
	}

}