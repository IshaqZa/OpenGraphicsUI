#include "Scene/SceneManager.h"

SceneManager* SceneManager::instancePtr = nullptr;

void SceneManager::addScene(std::string name, std::shared_ptr<Scene2D> scene){
    if(scenes.count(name) > 0) throw std::runtime_error("Scene already exists");
    if(currScene.empty()) currScene = name;
    scenes[name] = scene;
}

void SceneManager::switchCurrentScene(std::string name){
    if(scenes.count(name) > 0){
        currScene = name;
        scenes[currScene]->activate();
    } else {
        throw std::runtime_error("Scene does not exist");
    }
}

void SceneManager::update(GLFWwindow* window){
    try{
        if(currScene.empty()) throw std::runtime_error("No scenes added to Scene Manager");
        if(!scenes[currScene]) throw std::runtime_error("Empty scene pointer");
        scenes[currScene]->update(window);

    }catch(std::runtime_error& e){
        std::cerr << e.what() << std::endl;
        std::cout << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cout << "Done updating cycle" << std::endl;
}

void SceneManager::render(){
    if(currScene.empty()) throw std::runtime_error("No scenes added to Scene Manager");
    
    std::cout << "starting current scene rendering" << std::endl;
    try{
        if(!scenes[currScene]) throw std::runtime_error("current scene pointer is empty");
        scenes[currScene]->render();
        std::cout << "Done rendering current scene" << std::endl;
    }catch(std::runtime_error& e){
        std::cerr << e.what() << std::endl;
        std::cout << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }catch(std::exception& e){
        std::cerr << e.what() << std::endl;
        std::cout << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
    // std::cout << "Done rendering cycle" << std::endl;
}

std::shared_ptr<Shader> SceneManager::getCurrentSceneShader(){
    return scenes[currScene]->getShaderProgram();
}

void SceneManager::printAllScenes(){
    for(auto& scene: scenes){
        if(scene.second == nullptr) std::cout << "Scene is empty!" << std::endl;
        std::cout << scene.first << std::endl;
    }
}

SceneManager* SceneManager::getInstance(){
    if(instancePtr == nullptr){
        instancePtr = new SceneManager();
        return instancePtr;
    }
    else return instancePtr;
}

std::shared_ptr<std::vector<GLfloat>> SceneManager::getCurrSceneVertexData(){
    return scenes[currScene]->getVertices();
}

std::shared_ptr<Scene2D> SceneManager::getCurrentScene(){
    return scenes[currScene];
}