#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include<glad/glad.h>
#include<stb/stb_image.h>

#include "shader/shader.h"

#include <Debugger/Debugger.h>

class Texture
{
public:
	GLuint ID;
	GLenum type;
	std::string path;
	Texture(const char* image, GLenum texType, GLenum slot, GLenum pixelType);

	// Assigns a texture unit to a texture
	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	// Binds a texture
	void Bind();
	// Unbinds a texture
	void Unbind();
	// Deletes a texture
	void Delete();
};

#endif