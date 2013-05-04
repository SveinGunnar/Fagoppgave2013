/**
 * 
 * World manager
 * Alf-Andre Walla, s181087
 * 
 * Vector implementation
 * 
**/

#include "vector.h"
#include <cmath>

namespace platformer
{
	
	// vec3 constructors
	vec3::vec3()
	{
		x = y = z = 0.0;
	}
	vec3::vec3(vector_precision_t v)
	{
		x = y = z = v;
	}
	vec3::vec3(vector_precision_t X, vector_precision_t Y, vector_precision_t Z)
	{
		x = X; y = Y; z = Z;
	}
	vec3::vec3(const vec3& v)
	{
		x = v.x; y = v.y; z = v.z;
	}
	
	// vec4 constructors
	vec4::vec4() : vec3(0.0)
	{
		w = 0.0;
	}
	vec4::vec4(vector_precision_t v) : vec3(v)
	{
		w = v;
	}
	vec4::vec4(vector_precision_t X, vector_precision_t Y, vector_precision_t Z, vector_precision_t W) : vec3(X, Y, Z)
	{
		w = W;
	}
	vec4::vec4(const vec3& v, vector_precision_t W) : vec3(v)
	{
		w = W;
	}
	
	// utility
	vector_precision_t vec3::length() const
	{
		vector_precision_t L = x * x + y * y + z * z;
		return sqrtf(L);
	}
	
	void vec3::normalize()
	{
		vector_precision_t L = length();
		if (L == 0) return;
		// normalize
		L = 1.0 / L;
		x *= L; y *= L; z *= L;
	}
	
	vector_precision_t vec3::dot(const vec3& v) const
	{
		return x * v.x + y * v.y + z * v.z;
	}
	
	vec3 vec3::cross(const vec3& v) const
	{
		return vec3
		(
			(y * v.z) - (v.y * z),
			(z * v.x) - (v.z * x),
			(x * v.y) - (v.x * y)
		);
	}
	
	vec3 vec3::frac() const
	{
		// NB. does not work for negative numbers
		return vec3( x - (int)x, y - (int)y, z - (int)z );
	}
	
	vec3 vec3::reflect(const vec3& normal) const
	{
		// incident - 2.0 * dot(normal, incident) * normal
		return *this - vec3(normal) * 2.0f * dot(normal);
	}
	
	vec3 vec3::mix(const vec3& v, float mixlevel) const
	{
		return vec3(
			this->x * (1.0 - mixlevel) + v.x * mixlevel,
			this->y * (1.0 - mixlevel) + v.y * mixlevel,
			this->z * (1.0 - mixlevel) + v.z * mixlevel
		);
	}
	
	const vec3& vec3::min(const vec3& a, const vec3& b) const
	{
		return (a.length() < b.length()) ? a : b;
	}
	
	const vec3& vec3::max(const vec3& a, const vec3& b) const
	{
		return (a.length() > b.length()) ? a : b;
	}
	
	// vector operators
	vec3 vec3::operator+ (const vec3& v) const
	{
		return vec3(x + v.x, y + v.y, z + v.z);
	}
	vec3 vec3::operator- (const vec3& v) const
	{
		return vec3(x - v.x, y - v.y, z - v.z);
	}
	vec3 vec3::operator* (const vec3& v) const
	{
		return vec3(x * v.x, y * v.y, z * v.z);
	}
	vec3 vec3::operator/ (const vec3& v) const
	{
		return vec3(x / v.x, y / v.y, z / v.z);
	}
	
	// vector arithmetic literal operators
	vec3 vec3::operator+ (const vector_precision_t v) const
	{
		return vec3(x + v, y + v, z + v);
	}
	vec3 vec3::operator- (const vector_precision_t v) const
	{
		return vec3(x - v, y - v, z - v);
	}
	vec3 vec3::operator* (const vector_precision_t v) const
	{
		return vec3(x * v, y * v, z * v);
	}
	vec3 vec3::operator/ (const vector_precision_t v) const
	{
		return vec3(x / v, y / v, z / v);
	}
	
	// vector compound operators
	vec3& vec3::operator +=(const vector_precision_t v)
	{
		x += v; y += v; z += v;
		return *this;
	}
	vec3& vec3::operator -=(const vector_precision_t v)
	{
		x -= v; y -= v; z -= v;
		return *this;
	}
	vec3& vec3::operator *=(const vector_precision_t v)
	{
		x *= v; y *= v; z *= v;
		return *this;
	}
	vec3& vec3::operator /=(const vector_precision_t v)
	{
		x /= v; y /= v; z /= v;
		return *this;
	}
	
}
