#include <Scene/Scene.h>

void Scene2D::linkVBO(VBO *vbo){
    this->vbo = vbo;
}

void Scene2D::linkVAO(VAO *vao){
    this->vao = vao;
}

void Scene2D::addElement(MenuElement* element) {
    elementArray.push_back(element);
}

void Scene2D::createVAO(int posSize, int colorSize, int texSize, GLenum type){

    vao = new VAO();
    vao->Bind();
    if(vbo){
        vao->linkAttrib(*vbo, 0, posSize, type, (posSize + colorSize + texSize) * sizeof(float), (void*) 0);
        vao->linkAttrib(*vbo, 1, colorSize, type, (posSize + colorSize + texSize) * sizeof(float), (void*)(posSize * sizeof(float)));
        vao->linkAttrib(*vbo, 2, texSize, type, (posSize + colorSize + texSize) * sizeof(float), (void*)((colorSize + posSize) * sizeof(float)));
    } else {
        throw std::runtime_error("VBO not initialised!");
    }
    vao->Unbind();
}

void Scene2D::createVBO(std::vector<GLfloat> &vertices){
    vbo = new VBO(vertices.data(), vertices.size() * sizeof(vertices));
}

void Scene2D::activate(){
    if(vao == nullptr) throw std::runtime_error("VAO not initialised");
    if(vbo == nullptr) throw std::runtime_error("VBO not initialised");
    vao->Bind();
    vbo->Bind();
}

//TODO: one element is being drawn, fix that
void Scene2D::render(GLuint texBool){
    vao->Bind();
    for(MenuElement* x : elementArray){
        x->draw(texBool);
    }
}