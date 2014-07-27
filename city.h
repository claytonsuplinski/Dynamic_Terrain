/*
Name: Clayton Suplinski
Project: First-Person Shooter
*/

#pragma once
#include "object.h"
#include "shader.h"
#include "gengar.h"
#include "building.h"
#include <fstream>

using namespace std;
using namespace glm;

class City : public Object
{
public:
	City();
	~City();
	virtual bool Initialize();
	virtual void Draw(const mat4& projection, mat4 modelview, const ivec2 & size, const float time = 0);
	void saveBuildingVertices();
	void TakeDown();
	void loadBuildings();

	float sign(vec2 p1, vec2 p2, vec2 p3);
	bool PointInTriangle(vec2 pt, vec2 v1, vec2 v2, vec2 v3);

	bool buildingInFront(int buildingIndex, float distance, float angleOffset, float buffer);
	bool linesIntersect(vec2 a1, vec2 a2, vec2 b1, vec2 b2);

	Gengar * water;

	struct xzBoundary{
		vector<vec2> points;
	};

	struct blockDimensions{
		vec2 ul, ur, dl, dr;
		float width; //East-west - x
		float length; //North-south - z
	};

	Building * building;
	vector<Gengar*> cityBlocks;
	vector<vec3> cityBlocksPositions;

	vector<int> cityBlocksBuildings;
	vector<vec3> cityBlocksBuildingsPositions;
	vector<float> cityBlocksBuildingsRotations;

	int currBuilding;
	vec3 currBuildingPosition;
	float currBuildingRotation;

	bool buildingsInitialized;

	vector<blockDimensions> cityBlocksDimensions; //Dimensions of each block
	vector<blockDimensions> cityBlocksDimensions2;
	vector<float> cityBlocksRotations;
	static const int cityLength = 33; //North-south
	static const int cityWidth = 8; //East-west

	vector<vector<int>> blocksToDraw; //An array of arrays of indices for blocks to draw while in a certain block
	int currBlock; //Index of the current block the user is in
	
	vector<vector<xzBoundary>> cityBlocksBoundaries; //will need to use boost to check these

	vec3 userPosition;float userRotation;

	bool inWater;

	//Need to have terrain separate from buildings	

	//Steps
	//1) Make entire city in 3ds max (terrain and buildings)
	//2) Sub-divide city into chunks
	//3) Make two models for each chunk - one for terrain (cityBlocks) and one for buildings (cityBlocksBuildings)

	//Have a different class for movable objects

private:
	typedef Object super;
};