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

class Bridge : public Object
{
public:
	Bridge();
	~Bridge();
	virtual bool Initialize();
	virtual void Draw(const mat4& projection, mat4 modelview, const ivec2 & size, const float time = 0);
	void TakeDown();
	void loadBuildings();

	float sign(vec2 p1, vec2 p2, vec2 p3);
	bool PointInTriangle(vec2 pt, vec2 v1, vec2 v2, vec2 v3);

	vector<Gengar*> cityBlocks;
	vector<vec3> cityBlocksPositions;

	vector<int> cityBlocksBuildings;
	vector<vec3> cityBlocksBuildingsPositions;
	vector<float> cityBlocksBuildingsRotations;

	Building * building;

	int currBuilding;
	vec3 currBuildingPosition;
	float currBuildingRotation;

	bool buildingsInitialized;

	vec3 userPosition;float userRotation;

private:
	typedef Object super;
};