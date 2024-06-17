#ifndef SCENE_MANAGER_CLASS_H
#define SCENE_MANAGER_CLASS_H

#include "Scene/Scene.h"

class SceneManager {

    private:
        std::unordered_map<std::string, std::unique_ptr<Scene>> scenes;
        Scene* currScene;

    public:
        void addScene(std::string name, std::unique_ptr<Scene> scene);
        void switchCurrentScene(std::string name);
        void update();
        void render();
};

#endif