#pragma once

#include "transform.h"
#include "../Math/vec.h"

namespace NS_SG
{
	

	
	class targetTransform : public transform
	{
	public:
		targetTransform(std::string name) : transform(name), target(NULL) {}

		void getLocalTransform(M3DMatrix44f in)
		{

			if (NULL == target)
			{
				m3dLoadIdentity44(in);
			
			}


			M3DMatrix44f eyeAbs;
			m3dLoadIdentity44(eyeAbs);
			if (NULL != getParent())
			{
			  getParent()->getAbsoluteTransform(eyeAbs);
			}
			
			// get target position into the local coordinate system
			// note: this will obviously fail horribly if target is dependent on this node
			
			//lol faen for en stut jeg er
			M3DMatrix44f eyeAbsInv;
			M3DVector4f invProdukt;
			//3dInvertMatrix44(eyeInvTemp, eyeAbs);
			//m3dGetMatrixColumn44(invProdukt, eyeInvTemp, 3);

			invProdukt[0] = 0.0f;
			invProdukt[1] = 0.0f;
			invProdukt[2] = 0.0f;
			invProdukt[3] = 0.0f;

			m3dGetMatrixColumn44(invProdukt, eyeAbs, 3);

			m3dLoadIdentity44(eyeAbsInv);
			m3dSetMatrixColumn44(eyeAbsInv, invProdukt, 3);
			
			
			//NS_VEC::VEC3 targetPos;
			M3DVector4f targetPos;

			targetPos[0] = 0.0f;
			targetPos[1] = 0.0f;
			targetPos[2] = 0.0f;
			targetPos[3] = 0.0f;



			M3DVector4f targetTran;

			targetTran[0] = 0.0f;
			targetTran[1] = 0.0f;
			targetTran[2] = 0.0f;
			targetTran[3] = 0.0f;

			M3DMatrix44f targetTransform;

			target->getAbsoluteTransform(&targetTransform[0]);

			/*
			printf("TargetMat: %f %f %f %f\n %f %f %f %f\n %f %f %f %f\n %f %f %f %f\n",
				targetTransform[0], targetTransform[1], targetTransform[2], targetTransform[3], targetTransform[4], targetTransform[5], targetTransform[6], targetTransform[7], targetTransform[8], targetTransform[9], targetTransform[10], targetTransform[11], targetTransform[12], targetTransform[13], targetTransform[14], targetTransform[15]
			);
			*/

			m3dGetMatrixColumn44(targetTran, targetTransform, 3);
			
			//remember to remove with below
			targetTran[3] = 0.0f;
			
			//LOL ofcourse the lookat didnt work, well this works now for my demo
			//later versions will have this fixed
			//targetTran[3] = 1.0f;



			//Task find out why this function does not work in release with visual studio c++ compiler 2015
			//the first value in the array allways returns "-nan" here I recreated the functionality withouyt using m3dTransformVector4; 
			//m3dTransformVector4(targetPos,  &eyeAbsInv[0], &targetTran[0]);
			targetPos[0] = eyeAbsInv[0] * targetTran[0] + eyeAbsInv[4] * targetTran[1] + eyeAbsInv[8] * targetTran[2] + eyeAbsInv[12] * targetTran[3];
			targetPos[1] = eyeAbsInv[1] * targetTran[0] + eyeAbsInv[5] * targetTran[1] + eyeAbsInv[9] * targetTran[2] + eyeAbsInv[13] * targetTran[3];
			targetPos[2] = eyeAbsInv[2] * targetTran[0] + eyeAbsInv[6] * targetTran[1] + eyeAbsInv[10] * targetTran[2] + eyeAbsInv[14] * targetTran[3];
			targetPos[3] = eyeAbsInv[3] * targetTran[0] + eyeAbsInv[7] * targetTran[1] + eyeAbsInv[11] * targetTran[2] + eyeAbsInv[15] * targetTran[3];

			/*
			printf("targetPos After: %f %f %f %f\n",
				targetPos[0], targetPos[1], targetPos[2], targetPos[3]
			);
			*/
			//HELVETES DRITT BIBLIOTEK! ERSTATT DET!
			M3DVector3f at, from, up;
			at[0] = targetPos[0];
			at[1] = targetPos[1];
			at[2] = targetPos[2];
			from[0] = eyeAbs[12];
			from[1] = eyeAbs[13];
			from[2] = eyeAbs[14];
			up[0] = 0.0f;
			up[1] = 1.0f;
			up[2] = 0.0f;


			M3DMatrix44f lookat, lookat_inv;
			m3dLoadIdentity44(lookat);

			m3dLookAt(lookat, at, from, up, 0.0f);
			
			m3dInvertMatrix44(in, lookat);
			//m3dCopyMatrix44(in, lookat);

	

		}

		void setTarget(node *target)
		{
			this->target = target;
		}

		node *getTarget() const
		{
			return target;
		}

	private:
		node *target;
	};
	
}
