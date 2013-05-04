/**
 *  Alf-Andre Walla
 *	s181087
 *	
 *	OpenGL implementation
 *	
**/

#include "global.h"
#include "config.h"
#include "opengl.h"

#include <string>

namespace platformer
{
	// declarations
	OpenGL ogl;
	
	// initialize glfw, open OpenGL window, read function entry points
	void OpenGL::init()
	{
		glfwInit();
		
		// renderer initialization settings
		ogl.SW = Config::get("screen.w", 800);
		ogl.SH = Config::get("screen.h", 600);
		ogl.SA = (float)ogl.SW / (float)ogl.SH;
		
		ogl.multisample = Config::get("ogl.multisample", 0);
		ogl.anisotrophy = Config::get("ogl.anisotrophy", 2);
		
		bool fullscr = Config::get("screen.full", false);
		
		glfwOpenWindowHint(GLFW_WINDOW_NO_RESIZE, 1);
		glfwOpenWindowHint(GLFW_FSAA_SAMPLES, ogl.multisample);
		//glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3)
		//glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3)
		//glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE)
		
		if (glfwOpenWindow(ogl.SW, ogl.SH, 8, 8, 8, 8, 24, 8, (fullscr) ? GLFW_FULLSCREEN : GLFW_WINDOW) == GL_FALSE)
		{
			//cout << "ERROR: Could not open 32bit / 24d8s window of size: " << ogl.SW << ", " << ogl.SH << endl;
			logger.write(LERR, "Could not open 32bit / 24d8s window");
			glfwTerminate();
			throw "Opengl::init(): Could not open OpenGL context window, check your drivers!";
		}
		
		// standard formats
		ogl.imageformat = GL_RGBA8;
		ogl.storageformat = GL_UNSIGNED_BYTE;
		
		if (!fullscr)
		{
			if (Config::get("screen.center", false))
			{
				GLFWvidmode dsk;
				glfwGetDesktopMode(&dsk);
				
				glfwSetWindowPos( (dsk.Width - ogl.SW) / 2, (dsk.Height - ogl.SH) / 2 );
			}
			else
			{
				glfwSetWindowPos(Config::get("screen.x", 64), Config::get("screen.y", 64));
			}
		}
		
		// default window title
		glfwSetWindowTitle("-=testclient=- ");
		// vertical sync
		glfwSwapInterval(1); //getint("vsync", 0));
		// default viewport
		glViewport(0, 0, ogl.SW, ogl.SH);
		
		//-== openGL extensions ==-//
		
		//vertex buffer objects
		glGenBuffers    = (void(GLapi*)(GLsizei, GLuint*))glfwGetProcAddress("glGenBuffers");
		glBindBuffer    = (void(GLapi*)(GLenum, GLuint))glfwGetProcAddress("glBindBuffer");
		glBufferData    = (void(GLapi*)(GLenum, GLint, GLvoid*, GLenum))glfwGetProcAddress("glBufferData");
		glBufferSubData = (void(GLapi*)(GLenum, GLint, GLsizei, GLvoid*))glfwGetProcAddress("glBufferSubData");
		glDeleteBuffers = (void(GLapi*)(GLsizei, GLuint*))glfwGetProcAddress("glDeleteBuffers");
		
		//textures & mipmapping
		glGenerateMipmap	= (void(GLapi*)(GLenum))glfwGetProcAddress("glGenerateMipmap");
		glActiveTexture		= (void(GLapi*)(GLenum))glfwGetProcAddress("glActiveTexture");
		glTexImage3D		= (void(GLapi*)(GLenum, GLint, GLint, GLsizei, GLsizei, GLsizei, GLint, GLenum, GLenum, GLvoid*))glfwGetProcAddress("glTexImage3D");
		
		//shaders
		glCreateProgram			= (GLuint(GLapi*)())glfwGetProcAddress("glCreateProgram");
		glDeleteProgram	 		= (void(GLapi*)(GLuint))glfwGetProcAddress("glDeleteProgram");
		glCreateShader			= (GLuint(GLapi*)(GLenum))glfwGetProcAddress("glCreateShader");
		glDeleteShader			= (void(GLapi*)(GLuint))glfwGetProcAddress("glDeleteShader");
		glCompileShader			= (void(GLapi*)(GLuint))glfwGetProcAddress("glCompileShader");
		glShaderSource			= (void(GLapi*)(GLuint, GLsizei, GLchar**, GLint*))glfwGetProcAddress("glShaderSource");
		glGetShaderInfoLog		= (void(GLapi*)(GLuint, GLsizei, GLsizei*, GLchar*))glfwGetProcAddress("glGetShaderInfoLog");
		glGetShaderiv			= (void(GLapi*)(GLuint, GLenum, GLint*))glfwGetProcAddress("glGetShaderiv");
		glAttachShader          = (void(GLapi*)(GLuint, GLuint))glfwGetProcAddress("glAttachShader");
		glDetachShader          = (void(GLapi*)(GLuint, GLuint))glfwGetProcAddress("glDetachShader");
		glLinkProgram			= (void(GLapi*)(GLuint))glfwGetProcAddress("glLinkProgram");
		glUseProgram			= (void(GLapi*)(GLuint))glfwGetProcAddress("glUseProgram");
		
		glGetUniformLocation    = (GLint(GLapi*)(GLuint, GLchar*))glfwGetProcAddress("glGetUniformLocation");
		glUniform1i				= (void(GLapi*)(GLint, GLint))glfwGetProcAddress("glUniform1i");
		glUniform2i				= (void(GLapi*)(GLint, GLint, GLint))glfwGetProcAddress("glUniform2i");
		glUniform3i				= (void(GLapi*)(GLint, GLint, GLint, GLint))glfwGetProcAddress("glUniform3i");
		glUniform1f				= (void(GLapi*)(GLint, GLfloat))glfwGetProcAddress("glUniform1f");
		glUniform2f				= (void(GLapi*)(GLint, GLfloat, GLfloat))glfwGetProcAddress("glUniform2f");
		glUniform3f				= (void(GLapi*)(GLint, GLfloat, GLfloat, GLfloat))glfwGetProcAddress("glUniform3f");
		glUniform3fv			= (void(GLapi*)(GLint, GLsizei, GLfloat*))glfwGetProcAddress("glUniform3fv");
		glUniform4f				= (void(GLapi*)(GLint, GLfloat, GLfloat, GLfloat, GLfloat))glfwGetProcAddress("glUniform4f");
		glUniform4fv			= (void(GLapi*)(GLint, GLsizei, GLfloat*))glfwGetProcAddress("glUniform4fv");
		
		glUniformMatrix4fv      = (void(GLapi*)(GLint, GLsizei, GLboolean, GLfloat*))glfwGetProcAddress("glUniformMatrix4fv");
		
		glGenVertexArrays           = (void(GLapi*)(GLsizei, GLuint*))glfwGetProcAddress("glGenVertexArrays");
		glBindVertexArray           = (void(GLapi*)(GLuint))glfwGetProcAddress("glBindVertexArray");
		glDeleteVertexArrays        = (void(GLapi*)(GLsizei, GLuint*))glfwGetProcAddress("glDeleteVertexArrays");
		
		glDisableVertexAttribArray	= (void(GLapi*)(GLuint))glfwGetProcAddress("glDisableVertexAttribArray");
		glEnableVertexAttribArray	= (void(GLapi*)(GLuint))glfwGetProcAddress("glEnableVertexAttribArray");
												//	index,  count,   type,  normalized, stride,  data
		glVertexAttribPointer		= (void(GLapi*)(GLuint, GLsizei, GLenum, GLboolean, GLsizei, GLvoid*))glfwGetProcAddress("glVertexAttribPointer");
		glBindAttribLocation        = (void(GLapi*)(GLuint, GLuint, GLchar*))glfwGetProcAddress("glBindAttribLocation");
		
		// point sprites
		//glPointParameterfARB        = (void(GLapi*)())glfwGetProcAddress("glPointParameterf")
		//glPointParameterfvARB       = (void(GLapi*)())glfwGetProcAddress("glPointParameterfv")
		
		if (glGenBuffers == NULL)
		{
			logger.write(LERR, "Your video card does not support VBO's (OpenGL 1.2+). Exiting.");
			throw "Opengl::init(): Missing VBO support, check your drivers!";
		}
		if (glCreateProgram == NULL)
		{
			logger.write(LERR, "Your video card does not support Programmable Shader Pipeline. Exiting.");
			throw "Opengl::init(): Missing shader support, check your drivers!";
		}
		if (glGenVertexArrays == NULL)
		{
			logger.write(LERR, "Your video card does not support Vertex Array Objects. Exiting.");
			throw "Opengl::init(): Missing VAO support, check your drivers!";
		}
		if (glVertexAttribPointer == NULL)
		{
			logger.write(LERR, "Your video card does not support Vertex Attributes. Exiting.");
			throw "Opengl::init(): Missing vertexattrib support, check your drivers!";
		}
		
		if (glGenerateMipmap == NULL)
		{
			logger.write(LERR, "Your video card does not support automatic mipmap generation. Exiting.");
			throw "Opengl::init(): Missing mipmap generation support, check your drivers!";
		}
		
		GLenum glerr = glGetError();
		if (glerr)
		{
			logger.write(LERR, "OpenGL initialization error");
			throw "OpenGL::init(): Initialization error";
		}
		
	}
	
	const bool OpenGL::checkError()
	{
		GLenum error = glGetError();
		if (error)
		{
			std::string errorString;
			switch (error)
			{
			case GL_INVALID_ENUM:
				errorString = "Invalid enumeration parameter (GL_INVALID_ENUM)";
				break;
			case GL_INVALID_VALUE:
				errorString = "Invalid value for parameter (GL_INVALID_VALUE)";
				break;
			case GL_INVALID_OPERATION:
				errorString = "Invalid operation for current state (GL_INVALID_OPERATION)";
				break;
				
			default:
				errorString = "Unknown error (GL_INVALID_ENUM)";
			}
			
			logger.write(LERR, "OpenGL error: " + errorString);
			return true;
		}
		
	}
	
}
