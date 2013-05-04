/**
 *
**/

#ifndef __SHADER_H
#define __SHADER_H

#include <GL/gl.h>
#include <string>
#include <vector>
#include "vector.h"
#include "matrix.h"

namespace platformer
{
	typedef struct
	{
		// common uniforms
		GLint matview;
		GLint matproj;
		GLint texture;
		GLint frame;
		
	} shader_uniforms_t;
	
	class Shader
	{
	private:
		GLuint shader;
		shader_uniforms_t uniforms;
		
		void printShaderStatus(GLuint);
		
		// keep track of last bound shader
		static GLuint lastShader;
	public:
		Shader() {};
		Shader(std::string, std::vector<std::string>);
		
		bool sendFloat(GLint, float);
		bool sendVec3 (GLint, vec3&);
		bool sendVec4 (GLint, vec4&);
		bool sendMatrix(GLint, Matrix&);
		
		void bind();
		const shader_uniforms_t& getUniforms();
		
		GLint getUniform(std::string);
		static void unbind();
	};
	
}

#endif
