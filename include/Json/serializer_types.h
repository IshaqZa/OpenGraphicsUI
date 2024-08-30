#ifndef SERIALIZER_CLASS_H
#define SERIALIZER_CLASS_H

#include <glad/glad.h>
#include <vector>
#include <string>
#include <unordered_map>
#include <EventHandler/EventType.h>
#include <Json/json.hpp>
#include <ui/ui.h>

struct StructEvent {
    EventType event;
    std::string action;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(StructEvent, event, action);
};

struct StructAppearance{
    GLfloat posX, posY;
    GLfloat width, height;
    GLfloat color[4];
    GLfloat texturePosX, texturePosY;
    std::string textureImagePath;
    int renderType;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(StructAppearance, posX, posY, width, height, color, texturePosX, texturePosY, textureImagePath, renderType);
};

struct StructButton{

    std::string name;
    std::vector<StructEvent> events;
    StructAppearance appearance;
    Shapes shape;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(StructButton, name, events, appearance, shape);
};

struct StructScene {
    std::string name;
    bool isBackgroundImage;
    std::vector<StructButton> sceneMembers;
    std::string vertexShaderPath;
    std::string fragmentShaderPath;
    GLfloat backgroundColor[4];
    std::string backgroundImagePath;
    int posSize, colorSize, texSize;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(StructScene, name, isBackgroundImage, sceneMembers, vertexShaderPath, fragmentShaderPath, backgroundColor, backgroundImagePath, posSize, colorSize, texSize);
};

struct StructScenes{
    std::vector<StructScene> scenes;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(StructScenes, scenes);
};

#endif