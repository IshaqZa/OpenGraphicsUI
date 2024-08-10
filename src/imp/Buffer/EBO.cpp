#include "Buffer/EBO.h"

EBO::EBO(GLuint* vertices, GLsizeiptr size){

    glGenBuffers(1, &ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

};

void EBO::Bind(){
    // std::cout << "calling glBindBuffer" << std::endl;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    // std::cout << "done calling glBindBuffer" << std::endl;
    // GLenum error = glGetError();
    // std::cout << "Checked for any glad errors" << std::endl;
    // if(error != GL_NO_ERROR) throw std::runtime_error("OpenGL error: " + error);

};

void EBO::Unbind(){

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

};

void EBO::Delete(){

    glDeleteBuffers(1, &ID);

};