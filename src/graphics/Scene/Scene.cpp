#include <Scene/Scene.h>

Scene::Scene(){
    vertices = std::make_shared<std::vector<GLfloat>>(); 
}

void Scene::linkVBO(std::shared_ptr<VBO> vbo){
    this->vbo = vbo;
}

void Scene::linkVAO(std::shared_ptr<VAO> vao){
    this->vao = vao;
}

void Scene::linkShader(std::shared_ptr<Shader> shader){
    this->shader = shader;
    isTex = glGetUniformLocation(shader->ID, "isTex");
}

std::shared_ptr<Shader> Scene::createShader(const char* vertexFile, const char* fragmentFile){
    shader = std::make_shared<Shader>(vertexFile, fragmentFile);
    isTex = glGetUniformLocation(shader->ID, "isTex");
    return shader;
}

void Scene::setBackgroundColor(glm::vec4 backgroundColor){
    this->backgroundColor = backgroundColor;
}

void Scene::createVAO(int posSize, int colorSize, int texSize, GLenum type){

    vao = std::make_shared<VAO>();
    vao->Bind();
    if(vbo){
        vao->linkAttrib(*vbo, 0, posSize, type, (posSize + colorSize + texSize) * sizeof(float), (void*) 0);
        vao->linkAttrib(*vbo, 1, colorSize, type, (posSize + colorSize + texSize) * sizeof(float), (void*)(posSize * sizeof(float)));
        if(texSize > 0) vao->linkAttrib(*vbo, 2, texSize, type, (posSize + colorSize + texSize) * sizeof(float), (void*)((colorSize + posSize) * sizeof(float)));
    } else {
        throw std::runtime_error("VBO not initialised!");
    }
    vao->Unbind();
}

void Scene::createVBO(){
    vbo = std::make_shared<VBO>(vertices->data(), vertices->size() * sizeof(vertices));
}

void Scene::activate(){
    glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, backgroundColor.w);
    if(vao == nullptr) throw std::runtime_error("VAO not initialised");
    if(vbo == nullptr) throw std::runtime_error("VBO not initialised");
    vbo->Bind();
    vao->Bind();
}

std::shared_ptr<std::vector<GLfloat>> Scene::getVertices(){
    return vertices;
}

unsigned int* Scene::currentIndex(){

    return &index;

}

std::shared_ptr<Shader> Scene::getShaderProgram(){
    return shader;
}