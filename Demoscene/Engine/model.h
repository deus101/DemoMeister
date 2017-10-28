#ifndef MODEL_HPP
#define MODEL_HPP


#include <string>
#include <vector>
#include <deque> 
#include <map>


#include "mesh.h"
#include "materials.h"

//obviusly this wont work if I want to be forward and deferred, but fuck it
#include "../ShaderFu/DeferredPackets/GeomPacket.h"
#include "../util.h"

//#include "../Rendrer/context.h"



//http://stackoverflow.com/questions/16501419/creating-a-class-with-a-static-member-container-holding-all-instances-of-said-cl
//Hurm isnt it safer with a composite class?

namespace NS_ENG{

	//AHAAA! JEG KAN GENNE FRA GRUPPE, BUFFER GRUPPENE TIL MODDELEN FLERE NODER! 
	//Alt ligger på på plass! og model noden trenger jo bare å kjøre addchildren eller gi den til faren

	struct buffer_Group
	{
		buffer_Group()
		{
			IBO.clear();
			tex = NULL;

			OriginalMat = "";
			OriginalEffect = "";


			ObjName = "";
			MatName = "";
			Effect = "";

			ObjectID = NULL;
			MatId = NULL;
			EffectID = NULL;
			
		}


		//we got what we need for an oct-tree
		GLint SiblingValue;

		GLuint vao;
		//I should have called this IBO
		GLuint vbo;
		//And This IBO_Data
		std::vector<unsigned int> IBO;
		
		NS_MESH::s_ModelAid ModelAidChild;

		//yep, must bloat it some more.
		//Atleast I make sure data don't duplicate.
		std::string OriginalMat;
		std::string OriginalEffect;
		
		
		std::string ObjName;
		std::string MatName;
		std::string Effect;



		//Remove Tex
		GLint tex;
		GLint MatId;
		GLint EffectID;
		GLint ObjectID;

		//strictly speaking we wont need these
		GLfloat amb[4];
		NS_VEC::VEC3 dif;
		NS_VEC::VEC3 spec;
		NS_VEC::VEC3 emi;
		NS_VEC::VEC3 shiny;

	};

	struct PackedVertex{
		NS_VEC::VEC3 position;
		NS_VEC::VEC2 uv;
		NS_VEC::VEC3 normal;
		bool operator<(const PackedVertex that) const{
			return memcmp((void*)this, (void*)&that, sizeof(PackedVertex)) > 0;
		};
	};

	


	class model : public asset
	{
	private:
		//Rename to model Iter
		std::list <model*>::iterator iter;
		//std::list <model*>::iterator classModelIter;
	public:
		static std::list <model*> classModelList;
		//heh should be private
		std::vector<NS_VEC::VEC3> Sort_Pos;
		std::vector<NS_VEC::VEC3> Sort_Norms;
		std::vector<NS_VEC::VEC2> Sort_Uvs;
		std::vector<NS_VEC::VEC3> Sort_Tang;



		std::vector<buffer_Group> Sort_Groups;

		NS_MESH::s_ModelAid ModelAidRoot;
		//GLuint vao_model;
		
		
		GLuint vbo_vertices;
		GLuint vbo_normals;
		GLuint vbo_uv;

		GLuint vbo_BaseTool;
		GLuint vbo_ChildTool;

		//should be grouped per face..so array....
		GLuint vbo_indices;
		model();
		//might need later 
		//model(model const &from)
		model( std::string obj, std::string mtl, bool UV = true, bool Tangent = true);
		~model();

		void SetMaterial(buffer_Group &Object, std::string TaskModel, std::string TaskMaterial);
		

		/*
		model &operator=(model const &src) {
			return *this;
		
		*/

		void Init() {};
		int Init(int t) { return t; };
		void Load();
		void Load(std::string obj, std::string mtl, bool UV, bool Tangent);

		void Draw();
		void Draw(int instances);
	public:



		NS_MESH::MESH meshy;
		//hmmm should I maybe not care how many instances of palette there is...if only I can ID them?
		//NS_MAT
		NS_ENG::MATERIALS palette;
		NS_VEC::VEC3 color;

	private:
		bool getSimilarVertexIndex_fast(
			PackedVertex & packed,
			std::map<PackedVertex, unsigned int> & VertexToOutIndex,
			unsigned int & result
			)
		{

			std::map<PackedVertex, unsigned int>::iterator it = VertexToOutIndex.find(packed);
			if (it == VertexToOutIndex.end()){
				return false;
			}
			else{
				result = it->second;
				return true;
			}
		};

		void DumpBuffer();

		void BufferLog();





	};
	//const void loadBuffer(Model &mModel, renderPacket &mPacket);
}
#endif