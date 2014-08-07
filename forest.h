/*
Name: Clayton Suplinski
Project: First-Person Shooter
*/

#pragma once
#include "object.h"
#include "shader.h"
#include "gengar.h"
#include "environmentObject.h"

using namespace std;
using namespace glm;

class Forest : public Object
{
public:
	Forest();
	~Forest();
	virtual bool Initialize();
	virtual void Draw(const mat4& projection, mat4 modelview, const ivec2 & size, const float time = 0);
	void TakeDown();

	Gengar * terrain;

	EnvironmentObject* environmentObject;
	vector<int> environmentObjectIndices;
	vector<vec3> environmentObjectsPositions;

	bool buildingInFront(int buildingIndex, float distance, float angleOffset, float buffer);
	bool linesIntersect(vec2 a1, vec2 a2, vec2 b1, vec2 b2);
	bool CCW(vec2 C, vec2 W1, vec2 W2);

	bool buildingsInitialized;

	vec3 userPosition;float userRotation;

private:
	typedef Object super;
};