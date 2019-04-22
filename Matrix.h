#pragma once
#include "Vector3.h"

// do addition and multiplications
// rotations and scaling
//COLUMN MAJOR MATH, where (0, 0, 0, 0) == (4x1)
/* Visually speaking, this is how a some matrices looks like: 

 | a |     
 | b |     
 | c |  *  | e f g h | = some (4 x 4) matrix  
 | d |           (1 x 4)             
	(4 x 1)
*/
namespace math
{
	class Matrix
	{
	public: 

		float matrix[16] =
		{
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1
		};

		Matrix();
		Matrix(float diagonal); //identity matrix();
		
		//explicit Matrix(float matrix[]); 
		// ^it used to be this, but its not working atm so we changing things up
		explicit Matrix
		(	float a, float b, float c, float d, 
			float e, float f, float g, float h, 
			float i, float j, float k, float l, 
			float m, float n, float o, float p);

		Matrix operator+(Matrix const & right);
		Matrix& operator+=(Matrix const & right);

		Matrix operator-(Matrix const & right);
		Matrix& operator-=(Matrix const & right);

		Matrix operator*(Matrix const & right);
		Matrix& operator*=(Matrix const & right);

		Vector3 operator*(Vector3 const & left);
//		Vector3 operator*(Vector3 const & right);

	//	Vector3 operator*(Vector3 const & right);

	//	Vector3 & operator*=(Vector3 const & right);

	//	we really don't have time to do this boi right now
	/*	
		Matrix operator^(Matrix const & right); //THIS IS SIMD MATH LOL DON't F it up BOI
		Matrix operator^=(Matrix const & right);
	*/

		//Matrix operator*(Vector3 const & right) const; //vector multiplication
		//Matrix& operator*=(Vector3 const & right); //ah i forgot about this lol

		Matrix MatrixTranspose();
		//Vector3 MatrixTranslate(Vector3 const & right, Vector3 const & left);
		Vector3 MatrixTranslate(Vector3 const & right, Vector3 const & left);
		Vector3 MatrixScale(Vector3 const & right, Vector3 const & left);
		
		Matrix MatrixRotateX();
		Matrix MatrixRotateY();
		Matrix MatrixRotateZ();
		Matrix MatrixRotate();
	//	Vector3 MatrixScale(Matrix const &right, Vector3 const &left);

		/* UTILITY FUNCTIONS FOR PRINTING */

		friend std::ostream& operator<<(std::ostream &strm, const Matrix &m) {
			return strm << "[" << m.matrix[0] << ", " << m.matrix[1] << ", " << m.matrix[2] << ", " << m.matrix[3] <<
				", " << m.matrix[4] << ", " << m.matrix[5] << ", " << m.matrix[6] << ", " << m.matrix[7] <<
				", " << m.matrix[8] << ", " << m.matrix[9] << ", " << m.matrix[10] << ", " << m.matrix[11] <<
				", " << m.matrix[12] << ", " << m.matrix[13] << ", " << m.matrix[14] << ", " << m.matrix[15] << "]";
		}

		/*std::string to_string() {
			return std::string("[") + std::to_string(a) + "," + std::to_string(b) + "," + std::to_string(c) + "," + std::to_string(b) + "\n" +
				"," + std::to_string(e) + "," + std::to_string(f) + "," + std::to_string(g) + "," + std::to_string(h) + "\n" +
				"," + std::to_string(i) + "," + std::to_string(j) + "," + std::to_string(k) + "," + std::to_string(l) + "\n" +
				"," + std::to_string(m) + "," + std::to_string(n) + "," + std::to_string(o) + "," + std::to_string(p) + "]";
		}*/
	private: 
	};
	
} //end namespace math