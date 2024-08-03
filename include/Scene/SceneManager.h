#ifndef SCENE_MANAGER_CLASS_H
#define SCENE_MANAGER_CLASS_H

#include "Scene/Scene.h"

class Scene;
class EventHandler;

class SceneManager {

    private:
        std::unordered_map<std::string, std::shared_ptr<Scene2D>> scenes;
        std::string currScene;
        static SceneManager* instancePtr;

        SceneManager(){}
    public:
        SceneManager(const SceneManager& obj) = delete;

        static SceneManager* getInstance();

        void addScene(std::string name, std::shared_ptr<Scene2D> scene);
        std::shared_ptr<std::vector<GLfloat>> getCurrSceneVertexData();
        void switchCurrentScene(std::string name);
        std::shared_ptr<Shader> getCurrentSceneShader();
        void update(GLFWwindow* window);
        void render();
        void printAllScenes();
        std::shared_ptr<Scene2D> getCurrentScene();
        std::unordered_map<std::string, std::shared_ptr<Scene2D>> getAllScenes();
};

#endif