#pragma once
//VERY IMPORTANT! #pragma once  GOES AT THE TOP OF EVERY .h/.hpp FILE!
//it is a header guard, and will keep many strange compiler errors at bay 

#include <iostream>
#include <string>

//Example Vector3 class for reference

namespace math {

	class Matrix;
	class ResourceManager;

	class Vector3
	{
		//all variables & functions following this will be public
		//private works the same way 
	public:

		//default values, otherwise the value is undefined (ie whatever the memory had beforehand}
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
		float w = 0.0f; //this is a vector, if this value is 1 its a point

		/* CONSTRUCTION */

		//default constructor (ctor)
		Vector3();

		//ctor with arguments
		explicit Vector3(float x, float y, float z, float w);

		/* OPERATOR OVERLOADING */

		//operator overloading enables very convenient access in user code.
		//Ex: vecA = vecB + vecC; compare to a java: vecA = vecB.Add(vecC);

		Vector3 operator-(); //unary minus

		Vector3 operator+(Vector3 const & right); //binary addition
		Vector3& operator+=(Vector3 const & right); //addition assignment

		Vector3 operator-(Vector3 const & right); //binary negation
		Vector3& operator-=(Vector3 const & right); //negation assignment

		/* SCALING OPERATIONS */
		/*	this section is multiplication and division at the same time, 
			since division is just creating a new ratio of the same numbers, 
			they can all be represented by fractions [i.e. 6|2 = 3 is 6 * 1/2 = 3]
		*/
		Vector3 operator*(float s); 
		Vector3& operator*=(float s);

		/* BREAKING FUNDAMENTAL RULES OF VECTOR MATH */

		Vector3 operator/(Vector3 const & right);
		Vector3& operator/=(Vector3 const & right);

		/* EQUALITY COMPARISON */

		bool operator==(Vector3 const& right);
		bool operator!=(Vector3 const& right);

		/* COMMON OPERATIONS */

		//gets the magnitude
		float Magnitude() const;

		//mutates the class
		void Normalize();

		//returns a Vector3 that is the normal, but doesn't change the original one
		Vector3 Normal() const;

		// member functions
		float Dot(Vector3 const& right);
		Vector3 Cross(Vector3 const& right);

		//extra fun stuff
		float Lerp(Vector3& left, float val);
		Vector3 Projection(Vector3& left, Vector3& right);
		Vector3 Perpendicular(Vector3& left, Vector3& right);

		/* UTILITY FUNCTIONS */

		//return address of first element. useful for uploading to GPU
		float* data_ptr();

		//this is what a idiomatic to_string looks like.
		friend std::ostream& operator<<(std::ostream &strm, const Vector3 &v) 
		{
			return strm << "[" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << "]";
		}

		std::string to_string() {
			return std::string("[") + 
				std::to_string(x) + "," + 
				std::to_string(y) + "," + 
				std::to_string(z) + "," + 
				std::to_string(w) + "]";
		}

	//As Vector3 hides nothing, nothing needs to be private
	private:

	};

	//free standing functions

	float Dot(Vector3& left, Vector3& right);
	Vector3 Cross(Vector3& left, Vector3& right);

	Vector3 Lerp(Vector3& left, float val);
	Vector3 Projection(Vector3& left, Vector3& right);
	Vector3 Perpendicular(Vector3& left, Vector3& right);


	//assuming right handed Y-up axis
	static const Vector3 VECTOR3_UP{ 0.0f, 1.0f, 0.0f, 0.0f };
	static const Vector3 VECTOR3_DOWN{ 0.0f, -1.0f, 0.0f, 0.0f };
	static const Vector3 VECTOR3_RIGHT{ 1.0f, 0.0f, 0.0f, 0.0f };
	static const Vector3 VECTOR3_LEFT{ -1.0f, 1.0f, 0.0f, 0.0f };
	static const Vector3 VECTOR3_FORWARD{ 0.0f, 0.0f, 1.0f, 0.0f };
	static const Vector3 VECTOR3_BACKWARD{ 0.0f, 0.0f, -1.0f, 0.0f };

}