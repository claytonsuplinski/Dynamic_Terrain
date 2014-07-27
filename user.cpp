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
	person->Initialize("./models/soldier.obj", "./models/soldier.png", "basic_texture_shader.vert", "basic_texture_shader.frag");
	
	if (this->GLReturnedError("User::Initialize - on exit"))
		return false;

	return true;
}

void User::TakeDown(){super::TakeDown();}

void User::Draw(const mat4 & projection, mat4 modelview, const ivec2 & size, const float time){

	if (this->GLReturnedError("User ::Draw - on entry")){
		return;	
	}
	
	mat4 scaler = scale(modelview, vec3(0.05, 0.05, 0.05));
	person->Draw(projection, scaler, size, 2.5);

	if (this->GLReturnedError("User::Draw - on exit")){
		return;
	}
}
