/*
Name: Clayton Suplinski
Project: First-Person Shooter
*/

#include "forest.h"

Forest::Forest() : Object(){}

Forest::~Forest(){}

bool Forest::Initialize()
{
	if (this->GLReturnedError("Forest::Initialize - on entry"))
		return false;

	terrain = new Gengar();
	terrain->order = 1;
	terrain->Initialize("./models/terrain/forest.obj", "./models/terrain/forest.png", "basic_texture_shader.vert", "basic_texture_shader.frag");

	vector<vector<vec3>> terrainFaces;

	for(int i=0; i<terrain->gengar_faces.size()-9; i+=9){
		vector<vec3> tmpTerrainFace;
		tmpTerrainFace.push_back(vec3(terrain->gengar_vertices.at(terrain->gengar_faces.at(i)-1)));
		tmpTerrainFace.push_back(vec3(terrain->gengar_vertices.at(terrain->gengar_faces.at(i+3)-1)));
		tmpTerrainFace.push_back(vec3(terrain->gengar_vertices.at(terrain->gengar_faces.at(i+6)-1)));
		terrainFaces.push_back(tmpTerrainFace);
	}

	for(int i=0; i<1000; i++){
		
		//cout << terrain->gengar_faces.at(0) << endl;
		environmentObjectIndices.push_back(1);
		environmentObjectsPositions.push_back(vec3(rand() % 8000 - 4000, 0, rand() % 10000 -5000));
	}
	
	if (this->GLReturnedError("Forest::Initialize - on exit"))
		return false;

	return true;
}

void Forest::TakeDown(){super::TakeDown();}

void Forest::Draw(const mat4 & projection, mat4 modelview, const ivec2 & size, const float time){

	if (this->GLReturnedError("Forest ::Draw - on entry")){
		return;	
	}
	
	terrain->Draw(projection, modelview, size, time);

	mat4 objectMat = modelview;
	for(int i=0; i<environmentObjectIndices.size(); i++){
		/*float absDiffX = abs(environmentObjectsPositions.at(i).x - userPosition.x);
		float absDiffZ = abs(environmentObjectsPositions.at(i).z - userPosition.z);
		if(absDiffX < 1800 && absDiffZ < 1800){*/
		objectMat = translate(modelview, environmentObjectsPositions.at(i));
		environmentObject->objectIndex = environmentObjectIndices.at(i);
		environmentObject->Draw(projection, objectMat, size, time);
		//}
	}

	if (this->GLReturnedError("Forest::Draw - on exit")){
		return;
	}
}


bool Forest::buildingInFront(int buildingIndex, float distance, float angleOffset, float buffer){
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

bool Forest::CCW(vec2 C, vec2 W1, vec2 W2){
	vec2 ab = W1-C;
	vec2 ac = W2-C;
	double y = (ab.x * ac.y) - (ab.y * ac.x);

    // dot product
    double x = (ab.x * ab.y) + (ac.x * ac.y);

	return atan2(y, x) > 0;
}

bool Forest::linesIntersect(vec2 a1, vec2 a2, vec2 b1, vec2 b2){
	return (CCW(a1, b1, b2) != CCW(a2, b1, b2)) && (CCW(b1, a1, a2) != CCW(b2, a1, a2));
}

