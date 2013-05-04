/**
 * 
 * 
**/
#include "matrix.h"
#include <cmath>

namespace platformer
{
	
	Matrix::Matrix()
	{
		this->m = new matrix_t[4 * 4];
		identity();
	}
	Matrix::Matrix(const Matrix& matrix)
	{
		this->m = new matrix_t[4 * 4];
		for (int i = 0; i < 16; i++)
			m[i] = matrix[i];
		
	}
	Matrix::~Matrix()
	{
		if (this->m) delete m;
	}
	
	matrix_t* Matrix::ptr()
	{
		return this->m;
	}
	
	void Matrix::identity()
	{
		m[0] = 1.0; m[4] = 0.0; m[ 8] = 0.0; m[12] = 0.0;
		m[1] = 0.0; m[5] = 1.0; m[ 9] = 0.0; m[13] = 0.0;
		m[2] = 0.0; m[6] = 0.0; m[10] = 1.0; m[14] = 0.0;
		m[3] = 0.0; m[7] = 0.0; m[11] = 0.0; m[15] = 1.0;
	}
	
	void Matrix::bias()
	{
		m[0] = 0.5; m[4] = 0.0; m[8 ] = 0.0; m[12] = 0.5;
		m[1] = 0.0; m[5] = 0.5; m[9 ] = 0.0; m[13] = 0.5;
		m[2] = 0.0; m[6] = 0.0; m[10] = 0.5; m[14] = 0.5;
		m[3] = 0.0; m[7] = 0.0; m[11] = 0.0; m[15] = 1.0;
	}
	
	vec4 Matrix::vright()
	{
		return vec4(m[0], m[1], m[2], m[3]);
	}
	vec4 Matrix::vup()
	{
		return vec4(m[4], m[5], m[6], m[7]);
	}
	vec4 Matrix::vforward()
	{
		return vec4(m[8], m[9], m[10], m[11]);
	}
	vec4 Matrix::vtranslate()
	{
		return vec4(m[12], m[13], m[14], m[15]);
	}
	
	const matrix_t& Matrix::operator[] (int i) const
	{
		return m[i];
	}
	
	// transform vector
	vec4 Matrix::operator* (const vec4& v)
	{
		return vec4(
			v.x * (m[ 0] + m[ 1] + m[ 2] + m[ 3]),
			v.y * (m[ 4] + m[ 5] + m[ 6] + m[ 7]),
			v.z * (m[ 8] + m[ 9] + m[10] + m[11]),
			v.w * (m[12] + m[13] + m[14] + m[15])
		);
	}
	
	Matrix& Matrix::operator* (const Matrix& matrix)
	{
		Matrix temp(*this);
		
		m[0] = temp.m[0 ] * matrix.m[0 ]
			 + temp.m[4 ] * matrix.m[1 ]
			 + temp.m[8 ] * matrix.m[2 ]
			 + temp.m[12] * matrix.m[3 ];
		
		m[1] = temp.m[1 ] * matrix.m[0 ]
			 + temp.m[5 ] * matrix.m[1 ]
			 + temp.m[9 ] * matrix.m[2 ]
			 + temp.m[13] * matrix.m[3 ];
		
		m[2] = temp.m[2 ] * matrix.m[0 ]
			 + temp.m[6 ] * matrix.m[1 ]
			 + temp.m[10] * matrix.m[2 ]
			 + temp.m[14] * matrix.m[3 ];
		
		m[3] = temp.m[3 ] * matrix.m[0 ]
			 + temp.m[7 ] * matrix.m[1 ]
			 + temp.m[11] * matrix.m[2 ]
			 + temp.m[15] * matrix.m[3 ];
		
		m[4] = temp.m[0 ] * matrix.m[4 ]
			 + temp.m[4 ] * matrix.m[5 ]
			 + temp.m[8 ] * matrix.m[6 ]
			 + temp.m[12] * matrix.m[7 ];
		
		m[5] = temp.m[1 ] * matrix.m[4 ]
			 + temp.m[5 ] * matrix.m[5 ]
			 + temp.m[9 ] * matrix.m[6 ]
			 + temp.m[13] * matrix.m[7 ];
		
		m[6] = temp.m[2 ] * matrix.m[4 ]
			 + temp.m[6 ] * matrix.m[5 ]
			 + temp.m[10] * matrix.m[6 ]
			 + temp.m[14] * matrix.m[7 ];
		
		m[7] = temp.m[3 ] * matrix.m[4 ]
			 + temp.m[7 ] * matrix.m[5 ]
			 + temp.m[11] * matrix.m[6 ]
			 + temp.m[15] * matrix.m[7 ];
		
		m[8] = temp.m[0 ] * matrix.m[8 ]
			 + temp.m[4 ] * matrix.m[9 ]
			 + temp.m[8 ] * matrix.m[10]
			 + temp.m[12] * matrix.m[11];
		
		m[9] = temp.m[1 ] * matrix.m[8 ]
			 + temp.m[5 ] * matrix.m[9 ]
			 + temp.m[9 ] * matrix.m[10]
			 + temp.m[13] * matrix.m[11];
		
		m[10]= temp.m[2 ] * matrix.m[8 ]
			 + temp.m[6 ] * matrix.m[9 ]
			 + temp.m[10] * matrix.m[10]
			 + temp.m[14] * matrix.m[11];
		
		m[11]= temp.m[3 ] * matrix.m[8 ]
			 + temp.m[7 ] * matrix.m[9 ]
			 + temp.m[11] * matrix.m[10]
			 + temp.m[15] * matrix.m[11];

		m[12]= temp.m[0 ] * matrix.m[12]
			 + temp.m[4 ] * matrix.m[13]
			 + temp.m[8 ] * matrix.m[14]
			 + temp.m[12] * matrix.m[15];

		m[13]= temp.m[1 ] * matrix.m[12]
			 + temp.m[5 ] * matrix.m[13]
			 + temp.m[9 ] * matrix.m[14]
			 + temp.m[13] * matrix.m[15];

		m[14]= temp.m[2 ] * matrix.m[12]
			 + temp.m[6 ] * matrix.m[13]
			 + temp.m[10] * matrix.m[14]
			 + temp.m[14] * matrix.m[15];

		m[15]= temp.m[3 ] * matrix.m[12]
			 + temp.m[7 ] * matrix.m[13]
			 + temp.m[11] * matrix.m[14]
			 + temp.m[15] * matrix.m[15];
		
		return *this;
	}
	
	void Matrix::translate(matrix_t x, matrix_t y, matrix_t z)
	{
		// set translation vector (x, y, z, 1)
		m[12] = x; m[13] = y; m[14] = z; m[15] = 1.0;
	}
	
	void Matrix::translated(matrix_t x, matrix_t y, matrix_t z)
	{
		// translate with delta +(x, y, z)
		m[12] +=  m[0 ] * x + m[4 ] * y + m[8 ] * z;
		m[13] +=  m[1 ] * x + m[5 ] * y + m[9 ] * z;
		m[14] +=  m[2 ] * x + m[6 ] * y + m[10] * z;
		//m[15] +=  m[3 ] * x + m[7 ] * y + m[11] * z;
	}
	
	void Matrix::translate_xy(matrix_t x, matrix_t y)
	{
		// translate with delta +(x, y)
		m[12] +=  m[0 ] * x + m[4] * y;
		m[13] +=  m[1 ] * x + m[5] * y;
		m[14] +=  m[2 ] * x + m[6] * y;
		//m[15] +=  m[3 ] * x + m[7] * y;
	}
	
	void Matrix::translate_xz(matrix_t x, matrix_t z)
	{
		// translate with delta +(x, y)
		m[12] +=  m[0 ] * x + m[ 8] * z;
		m[13] +=  m[1 ] * x + m[ 9] * z;
		m[14] +=  m[2 ] * x + m[10] * z;
		//m[15] +=  m[3 ] * x + m[7 ] * y;
	}
	
	void Matrix::rotateZYX(matrix_t x, matrix_t y, matrix_t z)
	{
		//////////////////////////////////////////////////////////////////////////////
		// convert Euler angles(x,y,z) to axes(left, up, forward)					//
		// Each column of the rotation matrix represents left, up and forward axis. //
		// The order of rotation is Roll->Yaw->Pitch (Rx*Ry*Rz)
		// Rx: rotation about X-axis, pitch
		// Ry: rotation about Y-axis, yaw(heading)
		// Rz: rotation about Z-axis, roll
		//    Rx           Ry          Rz
		// |1  0   0| | Cy  0 Sy| |Cz -Sz 0|   | CyCz        -CySz         Sy  |	//
		// |0 Cx -Sx|*|  0  1  0|*|Sz  Cz 0| = | SxSyCz+CxSz -SxSySz+CxCz -SxCy|	//
		// |0 Sx  Cx| |-Sy  0 Cy| | 0   0 1|   |-CxSyCz+SxSz  CxSySz+SxCz  CxCy|	//
		//////////////////////////////////////////////////////////////////////////////
		
		// rotation angle about X-axis (pitch)
		matrix_t sx = sin(x);
		matrix_t cx = cos(x);
		
		// rotation angle about Y-axis (yaw)
		matrix_t sy = sin(y);
		matrix_t cy = cos(y);
		
		if (z != 0.0)
		{
			// rotation angle about Z-axis (roll)
			matrix_t sz = sin(z);
			matrix_t cz = cos(z);
			
			// left vector
			m[0] =  cy * cz;
			m[1] =  sx * sy * cz + cx * sz;
			m[2] = -cx * sy * cz + sx * sz;
			m[3] = 0.0; // w1
			
			// up vector
			m[4] = -cy * sz;
			m[5] = -sx * sy * sz + cx * cz;
			m[6] =  cx * sy * sz + sx * cz;
			m[7] = 0.0; // w2
			
		} else {
			
			// sz = 0.0 (sin(0) = 0)
			// cz = 1.0 (cos(0) = 1)
			
			// left vector
			m[0] =  cy;
			m[1] =  sx * sy;
			m[2] = -cx * sy;
			m[3] = 0.0; // w1
			
			// up vector
			m[4] = 0.0;
			m[5] = cx;
			m[6] = sx;
			m[7] = 0.0; // w2
		}
		
		// forward vector
		m[ 8] =  sy;
		m[ 9] = -sx * cy;
		m[10] =  cx * cy;
		m[11] = 0.0; // w3
		
		m[12] = 0.0; // tx
		m[13] = 0.0; // ty
		m[14] = 0.0; // tz
		m[15] = 1.0; // w4
	}
	
	void Matrix::perspective(matrix_t fov, matrix_t aspect, matrix_t znear, matrix_t zfar)
	{
		const matrix_t pio360 = 4.0 * atan(1.0) / 360.0;
		
		matrix_t h = 1.0 / tan(fov * pio360);
		matrix_t negd = znear - zfar;
		
		m[ 0] = h / aspect; m[ 1] = 0; m[ 2] = 0;                           m[ 3] =  0;
		m[ 4] = 0;          m[ 5] = h; m[ 6] = 0;                           m[ 7] =  0;
		m[ 8] = 0;          m[ 9] = 0; m[10] = (zfar + znear) / negd;       m[11] = -1;
		m[12] = 0;          m[13] = 0; m[14] = 2.0 * (znear * zfar) / negd; m[15] =  0;
		
	}
	
}