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
	filenames.push_back("bridge");dimensions.push_back(vec3(99999999, 99999999, 99999999));
	filenames.push_back("bridgeMiddle");dimensions.push_back(vec3(99999999, 99999999, 99999999));
	filenames.push_back("newWTC");dimensions.push_back(vec3(250, 1776, 250));
	filenames.push_back("searsTower");dimensions.push_back(vec3(195, 1450, 195));
	filenames.push_back("transAmPyramid");dimensions.push_back(vec3(200, 850, 150));
	filenames.push_back("05building1");dimensions.push_back(vec3(30, 62.5, 20));
	filenames.push_back("05building2");dimensions.push_back(vec3(30, 62.5, 20));
	filenames.push_back("10building1");dimensions.push_back(vec3(40, 125, 30));
	filenames.push_back("10building2");dimensions.push_back(vec3(40, 125, 30));
	filenames.push_back("20building1");dimensions.push_back(vec3(80, 250, 50));
	filenames.push_back("20building2");dimensions.push_back(vec3(80, 250, 50));
	filenames.push_back("20building3");dimensions.push_back(vec3(80, 250, 50));
	filenames.push_back("30building1");dimensions.push_back(vec3(100, 375, 60));
	filenames.push_back("30building2");dimensions.push_back(vec3(100, 375, 60));
	filenames.push_back("30building3");dimensions.push_back(vec3(100, 375, 60));
	filenames.push_back("30building4");dimensions.push_back(vec3(100, 375, 60));
	filenames.push_back("40building1");dimensions.push_back(vec3(120, 450, 80));
	filenames.push_back("40building2");dimensions.push_back(vec3(120, 450, 80));
	filenames.push_back("40building3");dimensions.push_back(vec3(120, 450, 80));
	filenames.push_back("40building4");dimensions.push_back(vec3(120, 450, 80));
	filenames.push_back("40building5");dimensions.push_back(vec3(120, 450, 80));

	for(unsigned int i=0; i<filenames.size(); i++){
		tmpGengar = new Gengar();
		tmpGengar->order = 1;
		string filename = "./models/buildings/" + filenames.at(i) + ".obj";
		string texturename = "./models/buildings/" + filenames.at(i) + ".png";
		tmpGengar->Initialize(filename.c_str(), texturename.c_str(), "basic_texture_shader.vert", "basic_texture_shader.frag");
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

	if(buildingIndex == 7){
		glDisable(GL_CULL_FACE);
	}
	buildings.at(buildingIndex)->Draw(projection, modelview, size, time);
	if(buildingIndex == 7){
		glEnable(GL_CULL_FACE);
	}

	if (this->GLReturnedError("Building::Draw - on exit")){
		return;
	}
}
