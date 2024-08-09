#include <Scene/Scene2D.h>

Scene2D::Scene2D() : Scene() {
    events = std::make_unique<EventHandler>();
}

void Scene2D::addElement(std::string name, std::shared_ptr<MenuElement> element) {
    elementArray[name] = element;
}

std::shared_ptr<MenuElement> Scene2D::getElementByName(std::string name){ return elementArray[name]; }

void Scene2D::render(){
    glClear(GL_COLOR_BUFFER_BIT);
    std::cout << "background color cleared" << std::endl;
    shader->Activate();
    std::cout << "Shader activated" << std::endl;
    vao->Bind();
    std::cout << "VAO bound" << std::endl;
    
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
    // std::cout << "update insdie 2D scene" << std::endl;
    
}

void Scene2D::addEventListener(EventType eventType, std::string elementName, std::function<void()> action){
    if(!events) throw std::runtime_error("Event Handler has not been created for this scene");
    if(!elementArray[elementName]) throw std::runtime_error("No such element");

    switch(eventType){
        case EVENT_ON_CLICK:
            events->addOnClickElement(elementArray[elementName], action);
        break;
        case EVENT_ON_HOVER:
            events->addOnHoverElement(elementArray[elementName], action);
        break;
    }
}