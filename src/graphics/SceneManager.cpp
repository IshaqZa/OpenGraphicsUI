#include "Scene/SceneManager.h"

void SceneManager::addScene(std::string name, std::shared_ptr<Scene> scene){
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
    if(currScene.empty()) throw std::runtime_error("No scenes added to Scene Manager");
    scenes[currScene]->update(window, (*this));
    // std::cout << "Done updating cycle" << std::endl;
}

void SceneManager::render(){
    if(currScene.empty()) throw std::runtime_error("No scenes added to Scene Manager");
    
    scenes[currScene]->render();
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