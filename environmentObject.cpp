/*
Name: Clayton Suplinski
Project: First-Person Shooter
*/

#include "environmentObject.h"

EnvironmentObject::EnvironmentObject() : Object(){}

EnvironmentObject::~EnvironmentObject(){}

bool EnvironmentObject::Initialize()
{
	if (this->GLReturnedError("EnvironmentObject::Initialize - on entry"))
		return false;

	Gengar * tmpGengar;

	vector<string> filenames;
	filenames.push_back("stopLight");dimensions.push_back(vec3(99999999, 99999999, 99999999));
	filenames.push_back("pineTree");dimensions.push_back(vec3(99999999, 99999999, 99999999));
	filenames.push_back("umbrella");dimensions.push_back(vec3(99999999, 99999999, 99999999));
	filenames.push_back("volleyballNet");dimensions.push_back(vec3(99999999, 99999999, 99999999));
	filenames.push_back("cactus");dimensions.push_back(vec3(99999999, 99999999, 99999999));
	filenames.push_back("grassClump");dimensions.push_back(vec3(99999999, 99999999, 99999999));
	filenames.push_back("tree");dimensions.push_back(vec3(99999999, 99999999, 99999999));
	filenames.push_back("boundingFence");dimensions.push_back(vec3(99999999, 99999999, 99999999));

	for(unsigned int i=0; i<filenames.size(); i++){
		tmpGengar = new Gengar();
		tmpGengar->order = 1;
		string filename = "./models/objects/" + filenames.at(i) + ".obj";
		string texturename = "./models/objects/" + filenames.at(i) + ".png";
		tmpGengar->Initialize(filename.c_str(), texturename.c_str(), "basic_texture_shader.vert", "basic_texture_shader.frag");
		objects.push_back(tmpGengar);
	}

	if (this->GLReturnedError("EnvironmentObject::Initialize - on exit"))
		return false;

	return true;
}

void EnvironmentObject::TakeDown(){super::TakeDown();}

void EnvironmentObject::Draw(const mat4 & projection, mat4 modelview, const ivec2 & size, const float time){

	if (this->GLReturnedError("EnvironmentObject ::Draw - on entry")){
		return;	
	}

	objects.at(objectIndex)->Draw(projection, modelview, size, time);

	if (this->GLReturnedError("EnvironmentObject::Draw - on exit")){
		return;
	}
}
