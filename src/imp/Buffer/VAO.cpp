#include "Buffer/VAO.h"

VAO::VAO(){

    glGenVertexArrays(1, &ID);
    if(glCheckError() != GL_NO_ERROR){
        exit(EXIT_FAILURE);
    }

}

void VAO::linkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset){

    VBO.Bind();

    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
    if(glCheckError() != GL_NO_ERROR){
        exit(EXIT_FAILURE);
    }

    glEnableVertexAttribArray(layout);
    if(glCheckError() != GL_NO_ERROR){
        exit(EXIT_FAILURE);
    }

    VBO.Unbind();
}

void VAO::Bind(){

    glBindVertexArray(ID);
    if(glCheckError() != GL_NO_ERROR){
        exit(EXIT_FAILURE);
    }

}

void VAO::Unbind(){

    glBindVertexArray(0);
    if(glCheckError() != GL_NO_ERROR){
        exit(EXIT_FAILURE);
    }

}

void VAO::Delete(){

    glDeleteVertexArrays(1, &ID);
    if(glCheckError() != GL_NO_ERROR){
        exit(EXIT_FAILURE);
    }

}