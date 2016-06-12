#ifndef MODEL_HPP
#define MODEL_HPP


#include <string>
#include <vector>
#include <deque> 
#include <map>


#include "mesh.h"
#include "materials.h"
#include "../Effect/GeomPacket.h"
#include "../Rendrer/context.h"


namespace NS_ENG{

	//AHAAA! JEG KAN GENNE FRA GRUPPE, BUFFER GRUPPENE TIL MODDELEN FLERE NODER! 
	//Alt ligger på på plass! og model noden trenger jo bare å kjøre addchildren eller gi den til faren

	struct buffer_Group
	{
		buffer_Group()
		{
			IBO.clear();
		}
		GLuint vao;
		GLuint vbo;
		std::vector<unsigned int> IBO;
		//std::vector<unsigned short> IBO;


		//been to long...
		//VEC3 amb;
		GLfloat amb[4];
		NS_VEC::VEC3 dif;
		NS_VEC::VEC3 spec;
		NS_VEC::VEC3 emi;
		NS_VEC::VEC3 shiny;
		GLuint tex;
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
	public:
		std::vector<NS_VEC::VEC3> Sort_Pos;
		std::vector<NS_VEC::VEC3> Sort_Norms;
		std::vector<NS_VEC::VEC2> Sort_Uvs;




		std::vector<buffer_Group> Sort_Groups;



		GLuint vao_model;
		GLuint vbo_vertices;
		GLuint vbo_normals;
		GLuint vbo_uv;

		//should be grouped per face..so array....
		GLuint vbo_indices;
		model();
		model( std::string obj, std::string mtl);
		~model();
		
		//AAA fuck it!
		GLuint VEC3_DIFF_UNILOC, FLOAT_SPECINT_UNILOC, FLOAT_SPECPOW_UNILOC;


		void Draw();

	public:



		NS_MESH::MESH meshy;
		NS_MAT::MATERIALS palette;
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