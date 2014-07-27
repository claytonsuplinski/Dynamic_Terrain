/*
Name: Clayton Suplinski
Project: First-Person Shooter
*/

#pragma once
#include "object.h"
#include "shader.h"

using namespace std;
using namespace glm;

class TerrainManager : public Object
{
public:
	TerrainManager();
	~TerrainManager();
	virtual bool Initialize();
	virtual void Draw(const mat4& projection, mat4 modelview, const ivec2 & size, const float time = 0);
	void TakeDown();

	vec3 userPosition;float userRotation;

private:
	typedef Object super;
};