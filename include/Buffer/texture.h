#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include<glad/glad.h>
#include<stb/stb_image.h>
#include<json/json.hpp>

#include "shader/shader.h"

using json = nlohmann::json;

class Texture
{
public:
	GLuint ID;
	GLenum type;
	std::string path;
	Texture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

	// Assigns a texture unit to a texture
	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	// Binds a texture
	void Bind();
	// Unbinds a texture
	void Unbind();
	// Deletes a texture
	void Delete();
};

void to_json(json& j, const Texture& texture);
void from_json(const json& j, Texture& texture);

#endif