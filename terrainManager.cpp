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

	environmentObject = new EnvironmentObject;
	environmentObject->Initialize();

	city = new City();	
	forest = new Forest();
	desert = new Desert();
	plains = new Plains();
	mountains = new Mountains();
	bigCity = new BigCity();

	city->environmentObject = environmentObject;
	forest->environmentObject = environmentObject;

	city->Initialize();	
	forest->Initialize();
	desert->Initialize();
	plains->Initialize();
	mountains->Initialize();
	bigCity->Initialize();

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
bigCity->TakeDown();
}

void TerrainManager::Draw(const mat4 & projection, mat4 modelview, const ivec2 & size, const float time){

	if (this->GLReturnedError("TerrainManager ::Draw - on entry")){
		return;	
	}

	glEnable(GL_DEPTH_TEST);


	if(userPosition.x > -14238 && userPosition.z > -15539){
	city->userPosition = userPosition * vec3(-1, 1, -1);
	city->userRotation = userRotation;
	city->Draw(projection, modelview, size, time);
	}

	if(userPosition.x < -5238 && userPosition.z > -14573){
	mat4 forestOffset = modelview;
	forestOffset = translate(forestOffset, vec3(14241,0,4389));
	forest->Draw(projection, forestOffset, size, 0);
	}

	if(userPosition.x < -5238 && userPosition.z > -21266 && userPosition.z < -5034){
	mat4 desertOffset = modelview;
	desertOffset = translate(desertOffset, vec3(14241,0,11589));
	desert->Draw(projection, desertOffset, size, 0);
	}

	if(userPosition.x > -14238 && userPosition.z > -21266 && userPosition.z < -5369){
	mat4 plainsOffset = modelview;
	plainsOffset = translate(plainsOffset, vec3(3360,0,11496.5));
	plains->Draw(projection, plainsOffset, size, 0);
	}

	if(userPosition.z < -11345){
	mat4 mountainsOffset = modelview;
	mountainsOffset = translate(mountainsOffset, vec3(9120.5,0,20664));
	mountains->Draw(projection, mountainsOffset, size, 0);
	}

	if(userPosition.z < -22412){
	mat4 bigCityOffset = modelview;
	bigCityOffset = translate(bigCityOffset, vec3(0,0,28188));
	bigCity->Draw(projection, bigCityOffset, size, 0);
	}



	/*
	if(userPosition.x > -6720 && userPosition.x < 0 && userPosition.z > -9204 && userPosition.z < 0){

		for(int i=0; i<city->cityLength; i++){
			for(int j=0; j<city->cityWidth; j++){
				if(abs(userPosition.x + city->cityBlocksPositions.at(i*city->cityWidth + j).x) < 537
						&& abs(userPosition.z + city->cityBlocksPositions.at(i*city->cityWidth + j).z) < 144){
							cout << "user on city" << endl;
				}
			}
		}
		//select the current block you're on (or bridge)
		//use the vertices in that gengar

		//first go through all vertices - if the vertex is within 1074/2, keep it (push back its index in a vector)
		//go through all the faces and keep the ones that contain the vertices from above (push back the index of the face)
		//go through the remaining faces and check each triangle to see if it contains the user
		//use the y-values of the 3 points on the resulting face to get the user's altitude

	}
	else{
		cout << "user not on city" << endl;
	}
	*/

	

	if (this->GLReturnedError("TerrainManager::Draw - on exit")){
		return;
	}
}