#include <Scene/Scene.h>

void Scene::createVertexData(){
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
}

void Scene2D::createEventHandler(){
    if(events) throw std::runtime_error("Event Handler already exists");
    events = std::make_unique<EventHandler>();
}

std::shared_ptr<Shader> Scene::createShader(const char* vertexFile, const char* fragmentFile){
    shader = std::make_shared<Shader>(vertexFile, fragmentFile);
    return shader;
}

void Scene::setBackgroundColor(glm::vec4 backgroundColor){
    this->backgroundColor = backgroundColor;
}

void Scene2D::addElement(std::string name, std::shared_ptr<MenuElement> element) {
    elementArray[name] = element;
}

void Scene::createVAO(int posSize, int colorSize, int texSize, GLenum type){

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

void Scene::createVBO(){
    vbo = std::make_shared<VBO>(vertices->data(), vertices->size() * sizeof(vertices));
}

void Scene::activate(){
    glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, backgroundColor.w);
    if(vao == nullptr) throw std::runtime_error("VAO not initialised");
    if(vbo == nullptr) throw std::runtime_error("VBO not initialised");
    vao->Bind();
    vbo->Bind();
}

void Scene2D::render(){
    GLuint texBool = glGetUniformLocation(shader->ID, "isTex");
    if(texBool < 0) {
        std::cout << "Error retrieving tex bool" << std::endl;
        exit(EXIT_FAILURE);
    }
    try{
        for(const auto& x : elementArray){
            if(!x.second){
                throw std::runtime_error("Empty element pointer");
            }
            std::cout << "rendering: " << x.first << std::endl;
            x.second->draw(texBool);
        }
    }catch(std::runtime_error& e){
        std::cerr << e.what() << std::endl;
        std::cout << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Scene2D::update(GLFWwindow* window){
    events->processInputs(window);
    // std::cout << "update insdie 2D scene" << std::endl;
    glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, backgroundColor.w);
    glClear(GL_COLOR_BUFFER_BIT);
    shader->Activate();
    vao->Bind();
}

std::shared_ptr<std::vector<GLfloat>> Scene::getVertices(){
    return vertices;
}

unsigned int* Scene::currentIndex(){

    return &index;

}

void Scene2D::addEventListener(EventType eventType, std::string elementName, std::function<void()> action){
    if(!events) throw std::runtime_error("Event Handler has not been created for this scene");
    if(!elementArray[elementName]) throw std::runtime_error("No such element");

    switch(eventType){
        case EVENT_ON_CLICK:
            events->addOnClickElement(elementArray[elementName], action);
        break;
    }
}

std::shared_ptr<Shader> Scene::getShaderProgram(){
    return shader;
}
