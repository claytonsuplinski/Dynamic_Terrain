/*
Name: Clayton Suplinski
Project: First-Person Shooter
*/

#pragma once
#include "object.h"
#include "shader.h"
#include "gengar.h"

using namespace std;
using namespace glm;

class City : public Object
{
public:
	City();
	~City();
	virtual bool Initialize();
	virtual void Draw(const mat4& projection, mat4 modelview, const ivec2 & size, const float time = 0);
	void TakeDown();

	Gengar * water;

	struct xzBoundary{
		vector<vec2> points;
	};

	struct blockDimensions{
		vec2 ul, ur, dl, dr;
		float width; //East-west - x
		float length; //North-south - z
	};

	vector<Gengar*> cityBlocks;
	vector<Gengar*> cityBlocksBuildings;
	vector<blockDimensions> cityBlocksDimensions; //Dimensions of each block
	vector<float> cityBlocksRotations;
	static const int cityLength = 10;
	static const int cityWidth = 8;

	vector<vector<int>> blocksToDraw; //An array of arrays of indices for blocks to draw while in a certain block
	int currBlock; //Index of the current block the user is in
	
	vector<vector<xzBoundary>> cityBlocksBoundaries; //will need to use boost to check these

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