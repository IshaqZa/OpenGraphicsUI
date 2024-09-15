#include "Buffer/texture.h"

Texture::Texture(const char* image, GLenum texType, GLenum slot, GLenum pixelType)
{
	std::cout << image << std::endl;
	path = image;
	// Assigns the type of the texture ot the texture object
	type = texType;

	// Stores the width, height, and the number of color channels of the image
	int widthImg, heightImg, numColCh;
	// Flips the image so it appears right side up
	stbi_set_flip_vertically_on_load(true);
	// Reads the image from a file and stores it in bytes
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

	std::cout << "Image specs:" << std::endl;
	std::cout << "width, height: " << widthImg << ", " << heightImg << std::endl;
	std::cout << "Number of color channels: " << numColCh << std::endl;
	std::cout << "Size of image bytes" << sizeof(bytes) << std::endl;


	if(bytes == NULL){
		std::cerr << "Texture Error: " << stbi_failure_reason() << std::endl;
		exit(EXIT_FAILURE);
	}

	// Generates an OpenGL texture object
	glGenTextures(1, &ID);

	// Assigns the texture to a Texture Unit
	glActiveTexture(slot);

	glBindTexture(texType, ID);

	std::cout << "generated textures, activated slot and bound" << std::endl;

	// Configures the type of algorithm that is used to make the image smaller or bigger
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Configures the way the texture repeats (if it does at all)
	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	std::cout << "Set needed parameters" << std::endl;

	// Extra lines in case you choose to use GL_CLAMP_TO_BORDER
	// float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
	// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

	// Assigns the image to the OpenGL Texture object
	if(numColCh == 1){ // gray-scale
		glTexImage2D(texType, 0, GL_RED, widthImg, heightImg, 0, GL_RED, pixelType, bytes);
	}
	else if(numColCh == 3){ // RGB
		glTexImage2D(texType, 0, GL_RGB, widthImg, heightImg, 0, GL_RGB, pixelType, bytes);
	}
	else if(numColCh == 4){ // RGBA
		glTexImage2D(texType, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA, pixelType, bytes);
	}
	else {
		std::cerr << "Image type unsupported" << std::endl;
		exit(EXIT_FAILURE);
	}

	std::cout << "Generated 2D Image Texture" << std::endl;
	// Generates MipMaps
	glGenerateMipmap(texType);

	std::cout << "Generated mipmap" << std::endl;

	// Deletes the image data as it is already in the OpenGL Texture object
	stbi_image_free(bytes);
	// Unbinds the OpenGL Texture object so that it can't accidentally be modified
	glBindTexture(texType, 0);
	std::cout << "Texture created successfully" << std::endl;
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{

	std::cout << "tex unit values: " << std::endl;
	std::cout << "shader ID: " << shader.ID << std::endl;
	std::cout << "uniform: " << uniform << std::endl;
	std::cout << "unit: " << unit << std::endl;

	// Gets the location of the uniform
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);
	if(texUni == -1){
		std::cerr << "passed uniform value does not exist in shader in tex unit" << std::endl;
		exit(EXIT_FAILURE);
	}

	// Shader needs to be activated before changing the value of a uniform
	shader.Activate();
	// Sets the value of the uniform
	glUniform1i(texUni, unit);
	glCheckError();
}

void Texture::Bind()
{
	glBindTexture(type, ID);
	glCheckError();
}

void Texture::Unbind()
{
	glBindTexture(type, 0);
	glCheckError();
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
	glCheckError();
}