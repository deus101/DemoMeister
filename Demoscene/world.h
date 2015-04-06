#ifndef WORLD_H
#define WORLD_H

#include <glload/gl_3_3.hpp>
#include <glload/gl_load.hpp>
////
////#include "node.h"
////#include "composite.h"
////#include "circle.h"
////#include "shaders.h"
//#include "rigidBody.h"

#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

#include <set>
#include <time.h>
#include <cstdlib>


//#include <windows.h>



#include <gl\freeglut.h>


//#include "gbuffer.h"
#include "util.h"
#include "bass.h"

#include "sync.h"


#include "SceneGraph\node.h"
#include "SceneGraph\camera.h"
#include "SceneGraph\composite.h"
#include "SceneGraph\modelNode.h"





class world
{



public:


	


	world();


	void RenderScene();

	void Water();

	void DrawStage();

	void InitLights();

	void AfterInit();

	void HyperSpace();

	void HyperPlane();

	void HyperHex();

public:
	int WindowID;

	//NS_SG::composite o_loader;
	// void keyDown(int key, int x, int y);
	//
	// void keyRelease(int key, int x, int y);
	//


	//void AddCue();





};



#endif
