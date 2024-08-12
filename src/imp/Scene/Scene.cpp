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
    isTex = glGetUniformLocation(shader->ID, "isTex");
}

void Scene2D::createEventHandler(){
    if(events) throw std::runtime_error("Event Handler already exists");
    events = std::make_unique<EventHandler>();
}

std::shared_ptr<Shader> Scene::createShader(const char* vertexFile, const char* fragmentFile){
    shader = std::make_shared<Shader>(vertexFile, fragmentFile);
    isTex = glGetUniformLocation(shader->ID, "isTex");
    return shader;
}

void Scene::setBackground(glm::vec4 backgroundColor){
    this->backgroundColor = backgroundColor;
}

void Scene::setBackground(Texture texture, const char* texLocation, GLuint unit){
    backgroundImage = std::make_shared<Texture>(texture);
    backgroundImage->texUnit((*shader), texLocation, unit);
}

void Scene::setBackgroundImage(bool isImage){
    isBackgroundImage = isImage;
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

    if(isBackgroundImage){
        vertices->insert(vertices->begin(), {
            -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 
             1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
        });
    }
    vbo = std::make_shared<VBO>(vertices->data(), vertices->size() * sizeof(vertices));
}

void Scene::activate(){
    glClearColor(backgroundColor.x, backgroundColor.y, backgroundColor.z, backgroundColor.w);

    if(vao == nullptr) throw std::runtime_error("VAO not initialised");
    if(vbo == nullptr) throw std::runtime_error("VBO not initialised");
    vbo->Bind();
    vao->Bind();
}

void Scene2D::render(){
    glClear(GL_COLOR_BUFFER_BIT);
    std::cout << "background color cleared" << std::endl;
    shader->Activate();
    std::cout << "Shader activated" << std::endl;
    vao->Bind();
    std::cout << "VAO bound" << std::endl;

    if(isBackgroundImage){
        backgroundImage->Bind();
        gl
        glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
        backgroundImage->Unbind();
    }
    
    try{
        for(const auto& x : elementArray){
            if(!x.second){
                throw std::runtime_error("Empty element pointer");
            }
            std::cout << "rendering: " << x.first << std::endl;
            x.second->draw(isTex);
        }
        vao->Unbind();
    }catch(std::runtime_error& e){
        std::cerr << e.what() << std::endl;
        std::cout << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
}

void Scene2D::update(GLFWwindow* window){
    events->processInputs(window);
    std::cout << "Processed user inputs" << std::endl;
    // std::cout << "update insdie 2D scene" << std::endl;
    
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
        case EVENT_ON_CLICK_UP:
            events->addOnClickUpElement(elementArray[elementName], action);
        break;
        case EVENT_ON_CLICK_DOWN:
            events->addOnClickDownElement(elementArray[elementName], action);
        break;
        case EVENT_ON_HOVER_ENTER:
            events->addOnHoverEnterElement(elementArray[elementName], action);
        break;
        case EVENT_ON_HOVER_LEAVE:
            events->addOnHoverLeaveElement(elementArray[elementName], action);
    }
}

std::shared_ptr<Shader> Scene::getShaderProgram(){
    return shader;
}

std::shared_ptr<MenuElement> Scene2D::getElementByName(std::string name){ return elementArray[name]; }