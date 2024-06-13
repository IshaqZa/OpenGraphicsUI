#include <Scene/Scene.h>

void Scene2D::createVertexData(){
    vertices = std::make_shared<std::vector<GLfloat>>();
}

void Scene2D::linkVBO(std::shared_ptr<VBO> vbo){
    this->vbo = vbo;
}

void Scene2D::linkVAO(std::shared_ptr<VAO> vao){
    this->vao = vao;
}

void Scene2D::linkShader(std::shared_ptr<Shader> shader){
    this->shader = shader;
}

std::shared_ptr<Shader> Scene2D::createShader(const char* vertexFile, const char* fragmentFile){
    shader = std::make_shared<Shader>(vertexFile, fragmentFile);
    return shader;
}

void Scene2D::setBackgroundColor(glm::vec4 backgroundColor){
    this->backgroundColor = backgroundColor;
}

void Scene2D::addElement(MenuElement* element) {
    elementArray.push_back(element);
}

void Scene2D::createVAO(int posSize, int colorSize, int texSize, GLenum type){

    vao = std::make_shared<VAO>();
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
    vbo = std::make_shared<VBO>(vertices->data(), vertices->size() * sizeof(vertices));
}

void Scene2D::activate(){
    glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, backgroundColor.w);
    if(vao == nullptr) throw std::runtime_error("VAO not initialised");
    if(vbo == nullptr) throw std::runtime_error("VBO not initialised");
    vao->Bind();
    vbo->Bind();
}

void Scene2D::render(GLuint texBool){
    vao->Bind();
    std::cout << "Prepared to render elements" << std::endl;
    int i = 1;
    for(MenuElement* x : elementArray){
        std::cout << "Rendering element: " << i << std::endl;
        i++;
        if(!x) std::cout << "Error: Element is empty" << std::endl;
        x->draw(texBool);
    }
}

std::shared_ptr<std::vector<GLfloat>> Scene2D::getVertices(){
    return vertices;
}

unsigned int* Scene2D::currentIndex(){

    return &index;

}