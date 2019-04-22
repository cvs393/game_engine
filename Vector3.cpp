#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Vector3.h"

//VECTOR IS 0, POINT IS 1 
//FUNCTIONS THAT DON"T WORK: DOT, CROSS, MAYBE LERP, Haven't tested the rest. 

namespace math
{

	Vector3::Vector3() : x(0), y(0), z(0), w(0)
	{
	}

	Vector3::Vector3(float x, float y, float z, float w) : x(x), y(y), z(z), w(w)
	{

	}

	/* OPERATOR OVERLOADING */

	Vector3 Vector3::operator-() 
	{ 
		return Vector3(-x, -y, -z, w); 
	}

	Vector3 Vector3::operator+(Vector3 const &right) 
	{ 
		return Vector3(right.x + x, right.y + y, right.z + z, w); 
	}
	Vector3 &Vector3::operator+=(Vector3 const &right)
	{
		x += right.x;
		y += right.y;
		z += right.z;
		return *this; //returns a reference, *this returns the reference to itself
	}

	Vector3 Vector3::operator-(Vector3 const &right) 
	{
		return Vector3(x - right.x , y - right.y,z -  right.z,w); 
	}

	Vector3 &Vector3::operator-=(Vector3 const &right)
	{
		x -= right.x;
		y -= right.y;
		z -= right.z;
		return *this;
	}

	Vector3 Vector3::operator*( float s)
	{
		
		return Vector3(x * s, y * s, z* s, w);
	}

	Vector3 &Vector3::operator*=(float s)
	{
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}
	

	Vector3 Vector3::operator/(Vector3 const &right) 
	{ 
		if(right.x, right.y, right.z != 0)
		{
			return Vector3(right.x / x, right.y / y, right.z / z, w);
		}
		else return Vector3(0, 0, 0, 0);
	}

	Vector3 &Vector3::operator/=(Vector3 const &right)
	{
		x /= right.x;
		y /= right.y;
		z /= right.z;
		return *this;
	}

	/* EQUALITY COMPARISON */

	bool Vector3::operator==(Vector3 const &right)
	{
		return x == right.x && y == right.y && z == right.z;
	}

	bool Vector3::operator!=(Vector3 const &right)
	{
		return !(*this == right); // no need to rewrite
	}
	
	/* COMMON OPERATIONS */

	//functions that
	float Vector3::Magnitude() const
	{
		float mag = sqrt(x * this->x + y * this->y + z * this->z);
		return mag;
	}
	
	//mutates the class
	void Vector3::Normalize() 
	{
		
		float mag = Magnitude();
	
		Vector3 newVec = {};
		if (mag != 0.0)
		{
			newVec.x = x / mag;
			newVec.y = y / mag;
			newVec.z = z / mag;
			newVec.w = w;
		}
		
		*this = newVec;
	}

	//returns a Vector3 that is the normal, but doesn't change the original one
	Vector3 Vector3::Normal() const 
	{
		float mag = Magnitude();

		if (mag == 0.0)
		{
			throw("You need like a non-zero thing");
		}
		float normX = x / mag;
		float normY = y / mag;
		float normZ = z / mag;

		return Vector3{normX, normY, normZ, w};
	}

	//SPECIAL VECTOR FUNCTIONS

	float Vector3::Dot(Vector3 const &right) 
	{
		//this destroys the original value of a vector

		float new_x = x * right.x;
		float new_y = y * right.y;
		float new_z = z * right.z;
		
		if (new_x + new_y + new_z != 0)
		{ 
			return new_x + new_y + new_z;
		}
		else
		{
			return -1;
		}
	}

	Vector3 Vector3::Cross(Vector3 const &right) 
	{ 
		/*	A x B == -(B x A)
			where:
			A = <x, y, z, 0>, 
			B = <right.x, right.y, right.z, 0>
		*/
		float newX = (y * right.z) - (z * right.y);
		float newY = (z * right.x) - (x * right.z);
		float newZ = (x * right.y) - (y * right.x);
		w = 0.0f; 

		return Vector3{newX, newY,newZ, w}; 
	}

	float Vector3::Lerp(Vector3 &left, float val) 
	{ 
	    float L; 
	    L = (1 - val)*left.x + val * 
	    	this->x*(1 - val)*left.y + val * 
	    	this->y*(1 - val)*left.z + val*(this->z);
	    return L;
	}

	//the project of Vector LEFT onto RIGHT: Left's shadow onto Right's line
	//normalizing a vector makes it a unit vector convienently so go from there 
	Vector3 Vector3::Projection(Vector3 &left, Vector3 &right) 
	{
		left.Normal();
		float scalarProj = left.Dot(right);

		x *= scalarProj;
		y *= scalarProj;
		z *= scalarProj;

		return Vector3{x, y, z, w}; 
	}

	//this needs to be a matrix operation instead
	/*Vector3 Vector3::operator*(Vector3 const &right)
	{
	if (right.x != 0 && right.y != 0 && right.z != 0)
	{
		return Vector3(right.x * x, right.y * y, right.z * z, w);
	}
	else return Vector3(0, 0, 0, 0);
	//also this is not really a real thing....? in math...? same with divide lol
	//wait, this can be matrix multiplication. cause...fuck uhggghghghgghhuirehgreihg
	}*/

	/* UTILITY FUNCTIONS */

	//return address of first element. useful for uploading to GPU
	float *Vector3::data_ptr() { return &x; }

} // namespace math