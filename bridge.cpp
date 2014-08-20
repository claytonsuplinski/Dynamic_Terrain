/*
Name: Clayton Suplinski
Project: First-Person Shooter
*/

#include "bridge.h"

Bridge::Bridge() : Object(){}

Bridge::~Bridge(){}

bool Bridge::Initialize()
{
	if (this->GLReturnedError("Bridge::Initialize - on entry"))
		return false;

	building = new Building();
	building->Initialize();

	loadBuildings();

	if (this->GLReturnedError("Bridge::Initialize - on exit"))
		return false;

	return true;
}

void Bridge::TakeDown(){super::TakeDown();}


void Bridge::Draw(const mat4 & projection, mat4 modelview, const ivec2 & size, const float time){

	if (this->GLReturnedError("Bridge ::Draw - on entry")){
		return;	
	}

	glEnable(GL_DEPTH_TEST);
	mat4 buildingMatrix = modelview;

	for(int i=0; i<cityBlocksBuildingsPositions.size(); i++){
		buildingMatrix = translate(modelview, cityBlocksBuildingsPositions.at(i));
		buildingMatrix = rotate(buildingMatrix, cityBlocksBuildingsRotations.at(i), vec3(0,1,0));
		building->buildingIndex = cityBlocksBuildings.at(i);
		building->Draw(projection, buildingMatrix, size, 0);
	}

	if (this->GLReturnedError("Bridge::Draw - on exit")){
		return;
	}
}

float Bridge::sign(vec2 p1, vec2 p2, vec2 p3)
{
  return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

bool Bridge::PointInTriangle(vec2 pt, vec2 v1, vec2 v2, vec2 v3)
{
  bool b1, b2, b3;

  b1 = sign(pt, v1, v2) < 0.0f;
  b2 = sign(pt, v2, v3) < 0.0f;
  b3 = sign(pt, v3, v1) < 0.0f;

  return ((b1 == b2) && (b2 == b3));
}


void Bridge::loadBuildings(){
cityBlocksBuildings.push_back(0);cityBlocksBuildingsPositions.push_back(vec3(0, 0, 0));cityBlocksBuildingsRotations.push_back(0);
cityBlocksBuildings.push_back(1);cityBlocksBuildingsPositions.push_back(vec3(600, 0, 0));cityBlocksBuildingsRotations.push_back(0);
cityBlocksBuildings.push_back(1);cityBlocksBuildingsPositions.push_back(vec3(1674, 0, 0));cityBlocksBuildingsRotations.push_back(0);
cityBlocksBuildings.push_back(1);cityBlocksBuildingsPositions.push_back(vec3(2748, 0, 0));cityBlocksBuildingsRotations.push_back(0);
cityBlocksBuildings.push_back(1);cityBlocksBuildingsPositions.push_back(vec3(3822, 0, 0));cityBlocksBuildingsRotations.push_back(0);
}