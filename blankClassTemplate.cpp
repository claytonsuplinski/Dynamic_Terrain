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

	
	if (this->GLReturnedError("TerrainManager::Initialize - on exit"))
		return false;

	return true;
}

void TerrainManager::TakeDown(){super::TakeDown();}

void TerrainManager::Draw(const mat4 & projection, mat4 modelview, const ivec2 & size, const float time){

	if (this->GLReturnedError("TerrainManager ::Draw - on entry")){
		return;	
	}

	glEnable(GL_DEPTH_TEST);
	mat4 another = modelview;
	

	if (this->GLReturnedError("TerrainManager::Draw - on exit")){
		return;
	}
}