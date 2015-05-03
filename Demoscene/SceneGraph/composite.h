#ifndef COMPOSITE_HPP
#define COMPOSITE_HPP

//#include "world.h"
#include <iostream>
//#include "Timer.h"
#include "boost/shared_ptr.hpp"
#include <vector>
#include "node.h"
#include "objTransform.h"

//Hvorfor trengte jeg denne?
#include "../Engine/model.h"

#include "../util.h"
#include "camera.h"

//#include "sync.h"



//#include "bass.h"


namespace NS_SG{

		class objectAnim
		{
		public:
			NS_VEC::VEC3   getPos(float time);
			NS_VEC::QUAT getRot(float time);
			NS_VEC::VEC3   getScale(float time);

			void setPosKeyFrame(float time, const NS_VEC::VEC3  &pos)
			{
				posTrack[time] = pos;
			}

			void setRotKeyFrame(float time, const NS_VEC::QUAT &rot)
			{
				rotTrack[time] = rot;
			}

			void setScaleKeyFrame(float time, const	NS_VEC::VEC3 &scale)
			{
				scaleTrack[time] = scale;
			}

		private:
			std::map<float, NS_VEC::VEC3> posTrack;
			std::map<float, NS_VEC::QUAT> rotTrack;
			std::map<float, NS_VEC::VEC3> scaleTrack;
		};

//ubrukelig?
//Kansje jeg kan bruke den til noe annet men kompositt slik kan ikke brukes i en scanegraph 
//fordi data og noder bør holdes seperat.


//OOOOR! I can  use the actors system as leafnodes.

		class composite : public node
		{
		//Timer clock;
		public:

			composite(std::string name) : node(name) {}
			
			virtual NodeType getType() { return NODE_COMPOSER; }
		

			void anim(float time);
			//double *row;
			//sync_device *rocket;
			//legg se og få brukt referanse noden til denne
			
		
			//nodePtr findCamera(const std::string &name)
			//{
			//	//reinterpt her?
			//	nodePtr cam = findNodeByType<nodePtr, NODE_CAMERA>(name);
			//	//return findNodeByType<camera, NODE_CAMERA>(name);
			//	return cam;
			//}

			nodePtr findNode(const std::string &name)
			{
				return findChild(name);
			}

			void addObjectAnime(objTransform *node, const objectAnim &anim)
			{
				animTracks[node] = anim;
			}

			//void AddActor(GLfloat, GLfloat, GLfloat);
			
			void AddActor(int, GLfloat, GLfloat, GLfloat);
			void AddActor(NS_VEC::VEC3, std::string, std::string, GLfloat, GLfloat, GLfloat);
			void Magic(bool);
			void DrawAll();
			void StartTimer();
			void SortTracks();



		private:
			std::map<objTransform*, objectAnim> animTracks;

			template <typename T, NodeType t>
			T findNodeByType(const std::string &name)
			{
				// find node
				//node *oNode = findChild(name);
				nodePtr oNode = findChild(name);
				if (NULL == oNode) return NULL;

				// type check
				if (oNode->getType() != t) return NULL;
				return reinterpret_cast<T>(oNode);
			};

		};




	
}


#endif