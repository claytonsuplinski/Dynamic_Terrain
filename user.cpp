/*
Name: Clayton Suplinski
Project: First-Person Shooter
*/

#include "user.h"

User::User() : Object(){}

User::~User(){}

bool User::Initialize()
{
	if (this->GLReturnedError("User::Initialize - on entry"))
		return false;

	person = new Gengar();
	person->order = 1;
	person->Initialize("./models/objects/car1.obj", "./models/objects/stopLight.png", "basic_texture_shader.vert", "basic_texture_shader.frag");

	velocity = 0;
	prevTime = 0;currTime = 0;
	
	if (this->GLReturnedError("User::Initialize - on exit"))
		return false;

	return true;
}

void User::TakeDown(){super::TakeDown();}

void User::Draw(const mat4 & projection, mat4 modelview, const ivec2 & size, const float time){

	if (this->GLReturnedError("User ::Draw - on entry")){
		return;	
	}
	
	mat4 scaler = rotate(modelview, 180.f, vec3(0,1,0));
	person->Draw(projection, scaler, size, 2.5);

	if (this->GLReturnedError("User::Draw - on exit")){
		return;
	}
}
