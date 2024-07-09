#include "EventHandler/Actions.h"

SceneManager* sceneManager = SceneManager::getInstance();

void settingsOnClick(){
    sceneManager->switchCurrentScene("Settings");
}