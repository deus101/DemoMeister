#include "WCD_1.h"




WCD::WCD()
{



}
/*
WCD::~WCD(void)
{
}

*/

void WCD::PreInit() {

	this->AddPass(Squiddy.FindAndRegister("Deferred_GBUFFER_Normal_GeometryPass.xml"));


	this->AddPass(Squiddy.FindAndRegister("Deferred_GBUFFER_Raymarching_GeometryPass.xml"));
}

void WCD::Init() {
	return;

}

void WCD::AfterInit(){
	return;
}

void WCD::HackerSpace() {
	return;
}