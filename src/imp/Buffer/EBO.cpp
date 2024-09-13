#include "Buffer/EBO.h"

EBO::EBO(GLuint* vertices, GLsizeiptr size){
    GLenum error;
    glGenBuffers(1, &ID);

    if(error = glGetError() != GL_NO_ERROR){
		std::cerr << "OpenGL Error generating ebo buffer: " << error << std::endl;
		exit(EXIT_FAILURE);
	}

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);

    if(error = glGetError() != GL_NO_ERROR){
		std::cerr << "OpenGL Error binding ebo buffer: " << error << std::endl;
		exit(EXIT_FAILURE);
	}

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

    if(error = glGetError() != GL_NO_ERROR){
		std::cerr << "OpenGL Error uploading ebo buffer data: " << error << std::endl;
		exit(EXIT_FAILURE);
	}

};

void EBO::Bind(){
    // std::cout << "calling glBindBuffer" << std::endl;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);

    if(GLenum error = glGetError() != GL_NO_ERROR){
		std::cerr << "OpenGL Error binding ebo buffer: " << error << std::endl;
		exit(EXIT_FAILURE);
	}

    // std::cout << "done calling glBindBuffer" << std::endl;
    // GLenum error = glGetError();
    // std::cout << "Checked for any glad errors" << std::endl;
    // if(error != GL_NO_ERROR) throw std::runtime_error("OpenGL error: " + error);

};

void EBO::Unbind(){

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    if(GLenum error = glGetError() != GL_NO_ERROR){
		std::cerr << "OpenGL Error unbinding ebo: " << error << std::endl;
		exit(EXIT_FAILURE);
	}

};

void EBO::Delete(){

    glDeleteBuffers(1, &ID);
    if(GLenum error = glGetError() != GL_NO_ERROR){
		std::cerr << "OpenGL Error deleting ebo: " << error << std::endl;
		exit(EXIT_FAILURE);
	}
};