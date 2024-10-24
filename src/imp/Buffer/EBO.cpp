#include "Buffer/EBO.h"

EBO::EBO(GLuint* vertices, GLsizeiptr size){

    glGenBuffers(1, &ID);
    if(glCheckError() != GL_NO_ERROR){
        exit(EXIT_FAILURE);
    }
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    if(glCheckError() != GL_NO_ERROR){
        exit(EXIT_FAILURE);
    }

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    if(glCheckError() != GL_NO_ERROR){
        exit(EXIT_FAILURE);
    }

};

void EBO::Bind(){
    // std::cout << "calling glBindBuffer" << std::endl;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    if(glCheckError() != GL_NO_ERROR){
        exit(EXIT_FAILURE);
    }
    // std::cout << "done calling glBindBuffer" << std::endl;
    // GLenum error = glGetError();
    // std::cout << "Checked for any glad errors" << std::endl;
    // if(error != GL_NO_ERROR) throw std::runtime_error("OpenGL error: " + error);

};

void EBO::Unbind(){

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    if(glCheckError() != GL_NO_ERROR){
        exit(EXIT_FAILURE);
    }

};

void EBO::Delete(){

    glDeleteBuffers(1, &ID);
    if(glCheckError() != GL_NO_ERROR){
        exit(EXIT_FAILURE);
    }

};