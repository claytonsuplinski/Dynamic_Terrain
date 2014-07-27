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

class User : public Object
{
public:
	User();
	~User();
	virtual bool Initialize();
	virtual void Draw(const mat4& projection, mat4 modelview, const ivec2 & size, const float time = 0);
	void TakeDown();

	Gengar * person;

private:
	typedef Object super;
};