/*
Name: Clayton Suplinski
Project: First-Person Shooter
*/

#include "desert.h"

Desert::Desert() : Object(){}

Desert::~Desert(){}

bool Desert::Initialize()
{
	if (this->GLReturnedError("Desert::Initialize - on entry"))
		return false;

	terrain = new Gengar();
	terrain->order = 1;
	terrain->Initialize("./models/terrain/desert1.obj", "./textures/floorPatternDesert.jpg", "basic_texture_shader.vert", "basic_texture_shader.frag");

	terrain2 = new Gengar();
	terrain2->order = 1;
	terrain2->Initialize("./models/terrain/desert2.obj", "./textures/floorPatternDesert.jpg", "basic_texture_shader.vert", "basic_texture_shader.frag");
	
	if (this->GLReturnedError("Desert::Initialize - on exit"))
		return false;

	return true;
}

void Desert::TakeDown(){super::TakeDown();}

void Desert::Draw(const mat4 & projection, mat4 modelview, const ivec2 & size, const float time){

	if (this->GLReturnedError("Desert ::Draw - on entry")){
		return;	
	}
	
	terrain->Draw(projection, modelview, size, time);

	mat4 another = modelview;

	another = translate(another, vec3(0,0,4400));
	terrain2->Draw(projection, another, size, time);

	if (this->GLReturnedError("Desert::Draw - on exit")){
		return;
	}
}


bool Desert::buildingInFront(int buildingIndex, float distance, float angleOffset, float buffer){
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

bool Desert::CCW(vec2 C, vec2 W1, vec2 W2){
	vec2 ab = W1-C;
	vec2 ac = W2-C;
	double y = (ab.x * ac.y) - (ab.y * ac.x);

    // dot product
    double x = (ab.x * ab.y) + (ac.x * ac.y);

	return atan2(y, x) > 0;
}

bool Desert::linesIntersect(vec2 a1, vec2 a2, vec2 b1, vec2 b2){
	return (CCW(a1, b1, b2) != CCW(a2, b1, b2)) && (CCW(b1, a1, a2) != CCW(b2, a1, a2));
}

