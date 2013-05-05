/**
 * 
 * 
**/
#ifndef __MATRIX_H
#define __MATRIX_H

#include "vector.h"

namespace platformer
{
	// datatype must be 32bit float
	typedef float matrix_t;
	
	class Matrix
	{
		// this class cannot be implemented as vector, without vector::data which is c++11
		private:
			matrix_t* m;
			
		public:
			Matrix();
			Matrix(const Matrix&);
			~Matrix();
			
			matrix_t* ptr();
			
			vec4 vright();		// right-vector
			vec4 vup();			// up-vector
			vec4 vforward();	// forward-vector
			vec4 vtranslate();	// translation-vector
			
			void identity();
			void bias();
			
			const matrix_t& operator[] (int) const;
			vec4 operator* (const vec4&);
			Matrix& operator* (const Matrix&);
			
			void scale(matrix_t scale);
			void scale(matrix_t x, matrix_t y, matrix_t z);
			
			void translate(matrix_t x, matrix_t y, matrix_t z);
			void translated(matrix_t x, matrix_t y, matrix_t z);
			void translate_xy(matrix_t x, matrix_t y);
			void translate_xz(matrix_t x, matrix_t z);
			
			void rotateZYX(matrix_t x, matrix_t y, matrix_t z);
			
			void transpose();
			void perspective(matrix_t fov, matrix_t aspect, matrix_t znear, matrix_t zfar);
		
	};
}

#endif
