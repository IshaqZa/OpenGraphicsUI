#ifndef SCENE_MANAGER_CLASS_H
#define SCENE_MANAGER_CLASS_H

#include "Scene/Scene.h"

class SceneManager {

    private:
        std::unordered_map<std::string, std::shared_ptr<Scene>> scenes;
        std::string currScene;

    public:
        void addScene(std::string name, std::shared_ptr<Scene> scene);
        void switchCurrentScene(std::string name);
        void update(GLFWwindow* window);
        void render(GLuint texBool);
};

#endif