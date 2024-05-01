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

    if(vbo){
        vao->linkAttrib(*vbo, 0, posSize, type, (posSize + colorSize + texSize) * sizeof(float), (void*) 0);
        vao->linkAttrib(*vbo, 1, colorSize, type, (posSize + colorSize + texSize) * sizeof(float), (void*)(3 * sizeof(float)));
        vao->linkAttrib(*vbo, 2, texSize, type, (posSize + colorSize + texSize) * sizeof(float), (void*)(6 * sizeof(float)));
    } else {
        throw std::runtime_error("VBO not initialised!");
    }
}

void Scene2D::createVBO(std::vector<GLfloat> &vertices){
    *vbo = VBO(vertices.data(), vertices.size() * sizeof(vertices));
}

void Scene2D::activate(){
    vao->Bind();
    vbo->Bind();
}

void Scene2D::render(){
    vao->Bind();
    for(MenuElement* x : elementArray){
        std::cout << "Reached here" << std::endl;
        x->dummyFun();
        // std::cin.get();
        x->draw();
    }
}