/*
Name: Clayton Suplinski
Project: First-Person Shooter
*/

#include "sky.h"

Sky::Sky() : Object(){}

Sky::~Sky(){}

bool Sky::Initialize()
{
	if (this->GLReturnedError("Sky::Initialize - on entry"))
		return false;

	sun = new Square3();
	sun->Initialize(1, 300, "./textures/sun.png", "basic_skybox_shader.vert", "basic_skybox_shader.frag");

	cloud = new Square3();
	cloud->Initialize(1, 1000, "./textures/cloud.png", "basic_skybox_shader.vert", "basic_skybox_shader.frag");

	horizon1 = new Cylinder2();
	horizon1->Initialize(1, 40, 200, 200, "./textures/horizon1.png", "basic_skybox_shader.vert", "basic_skybox_shader.frag");

	horizon2 = new Cylinder2();
	horizon2->Initialize(1, 40, 200, 200, "./textures/horizon2.png", "basic_skybox_shader.vert", "basic_skybox_shader.frag");

	for(int i=0; i<100; i++){
		float r = 2000;
		float t = 360*((float) rand()) / (float) RAND_MAX;
		float p = 85*((float) rand()) / (float) RAND_MAX;
		cloudPositions.push_back(vec3(t, r, p));
	}
	
	if (this->GLReturnedError("Sky::Initialize - on exit"))
		return false;

	return true;
}

void Sky::TakeDown(){super::TakeDown();}

void Sky::Draw(const mat4 & projection, mat4 modelview, const ivec2 & size, const float time){

	if (this->GLReturnedError("Sky ::Draw - on entry")){
		return;	
	}	

	glDisable(GL_DEPTH_TEST);
	glDepthMask(false);

	mat4 sunMatrix = modelview;
	sunMatrix = translate(modelview, userPosition);
	sunMatrix = rotate(sunMatrix, 0.f, vec3(0,1,0));
	sunMatrix = rotate(sunMatrix, 75.f, vec3(0,0,1));
	sunMatrix = translate(sunMatrix, vec3(0,2000,0));
	sun->Draw(projection, sunMatrix, size, time);

	mat4 cloudMatrix = modelview;
	for(int i=0; i<cloudPositions.size(); i++){
	cloudMatrix = translate(modelview, userPosition);
	cloudMatrix = rotate(cloudMatrix, cloudPositions.at(i).x, vec3(0,1,0));
	cloudMatrix = rotate(cloudMatrix, cloudPositions.at(i).z, vec3(0,0,1));
	cloudMatrix = translate(cloudMatrix, vec3(0,cloudPositions.at(i).y,0));
	cloud->Draw(projection, cloudMatrix, size, time);
	}	

	glDisable(GL_CULL_FACE);
	mat4 horizonMatrix = modelview;
	horizonMatrix = translate(modelview, userPosition);
	horizon1->Draw(projection, horizonMatrix, size, time);
	horizonMatrix = translate(modelview, userPosition + vec3(0,-40,0));
	horizon2->Draw(projection, horizonMatrix, size, time);
	horizonMatrix = translate(modelview, userPosition + vec3(0,-80,0));
	horizon2->Draw(projection, horizonMatrix, size, time);
	glEnable(GL_CULL_FACE);


	glDepthMask(true);
	glEnable(GL_DEPTH_TEST);

	if (this->GLReturnedError("Sky::Draw - on exit")){
		return;
	}
}