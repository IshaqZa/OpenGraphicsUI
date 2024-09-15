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

    if(isTex == -1) {
        std::cerr << "isTex does not exist in shader program in createShader()" << std::endl;
        exit(EXIT_FAILURE);
    }

    GLenum error = glGetError();

    return shader;
}

void Scene::setBackground(glm::vec4 backgroundColor){
    this->backgroundColor = backgroundColor;
}

void Scene::setBackground(Texture texture, const char* texLocation, GLuint unit){
    backgroundImage = std::make_shared<Texture>(texture);
    backgroundImage->texUnit((*shader), texLocation, unit);
    vertices->insert(vertices->begin(), {
            -1.0f, 1.0f, 0.0f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, // top left
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
            1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.5f, 1.0f, 1.0f, 0.0f, // bottom right
             1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f // top right
        });
    backgroundIndex = index;
    GLuint normBackgroundIndex = backgroundIndex/9;
    std::vector<GLuint> indices = {
        normBackgroundIndex + 0, normBackgroundIndex + 3, normBackgroundIndex + 1,
        normBackgroundIndex + 3, normBackgroundIndex + 1, normBackgroundIndex + 2
    };

    backgroundEBO = std::make_shared<EBO>(indices.data(), indices.size() * sizeof(indices));

    index += 36;
}

void Scene::setBackgroundImage(bool isImage){
    isBackgroundImage = isImage;
}

void Scene2D::addElement(std::string name, std::shared_ptr<Element> element) {
    elementArray[name] = element;
}

void Scene::createVAO(int posSize, int colorSize, int texSize, GLenum type){

    
    if(vbo){
        vao = std::make_shared<VAO>();
        vao->Bind();

        if(posSize > 0) vao->linkAttrib(*vbo, 0, posSize, type, (posSize + colorSize + texSize) * sizeof(float), reinterpret_cast<void*>(0));
        if(colorSize > 0) vao->linkAttrib(*vbo, 1, colorSize, type, (posSize + colorSize + texSize) * sizeof(float), reinterpret_cast<void*>(posSize * sizeof(float)));
        if(texSize >  0) vao->linkAttrib(*vbo, 2, texSize, type, (posSize + colorSize + texSize) * sizeof(float), reinterpret_cast<void*>((colorSize + posSize) * sizeof(float)));
        
        vao->Unbind();
    } else {
        throw std::runtime_error("VBO not initialised when creating VAO!");
    }
    
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

void Scene2D::render(){
    glClear(GL_COLOR_BUFFER_BIT);
    std::cout << "background color cleared" << std::endl;
    shader->Activate();
    std::cout << "Shader activated" << std::endl;
    vao->Bind();
    std::cout << "VAO bound" << std::endl;

    if(isBackgroundImage){
        backgroundEBO->Bind();
        backgroundImage->Bind();
        glUniform1i(isTex, 1);
        GLuint normIndex = backgroundIndex / 9;
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        backgroundImage->Unbind();
        backgroundEBO->Unbind();
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
    if(!elementArray[elementName]) throw std::runtime_error("No such element to add event listener");

    events->addElementEvent(eventType, elementArray[elementName], action);
}

std::shared_ptr<Shader> Scene::getShaderProgram(){
    return shader;
}

std::shared_ptr<Element> Scene2D::getElementByName(std::string name){ return elementArray[name]; }