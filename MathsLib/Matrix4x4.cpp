// This is an independent project of an individual developer. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com

#include "Matrix4x4.h"
#include "FuncSplit.h"

#include <emmintrin.h>
#include <xmmintrin.h>

#include <sstream>


namespace MathsLib
{
	// Initialize static members
	const Matrix4x4 Matrix4x4::IDENTITY(1.0f, 0.0f, 0.0f, 0.0f,
										0.0f, 1.0f, 0.0f, 0.0f,
										0.0f, 0.0f, 1.0f, 0.0f,
										0.0f, 0.0f, 0.0f, 1.0f);


	Matrix4x4::Matrix4x4()
	{
		identity();
	}

	Matrix4x4::Matrix4x4(float _m11, float _m12, float _m13, float _m14,
						 float _m21, float _m22, float _m23, float _m24,
						 float _m31, float _m32, float _m33, float _m34,
						 float _m41, float _m42, float _m43, float _m44)
	{
		set(_m11, _m12, _m13, _m14,
			_m21, _m22, _m23, _m24,
			_m31, _m32, _m33, _m34,
			_m41, _m42, _m43, _m44);
	}

	Matrix4x4::~Matrix4x4()
	{
	}

	void Matrix4x4::fromString(const std::string& _string)
	{
		std::vector <std::string> vecValues;
		FuncSplit <std::string> tokenizer;
		tokenizer(_string, vecValues, " ,;");

		if(vecValues.size() == 16)
		{
			auto iter = vecValues.begin();
			for(unsigned int i = 0; i < 16; ++i)
				m[i] = atof((iter++)->c_str());
		}
	}

	std::string Matrix4x4::toString()
	{
		std::stringstream buffer;
		for(unsigned int i = 0; i < 15; ++i)
			buffer << m[i] << " ";
		buffer << m[15];

		return buffer.str();
	}

	void Matrix4x4::transpose()
	{
		if(Maths::isUsingSSE())
		{
			__m128 row0 = _mm_loadu_ps((float*)&m[0]);
			__m128 row1 = _mm_loadu_ps((float*)&m[4]);
			__m128 row2 = _mm_loadu_ps((float*)&m[8]);
			__m128 row3 = _mm_loadu_ps((float*)&m[12]);

			_MM_TRANSPOSE4_PS(row0, row1, row2, row3);

			_mm_storeu_ps((float*)&m[0], row0);
			_mm_storeu_ps((float*)&m[4], row1);
			_mm_storeu_ps((float*)&m[8], row2);
			_mm_storeu_ps((float*)&m[12], row3);
		}
		else
		{
			Matrix4x4 mat = (*this);
			mat._m[0][0] = _m[0][0];
			mat._m[0][1] = _m[1][0];
			mat._m[0][2] = _m[2][0];
			mat._m[0][3] = _m[3][0];

			mat._m[1][0] = _m[0][1];
			mat._m[1][1] = _m[1][1];
			mat._m[1][2] = _m[2][1];
			mat._m[1][3] = _m[3][1];

			mat._m[2][0] = _m[0][2];
			mat._m[2][1] = _m[1][2];
			mat._m[2][2] = _m[2][2];
			mat._m[2][3] = _m[3][2];

			mat._m[3][0] = _m[0][3];
			mat._m[3][1] = _m[1][3];
			mat._m[3][2] = _m[2][3];
			mat._m[3][3] = _m[3][3];

			(*this) = mat;
		}
	}

	Vector4 Matrix4x4::multiply(const Vector4& _vec)
	{
		Vector4 vecResult;
		if(Maths::isUsingSSE())
		{
			float* pMat = &m[0];
			float* pDst = &vecResult.vals[0];

			__m128 vector = _mm_loadu_ps((float*)&_vec.vals[0]);

			__m128 v2v3 = _mm_shuffle_ps(vector, vector, 238);
			__m128 v0v1 = _mm_shuffle_ps(vector, vector, 68);

			__m128 _xmm2 = _mm_setzero_ps();
			_xmm2 = _mm_loadl_pi(_xmm2, (__m64*)pMat);
			_xmm2 = _mm_loadh_pi(_xmm2, (__m64*)(pMat + 4));
			_xmm2 = _mm_mul_ps(_xmm2, v0v1);

			__m128 _xmm3 = _mm_setzero_ps();
			_xmm3 = _mm_loadl_pi(_xmm3, (__m64*)(pMat + 2));
			_xmm3 = _mm_loadh_pi(_xmm3, (__m64*)(pMat + 6));
			_xmm3 = _mm_mul_ps(_xmm3, v2v3);

			__m128 _xmm4 = _mm_setzero_ps();
			_xmm4 = _mm_loadl_pi(_xmm4, (__m64*)(pMat + 8));
			_xmm4 = _mm_loadh_pi(_xmm4, (__m64*)(pMat + 12));
			v0v1 = _mm_mul_ps(_xmm4, v0v1);

			__m128 _xmm5 = _mm_setzero_ps();
			_xmm5 = _mm_loadl_pi(_xmm5, (__m64*)(pMat + 10));
			_xmm5 = _mm_loadh_pi(_xmm5, (__m64*)(pMat + 14));
			v2v3 = _mm_mul_ps(_xmm5, v2v3);

			_xmm2 = _mm_add_ps(_xmm2, _xmm3);
			_xmm3 = _xmm2;
			v0v1 = _mm_add_ps(v0v1, v2v3);

			_xmm2 = _mm_shuffle_ps(_xmm2, v0v1, 221);
			_xmm3 = _mm_shuffle_ps(_xmm3, v0v1, 136);

			_xmm3 = _mm_add_ps(_xmm3, _xmm2);
			_mm_storeu_ps(pDst, _xmm3);
		}
		else
		{
			vecResult.set(_m11 * _vec.x + _m12 * _vec.y + _m13 * _vec.z + _m14 * _vec.w,
						  _m21 * _vec.x + _m22 * _vec.y + _m23 * _vec.z + _m24 * _vec.w,
						  _m31 * _vec.x + _m32 * _vec.y + _m33 * _vec.z + _m34 * _vec.w,
						  _m41 * _vec.x + _m42 * _vec.y + _m43 * _vec.z + _m44 * _vec.w);
		}

		return vecResult;
	}
//---------------------------------------------------------------------
	void Matrix4x4::multiply(const float& _number)
	{
		if(Maths::isUsingSSE())
		{
			__m128 row0 = _mm_loadu_ps((float*)&m[0]);
			__m128 row1 = _mm_loadu_ps((float*)&m[4]);
			__m128 row2 = _mm_loadu_ps((float*)&m[8]);
			__m128 row3 = _mm_loadu_ps((float*)&m[12]);

			__m128 number = _mm_set_ps1(_number);

			row0 = _mm_mul_ps(row0, number);
			row1 = _mm_mul_ps(row1, number);
			row2 = _mm_mul_ps(row2, number);
			row3 = _mm_mul_ps(row3, number);

			_mm_storeu_ps((float*)&m[0], row0);
			_mm_storeu_ps((float*)&m[4], row1);
			_mm_storeu_ps((float*)&m[8], row2);
			_mm_storeu_ps((float*)&m[12], row3);
		}
		else
		{
			_m[0][0] *= _number; _m[0][1] *= _number; _m[0][2] *= _number; _m[0][3] *= _number;
			_m[1][0] *= _number; _m[1][1] *= _number; _m[1][2] *= _number; _m[1][3] *= _number;
			_m[2][0] *= _number; _m[2][1] *= _number; _m[2][2] *= _number; _m[2][3] *= _number;
			_m[3][0] *= _number; _m[3][1] *= _number; _m[3][2] *= _number; _m[3][3] *= _number;
		}
	}
//---------------------------------------------------------------------
	void Matrix4x4::divide(const float& _number)
	{
		float invNumber = 1.0f / _number;

		if(Maths::isUsingSSE())
		{
			__m128 row0 = _mm_loadu_ps((float*)&m[0]);
			__m128 row1 = _mm_loadu_ps((float*)&m[4]);
			__m128 row2 = _mm_loadu_ps((float*)&m[8]);
			__m128 row3 = _mm_loadu_ps((float*)&m[12]);

			__m128 number = _mm_set_ps1(invNumber);

			row0 = _mm_mul_ps(row0, number);
			row1 = _mm_mul_ps(row1, number);
			row2 = _mm_mul_ps(row2, number);
			row3 = _mm_mul_ps(row3, number);

			_mm_storeu_ps((float*)&m[0], row0);
			_mm_storeu_ps((float*)&m[4], row1);
			_mm_storeu_ps((float*)&m[8], row2);
			_mm_storeu_ps((float*)&m[12], row3);
		}
		else
		{
			_m11 *= invNumber; _m12 *= invNumber; _m13 *= invNumber; _m14 *= invNumber;
			_m21 *= invNumber; _m22 *= invNumber; _m23 *= invNumber; _m24 *= invNumber;
			_m31 *= invNumber; _m32 *= invNumber; _m33 *= invNumber; _m34 *= invNumber;
			_m41 *= invNumber; _m42 *= invNumber; _m43 *= invNumber; _m44 *= invNumber;
		}
	}
//---------------------------------------------------------------------
	void Matrix4x4::add(const Matrix4x4& _mat)
	{
		if(Maths::isUsingSSE())
		{
			__m128 row0m1 = _mm_loadu_ps(&m[0]);
			__m128 row0m2 = _mm_loadu_ps((float*)&_mat.m[0]);
			row0m1 = _mm_add_ps(row0m1, row0m2);
			_mm_storeu_ps((float*)&m[0], row0m1);

			row0m1 = _mm_loadu_ps(&m[4]);
			row0m2 = _mm_loadu_ps((float*)&_mat.m[4]);
			row0m1 = _mm_add_ps(row0m1, row0m2);
			_mm_storeu_ps((float*)&m[4], row0m1);

			row0m1 = _mm_loadu_ps(&m[8]);
			row0m2 = _mm_loadu_ps((float*)&_mat.m[8]);
			row0m1 = _mm_add_ps(row0m1, row0m2);
			_mm_storeu_ps((float*)&m[8], row0m1);

			row0m1 = _mm_loadu_ps(&m[12]);
			row0m2 = _mm_loadu_ps((float*)&_mat.m[12]);
			row0m1 = _mm_add_ps(row0m1, row0m2);
			_mm_storeu_ps((float*)&m[12], row0m1);
		}
		else
		{
			_m11 += _mat._m11; _m12 += _mat._m12; _m13 += _mat._m13; _m14 += _mat._m14;
			_m21 += _mat._m21; _m22 += _mat._m22; _m23 += _mat._m23; _m24 += _mat._m24;
			_m31 += _mat._m31; _m32 += _mat._m32; _m33 += _mat._m33; _m34 += _mat._m34;
			_m41 += _mat._m41; _m42 += _mat._m42; _m43 += _mat._m43; _m44 += _mat._m44;
		}
	}

	void Matrix4x4::set(float _m11, float _m12, float _m13, float _m14,
		float _m21, float _m22, float _m23, float _m24,
		float _m31, float _m32, float _m33, float _m34,
		float _m41, float _m42, float _m43, float _m44)
	{
		_m[0][0] = _m11; _m[0][1] = _m12; _m[0][2] = _m13; _m[0][3] = _m14;
		_m[1][0] = _m21; _m[1][1] = _m22; _m[1][2] = _m23; _m[1][3] = _m24;
		_m[2][0] = _m31; _m[2][1] = _m32; _m[2][2] = _m33; _m[2][3] = _m34;
		_m[3][0] = _m41; _m[3][1] = _m42; _m[3][2] = _m43; _m[3][3] = _m44;
	}

	void Matrix4x4::lookAt(const Vector3& _eyePos, const Vector3& _target, const Vector3& _up)
	{
		Vector3 z = normalize(_target - _eyePos);
		Vector3 x = normalize(_up.crossProduct(z));
		Vector3 y = z.crossProduct(x);

		_m11 = x.x;
		_m12 = y.x;
		_m13 = z.x;
		_m14 = 0.0f;

		_m21 = x.y;
		_m22 = y.y;
		_m23 = z.y;
		_m24 = 0.0f;

		_m31 = x.z;
		_m32 = y.z;
		_m33 = z.z;
		_m34 = 0.0f;

		_m41 = -x.dotProduct(_eyePos);
		_m42 = -y.dotProduct(_eyePos);
		_m43 = -z.dotProduct(_eyePos);
		_m44 = 1.0f;
	}

	void Matrix4x4::orthogonal(float _width, float _height, float _near, float _far)
	{
		identity();

		_m11 = 2.0f / _width;
		_m22 = 2.0f / _height;
		_m33 = 1.0f / (_far - _near);
		_m43 = _near / (_near - _far);
	}

	void Matrix4x4::perspective(float _fov, float _aspect, float _near, float _far)
	{
		if (!Maths::floatCompare(_far, _near))
		{
			return;
		}

		zero();

		float sinFov = Maths::fsin(_fov * 0.5f);
		float cosFov = Maths::fcos(_fov * 0.5f);

		float h = (cosFov / sinFov);
		float w = h / _aspect;
		float q = _far / (_far - _near);

		_m[0][0] = w;
		_m[1][1] = h;
		_m[2][2] = q;
		_m[2][3] = 1.0f;
		_m[3][2] = -q * _near;
	}

	void Matrix4x4::identity()
	{
		float* f = &(this->_m[0][0]);
		memset(f, 0, sizeof(Matrix4x4));
		_m[0][0] = _m[1][1] = _m[2][2] = _m[3][3] = 1.0f;
	}

	void Matrix4x4::zero()
	{
		float* f = &(this->_m[0][0]);
		memset(f, 0, sizeof(Matrix4x4));
	}

	void Matrix4x4::negate()
	{
		// Boring stuff... it is better however not to
		// use loop in this case as it will be slower
		_m[0][0] = -_m[0][0];
		_m[1][0] = -_m[1][0];
		_m[2][0] = -_m[2][0];
		_m[3][0] = -_m[3][0];
		_m[0][1] = -_m[0][1];
		_m[1][1] = -_m[1][1];
		_m[2][1] = -_m[2][1];
		_m[3][1] = -_m[3][1];
		_m[0][2] = -_m[0][2];
		_m[1][2] = -_m[1][2];
		_m[2][2] = -_m[2][2];
		_m[3][2] = -_m[3][2];
		_m[0][3] = -_m[0][3];
		_m[1][3] = -_m[1][3];
		_m[2][3] = -_m[2][3];
		_m[3][3] = -_m[3][3];
	}

	void Matrix4x4::invert()
	{
		float det = determinant();

		// If cannot be inverted, exit
		if (Maths::floatEquals(det, 0.0f))
			return;

		Matrix4x4 adjoin = adjoint();
		adjoin.transpose();

		(*this) = adjoin * (1.0f / det);
	}

	float Matrix4x4::determinant() const
	{
		// We use Laplace theorem to calculate determinant
		return (_m[0][0] * minor(1, 2, 3, 1, 2, 3) -
			_m[1][0] * minor(0, 2, 3, 1, 2, 3) +
			_m[2][0] * minor(0, 1, 3, 1, 2, 3) -
			_m[3][0] * minor(0, 1, 2, 1, 2, 3));
	}

	float Matrix4x4::minor(unsigned int r0, unsigned int r1, unsigned int r2,
		unsigned int c0, unsigned int c1, unsigned int c2) const
	{
		// We use Sarrus method here
		return (_m[r0][c0] * (_m[r1][c1] * _m[r2][c2] - _m[r2][c1] * _m[r1][c2]) +
			_m[r0][c1] * (_m[r1][c2] * _m[r2][c0] - _m[r1][c0] * _m[r2][c2]) +
			_m[r0][c2] * (_m[r1][c0] * _m[r2][c1] - _m[r1][c1] * _m[r2][c0]));
	}

	Matrix4x4 Matrix4x4::adjoint() const
	{
		return Matrix4x4(minor(1, 2, 3, 1, 2, 3),
			-minor(1, 2, 3, 0, 2, 3),
			minor(1, 2, 3, 0, 1, 3),
			-minor(1, 2, 3, 0, 1, 2),

			-minor(0, 2, 3, 1, 2, 3),
			minor(0, 2, 3, 0, 2, 3),
			-minor(0, 2, 3, 0, 1, 3),
			minor(0, 2, 3, 0, 1, 2),

			minor(0, 1, 3, 1, 2, 3),
			-minor(0, 1, 3, 0, 2, 3),
			minor(0, 1, 3, 0, 1, 3),
			-minor(0, 1, 3, 0, 1, 2),

			-minor(0, 1, 2, 1, 2, 3),
			minor(0, 1, 2, 0, 2, 3),
			-minor(0, 1, 2, 0, 1, 3),
			minor(0, 1, 2, 0, 1, 2));
	}

	Matrix4x4 add(const Matrix4x4& _mat1, const Matrix4x4& _mat2)
	{
		Matrix4x4 result = _mat1;
		result.add(_mat2);

		return result;
	}

	void Matrix4x4::subtract(const Matrix4x4& _mat)
	{
		_m11 -= _mat._m11; _m12 -= _mat._m12; _m13 -= _mat._m13; _m14 -= _mat._m14;
		_m21 -= _mat._m21; _m22 -= _mat._m22; _m23 -= _mat._m23; _m24 -= _mat._m24;
		_m31 -= _mat._m31; _m32 -= _mat._m32; _m33 -= _mat._m33; _m34 -= _mat._m34;
		_m41 -= _mat._m41; _m42 -= _mat._m42; _m43 -= _mat._m43; _m44 -= _mat._m44;
	}

	Matrix4x4 subtract(const Matrix4x4& _mat1, const Matrix4x4& _mat2)
	{
		Matrix4x4 result = _mat1;
		result.subtract(_mat2);

		return result;
	}

	void Matrix4x4::multiply(const Matrix4x4& _matrix)
	{
		Matrix4x4 mat;
		if (Maths::isUsingSSE())
		{
		}
		else
		{
		}

		mat[0][0] = _m[0][0] * _matrix[0][0] + _m[0][1] * _matrix[1][0] +
			_m[0][2] * _matrix[2][0] + _m[0][3] * _matrix[3][0];
		mat[0][1] = _m[0][0] * _matrix[0][1] + _m[0][1] * _matrix[1][1] +
			_m[0][2] * _matrix[2][1] + _m[0][3] * _matrix[3][1];
		mat[0][2] = _m[0][0] * _matrix[0][2] + _m[0][1] * _matrix[1][2] +
			_m[0][2] * _matrix[2][2] + _m[0][3] * _matrix[3][2];
		mat[0][3] = _m[0][0] * _matrix[0][3] + _m[0][1] * _matrix[1][3] +
			_m[0][2] * _matrix[2][3] + _m[0][3] * _matrix[3][3];

		mat[1][0] = _m[1][0] * _matrix[0][0] + _m[1][1] * _matrix[1][0] +
			_m[1][2] * _matrix[2][0] + _m[1][3] * _matrix[3][0];
		mat[1][1] = _m[1][0] * _matrix[0][1] + _m[1][1] * _matrix[1][1] +
			_m[1][2] * _matrix[2][1] + _m[1][3] * _matrix[3][1];
		mat[1][2] = _m[1][0] * _matrix[0][2] + _m[1][1] * _matrix[1][2] +
			_m[1][2] * _matrix[2][2] + _m[1][3] * _matrix[3][2];
		mat[1][3] = _m[1][0] * _matrix[0][3] + _m[1][1] * _matrix[1][3] +
			_m[1][2] * _matrix[2][3] + _m[1][3] * _matrix[3][3];

		mat[2][0] = _m[2][0] * _matrix[0][0] + _m[2][1] * _matrix[1][0] +
			_m[2][2] * _matrix[2][0] + _m[2][3] * _matrix[3][0];
		mat[2][1] = _m[2][0] * _matrix[0][1] + _m[2][1] * _matrix[1][1] +
			_m[2][2] * _matrix[2][1] + _m[2][3] * _matrix[3][1];
		mat[2][2] = _m[2][0] * _matrix[0][2] + _m[2][1] * _matrix[1][2] +
			_m[2][2] * _matrix[2][2] + _m[2][3] * _matrix[3][2];
		mat[2][3] = _m[2][0] * _matrix[0][3] + _m[2][1] * _matrix[1][3] +
			_m[2][2] * _matrix[2][3] + _m[2][3] * _matrix[3][3];

		mat[3][0] = _m[3][0] * _matrix[0][0] + _m[3][1] * _matrix[1][0] +
			_m[3][2] * _matrix[2][0] + _m[3][3] * _matrix[3][0];
		mat[3][1] = _m[3][0] * _matrix[0][1] + _m[3][1] * _matrix[1][1] +
			_m[3][2] * _matrix[2][1] + _m[3][3] * _matrix[3][1];
		mat[3][2] = _m[3][0] * _matrix[0][2] + _m[3][1] * _matrix[1][2] +
			_m[3][2] * _matrix[2][2] + _m[3][3] * _matrix[3][2];
		mat[3][3] = _m[3][0] * _matrix[0][3] + _m[3][1] * _matrix[1][3] +
			_m[3][2] * _matrix[2][3] + _m[3][3] * _matrix[3][3];

		(*this) = mat;
	}
	//---------------------------------------------------------------------
	Matrix4x4 multiply(const Matrix4x4& _mat1, const Matrix4x4& _mat2)
	{
		Matrix4x4 temp = _mat1;
		temp.multiply(_mat2);

		return (temp);
	}
	//---------------------------------------------------------------------
	void Matrix4x4::translate(const Vector3& _translate)
	{
		identity();
		_m[3][0] = _translate.x;
		_m[3][1] = _translate.y;
		_m[3][2] = _translate.z;
	}

	void Matrix4x4::translate(float _x, float _y, float _z)
	{
		identity();
		_m[3][0] = _x;
		_m[3][1] = _y;
		_m[3][2] = _z;
	}

	void Matrix4x4::setTranslation(const Vector3& _translate)
	{
		_m41 = _translate.x;
		_m42 = _translate.y;
		_m43 = _translate.z;
	}

	void Matrix4x4::setTranslation(float _x, float _y, float _z)
	{
		_m41 = _x;
		_m42 = _y;
		_m43 = _z;
	}

	Vector3 Matrix4x4::getTranslation() const
	{
		return Vector3(_m41, _m42, _m43);
	}

	void Matrix4x4::rotateAroundXAxis(float _angle)
	{
		identity();
		float cs = Maths::fcos(_angle);
		float sn = Maths::fsin(_angle);

		_m[1][1] = cs;
		_m[1][2] = sn;
		_m[2][1] = -sn;
		_m[2][2] = cs;
	}

	void Matrix4x4::rotateAroundYAxis(float _angle)
	{
		identity();
		float cs = Maths::fcos(_angle);
		float sn = Maths::fsin(_angle);

		_m[0][0] = cs;
		_m[0][2] = -sn;
		_m[2][0] = sn;
		_m[2][2] = cs;
	}

	void Matrix4x4::rotateAroundZAxis(float _angle)
	{
		identity();
		float cs = Maths::fcos(_angle);
		float sn = Maths::fsin(_angle);

		_m[0][0] = cs;
		_m[0][1] = sn;
		_m[1][0] = -sn;
		_m[1][1] = cs;
	}

	void Matrix4x4::rotate(const Vector3& _axis, float _angle)
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

	void Matrix4x4::rotateYawPitchRoll(const Vector3& _euler)
	{
		float sy = Maths::fsin(_euler.z), cy = Maths::fcos(_euler.z);
		float sp = Maths::fsin(_euler.x), cp = Maths::fcos(_euler.x);
		float sr = Maths::fsin(_euler.y), cr = Maths::fcos(_euler.y);

		_m11 = cy * cr + sy * sp * sr;  _m12 = sr * cp; _m13 = -sy * cr + cy * sp * sr; _m14 = 0.0f;
		_m21 = -cy * sr + sy * sp * cr; _m22 = cr * cp; _m23 = sr * sy + cy * sp * cr;  _m24 = 0.0f;
		_m31 = sy * cp;             _m32 = -sp;   _m33 = cy * cp;             _m34 = 0.0f;
		_m41 = 0.0f;              _m42 = 0.0f;  _m43 = 0.0f;              _m44 = 1.0f;
	}

	void Matrix4x4::rotateYawPitchRoll(float _yaw, float _pitch, float _roll)
	{
		float sy = Maths::fsin(_yaw), cy = Maths::fcos(_yaw);
		float sp = Maths::fsin(_pitch), cp = Maths::fcos(_pitch);
		float sr = Maths::fsin(_roll), cr = Maths::fcos(_roll);

		_m11 = cy * cr + sy * sp * sr;  _m12 = sr * cp; _m13 = -sy * cr + cy * sp * sr; _m14 = 0.0f;
		_m21 = -cy * sr + sy * sp * cr; _m22 = cr * cp; _m23 = sr * sy + cy * sp * cr;  _m24 = 0.0f;
		_m31 = sy * cp;             _m32 = -sp;   _m33 = cy * cp;             _m34 = 0.0f;
		_m41 = 0.0f;              _m42 = 0.0f;  _m43 = 0.0f;              _m44 = 1.0f;
	}

	void Matrix4x4::scale(const Vector3& _scale)
	{
		identity();
		_m11 = _scale.x;
		_m22 = _scale.y;
		_m33 = _scale.z;
	}

	void Matrix4x4::scale(float _x, float _y, float _z)
	{
		identity();
		_m11 = _x;
		_m22 = _y;
		_m33 = _z;
	}

	void Matrix4x4::scale(float _s)
	{
		identity();
		_m11 = _s;
		_m22 = _s;
		_m33 = _s;
	}

	bool Matrix4x4::isIdentity()
	{
		return ((*this) == Matrix4x4(1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f));
	}

	bool Matrix4x4::isZero()
	{
		return ((*this) == Matrix4x4(0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 0.0f));
	}

	const Matrix4x4 Matrix4x4::operator-()
	{
		Matrix4x4 newMatrix(*this);
		newMatrix.negate();

		return newMatrix;
	}

	const Matrix4x4 operator+(const Matrix4x4& lhs, const Matrix4x4& rhs)
	{
		Matrix4x4 result = lhs;
		result.add(rhs);

		return result;
	}

	const Matrix4x4 operator-(const Matrix4x4& lhs, const Matrix4x4& rhs)
	{
		Matrix4x4 result = lhs;
		result.subtract(rhs);

		return result;
	}

	const Matrix4x4 operator*(const Matrix4x4& lhs, const float& rhs)
	{
		Matrix4x4 result = lhs;
		result.multiply(rhs);

		return result;
	}

	const Matrix4x4 operator*(const float& lhs, const Matrix4x4& rhs)
	{
		Matrix4x4 result = rhs;
		result.multiply(lhs);

		return result;
	}

	const Matrix4x4 operator*(const Matrix4x4& lhs, const Matrix4x4& rhs)
	{
		Matrix4x4 result = lhs;
		result.multiply(rhs);

		return result;
	}

	const Vector4 operator*(const Matrix4x4& lhs, const Vector4& rhs)
	{
		Matrix4x4 mat = lhs;

		return mat.multiply(rhs);
	}

	const Vector4 operator*(const Vector4& lhs, const Matrix4x4& rhs)
	{
		Vector4 vec = lhs;
		vec.multiply(rhs);

		return vec;
	}

	float* Matrix4x4::operator[](unsigned int i)
	{
		Assert(i < 4, "Matrix row index not allowed");
		return (_m[i]);
	}

	const float* const Matrix4x4::operator[](unsigned int i) const
	{
		Assert(i < 4, "Matrix row index not allowed");
		return (_m[i]);
	}

	Matrix4x4& Matrix4x4::operator*=(const Matrix4x4& rhs)
	{
		multiply(rhs);
		return (*this);
	}

	Vector4 Matrix4x4::operator*=(const Vector4& rhs)
	{
		return multiply(rhs);
	}

	Matrix4x4& Matrix4x4::operator*=(const float& rhs)
	{
		multiply(rhs);
		return (*this);
	}

	Matrix4x4& Matrix4x4::operator+=(const Matrix4x4& rhs)
	{
		add(rhs);
		return (*this);
	}

	Matrix4x4& Matrix4x4::operator-=(const Matrix4x4& rhs)
	{
		subtract(rhs);
		return (*this);
	}

	bool Matrix4x4::operator==(const Matrix4x4& _mat)
	{
		for (int i = 0; i < 16; ++i)
			if (!Maths::floatEquals(this->m[i], _mat.m[i])) return false;

		return true;
	}

	float* Matrix4x4::getData()
	{
		return (&_m[0][0]);
	}

}