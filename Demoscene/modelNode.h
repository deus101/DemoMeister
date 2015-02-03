#include "assetNode.h"
#include "shaders.h"
#include "model.h"
#include "renderPacket.h"

namespace sg{
	namespace noder{

		class modelNode : public assetNode
		{
		public:
			modelNode(std::string name, model  *mesh, renderPacket *mat) :
				assetNode(name),
				Model(mesh),
				Magic(mat),
				transparent(false)
			{}

			bool isTransparent()
			{
				return transparent;
			}

			void draw()
			{	
				//getAbsoluteTransform
				assert(NULL != Model);
				assert(NULL != Magic);
				//effect->draw(mesh, material, matrix);
			}

			bool transparent;

			model *Model;
			renderPacket *Magic;



	}



}