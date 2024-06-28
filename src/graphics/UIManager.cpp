#include <UIManager/UIManager.h>

std::vector<std::shared_ptr<MenuElement>> UIManager::loadUiConfig(std::shared_ptr<Scene> scene){
    std::ifstream uiFile("..\\resources\\ui\\ui.json");

    if(!uiFile.is_open()){
        std::cerr << "Failed to load ui configuration file" << std::endl;
        exit(EXIT_FAILURE);
    }

    

}