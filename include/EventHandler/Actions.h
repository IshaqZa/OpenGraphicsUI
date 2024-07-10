#ifndef ACTIONS_CLASS_H
#define ACTIONS_CLASS_H
#include <Scene/SceneManager.h>

extern SceneManager* sceneManager;
namespace actions{
    void settingsOnClick();
    void quitOnClick();
    void playOnHover();
    void empty();
}
#endif