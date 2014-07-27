/*
Name: Clayton Suplinski
Project: First-Person Shooter
*/

#include "mountains.h"

Mountains::Mountains() : Object(){}

Mountains::~Mountains(){}

bool Mountains::Initialize()
{
	if (this->GLReturnedError("Mountains::Initialize - on entry"))
		return false;

	terrain = new Gengar();
	terrain->order = 1;
	terrain->Initialize("./models/terrain/mountains1.obj", "./textures/floorPattern.jpg", "basic_texture_shader.vert", "basic_texture_shader.frag");

	terrain2 = new Gengar();
	terrain2->order = 1;
	terrain2->Initialize("./models/terrain/mountains2.obj", "./textures/floorPattern.jpg", "basic_texture_shader.vert", "basic_texture_shader.frag");
	
	if (this->GLReturnedError("Mountains::Initialize - on exit"))
		return false;

	return true;
}

void Mountains::TakeDown(){super::TakeDown();}

void Mountains::Draw(const mat4 & projection, mat4 modelview, const ivec2 & size, const float time){

	if (this->GLReturnedError("Mountains ::Draw - on entry")){
		return;	
	}
	
	terrain->Draw(projection, modelview, size, time);

	mat4 another = modelview;

	another = translate(another, vec3(0,0,5050));
	terrain2->Draw(projection, another, size, time);

	if (this->GLReturnedError("Mountains::Draw - on exit")){
		return;
	}
}


bool Mountains::buildingInFront(int buildingIndex, float distance, float angleOffset, float buffer){
	/*if(distance > 0){
		
		float tmpRot = (userRotation+270 + angleOffset)*0.0174;
		float tmpSin = userPosition.z+distance*sin(tmpRot);
		float tmpCos = userPosition.x+distance*cos(tmpRot);
		float halfDimX = buffer + building->dimensions.at(cityBlocksBuildings.at(buildingIndex)).x/2;
		float halfDimZ = buffer + building->dimensions.at(cityBlocksBuildings.at(buildingIndex)).z/2;
		if(linesIntersect(vec2(userPosition.x, userPosition.z), vec2(tmpCos, tmpSin),
			vec2(cityBlocksBuildingsPositions.at(buildingIndex).x+halfDimX, cityBlocksBuildingsPositions.at(buildingIndex).z+halfDimZ), 
			vec2(cityBlocksBuildingsPositions.at(buildingIndex).x-halfDimX, cityBlocksBuildingsPositions.at(buildingIndex).z-halfDimZ))
			||
			linesIntersect(vec2(userPosition.x, userPosition.z), vec2(tmpCos, tmpSin),
			vec2(cityBlocksBuildingsPositions.at(buildingIndex).x-halfDimX, cityBlocksBuildingsPositions.at(buildingIndex).z+halfDimZ), 
			vec2(cityBlocksBuildingsPositions.at(buildingIndex).x+halfDimX, cityBlocksBuildingsPositions.at(buildingIndex).z-halfDimZ))){
				return true;
		}

	}*/
	return false;
}

bool Mountains::CCW(vec2 C, vec2 W1, vec2 W2){
	vec2 ab = W1-C;
	vec2 ac = W2-C;
	double y = (ab.x * ac.y) - (ab.y * ac.x);

    // dot product
    double x = (ab.x * ab.y) + (ac.x * ac.y);

	return atan2(y, x) > 0;
}

bool Mountains::linesIntersect(vec2 a1, vec2 a2, vec2 b1, vec2 b2){
	return (CCW(a1, b1, b2) != CCW(a2, b1, b2)) && (CCW(b1, a1, a2) != CCW(b2, a1, a2));
}

