#include <Scene/Scene.h>

void Scene2D::linkVBO(VBO *vbo){
    this->vbo = vbo;
}

void Scene2D::linkVAO(VAO *vao){
    this->vao = vao;
}

void Scene2D::linkShader(Shader* shader){
    this->shader = shader;
}

Shader* Scene2D::createShader(const char* vertexFile, const char* fragmentFile){
    shader = new Shader(vertexFile, fragmentFile);
    return shader;
}

void Scene2D::setBackgroundColor(GLfloat r, GLfloat g, GLfloat b, GLfloat alpha){
    backgroundColor[0] = r;
    backgroundColor[1] = g;
    backgroundColor[2] = b;
    backgroundColor[3] = alpha;
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

void Scene2D::createVBO(){
    vbo = new VBO(vertices.data(), vertices.size() * sizeof(vertices));
}

void Scene2D::activate(){
    glClearColor(backgroundColor[0], backgroundColor[1], backgroundColor[2], backgroundColor[3]);
    if(vao == nullptr) throw std::runtime_error("VAO not initialised");
    if(vbo == nullptr) throw std::runtime_error("VBO not initialised");
    vao->Bind();
    vbo->Bind();
}

void Scene2D::render(GLuint texBool){
    vao->Bind();
    for(MenuElement* x : elementArray){
        x->draw(texBool);
    }
}

std::vector<GLfloat>* Scene2D::getVertices(){
    return &vertices;
}

void Scene2D::deleteResources(){
    if(vao != nullptr){
        vao->Delete();
        delete vao;
    }
    if(vbo != nullptr){
        vbo->Delete();
        delete vbo;
    }
    if(shader != nullptr){
        shader->Delete();
        delete shader;
    }  
}

unsigned int* Scene2D::currentIndex(){

    return &index;

}