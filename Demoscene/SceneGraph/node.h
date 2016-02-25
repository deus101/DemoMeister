#pragma once
#include <string>
#include "../Math/math3d.h"
#include <boost/enable_shared_from_this.hpp>
#include <deque>
#include <list>
#include <map>


namespace NS_SG{
	

		typedef boost::shared_ptr< class node > nodePtr;
		typedef boost::shared_ptr<const class node> nodeConstPtr;

		typedef boost::weak_ptr< class node > svakRef;
		//parent???

	
		typedef std::list< node* > Nodes;
		typedef std::map< unsigned int, svakRef> NodeKart;
		
		class node
			: public boost::enable_shared_from_this<node>
		{
		public:
			node(const std::string &name) : parent(), name(name) { assert(name.length() > 0); }
			virtual ~node();

			enum NodeType
			{
				NODE_COMPOSER,
				NODE_CAMERA,
				NODE_LIGHT_POINT,
				NODE_LIGHT_DIR,
				NODE_TRANSFORM,
				NODE_ASSET,
				NODE_TARGET,
			};

			

			void addChild(node* Node)
			{
				
				children.push_back(Node);
				Node->setParent(shared_from_this() );

			}
			////Husk
			//void removeChild(nodePtr node)
			//{
			//	Nodes::iterator itr = std::find(children.begin(), children.end(), node);
			//	if (itr != children.end())
			//	{
			//		// reset parent
			//		//(*itr)->setParent(nodePtr());
			//		// remove from children
			//		children.erase(itr);
			//	}
			//}

			void setParent(nodePtr node){ parent = svakRef(node); }


			//trouble?
			nodePtr getParent() const { return parent.lock(); }

			////! returns the node's parent node (provide a templated function for easier down-casting of nodes)
			//template <class T>
			//boost::shared_ptr<T> getParent() const {
			//	return boost::dynamic_pointer_cast<T>(parent.lock());
			//}



			nodePtr findChild(const std::string &name)
			{
			if (this->name == name) 
				return shared_from_this();
					nodePtr node;
					Nodes::iterator itr;
					for (itr = children.begin(); itr != children.end(); ++itr) {
						node = (*itr)->findChild(name);
						if (node) return node;
					}
				return node;
			}


			virtual NodeType getType() = 0;

			//why the fuck dont i just leave the math3dshit behnd? 
			virtual void getLocalTransform(M3DMatrix44f in) 
			{ 
				M3DMatrix44f trans; 
				m3dLoadIdentity44(trans); 
				m3dCopyMatrix44(in, trans); 
			
			}

			virtual void getInverseRotation(M3DMatrix44f in)
			{
				M3DMatrix44f trans;
				m3dLoadIdentity44(trans);
				m3dCopyMatrix44(in, trans);

			}

			virtual void getAbsoluteTransform(M3DMatrix44f in)
			{
				M3DMatrix44f absoluteTransform;
				getLocalTransform(absoluteTransform);
				nodePtr curr = shared_from_this();
				while (NULL != curr->getParent())
				{
					M3DMatrix44f currentTransform;
					curr = curr->parent.lock();

					curr->getLocalTransform(currentTransform);
					//HOLY FUCK!!!!!!!!!!!!!!!!
					//m3dMatrixMultiply44(absoluteTransform, absoluteTransform, currentTransform);
					m3dMatrixMultiply44(absoluteTransform, currentTransform, absoluteTransform);
				}

				m3dCopyMatrix44(in, absoluteTransform);
			}

			virtual std::string getName(void)
			{
				return this->name;
			}


			typedef std::list<node*>::iterator child_iterator;
			typedef std::list<node *>::const_iterator child_const_iterator;
			child_iterator beginChildren() { return children.begin(); }
			child_iterator endChildren() { return children.end(); }
			child_const_iterator beginChildren() const { return children.begin(); }
			child_const_iterator endChildren() const { return children.end(); }

				
			

		private:
			const std::string name;
															
			svakRef parent;
			Nodes children;
		};
	

}

