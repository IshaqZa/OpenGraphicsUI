#ifndef UIMANAGER_CLASS_H
#define UIMANAGER_CLASS_H

#include <ui/ui.h>
#include <Scene/Scene.h>
#include <Json/json.hpp>

class UIManager {
    public:
        std::vector<std::shared_ptr<MenuElement>> loadUiConfig(std::shared_ptr<Scene> scene);
        void saveUiConfig(std::shared_ptr<Scene> scene);
        void triggerActions(std::shared_ptr<Scene> scene);
};

#endif