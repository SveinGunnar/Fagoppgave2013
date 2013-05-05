/**
 * 
 * World manager
 * Alf-Andre Walla, s181087
 * 
 * Vector definition
 * 
 * normalize - makes the vector length == 1
 * dot       - returns cos-angle between vectors
 * frac      - returns a fraction-vector
 * cross     - cross product
 * reflect   - reflection vector
 * refract   - TBA :)
 * mix       - one-pole filter (lerp)
 * 
**/

#ifndef __VECTOR_H
#define __VECTOR_H

namespace platformer
{
	typedef float vector_precision_t;
	
	class vec3
	{
	public:
		// fields
		vector_precision_t x, y, z;
		
		// constructors
		vec3();
		vec3(vector_precision_t);
		vec3(vector_precision_t, vector_precision_t, vector_precision_t);
		vec3(const vec3&);
		
		// utility
		vector_precision_t length() const;
		void normalize();
		vector_precision_t dot(const vec3&) const;
		vec3 frac() const;
		vec3 cross(const vec3&) const;
		vec3 reflect(const vec3&) const;
		vec3 mix(const vec3&, float) const;
		
		const vec3& max(const vec3&, const vec3&) const;
		const vec3& min(const vec3&, const vec3&) const;
		
		// unary - (negate)
		vec3 operator - ();
		
		// arithmetic operators
		vec3 operator + (const vec3&) const;
		vec3 operator - (const vec3&) const;
		vec3 operator * (const vec3&) const;
		vec3 operator / (const vec3&) const;
		
		vec3& operator +=(const vector_precision_t);
		vec3& operator -=(const vector_precision_t);
		vec3& operator *=(const vector_precision_t);
		vec3& operator /=(const vector_precision_t);
		vec3  operator + (const vector_precision_t) const;
		vec3  operator - (const vector_precision_t) const;
		vec3  operator * (const vector_precision_t) const;
		vec3  operator / (const vector_precision_t) const;
		
	};
	
	class vec4 : public vec3
	{
	public:
		// homogenous coordinate (perspective division)
		vector_precision_t w;
		
		// constructors
		vec4();
		vec4(vector_precision_t);
		vec4(vector_precision_t, vector_precision_t, vector_precision_t, vector_precision_t);
		vec4(const vec3&, vector_precision_t);
		
		// utility
		vec3 xyz();
	};
	
}

#endif
