#include "Buffer/VAO.h"

VAO::VAO(){

    glGenVertexArrays(1, &ID);
    glCheckError();
}

void VAO::linkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset){

    VBO.Bind();

    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
    glCheckError();
    VBO.Unbind();

}

void VAO::Bind(){

    glBindVertexArray(ID);
    glCheckError();
}

void VAO::Unbind(){

    glBindVertexArray(0);
    glCheckError();
}

void VAO::Delete(){

    glDeleteVertexArrays(1, &ID);
    glCheckError();
}