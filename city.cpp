/*
Name: Clayton Suplinski
Project: First-Person Shooter
*/

#include "city.h"

City::City() : Object(){}

City::~City(){}

bool City::Initialize()
{
	if (this->GLReturnedError("City::Initialize - on entry"))
		return false;

	Gengar * tmpGengar;

	water = new Gengar();
	water->order = 1;
	water->Initialize("./models/water.obj", "./textures/water.png", "basic_texture_shader.vert", "basic_texture_shader.frag");

	Gengar * beachCorner = new Gengar();
	beachCorner->order = 1;
	beachCorner->Initialize("./models/beachCorner.obj", "./textures/floorPatternDesert.jpg", "basic_texture_shader.vert", "basic_texture_shader.frag");

	Gengar * beachCornerBridge = new Gengar();
	beachCornerBridge->order = 1;
	beachCornerBridge->Initialize("./models/beachCornerBridge.obj", "./textures/floorPatternDesert.jpg", "basic_texture_shader.vert", "basic_texture_shader.frag");

	Gengar * beachHorizontal = new Gengar();
	beachHorizontal->order = 1;
	beachHorizontal->Initialize("./models/beachHorizontal.obj", "./models/arch.png", "basic_texture_shader.vert", "basic_texture_shader.frag");

	Gengar * beachVertical = new Gengar();
	beachVertical->order = 1;
	beachVertical->Initialize("./models/beachVertical.obj", "./models/arch.png", "basic_texture_shader.vert", "basic_texture_shader.frag");

	Gengar * beachVerticalBridge = new Gengar();
	beachVerticalBridge->order = 1;
	beachVerticalBridge->Initialize("./models/beachVerticalBridge.obj", "./models/arch.png", "basic_texture_shader.vert", "basic_texture_shader.frag");

	Gengar * block1 = new Gengar();
	block1->order = 1;
	block1->Initialize("./models/block1.obj", "./textures/forestWall.png", "basic_texture_shader.vert", "basic_texture_shader.frag");

	Gengar * block2L = new Gengar();
	block2L->order = 1;
	block2L->Initialize("./models/block2L.obj", "./textures/explosion.png", "basic_texture_shader.vert", "basic_texture_shader.frag");

	Gengar * block2R = new Gengar();
	block2R->order = 1;
	block2R->Initialize("./models/block2R.obj", "./textures/floorPattern.jpg", "basic_texture_shader.vert", "basic_texture_shader.frag");

	Gengar * block4 = new Gengar();
	block4->order = 1;
	block4->Initialize("./models/block4Corner.obj", "./textures/floorPattern.jpg", "basic_texture_shader.vert", "basic_texture_shader.frag");

	Gengar * block4Right = new Gengar();
	block4Right->order = 1;
	block4Right->Initialize("./models/block4CornerRight.obj", "./textures/explosion.png", "basic_texture_shader.vert", "basic_texture_shader.frag");

	int myInt = 30;
char *chars = reinterpret_cast<char*>(&myInt);

	string filePath = "./models/";
	
	for(int i=0; i<cityLength; i++){
		for(int j=0; j<cityWidth; j++){
			if(i==0 && j==0){
				cityBlocksRotations.push_back(0.f);
				cityBlocks.push_back(beachCorner);
			}
			else if(i==0 && (j>0 && j<7)){
				cityBlocksRotations.push_back(0.f);
				cityBlocks.push_back(beachHorizontal);
			}
			else if(i==0 && j==7){
				cityBlocksRotations.push_back(-90.f);
				cityBlocks.push_back(beachCornerBridge);
			}
			else if(i==1 && j==7){
				cityBlocksRotations.push_back(180.f);
				cityBlocks.push_back(beachVerticalBridge);
			}
			else if(i>0 && (j==0 || j==7)){
				if(j==7){
					cityBlocksRotations.push_back(180.f);
				}
				else{
					cityBlocksRotations.push_back(0.f);
				}
				cityBlocks.push_back(beachVertical);
			}
			else if(i==1 && (j==2 || j==5)){
				cityBlocksRotations.push_back(0.f);
				cityBlocks.push_back(block2L);
			}
			else if(i==1 && (j==3 || j==6)){
				cityBlocksRotations.push_back(0.f);
				cityBlocks.push_back(block2R);
			}
			else if(i==7 && j==4){
				cityBlocksRotations.push_back(0.f);
				cityBlocks.push_back(block4);
			}
			else if(i==8 && j==5){
				cityBlocksRotations.push_back(180.f);
				cityBlocks.push_back(block4);
			}
			else if(i==7 && j==5){
				cityBlocksRotations.push_back(0.f);
				cityBlocks.push_back(block4Right);
			}
			else if(i==8 && j==4){
				cityBlocksRotations.push_back(180.f);
				cityBlocks.push_back(block4Right);
			}
			else{
				cityBlocksRotations.push_back(0.f);
				cityBlocks.push_back(block1);
			}
			/*else{
			tmpGengar = new Gengar();
			tmpGengar->order = 1;

			stringstream fileNameA (stringstream::in | stringstream::out);
			fileNameA << i;
			stringstream fileNameB (stringstream::in | stringstream::out);
			fileNameB << j;

			string fileName = fileNameA.str() + "-" + fileNameB.str();
			fileName = filePath + fileName + ".obj";
			const char* objName = fileName.c_str();
			tmpGengar->Initialize(objName, "./models/arch.png", "basic_texture_shader.vert", "basic_texture_shader.frag");
			cityBlocks.push_back(tmpGengar);
			}*/

			float minX, minZ, maxX, maxZ;
			minX = minZ = 99999999999;
			maxX = maxZ = -99999999999;
			for(unsigned int k=0; k<cityBlocks.at(cityBlocks.size()-1)->gengar_vertices.size(); k++){
				if(cityBlocks.at(cityBlocks.size()-1)->gengar_vertices.at(k).x < minX){
					minX = cityBlocks.at(cityBlocks.size()-1)->gengar_vertices.at(k).x;
				}
				if(cityBlocks.at(cityBlocks.size()-1)->gengar_vertices.at(k).z < minZ){
					minZ = cityBlocks.at(cityBlocks.size()-1)->gengar_vertices.at(k).z;
				}
				if(cityBlocks.at(cityBlocks.size()-1)->gengar_vertices.at(k).x > maxX){
					maxX = cityBlocks.at(cityBlocks.size()-1)->gengar_vertices.at(k).x;
				}
				if(cityBlocks.at(cityBlocks.size()-1)->gengar_vertices.at(k).z > maxZ){
					maxZ = cityBlocks.at(cityBlocks.size()-1)->gengar_vertices.at(k).z;
				}
			}

			blockDimensions tmpDim;
			tmpDim.width = maxX - minX;
			tmpDim.length = maxZ - minZ;
			this->cityBlocksDimensions.push_back(tmpDim);
		}
	}
	
	if (this->GLReturnedError("City::Initialize - on exit"))
		return false;

	return true;
}

void City::TakeDown(){super::TakeDown();}

void City::Draw(const mat4 & projection, mat4 modelview, const ivec2 & size, const float rotY){

	if (this->GLReturnedError("City ::Draw - on entry")){
		return;	
	}

	glEnable(GL_DEPTH_TEST);
	mat4 another = modelview;

	float lengthOffset = 0;
	float widthOffset = 0;
	float waterWidthOffset = 0;
	for(int i=0; i<cityLength; i++){
		for(int j=0; j<cityWidth; j++){
			widthOffset += this->cityBlocksDimensions.at(i*cityWidth + j).width/2;
			lengthOffset += this->cityBlocksDimensions.at(i*cityWidth + j).length/2;

			another = translate(modelview, vec3(widthOffset, 0, lengthOffset));

			lengthOffset -= this->cityBlocksDimensions.at(i*cityWidth + j).length/2;
			widthOffset += this->cityBlocksDimensions.at(i*cityWidth + j).width/2;

			another = rotate(another, cityBlocksRotations.at(i*cityWidth + j), vec3(0,1,0));
			cityBlocks.at(i*cityWidth + j)->Draw(projection, another, size, 0);
		}
		waterWidthOffset = widthOffset;
		widthOffset = 0;
		lengthOffset += this->cityBlocksDimensions.at(i*cityWidth).length;
	}

	mat4 waterMatrix = modelview;
	waterMatrix = translate(modelview, vec3(-5000,0,-5000));
	water->Draw(projection, waterMatrix, size, 0);
	waterMatrix = translate(modelview, vec3(5000,0,-5000));
	water->Draw(projection, waterMatrix, size, 0);
	waterMatrix = translate(modelview, vec3(-5000,0,5000));
	water->Draw(projection, waterMatrix, size, 0);
	waterMatrix = translate(modelview, vec3(waterWidthOffset+5000,0,5000));
	water->Draw(projection, waterMatrix, size, 0);

	if (this->GLReturnedError("City::Draw - on exit")){
		return;
	}
}
