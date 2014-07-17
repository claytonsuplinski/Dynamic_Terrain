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

class Building : public Object
{
public:
	Building();
	~Building();
	virtual bool Initialize();
	virtual void Draw(const mat4& projection, mat4 modelview, const ivec2 & size, const float time = 0);
	void TakeDown();

	struct xzBoundary{
		vector<vec2> points;
	};

	vector<Gengar*> buildings;
	vector<vec3> dimensions;

	int buildingIndex;

private:
	typedef Object super;
};