#pragma once

#include <list>
#include "../util.h"
//#include "../Rendrer/base_buffer.h"

//std::list <model*> assetL::classModelList= std::list <model*>();

//EffectStageConstPtr CurrentStage = EffectStageConstPtr();

//NS_ENG::asset::CurrentStage;
namespace NS_ENG{
	
	
		
	class asset
	{//the Extern DemoMeister class might ugly, an  idea might be create an constructor here that takes in a reference to a DemoMeister class 
	
	//protected:
		//static EffectStageConstPtr CurrentStage;


	public:
		virtual void Draw() = 0;

		//OK, it does not make much sense why this should be here.
		//or maybe...
		static EffectStageConstPtr CurrentStage;
		static void SetCurrentStage(EffectStageConstPtr newLookUp) {
			CurrentStage = newLookUp;
		};
		//GLuint SpecularIntLoc, SpecularPowLoc, DiffuseColLoc;
	};
}
