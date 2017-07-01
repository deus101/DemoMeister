#ifndef WORLD_HPP
#define WORLD_HPP


/*
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
*/

//#include <windows.h>






//#include "Rendrer\gbuffer.h"
#include "util.h"
//#include "bass.h"

//#include "sync.h"

#include "Rendrer\base_buffer.h"
#include "Rendrer\gbuffer.h"
#include "Rendrer\aobuffer.h"

#include "SceneGraph\node.h"
#include "SceneGraph\objTransform.h"
//#include "Effect\renderPacket.h"
#include "SceneGraph\camera.h"
#include "SceneGraph\composite.h"
//#include "SceneGraph\modelNode.h"
#include "Effect\renderPacket.h"


typedef boost::shared_ptr< NS_SG::composite >  compoPointer;
typedef std::vector< NS_EFF::renderPacket* > MasterList_Effects;
typedef std::vector< base_buffer* > MasterList_Passes;

class world
{



public:
	MasterList_Passes BufferContainer;
	
	MasterList_Effects EffectPackets;


	//remember destructors, carefull with utilizing the constructor before opengl is initialized,
	//the way its setup no it wont.

	world();

	//all these should be virtual
	void AddPass();

	void AddNode();

	void AddEffect();

	//This is one of the main reasons Im doing this, I want a material system
	void AddAsset();
	void RetriveAsset();
	//This is one of the main reasons Im doing this, I want a material system
	void AddMaterial();
	void RetriveMaterial();

	//I want something to check for duplicates, materials and textures(materials can be different but use the same)
	//at some point this might be what I need the world class for, a hackers space so I dont have to create a class for
	//everything like procedural textures.


	//with an id argument perhaps, thinking gnu rocket should sync up here
	void HackerSpace();



	//either initialization of passes, packets and loading on models can be done on the fly
	//void PreInit();
	void AfterInit();
	//I could set the soundtrack setup here but leave that for later

//private:
	//containers for textures, assets, packets, buffers,
public:
	//int WindowID;
	boost::shared_ptr<NS_SG::composite>  o_loader;
	//boost::weak_ptr<NS_SG::node>  anchor;
	//NS_SG::composite o_loader;
	// void keyDown(int key, int x, int y);
	//
	// void keyRelease(int key, int x, int y);
	//
	unsigned int ResolutionX;
	unsigned int ResolutionY;

	//void AddCue();


};



#endif
