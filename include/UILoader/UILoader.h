#ifndef UIMANAGER_CLASS_H
#define UIMANAGER_CLASS_H

#include <ui/ui.h>
#include <Scene/SceneManager.h>
#include <Json/json.hpp>
#include <fstream>
#include <Json/serializer_types.h>

class UILoader {
    private:
        std::unordered_map<std::string, std::function<void()>> actionMap;
        SceneManager* sceneManager;
        void printSceneData(StructScene sceneData);
    public:
        UILoader();
        void loadUiConfig(std::string path);
        void registerFunction(std::string name, std::function<void()> action);
        json loadJsonFile(std::string path);
        // void saveUiConfig(std::shared_ptr<Scene> scene);
};

#endif