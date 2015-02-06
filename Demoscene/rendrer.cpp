#include "rendrer.h"

#include "transform.h"
#include "assetNode.h"
#include "modelNode.h"
#include "node.h"


#include <stack>



using namespace sg::noder;


void rendrer::visit(node *Node, M3DMatrix44f  world)
{
	if (4 == Node->getType())
	{
		modelNode *mesh = reinterpret_cast<modelNode*>(Node);
		if (NULL != mesh->Magic)
		{
			mesh->Magic->setMatrices(Node->getAbsoluteTransform(), view, projection);
			mesh->Magic->commitChanges();
		}
		mesh->draw();
	}
	for (Node::child_iterator i = node->beginChildren(); i != Node->endChildren(); ++i) visit(*i, world);
}
void rendrer::draw()
{
	visit(scene, M3DMatrix44f world );
}