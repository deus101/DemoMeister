#include "assetNode.h"
#include "shaders.h"
#include "model.h"
#include "renderPacket.h"

namespace sg{
	namespace noder{ 

		class modelNode : public assetNode
		{
		public:
			modelNode(std::string name, model  *mesh, renderPacket *tech) :
				assetNode(name),
				Model(mesh),
				Magic(tech),
				transparent(false)
			{}

			bool isTransparent()
			{
				return transparent;
			}

			void draw()
			{
				M3DMatrix44f ABS;
				getAbsoluteTransform(ABS);
				assert(NULL != Model);
				assert(NULL != Magic);
				Magic->Draw(Model, ABS);
			}

			bool transparent;

			model *Model;
			renderPacket *Magic;

		};

	}



}