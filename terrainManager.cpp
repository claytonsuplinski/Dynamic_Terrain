/*
Name: Clayton Suplinski
Project: First-Person Shooter
*/

#include "terrainManager.h"

TerrainManager::TerrainManager() : Object(){}

TerrainManager::~TerrainManager(){}

bool TerrainManager::Initialize()
{
	if (this->GLReturnedError("TerrainManager::Initialize - on entry"))
		return false;

	city = new City();	
	forest = new Forest();
	desert = new Desert();
	plains = new Plains();
	mountains = new Mountains();

	city->Initialize();	
	forest->Initialize();
	desert->Initialize();
	plains->Initialize();
	mountains->Initialize();

	if (this->GLReturnedError("TerrainManager::Initialize - on exit"))
		return false;

	return true;
}

void TerrainManager::TakeDown(){
super::TakeDown();
city->TakeDown();
forest->TakeDown();
desert->TakeDown();
plains->TakeDown();
mountains->TakeDown();
}

void TerrainManager::Draw(const mat4 & projection, mat4 modelview, const ivec2 & size, const float time){

	if (this->GLReturnedError("TerrainManager ::Draw - on entry")){
		return;	
	}

	glEnable(GL_DEPTH_TEST);

	if(userPosition.x > -14238){
	city->userPosition = userPosition * vec3(-1, 1, -1);
	city->userRotation = userRotation;
	city->Draw(projection, modelview, size, time);
	}

	if(userPosition.x < -6238){
	mat4 forestOffset = modelview;
	forestOffset = translate(forestOffset, vec3(14241,0,4389));
	forest->Draw(projection, forestOffset, size, 0);
	}

	if(userPosition.x < -6238){
	mat4 desertOffset = modelview;
	desertOffset = translate(desertOffset, vec3(14241,0,11589));
	desert->Draw(projection, desertOffset, size, 0);
	}

	if(userPosition.x > -14238){
	mat4 plainsOffset = modelview;
	plainsOffset = translate(plainsOffset, vec3(3360,0,11496.5));
	plains->Draw(projection, plainsOffset, size, 0);
	}

	mat4 mountainsOffset = modelview;
	mountainsOffset = translate(mountainsOffset, vec3(9120.5,0,20664));
	mountains->Draw(projection, mountainsOffset, size, 0);


	

	if (this->GLReturnedError("TerrainManager::Draw - on exit")){
		return;
	}
}