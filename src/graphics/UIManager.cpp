#include <UIManager/UIManager.h>

UIManager::UIManager(){
    actionMap["settings"] = &settingsOnClick;
}

std::function<void(SceneManager&)> UIManager::triggerAction(std::string action){
    return actionMap[action];
}

void UIManager::loadUiConfig(SceneManager& sceneManager){
    std::ifstream uiFile("..\\resources\\ui\\ui.json");
    if(!uiFile.is_open()){
        std::cerr << "Failed to load ui configuration file" << std::endl;
        exit(EXIT_FAILURE);
    }

    json uiConfig;
    try{
        uiFile >> uiConfig;
    }catch(const json::parse_error& e){
        std::cerr << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    StructScenes scenesData;
    try{
        scenesData = uiConfig.get<StructScenes>();
    }catch(const json::type_error& e){
        std::cerr << e.what() <<std::endl;
        exit(EXIT_FAILURE);
    }
    
    for(auto& sceneData: scenesData.scenes){
        Scene2D newScene;
        newScene.createVertexData();
        newScene.createShader(sceneData.vertexShaderPath.c_str(), sceneData.fragmentShaderPath.c_str());
        newScene.createVBO();
        newScene.createVAO(sceneData.posSize, sceneData.colorSize, sceneData.texSize, GL_FLOAT);
        newScene.createEventHandler();
        newScene.setBackgroundColor(
            glm::vec4(
                sceneData.backgroundColor[0],
                sceneData.backgroundColor[1],
                sceneData.backgroundColor[2],
                sceneData.backgroundColor[3]
            )
        );

        std::shared_ptr<std::vector<GLfloat>> vertices = newScene.getVertices();
        for(auto& button: sceneData.sceneMembers){
            StructAppearance currApp = button.appearance;
            Texture texture(currApp.textureImagePath.c_str(), GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);
            Appearance2D newApp(
                glm::vec2(currApp.posX, currApp.posY),
                glm::vec2(currApp.width, currApp.height),
                glm::vec4(currApp.color[0], currApp.color[1], currApp.color[2], currApp.color[3]),
                glm::vec2(currApp.texturePosX, currApp.texturePosY),
                texture,
                currApp.renderType
            );

            Button newButton(vertices, newScene.currentIndex(), button.name, std::make_shared<Appearance2D>(newApp), button.shape);
            newScene.addElement(button.name, std::make_shared<MenuElement>(newButton));

            if(!button.events.empty()){
                
            }
        }

        sceneManager.addScene(sceneData.name, std::make_shared<Scene2D>(newScene));
    }

}