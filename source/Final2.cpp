#include <GL/glut.h>
#include <stdio.h>
#include <gl/freeglut.h> // 마우스 휠
#include <math.h>
#include <iostream>
#include <algorithm>
#include <string.h>
#include <GL/glext.h>

#include "ObjParser.h"
#include "init.h"
#include "define.h"
#include "idle.h"
#include "bmpfuncs.h"

#define WIDTH 1000
#define HEIGHT 800

using namespace std;

int w = 1000, h = 800;

extern bool bjump;
extern bool ud;
extern bool rotate_camera;
extern bool run ;
extern bool cUp , cDown;
extern bool cam2mode;
extern bool lava;

extern int jy;
extern int j;
extern int cc;
extern int cam ;
extern float chareyeY;
extern double lavaHeight;
extern double lavaX;
extern double lavaY;
extern int lavastate;

int num_lego;
int undo_num = 0;
int undo_num2 = 0;
int scolor = 0;
int character_color[6] = { 0, };
int char_part = 0;
GLdouble tmp[100][16];


void obj_read();
void environmentTextureMapping(); // skybox setting
void tileTextureMapping(); // 바닥

void resize(int,int); // init

bool crashLegochar();
bool crashLego();

void idle(int); 
void camera_idle();
void camera_idle2();
void jump_idle(); // 점프 
void gravity_idle(); // 중력
void walk_idle(); // 걷기
void back_walk_idle(); // 뒤로걷기
void leg_idle();
void lavaUp();

void obj_read(); // obj read
void check_min_max(); // min,max 계산
void draw_lego(int, int);	
void draw_axis();
void draw_char();
void draw_texturetile();
void draw_skybox(); // 배경
void draw_string(void*, const char*, float, int);

void preview_lego();
void draw();

void pkeyboard(unsigned char, int, int);
void rkeyboard(unsigned char, int, int);
void specialpkeyboard(int, int, int);
void specialrkeyboard(int, int, int);
void mouse(int, int, int, int);
void motion(int, int);
void passive(int, int);

void sub_menu_function(int);
void sub_menu_function2(int);
void sub_menu_function3(int);
void main_menu_function(int);

GLuint g_nCubeTex;
GLuint tile;

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(1000, 800);
	glutInitWindowPosition(600, 100);
	glutCreateWindow("DRAW");

	glutReshapeFunc(resize);
	init_light();

	//crashLegochar();

	glutSpecialFunc(specialpkeyboard);
	glutSpecialUpFunc(specialrkeyboard);

	glutKeyboardFunc(pkeyboard); // press
	glutKeyboardUpFunc(rkeyboard); // release

	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutPassiveMotionFunc(passive);

	glutDisplayFunc(draw);
	//glutIdleFunc(idle);
	glutTimerFunc(10,idle,1);
	int submenu1;
	submenu1 = glutCreateMenu(sub_menu_function);

	glutAddMenuEntry("Create", 1);
	glutAddMenuEntry("Game", 2);
	glutAddMenuEntry("Customizing", 3);

	int submenu2;
	submenu2 = glutCreateMenu(sub_menu_function2);

	glutAddMenuEntry("Save 1", 1);
	glutAddMenuEntry("Save 2", 2);
	glutAddMenuEntry("Save 3", 3);

	int submenu3;
	submenu3 = glutCreateMenu(sub_menu_function3);

	glutAddMenuEntry("Load 1", 1);
	glutAddMenuEntry("Load 2", 2);
	glutAddMenuEntry("Load 3", 3);

	glutCreateMenu(main_menu_function);
	glutAddSubMenu("Game mode", submenu1);
	glutAddSubMenu("Save", submenu2);
	glutAddSubMenu("Load", submenu3);

	glutAddMenuEntry("Clear", 1);
	glutAddMenuEntry("lava start", 2);
	glutAddMenuEntry("lava stop", 3);
	

	glutAddMenuEntry("Quit", 999);
	glutAttachMenu(GLUT_RIGHT_BUTTON);


	glutMainLoop();

	return 0;
}


void environmentTextureMapping() {
	glGenTextures(1, &g_nCubeTex);
	int width, height, channels;
	
	
	//uchar* img0 = readImageData("img/512px.bmp", &width, &height, &channels);
	//uchar* img1 = readImageData("img/512nx.bmp", &width, &height, &channels);
	//uchar* img2 = readImageData("img/512py.bmp", &width, &height, &channels);
	//uchar* img3 = readImageData("img/512ny.bmp", &width, &height, &channels);
	//uchar* img4 = readImageData("img/512pz.bmp", &width, &height, &channels);
	//uchar* img5 = readImageData("img/512nz.bmp", &width, &height, &channels);


	/*uchar* img0 = readImageData("img/clouds1_east.bmp", &width, &height, &channels);
	uchar* img1 = readImageData("img/clouds1_west.bmp", &width, &height, &channels);
	uchar* img2 = readImageData("img/clouds1_up.bmp", &width, &height, &channels);
	uchar* img3 = readImageData("img/clouds1_down.bmp", &width, &height, &channels);
	uchar* img4 = readImageData("img/clouds1_south.bmp", &width, &height, &channels);
	uchar* img5 = readImageData("img/clouds1_north.bmp", &width, &height, &channels);*/

	uchar* img0 = readImageData("img/lava/right.bmp", &width, &height, &channels);
	uchar* img1 = readImageData("img/lava/left.bmp", &width, &height, &channels);
	uchar* img2 = readImageData("img/lava/top.bmp", &width, &height, &channels);
	uchar* img3 = readImageData("img/lava/bottom.bmp", &width, &height, &channels);
	uchar* img4 = readImageData("img/lava/front.bmp", &width, &height, &channels);
	uchar* img5 = readImageData("img/lava/back.bmp", &width, &height, &channels);


	glBindTexture(GL_TEXTURE_CUBE_MAP, g_nCubeTex);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img0);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img1);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img2);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img3);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img4);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img5);


	glBindTexture(GL_TEXTURE_CUBE_MAP, g_nCubeTex);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
	glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);

	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	glEnable(GL_TEXTURE_GEN_R);
	glEnable(GL_TEXTURE_CUBE_MAP);
}

void tileTextureMapping() {
	glGenTextures(1, &tile);
	int imgwidth, imgheight, channels;
	glBindTexture(GL_TEXTURE_2D, tile);
	uchar *img = readImageData("img/lava.bmp", &imgwidth, &imgheight, &channels);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imgwidth, imgheight, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void draw_texturetile() {
	glEnable(GL_TEXTURE_2D);
	glColor3f(1.0, 1.0, 1.0);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); // gl_modulate , gl_decal, gl_replace

	glBindTexture(GL_TEXTURE_2D, tile);
	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0, 0); glVertex3f(-250.0f, 0.0f, 250.0f);
	glTexCoord2f(10, 0); glVertex3f(250.0f,0.0f, 250.0f);
	glTexCoord2f(10, 10); glVertex3f(250.0f, 0.0f, -250.0f);
	glTexCoord2f(0, 10); glVertex3f(-250.0f, 0.0f, -250.0f);
	glEnd();
}

void draw_skybox(void) {
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_CUBE_MAP);
	glBindTexture(GL_TEXTURE_CUBE_MAP, g_nCubeTex);
	float g_nskysize = 250.0f;

	glBegin(GL_QUADS);

	glTexCoord3d(1.0, -1.0, -1.0); glVertex3f(g_nskysize, -g_nskysize, -g_nskysize);
	glTexCoord3d(1.0, -1.0, 1.0); glVertex3f(g_nskysize, -g_nskysize, g_nskysize);
	glTexCoord3d(1.0, 1.0, 1.0); glVertex3f(g_nskysize, g_nskysize, g_nskysize);
	glTexCoord3d(1.0, 1.0, -1.0); glVertex3f(g_nskysize, g_nskysize, -g_nskysize);

	glTexCoord3d(-1.0, -1.0, -1.0); glVertex3f(-g_nskysize, -g_nskysize, -g_nskysize);
	glTexCoord3d(-1.0, -1.0, 1.0); glVertex3f(-g_nskysize, -g_nskysize, g_nskysize);
	glTexCoord3d(-1.0, 1.0, 1.0); glVertex3f(-g_nskysize, g_nskysize, g_nskysize);
	glTexCoord3d(-1.0, 1.0, -1.0); glVertex3f(-g_nskysize, g_nskysize, -g_nskysize);

	glTexCoord3d(1.0, 1.0, 1.0); glVertex3f(g_nskysize, g_nskysize, g_nskysize);
	glTexCoord3d(-1.0, 1.0, 1.0); glVertex3f(-g_nskysize, g_nskysize, g_nskysize);
	glTexCoord3d(-1.0, 1.0, -1.0); glVertex3f(-g_nskysize, g_nskysize, -g_nskysize);
	glTexCoord3d(1.0, 1.0, -1.0); glVertex3f(g_nskysize, g_nskysize, -g_nskysize);

	glTexCoord3d(1.0, -1.0, 1.0); glVertex3f(g_nskysize, -g_nskysize, g_nskysize);
	glTexCoord3d(-1.0, -1.0, 1.0); glVertex3f(-g_nskysize, -g_nskysize, g_nskysize);
	glTexCoord3d(-1.0, -1.0, -1.0); glVertex3f(-g_nskysize, -g_nskysize, -g_nskysize);
	glTexCoord3d(1.0, -1.0, -1.0); glVertex3f(g_nskysize, -g_nskysize, -g_nskysize);

	glTexCoord3d(1.0, -1.0, 1.0); glVertex3f(g_nskysize, -g_nskysize, g_nskysize);
	glTexCoord3d(-1.0, -1.0, 1.0); glVertex3f(-g_nskysize, -g_nskysize, g_nskysize);
	glTexCoord3d(-1.0, 1.0, 1.0); glVertex3f(-g_nskysize, g_nskysize, g_nskysize);
	glTexCoord3d(1.0, 1.0, 1.0); glVertex3f(g_nskysize, g_nskysize, g_nskysize);

	glTexCoord3d(1.0, -1.0, -1.0); glVertex3f(g_nskysize, -g_nskysize, -g_nskysize);
	glTexCoord3d(-1.0, -1.0, -1.0); glVertex3f(-g_nskysize, -g_nskysize, -g_nskysize);
	glTexCoord3d(-1.0, 1.0, -1.0); glVertex3f(-g_nskysize, g_nskysize, -g_nskysize);
	glTexCoord3d(1.0, 1.0, -1.0); glVertex3f(g_nskysize, g_nskysize, -g_nskysize);

	glEnd();
}

void resize(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (float)width / (float)height, 1, 2500);
	w = width;
	h = height;
	
	glMatrixMode(GL_MODELVIEW);
	glClearDepth(1.0f);
	antialiase_mode();
	//glFrontFace(GL_CW);
	glEnable(GL_DEPTH_TEST);
	
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glEnable(GL_TEXTURE_2D);
	environmentTextureMapping();
	tileTextureMapping();

	obj_read();
}

bool crashLegochar() {
	for (int i = 0; i < num_lego; i++) {
		double xmax = max(lego_char.locate.x, slego[i].min.x + 1);
		double xmin = min((lego_char.locate.x + lego_char.length.x), (slego[i].max.x + 1));

		double ymax = max(lego_char.locate.y, slego[i].min.y);
		double ymin = min((lego_char.locate.y + lego_char.length.y), (slego[i].max.y));

		double zmax = max(lego_char.locate.z, slego[i].min.z + 0.8f);
		double zmin = min((lego_char.locate.z + lego_char.length.z), (slego[i].max.z + 0.8f));

		if (xmax < xmin && ymax < ymin && zmax < zmin) {
			return true;
		}
	}

	return false;

	glutPostRedisplay();
}



inline void idle(int value) {
	gravity_idle();
	walk_idle();
	back_walk_idle();
	camera_idle();
	camera_idle2();
	jump_idle();
	leg_idle();
	left_rotate();
	right_rotate();
	lavaUp();

	glutTimerFunc(10, idle, 1); // 10msec 

	glutPostRedisplay();
}

void obj_read() {
	//lego_1 = new ObjParser("obj/Lego1.obj");
	//lego_2 = new ObjParser("obj/Lego2.obj");
	//lego_3 = new ObjParser("obj/Lego3.obj");
	//lego_4 = new ObjParser("obj/Lego4.obj");
	//lego_5 = new ObjParser("obj/Lego5.obj");
	//lego_6 = new ObjParser("obj/Lego6.obj");
	//lego_7 = new ObjParser("obj/Lego7.obj");
	//lego_8 = new ObjParser("obj/Lego8.obj");

	lego_head = new ObjParser("obj/character/head.obj");
	lego_body = new ObjParser("obj/character/body.obj");
	lego_bottom = new ObjParser("obj/character/bottom.obj");
	lego_left_arm = new ObjParser("obj/character/left_arm.obj");
	lego_left_leg = new ObjParser("obj/character/left_leg.obj");
	lego_left_hand = new ObjParser("obj/character/left_hand.obj");
	lego_right_arm = new ObjParser("obj/character/right_arm.obj");
	lego_right_leg = new ObjParser("obj/character/right_leg.obj");
	lego_right_hand = new ObjParser("obj/character/right_hand.obj");

	lego[1].length = { 2,2,2 };
	lego[2].length = { 2,2,4 };
	lego[3].length = { 2,2,4 };
	lego[4].length = { 4,1,4 };
	lego[5].length = { 4,1,4 };
	lego[6].length = { 2,1,8 };
	lego[7].length = { 2,1,4 };
	lego[8].length = { 2,2,2 };

	lego_char.length = { 1,4,2 };
}

void check_min_max() {
	//printf("%d\n", (int)lego[index].angle.y);
	lego[index].max.y = lego[index].locate.y + lego[index].length.y;
	lego[index].min.y = lego[index].locate.y;

	switch ((int)lego[index].angle.y) {

	case 0:
		lego[index].min = lego[index].locate;
		lego[index].max = lego[index].min + lego[index].length;
		break;
	case 90:
		lego[index].min = lego[index].locate;
		lego[index].max.x = lego[index].min.x + lego[index].length.z;
		lego[index].max.z = lego[index].min.z + lego[index].length.x;
		break;
	case 180:
		lego[index].min.x = lego[index].locate.x;
		lego[index].min.z = lego[index].locate.z - lego[index].length.z + 2;
		lego[index].max.x = lego[index].locate.x + 2;
		lego[index].max.z = lego[index].locate.z + 2;
		break;
	case 270:
		lego[index].min.x = lego[index].locate.x - lego[index].length.z + 2;
		lego[index].min.z = lego[index].locate.z;
		lego[index].max.x = lego[index].locate.x + 2;
		lego[index].max.z = lego[index].locate.z + 2;
		break;
		
	}
}

void draw_lego(int index, int c) {
	glColor4fv(trans_colors[c]);
	//glColor3fv(colors[c]);
	switch (index) {
	case 1:
		draw_obj2(lego_1);
		break;
	case 2:
		draw_obj2(lego_2);
		break;
	case 3:
		glPushMatrix();
		glRotatef(-90, 0, 1, 0);
		draw_obj2(lego_3);
		glPopMatrix();
		break;
	case 4:

		draw_obj2(lego_4);

		break;
	case 5:
		draw_obj2(lego_5);
		break;
	case 6:
		draw_obj2(lego_6);
		break;
	case 7:
		draw_obj2(lego_7);
		break;
	case 8:
		draw_obj2(lego_8);
		break;
	}
}

void draw_lego2(int index, int c) {
	glColor4fv(colors[c]);
	//glColor3fv(colors[c]);
	switch (index) {
	case 1:
		draw_obj2(lego_1);
		break;
	case 2:
		draw_obj2(lego_2);
		break;
	case 3:
		glPushMatrix();
		glRotatef(-90, 0, 1, 0);
		draw_obj2(lego_3);
		glPopMatrix();
		break;
	case 4:

		draw_obj2(lego_4);

		break;
	case 5:
		draw_obj2(lego_5);
		break;
	case 6:
		draw_obj2(lego_6);
		break;
	case 7:
		draw_obj2(lego_7);
		break;
	case 8:
		draw_obj2(lego_8);
		break;
	}
}

void draw_axis(void) {
	glLineWidth(3);
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(15, 0, 0);

	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 15, 0);

	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 15);
	glEnd();
	glLineWidth(1);

	glColor3f(0.0f, 0.0f, 1.0f);
}

void draw_char(void) {
	glColor3fv(colors[character_color[0]]);
	draw_obj(lego_head);
	glColor3fv(colors[character_color[1]]);
	draw_obj(lego_body);
	glColor3fv(colors[character_color[2]]);
	draw_obj(lego_bottom);

	glPushMatrix();
	glTranslated(0, 3.4, 0);
	glRotated(spin, 1, 0, 0);
	glTranslated(0, -3.4, 0);
	glColor3fv(colors[character_color[3]]);
	draw_obj(lego_right_arm);
	glColor3fv(colors[character_color[5]]);
	draw_obj(lego_right_hand);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 3.4, 0);
	glRotated(-spin, 1, 0, 0);
	glTranslated(0, -3.4, 0);
	glColor3fv(colors[character_color[3]]);
	draw_obj(lego_left_arm);
	glColor3fv(colors[character_color[5]]);
	draw_obj(lego_left_hand);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 1.6, 0);
	glRotated(spin, 1, 0, 0);
	glTranslated(0, -1.6, 0);
	glColor3fv(colors[character_color[4]]);
	draw_obj(lego_left_leg);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 1.6, 0);
	glRotated(-spin, 1, 0, 0);
	glTranslated(0, -1.6, 0);
	glColor3fv(colors[character_color[4]]);
	draw_obj(lego_right_leg);
	glPopMatrix();
}

void preview_lego() {
	glViewport(w*3/4, h*3/4, w / 4, h / 4);

	glLoadIdentity();
	gluLookAt(6, 8, 10, 0, 0, 0, 0, 1, 0);

	glDisable(GL_BLEND);

	//draw_axis();
	draw_lego(index, color);
	glEnable(GL_BLEND);

	glFlush();
}

void draw_text(void) {
	glViewport(w * 3 / 4, h * 3 / 4, w / 4, h / 4);
	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 0);
	draw_string(GLUT_BITMAP_TIMES_ROMAN_24, "PREVIEW", -2, -3);
	glFlush();
}


void draw(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	
	glLoadIdentity();
	glViewport(0, 0, w, h);
	GLfloat light_position[] = { -200.0,200.0,-200.0,1.0 };

	if (gamemode == 0)gluLookAt(eyeX + mX, eyeY, eyeZ + mZ, mX, 0, mZ, 0, upY, 0);
	else if (gamemode == 1) {
		if (cam == 1) {
			gluLookAt(lego_char.locate.x - 20 * sin(deg2rad(lego_char.angle.y)), lego_char.locate.y + 15, lego_char.locate.z - 20 * cos(deg2rad(lego_char.angle.y))
				, lego_char.locate.x + 10 * sin(deg2rad(lego_char.angle.y)), lego_char.locate.y + 6
				, lego_char.locate.z + 10 * cos(deg2rad(lego_char.angle.y)), 0, 1, 0);
			cam2mode = false;
		}
		else if (cam == 2) {
			gluLookAt(lego_char.locate.x, lego_char.locate.y + 4, lego_char.locate.z
				, lego_char.locate.x + 20 * sin(deg2rad(lego_char.angle.y)), lego_char.locate.y + chareyeY
				, lego_char.locate.z + 20 * cos(deg2rad(lego_char.angle.y)), 0, 1, 0);
			cam2mode = true;
		}
	}
	else if (gamemode == 2) {
		gluLookAt(eyeX2, eyeY2, eyeZ2 , 0, 3, 0, 0, upY2, 0);
	}
	// 캐릭터 카메라시점
	//glDisable(GL_BLEND);

	draw_skybox();
	
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);
	glDisable(GL_TEXTURE_GEN_R);
	glDisable(GL_TEXTURE_CUBE_MAP);
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glPushMatrix();
	glTranslated(lavaX, lavaHeight, lavaY); // LAVA 상승

	draw_texturetile();  // LAVA
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);

	if (gamemode == 0 || gamemode == 1) {
		draw_axis();
		for (int i = 0; i < num_lego; i++) {
			glPushMatrix();
			glTranslatef(1, slego[i].length.y / 2, 1); // 원점 잡기
			glTranslatef(slego[i].locate.x, slego[i].locate.y, slego[i].locate.z);
			glRotatef(slego[i].angle.x, 1, 0, 0);
			glRotatef(slego[i].angle.y, 0, 1, 0);
			glRotatef(slego[i].angle.z, 0, 0, 1);
			//glLoadMatrixd(tmp[i]);
			draw_lego2(slego[i].type, slego[i].color);
			glPopMatrix();
		}
		if (gamemode == 0) {
			glPushMatrix();
			glTranslatef(1, lego[index].length.y / 2, 1);
			glTranslatef(lego[index].locate.x, lego[index].locate.y, lego[index].locate.z);
			glRotatef(lego[index].angle.x, 1, 0, 0);
			glRotatef(lego[index].angle.y, 0, 1, 0);
			glRotatef(lego[index].angle.z, 0, 0, 1);
			//glGetDoublev(GL_MODELVIEW_MATRIX, tmp[0]);
			glEnable(GL_BLEND);
			draw_lego(index, color);
			glPopMatrix();

		}
		//glDisable(GL_BLEND);
		

		if (gamemode == 1) {
			glColor3f(1.0f, 1.0f, 1.0f);
			glPushMatrix();
			glTranslated(lego_char.locate.x, lego_char.locate.y, lego_char.locate.z);
			glRotated(lego_char.angle.y, 0, 1, 0);
			draw_char();
			glPopMatrix();
		}
		if (gamemode == 0) {
			preview_lego();
			draw_text();
		}
	}else if (gamemode == 2) {
		if (cc >= 0) {
			glColor3fv(colors[character_color[0]]);
			draw_obj(lego_head);
		}
		if (cc >= 1) {
			glColor3fv(colors[character_color[1]]);
			draw_obj(lego_body);
		}
		if (cc >= 2) {
			glColor3fv(colors[character_color[2]]);
			draw_obj(lego_bottom);
		}
		if (cc >= 3) {
			glColor3fv(colors[character_color[3]]);
			draw_obj(lego_left_arm);
			draw_obj(lego_right_arm);
		}
		if (cc >= 4) {
			glColor3fv(colors[character_color[4]]);
			draw_obj(lego_left_leg);
			draw_obj(lego_right_leg);
		}
		if (cc >= 5) {
			glColor3fv(colors[character_color[5]]);
			draw_obj(lego_left_hand);
			draw_obj(lego_right_hand);
		}

	}


	glFlush();
	glutSwapBuffers();
}

bool crashLego() {
	for (int i = 0; i < num_lego; i++) {
		double xmax = max(lego[index].min.x, slego[i].min.x);
		double xmin = min((lego[index].max.x), (slego[i].max.x));

		double ymax = max(lego[index].min.y, slego[i].min.y);
		double ymin = min((lego[index].max.y), (slego[i].max.y));

		double zmax = max(lego[index].min.z, slego[i].min.z);
		double zmin = min((lego[index].max.z), (slego[i].max.z));

		if (xmax < xmin && ymax < ymin && zmax < zmin) {
			return true;
		}
	}
	return false;
}

void pkeyboard(unsigned char key, int x, int y) {
	if (gamemode == 0) {

		//printf("$$%f$$", lego[index].max.x);
		//printf("%f %f %f\n", lego[index].max.x, lego[index].max.y, lego[index].max.z);
		if (key == 'w') {
			lego[index].locate.x -= 2;
			check_min_max();
			if (crashLego() == true)lego[index].locate.x += 2;
		}
		else if (key == 's') {
			lego[index].locate.x += 2;
			check_min_max();
			if (crashLego() == true)lego[index].locate.x -= 2;
		}
		else if (key == 'a') {
			lego[index].locate.z += 2;
			check_min_max();
			if (crashLego() == true)lego[index].locate.z -= 2;
		}
		else if (key == 'd') {
			lego[index].locate.z -= 2;
			check_min_max();
			if (crashLego() == true)lego[index].locate.z += 2;
		}
		else if (key == 'q') {
			lego[index].locate.y += 1;
			check_min_max();
			if (crashLego() == true)lego[index].locate.y -= 1;
		}
		else if (key == 'e') {
			if (lego[index].locate.y > 0) {
				lego[index].locate.y -= 1;
				check_min_max();
				if (crashLego() == true)lego[index].locate.y += 1;
			}
		}
		else if (key == 'r') {
			lego[index].angle.y = lego[index].angle.y + 90;
			if (lego[index].angle.y == 360)lego[index].angle.y = 0;
			check_min_max();
		}

		else if (key == 'c') {
			color++;
			if (color == 8) {
				color = 0;
			}
		}
		else if (key == 'z') {
			undo_num++;
			num_lego--;
		}
		else if (key == 'x') {
			if (undo_num > 0) {
				num_lego++;
				undo_num--;
			}
		}
		if (key == 'o') {
			if (crashLego() == false) {
				slego[num_lego] = lego[index];
				slego[num_lego].type = index;
				slego[num_lego].color = color;
				slego[num_lego].angle = lego[index].angle;
				slego[num_lego].min = lego[index].min;
				slego[num_lego].max = lego[index].max;

				num_lego++;

				lego[index].locate = { 0,0,0 };
				lego[index].angle = { 0,0,0 };
				lego[index].min = { 0,0,0 };
				j++;
			}
		}

		if (key == '1') {
			index = 1;
			lego[index].locate = { 0,0,0 };
			lego[index].angle = { 0,0,0 };
			lego[index].min = { 0,0,0 };
		}
		else if (key == '2') {
			index = 2;
			lego[index].locate = { 0,0,0 };
			lego[index].angle = { 0,0,0 };
			lego[index].min = { 0,0,0 };
		}
		else if (key == '3') {
			index = 3;
			lego[index].locate = { 0,0,0 };
			lego[index].angle = { 0,0,0 };
			lego[index].min = { 0,0,0 };
		}
		else if (key == '4') {
			index = 4;
			lego[index].locate = { 0,0,0 };
			lego[index].angle = { 0,0,0 };
			lego[index].min = { 0,0,0 };
		}
		else if (key == '5') {
			index = 5;
			lego[index].locate = { 0,0,0 };
			lego[index].angle = { 0,0,0 };
			lego[index].min = { 0,0,0 };
		}
		else if (key == '6') {
			index = 6;
			lego[index].locate = { 0,0,0 };
			lego[index].angle = { 0,0,0 };
			lego[index].min = { 0,0,0 };
		}
		else if (key == '7') {
			index = 7;
			lego[index].locate = { 0,0,0 };
			lego[index].angle = { 0,0,0 };
			lego[index].min = { 0,0,0 };
		}
		else if (key == '8') {
			index = 8;
			lego[index].locate = { 0,0,0 };
			lego[index].angle = { 0,0,0 };
			lego[index].min = { 0,0,0 };
		}
		else if (key == '9') {
			index = 9;
			lego[index].locate = { 0,0,0 };
			lego[index].angle = { 0,0,0 };
			lego[index].min = { 0,0,0 };
		}
	}
	else if (gamemode == 1) {
		if (key == 'w' || key == 'W') {
			leg_rotate = true;
			walk = true;
		}
		else if (key == 's' || key == 'S') {
			leg_rotate = true;
			bwalk = true;
		}
		else if (key == 'a' || key == 'A') {
			if (bwalk == true) {
				rrotate = true;
			}
			else {
				lrotate = true;
			}
		}
		else if (key == 'd' || key == 'D') {
			if (bwalk == true) {
				lrotate = true;
			}
			else {
				rrotate = true;
			}
		}
		else if (key == '1') {
			cam = 1;
		}
		else if (key == '2') {
			cam = 2;
		}

		if (key == 32) {  // spacebar
			//if (crashLegochar() == true || lego_char.locate.y < 0.001) {
			leg_rotate = true;
			bjump = true;

			//}
		}
	}
	else if (gamemode == 2) {
		if (key == 'c') {
			
			color++;
			if (color == 8) {
				color = 0;
			}
			character_color[cc] = color;
		}else if (key == 13) {
			character_color[cc] = color;
			cc++;
		}
		else if (key == 'z') {
			if (cc > 0) {
				undo_num2++;
				cc--;
			}
		}
		else if (key == 'x') {
			if (undo_num2 > 0) {
				cc++;
			}
		}
	}
	glutPostRedisplay();
}

void rkeyboard(unsigned char key, int x, int y) {
	if (gamemode == 1) {
		if (key == 'w' || key == 'W') {
			walk = false;
			leg_rotate = false;
		}
		else if (key == 's' || key == 'S') {
			bwalk = false;
			leg_rotate = false;
		}
		else if (key == 'a' || key == 'A') {
			lrotate = false;
			rrotate = false;
		}
		else if (key == 'd' || key == 'D') {
			rrotate = false;
			lrotate = false;
		}
		if (key == 32) {
			if (walk == true || bwalk == true)leg_rotate = true;
			else leg_rotate = false;
		}
	}
}

void specialpkeyboard(int key, int x, int y) {
	if (key == GLUT_KEY_LEFT) {
		mZ += 1;
	}
	else if (key == GLUT_KEY_RIGHT) {
		mZ -= 1;
	}
	else if (key == GLUT_KEY_UP) {
		mX -= 1;
	}
	else if (key == GLUT_KEY_DOWN) {
		mX += 1;
	}
	else if (key == GLUT_KEY_SHIFT_L) {
		wspeed *= 2;
		run = true;
	}

	eyeX = r * sin(deg2rad(theta))*sin(deg2rad(phi));
	eyeY = r * cos(deg2rad(theta));
	eyeZ = r * sin(deg2rad(theta))*cos(deg2rad(phi));
	//printf("Φ : %f , Θ : %f  (%f, %f, %f) \n", phi, theta, eyeX, eyeY, eyeZ);
	glutPostRedisplay();
}

void specialrkeyboard(int key, int x, int y) {

	if (key == GLUT_KEY_SHIFT_L) {
		wspeed /= 2;
		run = false;
	}

	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
	if (state == 0) {
		if (button == 0) { // 좌클릭 press
			rotate_camera = false;
			drag = 1;
			tempX = x;
			tempY = y;
		}
		else if (button == 3) {
			if (r > 3)r--;
		}
		else if (button == 4) {
			r++;
		}
	}
	else { // release
		if (button == 0) {
			rotate_camera = true;

			drag = 0;
		}
	}

	eyeX = r * sin(deg2rad(theta))*sin(deg2rad(phi));
	eyeY = r * cos(deg2rad(theta));
	eyeZ = r * sin(deg2rad(theta))*cos(deg2rad(phi));

	glutPostRedisplay();
}

void motion(int x, int y) {

	if (drag == 1) { // 좌클릭 Press 상태
		if (gamemode == 0) {
			if (x > tempX) {
				phi = phi + 1;
				if (phi >= 355) {
					phi = 0;
				}
			}
			else if (x < tempX) {
				phi = phi - 1;
				if (phi <= 0) {
					phi = 360;
				}
			}
			if (y > tempY) {
				if (theta < 88)theta = theta + 1;
				if (fmod(theta, 180) == 0.5) { //  지형 밑으로 시점 못내려감.
					upY = -1;
				}
				if (theta >= 360) {
					theta = 5;
					upY = 1;
				}
			}
			else if (y < tempY) {
				if (theta > 1)theta = theta - 1;
				if (fmod(theta, 180) == 0) {
					upY = 1;
				}
				if (theta <= 0) {
					theta = 360;
					upY = -1;
				}
			}
			tempX = x;
			tempY = y;
		}
		else if (gamemode == 2) {
			if (x > tempX) {
				phi2 = phi2 + 1;
				if (phi2 >= 355) {
					phi2 = 0;
				}
			}
			else if (x < tempX) {
				phi2 = phi2 - 1;
				if (phi2 <= 0) {
					phi2 = 360;
				}
			}
			if (y > tempY) {
				if (theta2 < 88)theta2 = theta2 + 1;
				if (fmod(theta2, 180) == 0.5) { //  지형 밑으로 시점 못내려감.
					upY2 = -1;
				}
				if (theta2 >= 360) {
					theta2 = 5;
					upY2 = 1;
				}
			}
			else if (y < tempY) {
				if (theta2 > 1)theta2 = theta2 - 1;
				if (fmod(theta2, 180) == 0) {
					upY2 = 1;
				}
				if (theta2 <= 0) {
					theta2 = 360;
					upY2 = -1;
				}
			}
			tempX = x;
			tempY = y;
		}
	}


	eyeX = r * sin(deg2rad(theta))*sin(deg2rad(phi));
	eyeY = r * cos(deg2rad(theta));
	eyeZ = r * sin(deg2rad(theta))*cos(deg2rad(phi));

	eyeX2 = r2 * sin(deg2rad(theta2))*sin(deg2rad(phi2));
	eyeY2 = r2 * cos(deg2rad(theta2));
	eyeZ2 = r2 * sin(deg2rad(theta2))*cos(deg2rad(phi2));
	glutPostRedisplay();
}

void passive(int x, int y) {
	if (gamemode == 1) {
		if (y < 300) { cDown = true; cUp = false; }
		else if (y > 500) { cUp = true; cDown = false; }
		else { cUp = false; cDown = false; }
	}
	
	glutPostRedisplay();
}

void sub_menu_function(int option) { // draw 서브메뉴
	lavaHeight = 0;
	if (option == 1) {
		printf("Create Lego\n");
		gamemode = 0;
	}
	else if (option == 2) {
		printf("Game \n");
		gamemode = 1;
		lego_char.locate.y = 20;

	}
	else if (option == 3) {
		printf("Customizing\n");
		gamemode = 2;
	}
	
	glutPostRedisplay();
}

void sub_menu_function2(int option) { // draw 서브메뉴
	lavaHeight = 0;
	if (option == 1) {
		FILE* f = fopen("save1.txt", "w+");
		fprintf(f, "%d\n", num_lego);
		for (int i = 0; i < num_lego; i++) {
			fprintf(f, "%f %f %f ", slego[i].length.x, slego[i].length.y, slego[i].length.z);
			fprintf(f, "%f %f %f ", slego[i].locate.x, slego[i].locate.y, slego[i].locate.z);
			fprintf(f, "%f %f %f ", slego[i].angle.x, slego[i].angle.y, slego[i].angle.z);
			fprintf(f, "%f %f %f ", slego[i].min.x, slego[i].min.y, slego[i].min.z);
			fprintf(f, "%f %f %f ", slego[i].max.x, slego[i].max.y, slego[i].max.z);
			fprintf(f, "%d %d\n", slego[i].type, slego[i].color);
		}
		fclose(f);
	}
	else if (option == 2) {
		FILE* f = fopen("save2.txt", "w+");
		fprintf(f, "%d\n", num_lego);
		for (int i = 0; i < num_lego; i++) {
			fprintf(f, "%f %f %f ", slego[i].length.x, slego[i].length.y, slego[i].length.z);
			fprintf(f, "%f %f %f ", slego[i].locate.x, slego[i].locate.y, slego[i].locate.z);
			fprintf(f, "%f %f %f ", slego[i].angle.x, slego[i].angle.y, slego[i].angle.z);
			fprintf(f, "%f %f %f ", slego[i].min.x, slego[i].min.y, slego[i].min.z);
			fprintf(f, "%f %f %f ", slego[i].max.x, slego[i].max.y, slego[i].max.z);
			fprintf(f, "%d %d\n", slego[i].type, slego[i].color);
		}
		fclose(f);
	}
	else if (option == 3) {
		FILE* f = fopen("save3.txt", "w+");
		fprintf(f, "%d\n", num_lego);
		for (int i = 0; i < num_lego; i++) {
			fprintf(f, "%f %f %f ", slego[i].length.x, slego[i].length.y, slego[i].length.z);
			fprintf(f, "%f %f %f ", slego[i].locate.x, slego[i].locate.y, slego[i].locate.z);
			fprintf(f, "%f %f %f ", slego[i].angle.x, slego[i].angle.y, slego[i].angle.z);
			fprintf(f, "%f %f %f ", slego[i].min.x, slego[i].min.y, slego[i].min.z);
			fprintf(f, "%f %f %f ", slego[i].max.x, slego[i].max.y, slego[i].max.z);
			fprintf(f, "%d %d\n", slego[i].type, slego[i].color);
		}
		fclose(f);
	}
	

}

void sub_menu_function3(int option) { // draw 서브메뉴
	lavaHeight = 0;
	num_lego = 0;
	if (option == 1) {
		FILE* f = fopen("save1.txt", "r+");
		int n;
		if (f == NULL) {
			printf("No such files\n");
			return;
		}
		fscanf_s(f, "%d", &num_lego);
		for (int i = 0; i < num_lego; i++) {
			fscanf(f, "%f %f %f ", &slego[i].length.x, &slego[i].length.y, &slego[i].length.z);
			fscanf(f, "%f %f %f ", &slego[i].locate.x, &slego[i].locate.y, &slego[i].locate.z);
			fscanf(f, "%f %f %f ", &slego[i].angle.x, &slego[i].angle.y, &slego[i].angle.z);
			fscanf(f, "%f %f %f ", &slego[i].min.x, &slego[i].min.y, &slego[i].min.z);
			fscanf(f, "%f %f %f ", &slego[i].max.x, &slego[i].max.y, &slego[i].max.z);
			fscanf(f, "%d %d\n", &slego[i].type, &slego[i].color);
		}
		fclose(f);
	}
	else if (option == 2) {
		FILE* f = fopen("save2.txt", "r+");
		int n;
		if (f == NULL) {
			printf("No such files\n");
			return;
		}
		fscanf_s(f, "%d", &num_lego);
		for (int i = 0; i < num_lego; i++) {
			fscanf(f, "%f %f %f ", &slego[i].length.x, &slego[i].length.y, &slego[i].length.z);
			fscanf(f, "%f %f %f ", &slego[i].locate.x, &slego[i].locate.y, &slego[i].locate.z);
			fscanf(f, "%f %f %f ", &slego[i].angle.x, &slego[i].angle.y, &slego[i].angle.z);
			fscanf(f, "%f %f %f ", &slego[i].min.x, &slego[i].min.y, &slego[i].min.z);
			fscanf(f, "%f %f %f ", &slego[i].max.x, &slego[i].max.y, &slego[i].max.z);
			fscanf(f, "%d %d\n", &slego[i].type, &slego[i].color);
		}
		fclose(f);
	}
	else if (option == 3) {
		FILE* f = fopen("save3.txt", "r+");
		int n;
		if (f == NULL) {
			printf("No such files\n");
			return;
		}
		fscanf_s(f, "%d", &num_lego);
		for (int i = 0; i < num_lego; i++) {
			fscanf(f, "%f %f %f ", &slego[i].length.x, &slego[i].length.y, &slego[i].length.z);
			fscanf(f, "%f %f %f ", &slego[i].locate.x, &slego[i].locate.y, &slego[i].locate.z);
			fscanf(f, "%f %f %f ", &slego[i].angle.x, &slego[i].angle.y, &slego[i].angle.z);
			fscanf(f, "%f %f %f ", &slego[i].min.x, &slego[i].min.y, &slego[i].min.z);
			fscanf(f, "%f %f %f ", &slego[i].max.x, &slego[i].max.y, &slego[i].max.z);
			fscanf(f, "%d %d\n", &slego[i].type, &slego[i].color);
		}	
		fclose(f);
	}
}

void main_menu_function(int option) {
	lavaHeight = 0;
	if (option == 1) {
		num_lego = 0;
	}
	else if (option == 2) {
		if (gamemode == 1) {
			lava = true;
		}
	}
	else if (option == 3) {
		lava = false;
	}
	else if (option == 999) {
		exit(0);
	}

	glutPostRedisplay();
}

