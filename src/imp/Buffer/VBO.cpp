#include "Buffer/VBO.h"
VBO::VBO(GLfloat* vertices, GLsizeiptr size){

    glGenBuffers(1, &ID);
    if(glCheckError() != GL_NO_ERROR){
        exit(EXIT_FAILURE);
    }

    glBindBuffer(GL_ARRAY_BUFFER, ID);
    if(glCheckError() != GL_NO_ERROR){
        exit(EXIT_FAILURE);
    }

    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    if(glCheckError() != GL_NO_ERROR){
        exit(EXIT_FAILURE);
    }

};

void VBO::Bind(){

    glBindBuffer(GL_ARRAY_BUFFER, ID);
    if(glCheckError() != GL_NO_ERROR){
        exit(EXIT_FAILURE);
    }

};

void VBO::Unbind(){

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    if(glCheckError() != GL_NO_ERROR){
        exit(EXIT_FAILURE);
    }

};

void VBO::Delete(){

    glDeleteBuffers(1, &ID);
    if(glCheckError() != GL_NO_ERROR){
        exit(EXIT_FAILURE);
    }

};