#ifndef UIMANAGER_CLASS_H
#define UIMANAGER_CLASS_H

#include <ui/ui.h>
#include <Scene/SceneManager.h>
#include <Json/json.hpp>
#include <fstream>
#include <Json/serializer_types.h>
#include <EventHandler/Actions.h>

class UILoader {
    private:
        std::unordered_map<std::string, std::function<void()>> actionMap;
        SceneManager* sceneManager = SceneManager::getInstance();
    public:
        UILoader();
        void loadUiConfig();
        std::function<void()> triggerAction(std::string action);
        // void saveUiConfig(std::shared_ptr<Scene> scene);
};

#endif