/*
Name: Clayton Suplinski
Project: First-Person Shooter
*/

#include "desert.h"

Desert::Desert() : Object(){}

Desert::~Desert(){}

bool Desert::Initialize()
{
	if (this->GLReturnedError("Desert::Initialize - on entry"))
		return false;

	terrain = new Gengar();
	terrain->order = 1;
	terrain->Initialize("./models/terrain/desert1.obj", "./models/terrain/desert1.png", "basic_texture_shader.vert", "basic_texture_shader.frag");

	terrain2 = new Gengar();
	terrain2->order = 1;
	terrain2->Initialize("./models/terrain/desert2.obj", "./models/terrain/desert2.png", "basic_texture_shader.vert", "basic_texture_shader.frag");

	/*
	vector<vector<vec3>> terrainFaces;
	vector<vector<vec3>> roadTerrainFaces;

	for(int i=0; i<terrain->gengar_faces.size()-9; i+=9){
		vector<vec3> tmpTerrainFace;
		tmpTerrainFace.push_back(vec3(terrain->gengar_vertices.at(terrain->gengar_faces.at(i)-1)));
		tmpTerrainFace.push_back(vec3(terrain->gengar_vertices.at(terrain->gengar_faces.at(i+3)-1)));
		tmpTerrainFace.push_back(vec3(terrain->gengar_vertices.at(terrain->gengar_faces.at(i+6)-1)));
		terrainFaces.push_back(tmpTerrainFace);

		if((tmpTerrainFace.at(0).y == 30 && tmpTerrainFace.at(1).y == 30 && tmpTerrainFace.at(2).y == 30)
			|| (tmpTerrainFace.at(0).y == 30.5 && tmpTerrainFace.at(1).y == 30.5 && tmpTerrainFace.at(2).y == 30.5)
			|| (tmpTerrainFace.at(0).y == 20 && tmpTerrainFace.at(1).y == 20 && tmpTerrainFace.at(2).y == 20)){
				roadTerrainFaces.push_back(tmpTerrainFace);
		}
	}

	for(int i=0; i<500; i++){
		float tmpTreeX = rand() % 8000 - 4000;
		float tmpTreeZ = rand() % 10000 -5000;
		float tmpTreeY = 0;
		bool placeTheTree = false;
		for(int j=0; j<terrainFaces.size(); j++){
			
				if(PointInTriangle(vec2(tmpTreeX, tmpTreeZ), 
					vec2(terrainFaces.at(j).at(0).x, terrainFaces.at(j).at(0).z), 
					vec2(terrainFaces.at(j).at(1).x, terrainFaces.at(j).at(1).z), 
					vec2(terrainFaces.at(j).at(2).x, terrainFaces.at(j).at(2).z))){

						bool treeOnRoad = false;
						for(int k=0; k<roadTerrainFaces.size(); k++){
							if((abs(tmpTreeX-roadTerrainFaces.at(k).at(0).x) < 100 && abs(tmpTreeZ-roadTerrainFaces.at(k).at(0).z) < 100)
								|| (abs(tmpTreeX-roadTerrainFaces.at(k).at(1).x) < 100 && abs(tmpTreeZ-roadTerrainFaces.at(k).at(1).z) < 100)
								|| (abs(tmpTreeX-roadTerrainFaces.at(k).at(2).x) < 100 && abs(tmpTreeZ-roadTerrainFaces.at(k).at(2).z) < 100)){
								treeOnRoad = true;
								k+=roadTerrainFaces.size()+5;
							}
						}

						if(!treeOnRoad){
						vec3 currTreePoint = vec3(tmpTreeX, 0, tmpTreeZ);
						vec3 crossOfFace = cross(terrainFaces.at(j).at(0)-terrainFaces.at(j).at(2), terrainFaces.at(j).at(1)-terrainFaces.at(j).at(2));
						float crossOfFaceOffset = -dot(crossOfFace, terrainFaces.at(j).at(0));
						tmpTreeY = -(crossOfFace.x * tmpTreeX + crossOfFace.z * tmpTreeZ + crossOfFaceOffset)/crossOfFace.y;
					
							tmpTreeY-=1;
							
							placeTheTree = true;
						}
						j+=terrainFaces.size()+5;
				}
			
		}

		if(placeTheTree){
		environmentObjectIndices.push_back(4);
		environmentObjectRotations.push_back(rand() % 360);
		environmentObjectsPositions.push_back(vec3(tmpTreeX, tmpTreeY, tmpTreeZ));
		}
	}
	*/

	initCacti();
	
	if (this->GLReturnedError("Desert::Initialize - on exit"))
		return false;

	return true;
}

void Desert::saveBuildingVertices(){
	ofstream outputFile;
outputFile.open("desertPositions.txt");

for(int i=0; i<environmentObjectsPositions.size(); i++){
	outputFile << "environmentObjectIndices.push_back(" << environmentObjectIndices.at(i) 
		<< ");environmentObjectsPositions.push_back(vec3(" << environmentObjectsPositions.at(i).x << ", " << environmentObjectsPositions.at(i).y << ", "
		<< (environmentObjectsPositions.at(i).z+4400)
		<< "));environmentObjectRotations.push_back(" << environmentObjectRotations.at(i) << ");" << endl;
}

outputFile.close();
}

void Desert::TakeDown(){super::TakeDown();}

void Desert::Draw(const mat4 & projection, mat4 modelview, const ivec2 & size, const float time){

	if (this->GLReturnedError("Desert ::Draw - on entry")){
		return;	
	}
	
	terrain->Draw(projection, modelview, size, time);

	mat4 another = modelview;

	another = translate(another, vec3(0,0,4400));
	terrain2->Draw(projection, another, size, time);

	mat4 objectMat = modelview;
	float objectClippingDistanceX = 3000;float objectClippingDistanceZ = 3000;
	float absUserX = abs(userPosition.x);float absUserZ = abs(userPosition.z);
	bool expandX = absUserX > 4000;bool expandZ = absUserZ > 5000;
	if(expandX || expandZ){objectClippingDistanceX=5000;objectClippingDistanceZ=5000;}
	
	for(int i=0; i<environmentObjectIndices.size(); i++){
		float absDiffX = abs(environmentObjectsPositions.at(i).x - userPosition.x);
		float absDiffZ = abs(environmentObjectsPositions.at(i).z - userPosition.z);
		if(absDiffX < objectClippingDistanceX && absDiffZ < objectClippingDistanceZ){
		objectMat = translate(modelview, environmentObjectsPositions.at(i));
		objectMat = rotate(objectMat, environmentObjectRotations.at(i), vec3(0,1,0));
		environmentObject->objectIndex = environmentObjectIndices.at(i);
		environmentObject->Draw(projection, objectMat, size, time);
		}
	}

	if (this->GLReturnedError("Desert::Draw - on exit")){
		return;
	}
}


bool Desert::buildingInFront(int buildingIndex, float distance, float angleOffset, float buffer){
	/*if(distance > 0){
		
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

	}*/
	return false;
}

bool Desert::CCW(vec2 C, vec2 W1, vec2 W2){
	vec2 ab = W1-C;
	vec2 ac = W2-C;
	double y = (ab.x * ac.y) - (ab.y * ac.x);

    // dot product
    double x = (ab.x * ab.y) + (ac.x * ac.y);

	return atan2(y, x) > 0;
}

bool Desert::linesIntersect(vec2 a1, vec2 a2, vec2 b1, vec2 b2){
	return (CCW(a1, b1, b2) != CCW(a2, b1, b2)) && (CCW(b1, a1, a2) != CCW(b2, a1, a2));
}

float Desert::sign(vec2 p1, vec2 p2, vec2 p3)
{
  return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

bool Desert::PointInTriangle(vec2 pt, vec2 v1, vec2 v2, vec2 v3)
{
  bool b1, b2, b3;

  b1 = sign(pt, v1, v2) < 0.0f;
  b2 = sign(pt, v2, v3) < 0.0f;
  b3 = sign(pt, v3, v1) < 0.0f;

  return ((b1 == b2) && (b2 == b3));
}


void Desert::initCacti(){
	environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(3951, 1.65625, 129));environmentObjectRotations.push_back(62);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(2541, 29.222, -1292));environmentObjectRotations.push_back(4);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-1435, 108.66, 882));environmentObjectRotations.push_back(200);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-147, 19, 558));environmentObjectRotations.push_back(42);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-792, 35.993, -99));environmentObjectRotations.push_back(331);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(2951, 47.1393, -1531));environmentObjectRotations.push_back(305);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-358, 19, -1640));environmentObjectRotations.push_back(354);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-1351, 96.9825, -633));environmentObjectRotations.push_back(245);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(2482, 54.5682, 1188));environmentObjectRotations.push_back(32);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-3975, -2.09375, -466));environmentObjectRotations.push_back(186);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(2203, 54.5682, 1565));environmentObjectRotations.push_back(128);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(655, 44.7501, -878));environmentObjectRotations.push_back(312);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(2759, 19, 2086));environmentObjectRotations.push_back(57);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-3973, -1.78125, -324));environmentObjectRotations.push_back(42);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-2874, 58.4628, -284));environmentObjectRotations.push_back(114);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-415, 19, -1206));environmentObjectRotations.push_back(101);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-158, 19, 986));environmentObjectRotations.push_back(159);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(2435, 19, 339));environmentObjectRotations.push_back(107);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(982, 41.4132, -1029));environmentObjectRotations.push_back(232);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(1244, 49.9977, 1445));environmentObjectRotations.push_back(0);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(2288, 37.5925, 1579));environmentObjectRotations.push_back(308);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(1756, 19, -1861));environmentObjectRotations.push_back(84);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(1141, 42.2696, -463));environmentObjectRotations.push_back(37);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(2106, 54.5682, 1490));environmentObjectRotations.push_back(63);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(2097, 29.222, -752));environmentObjectRotations.push_back(329);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(3989, -4.28125, 1487));environmentObjectRotations.push_back(137);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-654, 53.9543, -1655));environmentObjectRotations.push_back(153);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-808, 31.0152, -70));environmentObjectRotations.push_back(121);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(3011, 62.2807, -1504));environmentObjectRotations.push_back(286);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(674, 44.9863, -1073));environmentObjectRotations.push_back(9);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(1094, 24.4785, 1861));environmentObjectRotations.push_back(267);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-3998, -5.6875, -1507));environmentObjectRotations.push_back(259);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-2154, 38.5502, 1706));environmentObjectRotations.push_back(105);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-3045, 47.6975, 1021));environmentObjectRotations.push_back(87);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(3278, 19, -330));environmentObjectRotations.push_back(292);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-1054, 80.9469, 1608));environmentObjectRotations.push_back(191);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-3121, 47.6975, 1012));environmentObjectRotations.push_back(203);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-3552, 19, 548));environmentObjectRotations.push_back(182);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(3949, 1.96875, -604));environmentObjectRotations.push_back(123);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-3168, 30.0114, -999));environmentObjectRotations.push_back(127);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-3113, 60.0003, -563));environmentObjectRotations.push_back(56);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(1106, 35.4633, 1710));environmentObjectRotations.push_back(343);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(1221, 47.3279, 266));environmentObjectRotations.push_back(280);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-3125, 60.0003, -601));environmentObjectRotations.push_back(303);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-666, 76.362, 1655));environmentObjectRotations.push_back(279);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(3924, 5.875, 1878));environmentObjectRotations.push_back(32);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(3809, 19, 1203));environmentObjectRotations.push_back(245);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(1416, 68.0498, 652));environmentObjectRotations.push_back(327);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-2650, 60.0003, 60));environmentObjectRotations.push_back(323);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-2662, 47.6975, 759));environmentObjectRotations.push_back(206);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(1955, 38.3802, 16));environmentObjectRotations.push_back(104);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(3995, -5.21875, -1246));environmentObjectRotations.push_back(48);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(2767, 53.5982, 1106));environmentObjectRotations.push_back(319);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(949, 44.9863, -812));environmentObjectRotations.push_back(285);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-3515, 51.3003, -964));environmentObjectRotations.push_back(44);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-2254, 54.8257, 43));environmentObjectRotations.push_back(303);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(2966, 76.2709, 731));environmentObjectRotations.push_back(124);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-1888, 66.8061, -588));environmentObjectRotations.push_back(102);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-1605, 89.8489, -643));environmentObjectRotations.push_back(241);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(2417, 19, -2096));environmentObjectRotations.push_back(250);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(2584, 38.3802, -642));environmentObjectRotations.push_back(68);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-2984, 45.6502, -546));environmentObjectRotations.push_back(187);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-3144, 41.1774, -119));environmentObjectRotations.push_back(29);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(642, 50.7734, 848));environmentObjectRotations.push_back(318);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-1478, 37.5591, -992));environmentObjectRotations.push_back(307);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-3220, 51.3003, -1452));environmentObjectRotations.push_back(316);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(1056, 60.9017, 1120));environmentObjectRotations.push_back(6);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(3963, -0.21875, 1477));environmentObjectRotations.push_back(209);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(1829, 44.1762, 940));environmentObjectRotations.push_back(343);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-3393, 41.7786, 1015));environmentObjectRotations.push_back(57);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(1456, 44.9863, 14));environmentObjectRotations.push_back(82);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-944, 93.1524, 443));environmentObjectRotations.push_back(280);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-646, 56.7622, -426));environmentObjectRotations.push_back(180);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-769, 89.5745, -1548));environmentObjectRotations.push_back(67);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-1480, 102.693, -248));environmentObjectRotations.push_back(214);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-1588, 19, 1434));environmentObjectRotations.push_back(150);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(1234, 60.9017, 1023));environmentObjectRotations.push_back(55);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-2699, 124.349, 453));environmentObjectRotations.push_back(170);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-1975, 47.343, -950));environmentObjectRotations.push_back(200);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(2732, 65.7191, 4012));environmentObjectRotations.push_back(69);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-1250, 45.6003, 4772));environmentObjectRotations.push_back(79);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(3304, 19, 3538));environmentObjectRotations.push_back(128);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-3464, 21.0175, 3458));environmentObjectRotations.push_back(242);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(3809, 5.93751, 6066));environmentObjectRotations.push_back(342);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(782, 31.0334, 6059));environmentObjectRotations.push_back(324);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-1322, 0.772727, 6574));environmentObjectRotations.push_back(172);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-178, 19, 5385));environmentObjectRotations.push_back(148);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(904, 49.4675, 5403));environmentObjectRotations.push_back(212);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-3453, 20.9894, 3918));environmentObjectRotations.push_back(316);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-1265, 16.2886, 5212));environmentObjectRotations.push_back(309);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(3851, 3.31251, 3619));environmentObjectRotations.push_back(35);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(3209, 27.7975, 6119));environmentObjectRotations.push_back(13);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-3109, 33.9189, 3224));environmentObjectRotations.push_back(40);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-1263, 19, 2318));environmentObjectRotations.push_back(243);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-2418, 16.3759, 2626));environmentObjectRotations.push_back(172);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(1238, 69.4007, 4963));environmentObjectRotations.push_back(0);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-543, 39.1734, 4277));environmentObjectRotations.push_back(182);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(3725, 11.1875, 4411));environmentObjectRotations.push_back(165);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-2225, 7.14531, 4673));environmentObjectRotations.push_back(199);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-2568, 23.0539, 2555));environmentObjectRotations.push_back(307);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-3708, 16.8607, 2595));environmentObjectRotations.push_back(69);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(2874, 56.1872, 3865));environmentObjectRotations.push_back(334);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-1450, 77.364, 4569));environmentObjectRotations.push_back(24);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(2951, 47.9286, 4376));environmentObjectRotations.push_back(279);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-3350, 30.6555, 5072));environmentObjectRotations.push_back(127);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(977, 52.7143, 5567));environmentObjectRotations.push_back(311);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(3038, 54.5683, 5317));environmentObjectRotations.push_back(238);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-3954, 7.79438, 6459));environmentObjectRotations.push_back(228);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-2935, 5.04142, 3577));environmentObjectRotations.push_back(74);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(2255, 50.2792, 5944));environmentObjectRotations.push_back(252);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-3540, 19, 2508));environmentObjectRotations.push_back(353);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-3048, 5.75, 6501));environmentObjectRotations.push_back(66);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-2575, 36.3468, 4000));environmentObjectRotations.push_back(352);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-3541, 25.3402, 3108));environmentObjectRotations.push_back(105);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-155, 19, 3987));environmentObjectRotations.push_back(32);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(3356, 29.2199, 5843));environmentObjectRotations.push_back(28);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(3108, 43.2054, 5706));environmentObjectRotations.push_back(210);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(1129, 39.6497, 2903));environmentObjectRotations.push_back(278);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(997, 19, 2454));environmentObjectRotations.push_back(14);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(2040, 58.4333, 4519));environmentObjectRotations.push_back(116);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-250, 19, 3977));environmentObjectRotations.push_back(213);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(2228, 40.7057, 5648));environmentObjectRotations.push_back(275);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(2636, 19, 2443));environmentObjectRotations.push_back(128);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(571, 39.2535, 4156));environmentObjectRotations.push_back(220);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-1875, 22.4832, 6128));environmentObjectRotations.push_back(232);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(608, 19, 2466));environmentObjectRotations.push_back(132);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-1094, 5.47727, 6505));environmentObjectRotations.push_back(306);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-1978, -0.823169, 4552));environmentObjectRotations.push_back(136);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(2892, 41.9916, 5840));environmentObjectRotations.push_back(135);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-671, 54.0542, 3840));environmentObjectRotations.push_back(338);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-1326, 48.0821, 3079));environmentObjectRotations.push_back(256);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-2286, -5.6939, 4308));environmentObjectRotations.push_back(207);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(1890, 26.7023, 2553));environmentObjectRotations.push_back(68);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(2199, 63.3753, 5253));environmentObjectRotations.push_back(215);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-3024, 50.6368, 4033));environmentObjectRotations.push_back(45);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(3628, 1.61363, 6536));environmentObjectRotations.push_back(95);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(999, 57.0319, 5387));environmentObjectRotations.push_back(301);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-2996, 81.3802, 4250));environmentObjectRotations.push_back(128);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(3024, 19.907, 6288));environmentObjectRotations.push_back(152);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(1690, 33.3476, 3978));environmentObjectRotations.push_back(256);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-1757, 26.6695, 6190));environmentObjectRotations.push_back(40);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-3638, 8.59387, 6458));environmentObjectRotations.push_back(324);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(3331, 28.5846, 5951));environmentObjectRotations.push_back(238);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(3466, 19, 2917));environmentObjectRotations.push_back(300);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(2285, 65.0708, 5821));environmentObjectRotations.push_back(307);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(1119, 62.0053, 5425));environmentObjectRotations.push_back(28);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-2776, 40.2606, 4828));environmentObjectRotations.push_back(355);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(2645, 69.7917, 5617));environmentObjectRotations.push_back(110);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(2177, 16.4545, 6344));environmentObjectRotations.push_back(222);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-3378, 30.2366, 5127));environmentObjectRotations.push_back(53);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(2789, 66.3266, 4480));environmentObjectRotations.push_back(254);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-3957, 12.2193, 6394));environmentObjectRotations.push_back(202);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(3848, 3.50001, 4299));environmentObjectRotations.push_back(265);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(1596, 30.1251, 3558));environmentObjectRotations.push_back(215);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-1893, 15.1963, 5671));environmentObjectRotations.push_back(220);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-2413, 28.5973, 5537));environmentObjectRotations.push_back(147);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-3969, -1.80527, 2748));environmentObjectRotations.push_back(248);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(266, -0.522727, 6593));environmentObjectRotations.push_back(25);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-1034, 38.5416, 5764));environmentObjectRotations.push_back(232);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-3505, 19, 2491));environmentObjectRotations.push_back(159);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-627, 17.5455, 6328));environmentObjectRotations.push_back(145);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(1873, 26.6076, 3140));environmentObjectRotations.push_back(248);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-954, 40.7156, 3058));environmentObjectRotations.push_back(43);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-3780, 11.6531, 4673));environmentObjectRotations.push_back(127);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-563, 16.2251, 5295));environmentObjectRotations.push_back(135);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-580, 43.9499, 3991));environmentObjectRotations.push_back(16);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-1050, 72.7158, 4606));environmentObjectRotations.push_back(18);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-3881, 26.2802, 5155));environmentObjectRotations.push_back(27);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-89, 19, 3793));environmentObjectRotations.push_back(20);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(2252, 6.22727, 6494));environmentObjectRotations.push_back(298);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(1394, 39.4093, 6128));environmentObjectRotations.push_back(42);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-1372, -0.454546, 6592));environmentObjectRotations.push_back(20);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-1066, 2.79141, 6034));environmentObjectRotations.push_back(138);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(3058, 45.8356, 5499));environmentObjectRotations.push_back(13);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(600, 33.9025, 5284));environmentObjectRotations.push_back(128);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-2970, 9.03434, 2618));environmentObjectRotations.push_back(284);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-3804, 5.48243, 6498));environmentObjectRotations.push_back(44);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-2597, 51.1641, 5275));environmentObjectRotations.push_back(249);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-1026, 31.5025, 3706));environmentObjectRotations.push_back(131);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(3682, 13.875, 2940));environmentObjectRotations.push_back(132);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-3036, 32.7394, 5528));environmentObjectRotations.push_back(297);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-1604, 45.0163, 3991));environmentObjectRotations.push_back(252);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-1265, 53.5706, 3074));environmentObjectRotations.push_back(241);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(259, 19, 3076));environmentObjectRotations.push_back(38);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(950, 62.565, 4715));environmentObjectRotations.push_back(350);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-625, 16.1236, 2618));environmentObjectRotations.push_back(117);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(950, 40.8217, 5854));environmentObjectRotations.push_back(331);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(899, 50.6143, 3491));environmentObjectRotations.push_back(149);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(1974, 49.0475, 5092));environmentObjectRotations.push_back(265);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-3036, 47.3368, 4722));environmentObjectRotations.push_back(257);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-2945, 19, 2308));environmentObjectRotations.push_back(319);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(1141, 66.0899, 3436));environmentObjectRotations.push_back(354);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(1247, 56.0358, 5521));environmentObjectRotations.push_back(104);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(268, 19, 4699));environmentObjectRotations.push_back(341);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-1118, 35.4274, 3921));environmentObjectRotations.push_back(84);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(93, 19, 6184));environmentObjectRotations.push_back(15);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-2092, -5.6939, 4269));environmentObjectRotations.push_back(264);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(907, 88.3781, 4301));environmentObjectRotations.push_back(275);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(3575, 19, 2262));environmentObjectRotations.push_back(48);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(817, 50.3449, 5091));environmentObjectRotations.push_back(225);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(685, 41.3055, 3782));environmentObjectRotations.push_back(184);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-3178, 81.8609, 4585));environmentObjectRotations.push_back(31);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-2776, 68.3403, 4219));environmentObjectRotations.push_back(60);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-3520, 14.3103, 2922));environmentObjectRotations.push_back(14);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(142, 19, 5875));environmentObjectRotations.push_back(77);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-3584, 21.8719, 4669));environmentObjectRotations.push_back(70);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-3405, 16.5909, 6342));environmentObjectRotations.push_back(333);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-3969, 3.90753, 5427));environmentObjectRotations.push_back(288);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-1984, 46.5282, 3435));environmentObjectRotations.push_back(220);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(3711, 12.0625, 3880));environmentObjectRotations.push_back(313);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-3934, 7.62067, 6010));environmentObjectRotations.push_back(302);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(536, 45.4327, 4390));environmentObjectRotations.push_back(100);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-3039, 9.63636, 6444));environmentObjectRotations.push_back(269);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(1256, 55.6126, 5510));environmentObjectRotations.push_back(295);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-897, 52.9783, 3845));environmentObjectRotations.push_back(120);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-1401, 8.63462, 6177));environmentObjectRotations.push_back(224);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(1397, 53.1745, 3763));environmentObjectRotations.push_back(33);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(3863, 5.59019, 2513));environmentObjectRotations.push_back(56);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-2347, -0.172007, 4601));environmentObjectRotations.push_back(213);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(2895, 79.9821, 5128));environmentObjectRotations.push_back(40);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-2604, 17.8842, 6116));environmentObjectRotations.push_back(51);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(1660, 36.2811, 5448));environmentObjectRotations.push_back(205);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(2370, 19, 2374));environmentObjectRotations.push_back(319);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(3065, 32.6175, 3927));environmentObjectRotations.push_back(0);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-3601, 18.9549, 4303));environmentObjectRotations.push_back(113);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(1709, 51.8377, 2838));environmentObjectRotations.push_back(24);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-1419, 0.801903, 3664));environmentObjectRotations.push_back(124);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(905, 11.3409, 6419));environmentObjectRotations.push_back(111);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-3798, 7.90863, 3106));environmentObjectRotations.push_back(133);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-610, 47.9496, 4742));environmentObjectRotations.push_back(256);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-2779, 3.41007, 3500));environmentObjectRotations.push_back(197);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(1466, 67.4295, 5832));environmentObjectRotations.push_back(345);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-2866, 0.704545, 6575));environmentObjectRotations.push_back(329);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(2964, 1.18182, 6568));environmentObjectRotations.push_back(199);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(1938, 60.7629, 4377));environmentObjectRotations.push_back(358);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(3099, 36.7418, 5906));environmentObjectRotations.push_back(73);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(3429, 19, 2367));environmentObjectRotations.push_back(278);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-1754, 8.36311, 5265));environmentObjectRotations.push_back(296);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(1732, 34.0312, 5267));environmentObjectRotations.push_back(29);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(3965, -3.81249, 3023));environmentObjectRotations.push_back(138);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(1883, 74.0398, 5413));environmentObjectRotations.push_back(106);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-3917, 0.821933, 2930));environmentObjectRotations.push_back(41);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(3621, 17.6875, 5291));environmentObjectRotations.push_back(145);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(1626, 32.7575, 5010));environmentObjectRotations.push_back(163);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-3354, 18.8269, 5388));environmentObjectRotations.push_back(177);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(1540, 29.9954, 5365));environmentObjectRotations.push_back(171);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(2902, 40.1108, 5874));environmentObjectRotations.push_back(158);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-2965, 15.2955, 6361));environmentObjectRotations.push_back(180);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(2968, 60.7722, 5014));environmentObjectRotations.push_back(357);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(3820, 5.25001, 5797));environmentObjectRotations.push_back(80);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(278, 19, 6106));environmentObjectRotations.push_back(168);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-2586, 3.56818, 6533));environmentObjectRotations.push_back(295);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-2591, 18.279, 6282));environmentObjectRotations.push_back(164);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-3908, 1.00784, 2814));environmentObjectRotations.push_back(39);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-2270, 14.9092, 5743));environmentObjectRotations.push_back(206);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-3304, 23.8246, 5464));environmentObjectRotations.push_back(85);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(2901, 24.3167, 2588));environmentObjectRotations.push_back(342);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(3056, 39.4977, 5819));environmentObjectRotations.push_back(326);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-1764, 27.8957, 2849));environmentObjectRotations.push_back(256);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-3040, 13.6214, 3561));environmentObjectRotations.push_back(91);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-2855, -0.49827, 5093));environmentObjectRotations.push_back(207);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(1660, 43.4794, 3592));environmentObjectRotations.push_back(338);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(458, 19, 2638));environmentObjectRotations.push_back(95);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-3579, 30.4645, 4952));environmentObjectRotations.push_back(145);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(2880, 52.2458, 4735));environmentObjectRotations.push_back(115);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(2870, 57.3391, 4366));environmentObjectRotations.push_back(96);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-3188, 32.2682, 4826));environmentObjectRotations.push_back(205);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-286, 19, 3323));environmentObjectRotations.push_back(113);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-189, 19, 2531));environmentObjectRotations.push_back(163);
environmentObjectIndices.push_back(4);environmentObjectsPositions.push_back(vec3(-3762, 36.1532, 5172));environmentObjectRotations.push_back(258);

}
