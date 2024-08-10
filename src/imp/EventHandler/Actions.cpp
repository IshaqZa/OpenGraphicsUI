#include "EventHandler/Actions.h"

SceneManager* sceneManager = SceneManager::getInstance();

void actions::settingsOnClick(){
    sceneManager->switchCurrentScene("Settings");
}

void actions::quitOnClick(){
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
    Texture tex("../resources/textures/START blue.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
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
    Texture tex("../resources/textures/START purple.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    std::cout << "Created texture" << std::endl;
    btn->setTexture(tex, (*currShader), "tex", 0);
    std::cout << "set texture" << std::endl;
}


void actions::optionsOnHoverEnter(){
    std::unordered_map<std::string, std::shared_ptr<Scene2D>> scenes = sceneManager->getAllScenes();
    std::cout << "Hovered Over button" << std::endl;
    if(scenes.empty()) std::cout << "Scenes is empty" << std::endl;
    std::shared_ptr<Scene2D> scene = scenes["Main Menu"];
    std::cout << "Returned Main Menu Scene" << std::endl;
    std::shared_ptr<Shader> currShader = scene->getShaderProgram();
    std::cout << "Returned active shader" << std::endl;
    std::shared_ptr<MenuElement> btn = scene->getElementByName("options");
    std::cout << "Returned Play Button" << std::endl;
    Texture tex("../resources/textures/OPTIONS blue.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    btn->setTexture(tex, (*currShader), "tex", 0);
}
void actions::optionsOnHoverLeave(){
    std::unordered_map<std::string, std::shared_ptr<Scene2D>> scenes = sceneManager->getAllScenes();
    std::cout << "Hovered Over button" << std::endl;
    if(scenes.empty()) std::cout << "Scenes is empty" << std::endl;
    std::shared_ptr<Scene2D> scene = scenes["Main Menu"];
    std::cout << "Returned Main Menu Scene" << std::endl;
    std::shared_ptr<Shader> currShader = scene->getShaderProgram();
    std::cout << "Returned active shader" << std::endl;
    std::shared_ptr<MenuElement> btn = scene->getElementByName("options");
    std::cout << "Returned Play Button" << std::endl;
    Texture tex("../resources/textures/OPTIONS purple.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
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
    Texture tex("../resources/textures/QUIT blue.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
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
    Texture tex("../resources/textures/QUIT purple.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
    btn->setTexture(tex, (*currShader), "tex", 0);
}

void actions::empty(){}