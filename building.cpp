/*
Name: Clayton Suplinski
Project: First-Person Shooter
*/

#include "building.h"

Building::Building() : Object(){}

Building::~Building(){}

bool Building::Initialize()
{
	if (this->GLReturnedError("Building::Initialize - on entry"))
		return false;

	Gengar * tmpGengar;

	vector<string> filenames;
	filenames.push_back("bridge");
	filenames.push_back("bridgeMiddle");
	filenames.push_back("newWTC");
	filenames.push_back("searsTower");
	filenames.push_back("transAmPyramid");
	filenames.push_back("05building1");
	filenames.push_back("05building2");
	filenames.push_back("10building1");
	filenames.push_back("10building2");
	filenames.push_back("20building1");
	filenames.push_back("20building2");
	filenames.push_back("20building3");
	filenames.push_back("30building1");
	filenames.push_back("30building2");
	filenames.push_back("30building3");
	filenames.push_back("30building4");
	filenames.push_back("40building1");
	filenames.push_back("40building2");
	filenames.push_back("40building3");
	filenames.push_back("40building4");
	filenames.push_back("40building5");

	for(unsigned int i=0; i<filenames.size(); i++){
		tmpGengar = new Gengar();
		tmpGengar->order = 1;
		string filename = "./models/buildings/" + filenames.at(i) + ".obj";
		tmpGengar->Initialize(filename.c_str(), "./models/arch.png", "basic_texture_shader.vert", "basic_texture_shader.frag");
		buildings.push_back(tmpGengar);
	}

	if (this->GLReturnedError("Building::Initialize - on exit"))
		return false;

	return true;
}

void Building::TakeDown(){super::TakeDown();}

void Building::Draw(const mat4 & projection, mat4 modelview, const ivec2 & size, const float time){

	if (this->GLReturnedError("Building ::Draw - on entry")){
		return;	
	}

	buildings.at(buildingIndex)->Draw(projection, modelview, size, time);	

	if (this->GLReturnedError("Building::Draw - on exit")){
		return;
	}
}
