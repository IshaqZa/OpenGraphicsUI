#include "EventHandler/Actions.h"

SceneManager* sceneManager = SceneManager::getInstance();

void actions::settingsOnMouseUp(){
    sceneManager->switchCurrentScene("Settings");
}

void actions::quitOnMouseUp(){
    exit(EXIT_SUCCESS);
}

void actions::playOnHoverEnter(){
    std::unordered_map<std::string, std::shared_ptr<Scene2D>> scenes = sceneManager->getAllScenes();
    std::cout << "Hovered Over button" << std::endl;
    if(scenes.empty()) std::cout << "Scenes is empty" << std::endl;
    std::shared_ptr<Scene2D> scene = scenes["Main Menu"];
    std::cout << "Returned Main Menu Scene" << std::endl;
    std::shared_ptr<Shader> currShader = scene->getShaderProgram();
    std::cout << "Returned active shader" << std::endl;
    std::shared_ptr<MenuElement> btn = scene->getElementByName("Play");
    std::cout << "Returned Play Button" << std::endl;
    Texture tex("../resources/textures/START blue.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);
    btn->setTexture(tex, (*currShader), "tex", 0);

}

void actions::playOnHoverLeave(){
    std::unordered_map<std::string, std::shared_ptr<Scene2D>> scenes = sceneManager->getAllScenes();
    std::cout << "Buttoned hovered left" << std::endl;
    std::shared_ptr<Scene2D> scene = scenes["Main Menu"];
    std::cout << "retrieved main menu" << std::endl;
    std::shared_ptr<Shader> currShader = scene->getShaderProgram();
    std::cout << "retrieved current active shader" << std::endl;
    std::shared_ptr<MenuElement> btn = scene->getElementByName("Play");
    std::cout << "retrieved play button" << std::endl;
    Texture tex("../resources/textures/START purple.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);
    std::cout << "Created texture" << std::endl;
    btn->setTexture(tex, (*currShader), "tex", 0);
    std::cout << "set texture" << std::endl;
}


void actions::settingsOnHoverEnter(){
    std::unordered_map<std::string, std::shared_ptr<Scene2D>> scenes = sceneManager->getAllScenes();
    std::cout << "Hovered Over button" << std::endl;
    if(scenes.empty()) std::cout << "Scenes is empty" << std::endl;
    std::shared_ptr<Scene2D> scene = scenes["Main Menu"];
    std::cout << "Returned Main Menu Scene" << std::endl;
    std::shared_ptr<Shader> currShader = scene->getShaderProgram();
    std::cout << "Returned active shader" << std::endl;
    std::shared_ptr<MenuElement> btn = scene->getElementByName("options");
    std::cout << "Returned Play Button" << std::endl;
    Texture tex("../resources/textures/OPTIONS blue.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);
    btn->setTexture(tex, (*currShader), "tex", 0);
}
void actions::settingsOnHoverLeave(){
    std::unordered_map<std::string, std::shared_ptr<Scene2D>> scenes = sceneManager->getAllScenes();
    std::cout << "Hovered Over button" << std::endl;
    if(scenes.empty()) std::cout << "Scenes is empty" << std::endl;
    std::shared_ptr<Scene2D> scene = scenes["Main Menu"];
    std::cout << "Returned Main Menu Scene" << std::endl;
    std::shared_ptr<Shader> currShader = scene->getShaderProgram();
    std::cout << "Returned active shader" << std::endl;
    std::shared_ptr<MenuElement> btn = scene->getElementByName("options");
    std::cout << "Returned Play Button" << std::endl;
    Texture tex("../resources/textures/OPTIONS purple.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);
    btn->setTexture(tex, (*currShader), "tex", 0);
}
void actions::quitOnHoverEnter(){
    std::unordered_map<std::string, std::shared_ptr<Scene2D>> scenes = sceneManager->getAllScenes();
    std::cout << "Hovered Over button" << std::endl;
    if(scenes.empty()) std::cout << "Scenes is empty" << std::endl;
    std::shared_ptr<Scene2D> scene = scenes["Main Menu"];
    std::cout << "Returned Main Menu Scene" << std::endl;
    std::shared_ptr<Shader> currShader = scene->getShaderProgram();
    std::cout << "Returned active shader" << std::endl;
    std::shared_ptr<MenuElement> btn = scene->getElementByName("Quit");
    std::cout << "Returned Play Button" << std::endl;
    Texture tex("../resources/textures/QUIT blue.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);
    btn->setTexture(tex, (*currShader), "tex", 0);
}
void actions::quitOnHoverLeave(){
    std::unordered_map<std::string, std::shared_ptr<Scene2D>> scenes = sceneManager->getAllScenes();
    std::cout << "Hovered Over button" << std::endl;
    if(scenes.empty()) std::cout << "Scenes is empty" << std::endl;
    std::shared_ptr<Scene2D> scene = scenes["Main Menu"];
    std::cout << "Returned Main Menu Scene" << std::endl;
    std::shared_ptr<Shader> currShader = scene->getShaderProgram();
    std::cout << "Returned active shader" << std::endl;
    std::shared_ptr<MenuElement> btn = scene->getElementByName("Quit");
    std::cout << "Returned Play Button" << std::endl;
    Texture tex("../resources/textures/QUIT purple.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);
    btn->setTexture(tex, (*currShader), "tex", 0);
}

void actions::settingsOnMouseDown(){
    std::unordered_map<std::string, std::shared_ptr<Scene2D>> scenes = sceneManager->getAllScenes();
    std::cout << "All scenes retrieved" << std::endl;
    if(scenes.empty()) std::cout << "scenes is empty" << std::endl;
    std::shared_ptr<Scene2D> currScene = scenes["Main Menu"];
    std::cout << "Main Menu scene retrieved" << std::endl;
    std::shared_ptr<Shader> currShader = currScene->getShaderProgram();
    std::cout << "Shader retrieved" << std::endl;
    std::shared_ptr<MenuElement> btn = currScene->getElementByName("options");
    std::cout << "Options button retrieved" << std::endl;
    Texture tex("../resources/textures/OPTIONS red.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_UNSIGNED_BYTE);
    btn->setTexture(tex, (*currShader), "tex", 0);
    std::cout << "texture set" << std::endl;
}

void actions::empty(){}