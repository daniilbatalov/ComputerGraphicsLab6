#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <GLee.h>
#include <glut.h>
#include <cmath>
#include <chrono>
#include <thread>

#define BOOL_STR(b) ((b)?"true":"false")
#define TV_STR(b) ((b)?"on":"off")
#define title_m title = "Lab6: X = " + std::to_string(x) + ", Y = " + std::to_string(y) + ", Z = " + std::to_string(z) + ", angle = " + std::to_string(angle) + ", lx:ly:lz = (" + std::to_string(lx) + ":" + std::to_string(ly) + ":" +std::to_string(lz) + "), fov: " + std::to_string(fov) + ", L0: " + BOOL_STR(sun_light) + ", L1: " + BOOL_STR(first_light) + ", L2: " + BOOL_STR(second_light) + ", L3: " + BOOL_STR(third_light)  + ", TV: " + TV_STR(tv)

float angle = 0.78539f; // 45 градусов

float lx = 0.7071067811f, ly = 0.0f, lz = -0.7071067811f;


float x = 1.0f, y = 1.0f, z = -1.0f;

float fov = 45.0f;

bool out = false, in = false, back = false;

float jumpVelocity = 0.3f, jumpAcceleration = 0.02f;

int mid_x, mid_y, jumpTime = 0;

bool wPressed = false, sPressed = false, aPressed = false, dPressed = false, plusPressed = false, minusPressed = false, jump = false, crouch = false, first_light = true, second_light = true, third_light = true, sun_light = true, tv = true;

std::string title_m;

void drawDivan()
{
	if (first_light)
	{
		glEnable(GL_LIGHT1);
	}
	glBegin(GL_QUADS);

	glColor4f(0.2549f, 0.4118f, 0.8824f, 1.0f);

	glNormal3f(0, 0, -1);
	glVertex3f(3.0f, 0.3f, -2.0f);
	glNormal3f(0, 0, -1);
	glVertex3f(3.0f, 0.0f, -2.0f);
	glNormal3f(0, 0, -1);
	glVertex3f(7.0f, 0.0f, -2.0f);
	glNormal3f(0, 0, -1);
	glVertex3f(7.0f, 0.3f, -2.0f); //передняя часть под сидушкой

	glNormal3f(0, 1, 0);
	glVertex3f(3.0f, 0.3f, -2.5f);
	glNormal3f(0, 1, 0);
	glVertex3f(3.0f, 0.3f, -2.0f);
	glNormal3f(0, 1, 0);
	glVertex3f(7.0f, 0.3f, -2.0f);
	glNormal3f(0, 1, 0);
	glVertex3f(7.0f, 0.3f, -2.5f); //сидушка
	 
	glColor4f(0.1255f, 0.2902f, 0.7843f, 1.0f);

	glNormal3f(0, 0, -1);
	glVertex3f(3.0f, 0.7f, -2.5f);
	glNormal3f(0, 0, -1);
	glVertex3f(3.0f, 0.0f, -2.5f);
	glNormal3f(0, 0, -1);
	glVertex3f(7.0f, 0.0f, -2.5f);
	glNormal3f(0, 0, -1);
	glVertex3f(7.0f, 0.7f, -2.5f); //передняя часть спинки

	glNormal3f(0, 1, 0);
	glVertex3f(3.0f, 0.7f, -2.6f);
	glNormal3f(0, 1, 0);
	glVertex3f(3.0f, 0.7f, -2.5f);
	glNormal3f(0, 1, 0);
	glVertex3f(7.0f, 0.7f, -2.5f);
	glNormal3f(0, 1, 0);
	glVertex3f(7.0f, 0.7f, -2.6f); //верхушка спинки

	glNormal3f(0, 0, 1);
	glVertex3f(3.0f, 0.0f, -2.6f);
	glNormal3f(0, 0, 1);
	glVertex3f(3.0f, 0.7f, -2.6f);
	glNormal3f(0, 0, 1);
	glVertex3f(7.0f, 0.7f, -2.6f);
	glNormal3f(0, 0, 1);
	glVertex3f(7.0f, 0.0f, -2.6f); //задняя часть спинки

	glNormal3f(-1, 0, 0);
	glVertex3f(3.0f, 0.5f, -2.5f);
	glNormal3f(-1, 0, 0);
	glVertex3f(3.0f, 0.7f, -2.5f);
	glNormal3f(-1, 0, 0);
	glVertex3f(3.0f, 0.7f, -2.6f);
	glNormal3f(-1, 0, 0);
	glVertex3f(3.0f, 0.5f, -2.6f); //левая часть спинки

	glNormal3f(1, 0, 0);
	glVertex3f(7.0f, 0.7f, -2.5f);
	glNormal3f(1, 0, 0);
	glVertex3f(7.0f, 0.5f, -2.5f);
	glNormal3f(1, 0, 0);
	glVertex3f(7.0f, 0.5f, -2.6f);
	glNormal3f(1, 0, 0);
	glVertex3f(7.0f, 0.7f, -2.6f); //правая часть спинки

	glColor4f(0.102f, 0.2314f, 0.6275f, 1.0f);

	glNormal3f(1, 0, 0);
	glVertex3f(3.0f, 0.0f, -2.0f);
	glNormal3f(1, 0, 0);
	glVertex3f(3.0f, 0.0f, -2.6f);
	glNormal3f(1, 0, 0);
	glVertex3f(3.0f, 0.5f, -2.6f);
	glNormal3f(1, 0, 0);
	glVertex3f(3.0f, 0.5f, -2.0f); //правая часть левого подлокотника

	glNormal3f(-1, 0, 0);
	glVertex3f(7.0f, 0.0f, -2.6f);
	glNormal3f(-1, 0, 0);
	glVertex3f(7.0f, 0.0f, -2.0f);
	glNormal3f(-1, 0, 0);
	glVertex3f(7.0f, 0.5f, -2.0f);
	glNormal3f(-1, 0, 0);
	glVertex3f(7.0f, 0.5f, -2.6f); //левая часть правого подлокотника

	glNormal3f(-1, 0, 0);
	glVertex3f(2.9f, 0.0f, -2.6f);
	glNormal3f(-1, 0, 0);
	glVertex3f(2.9f, 0.0f, -2.0f);
	glNormal3f(-1, 0, 0);
	glVertex3f(2.9f, 0.5f, -2.0f);
	glNormal3f(-1, 0, 0);
	glVertex3f(2.9f, 0.5f, -2.6f); //левая часть левого подлокотника

	glNormal3f(1, 0, 0);
	glVertex3f(7.1f, 0.0f, -2.0f);
	glNormal3f(1, 0, 0);
	glVertex3f(7.1f, 0.0f, -2.6f);
	glNormal3f(1, 0, 0);
	glVertex3f(7.1f, 0.5f, -2.6f);
	glNormal3f(1, 0, 0);
	glVertex3f(7.1f, 0.5f, -2.0f); //правая часть правого подлокотника

	glNormal3f(0, 1, 0);
	glVertex3f(2.9f, 0.5f, -2.0f);
	glNormal3f(0, 1, 0);
	glVertex3f(3.0f, 0.5f, -2.0f);
	glNormal3f(0, 1, 0);
	glVertex3f(3.0f, 0.5f, -2.6f);
	glNormal3f(0, 1, 0);
	glVertex3f(2.9f, 0.5f, -2.6f); //верхняя левого подлокотника

	glNormal3f(0, 1, 0);
	glVertex3f(7.1f, 0.5f, -2.6f);
	glNormal3f(0, 1, 0);
	glVertex3f(7.0f, 0.5f, -2.6f);
	glNormal3f(0, 1, 0);
	glVertex3f(7.0f, 0.5f, -2.0f);
	glNormal3f(0, 1, 0);
	glVertex3f(7.1f, 0.5f, -2.0f); //верхняя правого подлокотника

	glNormal3f(0, 0, -1);
	glVertex3f(3.0f, 0.5f, -2.0f);
	glNormal3f(0, 0, -1);
	glVertex3f(2.9f, 0.5f, -2.0f);
	glNormal3f(0, 0, -1);
	glVertex3f(2.9f, 0.0f, -2.0f);
	glNormal3f(0, 0, -1);
	glVertex3f(3.0f, 0.0f, -2.0f); //перед левого подлокотника

	glNormal3f(0, 0, 1);
	glVertex3f(2.9f, 0.5f, -2.6f);
	glNormal3f(0, 0, 1);
	glVertex3f(3.0f, 0.5f, -2.6f);
	glNormal3f(0, 0, 1);
	glVertex3f(3.0f, 0.0f, -2.6f);
	glNormal3f(0, 0, 1);
	glVertex3f(2.9f, 0.0f, -2.6f); //зад левого подлокотника

	glNormal3f(0, 0, -1);
	glVertex3f(7.0f, 0.0f, -2.0f);
	glNormal3f(0, 0, -1);
	glVertex3f(7.1f, 0.0f, -2.0f);
	glNormal3f(0, 0, -1);
	glVertex3f(7.1f, 0.5f, -2.0f);
	glNormal3f(0, 0, -1);
	glVertex3f(7.0f, 0.5f, -2.0f); //перед правого подлокотника

	glNormal3f(0, 0, 1);
	glVertex3f(7.1f, 0.0f, -2.6f);
	glNormal3f(0, 0, 1);
	glVertex3f(7.0f, 0.0f, -2.6f);
	glNormal3f(0, 0, 1);
	glVertex3f(7.0f, 0.5f, -2.6f);
	glNormal3f(0, 0, 1);
	glVertex3f(7.1f, 0.5f, -2.6f);  //зад правого подлокотника
	glEnd();
	if (first_light)
	{
		glDisable(GL_LIGHT1);
	}
}
void drawFirstRoom()
{
	if (first_light)
	{
		glEnable(GL_LIGHT1);
	}
	glBegin(GL_QUADS);
	glColor4f(0.5f, 0.5f, 0.5f, 1.0f);

	glNormal3f(1, 0, 0);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glNormal3f(1, 0, 0);
	glVertex3f(0.0f, 0.0f, -2.0f);
	glNormal3f(1, 0, 0);
	glVertex3f(0.0f, 3.0f, -2.0f);
	glNormal3f(1, 0, 0);
	glVertex3f(0.0f, 3.0f, 0.0f);

	glNormal3f(1, 0, 0);
	glVertex3f(0.0f, 0.5f, -2.0f);
	glNormal3f(1, 0, 0);
	glVertex3f(0.0f, 0.0f, -2.0f);
	glNormal3f(1, 0, 0);
	glVertex3f(0.0f, 0.0f, -3.0f);
	glNormal3f(1, 0, 0);
	glVertex3f(0.0f, 0.5f, -3.0f);

	glNormal3f(1, 0, 0);
	glVertex3f(0.0f, 2.5f, -2.0f);
	glNormal3f(1, 0, 0);
	glVertex3f(0.0f, 2.5f, -3.0f);
	glNormal3f(1, 0, 0);
	glVertex3f(0.0f, 3.0f, -3.0f);
	glNormal3f(1, 0, 0);
	glVertex3f(0.0f, 3.0f, -2.0f);

	glNormal3f(1, 0, 0);
	glVertex3f(0.0f, 3.0f, -3.0f);
	glNormal3f(1, 0, 0);
	glVertex3f(0.0f, 0.0f, -3.0f);
	glNormal3f(1, 0, 0);
	glVertex3f(0.0f, 0.0f, -5.0f);
	glNormal3f(1, 0, 0);
	glVertex3f(0.0f, 3.0f, -5.0f);	//левая стена первой комнаты

	glNormal3f(-1, 0, 0);
	glVertex3f(10.0f, 0.0f, -2.0f);
	glNormal3f(-1, 0, 0);
	glVertex3f(10.0f, 0.0f, 0.0f);
	glNormal3f(-1, 0, 0);
	glVertex3f(10.0f, 3.0f, 0.0f);
	glNormal3f(-1, 0, 0);
	glVertex3f(10.0f, 3.0f, -2.0f);

	glNormal3f(-1, 0, 0);
	glVertex3f(10.0f, 2.0f, -3.0f);
	glNormal3f(-1, 0, 0);
	glVertex3f(10.0f, 2.0f, -2.0f);
	glNormal3f(-1, 0, 0);
	glVertex3f(10.0f, 3.0f, -2.0f);
	glNormal3f(-1, 0, 0);
	glVertex3f(10.0f, 3.0f, -3.0f);

	glNormal3f(-1, 0, 0);
	glVertex3f(10.0f, 0.0f, -3.0f);
	glNormal3f(-1, 0, 0);
	glVertex3f(10.0f, 3.0f, -3.0f);
	glNormal3f(-1, 0, 0);
	glVertex3f(10.0f, 3.0f, -5.0f);
	glNormal3f(-1, 0, 0);
	glVertex3f(10.0f, 0.0f, -5.0f); //правая стена первой комнаты

	glColor4f(0.4f, 0.4f, 0.4f, 1.0f);

	glNormal3f(0, 0, -1);
	glVertex3f(10.0f, 0.0f, 0.0f);
	glNormal3f(0, 0, -1);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glNormal3f(0, 0, -1);
	glVertex3f(0.0f, 3.0f, 0.0f);
	glNormal3f(0, 0, -1);
	glVertex3f(10.0f, 3.0f, 0.0f);	//задняя стена первой комнаты

	glNormal3f(0, 0, 1);
	glVertex3f(0.0f, 3.0f, -5.0f);
	glNormal3f(0, 0, 1);
	glVertex3f(0.0f, 0.0f, -5.0f);
	glNormal3f(0, 0, 1);
	glVertex3f(6.0f, 0.0f, -5.0f);
	glNormal3f(0, 0, 1);
	glVertex3f(6.0f, 3.0f, -5.0f);

	glNormal3f(0, 0, 1);
	glVertex3f(6.0f, 3.0f, -5.0f);
	glNormal3f(0, 0, 1);
	glVertex3f(6.0f, 2.0f, -5.0f);
	glNormal3f(0, 0, 1);
	glVertex3f(8.0f, 2.0f, -5.0f);
	glNormal3f(0, 0, 1);
	glVertex3f(8.0f, 3.0f, -5.0f);

	glNormal3f(0, 0, 1);
	glVertex3f(8.0f, 3.0f, -5.0f);
	glNormal3f(0, 0, 1);
	glVertex3f(8.0f, 0.0f, -5.0f);
	glNormal3f(0, 0, 1);
	glVertex3f(10.0f, 0.0f, -5.0f);
	glNormal3f(0, 0, 1);
	glVertex3f(10.0f, 3.0f, -5.0f);	//передняя стена первой комнаты

	glColor4f(0.3961f, 0.2627f, 0.1294f, 1.0f);
	glNormal3f(0, 1, 0);
	glVertex3f(0.0f, 0.0002f, -5.0f);
	glNormal3f(0, 1, 0);
	glVertex3f(0.0f, 0.0002f, 0.0f);
	glNormal3f(0, 1, 0);
	glVertex3f(10.0f, 0.0002f, 0.0f);
	glNormal3f(0, 1, 0);
	glVertex3f(10.0f, 0.0002f, -5.0f); // пол первой комнаты

	glColor4f(0.9f, 0.9f, 0.9f, 1.0f);
	glNormal3f(0, -1, 0);
	glVertex3f(0.0f, 3.0f, 0.0f);
	glNormal3f(0, -1, 0);
	glVertex3f(0.0f, 3.0f, -5.0f);
	glNormal3f(0, -1, 0);
	glVertex3f(10.0f, 3.0f, -5.0f);
	glNormal3f(0, -1, 0);
	glVertex3f(10.0f, 3.0f, 0.0f); // потолок первой комнаты
	glEnd();
	if (first_light)
	{
		glDisable(GL_LIGHT1);
	}

}
void drawTVSet()
{
	if (first_light)
	{
		glEnable(GL_LIGHT1);
	}
	glBegin(GL_QUADS);
	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);

	glVertex3f(7.0f, 1.0f, -0.05f);
	glVertex3f(7.0f, 1.0f, 0.0f);
	glVertex3f(7.0f, 2.5f, 0.0f);
	glVertex3f(7.0f, 2.5f, -0.05f);

	glVertex3f(6.95f, 1.0f, -0.05f);
	glVertex3f(6.95f, 1.0f, 0.0f);
	glVertex3f(6.95f, 2.5f, 0.0f);
	glVertex3f(6.95f, 2.5f, -0.05f);

	glVertex3f(7.0f, 1.0f, -0.05f);
	glVertex3f(6.95f, 1.0f, -0.05f);
	glVertex3f(6.95f, 2.5f, -0.05f);
	glVertex3f(7.0f, 2.5f, -0.05f);

	glVertex3f(3.0f, 1.0f, -0.05f);
	glVertex3f(3.0f, 1.0f, 0.0f);
	glVertex3f(3.0f, 2.5f, 0.0f);
	glVertex3f(3.0f, 2.5f, -0.05f);

	glVertex3f(3.05f, 1.0f, -0.05f);
	glVertex3f(3.05f, 1.0f, 0.0f);
	glVertex3f(3.05f, 2.5f, 0.0f);
	glVertex3f(3.05f, 2.5f, -0.05f);

	glVertex3f(3.05f, 1.0f, -0.05f);
	glVertex3f(3.0f, 1.0f, -0.05f);
	glVertex3f(3.0f, 2.5f, -0.05f);
	glVertex3f(3.05f, 2.5f, -0.05f); // верт. рамки тв

	glVertex3f(3.0f, 2.5f, 0.0f);
	glVertex3f(7.0f, 2.5f, 0.0f);
	glVertex3f(7.0f, 2.5f, -0.05f);
	glVertex3f(3.0f, 2.5f, -0.05f);

	glVertex3f(3.0f, 2.45f, 0.0f);
	glVertex3f(7.0f, 2.45f, 0.0f);
	glVertex3f(7.0f, 2.45f, -0.05f);
	glVertex3f(3.0f, 2.45f, -0.05f);

	glVertex3f(3.0f, 2.5f, -0.05f);
	glVertex3f(7.0f, 2.5f, -0.05f);
	glVertex3f(7.0f, 2.45f, -0.05f);
	glVertex3f(3.0f, 2.45f, -0.05f);

	glVertex3f(3.0f, 1.0f, 0.0f);
	glVertex3f(7.0f, 1.0f, 0.0f);
	glVertex3f(7.0f, 1.0f, -0.05f);
	glVertex3f(3.0f, 1.0f, -0.05f);

	glVertex3f(3.0f, 1.05f, 0.0f);
	glVertex3f(7.0f, 1.05f, 0.0f);
	glVertex3f(7.0f, 1.05f, -0.05f);
	glVertex3f(3.0f, 1.05f, -0.05f);

	glVertex3f(3.0f, 1.0f, -0.05f);
	glVertex3f(7.0f, 1.0f, -0.05f);
	glVertex3f(7.0f, 1.05f, -0.05f);
	glVertex3f(3.0f, 1.05f, -0.05f);	//гор. рамки тв

	//glColor4f(0.0f, 0.0f, 0.8f, 1.0f);

	GLfloat no_em[] = { 0.0f, 0.0f, 0.0f, 0.00f };

	GLfloat tv_em[] = { 0.0f, 0.0f, 0.8f, 1.0f };
	GLfloat tv_em_off[] = {0.05f, 0.05f, 0.05f, 0.2f};

	if (tv)
	{
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, tv_em);
		
	}
	else
	{
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, tv_em_off);
	}
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 128);
	glNormal3f(0, 0, -1);
	glVertex3f(3.0f, 1.05f, -0.04f);
	glNormal3f(0, 0, -1);
	glVertex3f(7.0f, 1.05f, -0.04f);
	glNormal3f(0, 0, -1);
	glVertex3f(7.0f, 2.45f, -0.04f);
	glNormal3f(0, 0, -1);
	glVertex3f(3.0f, 2.45f, -0.04f);

	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, no_em);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0);

	glEnd();
	if (first_light)
	{
		glDisable(GL_LIGHT1);
	}
}
void drawSecondRoom()
{
	if (second_light)
	{
		glEnable(GL_LIGHT2);
	}
	glBegin(GL_QUADS);
	glColor4f(0.4f, 0.4f, 0.4f, 1.0f);

	glNormal3f(0, 0, 1);
	glVertex3f(5.0f, 0.0f, -10.0f);
	glNormal3f(0, 0, 1);
	glVertex3f(10.0f, 0.0f, -10.0f);
	glNormal3f(0, 0, 1);
	glVertex3f(10.0f, 3.0f, -10.0f);
	glNormal3f(0, 0, 1);
	glVertex3f(5.0f, 3.0f, -10.0f); // передняя стенка второй комнаты

	glColor4f(0.5f, 0.5f, 0.5f, 1.0f);

	glNormal3f(-1, 0, 0);
	glVertex3f(10.0f, 0.0f, -7.0f);
	glNormal3f(-1, 0, 0);
	glVertex3f(10.0f, 0.0f, -5.0f);
	glNormal3f(-1, 0, 0);
	glVertex3f(10.0f, 3.0f, -5.0f);
	glNormal3f(-1, 0, 0);
	glVertex3f(10.0f, 3.0f, -7.0f);

	glNormal3f(-1, 0, 0);
	glVertex3f(10.0f, 2.0f, -8.0f);
	glNormal3f(-1, 0, 0);
	glVertex3f(10.0f, 2.0f, -7.0f);
	glNormal3f(-1, 0, 0);
	glVertex3f(10.0f, 3.0f, -7.0f);
	glNormal3f(-1, 0, 0);
	glVertex3f(10.0f, 3.0f, -8.0f);
	
	glNormal3f(-1, 0, 0);
	glVertex3f(10.0f, 0.0f, -8.0f);
	glNormal3f(-1, 0, 0);
	glVertex3f(10.0f, 3.0f, -8.0f);
	glNormal3f(-1, 0, 0);
	glVertex3f(10.0f, 3.0f, -10.0f);
	glNormal3f(-1, 0, 0);
	glVertex3f(10.0f, 0.0f, -10.0f); // правая стенка второй комнаты

	glNormal3f(1, 0, 0);
	glVertex3f(5.0f, 0.0f, -5.0f);
	glNormal3f(1, 0, 0);
	glVertex3f(5.0f, 0.0f, -7.0f);
	glNormal3f(1, 0, 0);
	glVertex3f(5.0f, 3.0f, -7.0f);
	glNormal3f(1, 0, 0);
	glVertex3f(5.0f, 3.0f, -5.0f);

	glNormal3f(1, 0, 0);
	glVertex3f(5.0f, 0.5f, -7.0f);
	glNormal3f(1, 0, 0);
	glVertex3f(5.0f, 0.0f, -7.0f);
	glNormal3f(1, 0, 0);
	glVertex3f(5.0f, 0.0f, -8.0f);
	glNormal3f(1, 0, 0);
	glVertex3f(5.0f, 0.5f, -8.0f);

	glNormal3f(1, 0, 0);
	glVertex3f(5.0f, 2.5f, -7.0f);
	glNormal3f(1, 0, 0);
	glVertex3f(5.0f, 2.5f, -8.0f);
	glNormal3f(1, 0, 0);
	glVertex3f(5.0f, 3.0f, -8.0f);
	glNormal3f(1, 0, 0);
	glVertex3f(5.0f, 3.0f, -7.0f);

	glNormal3f(1, 0, 0);
	glVertex3f(5.0f, 3.0f, -8.0f);
	glNormal3f(1, 0, 0);
	glVertex3f(5.0f, 0.0f, -8.0f);
	glNormal3f(1, 0, 0);
	glVertex3f(5.0f, 0.0f, -10.0f);
	glNormal3f(1, 0, 0);
	glVertex3f(5.0f, 3.0f, -10.0f); // левая стенка второй комнаты

	glColor4f(0.4f, 0.25, 0.11f, 1.0f);

	glNormal3f(0, 1, 0);
	glVertex3f(5.0f, 0.0002f, -10.0f);
	glNormal3f(0, 1, 0);
	glVertex3f(5.0f, 0.0002f, -5.0f);
	glNormal3f(0, 1, 0);
	glVertex3f(10.0f, 0.0002f, -5.0f);
	glNormal3f(0, 1, 0);
	glVertex3f(10.0f, 0.0002f, -10.0f); // пол второй комнаты

	glColor4f(0.9f, 0.9f, 0.9f, 1.0f);

	glNormal3f(0, -1, 0);
	glVertex3f(5.0f, 3.0f, -5.0f);
	glNormal3f(0, -1, 0);
	glVertex3f(5.0f, 3.0f, -10.0f);
	glNormal3f(0, -1, 0);
	glVertex3f(10.0f, 3.0f, -10.0f);
	glNormal3f(0, -1, 0);
	glVertex3f(10.0f, 3.0f, -5.0f); // потолок второй комнаты

	glNormal3f(0, 0, 1);
	glVertex3f(5.0f, 3.0f, -5.001f);
	glNormal3f(0, 0, 1);
	glVertex3f(5.0f, 0.0f, -5.001f);
	glNormal3f(0, 0, 1);
	glVertex3f(6.0f, 0.0f, -5.001f);
	glNormal3f(0, 0, 1);
	glVertex3f(6.0f, 3.0f, -5.001f);

	glNormal3f(0, 0, 1);
	glVertex3f(6.0f, 3.0f, -5.001f);
	glNormal3f(0, 0, 1);
	glVertex3f(6.0f, 2.0f, -5.001f);
	glNormal3f(0, 0, 1);
	glVertex3f(8.0f, 2.0f, -5.001f);
	glNormal3f(0, 0, 1);
	glVertex3f(8.0f, 3.0f, -5.001f);

	glNormal3f(0, 0, 1);
	glVertex3f(8.0f, 3.0f, -5.001f);
	glNormal3f(0, 0, 1);
	glVertex3f(8.0f, 0.0f, -5.001f);
	glNormal3f(0, 0, 1);
	glVertex3f(10.0f, 0.0f, -5.001f);
	glNormal3f(0, 0, 1);
	glVertex3f(10.0f, 3.0f, -5.001f); // задняя стенка

	glEnd();
	if (second_light)
	{
		glDisable(GL_LIGHT2);
	}

}
void drawBed()
{
	if (second_light)
	{
		glEnable(GL_LIGHT2);
	}
	glBegin(GL_QUADS);

	glColor4f(0.6078f, 0.0667f, 0.1176f, 1.0f);

	glNormal3f(0, 1, 0);
	glVertex3f(6.0f, 0.3f, -9.8f);
	glNormal3f(0, 1, 0);
	glVertex3f(6.0f, 0.3f, -8.6f);
	glNormal3f(0, 1, 0);
	glVertex3f(7.75f, 0.3f, -8.6f);
	glNormal3f(0, 1, 0);
	glVertex3f(7.75f, 0.3f, -9.8f); 

	glNormal3f(0, 0, 1);
	glVertex3f(6.0f, 0.2f, -9.8f);
	glNormal3f(0, 0, 1);
	glVertex3f(6.0f, 0.3f, -9.8f);
	glNormal3f(0, 0, 1);
	glVertex3f(7.75f, 0.3f, -9.8f);
	glNormal3f(0, 0, 1);
	glVertex3f(7.75f, 0.2f, -9.8f);

	glNormal3f(0, 0, -1);
	glVertex3f(6.0f, 0.2f, -8.6f);
	glNormal3f(0, 0, -1);
	glVertex3f(6.0f, 0.3f, -8.6f);
	glNormal3f(0, 0, -1);
	glVertex3f(7.75f, 0.3f, -8.6f);
	glNormal3f(0, 0, -1);
	glVertex3f(7.75f, 0.2f, -8.6f);

	glNormal3f(-1, 0, 0);
	glVertex3f(6.0f, 0.3f, -8.6f);
	glNormal3f(-1, 0, 0);
	glVertex3f(6.0f, 0.3f, -9.8f);
	glNormal3f(-1, 0, 0);
	glVertex3f(6.0f, 0.2f, -9.8f);
	glNormal3f(-1, 0, 0);
	glVertex3f(6.0f, 0.2f, -8.6f);

	glColor4f(0.949f, 0.9529f, 0.9569f, 1.0f);

	glNormal3f(0, 1, 0);
	glVertex3f(7.75f, 0.3f, -9.8f);
	glNormal3f(0, 1, 0);
	glVertex3f(7.75f, 0.3f, -8.6f);
	glNormal3f(0, 1, 0);
	glVertex3f(8.5f, 0.3f, -8.6f);
	glNormal3f(0, 1, 0);
	glVertex3f(8.5f, 0.3f, -9.8f);

	glNormal3f(0, 0, 1);
	glVertex3f(7.75f, 0.2f, -9.8f);
	glNormal3f(0, 0, 1);
	glVertex3f(7.75f, 0.3f, -9.8f);
	glNormal3f(0, 0, 1);
	glVertex3f(8.5f, 0.3f, -9.8f);
	glNormal3f(0, 0, 1);
	glVertex3f(8.5f, 0.2f, -9.8f);

	glNormal3f(0, 0, -1);
	glVertex3f(7.75f, 0.2f, -8.6f);
	glNormal3f(0, 0, -1);
	glVertex3f(7.75f, 0.3f, -8.6f);
	glNormal3f(0, 0, -1);
	glVertex3f(8.5f, 0.3f, -8.6f);
	glNormal3f(0, 0, -1);
	glVertex3f(8.5f, 0.2f, -8.6f);

	glNormal3f(-1, 0, 0);
	glVertex3f(8.5f, 0.3f, -8.6f);
	glNormal3f(-1, 0, 0);
	glVertex3f(8.5f, 0.3f, -9.8f);
	glNormal3f(-1, 0, 0);
	glVertex3f(8.5f, 0.2f, -9.8f);
	glNormal3f(-1, 0, 0);
	glVertex3f(8.5f, 0.2f, -8.6f);

	glColor4f(0.40f, 0.34f, 0.26f, 1.0f);

	glNormal3f(0, 1, 0);
	glVertex3f(6.0f, 0.0f, -9.8f);
	glNormal3f(0, 1, 0);
	glVertex3f(6.0f, 0.2f, -9.8f);
	glNormal3f(0, 1, 0);
	glVertex3f(8.5f, 0.2f, -9.8f);
	glNormal3f(0, 1, 0);
	glVertex3f(8.5f, 0.0f, -9.8f);

	glNormal3f(0, -1, 0);
	glVertex3f(6.0f, 0.0f, -8.6f);
	glNormal3f(0, -1, 0);
	glVertex3f(6.0f, 0.2f, -8.6f);
	glNormal3f(0, -1, 0);
	glVertex3f(8.5f, 0.2f, -8.6f);
	glNormal3f(0, -1, 0);
	glVertex3f(8.5f, 0.0f, -8.6f);

	glNormal3f(-1, 0, 0);
	glVertex3f(6.0f, 0.2f, -9.8f);
	glNormal3f(-1, 0, 0);
	glVertex3f(6.0f, 0.0f, -9.8f);
	glNormal3f(-1, 0, 0);
	glVertex3f(6.0f, 0.0f, -8.6f);
	glNormal3f(-1, 0, 0);
	glVertex3f(6.0f, 0.2f, -8.6f);

	glNormal3f(-1, 0, 0);
	glVertex3f(8.5f, 0.2f, -9.8f);
	glNormal3f(-1, 0, 0);
	glVertex3f(8.5f, 0.0f, -9.8f);
	glNormal3f(-1, 0, 0);
	glVertex3f(8.5f, 0.0f, -8.6f);
	glNormal3f(-1, 0, 0);
	glVertex3f(8.5f, 0.2f, -8.6f);

	glEnd();
	if (second_light)
	{
		glDisable(GL_LIGHT2);
	}
}
void drawCloset(bool backDoor)
{
	if (!backDoor)
	{
		glDisable(GL_LIGHT0);
	}
	if (third_light)
	{
		glEnable(GL_LIGHT3);
	}
	glBegin(GL_QUADS);
	glColor4f(0.3176f, 0.2118f, 0.102f, 1.0f);

	glNormal3f(0, 0, 1);
	glVertex3f(11.0f, 2.0f, -6.1f);
	glNormal3f(0, 0, 1);
	glVertex3f(11.0f, 0.0f, -6.1f);
	glNormal3f(0, 0, 1);
	glVertex3f(14.0f, 0.0f, -6.1f);
	glNormal3f(0, 0, 1);
	glVertex3f(14.0f, 2.0f, -6.1f); // задняя стенка

	glColor4f(0.2549f, 0.1686f, 0.0824f, 1.0f);

	glNormal3f(1, 0, 0);
	glVertex3f(11.0f, 2.0f, -6.1f);
	glNormal3f(1, 0, 0);
	glVertex3f(11.0f, 0.0f, -6.1f);
	glNormal3f(1, 0, 0);
	glVertex3f(11.0f, 0.0f, -6.5f);
	glNormal3f(1, 0, 0);
	glVertex3f(11.0f, 2.0f, -6.5f);

	glNormal3f(-1, 0, 0);
	glVertex3f(11.1f, 0.0f, -6.1f);
	glNormal3f(-1, 0, 0);
	glVertex3f(11.1f, 2.0f, -6.1f);
	glNormal3f(-1, 0, 0);
	glVertex3f(11.1f, 2.0f, -6.5f);
	glNormal3f(-1, 0, 0);
	glVertex3f(11.1f, 0.0f, -6.5f);

	glNormal3f(0, 0, 1);
	glVertex3f(11.0f, 2.0f, -6.5f);
	glNormal3f(0, 0, 1);
	glVertex3f(11.0f, 0.0f, -6.5f);
	glNormal3f(0, 0, 1);
	glVertex3f(11.1f, 0.0f, -6.5f);
	glNormal3f(0, 0, 1);
	glVertex3f(11.1f, 2.0f, -6.5f); //правая стенка


	glNormal3f(-1, 0, 0);
	glVertex3f(14.0f, 0.0f, -6.1f);
	glNormal3f(-1, 0, 0);
	glVertex3f(14.0f, 2.0f, -6.1f);
	glNormal3f(-1, 0, 0);
	glVertex3f(14.0f, 2.0f, -6.5f);
	glNormal3f(-1, 0, 0);
	glVertex3f(14.0f, 0.0f, -6.5f);

	glNormal3f(1, 0, 0);
	glVertex3f(13.9f, 2.0f, -6.1f);
	glNormal3f(1, 0, 0);
	glVertex3f(13.9f, 0.0f, -6.1f);
	glNormal3f(1, 0, 0);
	glVertex3f(13.9f, 0.0f, -6.5f);
	glNormal3f(1, 0, 0);
	glVertex3f(13.9f, 2.0f, -6.5f);

	glNormal3f(0, 0, 1);
	glVertex3f(14.0f, 0.0f, -6.5f);
	glNormal3f(0, 0, 1);
	glVertex3f(14.0f, 2.0f, -6.5f);
	glNormal3f(0, 0, 1);
	glVertex3f(13.9f, 2.0f, -6.5f);
	glNormal3f(0, 0, 1);
	glVertex3f(13.9f, 0.0f, -6.5f);	//левая стенка 


	glNormal3f(0, -1, 0);
	glVertex3f(11.0f, 2.0f, -6.1f);
	glNormal3f(0, -1, 0);
	glVertex3f(11.0f, 2.0f, -6.5f);
	glNormal3f(0, -1, 0);
	glVertex3f(14.0f, 2.0f, -6.5f);
	glNormal3f(0, -1, 0);
	glVertex3f(14.0f, 2.0f, -6.1f);

	glNormal3f(0, 1, 0);
	glVertex3f(11.0f, 1.9f, -6.5f);
	glNormal3f(0, 1, 0);
	glVertex3f(11.0f, 1.9f, -6.1f);
	glNormal3f(0, 1, 0);
	glVertex3f(14.0f, 1.9f, -6.1f);
	glNormal3f(0, 1, 0);
	glVertex3f(14.0f, 1.9f, -6.5f);

	glNormal3f(0, 0, 1);
	glVertex3f(11.0f, 2.0f, -6.5f);
	glNormal3f(0, 0, 1);
	glVertex3f(11.0f, 1.9f, -6.5f);
	glNormal3f(0, 0, 1);
	glVertex3f(14.0f, 1.9f, -6.5f);
	glNormal3f(0, 0, 1);
	glVertex3f(14.0f, 2.0f, -6.5f);	//верхняя стенка

	glNormal3f(1, 0, 0);
	glVertex3f(12.45f, 2.0f, -6.1f);
	glNormal3f(1, 0, 0);
	glVertex3f(12.45f, 0.0f, -6.1f);
	glNormal3f(1, 0, 0);
	glVertex3f(12.45f, 0.0f, -6.501f);
	glNormal3f(1, 0, 0);
	glVertex3f(12.45f, 2.0f, -6.501f);

	glNormal3f(-1, 0, 0);
	glVertex3f(12.55f, 0.0f, -6.1f);
	glNormal3f(-1, 0, 0);
	glVertex3f(12.55f, 2.0f, -6.1f);
	glNormal3f(-1, 0, 0);
	glVertex3f(12.55f, 2.0f, -6.501f);
	glNormal3f(-1, 0, 0);
	glVertex3f(12.55f, 0.0f, -6.501f);

	glNormal3f(0, 0, 1);
	glVertex3f(12.45f, 2.0f, -6.501f);
	glNormal3f(0, 0, 1);
	glVertex3f(12.45f, 0.0f, -6.501f);
	glNormal3f(0, 0, 1);
	glVertex3f(12.55f, 0.0f, -6.501f);
	glNormal3f(0, 0, 1);
	glVertex3f(12.55f, 2.0f, -6.501f); //средняя стенка 

	glColor4f(0.2039f, 0.1333f, 0.0667f, 1.0f);

	glNormal3f(0, -1, 0);
	glVertex3f(11.1f, 1.5f, -6.1f);
	glNormal3f(0, -1, 0);
	glVertex3f(11.1f, 1.5f, -6.51f);
	glNormal3f(0, -1, 0);
	glVertex3f(13.9f, 1.5f, -6.51f);
	glNormal3f(0, -1, 0);
	glVertex3f(13.9f, 1.5f, -6.11f);

	glNormal3f(0, 1, 0);
	glVertex3f(11.1f, 1.4f, -6.51f);
	glNormal3f(0, 1, 0);
	glVertex3f(11.1f, 1.4f, -6.1f);
	glNormal3f(0, 1, 0);
	glVertex3f(13.9f, 1.4f, -6.1f);
	glNormal3f(0, 1, 0);
	glVertex3f(13.9f, 1.4f, -6.51f);

	glNormal3f(0, 0, 1);
	glVertex3f(11.1f, 1.5f, -6.51f);
	glNormal3f(0, 0, 1);
	glVertex3f(11.1f, 1.4f, -6.51f);
	glNormal3f(0, 0, 1);
	glVertex3f(13.9f, 1.4f, -6.51f);
	glNormal3f(0, 0, 1);
	glVertex3f(13.9f, 1.5f, -6.51f); // 1 полка

	glNormal3f(0, -1, 0);
	glVertex3f(11.1f, 1.0f, -6.1f);
	glNormal3f(0, -1, 0);
	glVertex3f(11.1f, 1.0f, -6.51f);
	glNormal3f(0, -1, 0);
	glVertex3f(13.9f, 1.0f, -6.51f);
	glNormal3f(0, -1, 0);
	glVertex3f(13.9f, 1.0f, -6.1f);

	glNormal3f(0, 1, 0);
	glVertex3f(11.1f, 0.9f, -6.51f);
	glNormal3f(0, 1, 0);
	glVertex3f(11.1f, 0.9f, -6.1f);
	glNormal3f(0, 1, 0);
	glVertex3f(13.9f, 0.9f, -6.1f);
	glNormal3f(0, 1, 0);
	glVertex3f(13.9f, 0.9f, -6.51f);

	glNormal3f(0, 0, 1);
	glVertex3f(11.1f, 1.0f, -6.51f);
	glNormal3f(0, 0, 1);
	glVertex3f(11.1f, 0.9f, -6.51f);
	glNormal3f(0, 0, 1);
	glVertex3f(13.9f, 0.9f, -6.51f);
	glNormal3f(0, 0, 1);
	glVertex3f(13.9f, 1.0f, -6.51f); // 2 полка

	glNormal3f(0, -1, 0);
	glVertex3f(11.1f, 0.5f, -6.1f);
	glNormal3f(0, -1, 0);
	glVertex3f(11.1f, 0.5f, -6.51f);
	glNormal3f(0, -1, 0);
	glVertex3f(13.9f, 0.5f, -6.51f);
	glNormal3f(0, -1, 0);
	glVertex3f(13.9f, 0.5f, -6.1f);

	glNormal3f(0, 1, 0);
	glVertex3f(11.1f, 0.4f, -6.51f);
	glNormal3f(0, 1, 0);
	glVertex3f(11.1f, 0.4f, -6.1f);
	glNormal3f(0, 1, 0);
	glVertex3f(13.9f, 0.4f, -6.1f);
	glNormal3f(0, 1, 0);
	glVertex3f(13.9f, 0.4f, -6.51f);

	glNormal3f(0, 0, 1);
	glVertex3f(11.1f, 0.5f, -6.51f);
	glNormal3f(0, 0, 1);
	glVertex3f(11.1f, 0.4f, -6.51f);
	glNormal3f(0, 0, 1);
	glVertex3f(13.9f, 0.4f, -6.51f);
	glNormal3f(0, 0, 1);
	glVertex3f(13.9f, 0.5f, -6.51f); // 3 полка
	glEnd();
	if (third_light)
	{
		glDisable(GL_LIGHT3);
	}
	if (!backDoor && sun_light)
	{
		glEnable(GL_LIGHT0);
	}
}
void drawDoors(bool outDoor, bool inDoor, bool backDoor)
{
	if (first_light)
	{
		glEnable(GL_LIGHT1);
	}
	glBegin(GL_QUADS);
	if (!outDoor)
	{
		glColor4f(0.9f, 0.922f, 0.843f, 1.0f);

		glNormal3f(-1, 0, 0);
		glVertex3f(10.0f, 0.0f, -2.1f);
		glNormal3f(-1, 0, 0);
		glVertex3f(10.0f, 2.0f, -2.1f);
		glNormal3f(-1, 0, 0);
		glVertex3f(10.0f, 2.0f, -3.0f);
		glNormal3f(-1, 0, 0);
		glVertex3f(10.0f, 0.0f, -3.0f);

		glColor4f(0.3176f, 0.2118f, 0.102f, 1.0f);
		glNormal3f(-1, 0, 0);
		glVertex3f(10.0f, 0.0f, -2.0f);
		glNormal3f(-1, 0, 0);
		glVertex3f(10.0f, 2.0f, -2.0f);
		glNormal3f(-1, 0, 0);
		glVertex3f(10.0f, 2.0f, -2.1f);
		glNormal3f(-1, 0, 0);
		glVertex3f(10.0f, 0.0f, -2.1f);
	}
	else
	{
		glColor4f(0.9f, 0.922f, 0.843f, 1.0f);

		glNormal3f(0, 0, -1);
		glVertex3f(10.0f, 2.0f, -3.0f);
		glNormal3f(0, 0, -1);
		glVertex3f(10.0f, 0.0f, -3.0f);
		glNormal3f(0, 0, -1);
		glVertex3f(9.1f, 0.0f, -3.0f);
		glNormal3f(0, 0, -1);
		glVertex3f(9.1f, 2.0f, -3.0f);

		glNormal3f(0, 0, 1);
		glVertex3f(10.0f, 2.0f, -3.001f);
		glNormal3f(0, 0, 1);
		glVertex3f(10.0f, 0.0f, -3.001f);
		glNormal3f(0, 0, 1);
		glVertex3f(9.1f, 0.0f, -3.001f);
		glNormal3f(0, 0, 1);
		glVertex3f(9.1f, 2.0f, -3.001f);

		glColor4f(0.3176f, 0.2118f, 0.102f, 1.0f);

		glNormal3f(0, 0, -1);
		glVertex3f(9.1f, 2.0f, -3.0f);
		glNormal3f(0, 0, -1);
		glVertex3f(9.1f, 0.0f, -3.0f);
		glNormal3f(0, 0, -1);
		glVertex3f(9.0f, 0.0f, -3.0f);
		glNormal3f(0, 0, -1);
		glVertex3f(9.0f, 2.0f, -3.0f);

		glNormal3f(0, 0, 1);
		glVertex3f(9.1f, 2.0f, -3.001f);
		glNormal3f(0, 0, 1);
		glVertex3f(9.1f, 0.0f, -3.001f);
		glNormal3f(0, 0, 1);
		glVertex3f(9.0f, 0.0f, -3.001f);
		glNormal3f(0, 0, 1);
		glVertex3f(9.0f, 2.0f, -3.001f);


	}
	glEnd();
	if (first_light)
	{
		glDisable(GL_LIGHT1);
	}
	if (!inDoor)
	{
		if (first_light)
		{
			glEnable(GL_LIGHT1);
		}
		glBegin(GL_QUADS);
		glColor4f(0.9f, 0.922f, 0.843f, 1.0f);

		glNormal3f(0, 0, 1);
		glVertex3f(6.0f, 2.0f, -5.0f);
		glNormal3f(0, 0, 1);
		glVertex3f(6.0f, 0.0f, -5.0f);
		glNormal3f(0, 0, 1);
		glVertex3f(6.9f, 0.0f, -5.0f);
		glNormal3f(0, 0, 1);
		glVertex3f(6.9f, 2.0f, -5.0f);

		glNormal3f(0, 0, 1);
		glVertex3f(8.0f, 0.0f, -5.0f);
		glNormal3f(0, 0, 1);
		glVertex3f(8.0f, 2.0f, -5.0f);
		glNormal3f(0, 0, 1);
		glVertex3f(7.1f, 2.0f, -5.0f);
		glNormal3f(0, 0, 1);
		glVertex3f(7.1f, 0.0f, -5.0f);

		glColor4f(0.3176f, 0.2118f, 0.102f, 1.0f);

		glNormal3f(0, 0, 1);
		glVertex3f(6.9f, 2.0f, -5.0f);
		glNormal3f(0, 0, 1);
		glVertex3f(6.9f, 0.0f, -5.0f);
		glNormal3f(0, 0, 1);
		glVertex3f(7.0f, 0.0f, -5.0f);
		glNormal3f(0, 0, 1);
		glVertex3f(7.0f, 2.0f, -5.0f);

		glNormal3f(0, 0, 1);
		glVertex3f(7.1f, 0.0f, -5.0f);
		glNormal3f(0, 0, 1);
		glVertex3f(7.1f, 2.0f, -5.0f);
		glNormal3f(0, 0, 1);
		glVertex3f(7.0f, 2.0f, -5.0f);
		glNormal3f(0, 0, 1);
		glVertex3f(7.0f, 0.0f, -5.0f);

		glEnd();
		if (first_light)
		{
			glDisable(GL_LIGHT1);
		}
		if (second_light)
		{
			glEnable(GL_LIGHT2);
		}
		glBegin(GL_QUADS);
		glColor4f(0.9f, 0.922f, 0.843f, 1.0f);

		glNormal3f(0, 0, 1);
		glVertex3f(6.0f, 2.0f, -5.001f);
		glNormal3f(0, 0, 1);
		glVertex3f(6.0f, 0.0f, -5.001f);
		glNormal3f(0, 0, 1);
		glVertex3f(6.9f, 0.0f, -5.001f);
		glNormal3f(0, 0, 1);
		glVertex3f(6.9f, 2.0f, -5.001f);

		glNormal3f(0, 0, 1);
		glVertex3f(8.0f, 0.0f, -5.001f);
		glNormal3f(0, 0, 1);
		glVertex3f(8.0f, 2.0f, -5.001f);
		glNormal3f(0, 0, 1);
		glVertex3f(7.1f, 2.0f, -5.001f);
		glNormal3f(0, 0, 1);
		glVertex3f(7.1f, 0.0f, -5.001f);

		glColor4f(0.3176f, 0.2118f, 0.102f, 1.0f);

		glNormal3f(0, 0, 1);
		glVertex3f(6.9f, 2.0f, -5.001f);
		glNormal3f(0, 0, 1);
		glVertex3f(6.9f, 0.0f, -5.001f);
		glNormal3f(0, 0, 1);
		glVertex3f(7.0f, 0.0f, -5.001f);
		glNormal3f(0, 0, 1);
		glVertex3f(7.0f, 2.0f, -5.001f);

		glNormal3f(0, 0, 1);
		glVertex3f(7.1f, 0.0f, -5.001f);
		glNormal3f(0, 0, 1);
		glVertex3f(7.1f, 2.0f, -5.001f);
		glNormal3f(0, 0, 1);
		glVertex3f(7.0f, 2.0f, -5.001f);
		glNormal3f(0, 0, 1);
		glVertex3f(7.0f, 0.0f, -5.001f);

		glEnd();
		if (second_light)
		{
			glDisable(GL_LIGHT2);
		}
	}

	if (!backDoor)
	{
		if (second_light)
		{
			glEnable(GL_LIGHT2);
		}
		glBegin(GL_QUADS);
		glColor4f(0.9f, 0.922f, 0.843f, 1.0f);

		glNormal3f(-1, 0, 0);
		glVertex3f(10.0f, 0.0f, -7.1f);
		glNormal3f(-1, 0, 0);
		glVertex3f(10.0f, 2.0f, -7.1f);
		glNormal3f(-1, 0, 0);
		glVertex3f(10.0f, 2.0f, -8.0f);
		glNormal3f(-1, 0, 0);
		glVertex3f(10.0f, 0.0f, -8.0f);

		glColor4f(0.3176f, 0.2118f, 0.102f, 1.0f);

		glNormal3f(-1, 0, 0);
		glVertex3f(10.0f, 2.0f, -7.1f);
		glNormal3f(-1, 0, 0);
		glVertex3f(10.0f, 0.0f, -7.1f);
		glNormal3f(-1, 0, 0);
		glVertex3f(10.0f, 0.0f, -7.0f);
		glNormal3f(-1, 0, 0);
		glVertex3f(10.0f, 2.0f, -7.0f);

		glEnd();
		if (second_light)
		{
			glDisable(GL_LIGHT2);
		}
		if (third_light)
		{
			glEnable(GL_LIGHT3);
		}
		glBegin(GL_QUADS);
		glColor4f(0.9f, 0.922f, 0.843f, 1.0f);

		glNormal3f(-1, 0, 0);
		glVertex3f(10.001f, 0.0f, -7.1f);
		glNormal3f(-1, 0, 0);
		glVertex3f(10.001f, 2.0f, -7.1f);
		glNormal3f(-1, 0, 0);
		glVertex3f(10.001f, 2.0f, -8.0f);
		glNormal3f(-1, 0, 0);
		glVertex3f(10.001f, 0.0f, -8.0f);

		glColor4f(0.3176f, 0.2118f, 0.102f, 1.0f);

		glNormal3f(-1, 0, 0);
		glVertex3f(10.001f, 2.0f, -7.1f);
		glNormal3f(-1, 0, 0);
		glVertex3f(10.001f, 0.0f, -7.1f);
		glNormal3f(-1, 0, 0);
		glVertex3f(10.001f, 0.0f, -7.0f);
		glNormal3f(-1, 0, 0);
		glVertex3f(10.001f, 2.0f, -7.0f);

		glEnd();
		if (third_light)
		{
			glDisable(GL_LIGHT3);
		}
	}
	else
	{
		if (second_light)
		{
			glEnable(GL_LIGHT2);
		}
		if (third_light)
		{
			glEnable(GL_LIGHT3);
		}
		glBegin(GL_QUADS);
		glColor4f(0.9f, 0.922f, 0.843f, 1.0f);

		glNormal3f(0, 0, -1);
		glVertex3f(10.0f, 0.0f, -8.0f);
		glNormal3f(0, 0, -1);
		glVertex3f(10.0f, 2.0f, -8.0f);
		glNormal3f(0, 0, -1);
		glVertex3f(10.9f, 2.0f, -8.0f);
		glNormal3f(0, 0, -1);
		glVertex3f(10.9f, 0.0f, -8.0f);

		glColor4f(0.3176f, 0.2118f, 0.102f, 1.0f);

		glNormal3f(0, 0, -1);
		glVertex3f(10.9f, 0.0f, -8.0f);
		glNormal3f(0, 0, -1);
		glVertex3f(10.9f, 2.0f, -8.0f);
		glNormal3f(0, 0, -1);
		glVertex3f(11.0f, 2.0f, -8.0f);
		glNormal3f(0, 0, -1);
		glVertex3f(11.0f, 0.0f, -8.0f);
		glEnd();
		if (second_light)
		{
			glDisable(GL_LIGHT2);
		}
		if (third_light)
		{
			glDisable(GL_LIGHT3);
		}
	}
}
void drawBackRoom(bool backDoor)
{
	if (!backDoor && sun_light)
	{
		glDisable(GL_LIGHT0);
	}
	if (third_light)
	{
		glEnable(GL_LIGHT3);
	}
	glBegin(GL_QUADS);

	glColor4f(0.4f, 0.4f, 0.4f, 1.0f);
	glNormal3f(0, 0, -1);
	glVertex3f(10.0f, 0.0f, -6.0f);
	glNormal3f(0, 0, -1);
	glVertex3f(10.0f, 3.0f, -6.0f);
	glNormal3f(0, 0, -1);
	glVertex3f(15.0f, 3.0f, -6.0f);
	glNormal3f(0, 0, -1);
	glVertex3f(15.0f, 0.0f, -6.0f);		//задняя

	glNormal3f(0, 0, 1);
	glVertex3f(10.0f, 3.0f, -9.0f);
	glNormal3f(0, 0, 1);
	glVertex3f(10.0f, 0.0f, -9.0f);
	glNormal3f(0, 0, 1);
	glVertex3f(15.0f, 0.0f, -9.0f);
	glNormal3f(0, 0, 1);
	glVertex3f(15.0f, 3.0f, -9.0f);		//передняя

	glColor4f(0.5f, 0.5f, 0.5f, 1.0f);

	glNormal3f(-1, 0, 0);
	glVertex3f(15.0f, 0.0f, -6.0f);
	glNormal3f(-1, 0, 0);
	glVertex3f(15.0f, 3.0f, -6.0f);
	glNormal3f(-1, 0, 0);
	glVertex3f(15.0f, 3.0f, -9.0f);
	glNormal3f(-1, 0, 0);
	glVertex3f(15.0f, 0.0f, -9.0f);		//правая

	glColor4f(0.3961f, 0.2627f, 0.1294f, 1.0f);

	glNormal3f(0, 1, 0);
	glVertex3f(10.0f, 0.0002f, -9.0f);
	glNormal3f(0, 1, 0);
	glVertex3f(10.0f, 0.0002f, -6.0f);
	glNormal3f(0, 1, 0);
	glVertex3f(15.0f, 0.0002f, -6.0f);
	glNormal3f(0, 1, 0);
	glVertex3f(15.0f, 0.0002f, -9.0f); // пол чулана

	glColor4f(0.9f, 0.9f, 0.9f, 1.0f);

	glNormal3f(0, -1, 0);
	glVertex3f(10.0f, 3.0f, -6.0f);
	glNormal3f(0, -1, 0);
	glVertex3f(10.0f, 3.0f, -9.0f);
	glNormal3f(0, -1, 0);
	glVertex3f(15.0f, 3.0f, -9.0f);
	glNormal3f(0, -1, 0);
	glVertex3f(15.0f, 3.0f, -6.0f);		//потолок

	glColor4f(0.5f, 0.5f, 0.5f, 1.0f);

	glNormal3f(-1, 0, 0);
	glVertex3f(10.001f, 0.0f, -7.0f);
	glNormal3f(-1, 0, 0);
	glVertex3f(10.001f, 0.0f, -6.0f);
	glNormal3f(-1, 0, 0);
	glVertex3f(10.001f, 3.0f, -6.0f);
	glNormal3f(-1, 0, 0);
	glVertex3f(10.001f, 3.0f, -7.0f);

	glNormal3f(-1, 0, 0);
	glVertex3f(10.001f, 2.0f, -8.0f);
	glNormal3f(-1, 0, 0);
	glVertex3f(10.001f, 2.0f, -7.0f);
	glNormal3f(-1, 0, 0);
	glVertex3f(10.001f, 3.0f, -7.0f);
	glNormal3f(-1, 0, 0);
	glVertex3f(10.001f, 3.0f, -8.0f);

	glNormal3f(1, 0, 0);
	glVertex3f(10.0f, 0.0f, -8.0f);
	glNormal3f(1, 0, 0);
	glVertex3f(10.0f, 3.0f, -8.0f);
	glNormal3f(1, 0, 0);
	glVertex3f(10.0f, 3.0f, -10.0f);
	glNormal3f(1, 0, 0);
	glVertex3f(10.0f, 0.0f, -10.0f); // правая стенка второй комнаты

	glNormal3f(-1, 0, 0);
	glVertex3f(10.001f, 0.0f, -8.0f);
	glNormal3f(-1, 0, 0);
	glVertex3f(10.001f, 3.0f, -8.0f);
	glNormal3f(-1, 0, 0);
	glVertex3f(10.001f, 3.0f, -9.0f);
	glNormal3f(-1, 0, 0);
	glVertex3f(10.001f, 0.0f, -9.0f);

	//внешние для корректного солнечного света


	glEnd();

	if (third_light)
	{
		glDisable(GL_LIGHT3);
	}
	if (!backDoor && sun_light)
	{
		glEnable(GL_LIGHT0);
	}

	glBegin(GL_QUADS);

	glColor4f(0.4f, 0.4f, 0.4f, 1.0f);
	glNormal3f(0, 0, -1);
	glVertex3f(10.0f, 0.0f, -5.999f);
	glNormal3f(0, 0, -1);
	glVertex3f(10.0f, 3.001f, -5.999f);
	glNormal3f(0, 0, -1);
	glVertex3f(15.001f, 3.001f, -5.999f);
	glNormal3f(0, 0, -1);
	glVertex3f(15.001f, 0.0f, -5.999f);

	glNormal3f(0, 0, 1);
	glVertex3f(10.0f, 3.001f, -9.001f);
	glNormal3f(0, 0, 1);
	glVertex3f(10.0f, 0.0f, -9.001f);
	glNormal3f(0, 0, 1);
	glVertex3f(15.0f, 0.0f, -9.001f);
	glNormal3f(0, 0, 1);
	glVertex3f(15.0f, 3.001f, -9.001f);

	glColor4f(0.9f, 0.9f, 0.9f, 1.0f);

	glNormal3f(0, -1, 0);
	glVertex3f(10.0f, 3.001f, -5.999f);
	glNormal3f(0, -1, 0);
	glVertex3f(10.0f, 3.001f, -9.001f);
	glNormal3f(0, -1, 0);
	glVertex3f(15.001f, 3.001f, -9.001f);
	glNormal3f(0, -1, 0);
	glVertex3f(15.001f, 3.001f, -5.999f);

	glColor4f(0.5f, 0.5f, 0.5f, 1.0f);

	glNormal3f(-1, 0, 0);
	glVertex3f(15.001f, 0.0f, -5.999f);
	glNormal3f(-1, 0, 0);
	glVertex3f(15.001f, 3.001f, -5.999f);
	glNormal3f(-1, 0, 0);
	glVertex3f(15.001f, 3.001f, -9.001f);
	glNormal3f(-1, 0, 0);
	glVertex3f(15.001f, 0.0f, -9.001f);

	glEnd();

}
void drawWindows()
{
	GLfloat no_em[] = { 0.0f, 0.0f, 0.0f, 0.00f };
	glMaterialfv(GL_FRONT, GL_EMISSION, no_em);
	if (first_light)
	{
		glEnable(GL_LIGHT1);
	}
	glBegin(GL_QUADS);
	glColor4f(1.0f, 1.0f, 1.0f, 0.5f);

	glNormal3f(1, 0, 0);
	glVertex3f(0.0f, 0.5f, -2.0f);
	glNormal3f(1, 0, 0);
	glVertex3f(0.0f, 2.5f, -2.0f);
	glNormal3f(1, 0, 0);
	glVertex3f(0.0f, 2.5f, -3.0f);
	glNormal3f(1, 0, 0);
	glVertex3f(0.0f, 0.5f, -3.0f);	// окно первой комнаты
	glEnd();
	if (first_light)
	{
		glDisable(GL_LIGHT1);
	}
	if (second_light)
	{
		glEnable(GL_LIGHT2);
	}
	glBegin(GL_QUADS);
	glNormal3f(1, 0, 0);
	glVertex3f(5.0f, 0.5f, -7.0f);
	glNormal3f(1, 0, 0);
	glVertex3f(5.0f, 2.5f, -7.0f);
	glNormal3f(1, 0, 0);
	glVertex3f(5.0f, 2.5f, -8.0f);
	glNormal3f(1, 0, 0);
	glVertex3f(5.0f, 0.5f, -8.0f);	// окно второй комнаты
	glEnd();
	if (second_light)
	{
		glDisable(GL_LIGHT2);
	}

}
void drawTeapots(bool backDoor)
{
	if (!backDoor)
	{
		glDisable(GL_LIGHT0);
	}
	if (third_light)
	{
		glEnable(GL_LIGHT3);
	}
	glColor4f(0.6549f, 0.2392f, 0.7373f, 1.0f);

	glPushMatrix();
	glTranslated(11.75f, 1.06f, -6.35f);
	glutSolidTeapot(0.1f);
	glPopMatrix();

	glColor4f(0.80f, 0.6078f, 0.3882f, 1.0f);

	glPushMatrix();
	glTranslated(13.25f, 1.56f, -6.35f);
	glutSolidTeapot(0.1f);
	glPopMatrix();

	glColor4f(0.5922f, 0.6627f, 0.8667f, 1.0f);

	glPushMatrix();
	glTranslated(13.25f, 0.56f, -6.35f);
	glutSolidTeapot(0.1f);
	glPopMatrix();
	if (third_light)
	{
		glDisable(GL_LIGHT3);
	}
	if (!backDoor)
	{
		glEnable(GL_LIGHT0);
	}
	GLfloat no_em[] = { 0.0f, 0.0f, 0.0f, 0.00f };

	GLfloat em1[] = {0.8f, 0.0f, 0.0f, 0.2f};
	if (first_light)
	{
		glMaterialfv(GL_FRONT, GL_EMISSION, em1);
	}
	else
	{
		glMaterialfv(GL_FRONT, GL_EMISSION, no_em);
		glColor4f(0.3f, 0.0f, 0.0f, 1.0f);
	}
	glPushMatrix();
	glTranslated(5.0f, 2.5f, -2.5f);
	glutSolidSphere(0.1f, 100, 100);
	glPopMatrix();

	GLfloat em2[] = { 0.0f, 0.8f, 0.0f, 0.2f };
	if (second_light)
	{
		glMaterialfv(GL_FRONT, GL_EMISSION, em2);
	}
	else
	{
		glMaterialfv(GL_FRONT, GL_EMISSION, no_em);
		glColor4f(0.0f, 0.3f, 0.0f, 1.0f);
	}

	glPushMatrix();
	glTranslated(7.5f, 2.5f, -7.5f);
	glutSolidSphere(0.1f, 100, 100);
	glPopMatrix();

	GLfloat em3[] = { 0.0f, 0.0f, 0.8f, 0.2f };
	if (third_light)
	{
		glMaterialfv(GL_FRONT, GL_EMISSION, em3);
	}
	else
	{
		glMaterialfv(GL_FRONT, GL_EMISSION, no_em);
		glColor4f(0.0f, 0.0f, 0.3f, 1.0f);
	}
	if (!backDoor)
	{
		glDisable(GL_LIGHT0);
	}
	glPushMatrix();
	glTranslated(12.5f, 2.8f, -7.5f);
	glutSolidSphere(0.1f, 100, 100);
	glPopMatrix();
	if (!backDoor)
	{
		glEnable(GL_LIGHT0);
	}
	GLfloat em0[] = { 1.0f, 1.0f, 1.0f, 0.5f };
	GLfloat em0_off[] = { 0.0f, 0.0f, 0.0f, 0.5f };
	if (sun_light)
	{
		glMaterialfv(GL_FRONT, GL_EMISSION, em0);
	}
	else
	{
		glMaterialfv(GL_FRONT, GL_EMISSION, em0_off);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	}

	glPushMatrix();
	glTranslated(-90.0f, 20.0f, 0.0f);
	glutSolidSphere(5.0f, 100, 100);
	glPopMatrix();

	
	glMaterialfv(GL_FRONT, GL_EMISSION, no_em);

	GLUquadricObj* quadratic1;
	quadratic1 = gluNewQuadric();

	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);

	glPushMatrix();
	glTranslated(5.0f, 2.5f, -2.5f);
	glRotated(-90, 1.0f, 0.0f, 0.0f);

	gluCylinder(quadratic1, 0.01f, 0.01f, 0.5f, 32, 32);
	
	glPopMatrix();

	GLUquadricObj* quadratic2;
	quadratic2 = gluNewQuadric();

	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);

	glPushMatrix();
	glTranslated(7.5f, 2.5f, -7.5f);
	glRotated(-90, 1.0f, 0.0f, 0.0f);

	gluCylinder(quadratic2, 0.01f, 0.01f, 0.5f, 32, 32);

	glPopMatrix();

	GLUquadricObj* quadratic3;
	quadratic3 = gluNewQuadric();

	glColor4f(0.0f, 0.0f, 0.0f, 1.0f);

	glPushMatrix();
	glTranslated(12.5f, 2.8f, -7.5f);
	glRotated(-90, 1.0f, 0.0f, 0.0f);

	gluCylinder(quadratic3, 0.01f, 0.01f, 0.2f, 32, 32);

	glPopMatrix();
}
void drawScene(bool outDoor, bool inDoor, bool backDoor) 
{
	drawFirstRoom();
	drawDivan();
	drawTVSet();
	drawSecondRoom();
	drawBed();
	drawDoors(outDoor, inDoor, backDoor);

	drawBackRoom(backDoor);
	drawCloset(backDoor);
	
	drawTeapots(backDoor);
	drawWindows();
}
void changeSize(int w, int h) 
{
	mid_x = w >> 1;
	mid_y = h >> 1;
	glutWarpPointer(mid_x, mid_y);
	// предотвращение деления на ноль
	if (h == 0)
		h = 1;
	float ratio = w * 1.0 / h;
	// используем матрицу проекции
	glMatrixMode(GL_PROJECTION);
	// обнуляем матрицу
	glLoadIdentity();
	// установить параметры вьюпорта
	glViewport(0, 0, w, h);
	// установить корректную перспективу
	gluPerspective(fov, ratio, 0.1f, 100.0f);
	// вернуться к матрице проекции
	glMatrixMode(GL_MODELVIEW);
}
void renderScene(void) 
{
	if (sun_light)
	{
		glClearColor(0.5294f, 0.8078f, 0.9216f, 1.0f);
	}
	else
	{
		glClearColor(0.145f, 0.157f, 0.314f, 1.0f);
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	gluLookAt(x, y, z,
		x + lx, y + ly, z + lz,
		0.0f, y, 0.0f);

	GLfloat light0_diffuse[] = {0.7f, 0.7f, 0.7f};
	GLfloat light0_position[] = {-90.0f, 20.0f, 0.0f, 1.0f};
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

	GLfloat light1_diffuse[] = {0.9f, 0.0f, 0.0f};
	GLfloat light1_position[] = {5.0f, 2.8f, -2.5f, 1.0f};

	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0f);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.0f);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.0f);


	GLfloat light2_diffuse[] = {0.0f, 0.7f, 0.0f};
	GLfloat light2_position[] = {7.5f, 2.5f, -7.5f, 1.0f};

	glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
	glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
	glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 1.5f);
	glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.0f);
	glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.0f);

	GLfloat light3_diffuse[] = {0.0f, 0.0f, 0.9f};
	GLfloat light3_position[] = {12.5f, 2.8f, -7.5f, 1.0f};

	glLightfv(GL_LIGHT3, GL_DIFFUSE, light3_diffuse);
	glLightfv(GL_LIGHT3, GL_POSITION, light3_position);
	glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 0.0f);
	glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, 0.01f);
	glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, 0.1f);

	if (sun_light)
	{
		glEnable(GL_LIGHT0);
	}
	else
	{
		glDisable(GL_LIGHT0);
	}

	glColor4f(0.0431f, 0.8549f, 0.3176f, 1.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glBegin(GL_QUADS);
	glVertex3f(-100.0f, 0.0f, -100.0f);
	glVertex3f(-100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, -100.0f);
	glEnd();

	drawScene(out, in, back);
	
	glutSwapBuffers();
}
void processNormalKeys(unsigned char key, int xx, int yy) 
{
	if (key == 27)
		exit(0);
	if (key == 'e')
	{
		float distanceOut = sqrt(abs((x - 10.0) * (x - 10.0) + (z + 2.5) * (z + 2.5)));
		float distanceIn = sqrt(abs((x - 7.0) * (x - 7.0) + (z + 5.0) * (z + 5.0)));
		float distanceBack = sqrt(abs((x - 10.0) * (x - 10.0) + (z + 7.5) * (z + 7.5)));
		if (distanceOut <= 2.5)
			out ? out = false : out = true;
		if (distanceIn <= 2.5)
			in ? in = false : in = true;
		if (distanceBack <= 2.5)
			back ? back = false : back = true;
	}
	if (key == ' ' && !crouch)
	{
		if (y - 1.0f < 0.01f)
		{
			jump = true;
			jumpVelocity -= jumpAcceleration;
			jumpTime++;
			y += (jumpVelocity * jumpTime / 10.0 + ((jumpAcceleration * jumpTime / 10.0 * jumpTime / 10.0) / 2.0));
		}
	}
	if (key == 45 || key == 'x')
	{
		minusPressed = true;
	}
	if (key == 43 || key == 'c')
	{
		plusPressed = true;
	}
	if (key == 'w')
	{
		wPressed = true;
	}
	if (key == 'a')
	{
		aPressed = true;
	}
	if (key == 's')
	{
		sPressed = true;
	}
	if (key == 'd')
	{
		dPressed = true;
	}
	if (key == 'z' && !crouch && !jump)
	{
		y -= 0.3f;
		crouch = true;
		title_m;
		glutSetWindowTitle(title.c_str());
	}
	if (key == '1')
	{
		first_light ? first_light = false : first_light = true;
		title_m;
		glutSetWindowTitle(title.c_str());
	}
	if (key == '2')
	{
		second_light ? second_light = false : second_light = true;
		title_m;
		glutSetWindowTitle(title.c_str());
	}
	if (key == '3')
	{
		third_light ? third_light = false : third_light = true;
		title_m;
		glutSetWindowTitle(title.c_str());
	}
	if (key == '4')
	{
		sun_light ? sun_light = false : sun_light = true;
		title_m;
		glutSetWindowTitle(title.c_str());
	}
	if (key == '5')
	{
		tv ? tv = false : tv = true;
		title_m;
		glutSetWindowTitle(title.c_str());
	}
}
void processUpNormalKeys(unsigned char key, int xx, int yy) 
{
	if (key == 45 || key == 'x')
	{
		minusPressed = false;
	}
	if (key == 43 || key == 'c')
	{
		plusPressed = false;
	}
	if (key == 'w')
	{
		wPressed = false;
	}
	if (key == 'a')
	{
		aPressed = false;
	}
	if (key == 's')
	{
		sPressed = false;
	}
	if (key == 'd')
	{
		dPressed = false;
	}
	if (key == 'z' && crouch && !jump)
	{	
		y += 0.3f;
		crouch = false;
		title_m;
		glutSetWindowTitle(title.c_str());
	}
}
void idleNormalKeys()
{
	//sleep_for(100ms);
	float fraction = 0.07f;
	float aux_lx;
	float aux_lz;
	if (wPressed)
	{
		x += lx * fraction;
		z += lz * fraction;
		title_m;
		glutSetWindowTitle(title.c_str());
	}
	if (aPressed)
	{
		aux_lx = sin(angle - 1.570796f);
		aux_lz = -cos(angle - 1.570796f);
		x += aux_lx * fraction;
		z += aux_lz * fraction;
		title_m;
		glutSetWindowTitle(title.c_str());
	}
	if (sPressed)
	{
		x -= lx * fraction;
		z -= lz * fraction;
		title_m;
		glutSetWindowTitle(title.c_str());
	}
	if (dPressed)
	{
		aux_lx = sin(angle + 1.570796f);
		aux_lz = -cos(angle + 1.570796f);
		x += aux_lx * fraction;
		z += aux_lz * fraction;
		title_m;
		glutSetWindowTitle(title.c_str());
	}
	if (minusPressed)
	{
		y -= 0.1f;
		title_m;
		glutSetWindowTitle(title.c_str());
	}
	if (plusPressed)
	{
		y += 0.1f;
		title_m;
		glutSetWindowTitle(title.c_str());
	}
	if (jump && !crouch)
	{
		float new_y = y + (jumpVelocity * jumpTime / 10.0 + ((jumpAcceleration * jumpTime / 10.0 * jumpTime / 10.0) / 2.0));
		if (new_y < 1.0f)
		{
			jumpVelocity = 0.3f;
			jumpTime = 0;
			jump = false;
			y = 1.0f;
		}
		else
		{
			y = new_y;
			jumpVelocity -= jumpAcceleration;
			jumpTime++;
		}
		title_m;
		glutSetWindowTitle(title.c_str());
	}
	renderScene();
}
void processMouse(int xx, int yy)
{
	if (xx == mid_x && yy == mid_y)
		return;
	angle -= (mid_x - xx) / 2000.0;
	if (angle > 6.283185307f)
	{
		angle -= 6.283185307f;
	}
	if (angle < -6.283185307f)
	{
		angle += 6.283185307f;
	}
	lx = sin(angle);
	lz = -cos(angle);
	ly += (mid_y - yy) / 2000.0;
	glutWarpPointer(mid_x, mid_y);
	title_m; 
	glutSetWindowTitle(title.c_str());
}
void processMouseClick(int button, int dir, int xx, int yy)
{
	if (dir == GLUT_UP) return;

	if (button == 0)
	{
		fov += 1.0f;
	}
	if (button == 2)
	{
		fov -= 1.0f;
	}
	title_m;
	glutSetWindowTitle(title.c_str());
	changeSize(1280, 720);
	return;
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1280, 720);
	glutCreateWindow(title.c_str());
	glutSetCursor(GLUT_CURSOR_NONE);

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutKeyboardFunc(processNormalKeys);
	glutKeyboardUpFunc(processUpNormalKeys);
	glutPassiveMotionFunc(processMouse);
	glutIdleFunc(idleNormalKeys);
	glutMouseFunc(processMouseClick);

	glutMainLoop();

	return 0;
}