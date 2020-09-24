#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>

#include <GL/glew.h>

#include "texture.h"
#include "shader.h"

class ResourceManager
{
public:
	//resource storage
	static std::map<std::string, Shader> Shaders;
	static std::map<std::string, Texture2D> Textures;
	//load/generate a shader program from file by loading vertex, fragment, and geometry (if present) shader source codes
	static Shader LoadShader(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile, std::string name);
	//retrieves a stored shader
	static Shader GetShader(std::string name);
	//loads/generates a texture from file
	static Texture2D LoadTexture(const GLchar *file, GLboolean alpha, std::string name);
	//retrieves a stored texture
	static Texture2D GetTexture(std::string name);
	//properly de-allocates all loaded resources
	static void Clear();
private:
	//private constructor - no actual resource manager objects desired
	ResourceManager() { }
	//loads a shader from file
	static Shader loadShaderFromFile(const GLchar *vShaderFile, const GLchar *fShaderFile, const GLchar *gShaderFile = nullptr);
	//loads a single texture from file
	static Texture2D loadTextureFromFile(const GLchar *file, GLboolean alpha);
};

#endif