#pragma once
#include <list>
namespace NS_ENG{
	class asset
	{//the Extern world class might ugly, an  idea might be create an constructor here that takes in a reference to a world class 
	public:
		virtual void Draw() = 0;


		//GLuint SpecularIntLoc, SpecularPowLoc, DiffuseColLoc;
	};
}
