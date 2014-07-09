/*
Name: Clayton Suplinski
Project: First-Person Shooter
*/

#include "city.h"

City::City() : Object(){}

City::~City(){}

bool City::Initialize()
{
	if (this->GLReturnedError("City::Initialize - on entry"))
		return false;

	building = new Gengar();
	building->order = 1;
	building->Initialize("./models/building1.obj", "./models/building1.png", "basic_texture_shader.vert", "basic_texture_shader.frag");
	
	if (this->GLReturnedError("City::Initialize - on exit"))
		return false;

	return true;
}

void City::TakeDown(){super::TakeDown();}

void City::Draw(const mat4 & projection, mat4 modelview, const ivec2 & size, const float rotY){

	if (this->GLReturnedError("City ::Draw - on entry")){
		return;	
	}

	glEnable(GL_DEPTH_TEST);
	mat4 another;

	building->Draw(projection, modelview, size, 0);

	if (this->GLReturnedError("City::Draw - on exit")){
		return;
	}
}
