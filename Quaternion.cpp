#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Vector3.h"
#include "Matrix.h"
#include "Quaternion.h"

namespace math
{
	Quaternion::Quaternion()
	{
		Q[0] = Q[1] = Q[2] = 0;
		Q[3] = 1;

	}

	Quaternion::Quaternion(const Vector3 & right, float w)
	{
		Q[0] = right.x;
		Q[1] = right.y;
		Q[2] = right.z;
		Q[3] = w;

	}

	Quaternion::Quaternion(const Vector3 right)
	{
		Q[0] = right.x;
		Q[1] = right.y;
		Q[2] = right.z;
		Q[3] = right.w;

	}

	Quaternion::Quaternion(const float* array)
	{
		if (array)
		{
			for (int i = 0; i < 4; i++)
			{
				Q[i] = array[i];
			}
		}
		
	}

	Quaternion::Quaternion(float x, float y, float z, float w)
	{
		Q[0] = x; 
		Q[1] = y;
		Q[2] = z;
		Q[3] = w;
	}

	//this makes for easier notation later on in the code
	float Quaternion::x() const
	{
		return Q[0];
	}
	float Quaternion::y() const
	{
		return Q[1];
	}
	float Quaternion::z() const
	{
		return Q[2];
	}
	float Quaternion::w() const
	{
		return Q[3]; 
	}
	
	/*
		Conjugate is faster than inverse when Norm() == 1;
		AKA an absolute Unit Quaternion (lol look at me im funny)
	*/
	Quaternion Quaternion::Conjugate(void) const
	{
		return Quaternion(-Q[0], -Q[1], -Q[2], Q[3]); 
		//First three values are the complex, the last one is real
	}

	//this is basically magnitude
	float Quaternion::Norm() const
	{
		return sqrt(Q[0] * Q[0] + Q[1] * Q[1] +
			Q[2] * Q[2] + Q[3] * Q[3]);
	}

	Quaternion Quaternion::Normalize(const Quaternion & right) const
	{
		return Quaternion
		(
			Q[0] / Norm(), Q[1] / Norm(), 
			Q[2] / Norm(), Q[3] / Q[3]
		); //makes sure that the last element is always 1 
	}

	/*Vector3 Quaternion::RotatedVector(const Vector3 & left) const
	{	
		Quaternion vector = -((*this) * Quaternion(left)) * Conjugate();
		Vector3 vectorUGH = (vector.x, vector.y, vector.z, vector.w);

		return Vector3(vectorUGH);
	}*/

	Quaternion Quaternion::Inverse(void) const
	{
		Quaternion inverse = (Conjugate() / Norm());
		return (inverse);
	}

	Quaternion Quaternion::Product(const Quaternion& right) const
	{
		return Quaternion
		(
			y()*right.z() - z()*right.y() + x()*right.w() + w()*right.x(),
			z()*right.x() - x()*right.z() + y()*right.w() + w()*right.y(),
			x()*right.y() - y()*right.x() + z()*right.w() + w()*right.z(),
			w()*right.w() - x()*right.x() - y()*right.y() - z()*right.z()
		);
	}

	Quaternion Quaternion::operator/(float s) const
	{
		if (s == 0) 
			std::clog << "Ya boi is trying to achieve infinity lol (divide by 0)." << std::endl;
		return Quaternion(-Q[0] / s, -Q[1] /s , -Q[2] / s, Q[3] / s);
	}

	Quaternion Quaternion::operator*(const Quaternion & right) const
	{
		return Product(right);
	}

	Quaternion Quaternion::operator*(float s) const
	{
		return Quaternion(-Q[0] * s, -Q[1] * s, -Q[2] * s, Q[3] * s);
	}

	Quaternion Quaternion::operator+(const Quaternion & right) const
	{
		return Quaternion
		(
			x() + right.x(), y() + right.y(), 
			z() + right.z(), w() + right.w()
		);
	}

	Quaternion Quaternion::operator-(const Quaternion & right) const
	{
		return Quaternion
		(
			x() - right.x(), y() - right.y(), 
			z() - right.z(), w() - right.w()
		);
	}

	/*	
		Standard negative operator, also negatifies? the w component
		thats the only difference between this boi and the conjugate
	*/
	Quaternion Quaternion::operator-() const
	{
		return Quaternion(-x(), -y(), -z(), -w());
	}

	//this isn't the rotational matrix but basically a cast 
	//for a quaternion to become a matrix
	//this->matrix() * q.vector() = (*this) * q for any quaternion q.
	Matrix Quaternion::matrix() const
	{
		float matrix[16] = {
		 w(), -z(),  y(), x(),
		 z(),  w(), -x(), y(),
		-y(),  x(),  w(), z(),
		-x(), -y(), -z(), w()
		};

		return Matrix
		(
			matrix[0], matrix[1], matrix[2], matrix[3],
			matrix[4], matrix[5], matrix[6], matrix[7],
			matrix[9], matrix[9], matrix[10], matrix[11],
			matrix[12], matrix[13], matrix[14], matrix[15]
		);
	}

	//roll, pitch, yaw (in that order)
	Quaternion Quaternion::EulerRotate(const Vector3& right) 
	{
		float c1 = cos(right.z * 0.5);
		float c2 = cos(right.y * 0.5);
		float c3 = cos(right.x * 0.5);
		float s1 = sin(right.z * 0.5);
		float s2 = sin(right.y * 0.5);
		float s3 = sin(right.x * 0.5);

		Q[0] = c1 * c2*s3 - s1 * s2*c3;
		Q[1] = c1 * s2*c3 + s1 * c2*s3;
		Q[2] = s1 * c2*c3 - c1 * s2*s3;
		Q[3] = c1 * c2*c3 + s1 * s2*s3;

		return (Q);
	}

	Vector3 Quaternion::Euler(void) const
	{
		Vector3 euler;
		const static float pi = atan(1) * 4;
		const static float pi_halved = pi * 0.5; //(pi/2)
		//	const static double EPSILON = 1e-10;
		const static float EPSILON = 0.001f;
		float squareX, squareY, squareZ, squareW;

		squareX = Q[3] * Q[3];
		squareY = Q[0] * Q[0];
		squareZ = Q[1] * Q[1];
		squareW = Q[2] * Q[2];

		euler.y = asin(2.0 * (Q[3] * Q[1] - Q[0] * Q[2]));

		if (pi_halved - fabs(euler.y) > EPSILON) 
		{
			euler.z = atan2(2.0 * (Q[0] * Q[1] + Q[3] * Q[2]),
				squareX - squareY - squareZ + squareW);

			euler.x = atan2(2.0 * (Q[3] * Q[0] + Q[1] * Q[2]),
				squareW - squareX - squareY + squareZ);
		}
		else {
			//compute heading from local 'down' vector
			euler.y = atan2(2 * Q[1] * Q[2] - 2 * Q[0] * Q[3],
				2 * Q[0] * Q[2] + 2 * Q[1] * Q[3]);
			euler.x = 0.0;

			//if facing down, do the reverse yaw
			if (euler.y < 0)
				euler.z = pi - euler.z;
		}
		return euler;
	}

	/*
		Returns pointer to the internal array.
		Array is in order x,y,z,w.
	*/
	float * Quaternion::row(int i)
	{
		return Q + i;
	}

	//const version of the same thingy
	const float * Quaternion::row(int i) const
	{
		return Q + i;
	}



}