/*
Name: Clayton Suplinski
Project: First-Person Shooter
*/

#pragma once
#include "object.h"
#include "shader.h"
#include "gengar.h"
#include "square3.h"
#include "sphere.h"
#include "cylinder2.h"

using namespace std;
using namespace glm;

class Sky : public Object
{
public:
	Sky();
	~Sky();
	virtual bool Initialize();
	virtual void Draw(const mat4& projection, mat4 modelview, const ivec2 & size, const float time = 0);
	void TakeDown();

	Square3 * sun;
	Square3 * cloud; 
	Cylinder2 * horizon1, * horizon2;

	vector<vec3> cloudPositions;

	vec3 userPosition;

private:
	typedef Object super;
};