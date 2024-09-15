#include "Buffer/EBO.h"

EBO::EBO(GLuint* vertices, GLsizeiptr size){
    glGenBuffers(1, &ID);

    std::cout << "ID: " << ID << std::endl;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    glCheckError();
};

void EBO::Bind(){
    // std::cout << "calling glBindBuffer" << std::endl;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glCheckError();

    // std::cout << "done calling glBindBuffer" << std::endl;
    // GLenum (error = glGetError());
    // std::cout << "Checked for any glad errors" << std::endl;
    // if(error != GL_NO_ERROR) throw std::runtime_error("OpenGL error: " + error);

};

void EBO::Unbind(){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glCheckError();
};

void EBO::Delete(){
    glDeleteBuffers(1, &ID);
    glCheckError();
};