#ifndef ACTIONS_CLASS_H
#define ACTIONS_CLASS_H
#include <Scene/SceneManager.h>
#include <shader/shader.h>

extern SceneManager* sceneManager;

namespace actions{
    void settingsOnClick();
    void quitOnClick();
    void playOnHoverEnter();
    void playOnHoverLeave();
    void optionsOnHoverEnter();
    void optionsOnHoverLeave();
    void quitOnHoverEnter();
    void quitOnHoverLeave();
    void empty();
}
#endif