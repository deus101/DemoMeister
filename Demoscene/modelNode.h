#include "assetNode.h"
#include "shaders.h"
#include "model.h"

namespace sg{
	namespace noder{

		class modelNode : public assetNode
		{
		public:
			modelNode(std::string name, engine::Mesh *mesh, engine::Effect *effect) :
				DrawableNode(name),
				mesh(mesh),
				effect(effect),
				transparent(false)
			{}

			bool isTransparent()
			{
				return transparent;
			}

			void draw()
			{
				assert(NULL != effect);
				assert(NULL != mesh);
				effect->draw(mesh);
			}

			bool transparent;
			NS_MESH::MESH *mesh;
			shade



	}



}