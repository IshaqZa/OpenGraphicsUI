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
    uiFile.close();

    // std::cout << uiConfig.dump(4) << std::endl;

    StructScenes scenesData;
    try{
        if(!uiConfig.contains("scenes")) throw std::runtime_error("scenes is not found");
        if(uiConfig["scenes"].is_null()) throw std::runtime_error("scenes is empty/null");
        scenesData = uiConfig.template get<StructScenes>();

    } catch (const std::runtime_error& e) {
        std::cerr << "Runtime Error: " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }catch(const json::type_error& e){
        std::cerr << "Error parsing JSON: " << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
    
    for(auto& sceneData: scenesData.scenes){

        // std::cout << "Current Scene Data:" << std::endl;
        // std::cout << "Scene Name: " << sceneData.name << std::endl;
        // std::cout << "Scene vertex shader: " << sceneData.vertexShaderPath << std::endl;
        // std::cout << "Scene fragment shader: " << sceneData.fragmentShaderPath << std::endl;
        // std::cout << "Background color data: " << sceneData.backgroundColor[0] << ", " << sceneData.backgroundColor[1] << ", " << sceneData.backgroundColor[2] << ", " << sceneData.backgroundColor[3] << std::endl;
        // std::cout << "vertex data position offset: " << sceneData.posSize << ", " << "vertex data color offset: " << sceneData.colorSize << ", " << "vertex data texture offset: " << sceneData.texSize << std::endl;

        // std::cout << "Creation of scene: " << sceneData.name << std::endl;
        std::shared_ptr<Scene2D> newScene;
        newScene->createVertexData();
        newScene->createShader(sceneData.vertexShaderPath.c_str(), sceneData.fragmentShaderPath.c_str());
        newScene->createVBO();
        newScene->createVAO(sceneData.posSize, sceneData.colorSize, sceneData.texSize, GL_FLOAT);
        newScene->createEventHandler();
        newScene->setBackgroundColor(
            glm::vec4(
                sceneData.backgroundColor[0],
                sceneData.backgroundColor[1],
                sceneData.backgroundColor[2],
                sceneData.backgroundColor[3]
            )
        );

        std::shared_ptr<std::vector<GLfloat>> vertices = newScene->getVertices();
        for(auto& button: sceneData.sceneMembers){
            // std::cout << "current button data:" << std::endl;
            // std::cout << "Button name: " << button.name << std::endl;
            // std::cout << "Button shape: " << button.shape << std::endl;
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

            std::shared_ptr<Button> newButton = std::make_shared<Button>(vertices, newScene->currentIndex(), button.name, std::make_shared<Appearance2D>(newApp), button.shape);

            if(newButton == nullptr) std::cerr << "Error making button pointer" << std::endl;
            newScene->addElement(button.name, newButton);
            if(!button.events.empty()){
                for(auto& event : button.events){
                    newScene->addEventListener(event.event, button.name, triggerAction(event.action));
                }
            }
        }

        sceneManager.addScene(sceneData.name, newScene);
    }

}