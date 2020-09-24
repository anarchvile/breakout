#ifndef SHADER_H
#define SHADER_H

#include <string>

#include <GL/glew.h>
#include <glut.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>

class Shader
{
public:
	//state
	GLuint ID;
	//constructor
	Shader() {}
	//activates the current shader
	Shader &Use();
	//compiles the shader from given source code
	void Compile(const GLchar *vertexSource, const GLchar *fragmentSource, const GLchar *geometrySource = nullptr); //note that the geometry shader is optional

	//utility functions for setting uniforms
	void SetFloat(const GLchar *name, GLfloat value, GLboolean useShader = false);
	void SetInteger(const GLchar *name, GLint value, GLboolean useShader = false);
	void SetVector2f(const GLchar *name, GLfloat x, GLfloat y, GLboolean useShader = false);
	void SetVector2f(const GLchar *name, const glm::vec2 &value, GLboolean useShader = false);
	void SetVector3f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLboolean useShader = false);
	void SetVector3f(const GLchar *name, const glm::vec3 &value, GLboolean useShader = false);
	void SetVector4f(const GLchar *name, GLfloat x, GLfloat y, GLfloat z, GLfloat w, GLboolean useShader = false);
	void SetVector4f(const GLchar *name, const glm::vec4 &value, GLboolean useShader = false);
	void SetMatrix4(const GLchar *name, const glm::mat4 &matrix, GLboolean useShader = false);
private:
	//check for compilation/linking errors, and print them if any are present
	void CheckCompileErrors(GLuint object, std::string type);
};

#endif
