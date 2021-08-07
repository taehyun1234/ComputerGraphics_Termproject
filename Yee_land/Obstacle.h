#pragma once
#include "Texture.h"
#include "collide.h"
#include <time.h>
#ifndef Obstacle
#define TREENUM 20
struct Point
{
	double x, y, z;
};

Point p[TREENUM]; // 장애물은 총 20개

class Obstacle : Texture
{
private:
	GLubyte *pBytes; // 데이터를 가리킬 포인터
	BITMAPINFO *info; // 비트맵 헤더 저장할 변수
	GLuint ob_textures[3];
public:
	int r;// 정사각형 충돌체크
	void Obstacle_enter()
	{
		r = 50;
		time(unsigned(NULL));
		p[0].x = 3187;
		p[0].y = 0;
		p[0].z = 2509;

		p[1].x = 2461;
		p[1].y = 0;
		p[1].z = -2474;

		p[2].x = 2403;
		p[2].y = 0;
		p[2].z = 4528;

		p[3].x = -50;
		p[3].y = 0;
		p[3].z = 3398;

		p[4].x = -2252;
		p[4].y = 0;
		p[4].z = -2825;

		p[5].x = -4426;
		p[5].y = 0;
		p[5].z = -2219;

		p[6].x = 247;
		p[6].y = 0;
		p[6].z = 4691;

		p[7].x = 247;
		p[7].y = 0;
		p[7].z = 4691;

		p[8].x = 4726;
		p[8].y = 0;
		p[8].z = 4668;

		p[9].x = 204;
		p[9].y = 0;
		p[9].z = -3694;

		p[10].x = -143;
		p[10].y = 0;
		p[10].z = -2704;

		p[11].x = -4536;
		p[11].y = 0;
		p[11].z = 4981;

		p[12].x = -2892;
		p[12].y = 0;
		p[12].z = -4205;

		p[13].x = -841;
		p[13].y = 0;
		p[13].z = -4375;

		p[14].x = -3263;
		p[14].y = 0;
		p[14].z = 821;

		p[15].x = 3523;
		p[15].y = 0;
		p[15].z = 1547;

		p[16].x = 1420;
		p[16].y = 0;
		p[16].z = -4050;

		p[17].x = -1035;
		p[17].y = 0;
		p[17].z = -3451;

		p[18].x = -3510;
		p[18].y = 0;
		p[18].z = -1055;

		p[19].x = 1148;
		p[19].y = 0;
		p[19].z = -196;

		initTextures();
	}
	void Draw_Tree_set()
	{
		for (int i = 0; i < 20; i++)
		{
			Draw_Tree(p[i].x - 25, p[i].y, p[i].z - 25);
			if (OnOff_collide_box)	Draw_collide_rect(p[i].x, p[i].y, p[i].z, 200, 30, 30);
		}
	}



	void Draw_Tree(double x, double y, double z)
	{
		glColor3f(1, 1, 1);
		glEnable(GL_TEXTURE_2D);
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
		glPushMatrix();
		glTranslatef(x, y, z);
		glScalef(1, 5, 1);
		{
			glBindTexture(GL_TEXTURE_2D, ob_textures[0]);
			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex3f(0, 0, 0);
			glTexCoord2f(1, 0);
			glVertex3f(50, 0, 0);
			glTexCoord2f(1, 1);
			glVertex3f(50, 0, 50);
			glTexCoord2f(0, 1);
			glVertex3f(0, 0, 50);
			glEnd();

			glBindTexture(GL_TEXTURE_2D, ob_textures[0]);
			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex3f(0, 50, 0);
			glTexCoord2f(1, 0);
			glVertex3f(50, 50, 0);
			glTexCoord2f(1, 1);
			glVertex3f(50, 50, 50);
			glTexCoord2f(0, 1);
			glVertex3f(0, 50, 50);
			glEnd();

			glBindTexture(GL_TEXTURE_2D, ob_textures[0]);
			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex3f(0, 0, 0);
			glTexCoord2f(1, 0);
			glVertex3f(0, 50, 0);
			glTexCoord2f(1, 1);
			glVertex3f(50, 50, 0);
			glTexCoord2f(0, 1);
			glVertex3f(50, 0, 0);
			glEnd();

			glBindTexture(GL_TEXTURE_2D, ob_textures[0]);
			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex3f(0, 0, 50);
			glTexCoord2f(1, 0);
			glVertex3f(0, 50, 50);
			glTexCoord2f(1, 1);
			glVertex3f(50, 50, 50);
			glTexCoord2f(0, 1);
			glVertex3f(50, 0, 50);
			glEnd();

			glBindTexture(GL_TEXTURE_2D, ob_textures[0]);
			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex3f(0, 0, 0);
			glTexCoord2f(1, 0);
			glVertex3f(0, 50, 0);
			glTexCoord2f(1, 1);
			glVertex3f(0, 50, 50);
			glTexCoord2f(0, 1);
			glVertex3f(0, 0, 50);
			glEnd();

			glBindTexture(GL_TEXTURE_2D, ob_textures[0]);
			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex3f(50, 0, 0);
			glTexCoord2f(1, 0);
			glVertex3f(50, 50, 0);
			glTexCoord2f(1, 1);
			glVertex3f(50, 50, 50);
			glTexCoord2f(0, 1);
			glVertex3f(50, 0, 50);
			glEnd();
		}
		glPopMatrix();


		glPushMatrix();
		glTranslatef(x-50, y+250, z-50);
		glScalef(3, 3, 3);
		{
			glBindTexture(GL_TEXTURE_2D, ob_textures[1]);
			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex3f(0, 0, 0);
			glTexCoord2f(1, 0);
			glVertex3f(50, 0, 0);
			glTexCoord2f(1, 1);
			glVertex3f(50, 0, 50);
			glTexCoord2f(0, 1);
			glVertex3f(0, 0, 50);
			glEnd();

			glBindTexture(GL_TEXTURE_2D, ob_textures[1]);
			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex3f(0, 50, 0);
			glTexCoord2f(1, 0);
			glVertex3f(50, 50, 0);
			glTexCoord2f(1, 1);
			glVertex3f(50, 50, 50);
			glTexCoord2f(0, 1);
			glVertex3f(0, 50, 50);
			glEnd();

			glBindTexture(GL_TEXTURE_2D, ob_textures[1]);
			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex3f(0, 0, 0);
			glTexCoord2f(1, 0);
			glVertex3f(0, 50, 0);
			glTexCoord2f(1, 1);
			glVertex3f(50, 50, 0);
			glTexCoord2f(0, 1);
			glVertex3f(50, 0, 0);
			glEnd();

			glBindTexture(GL_TEXTURE_2D, ob_textures[1]);
			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex3f(0, 0, 50);
			glTexCoord2f(1, 0);
			glVertex3f(0, 50, 50);
			glTexCoord2f(1, 1);
			glVertex3f(50, 50, 50);
			glTexCoord2f(0, 1);
			glVertex3f(50, 0, 50);
			glEnd();

			glBindTexture(GL_TEXTURE_2D, ob_textures[1]);
			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex3f(0, 0, 0);
			glTexCoord2f(1, 0);
			glVertex3f(0, 50, 0);
			glTexCoord2f(1, 1);
			glVertex3f(0, 50, 50);
			glTexCoord2f(0, 1);
			glVertex3f(0, 0, 50);
			glEnd();

			glBindTexture(GL_TEXTURE_2D, ob_textures[1]);
			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex3f(50, 0, 0);
			glTexCoord2f(1, 0);
			glVertex3f(50, 50, 0);
			glTexCoord2f(1, 1);
			glVertex3f(50, 50, 50);
			glTexCoord2f(0, 1);
			glVertex3f(50, 0, 50);
			glEnd();
		}
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	}
	void initTextures()
	{
		glGenTextures(3, ob_textures); //텍스처 이름을 생성한다. n:생성되어야할 텍스처이름의 수 

		glBindTexture(GL_TEXTURE_2D, ob_textures[0]); // 텍스처링 할 객체에 텍스처를 연결해준다.
		pBytes = LoadDIBitmap("Tree_Under.bmp", &info);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

		glBindTexture(GL_TEXTURE_2D, ob_textures[1]); // 텍스처링 할 객체에 텍스처를 연결해준다.
		pBytes = LoadDIBitmap("Tree_Up.bmp", &info);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	}
};

#endif // !Obstacle
