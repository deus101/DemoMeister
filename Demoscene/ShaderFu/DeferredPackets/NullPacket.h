
#ifndef NULL_PACKET_HPP
#define	NULL_PACKET_HPP

#include "../renderPacket.h"
#include "../DeferredPipeMother.h"
namespace NS_EFF{
	class NullPacket : public DeferredPipeMother {
	public:

		NullPacket();

		virtual bool Init();


	private:


	};

}
#endif