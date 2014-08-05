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

	currBuilding = 0;
	currBuildingPosition = vec3(0,0.5,0);

	building = new Building();
	building->Initialize();

	buildingsInitialized = false;

	loadBuildings();

	water = new Gengar();
	water->order = 1;
	water->Initialize("./models/water.obj", "./textures/water.png", "basic_texture_shader.vert", "basic_texture_shader_ocean.frag");

	Gengar * beachCorner = new Gengar();
	beachCorner->order = 1;
	beachCorner->Initialize("./models/beachCorner.obj", "./models/beachCorner.png", "basic_texture_shader.vert", "basic_texture_shader.frag");

	Gengar * beachCornerBridge = new Gengar();
	beachCornerBridge->order = 1;
	beachCornerBridge->Initialize("./models/beachCornerBridge.obj", "./models/beachCornerBridge.png", "basic_texture_shader.vert", "basic_texture_shader.frag");

	Gengar * beachCornerPlains = new Gengar();
	beachCornerPlains->order = 1;
	beachCornerPlains->Initialize("./models/beachCornerPlains.obj", "./models/beachCornerPlains.png", "basic_texture_shader.vert", "basic_texture_shader.frag");

	Gengar * beachCornerPlains2 = new Gengar();
	beachCornerPlains2->order = 1;
	beachCornerPlains2->Initialize("./models/beachCornerPlains2.obj", "./models/beachCornerPlains2.png", "basic_texture_shader.vert", "basic_texture_shader.frag");

	Gengar * beachHorizontal = new Gengar();
	beachHorizontal->order = 1;
	beachHorizontal->Initialize("./models/beachHorizontal.obj", "./models/beachHorizontal.png", "basic_texture_shader.vert", "basic_texture_shader.frag");

	Gengar * beachHorizontalPlains = new Gengar();
	beachHorizontalPlains->order = 1;
	beachHorizontalPlains->Initialize("./models/beachHorizontalPlains.obj", "./models/beachHorizontalPlains.png", "basic_texture_shader.vert", "basic_texture_shader.frag");

	Gengar * beachHorizontalPlainsHighway = new Gengar();
	beachHorizontalPlainsHighway->order = 1;
	beachHorizontalPlainsHighway->Initialize("./models/beachHorizontalPlainsHighway.obj", "./models/beachHorizontalPlainsHighway.png", "basic_texture_shader.vert", "basic_texture_shader.frag");

	Gengar * beachVertical = new Gengar();
	beachVertical->order = 1;
	beachVertical->Initialize("./models/beachVertical.obj", "./models/beachVertical.png", "basic_texture_shader.vert", "basic_texture_shader.frag");

	Gengar * beachVerticalBridge = new Gengar();
	beachVerticalBridge->order = 1;
	beachVerticalBridge->Initialize("./models/beachVerticalBridge.obj", "./models/beachVerticalBridge.png", "basic_texture_shader.vert", "basic_texture_shader.frag");

	Gengar * beachVerticalBridge2 = new Gengar();
	beachVerticalBridge2->order = 1;
	beachVerticalBridge2->Initialize("./models/beachVerticalBridge2.obj", "./models/beachVerticalBridge2.png", "basic_texture_shader.vert", "basic_texture_shader.frag");

	Gengar * block1 = new Gengar();
	block1->order = 1;
	block1->Initialize("./models/block1.obj", "./models/block1.png", "basic_texture_shader.vert", "basic_texture_shader.frag");

	Gengar * block2L = new Gengar();
	block2L->order = 1;
	block2L->Initialize("./models/block2L.obj", "./models/block2L.png", "basic_texture_shader.vert", "basic_texture_shader.frag");

	Gengar * block2R = new Gengar();
	block2R->order = 1;
	block2R->Initialize("./models/block2R.obj", "./models/block2R.png", "basic_texture_shader.vert", "basic_texture_shader.frag");

	int myInt = 30;
char *chars = reinterpret_cast<char*>(&myInt);

	string filePath = "./models/";
	
	blockDimensions tmpDim;
	for(int i=0; i<cityLength; i++){
		for(int j=0; j<cityWidth; j++){
			if(i==0 && j==0){
				cityBlocksRotations.push_back(0.f);
				cityBlocks.push_back(beachCorner);
				tmpDim.ul = vec2(0,0);tmpDim.dl = vec2(0,0);tmpDim.ur = vec2(0,0);tmpDim.dr = vec2(0,0);
				cityBlocksDimensions2.push_back(tmpDim);
			}
			else if(i==32 && j==0){ //Need different texture
				cityBlocksRotations.push_back(90.f);
				cityBlocks.push_back(beachCornerPlains);
				tmpDim.ul = vec2(0,0);tmpDim.dl = vec2(0,0);tmpDim.ur = vec2(0,0);tmpDim.dr = vec2(0,0);
				cityBlocksDimensions2.push_back(tmpDim);
			}
			else if(i==32 && j==7){ //Need different texture
				cityBlocksRotations.push_back(180.f);
				cityBlocks.push_back(beachCornerPlains2);
				tmpDim.ul = vec2(0,0);tmpDim.dl = vec2(0,0);tmpDim.ur = vec2(0,0);tmpDim.dr = vec2(0,0);
				cityBlocksDimensions2.push_back(tmpDim);
			}
			else if(i==0 && (j>0 && j<7)){
				cityBlocksRotations.push_back(0.f);
				cityBlocks.push_back(beachHorizontal);
				tmpDim.ul = vec2(0,0);tmpDim.dl = vec2(0,0);tmpDim.ur = vec2(0,0);tmpDim.dr = vec2(0,0);
				cityBlocksDimensions2.push_back(tmpDim);
			}
			else if(i==32 && (j>0 && j<7)){ //Need different texture
				if(j == 4){
					cityBlocksRotations.push_back(180.f);
					cityBlocks.push_back(beachHorizontalPlainsHighway);
					tmpDim.ul = vec2(0,0);tmpDim.dl = vec2(0,0);tmpDim.ur = vec2(0,0);tmpDim.dr = vec2(0,0);
					cityBlocksDimensions2.push_back(tmpDim);
				}
				else{
					cityBlocksRotations.push_back(180.f);
					cityBlocks.push_back(beachHorizontalPlains);
					tmpDim.ul = vec2(0,0);tmpDim.dl = vec2(0,0);tmpDim.ur = vec2(0,0);tmpDim.dr = vec2(0,0);
					cityBlocksDimensions2.push_back(tmpDim);
				}
			}
			else if(i==0 && j==7){
				cityBlocksRotations.push_back(-90.f);
				cityBlocks.push_back(beachCornerBridge);
				tmpDim.ul = vec2(0,0);tmpDim.dl = vec2(0,0);tmpDim.ur = vec2(0,0);tmpDim.dr = vec2(0,0);
				cityBlocksDimensions2.push_back(tmpDim);
			}
			else if((i==1 || i==25) && j==7){
				cityBlocksRotations.push_back(180.f);
				cityBlocks.push_back(beachVerticalBridge);
				tmpDim.ul = vec2(0,0);tmpDim.dl = vec2(0,0);tmpDim.ur = vec2(0,0);tmpDim.dr = vec2(0,0);
				cityBlocksDimensions2.push_back(tmpDim);
			}
			else if(i==24 && j==7){
				cityBlocksRotations.push_back(180.f);
				cityBlocks.push_back(beachVerticalBridge2);
				tmpDim.ul = vec2(0,0);tmpDim.dl = vec2(0,0);tmpDim.ur = vec2(0,0);tmpDim.dr = vec2(0,0);
				cityBlocksDimensions2.push_back(tmpDim);
			}
			else if(i>0 && (j==0 || j==7)){
				if(j==7){
					cityBlocksRotations.push_back(180.f);
				}
				else{
					cityBlocksRotations.push_back(0.f);
				}
				cityBlocks.push_back(beachVertical);
				tmpDim.ul = vec2(0,0);tmpDim.dl = vec2(0,0);tmpDim.ur = vec2(0,0);tmpDim.dr = vec2(0,0);
				cityBlocksDimensions2.push_back(tmpDim);
			}
			else if(i==1 && (j==2 || j==5)){
				cityBlocksRotations.push_back(0.f);
				cityBlocks.push_back(block2L);
				tmpDim.ul = vec2(-519,126);tmpDim.dl = vec2(-519, -126);tmpDim.ur = vec2(537, 126);tmpDim.dr = vec2(537, -126);
				cityBlocksDimensions2.push_back(tmpDim);
			}
			else if(i==1 && (j==3 || j==6)){
				cityBlocksRotations.push_back(0.f);
				cityBlocks.push_back(block2R);
				tmpDim.ul = vec2(-537,126);tmpDim.dl = vec2(-537, -126);tmpDim.ur = vec2(519, 126);tmpDim.dr = vec2(519, -126);
				cityBlocksDimensions2.push_back(tmpDim);
			}
			else{
				cityBlocksRotations.push_back(0.f);
				cityBlocks.push_back(block1);
				tmpDim.ul = vec2(-519,126);tmpDim.dl = vec2(-519,-126);tmpDim.ur = vec2(519,126);tmpDim.dr = vec2(519,-126);
				cityBlocksDimensions2.push_back(tmpDim);
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

void City::saveBuildingVertices(){
	ofstream outputFile;
outputFile.open("buildingPositions.txt");

for(int i=0; i<cityBlocksBuildings.size(); i++){
	outputFile << "cityBlocksBuildings.push_back(" << cityBlocksBuildings.at(i) 
		<< ");cityBlocksBuildingsPositions.push_back(vec3(" << cityBlocksBuildingsPositions.at(i).x << ", " << cityBlocksBuildingsPositions.at(i).y << ", "
		<< cityBlocksBuildingsPositions.at(i).z
		<< "));cityBlocksBuildingsRotations.push_back(" << cityBlocksBuildingsRotations.at(i) << ");" << endl;
}

outputFile.close();
}


void City::Draw(const mat4 & projection, mat4 modelview, const ivec2 & size, const float time){

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

			if(!buildingsInitialized){
				cityBlocksPositions.push_back(vec3(widthOffset, 0, lengthOffset));

				if(cityBlocksDimensions2.at(i*cityWidth + j).dl.x != 0){

					float topOffsetLeft = 0;
					float topOffsetRight = 0;
					float bottomOffsetLeft = 0;
					float bottomOffsetRight = 0;
					float leftOffsetTop = 0;
					float leftOffsetBottom = 0;
					float rightOffsetTop = 0;
					float rightOffsetBottom = 0;

					int randomizedBuilding = rand() % (building->dimensions.size()-5) + 5;

					cityBlocksBuildings.push_back(randomizedBuilding);
					cityBlocksBuildingsPositions.push_back(
						vec3(widthOffset + cityBlocksDimensions2.at(i*cityWidth + j).ul.x + building->dimensions.at(randomizedBuilding).x/2,
						0,
						lengthOffset + cityBlocksDimensions2.at(i*cityWidth + j).ul.y - building->dimensions.at(randomizedBuilding).z/2));
					cityBlocksBuildingsRotations.push_back(0);
					topOffsetLeft = building->dimensions.at(randomizedBuilding).x;
					leftOffsetTop = building->dimensions.at(randomizedBuilding).z;

					randomizedBuilding = rand() % (building->dimensions.size()-5) + 5;
					cityBlocksBuildings.push_back(randomizedBuilding);
					cityBlocksBuildingsPositions.push_back(
						vec3(widthOffset + cityBlocksDimensions2.at(i*cityWidth + j).ur.x - building->dimensions.at(randomizedBuilding).x/2,
						0,
						lengthOffset + cityBlocksDimensions2.at(i*cityWidth + j).ur.y - building->dimensions.at(randomizedBuilding).z/2));
					cityBlocksBuildingsRotations.push_back(0);
					topOffsetRight = building->dimensions.at(randomizedBuilding).x;
					rightOffsetTop = building->dimensions.at(randomizedBuilding).z;					

					randomizedBuilding = rand() % (building->dimensions.size()-5) + 5;
					cityBlocksBuildings.push_back(randomizedBuilding);
					cityBlocksBuildingsPositions.push_back(
						vec3(widthOffset + cityBlocksDimensions2.at(i*cityWidth + j).dl.x + building->dimensions.at(randomizedBuilding).x/2,
						0,
						lengthOffset + cityBlocksDimensions2.at(i*cityWidth + j).dl.y + building->dimensions.at(randomizedBuilding).z/2));
					cityBlocksBuildingsRotations.push_back(180);
					bottomOffsetLeft = building->dimensions.at(randomizedBuilding).x;
					leftOffsetBottom = building->dimensions.at(randomizedBuilding).z;					

					randomizedBuilding = rand() % (building->dimensions.size()-5) + 5;
					cityBlocksBuildings.push_back(randomizedBuilding);
					cityBlocksBuildingsPositions.push_back(
						vec3(widthOffset + cityBlocksDimensions2.at(i*cityWidth + j).dr.x - building->dimensions.at(randomizedBuilding).x/2,
						0,
						lengthOffset + cityBlocksDimensions2.at(i*cityWidth + j).dr.y + building->dimensions.at(randomizedBuilding).z/2));
					cityBlocksBuildingsRotations.push_back(180);
					bottomOffsetRight = building->dimensions.at(randomizedBuilding).x;
					rightOffsetBottom = building->dimensions.at(randomizedBuilding).z;					

					//Make sure the corners can never be landmarks
					//Place landmarks in the center of the block and place everything else around it
							//Determine if there will be a landmark before placing any other buildings
							//Place the landmark and use its width and length as boundaries
							//Place buildings all around it

					/////////Non-landmark case////////
					////Top//// (fixed + z; go from +x to -x)
					bool buildingFits = true;
					while(buildingFits){
						randomizedBuilding = rand() % (building->dimensions.size()-5) + 5;
						if(cityBlocksDimensions2.at(i*cityWidth + j).ul.x + building->dimensions.at(randomizedBuilding).x + topOffsetLeft < cityBlocksDimensions2.at(i*cityWidth + j).ur.x - topOffsetRight){
							cityBlocksBuildings.push_back(randomizedBuilding);
							cityBlocksBuildingsPositions.push_back(
								vec3(widthOffset + cityBlocksDimensions2.at(i*cityWidth + j).ul.x + building->dimensions.at(randomizedBuilding).x/2 + topOffsetLeft,
								0,
								lengthOffset + cityBlocksDimensions2.at(i*cityWidth + j).ul.y - building->dimensions.at(randomizedBuilding).z/2));
							cityBlocksBuildingsRotations.push_back(0);
							topOffsetLeft += building->dimensions.at(randomizedBuilding).x;
						}
						else{
							buildingFits = false;
						}
					}					

					////Bottom////  (fixed - z; go from +x to -x)
					buildingFits = true;
					bool tryLandmark = true;
					while(buildingFits){
						if(tryLandmark){
							randomizedBuilding = rand() % (building->dimensions.size()-5) + 5;
						}
						else{
							randomizedBuilding = rand() % (building->dimensions.size()-5) + 5;
						}
						if(cityBlocksDimensions2.at(i*cityWidth + j).dl.x + building->dimensions.at(randomizedBuilding).x + bottomOffsetLeft < cityBlocksDimensions2.at(i*cityWidth + j).dr.x - bottomOffsetRight){
							cityBlocksBuildings.push_back(randomizedBuilding);
							cityBlocksBuildingsPositions.push_back(
								vec3(widthOffset + cityBlocksDimensions2.at(i*cityWidth + j).dl.x + building->dimensions.at(randomizedBuilding).x/2 + bottomOffsetLeft,
								0,
								lengthOffset + cityBlocksDimensions2.at(i*cityWidth + j).dl.y + building->dimensions.at(randomizedBuilding).z/2));
							cityBlocksBuildingsRotations.push_back(180);
							bottomOffsetLeft += building->dimensions.at(randomizedBuilding).x;
							tryLandmark = false;
						}
						else if(!tryLandmark){
							buildingFits = false;
						}
						else{
							tryLandmark = false;
						}
					}					

					////Left////  (fixed + x; go from +z to -z)
					buildingFits = true;
					while(buildingFits){
						randomizedBuilding = rand() % (building->dimensions.size()-5) + 5;
						if(cityBlocksDimensions2.at(i*cityWidth + j).dl.y + building->dimensions.at(randomizedBuilding).x + leftOffsetBottom < cityBlocksDimensions2.at(i*cityWidth + j).ul.y - leftOffsetTop){
							cityBlocksBuildings.push_back(randomizedBuilding);
							cityBlocksBuildingsPositions.push_back(
								vec3(widthOffset + cityBlocksDimensions2.at(i*cityWidth + j).dl.x + building->dimensions.at(randomizedBuilding).z/2,
								0,
								lengthOffset + cityBlocksDimensions2.at(i*cityWidth + j).dl.y + building->dimensions.at(randomizedBuilding).x/2 + leftOffsetBottom));
							cityBlocksBuildingsRotations.push_back(270);
							leftOffsetBottom += building->dimensions.at(randomizedBuilding).x;
						}
						else{
							buildingFits = false;
						}
					}					

					////Right//// (fixed - x; go from +z to -z)
					buildingFits = true;
					while(buildingFits){
						randomizedBuilding = rand() % (building->dimensions.size()-5) + 5;
						if(cityBlocksDimensions2.at(i*cityWidth + j).dr.y + building->dimensions.at(randomizedBuilding).x + rightOffsetBottom < cityBlocksDimensions2.at(i*cityWidth + j).ur.y - rightOffsetTop){
							cityBlocksBuildings.push_back(randomizedBuilding);
							cityBlocksBuildingsPositions.push_back(
								vec3(widthOffset + cityBlocksDimensions2.at(i*cityWidth + j).dr.x - building->dimensions.at(randomizedBuilding).z/2,
								0,
								lengthOffset + cityBlocksDimensions2.at(i*cityWidth + j).dr.y + building->dimensions.at(randomizedBuilding).x/2 + rightOffsetBottom));
							cityBlocksBuildingsRotations.push_back(90);
							rightOffsetBottom += building->dimensions.at(randomizedBuilding).x;
						}
						else{
							buildingFits = false;
						}
					}					
				}
			}

			lengthOffset -= this->cityBlocksDimensions.at(i*cityWidth + j).length/2;
			widthOffset += this->cityBlocksDimensions.at(i*cityWidth + j).width/2;

			if(abs(userPosition.x - cityBlocksPositions.at(i*cityWidth + j).x) < 3500
				&& abs(userPosition.z - cityBlocksPositions.at(i*cityWidth + j).z) < 3000){
			another = rotate(another, cityBlocksRotations.at(i*cityWidth + j), vec3(0,1,0));
			cityBlocks.at(i*cityWidth + j)->Draw(projection, another, size, 0);
			}

			
		}
		waterWidthOffset = widthOffset;
		widthOffset = 0;
		lengthOffset += this->cityBlocksDimensions.at(i*cityWidth).length;
	}

	buildingsInitialized = true;

	mat4 waterMatrix = modelview;
	waterMatrix = translate(modelview, vec3(-5000,0,-5000));
	water->Draw(projection, waterMatrix, size, time);
	waterMatrix = translate(modelview, vec3(5000,0,-5000));
	water->Draw(projection, waterMatrix, size, time);
	waterMatrix = translate(modelview, vec3(-5000,0,5000));
	water->Draw(projection, waterMatrix, size, time);
	waterMatrix = translate(modelview, vec3(waterWidthOffset+5000,0,5000));
	water->Draw(projection, waterMatrix, size, time);

	mat4 buildingMatrix = modelview;

	float length0 = 3000;  //inside the city, this might be good enough
	// closer the angle is to 85, more length5 should be
	//closer the angle is to 5, more length5n should be
	float length5 = 3000;float length5n = 3000;
	float length10 = 3000;float length10n = 3000;

	//Simpler plan for dealing with viewing buildings from the shores/park
		//If in a certain x/z range, draw the buildings in another specified x/z range

	//Simpler plan for dealing with buildings in the city 
		//Only draw buildings within a certain x/z range of you

	float modUserRot = fmod(userRotation, 180.f);
	bool insideCity = (userPosition.x > 150 && userPosition.x < 6560 && userPosition.z > 150 && userPosition.z < 9054);

	for(int i=0; i<cityBlocksBuildings.size(); i++){		
	//	if((abs(cityBlocksBuildingsPositions.at(i).x - userPosition.x) < 3000 && abs(cityBlocksBuildingsPositions.at(i).z - userPosition.z) < 200)
	//		|| (abs(cityBlocksBuildingsPositions.at(i).x - userPosition.x) < 200 && abs(cityBlocksBuildingsPositions.at(i).z - userPosition.z) < 3000)){

		float absDistX = abs(userPosition.x - cityBlocksBuildingsPositions.at(i).x);
		float absDistZ = abs(userPosition.z - cityBlocksBuildingsPositions.at(i).z);

		if(absDistX < 3500 && absDistZ < 3500){

			if(absDistX < 400 && absDistZ < 400
				|| cityBlocksBuildings.at(i) < 5){
				buildingMatrix = translate(modelview, cityBlocksBuildingsPositions.at(i));
				buildingMatrix = rotate(buildingMatrix, cityBlocksBuildingsRotations.at(i), vec3(0,1,0));
				building->buildingIndex = cityBlocksBuildings.at(i);
				building->Draw(projection, buildingMatrix, size, 0);
			}
			else{
			
				if(insideCity){ //inside the city
					//Forget frustum, just draw buildings along the lines
	
					if(modUserRot < 135 && modUserRot > 45){
						if(absDistZ < 500 && absDistX < 3500){
							buildingMatrix = translate(modelview, cityBlocksBuildingsPositions.at(i));
							buildingMatrix = rotate(buildingMatrix, cityBlocksBuildingsRotations.at(i), vec3(0,1,0));
							building->buildingIndex = cityBlocksBuildings.at(i);
							building->Draw(projection, buildingMatrix, size, 0);
						}
					}
					else{
						if(absDistX < 500  && absDistZ < 3500){
							buildingMatrix = translate(modelview, cityBlocksBuildingsPositions.at(i));
							buildingMatrix = rotate(buildingMatrix, cityBlocksBuildingsRotations.at(i), vec3(0,1,0));
							building->buildingIndex = cityBlocksBuildings.at(i);
							building->Draw(projection, buildingMatrix, size, 0);
						}
					}
					
				}
				else{ //outside the city
					//stop using frustum, only draw a certain range along the city boundary and all those in a line with the user
					
					//(userPosition.x > 150 && userPosition.x < 6560 && userPosition.z > 150 && userPosition.z < 9054)
					bool alreadyDrawn = false;
					if(userPosition.x <= 150){
						if(cityBlocksBuildingsPositions.at(i).x < 550 || (absDistZ < 500 && absDistX < 3000)){
							buildingMatrix = translate(modelview, cityBlocksBuildingsPositions.at(i));
							buildingMatrix = rotate(buildingMatrix, cityBlocksBuildingsRotations.at(i), vec3(0,1,0));
							building->buildingIndex = cityBlocksBuildings.at(i);
							building->Draw(projection, buildingMatrix, size, 0);
							alreadyDrawn = true;
						}
					}
					else if(userPosition.x >= 6560){
						if(cityBlocksBuildingsPositions.at(i).x > 6160 || (absDistZ < 500 && absDistX < 3000)){
							buildingMatrix = translate(modelview, cityBlocksBuildingsPositions.at(i));
							buildingMatrix = rotate(buildingMatrix, cityBlocksBuildingsRotations.at(i), vec3(0,1,0));
							building->buildingIndex = cityBlocksBuildings.at(i);
							building->Draw(projection, buildingMatrix, size, 0);
							alreadyDrawn = true;
						}
					}

					if(!alreadyDrawn){
						if(userPosition.z <= 150){
							if(cityBlocksBuildingsPositions.at(i).z < 550 || (absDistX < 500 && absDistZ < 3000)){
								buildingMatrix = translate(modelview, cityBlocksBuildingsPositions.at(i));
								buildingMatrix = rotate(buildingMatrix, cityBlocksBuildingsRotations.at(i), vec3(0,1,0));
								building->buildingIndex = cityBlocksBuildings.at(i);
								building->Draw(projection, buildingMatrix, size, 0);
							}
						}
						else if(userPosition.z >= 9054){
							if(cityBlocksBuildingsPositions.at(i).z > 8654 || (absDistX < 500 && absDistZ < 3000)){
								buildingMatrix = translate(modelview, cityBlocksBuildingsPositions.at(i));
								buildingMatrix = rotate(buildingMatrix, cityBlocksBuildingsRotations.at(i), vec3(0,1,0));
								building->buildingIndex = cityBlocksBuildings.at(i);
								building->Draw(projection, buildingMatrix, size, 0);
							}
						}
					}


					/*//Frustum Calculations
				
					userRotation = -userRotation;
					vec2 vert1 = vec2(userPosition.x,userPosition.z);vec2 vert2 = vec2(userPosition.x,userPosition.z);
					vec2 forward = vec2(-sin(userRotation*3.14/180), -cos(userRotation*3.14/180));
					vec2 left = vec2(-cos(-userRotation*3.14/180), -sin(-userRotation*3.14/180));
					vec2 right = -left;	
					userRotation = -userRotation;

				
				

					if(building->dimensions.at(cityBlocksBuildings.at(i)).y < 100){
						forward*=3000;left*=1700;right*=1700;
					}
					else if(building->dimensions.at(cityBlocksBuildings.at(i)).y < 200){
						forward*=3000;left*=1700;right*=1700;
					}
					else if(building->dimensions.at(cityBlocksBuildings.at(i)).y < 300){
						forward*=3000;left*=1700;right*=1700;
					}
					else if(building->dimensions.at(cityBlocksBuildings.at(i)).y < 400){
						forward*=3000;left*=1700;right*=1700;
					}
					else if(building->dimensions.at(cityBlocksBuildings.at(i)).y < 1000){
						forward*=4000;left*=2050;right*=2050;
					}
					else{
						forward*=7000;left*=4000;right*=4000;
					}

					vert1 += forward + left;
					vert2 += forward + right;

					if(PointInTriangle(vec2(cityBlocksBuildingsPositions.at(i).x, cityBlocksBuildingsPositions.at(i).z), 
						vec2(userPosition.x,userPosition.z), vert1, vert2)){
						buildingMatrix = translate(modelview, cityBlocksBuildingsPositions.at(i));
						buildingMatrix = rotate(buildingMatrix, cityBlocksBuildingsRotations.at(i), vec3(0,1,0));
						building->buildingIndex = cityBlocksBuildings.at(i);
						building->Draw(projection, buildingMatrix, size, 0);
					}
					*/
				}
			}
		}

		/*
		bool alreadyDrewBuilding = false;
		if(abs(userPosition.x - cityBlocksBuildingsPositions.at(i).x) < 3000 && abs(userPosition.z - cityBlocksBuildingsPositions.at(i).z) < 3000){
			if(userPosition.x > 150 && userPosition.x < 6560 && userPosition.z > 150){ // Inside the city
				if(buildingInFront(i, length0, 0, 400) ||
					buildingInFront(i, length5, 5, 200) || buildingInFront(i, length5n, -5, 200)
					|| buildingInFront(i, length10, 10, 200) || buildingInFront(i, length10n, -10, 200)
					|| cityBlocksBuildings.at(i) < 2 //for the bridge
					){
					buildingMatrix = translate(modelview, cityBlocksBuildingsPositions.at(i));
					buildingMatrix = rotate(buildingMatrix, cityBlocksBuildingsRotations.at(i), vec3(0,1,0));
					building->buildingIndex = cityBlocksBuildings.at(i);
					building->Draw(projection, buildingMatrix, size, 0);
					alreadyDrewBuilding = true;
				}
			}
			else{ //Outside the city

				if(userPosition.x <= 150 && !alreadyDrewBuilding){
					if(
						(cityBlocksBuildingsPositions.at(i).x < 700 || 
						(buildingInFront(i, length0, 0, 400) || buildingInFront(i, length5, 5, 200) || buildingInFront(i, length5n, -5, 200)))

						|| cityBlocksBuildings.at(i) < 2
						|| building->dimensions.at(cityBlocksBuildings.at(i)).y > 1000){
						buildingMatrix = translate(modelview, cityBlocksBuildingsPositions.at(i));
						buildingMatrix = rotate(buildingMatrix, cityBlocksBuildingsRotations.at(i), vec3(0,1,0));
						building->buildingIndex = cityBlocksBuildings.at(i);
						building->Draw(projection, buildingMatrix, size, 0);
						alreadyDrewBuilding = true;
					}
				}
				if(userPosition.x >= 6560 && !alreadyDrewBuilding){
					if(
						(cityBlocksBuildingsPositions.at(i).x > 5860 || 
						(buildingInFront(i, length0, 0, 400) || buildingInFront(i, length5, 5, 200) || buildingInFront(i, length5n, -5, 200)))

						|| cityBlocksBuildings.at(i) < 2
						|| building->dimensions.at(cityBlocksBuildings.at(i)).y > 1000){
						buildingMatrix = translate(modelview, cityBlocksBuildingsPositions.at(i));
						buildingMatrix = rotate(buildingMatrix, cityBlocksBuildingsRotations.at(i), vec3(0,1,0));
						building->buildingIndex = cityBlocksBuildings.at(i);
						building->Draw(projection, buildingMatrix, size, 0);
						alreadyDrewBuilding = true;
					}
				}
				if(userPosition.z <= 150 && !alreadyDrewBuilding){
					if(
						(cityBlocksBuildingsPositions.at(i).z < 700 ||
						(buildingInFront(i, length0, 0, 400) || buildingInFront(i, length5, 5, 200) || buildingInFront(i, length5n, -5, 200)
						))

						|| cityBlocksBuildings.at(i) < 2
						|| building->dimensions.at(cityBlocksBuildings.at(i)).y > 1000){
						buildingMatrix = translate(modelview, cityBlocksBuildingsPositions.at(i));
						buildingMatrix = rotate(buildingMatrix, cityBlocksBuildingsRotations.at(i), vec3(0,1,0));
						building->buildingIndex = cityBlocksBuildings.at(i);
						building->Draw(projection, buildingMatrix, size, 0);
						alreadyDrewBuilding = true;
					}
				}
			}
		}*/
	}
	

	if (this->GLReturnedError("City::Draw - on exit")){
		return;
	}
}


bool City::buildingInFront(int buildingIndex, float distance, float angleOffset, float buffer){
	if(distance > 0){
		
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

	}
	return false;
}

float City::sign(vec2 p1, vec2 p2, vec2 p3)
{
  return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

bool City::PointInTriangle(vec2 pt, vec2 v1, vec2 v2, vec2 v3)
{
  bool b1, b2, b3;

  b1 = sign(pt, v1, v2) < 0.0f;
  b2 = sign(pt, v2, v3) < 0.0f;
  b3 = sign(pt, v3, v1) < 0.0f;

  return ((b1 == b2) && (b2 == b3));
}

bool CCW(vec2 C, vec2 W1, vec2 W2){
	vec2 ab = W1-C;
	vec2 ac = W2-C;
	double y = (ab.x * ac.y) - (ab.y * ac.x);

    // dot product
    double x = (ab.x * ab.y) + (ac.x * ac.y);

	return atan2(y, x) > 0;
}

bool City::linesIntersect(vec2 a1, vec2 a2, vec2 b1, vec2 b2){
	return (CCW(a1, b1, b2) != CCW(a2, b1, b2)) && (CCW(b1, a1, a2) != CCW(b2, a1, a2));
}


void City::loadBuildings(){
cityBlocksBuildings.push_back(0);cityBlocksBuildingsPositions.push_back(vec3(6660, 0, 138));cityBlocksBuildingsRotations.push_back(0);
cityBlocksBuildings.push_back(1);cityBlocksBuildingsPositions.push_back(vec3(7260, 0, 138));cityBlocksBuildingsRotations.push_back(0);
cityBlocksBuildings.push_back(1);cityBlocksBuildingsPositions.push_back(vec3(8334, 0, 138));cityBlocksBuildingsRotations.push_back(0);
cityBlocksBuildings.push_back(1);cityBlocksBuildingsPositions.push_back(vec3(9408, 0, 138));cityBlocksBuildingsRotations.push_back(0);
cityBlocksBuildings.push_back(1);cityBlocksBuildingsPositions.push_back(vec3(10482, 0, 138));cityBlocksBuildingsRotations.push_back(0);

cityBlocksBuildings.push_back(0);cityBlocksBuildingsPositions.push_back(vec3(6660, 0, 7050));cityBlocksBuildingsRotations.push_back(0);
cityBlocksBuildings.push_back(1);cityBlocksBuildingsPositions.push_back(vec3(7260, 0, 7050));cityBlocksBuildingsRotations.push_back(0);
cityBlocksBuildings.push_back(1);cityBlocksBuildingsPositions.push_back(vec3(8334, 0, 7050));cityBlocksBuildingsRotations.push_back(0);
cityBlocksBuildings.push_back(1);cityBlocksBuildingsPositions.push_back(vec3(9408, 0, 7050));cityBlocksBuildingsRotations.push_back(0);
cityBlocksBuildings.push_back(1);cityBlocksBuildingsPositions.push_back(vec3(10482, 0, 7050));cityBlocksBuildingsRotations.push_back(0);
}