#ifndef UIMANAGER_CLASS_H
#define UIMANAGER_CLASS_H

#include <ui/ui.h>
#include <Scene/SceneManager.h>
#include <Json/json.hpp>
#include <fstream>
#include <Json/serializer_types.h>
#include <EventHandler/Actions.h>

class UIManager {
    private:
        std::unordered_map<std::string, std::function<void(SceneManager&)>> actionMap;
    public:
        UIManager();
        void loadUiConfig(SceneManager& sceneManager);
        std::function<void(SceneManager&)> triggerAction(std::string action);
        // void saveUiConfig(std::shared_ptr<Scene> scene);
};

#endif