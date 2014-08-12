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
	vector<vector<vec3>> roadTerrainFaces;

	for(int i=0; i<terrain->gengar_faces.size()-9; i+=9){
		vector<vec3> tmpTerrainFace;
		tmpTerrainFace.push_back(vec3(terrain->gengar_vertices.at(terrain->gengar_faces.at(i)-1)));
		tmpTerrainFace.push_back(vec3(terrain->gengar_vertices.at(terrain->gengar_faces.at(i+3)-1)));
		tmpTerrainFace.push_back(vec3(terrain->gengar_vertices.at(terrain->gengar_faces.at(i+6)-1)));
		terrainFaces.push_back(tmpTerrainFace);

		if((tmpTerrainFace.at(0).y == 30 && tmpTerrainFace.at(1).y == 30 && tmpTerrainFace.at(2).y == 30)
			|| (tmpTerrainFace.at(0).y == 30.5 && tmpTerrainFace.at(1).y == 30.5 && tmpTerrainFace.at(2).y == 30.5)
			|| (tmpTerrainFace.at(0).y == 20 && tmpTerrainFace.at(1).y == 20 && tmpTerrainFace.at(2).y == 20)){
				roadTerrainFaces.push_back(tmpTerrainFace);
		}
	}

	for(int i=0; i<4000; i++){
		float tmpTreeX = rand() % 8000 - 4000;
		float tmpTreeZ = rand() % 10000 -5000;
		float tmpTreeY = 0;
		bool placeTheTree = false;
		for(int j=0; j<terrainFaces.size(); j++){
			
				if(PointInTriangle(vec2(tmpTreeX, tmpTreeZ), 
					vec2(terrainFaces.at(j).at(0).x, terrainFaces.at(j).at(0).z), 
					vec2(terrainFaces.at(j).at(1).x, terrainFaces.at(j).at(1).z), 
					vec2(terrainFaces.at(j).at(2).x, terrainFaces.at(j).at(2).z))){

						bool treeOnRoad = false;
						for(int k=0; k<roadTerrainFaces.size(); k++){
							if((abs(tmpTreeX-roadTerrainFaces.at(k).at(0).x) < 100 && abs(tmpTreeZ-roadTerrainFaces.at(k).at(0).z) < 100)
								|| (abs(tmpTreeX-roadTerrainFaces.at(k).at(1).x) < 100 && abs(tmpTreeZ-roadTerrainFaces.at(k).at(1).z) < 100)
								|| (abs(tmpTreeX-roadTerrainFaces.at(k).at(2).x) < 100 && abs(tmpTreeZ-roadTerrainFaces.at(k).at(2).z) < 100)){
								treeOnRoad = true;
								k+=roadTerrainFaces.size()+5;
							}
						}

						if(!treeOnRoad){
						vec3 currTreePoint = vec3(tmpTreeX, 0, tmpTreeZ);
						vec3 crossOfFace = cross(terrainFaces.at(j).at(0)-terrainFaces.at(j).at(2), terrainFaces.at(j).at(1)-terrainFaces.at(j).at(2));
						float crossOfFaceOffset = -dot(crossOfFace, terrainFaces.at(j).at(0));
						tmpTreeY = -(crossOfFace.x * tmpTreeX + crossOfFace.z * tmpTreeZ + crossOfFaceOffset)/crossOfFace.y;
					
							tmpTreeY-=1;
							
							placeTheTree = true;
						}
						j+=terrainFaces.size()+5;
				}
			
		}

		if(placeTheTree){
		environmentObjectIndices.push_back(1);
		environmentObjectsPositions.push_back(vec3(tmpTreeX, tmpTreeY, tmpTreeZ));
		}
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
	float objectClippingDistanceX = 3000;float objectClippingDistanceZ = 3000;
	float absUserX = abs(userPosition.x);float absUserZ = abs(userPosition.z);
	bool expandX = absUserX > 4000;bool expandZ = absUserZ > 5000;
	if(expandX || expandZ){objectClippingDistanceX=5000;objectClippingDistanceZ=5000;}
	
	for(int i=0; i<environmentObjectIndices.size(); i++){
		float absDiffX = abs(environmentObjectsPositions.at(i).x - userPosition.x);
		float absDiffZ = abs(environmentObjectsPositions.at(i).z - userPosition.z);
		if(absDiffX < objectClippingDistanceX && absDiffZ < objectClippingDistanceZ){
		objectMat = translate(modelview, environmentObjectsPositions.at(i));
		environmentObject->objectIndex = environmentObjectIndices.at(i);
		environmentObject->Draw(projection, objectMat, size, time);
		}
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

float Forest::dist(vec3 p1, vec3 p2){
	float a = p1.x-p2.x;
	float b = p1.y-p2.y;
	float c = p1.z-p2.z;
	return sqrt(a*a + b*b + c*c);
}

float Forest::sign(vec2 p1, vec2 p2, vec2 p3)
{
  return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

bool Forest::PointInTriangle(vec2 pt, vec2 v1, vec2 v2, vec2 v3)
{
  bool b1, b2, b3;

  b1 = sign(pt, v1, v2) < 0.0f;
  b2 = sign(pt, v2, v3) < 0.0f;
  b3 = sign(pt, v3, v1) < 0.0f;

  return ((b1 == b2) && (b2 == b3));
}

