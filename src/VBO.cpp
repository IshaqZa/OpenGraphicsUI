#include "Buffer/VBO.h"

VBO::VBO(GLfloat* indices, GLsizeiptr size){

    glGenBuffers(1, &ID);
    glBindBuffer(GL_ARRAY_BUFFER, ID);

    glBufferData(GL_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);

    glDeleteBuffers(1, &ID);

};

void VBO::Bind(){

    glBindBuffer(GL_ARRAY_BUFFER, ID);

};

void VBO::Unbind(){

    glBindBuffer(GL_ARRAY_BUFFER, 0);

};

void VBO::Delete(){

    glDeleteBuffers(1, &ID);

};