#include "base_buffer.h"

GLuint base_buffer::DiffArrayMapTexure = 0;

SamplerList base_buffer::GlobalTextures;

bool samplerComparator(const tup_Samplers &lhs, const tup_Samplers &rhs) 
{
	return boost::get<4>(lhs) < boost::get<4>(rhs);
}

void base_buffer::AddGlobalTexture(std::string GLSL_Name, GLenum Type, GLint TextureName, int size, int sortValue,  bool ready)
{
	std::cout << "===========GlobalTextures===========\n";
	for (auto TexIter : base_buffer::GlobalTextures)
	{
		if (GLSL_Name.compare(boost::tuples::get<0>(TexIter)) == 0 && boost::tuples::get<1>(TexIter) == Type)
		{


			boost::tuples::get<4>(TexIter) = size;
			std::cout << "GlobalTexturesUpdated \n " << boost::tuples::get<0>(TexIter) << "size: " << boost::tuples::get<4>(TexIter) << "\n";
			std::cout << "===========EndGlobalTextures===========\n";
			return;

		}

	}
	//typedef boost::tuple< std::string, GLenum, GLint, int, int, int, bool> tup_Samplers;
	//base_buffer::GlobalTextures.push_back(std::make_tuple<tup_Samplers>(GLSL_Name, Type, TextureName, size, sortValue));
	base_buffer::GlobalTextures.push_back(tup_Samplers(GLSL_Name, Type, TextureName, size, sortValue));
	

	std::sort(
		base_buffer::GlobalTextures.begin(),
		base_buffer::GlobalTextures.end(), 
		samplerComparator
	);
	std::cout << "New Global Texture order \n ";
	int SamplerOrder = 0;
	for (auto TexIter : base_buffer::GlobalTextures)
	{
		boost::tuples::get<5>(TexIter) = SamplerOrder;
		SamplerOrder++;
		std::cout << "--"<<boost::tuples::get<0>(TexIter) << " TextureUnit" << boost::tuples::get<5>(TexIter) << "\n";

	}
	std::cout << "===========EndGlobalTextures===========\n";
}

//return a.get<4>() > b.get<4>();

#define Derive_Buffer_CRTP(Type) class Type: public Buffer_CRTP<Type>
/*
base_buffer::base_buffer()
{
}
*/
/*
base_buffer::~base_buffer()
{
}
*/
/*
//int Init(unsigned int WindowWidth, unsigned int WindowHeight);
//int EnablePass(int PassId)
*/