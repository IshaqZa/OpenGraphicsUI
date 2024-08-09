#include "EventHandler/Actions.h"

SceneManager* sceneManager = SceneManager::getInstance();

void actions::settingsOnClick(){
    sceneManager->switchCurrentScene("Settings");
}

void actions::quitOnClick(){
    exit(EXIT_SUCCESS);
}

void actions::playOnHover(){
    std::cout << "Mouse within bounds of play" << std::endl;
}

void actions::empty(){}