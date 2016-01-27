#ifndef CALLBACKS_H
#define CALLBACKS_H


#include "GLFW\glfw3.h"

class ICallbacks
{
public:

	//virtual void KeyboardCB(GLFWkeyfun cbKey) {};

	//virtual void PassiveMouseCB(int x, int y) {};

	virtual void RenderSceneCB() {};

	//virtual void MouseCB(OGLDEV_MOUSE Button, OGLDEV_KEY_STATE State, int x, int y) {};
};


#endif