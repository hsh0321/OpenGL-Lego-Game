#define PI 3.14
#define WIDTH 1000
#define HEIGHT 800
//ObjParser *lego_1;
//ObjParser *lego_2;
//ObjParser *lego_3;
//ObjParser *lego_4;
//ObjParser *lego_5;
//ObjParser *lego_6;
//ObjParser *lego_7;
//ObjParser *lego_8;
//ObjParser *lego_9;
//ObjParser *lego_0;

ObjParser *lego_head;
ObjParser *lego_body;
ObjParser *lego_left_arm;
ObjParser *lego_right_arm;
ObjParser *lego_left_hand;
ObjParser *lego_right_hand;
ObjParser *lego_bottom;
ObjParser *lego_left_leg;
ObjParser *lego_right_leg;

static ObjParser lego_1("obj/Lego1.obj");
static ObjParser lego_2("obj/Lego2.obj");
static ObjParser lego_3("obj/Lego3.obj");
static ObjParser lego_4("obj/Lego4.obj");
static ObjParser lego_5("obj/Lego5.obj");
static ObjParser lego_6("obj/Lego6.obj");
static ObjParser lego_7("obj/Lego7.obj");
static ObjParser lego_8("obj/Lego8.obj");

//ObjParser lego_head;
//ObjParser lego_body;
//ObjParser lego_left_arm;
//ObjParser lego_right_arm;
//ObjParser lego_left_hand;
//ObjParser lego_right_hand;
//ObjParser lego_bottom;
//ObjParser lego_left_leg;
//ObjParser lego_right_leg;


int index = 1 , color = 0;


GLfloat colors[][4] = {
	{ 1.0, 0.0, 0.0 ,1.0},      // red
	{ 1.0, 1.0, 0.0 ,1.0},      // yellow
	{ 0.0, 1.0, 0.0,1.0 },      // green
	{ 0.0, 0.0, 1.0 ,1.0},      // blue
	{ 1.0, 1.0, 1.0,1.0 },      // white
	{ 1.0, 0.0, 1.0 ,1.0},
	{ 0.0, 0.0, 0.0 ,1.0},		//black
	{ 0.9, 0.9, 0.9 ,1.0} };

GLfloat trans_colors[][4] = {
	{ 1.0, 0.0, 0.0,0.4},      // red
	{ 1.0, 1.0, 0.0,0.4 },      // yellow
	{ 0.0, 1.0, 0.0 ,0.4},      // green
	{ 0.0, 0.0, 1.0 ,0.4},      // blue
	{ 1.0, 1.0, 1.0 ,0.4},      // white
	{ 1.0, 0.0, 1.0 ,0.4},
	{ 0.0, 0.0, 0.0 ,0.4},		//black
	{ 0.9, 0.9, 0.9 ,0.4} };



struct Lego {
	Vec3f locate = { 0,0,0 }; // 초기 위치
	Vec3f length = { 0,0,0 }; // 길이
	Vec3f angle = { 0,0,0 };  // 회전 각도
	Vec3f min = { 0,0,0 };    // 최소값을 갖는 점의 좌표
	Vec3f max;                // 최대값을 갖는 점의 좌표

	int color = 0;            // Color index
	int type = 0;			  // lego type index

};

struct Lego lego[10];  // 레고의 기본 정보
struct Lego slego[2000]; // 저장된 레고들의 정보



double rad2deg(double radian)
{
	return radian * 180 / PI;
}
double deg2rad(double degree)
{
	return degree * PI / 180;
}


////////////카메라/////////////////
int upY = 1;
double phi = 45;
double theta = 45;
int r = 40;
double eyeX = r * sin(deg2rad(theta))*sin(deg2rad(phi));
double eyeY = r * cos(deg2rad(theta));
double eyeZ = r * sin(deg2rad(theta))*cos(deg2rad(phi));
double mX=0, mY=0,mZ = 0;

int upY2 = 1;
double phi2 = 45;
double theta2 = 45;
int r2 = 10;
double eyeX2 = r2 * sin(deg2rad(theta2))*sin(deg2rad(phi2));
double eyeY2 = r2 * cos(deg2rad(theta2));
double eyeZ2 = r2 * sin(deg2rad(theta2))*cos(deg2rad(phi2));
///////////////////////////////////

bool antialiase = true;


int gamemode = 0;

int drag;
double tempX, tempY;


inline void draw_obj(ObjParser *objParser) {
	glBegin(GL_TRIANGLES);
	for (unsigned int n = 0; n < objParser->getFaceSize(); n += 3) {
		glNormal3f(objParser->normal[objParser->normalIdx[n] - 1].x,
			objParser->normal[objParser->normalIdx[n] - 1].y,
			objParser->normal[objParser->normalIdx[n] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n] - 1].x,
			objParser->vertices[objParser->vertexIdx[n] - 1].y,
			objParser->vertices[objParser->vertexIdx[n] - 1].z);
		glNormal3f(objParser->normal[objParser->normalIdx[n + 1] - 1].x,
			objParser->normal[objParser->normalIdx[n + 1] - 1].y,
			objParser->normal[objParser->normalIdx[n + 1] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n + 1] - 1].x,
			objParser->vertices[objParser->vertexIdx[n + 1] - 1].y,
			objParser->vertices[objParser->vertexIdx[n + 1] - 1].z);
		glNormal3f(objParser->normal[objParser->normalIdx[n + 2] - 1].x,
			objParser->normal[objParser->normalIdx[n + 2] - 1].y,
			objParser->normal[objParser->normalIdx[n + 2] - 1].z);
		glVertex3f(objParser->vertices[objParser->vertexIdx[n + 2] - 1].x,
			objParser->vertices[objParser->vertexIdx[n + 2] - 1].y,
			objParser->vertices[objParser->vertexIdx[n + 2] - 1].z);
	}
	glEnd();
}

inline void draw_obj2(ObjParser objParser) {
	glBegin(GL_TRIANGLES);
	for (unsigned int n = 0; n < objParser.getFaceSize(); n += 3) {
		glNormal3f(objParser.normal[objParser.normalIdx[n] - 1].x,
			objParser.normal[objParser.normalIdx[n] - 1].y,
			objParser.normal[objParser.normalIdx[n] - 1].z);
		glVertex3f(objParser.vertices[objParser.vertexIdx[n] - 1].x,
			objParser.vertices[objParser.vertexIdx[n] - 1].y,
			objParser.vertices[objParser.vertexIdx[n] - 1].z);
		glNormal3f(objParser.normal[objParser.normalIdx[n + 1] - 1].x,
			objParser.normal[objParser.normalIdx[n + 1] - 1].y,
			objParser.normal[objParser.normalIdx[n + 1] - 1].z);
		glVertex3f(objParser.vertices[objParser.vertexIdx[n + 1] - 1].x,
			objParser.vertices[objParser.vertexIdx[n + 1] - 1].y,
			objParser.vertices[objParser.vertexIdx[n + 1] - 1].z);
		glNormal3f(objParser.normal[objParser.normalIdx[n + 2] - 1].x,
			objParser.normal[objParser.normalIdx[n + 2] - 1].y,
			objParser.normal[objParser.normalIdx[n + 2] - 1].z);
		glVertex3f(objParser.vertices[objParser.vertexIdx[n + 2] - 1].x,
			objParser.vertices[objParser.vertexIdx[n + 2] - 1].y,
			objParser.vertices[objParser.vertexIdx[n + 2] - 1].z);
	}
	glEnd();
}

void draw_string(void* font, const char* str, float x_position, int y_position) {
	glPushAttrib(GL_LIGHTING_BIT);
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();

	glLoadIdentity();
	gluOrtho2D(-5, 5, -5, 5);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	unsigned int i;
	glRasterPos3f(x_position, y_position, 0);
	for (i = 0; i < strlen(str); i++) {
		glutBitmapCharacter(font, str[i]);
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopAttrib();
}




#pragma once
