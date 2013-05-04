/*

*/

#include "shaderman.h"
#include <string>
#include <vector>

namespace platformer
{
	Shaderman::Shaderman()
	{
		lastShader = 0;
	}
	
	void Shaderman::init()
	{
		// load and initialize all shaders
		std::vector<std::string> linkstage;
		
		// fullscreen shader
		shaders[FULLSCREEN_SHADER] = Shader("shaders/screenspace.glsl", linkstage);
		
		// standard 2d shader
		shaders[STANDARD_SHADER] = Shader("shaders/standard.glsl", linkstage);
		
		linkstage.push_back( "in_vertex" );
		linkstage.push_back( "in_texture" );
		linkstage.push_back( "in_color" );
		
		// extended 2d array shader
		shaders[TILESET_SHADER] = Shader("shaders/tileset.glsl", linkstage);
		
		shaders[PLAYER_SHADER] = Shader("shaders/player.glsl", linkstage);
		
		// return state to fixed pipeline
		Shader::unbind();
	}
	
	void Shaderman::sendProjection(Matrix& m)
	{
		shader_uniforms_t uniforms = shaders[lastShader].getUniforms();
		shaders[lastShader].sendMatrix(uniforms.matproj, m);
	}
	
	void Shaderman::sendView(Matrix& m)
	{
		shader_uniforms_t uniforms = shaders[lastShader].getUniforms();
		shaders[lastShader].sendMatrix(uniforms.matview, m);
	}
	
	void Shaderman::sendFrame(float f)
	{
		shader_uniforms_t uniforms = shaders[lastShader].getUniforms();
		shaders[lastShader].sendFloat(uniforms.frame, f);
	}
	
	void Shaderman::sendFloat(int uniform, float f)
	{
		shaders[lastShader].sendFloat(uniform, f);
	}
	
	int Shaderman::getUniform(std::string uniform)
	{
		return shaders[lastShader].getUniform(uniform);
	}
	
	void Shaderman::bind(shaderlist_t shader)
	{
		shaders[shader].bind();
		lastShader = shader;
	}
	
}