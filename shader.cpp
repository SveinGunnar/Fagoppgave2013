/**
 *	Alf-Andre Walla
 *	s181087
 *	
 *	Shader implementation
 *	
**/

#include "shader.h"

#include "global.h"
#include <GL/glext.h>
#include <fstream>
#include "opengl.h"

namespace platformer
{
	// static members
	GLuint Shader::lastShader = 0;
	
	// as written by user763305
	// http://stackoverflow.com/questions/6089231/getting-std-ifstream-to-handle-lf-cr-and-crlf
	std::istream& safeGetline(std::istream& is, std::string& t)
	{
    	t.clear();
		
	    // The characters in the stream are read one-by-one using a std::streambuf.
	    // That is faster than reading them one-by-one using the std::istream.
	    // Code that uses streambuf this way must be guarded by a sentry object.
	    // The sentry object performs various tasks,
	    // such as thread synchronization and updating the stream state.
		
	    std::istream::sentry se(is, true);
	    std::streambuf* sb = is.rdbuf();
		
	    for(;;) {
    	    int c = sb->sbumpc();
	        switch (c) {
		        case '\n':
		            return is;
        		case '\r':
		            if(sb->sgetc() == '\n')
		                sb->sbumpc();
		            return is;
		        case EOF:
		            // Also handle the case when the last line has no line ending
		            if(t.empty())
		                is.setstate(std::ios::eofbit);
		            return is;
		        default:
		            t += (char)c;
	        }
	    }
	} // safeGetline
	
	void Shader::printShaderStatus(GLuint shader, bool prog)
	{
		logger.write(LERR, "*** Shader program compile error:");
		GLint logsize;
		if (prog)
		{
			glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &logsize);
			GLchar infolog[logsize];
			glGetProgramInfoLog(shader, logsize, NULL, infolog);
			logger.write(LINFO, std::string("\n") + std::string(&infolog[0], logsize));
		}
		else
		{
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logsize);
			GLchar infolog[logsize];
			glGetShaderInfoLog(shader, logsize, NULL, infolog);
			logger.write(LINFO, std::string("\n") + std::string(&infolog[0], logsize));
		}
	}
	
	Shader::Shader(std::string filename, std::vector<std::string> linkstage)
	{
		std::ifstream file(filename.c_str());
		
		if (!file)
		{
			throw "Shader::load(): Could not open file " + filename;
		}
		
		// read file line by line
		const std::string DEF_VERT_PROG = "#define VERTEX_PROGRAM";
		std::string line;
		std::string fragshader = "", vertshader = "";
		
		while (safeGetline(file, line))
		{
			if (line.compare(DEF_VERT_PROG) != 0)
			{
				fragshader += line + "\n";
			}
			vertshader += line + "\n";
		}
		file.close();
		
		// char arrays for GL call
		char* source_v[1] = { const_cast<char*>(vertshader.c_str()) };
		char* source_f[1] = { const_cast<char*>(fragshader.c_str()) };
		
		// create shaders
		GLuint shader_v = glCreateShader(GL_VERTEX_SHADER_ARB);
		GLuint shader_f = glCreateShader(GL_FRAGMENT_SHADER_ARB);
		
		// upload source
		glShaderSource(shader_v, 1, (GLchar**) source_v, NULL);
		glShaderSource(shader_f, 1, (GLchar**) source_f, NULL);
		
		// compile shaders
		glCompileShader(shader_v);
		glCompileShader(shader_f);
		
		GLint status;
		// vertex status
		glGetShaderiv(shader_v, GL_COMPILE_STATUS, &status);
		if (!status)
		{
			printShaderStatus(shader_v, false);
			logger.write(LINFO, filename);
			throw "Shader::load(): Shader compilation error";
		}
		// fragment status
		glGetShaderiv(shader_f, GL_COMPILE_STATUS, &status);
		if (!status)
		{
			printShaderStatus(shader_f, false);
			logger.write(LINFO, filename);
			throw "Shader::load(): Shader compilation error";
		}
		
		// create shader program
		this->shader = glCreateProgram();
		glAttachShader(this->shader, shader_v);
		glAttachShader(this->shader, shader_f);
		
		// common attributes
		for (int i = 0; i < linkstage.size(); i++)
		{
			glBindAttribLocation(this->shader, i, (char*)linkstage[i].c_str());
		}
		
		// link program
		// we don't care about outlier errors for linking (ultra-rare)
		glLinkProgram(this->shader);
		
		// start program
		bind();
		
		glGetProgramiv(this->shader, GL_LINK_STATUS, &status);
		if (!status)
		{
			logger.write(LINFO, filename);
			printShaderStatus(this->shader, true);
			throw "Shader::load() failed to link shaders";
		}
		
		// get ultra-common uniforms
		uniforms.matproj = glGetUniformLocation(this->shader, "matproj");
		//if (uniforms.matproj == -1) throw "Could not find projection matrix uniform for shader: " + filename;
		
		uniforms.matview = glGetUniformLocation(this->shader, "matview");
		//if (uniforms.matview == -1) throw "Could not find modelview matrix uniform for shader: " + filename;
		
		uniforms.texture = glGetUniformLocation(this->shader, "texture");
		if (uniforms.texture+1) glUniform1i(uniforms.texture, 0);
		
		uniforms.frame = glGetUniformLocation(this->shader, "frame");
		
		// check for errors
		if (OpenGL::checkError())
		{
			throw "Shader::load(): Shader general OpenGL error";
		}
		
		logger.write(LINFO, "Loaded shader: " + filename);
	}
	
	const shader_uniforms_t& Shader::getUniforms()
	{
		return uniforms;
	}
	
	bool Shader::sendFloat(GLint uniform, float f)
	{
		glUniform1f(uniform, f);
	}
	
	bool Shader::sendVec3(GLint uniform, vec3& v)
	{
		glUniform3f(uniform, v.x, v.y, v.z);
	}
	
	bool Shader::sendMatrix(GLint uniform, Matrix& m)
	{
		glUniformMatrix4fv(uniform, 1, false, m.ptr());
	}
	
	GLint Shader::getUniform(std::string uniform)
	{
		return glGetUniformLocation(this->shader, (GLchar*)uniform.c_str());
	}
	
	void Shader::bind()
	{	// avoid costly rebind
		if (lastShader == shader) return;
		
		glUseProgram(shader);
		lastShader = shader;
	}
	
	void Shader::unbind()
	{
		if (lastShader)
		{
			lastShader = 0;
			glUseProgram(0);
		}
	}
	
}
