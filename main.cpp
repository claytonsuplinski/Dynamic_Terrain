/*
Name: Clayton Suplinski
Project: First-Person Shooter
*/

#include <time.h>       
#include <vector>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "shader_utils.h"

#include "cube2.h"
#include "globals.h"
#include "menu.h"
#include "precip.h"
#include "cylinder.h"
#include "city.h"

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

using namespace std;
using namespace glm;

#include <iostream>
#include <list>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>

#include <boost/geometry/io/wkt/wkt.hpp>

//The projection and modelview matrices. 
mat4 projection, modelview;

//x (0=Normal, 1=night, 2=twilight), y(0=normal, 1=underwater, 2=fog)
ivec2 tod = ivec2(0, 2);

//Perspective viewpoints (set to specific values later)
vec3 lookAtCenter;
vec3 lookAtEye;

//Creates a class for maintaining the window information for easy access.
class Window
{
public:
	Window()
	{
		this->time_last_pause_began = this->total_time_paused = 0;
		this->wireframe = this->paused = false;
		this->interval = 8;this->window_handle = -1;
	}
	float time_last_pause_began;float total_time_paused;bool paused , wireframe;
	int window_handle;int interval;ivec2 size;float window_aspect;
} window;

/////////////////////////////////////VARIABLE DECLARATIONS/////////////////////////////
int viewPerspective = 0; //Select amongst 1st and 3rd person views
int weatherType = 0; //Select amongst the weather types

//Keeps track of the time
float current_timeDisplay;

Cylinder healthBar;
Precip precip;
Cube2 skybox;Menu menu;
City city;

bool stadiumLoaded = false;

float velocity2 = 0;float maxUserVelocity = 1.0;

//Used to calculate the user's distance from buildings for optimization
float * gmTransX, * gmTransY, * gmTransZ;
double * gmRotatedX, * gmRotatedY;

bool gameOver;

//Keyboard flags
bool ePressed, wPressed, rPressed, zPressed, qPressed, aPressed, sPressed, dPressed;

//Values defining the position/rotation of the camera.
double RotatedX = 0;double RotatedY = 0;
float transX = 0;float transY = 0;float transZ = 0;

//Used to provide an angle for the snow falling when the user is moving
float movingWRTSnow = 0;

//Reset the game back to the main menu
void reset(){
	menu.reset();
	
	gameOver=false;stadiumLoaded = false;

	RotatedX = 0;RotatedY = 0;
	transX = 0;transY = 0;transZ = 0;movingWRTSnow = 0;
	velocity2 = 0;

	ePressed=false; wPressed=false; rPressed=false; zPressed=false; qPressed=false; aPressed=false; sPressed=false; dPressed=false;
}

//////////////////////////////////////TEXT RENDERING/////////////////////////////////////////////
////////Font variables//////////
GLuint program;GLint attribute_coord;GLint uniform_tex;GLint uniform_color;
struct point {GLfloat x;GLfloat y;GLfloat s;GLfloat t;};
GLuint vbo;FT_Library ft;FT_Face face;const char *fontfilename;
int init_resources()
{        /* Initialize the FreeType2 library */
        if(FT_Init_FreeType(&ft)){fprintf(stderr, "Could not init freetype library\n");return 0;}
        /* Load a font */
        if(FT_New_Face(ft, fontfilename, 0, &face)){fprintf(stderr, "Could not open font %s\n", fontfilename);return 0;}
        /* Compile and link the shader program */
        GLint link_ok = GL_FALSE;GLuint vs, fs;
        if ((vs = create_shader("text.vert", GL_VERTEX_SHADER))        == 0) return 0;
        if ((fs = create_shader("text.frag", GL_FRAGMENT_SHADER)) == 0) return 0;

        program = glCreateProgram();glAttachShader(program, vs);glAttachShader(program, fs);
        glLinkProgram(program);glGetProgramiv(program, GL_LINK_STATUS, &link_ok);
        if (!link_ok) {fprintf(stderr, "glLinkProgram:");print_log(program);return 0;}

        const char* attribute_name;attribute_name = "coord";
        attribute_coord = glGetAttribLocation(program, attribute_name);
        if (attribute_coord == -1) {fprintf(stderr, "Could not bind attribute %s\n", attribute_name);return 0;}

        const char* uniform_name;uniform_name = "tex";
        uniform_tex = glGetUniformLocation(program, uniform_name);
        if (uniform_tex == -1){fprintf(stderr, "Could not bind uniform %s\n", uniform_name);return 0;}

        uniform_name = "color";uniform_color = glGetUniformLocation(program, uniform_name);
        if (uniform_color == -1){fprintf(stderr, "Could not bind uniform %s\n", uniform_name);return 0;}

        // Create the vertex buffer object
        glGenBuffers(1, &vbo);
        return 1;
}

/**
 * Render text using the currently loaded font and currently set font size.
 * Rendering starts at coordinates (x, y), z is always 0.
 * The pixel coordinates that the FreeType2 library uses are scaled by (sx, sy).
 */
void render_text(const char *text, float x, float y, float sx, float sy) {
        const char *p;FT_GlyphSlot g = face->glyph;

        /* Create a texture that will be used to hold one "glyph" */
        GLuint tex;glActiveTexture(GL_TEXTURE0);
        glGenTextures(1, &tex);glBindTexture(GL_TEXTURE_2D, tex);
        glUniform1i(uniform_tex, 0);
        /* We require 1 byte alignment when uploading texture data */
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        /* Clamping to edges is important to prevent artifacts when scaling */
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        /* Linear filtering usually looks best for text */
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        /* Set up the VBO for our vertex data */
        glEnableVertexAttribArray(attribute_coord);glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(attribute_coord, 4, GL_FLOAT, GL_FALSE, 0, 0);
        /* Loop through all characters */
        for(p = text; *p; p++) {
                /* Try to load and render the character */
                if(FT_Load_Char(face, *p, FT_LOAD_RENDER))
                        continue;

                /* Upload the "bitmap", which contains an 8-bit grayscale image, as an alpha texture */
                glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, g->bitmap.width, g->bitmap.rows, 0, GL_ALPHA, GL_UNSIGNED_BYTE, g->bitmap.buffer);
                /* Calculate the vertex and texture coordinates */
                float x2 = x + g->bitmap_left * sx;float y2 = -y - g->bitmap_top * sy;
                float w = g->bitmap.width * sx;float h = g->bitmap.rows * sy;

                point box[4] = {
                        {x2,     -y2    , 0, 0}, {x2 + w, -y2    , 1, 0},
                        {x2,     -y2 - h, 0, 1}, {x2 + w, -y2 - h, 1, 1},
                };

                /* Draw the character on the screen */
                glBufferData(GL_ARRAY_BUFFER, sizeof box, box, GL_DYNAMIC_DRAW);
                glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

                /* Advance the cursor to the start of the next character */
                x += (g->advance.x >> 6) * sx;y += (g->advance.y >> 6) * sy;
        }
        glDisableVertexAttribArray(attribute_coord);glDeleteTextures(1, &tex);
}

void activeTextDisplay(const char* words, float x, float y, FT_UInt size, vec4 color)
{
		glDisable(GL_CULL_FACE);
        float sx = (float)(2.0/glutGet(GLUT_WINDOW_WIDTH));
        float sy = (float)(2.0/glutGet(GLUT_WINDOW_HEIGHT));

		/* Enable blending, necessary for our alpha texture */
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glUseProgram(program);

		/* Set font size to 48 pixels, color to black */
        FT_Set_Pixel_Sizes(face, 0, size);

		GLfloat black[4] = {color.x,color.y,color.z,color.w};glUniform4fv(uniform_color, 1, black);
		
		render_text(words,x,y,sx,sy); 
		
		glUseProgram(0);
		glEnable(GL_CULL_FACE);
}

////////////////////////////////////MOUSE DETECTION & MANAGEMENT/////////////////////////
//Mouse value/identification variables.
float mouseX = 0;float mouseY = 0;
float prevMouseY = (float)(window.size.y/2);
void mouseMovement(int x, int y) {
    mouseX=(float)x; //set lastx to the current x position
    mouseY=(float)y; //set lasty to the current y position
}

void mouseRotations(int stadium, int person){
	if(person == 1 || person == 3){
		//Turning controls
		if(mouseX < window.size.x/2){RotatedY -= abs((mouseX - window.size.x/2)/75);}
		else if(mouseX > window.size.x/2){RotatedY += abs((mouseX - window.size.x/2)/75);}
	}
	prevMouseY = mouseY;
}

/////////////////////////////////////CAMERA CONTROLS//////////////////////////////////////////
//Moves the camera according to user inputs -Draws things fitted to the environment
glm::mat4 render(mat4 Model){		
	Model = rotate(Model, (GLfloat) RotatedX, vec3(1,0,0));
	Model = rotate(Model, (GLfloat) RotatedY, vec3(0,1,0));
	Model = translate(Model, vec3(transX,0,0));    
	Model = translate(Model, vec3(0,0,transZ));    
	Model = translate(Model, vec3(0,-transY,0));	
	glLoadMatrixf(value_ptr(Model));
    return Model;
}

//Undoes the render function. -Use to draw independent of the environment (e.g. the user) 
glm::mat4 endRender(mat4 Model){	
	Model = translate(Model, vec3(0,transY,0));	
	Model = translate(Model, vec3(0,0,-transZ));
	Model = translate(Model, vec3(-transX,0,0));
	Model = rotate(Model, (GLfloat) -RotatedY, vec3(0,1,0));
	Model = rotate(Model, (GLfloat) -RotatedX, vec3(1,0,0));			
	glLoadMatrixf(value_ptr(Model));
    return Model;
}

//Changes the value of the angle in which the camera should be rotated vertically.
void rotateX(double angle){
    if(!(RotatedX>=89 && angle>0) && !(RotatedX<=-89 && angle<0)){RotatedX += angle;}
}

//Changes the value of the angle in which the camera should be rotated horizontally.
void rotateY(double angle){RotatedY += angle;}

//Deletes all of the created objects here.
void CloseFunc(){
	window.window_handle = -1;
	healthBar.TakeDown();
	skybox.TakeDown();
}

//Maintains aspect ratio when window is resized.
void ReshapeFunc(int w, int h){
	if (h > 0){window.size = ivec2(w, h);window.window_aspect = float(w) / float(h);}
}

//When a key is pressed down
void KeyboardFunc(unsigned char c, int x, int y){
	float current_time = float(glutGet(GLUT_ELAPSED_TIME)) / 1000.0f;

	switch (c){
		case 'e':ePressed = true;break;
		//case 'r':rPressed = true;break;
		case 'z':zPressed = true;break;
		case 'q':qPressed = true;break;
		case 'w':wPressed = true;break;
		case 's':sPressed = true;break;
		case 'a':aPressed = true;break;
		case 'd':dPressed = true;break;
		
		/*case 'n': //Reset back to main menu
			if(!menu.menuOn){
				reset();
			}
			break;*/

		case 'p': // Pause/unpause
			if(!menu.menuOn){
				if (window.paused == true){
					window.total_time_paused += (current_time - window.time_last_pause_began);
				}
				else{
					window.time_last_pause_began = current_time;
				}
				window.paused = !window.paused;
			}
			break;

		case 'r':
			city.currBuildingRotation+=90;
			if(city.currBuildingRotation >= 360){
				city.currBuildingRotation = 0;
			}
			break;
		case 'i':  //Toggles wireframe mode
			//window.wireframe = !window.wireframe;
			//+z
			city.currBuildingPosition.z++;
			break;
		case 'j':
			//+x
			city.currBuildingPosition.x++;
			break;
		case 'k':
			//-z
			city.currBuildingPosition.z--;
			break;
		case 'l':
			//-x
			city.currBuildingPosition.x--;
			break;
		case '8':  //Toggles wireframe mode
			//window.wireframe = !window.wireframe;
			//+z
			city.currBuildingPosition.z+=6;
			break;
		case '4':
			//+x
			city.currBuildingPosition.x+=6;
			break;
		case '5':
			//-z
			city.currBuildingPosition.z-=6;
			break;
		case '6':
			//-x
			city.currBuildingPosition.x-=6;
			break;
		case 'u':
			//+y
			city.currBuildingPosition.y+=0.5;
			break;
		case 'n':
			//-y
			city.currBuildingPosition.y-=0.5;
			break;
		case 'h':
			city.currBuilding++;
			city.currBuilding%=city.building->buildings.size();
			break;
		case 'g':
			city.currBuilding--;
			if(city.currBuilding < 0){city.currBuilding=city.building->buildings.size()-1;}
			break;

		case 'c': 
			city.cityBlocksBuildings.pop_back();
			city.cityBlocksBuildingsPositions.pop_back();
			city.cityBlocksBuildingsRotations.pop_back();
			break;

		case 'v': 
			city.cityBlocksBuildings.push_back(city.currBuilding);
			city.cityBlocksBuildingsPositions.push_back(city.currBuildingPosition);
			city.cityBlocksBuildingsRotations.push_back(city.currBuildingRotation);
			break;

		case 'x': 
			city.saveBuildingVertices();
			break;

		case '1': 	
			if(menu.menuOn){menu.Update(1);}
			return;
		case '2':  
			if(menu.menuOn){menu.Update(2);}
			return;
		case '3':
			if(menu.menuOn){menu.Update(3);}
			return;
		/*case '4':
			if(menu.menuOn){menu.Update(4);}
			return;
		case '5':
			if(menu.menuOn){menu.Update(5);}
			return;*/

		case 13: //Enter key
			return;

		case 27: //ESC key
			glutLeaveMainLoop();
			return;
	}	
}

void KeyboardUpFunc(unsigned char c, int x, int y){
	switch (c){
		case 'e':ePressed = false;break;
		case 'r':rPressed = false;break;
		case 'z':zPressed = false;break;
		case 'q':qPressed = false;break;
		case 'w':wPressed = false;break;
		case 's':sPressed = false;break;
		case 'a':aPressed = false;break;
		case 'd':dPressed = false;break;
	}	
}

void SpecialFunc(int c, int x, int y)
{
	switch(c){
        case GLUT_KEY_UP:
			if(!gameOver){rotateX(1);}
			return;
        case GLUT_KEY_DOWN:
			if(!gameOver){rotateX(-1);}
			return;
        case GLUT_KEY_RIGHT:rotateY(-1);return;
        case GLUT_KEY_LEFT:rotateY(1);return;
		case GLUT_KEY_F1:	
			weatherType = (weatherType + 1)%4;
			return;
		case GLUT_KEY_F2:
			tod.x  = (tod.x + 1)%3;
			return;
    }
}

void makeSkybox(){
	modelview = endRender(modelview);
	mat4 skyboxScale = modelview;
	skyboxScale = rotate(skyboxScale, (GLfloat) RotatedX, vec3(1,0,0));
	skyboxScale = rotate(skyboxScale, (GLfloat) RotatedY, vec3(0,1,0));
	skyboxScale = scale(skyboxScale, vec3(3,3,3));
	skybox.Draw(projection, skyboxScale, tod, current_timeDisplay/2);	
	modelview = render(modelview);
}

void drawPrecipitationWithRadar(){
		modelview = endRender(modelview);

		modelview = rotate(modelview, (GLfloat) RotatedX, vec3(1,0,0));
		modelview = rotate(modelview, (GLfloat) RotatedY, vec3(0,1,0));
		
		precip.RotatedY = (float)(RotatedY);
		precip.movingWRTSnow = movingWRTSnow;
		precip.weatherType = weatherType;

		precip.Draw(projection, modelview, tod, 0);	
			
		modelview = rotate(modelview, (GLfloat) -RotatedY, vec3(0,1,0));
		modelview = rotate(modelview, (GLfloat) -RotatedX, vec3(1,0,0));

//		gm1.DrawOrthographic(projection, modelview, tod, (viewPerspective == 1), 0);

		modelview = render(modelview);
}

//Response to a particular key being held down
void keyPress(){
	if(ePressed){
	}	
	if(rPressed){		
	}

	if(wPressed){
		maxUserVelocity = 5.f;

		if(velocity2 < maxUserVelocity){velocity2 += 0.1f;}
		if(movingWRTSnow < 1){movingWRTSnow = movingWRTSnow + 0.2f;}
		transZ = (float)(transZ + velocity2*cos(-RotatedY*3.14/180));
		transX = (float)(transX + velocity2*sin(-RotatedY*3.14/180));			
	}
	else{
		if(velocity2 > 0){velocity2 -= 0.1f;}
		if(velocity2 < 0){velocity2 = 0;}
	}

//	userTeam->soldiers[0].person.velocity = velocity2;

	if(zPressed){transY = transY - 1;}
	if(qPressed){transY = transY + 1;}
	if(sPressed){transZ = (float)(transZ - 1*cos(-RotatedY*3.14/180));transX = (float)(transX - 1*sin(-RotatedY*3.14/180));}
	if(aPressed){transX = (float)(transX + 1*cos(RotatedY*3.14/180));transZ = (float)(transZ + 1*sin(RotatedY*3.14/180));}
	if(dPressed){transX = (float)(transX - 1*cos(RotatedY*3.14/180));transZ = (float)(transZ - 1*sin(RotatedY*3.14/180));}
}

//Set up the environment for game play after selected in the menu
void initArena(){
	city.Initialize();
}

//Orchestrates all the objects and variables into a playable game
void GameDisplay(){
	glEnable(GL_CULL_FACE);
	glClearColor(0.486f, 0.596f, 0.737f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	projection = perspective(25.0f, window.window_aspect, 0.01f, 7000.0f);
	modelview = lookAt(lookAtEye, lookAtCenter, vec3(0.0f, 1.0f, 0.0f));
	modelview = render(modelview);
	glLoadMatrixf(value_ptr(modelview));
	glPolygonMode(GL_FRONT_AND_BACK, window.wireframe ? GL_LINE : GL_FILL);	

	lookAtEye = menu.s.lookAtEye;
	lookAtCenter = menu.s.lookAtCenter;
	viewPerspective = 3;
	if(lookAtEye == menu.FIRST_PERSON_EYE){
		viewPerspective = 1;
	}

	/////////////////////////////Menu Display////////////////////////////////
	if(menu.menuOn){
		//3P - eye = vec3(0.0f, 1, 10);center = vec3(0.0f, 0.0f, 0.0f);
		//1P - eye = vec3(0.0f, 1, -2);center = vec3(0.0f, 1.0f, -3.0f);
		viewPerspective = 3;
		lookAtEye = vec3(0.0f, 2, 10);
		lookAtCenter = vec3(0.0f, 1.0f, -10.0f);		

		glDepthMask(GL_FALSE);
		for(unsigned int i=0; i<menu.titles.size(); i++){
			activeTextDisplay(menu.titles.at(i).c_str(), -0.5f, 0.8f - i*0.25f, 32 - i*4, vec4(1,1,1,1));
		}
		for(unsigned int i=0; i<menu.lines.size(); i++){
			activeTextDisplay(menu.lines.at(i).c_str(), -0.5f, 0.25f-i*0.15f, 20, vec4(1,1,1,1));
		}
		glDepthMask(GL_TRUE);

	}
	///////////////////////Game Display///////////////////////////
	else if(!gameOver){

		if(!stadiumLoaded){
			initArena();
			stadiumLoaded = true;
		}
		
		current_timeDisplay = float(glutGet(GLUT_ELAPSED_TIME)) / 1000.0f;
		current_timeDisplay = (window.paused ? window.time_last_pause_began : current_timeDisplay) - window.total_time_paused;

		keyPress();		
		
		//Mouse movement
		mouseRotations(1, viewPerspective);		

		//makeSkybox();

		modelview = endRender(modelview);

//		*gmTransX = transX;*gmTransY = transY;*gmTransZ = transZ;
//		*gmRotatedX = RotatedX;*gmRotatedY = RotatedY;

//		gm1.DrawUser(projection, modelview, tod, 0);

		modelview = render(modelview);

//		gm1.DrawTeams(projection, modelview, tod, 0);

		city.userPosition = vec3(-transX, transY, -transZ);
		city.userRotation = RotatedY;
		city.Draw(projection, modelview, tod, current_timeDisplay);
		
		glDepthMask(GL_FALSE);
		drawPrecipitationWithRadar();

		//Display the relevant text on the screen
/*		stringstream yS (stringstream::in | stringstream::out);stringstream rS (stringstream::in | stringstream::out);
		stringstream bS (stringstream::in | stringstream::out);stringstream gS (stringstream::in | stringstream::out);
		stringstream ammo (stringstream::in | stringstream::out);stringstream grenades (stringstream::in | stringstream::out);
		stringstream kills (stringstream::in | stringstream::out);
		
		ammo << userTeam->soldiers[0].ammo;yS << userTeam->numRemaining;gS << greenTeam->numRemaining;
		kills << userTeam->soldiers[0].kills;
		bS << blueTeam->numRemaining;rS << redTeam->numRemaining;grenades << userTeam->soldiers[0].grenades;

		activeTextDisplay((yS.str()).c_str(), 0.3f, 0.85f, 32, vec4(1,1,0,1));
		activeTextDisplay((gS.str()).c_str(), 0.45f, 0.85f, 32, vec4(0,1,0,1));
		activeTextDisplay((bS.str()).c_str(), 0.6f, 0.85f, 32, vec4(0,0,1,1));
		activeTextDisplay((rS.str()).c_str(), 0.75f, 0.85f, 32, vec4(1,0,0,1));
		activeTextDisplay((kills.str()).c_str(), -0.94f, -0.85f, 16, vec4(1,1,1,1));
		activeTextDisplay((ammo.str()).c_str(), -0.85f, -0.85f, 16, vec4(1,1,1,1));
		activeTextDisplay((grenades.str()).c_str(), -0.74f, -0.85f, 16, vec4(1,1,1,1));
		*/
		glDepthMask(GL_TRUE);
	}

	//Calculations for moving while it's snowing
	if(movingWRTSnow > 0){movingWRTSnow = movingWRTSnow - 0.1f;}
	if(movingWRTSnow < 0){movingWRTSnow = 0.0;}

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glFlush();
	
}

//Manage pausing and when to display the game / jumbotrons
void DisplayFunc(){
	glViewport(0, 0, window.size.x, window.size.y);
	if(!window.paused){
		GameDisplay();	
		glViewport(0, 0, (GLsizei)(512.0), (GLsizei)(512.0));

		glutSwapBuffers();
	}	
}

void TimerFunc(int value){
	if (window.window_handle != -1){glutTimerFunc(window.interval, TimerFunc, value);glutPostRedisplay();}
}

int main(int argc, char * argv[])
{
	/* Enable blending, necessary for our alpha texture */
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glewInit();
	glutInit(&argc, argv);
	glutInitWindowSize(1024, 512);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);

	srand ((unsigned int)(time(NULL)));

	//Initialize everything
	fontfilename = "Motorwerk.ttf";

	window.window_handle = glutCreateWindow("Base Project");
	glutReshapeFunc(ReshapeFunc);
	glutCloseFunc(CloseFunc);
	
	glutMotionFunc(mouseMovement);
	glutPassiveMotionFunc(mouseMovement); //check for mouse movement
	glutKeyboardFunc(KeyboardFunc);
	glutKeyboardUpFunc(KeyboardUpFunc);
	glutSpecialFunc(SpecialFunc);
	glutTimerFunc(window.interval, TimerFunc, 0);
	
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);

	menu.Initialize();

	if (glewInit() != GLEW_OK)
	{
		cerr << "GLEW failed to initialize." << endl;
		return 0;
	}

	init_resources();
	glutDisplayFunc(DisplayFunc);

	if (!skybox.Initialize(0, 5000, "basic_skybox_shader.vert", "basic_skybox_shader.frag")){return 0;}	
	if (!precip.Initialize()){return 0;}

	//gm1.tSoldier = tSoldier;

	/*if(!gm1.Initialize()){return 0;}

	userTeam = &gm1.userTeam;
	greenTeam = &gm1.greenTeam;
	blueTeam = &gm1.blueTeam;
	redTeam = &gm1.redTeam;

	*&gmTransX = &gm1.transX;
	*&gmTransY = &gm1.transY;
	*&gmTransZ = &gm1.transZ;
	*&gmRotatedX = &gm1.RotatedX;
	*&gmRotatedY = &gm1.RotatedY;
	*&followCpuSoldier = &gm1.followCpuSoldier;
	*&soldierToFollowIndex = &gm1.soldierToFollowIndex;
	*&stadiumSelect = &gm1.stadiumSelect;

	gm1.stadium = new SquareStadium();
	gm1.forest = new Forest();
	gm1.desert = new Desert();
	gm1.volcano = new Volcano();
	gm1.cave = new Cave();*/

	glutMainLoop();
}