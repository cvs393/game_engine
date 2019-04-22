#include "Matrix.h"

namespace math
{
	math::Matrix::Matrix()
	{
		for (int i = 0; i < 15; i++) {
			matrix[i] = 0.0f;
		}
		matrix[15] = 1.0f;
	}

	math::Matrix::Matrix(float diagonal)
	{
		for (int i = 0; i < 15; i++)
		{
			matrix[i] = 0.0f;
		}
		matrix[0] = diagonal;
		matrix[5] = diagonal;
		matrix[10] = diagonal;
		matrix[15] = diagonal;
	}

	/* Matrix::Matrix(float matrix[])
	{
		matrix[0] = a;
		matrix[1] = b;
		matrix[2] = c;
		matrix[3] = d;
		matrix[4] = e;
		matrix[5] = f;
		matrix[6] = g;
		matrix[7] = h;
		matrix[8] = i;
		matrix[9] = j;
		matrix[10] = k;
		matrix[11] = l;
		matrix[12] = m;
		matrix[13] = n;
		matrix[14] = o;
		matrix[15] = 1.0f;
	}
	*/

	/*	 Vector3::Vector3(float x, float y, float z, float w)
		{
			//return Vector3{x, y, z, w};
		}
		*/

		//explicit constructor
	Matrix::Matrix(float a, float b, float c, float d,
		float e, float f, float g, float h,
		float i, float j, float k, float l,
		float m, float n, float o, float p) : matrix{ a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p }
	{
	}

	Matrix Matrix::operator+(Matrix const & right)
	{
		return Matrix(right.matrix[0] + matrix[0], right.matrix[1] + matrix[1], right.matrix[2] + matrix[2], right.matrix[3] + matrix[3],
			right.matrix[4] + matrix[4], right.matrix[5] + matrix[5], right.matrix[6] + matrix[6], right.matrix[7] + matrix[7],
			right.matrix[8] + matrix[8], right.matrix[9] + matrix[9], right.matrix[10] + matrix[10], right.matrix[11] + matrix[11],
			right.matrix[12] + matrix[12], right.matrix[13] + matrix[13], right.matrix[14] + matrix[14], right.matrix[15] + matrix[15]);
	}

	Matrix & Matrix::operator+=(Matrix const & right)
	{
		for (int i = 0; i < 16; i++)
		{
			matrix[i] += right.matrix[i];
		}
		return *this;
	}

	Matrix Matrix::operator-(Matrix const & right)
	{
		return Matrix(right.matrix[0] - matrix[0], right.matrix[1] - matrix[1], right.matrix[2] - matrix[2], right.matrix[3] - matrix[3],
			right.matrix[4] - matrix[4], right.matrix[5] - matrix[5], right.matrix[6] - matrix[6], right.matrix[7] - matrix[7],
			right.matrix[8] - matrix[8], right.matrix[9] - matrix[9], right.matrix[10] - matrix[10], right.matrix[11] - matrix[11],
			right.matrix[12] - matrix[12], right.matrix[13] - matrix[13], right.matrix[14] - matrix[14], right.matrix[15] - matrix[15]);
	}

	Matrix & Matrix::operator-=(Matrix const & right)
	{
		for (int i = 0; i < 16; i++)
		{
			matrix[i] -= right.matrix[i];
		}
		return *this;
	}

	Matrix Matrix::operator*(Matrix const & right)
	{
		// Matrix right x Matrix[16]
		return Matrix(right.matrix[0] * matrix[0], right.matrix[1] * matrix[1], right.matrix[2] * matrix[2], right.matrix[3] * matrix[3],
			right.matrix[4] * matrix[4], right.matrix[5] * matrix[5], right.matrix[6] * matrix[6], right.matrix[7] * matrix[7],
			right.matrix[8] * matrix[8], right.matrix[9] * matrix[9], right.matrix[10] * matrix[10], right.matrix[11] * matrix[11],
			right.matrix[12] * matrix[12], right.matrix[13] * matrix[13], right.matrix[14] * matrix[14], right.matrix[15] * matrix[15]);

	}

	Matrix & Matrix::operator*=(Matrix const & right)
	{
		for (int i = 0; i < 16; i++)
		{
			matrix[i] *= right.matrix[i];
		}
		return *this;
	}

	/*	Matrix is [4 x 4], Vector is [4 x 1]
		M x V = [4 x 1]
		Therefore this function returns a Vector
	*/
	Vector3 Matrix::operator*(Vector3 const & left)
	{
		return Vector3
		(
			matrix[0] * left.x + matrix[1] * left.y + matrix[2] * left.z + matrix[3] * left.w,
			matrix[4] * left.x + matrix[5] * left.y + matrix[6] * left.z + matrix[7] * left.w,
			matrix[8] * left.x + matrix[9] * left.y + matrix[10] * left.z + matrix[11] * left.w,
			matrix[12] * left.x + matrix[13] * left.y + matrix[14] * left.z + matrix[15] * left.w
		);
	}

	Matrix Matrix::MatrixTranspose()
	{
		Matrix matT;

		matT.matrix[0] = matrix[0];
		matT.matrix[1] = matrix[4];
		matT.matrix[2] = matrix[8];
		matT.matrix[3] = matrix[12];
		matT.matrix[4] = matrix[1];
		matT.matrix[5] = matrix[5];
		matT.matrix[6] = matrix[9];
		matT.matrix[7] = matrix[13];
		matT.matrix[8] = matrix[2];
		matT.matrix[9] = matrix[6];
		matT.matrix[10] = matrix[10];
		matT.matrix[11] = matrix[14];
		matT.matrix[13] = matrix[7];
		matT.matrix[14] = matrix[11];
		matT.matrix[15] = matrix[15];

		return matT;
	}


	Vector3 Matrix::MatrixTranslate(Vector3 const & right, Vector3 const & left)
	{
		//vector left is translation block = t, matrix right is the vector that is brought in...?
		//the vector here is the translation block...which is wrong
		Matrix TransMat =
			(1, 0, 0, left.x,
				0, 1, 0, left.y,
				0, 0, 1, left.z,
				0, 0, 0, left.w);

		Vector3 transVec = TransMat * right;
		return Vector3(transVec);
	} //this needs to return a vector...

	Vector3 Matrix::MatrixScale(Vector3 const & right, Vector3 const & left)
	{

		Matrix ScaleMat =
			(left.x, 0, 0, 0,
				0, left.y, 0, 0,
				0, 0, left.z, 0,
				0, 0, 0, 1.0f);
		Vector3 res_vec = ScaleMat * right;
		//operator
		return Vector3(res_vec);
	}


}