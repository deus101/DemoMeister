#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "node.h"

namespace NS_SG{


		class camera : public node
		{
		public:
		     camera(std::string name) :
				node(name),
				fov(60.0f), 
				aspect(16.0f / 9),
				znear(1.0f), zfar(50.0f),
				projection_dirty(true)
				{
				}

			virtual NodeType getType() { return NODE_CAMERA; }

			void setFov(float fov)
			{
				this->fov = fov;
				projection_dirty = true;
			}

			void setZNear(float znear)
			{
				this->znear = znear;
				projection_dirty = true;
			}

			void setZFar(float zfar)
			{
				this->zfar = zfar;
				projection_dirty = true;
			}

			void setAspect(float aspect)
			{
				this->aspect = aspect;
				projection_dirty = true;
			}


			const void  getProjection(M3DMatrix44f in) const
			{
				/* recalculate matrix if needed */
				if (projection_dirty)
				{
					
					m3dMakePerspectiveMatrix(projection,m3dDegToRad(fov), aspect, znear, zfar);
					
					projection_dirty = false;
				}

				m3dCopyMatrix44(in, projection);
			}


		private:
			float fov;
			float aspect;
			float znear, zfar;

			mutable M3DMatrix44f projection;
			mutable bool         projection_dirty;




		};

	
}


#endif