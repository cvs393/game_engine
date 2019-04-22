#pragma once
#include <iostream>
#include <string>

namespace math {
	
	class Matrix; 
	class Vector3; 

	class Quaternion
	{
		float Q[4];

	public: 
	
		/* CONSTRUCTOR AND SET UP JAZZ */
		Quaternion();
		
		Quaternion(const Vector3 & right, float w);
		Quaternion(const Vector3 right);
		Quaternion(const float* array);
		Quaternion(float x, float y, float z, float w);
		
		float x() const;
		float y() const;
		float z() const;
		float w() const;

		Matrix matrix() const;

		/* OPERATORS */
		Quaternion operator/(float s) const;
		Quaternion operator*(const Quaternion& right) const;
		Quaternion operator*(float s) const;
		Quaternion operator+(const Quaternion& right) const;
		Quaternion operator-(const Quaternion& right) const;
		Quaternion operator-() const;

		/* QUATERNION SPECIALS */
		Quaternion Product(const Quaternion& right) const;
		Quaternion Conjugate(void) const;
		Quaternion Inverse(void) const; 
		float Norm() const;
		Quaternion Normalize(const Quaternion& right) const;

		/*THE FUN STUFF -- ROTATIONS, EULER ANGLES, YUCK...*/
		//Vector3 RotatedVector(const Vector3& left) const;
		Quaternion EulerRotate(const Vector3& right);
		Vector3 Euler(void) const; //this is the meaty boi

		/*EXTRA CONVERSION STUFF (RETURNING POINTERS)*/
		float* row(int i);
		const float* row(int i) const;

		/*FOR PRINTING*/
		friend std::ostream& operator<<(std::ostream &strm, const Quaternion &q)
		{
			return strm << "[" << q.Q[0] << ", " << q.Q[1] <<
				", " << q.Q[2] << ", " << q.Q[3] << "]";
		}

		/*HOUSE KEEPING NOTES, SHOULD DELETE LATER*/
		//scaled axis....ripperoni
		//did not implement a rightMatrix for multiplication
		//norm returns a float, kinda like magnitude 
		//normalize returns a quaternion as a quaternion...
		//conjugate
		/*invert <- im not sure what this boi is supposed to do, 
		so i didn't implement this */
		//make rotation (with degree and axis)
	};
}