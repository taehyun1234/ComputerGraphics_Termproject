#pragma once
#include<glut.h>
#include <gl\GL.h>
#include <stdio.h>
#include <math.h>
#include <time.h>


#define DIVIDE 20
bool Thunder_OF = true;
int thun_num = 0;
int any_num = 0;

struct Dot_t {
	double x, y, z;
};

struct Thunderbolt {


	double x, y, z, ex, ey, ez;
	bool match = false;
	int loop_num;
	Dot_t Divide_dot[DIVIDE + 1];//새로 나눌 점들

	void Effect_Thunderbolt_Update(double x, double y, double z, double ex, double ey, double ez)
	{
		double len_x = (ex - x) / DIVIDE;
		double len_y = (ey - y) / DIVIDE;
		double len_z = (ez - z) / DIVIDE;//점과 점사이를 등분한 거리 

		for (int i = 0; i < DIVIDE; i++)
		{
			if (i % 2 == 0 && loop_num % 2 == 0) {
				Divide_dot[i].y = i*len_y + rand() % 20;
			}
			else if (i % 2 == 0 && loop_num % 2 == 1)
			{
				Divide_dot[i].y = i*len_y - rand() % 20;
			}
			else if (i % 2 == 1 && loop_num % 2 == 0)
				Divide_dot[i].y = i*len_y - rand() % 20;
			else
				Divide_dot[i].y = i*len_y + rand() % 20;
			Divide_dot[i].x = i*len_x + rand() % 40 - 20;
			Divide_dot[i].z = i*len_z + rand() % 40 - 20;
		}
		Divide_dot[0].x = x;
		Divide_dot[0].y = y;
		Divide_dot[0].z = z;

		loop_num++;
		any_num++;
		if (any_num > 50)
			match = false;

	}

	void Effect_Thunderbolt_Draw()
	{

		glLineWidth(2);
		glPointSize(3);
		if (loop_num % 2 == 0)
			glColor3f(0.2, 0.2, 0.8);
		else
			glColor3f(1.0, 1.0, 1.0);
		glPushMatrix();
		glTranslated(Divide_dot[0].x, Divide_dot[0].y, Divide_dot[0].z);

		glBegin(GL_LINE_STRIP);
		for (int i = 1; i < DIVIDE; i++)
			glVertex3f(Divide_dot[i].x, Divide_dot[i].y, Divide_dot[i].z);
		glEnd();
		glPopMatrix();



		if (loop_num % 2 == 1)
			glColor3f(1, 1.0, 0);
		else
			glColor3f(0.2, 0.2, 0.8);
		glPushMatrix();
		glTranslated(Divide_dot[0].x, Divide_dot[0].y, Divide_dot[0].z);

		glBegin(GL_LINE_STRIP);
		for (int i = 1; i < DIVIDE; i++)
			glVertex3f(Divide_dot[i].x + (rand() % 10 - 5), Divide_dot[i].y + (rand() % 10 - 5), Divide_dot[i].z + (rand() % 10 - 5));
		glEnd();
		glPopMatrix();


		glPushMatrix();
		glTranslated(Divide_dot[0].x, Divide_dot[0].y + 350, Divide_dot[0].z);

		glutWireSphere(20, 10, 10);
		glPopMatrix();
	}

};

Thunderbolt thunder[4];

void Thunder_update()
{
	for (int i = 0; i < 4; i++)
	{
		thunder[i].Effect_Thunderbolt_Update(thunder[i].x, thunder[i].y, thunder[i].z, thunder[i].ex, thunder[i].ey, thunder[i].ez);
	}
}

void Thunder_Draw()
{
	for (int i = 0; i < 4; i++)
	{
		if (thunder[i].match)
			thunder[i].Effect_Thunderbolt_Draw();
	}
}