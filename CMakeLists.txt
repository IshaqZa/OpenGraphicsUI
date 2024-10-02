cmake_minimum_required(VERSION "3.10")
Project(OpenUI)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/build")

add_library(OpenUI
    src/external/glad.c
    src/imp/Buffer/EBO.cpp
    src/imp/Buffer/VAO.cpp
    src/imp/Buffer/VBO.cpp
    src/imp/EventHandler/EventHandler.cpp
    src/imp/UI/ui.cpp
    src/imp/Texture/texture.cpp
    src/imp/Shader/shader.cpp
    src/imp/Scene/Scene.cpp
    src/imp/Scene/SceneManager.cpp
    src/imp/Shape/Shape.cpp
    src/imp/UI/UIbuilder.cpp
    src/imp/UI/UIFactory.cpp
    src/external/stb_image.cpp
    src/imp/Debugger/Debugger.cpp
)
target_include_directories(OpenUI PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")

find_package(GLFW3 REQUIRED)
target_link_libraries(OpenUI PRIVATE glfw)

if(UNIX)
    target_link_libraries(OpenUI PRIVATE X11 Xrandr Xi pthread dl m)
endif()

Project(tryout)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/build")

add_executable(tryout
    main.cpp
    src/external/glad.c
    src/imp/Debugger/Debugger.cpp
    src/imp/Buffer/EBO.cpp
    src/imp/Buffer/VAO.cpp
    src/imp/Buffer/VBO.cpp
    src/imp/EventHandler/EventHandler.cpp
    src/imp/EventHandler/Actions.cpp
    src/imp/UI/ui.cpp
    src/imp/Texture/texture.cpp
    src/imp/Shader/shader.cpp
    src/imp/Scene/Scene.cpp
    src/imp/Scene/SceneManager.cpp
    src/imp/Shape/Shape.cpp
    src/imp/UI/UIbuilder.cpp
    src/imp/UI/UIFactory.cpp
    src/external/stb_image.cpp
)
target_include_directories(tryout PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")

find_package(GLFW3 REQUIRED)
target_link_libraries(tryout PRIVATE glfw)

if(UNIX)
    target_link_libraries(tryout PRIVATE X11 Xrandr Xi pthread dl m)
endif()