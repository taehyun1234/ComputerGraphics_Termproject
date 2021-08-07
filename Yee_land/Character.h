#pragma once
#include "OBJModel.h"
#include <gl\GL.h>
#include <stdio.h>
#include "Texture.h"
#define C_UP 10
#define C_DOWN 40
#define C_RIGHT 20
#define C_LEFT 30
#define IDLE 50

OBJModel *hat;
OBJModel *clothe1;
OBJModel *clothe2;
OBJModel *clothe3;
OBJModel *rh;
OBJModel *lh;
bool walk = false;
int walk_angle = 0;
int walk_dir = 1;


void ImportTextures()
{
	clothe1 = new OBJModel("clothe1.obj");
	clothe2 = new OBJModel("clothe2.obj");
	clothe3 = new OBJModel("clothe3.obj");
	hat = new OBJModel("hat.obj");
	rh = new OBJModel("righthand.obj");
	lh = new OBJModel("lefthand.obj");
}
struct Bomb
{
	double x, y, z;
	bool isTrue;
	bool explode;
	int size;
	int timer;
	Bomb() {
		size = 0;
	}
};
#ifndef Character
class Character : Texture
{
private:

public:
	GLubyte *pBytes; // 데이터를 가리킬 포인터
	BITMAPINFO *info; // 비트맵 헤더 저장할 변수
	GLuint textures[1];
	double c_x, c_y, c_z;
	int timer;
	bool jump;
	int jump_num; //점프상수
	Bomb bm;
	int hp, mp;
	Character()
	{
		bm.isTrue = false;
		jump = false;
		hp = 200;
		mp = 200;
		jump_num = 0;
		c_x = 0, c_y = 100, c_z = 100; // 캐릭터의 처음 좌표 : 0,40,100
	}
	void init()
	{
		bm.isTrue = false;
		jump = false;
		hp = 200;
		mp = 200;
		jump_num = 0;
		c_x = 0, c_y = 100, c_z = 100; // 캐릭터의 처음 좌표 : 0,40,100
	}
	void Recovery_HP()
	{
		if (hp>150)
		{
			hp = 200;
		}
		else {
			hp += 50;
		}
	}
	void Recovery_MP()
	{
		if (mp>150)
		{
			mp = 200;
		}
		else {
			mp += 50;
		}
	}
	void set_bomb_True() // 폭탄을 설정해준다.
	{
		if (bm.isTrue == false && bm.explode == false) {
			bm.isTrue = true;
			bm.timer = 0;
			bm.x = c_x;
			bm.y = c_y;
			bm.z = c_z;
		}
	}
	void set_Char_coordinate(double x, double y, double z)
	{
		c_x = x;
		c_y = y;
		c_z = z;
	}
	void babo_coordinate()
	{
		c_x -= 10;
		c_z -= 10;
	}
	double get_cx()
	{
		return c_x;
	}
	double get_cy()
	{
		return c_y;
	}
	double get_cz()
	{
		return c_z;
	}

	void Update(double rotateY, double rotateX)
	{
		if (hp < 0)
		{
			GAME_OVER = true;
		}

		if (bm.isTrue == true)
		{
			bm.timer++;
			if (bm.timer < 10)
			{
				bm.y += 30;
				bm.x += 30 * sin((rotateY)* 3.141592 / 180) * sin((rotateX)* 3.141592 / 180) * 2;
				bm.z += 30 * sin((rotateY)* 3.141592 / 180) * cos((rotateX)* 3.141592 / 180) * 2;
			}
			else if (bm.timer >= 10 && bm.timer < 20)
			{
				bm.y -= 30;
				bm.x += 30 * sin((rotateY)* 3.141592 / 180) * sin((rotateX)* 3.141592 / 180) * 2;
				bm.z += 30 * sin((rotateY)* 3.141592 / 180) * cos((rotateX)* 3.141592 / 180) * 2;
			}
			else
			{
				bm.explode = true;
				bm.isTrue = false;
				bm.timer = 0;
			}
		}
		if (bm.explode == true)
		{
			bm.timer++;
			if (bm.timer < 10)
			{
				bm.size++;
			}
			else if (bm.timer >= 10 && bm.timer < 20)
			{
				bm.size--;
			}
			else
			{
				bm.size = 0;
				bm.explode = false;
			}
		}

		if (jump == true)
		{
			c_y += jump_num;
			jump_num -= 3;
			if (c_y < 100)
			{
				c_y = 100;
				jump = false;
			}
		}
	}

	void Jump()
	{
		jump = true;
		jump_num = 20;
	}
	void Move_Left(double xrotate, double speed)
	{
		c_x -= speed * cos((-xrotate) * 3.141592 / 180);
		c_z -= speed * sin((-xrotate) * 3.141592 / 180);
	}
	void Move_Right(double xrotate, double speed)
	{
		c_x += speed * cos((-xrotate) * 3.141592 / 180);
		c_z += speed * sin((-xrotate) * 3.141592 / 180);
	}
	void Move_Up(double xrotate, double speed)
	{
		c_x += speed * cos((-xrotate - 90) * 3.141592 / 180);
		c_z += speed * sin((-xrotate - 90) * 3.141592 / 180);
	}
	void Move_Down(double xrotate, double speed)
	{
		c_x -= speed  * cos((-xrotate - 90) * 3.141592 / 180);
		c_z -= speed  * sin((-xrotate - 90) * 3.141592 / 180);
	}

	void Change_Coordinate(double x, double y, double z)
	{
		c_x += x;
		c_y += y;
		c_z += z;
	}
	void Draw(double camxrotate, double camyrotate)
	{
	
		glEnable(GL_NORMALIZE);
		{
			glPushMatrix(); //로봇 전체적용
			glTranslatef(c_x, c_y+10, c_z);
			glRotatef(camxrotate + 180, 0, 1, 0);
			if (GAME_OVER) {
				glTranslated(0, -70, 0);
				glRotated(90, 0, 0, 1);
			}
			glPushMatrix();//모자, 옷1,2,3
			{
				glTranslated(0, walk_angle/5 , 0);
				glPushMatrix();
					glScaled(1.5, 1.5, 1.5);
					glColor3d(0.3, 0.1, 0.05);
					hat->Draw(0);
					glColor3d(0.3, 0.1, 0.05);
					clothe1->Draw(0);
					glColor3d(0.3, 0.2, 0.2);
					clothe2->Draw(0);
					glColor3d(0.3, 0.2, 0.1);
					clothe3->Draw(0);
				glPopMatrix();
			}
			glPopMatrix();

			glPushMatrix();//오른쪽손
			{
				
				
				glTranslated(0, 40, 0);
				glRotated(walk_angle, 1, 0, 0);
				glTranslated(0, -40, 0);
				glScaled(1.5, 1.5, 1.5);
				glColor3d(1, 0.7, 0.3);
				rh->Draw(0);

			}glPopMatrix();

			glPushMatrix();//왼쪽손
			{
				glTranslated(0, 40, 0);
				glRotated(-walk_angle, 1, 0, 0);
				//glRotated(-120, 1, 0, 0);
				glTranslated(0, -40, 0);

				glScaled(1.5, 1.5, 1.5);
				glColor3d(1, 0.7, 0.3);
				lh->Draw(0);

			}
			glPopMatrix();
			glPushMatrix();//지팡이전체
			{	glTranslated(0, 40, 0);
				glRotated(-walk_angle, 1, 0, 0);
				//glRotated(-120, 1, 0, 0);
				glTranslated(0, -40, 0);


				glPushMatrix();
				glTranslated(2, -12, -7);
				glRotated(-15, 0, 0, 1);
				glPushMatrix();//마법막대기
				{

					glColor3d(0.2, 0.1, 0.05);
					glTranslated(-50, 15, 25);
					glRotated(35, 1, 0, 0);
					glRotated(20, 0, 0, 1);
					glScaled(0.2, 2, 0.2);
					glutSolidCube(30);


				}glPopMatrix();

				glPushMatrix();//마법구슬
				{
					glColor3d(1, 1, 1);
					glTranslated(-58.5, 37, 40);
					glEnable(GL_TEXTURE_2D);
					glEnable(GL_TEXTURE_GEN_S);
					glEnable(GL_TEXTURE_GEN_T);
					glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
					glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
					glBindTexture(GL_TEXTURE_2D, textures[0]);
					glutSolidSphere(10, 30.0, 30.0);
					glDisable(GL_TEXTURE_GEN_S);
					glDisable(GL_TEXTURE_GEN_T);
					glDisable(GL_TEXTURE_2D);
				}}
			glPopMatrix();
			glPopMatrix();
			glPopMatrix();
			glPopMatrix();
			glPopMatrix();
		}
		glDisable(GL_NORMALIZE);
		
		
		if (bm.isTrue == true && bm.explode == false)
		{
			if (bm.timer % 3 == 0)
				glColor3d(1, 1, 0);
			else if (bm.timer % 3 == 1)glColor3d(1, 1, 1);
			else glColor3d(0, 0, 1);
			glPushMatrix();
			glTranslatef(bm.x, bm.y, bm.z);
			glLineWidth(2);
			glutWireSphere(50, 8, 8);
			glPopMatrix();
			glLineWidth(1);
		}
		if (bm.explode == true)
		{
			if (bm.timer % 2 == 0)
				glColor3d(1, 1, 0);
			else if (bm.timer % 3 == 1)glColor3d(1, 1, 1);
			else glColor3d(0, 0, 1);
			glPushMatrix();
			glTranslatef(bm.x, bm.y, bm.z);
			glLineWidth(2);
			glScaled(bm.size, bm.size, bm.size);
			glutWireSphere(50, 8, 8);
			glPopMatrix();
			glLineWidth(1);
		}
	}

	void initTextures()
	{
		glGenTextures(1, textures); //텍스처 이름을 생성한다. n:생성되어야할 텍스처이름의 수 

		glBindTexture(GL_TEXTURE_2D, textures[0]); // 텍스처링 할 객체에 텍스처를 연결해준다.
		pBytes = LoadDIBitmap("thunder.bmp", &info);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	}
};
#endif // !Character