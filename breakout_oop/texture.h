#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>

//Texture2D is able to store and configure a texture in OpenGL.
//It also hosts utility functions for easy management.
class Texture2D
{
public:
	//holds the texture object ID, which is referenced for many future operations
	GLuint ID;
	//texture image dimensions
	GLuint Width, Height; //image width and height, in pixels
	//texture format
	GLuint Internal_Format; //texture object format
	GLuint Image_Format; //loaded image format
	//texture configuration
	GLuint Wrap_S; //wrapping mode on s-axis
	GLuint Wrap_T; //wrapping mode on t-axis
	GLuint Filter_Min; //filtering mode if texture pixels < screen pixels
	GLuint Filter_Max; //filtering mode if texture pixels > screen pixels
	//constructor (sets default texture modes)
	Texture2D();
	//generates texture from image data
	void Generate(GLuint width, GLuint height, unsigned char* data);
	//binds the texture as the current active GL_TEXTURE_2D texture object
	void Bind() const;
};

#endif
