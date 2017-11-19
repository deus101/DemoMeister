#pragma once
#include "../Math/math3d.h"
#include "transform.h"
#include "../Math/vec.h"

namespace NS_SG
{
	
		class objTransform : public transform
		{
		public:
			objTransform(std::string name) :
				transform(name),
				position(0, 0, 0),
				rotation(0, 0, 0),
				scale(1, 1, 1),
				matrix_dirty(true)
			{}
			virtual void getInverseRotation(M3DMatrix44f in)
			{

				m3dCopyMatrix44(in, invRot);
			}
			//should maybe have a failure return here
			void getLocalTransform(M3DMatrix44f in)
			{

				//just to check how much I fuck ups
				M3DMatrix44f MatArgument;// parInv;
				NS_VEC::VEC3 parPos;
				m3dCopyMatrix44(MatArgument, in);
				//this->getParent()->getInverseRotation(parInv);

				
				if (matrix_dirty)
				{
					//m_rotTr,
					M3DMatrix44f m_scale, m_rot, m_tran,  m_ScaXRot, m_ScaXrotXtran;



					m3dLoadIdentity44(m_scale);
					m3dScaleMatrix44(m_scale, scale.X, scale.Y, scale.Z);


					//rotation.NormIt();
					m3dRotationMatrix44(m_rot, rotation);

					m3dLoadIdentity44(m_tran);



					m3dTranslationMatrix44(m_tran, position.X, position.Y, position.Z);
					


					m3dMatrixMultiply44(m_ScaXRot, m_rot,m_scale);
					//m3dCopyMatrix44(invRot, m_TranXScaXRot);

					m3dMatrixMultiply44(m_ScaXrotXtran, m_tran, m_ScaXRot);

					m3dCopyMatrix44(matrix, m_ScaXrotXtran);


					matrix_dirty = false;
					if (this->getName() == "tran_stalagmite_2")
					{
						std::string name = this->getName();
						int faen = 0;
					}

				}
				//M3DVector4f rotatedPos;
				//M3DVector4f current;

				//current[0] = this->position.X;
				//current[1] = this->position.Y;
				//current[2] = this->position.Z;
				//current[3] = 1.0f;
				//m3dTransformVector4(rotatedPos, current, parInv);
				//m3dMatrixMultiply44(in, matrix, parInv);
				//m3dSetMatrixColumn44(matrix, rotatedPos, 3);
				m3dCopyMatrix44(in, matrix);
			}

			void setPosition(NS_VEC::VEC3 &pos)
			{
				this->position = pos;
				this->matrix_dirty = true;
			}

			void setRotation(NS_VEC::QUAT &rot)
			{
				this->rotation = rot;
				//this->rotation.NormIt();
				this->matrix_dirty = true;
			}

			void setScale(NS_VEC::VEC3 &scale)
			{
				this->scale = scale;
				this->matrix_dirty = true;
			}

		private:
			NS_VEC::VEC3 position;
			NS_VEC::QUAT rotation;
			NS_VEC::VEC3 scale;

			M3DMatrix44f matrix, invRot;
			bool            matrix_dirty;
		};
	
}