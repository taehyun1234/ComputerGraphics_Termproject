#pragma once
#include <math.h>
#include "Texture.h"
#ifndef Boss
#define RAD_TO_ANGLE  3.141592/180 
#define ANGLE_TO_RAD 180/3.141592
class Boss : Texture
{
private:
	bool fall; // 보스가 내려왔을 때 내려온거 체크
	bool isTrue;
	bool quake;
	int angle;
	int timer; // 일정시간이되면 스킬을 사용함.
	bool Q;
	int   ntime = 0;
	bool n;
	bool Needle_Targetin; // 불뿜기 스킬 타겟팅중
	int Needle_Time;
	int Needle_Angle;
	int Qtimer;
	bool earth_Quake;// 내려찍기
	int skilltime_EarthQuake;//위에 있는시간.
	double theta;
	double x1, y1, x2, y2, x3, y3, x4, y4;
	double x11, y11, x22, y22, x33, y33, x44, y44;
	double dir;
	GLubyte *pBytes; // 데이터를 가리킬 포인터
	BITMAPINFO *info; // 비트맵 헤더 저장할 변수
	GLuint b_textures[2];
public:
	double x, y, z; // 보스의 x,y,z값
	int hp;
	void Boss_isTrueSet()
	{
		isTrue = true;
	}
	bool get_isTrue()
	{
		return isTrue;
	}
	Boss()
	{
		fall = false;
		x = 0;
		y = 1000;
		z = 0;
		hp = 50000;
	}
	void Draw_Boss(double c_x, double c_z)
	{
		if (isTrue == true) {
			Draw_Collide_Needle(x1, y1, x2, y2, x3, y3, x4, y4);
			Draw_Collide_Needle(x11, y11, x44, y44, x22, y22, x33, y33);
			{
				{
					glPushMatrix();
					glTranslatef(x, y + 50, z);
					glRotatef(dir, 0, 1, 0);
					glScalef(2, 2, 2);
					glColor3f(0.3, 0.5, 0.2);

					glPushMatrix();
					glTranslatef(0, 60, 0);
					glScalef(0.6, 2.5, 0.6);
					glutSolidCube(50);
					glPopMatrix();

					glPushMatrix();
					glTranslatef(0, 70, 0);
					{
						glPushMatrix();
						glTranslatef(0, 100, 0);
						glEnable(GL_TEXTURE_2D);
						glBindTexture(GL_TEXTURE_2D, b_textures[0]);
						glColor3f(1, 1, 1);
						glBegin(GL_QUADS);//앞면 육면체
						{
							glTexCoord2f(0.0f, 1.0f);
							glVertex3f(-50, 50, 50);
							glTexCoord2f(0.0f, 0.0f);
							glVertex3f(-50, -50, 50);
							glTexCoord2f(1.0f, 0.0f);
							glVertex3f(50, -50, 50);
							glTexCoord2f(1.0f, 1.0f);
							glVertex3f(50, 50, 50);
						}
						glEnd();

						glBindTexture(GL_TEXTURE_2D, b_textures[0]);
						glBegin(GL_QUADS);//뒷면 육면체
						{
							glTexCoord2f(1.0f, 1.0f);
							glVertex3f(50, 50, -50);
							glTexCoord2f(1.0f, 0.0f);
							glVertex3f(50, -50, -50);
							glTexCoord2f(0.0f, 0.0f);
							glVertex3f(-50, -50, -50);
							glTexCoord2f(0.0f, 1.0f);
							glVertex3f(-50, 50, -50);
						}
						glEnd();
						//////////////////////////////////
						glBindTexture(GL_TEXTURE_2D, b_textures[0]);
						glBegin(GL_QUADS);//윗면 육면체
						{
							glTexCoord2f(0.0f, 0.0f);
							glVertex3f(-50, 50, -50);
							glTexCoord2f(1.0f, 0.0f);
							glVertex3f(-50, 50, 50);
							glTexCoord2f(1.0f, 1.0f);
							glVertex3f(50, 50, 50);
							glTexCoord2f(0.0f, 1.0f);
							glVertex3f(50, 50, -50);
						}
						glEnd();
						//////////////////////////////////
						glBindTexture(GL_TEXTURE_2D, b_textures[0]);
						glBegin(GL_QUADS);//아랫면 육면체
						{
							glTexCoord2f(0.0f, 0.0f);
							glVertex3f(-50, -50, -50);
							glTexCoord2f(0.0f, 1.0f);
							glVertex3f(-50, -50, 50);
							glTexCoord2f(1.0f, 1.0f);
							glVertex3f(50, -50, 50);
							glTexCoord2f(1.0f, 0.0f);
							glVertex3f(50, -50, -50);
						}
						glEnd();

						glBindTexture(GL_TEXTURE_2D, b_textures[1]);
						{
							glBegin(GL_QUADS);//옆면 육면체 1
							glTexCoord2f(0.0f, 1.0f);
							glVertex3f(-50, 50, -50);
							glTexCoord2f(0.0f, 0.0f);
							glVertex3f(-50, -50, -50);
							glTexCoord2f(1.0f, 0.0f);
							glVertex3f(-50, -50, 50);
							glTexCoord2f(1.0f, 1.0f);
							glVertex3f(-50, 50, 50);
							glEnd();
						}//정면

						glBindTexture(GL_TEXTURE_2D, b_textures[1]);
						{
							glBegin(GL_QUADS);//옆면 육면체 1
							glTexCoord2f(1.0f, 1.0f);
							glVertex3f(50, 50, 50);
							glTexCoord2f(1.0f, 0.0f);
							glVertex3f(50, -50, 50);
							glTexCoord2f(0.0f, 0.0f);
							glVertex3f(50, -50, -50);
							glTexCoord2f(0.0f, 1.0f);
							glVertex3f(50, 50, -50);
							glEnd();
						}
						glDisable(GL_TEXTURE_2D);
						glPopMatrix();
					}// 얼굴
					glPopMatrix();
					glColor3f(0.4, 0.5, 0.2);
					{
						glPushMatrix();
						glTranslatef(0, -30, 30);
						glTranslatef(0, 30, 0);
						glRotatef(angle, 0, 0, 1);
						glTranslatef(0, -30, 0);
						glScalef(0.5, 1.5, 0.5);
						glutSolidCube(50);
						glPopMatrix();
					}
					glColor3f(0.4, 0.5, 0.2);
					{
						glPushMatrix();
						glTranslatef(0, -30, -30);
						glTranslatef(0, 30, 0);
						glRotatef(-angle, 0, 0, 1);
						glTranslatef(0, -30, 0);
						glScalef(0.5, 1.5, 0.5);
						glutSolidCube(50);
						glPopMatrix();
					}
					glPopMatrix();
				}
			}
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			if (earth_Quake == true)
			{
				glPushMatrix();
				glColor4f(0, 0, 0, 0.5f);
				glTranslatef(x, 0, z);
				glRotatef(dir, 0, 1, 0);
				glScalef(3, 0.1, 3);
				glutSolidCube(100);
				glPopMatrix();
			}

			if (Needle_Targetin == true)
			{
				glColor4f(0, 0, 0, 0.5f);
				glPushMatrix();
				glTranslatef(x, 0, z);
				glRotatef(Needle_Angle, 0, 1, 0);
				glTranslatef(-1000, 0, 0);
				glScalef(10, 0.1, 1);
				glutSolidCube(100);
				glPopMatrix();

				glColor4f(0, 0, 0, 0.5f);
				glPushMatrix();
				glTranslatef(x, 0, z);
				glRotatef(Needle_Angle, 0, 1, 0);
				glTranslatef(1000, 0, 0);
				glScalef(10, 0.1, 1);
				glutSolidCube(100);
				glPopMatrix();

				glColor4f(0, 0, 0, 0.5f);
				glPushMatrix();
				glTranslatef(x, 0, z);
				glRotatef(Needle_Angle, 0, 1, 0);
				glTranslatef(0, 0, 1000);
				glScalef(1, 0.1, 10);
				glutSolidCube(100);
				glPopMatrix();

				glColor4f(0, 0, 0, 0.5f);
				glPushMatrix();
				glTranslatef(x, 0, z);
				glRotatef(Needle_Angle, 0, 1, 0);
				glTranslatef(0, 0, -1000);
				glScalef(1, 0.1, 10);
				glutSolidCube(100);
				glPopMatrix();
			}
			glDisable(GL_BLEND);

			if (n == true)
			{
				glPushMatrix();
				{
					glTranslatef(0, -100 + Needle_Time * 10, 0);
					{
						glColor3f(0, 0, 1);
						for (int i = 0; i < 5; i++)
						{
							glPushMatrix();
							glTranslatef(x, 0, z);
							glRotatef(Needle_Angle, 0, 1, 0);
							glTranslatef(0, 0, -400 - i * 300);
							{
								glPushMatrix();
								glRotatef(270, 1, 0, 0);
								glutSolidCone(20, 100 + 20 * i, 20, 20);
								glPopMatrix();
							}
							glPopMatrix();
						}
					}

					{
						glColor3f(0, 0, 1);
						for (int i = 0; i < 5; i++)
						{
							glPushMatrix();
							glTranslatef(x, 0, z);
							glRotatef(Needle_Angle, 0, 1, 0);
							glTranslatef(0, 0, 400 + i * 300);
							{
								glPushMatrix();
								glRotatef(270, 1, 0, 0);
								glutSolidCone(20, 100 + 20 * i, 20, 20);
								glPopMatrix();
							}
							glPopMatrix();
						}
					}

					{
						glColor3f(0, 0, 1);
						for (int i = 0; i < 5; i++)
						{
							glPushMatrix();
							glTranslatef(x, 0, z);
							glRotatef(Needle_Angle, 0, 1, 0);
							glTranslatef(-400 - i * 300, 0, 0);
							{
								glPushMatrix();
								glRotatef(270, 1, 0, 0);
								glutSolidCone(20, 100 + 20 * i, 20, 20);
								glPopMatrix();
							}
							glPopMatrix();
						}
					}

					{
						glColor3f(0, 0, 1);
						for (int i = 0; i < 5; i++)
						{
							glPushMatrix();
							glTranslatef(x, 0, z);
							glRotatef(Needle_Angle, 0, 1, 0);
							glTranslatef(400 + i * 300, 0, 0);
							{
								glPushMatrix();
								glRotatef(270, 1, 0, 0);
								glutSolidCone(20, 100 + 20 * i, 20, 20);
								glPopMatrix();
							}
							glPopMatrix();
						}
					}

				}
				glPopMatrix();
			}
		}
	}
	double Collide_2D(double x, double z)
	{
		return sqrt((x - this->x)*(x - this->x) + (z - this->z)*(z - this->z));
	}
	void Collide_Boss(Bullet b)
	{
		if (b.head != NULL)
		{
			for (b.temp = b.head; b.temp->next != NULL; b.temp = b.temp->next)
			{
				if (this->x - 100 < b.temp->x&&this->x + 100 > b.temp->x
					&&this->y - 100 < b.temp->y&&this->y + 100 > b.temp->y
					&&this->z - 100 < b.temp->z&&this->z + 100 > b.temp->z)
				{
					this->hp -= 50;
				}
			}
		}
	}
	void Death_Boss()
	{
		if (this->hp < 0)
		{
			this->isTrue = false;
		}
	}
	bool Quake()
	{
		return quake;
	}
	void Update_Boss(double x, double z, Bullet b, Character *c)
	{
		if (n == false) {
			this->theta = Needle_Angle*RAD_TO_ANGLE;
			Needle_Angle++;
		}
		x1 = -50 * cos(this->theta) + 30 * (-50)*sin(this->theta) + this->x;
		x2 = 50 * cos(this->theta) + 30 * (-50)*sin(this->theta) + this->x;
		x3 = 50 * cos(this->theta) + 30 * (50)*sin(this->theta) + this->x;
		x4 = -50 * cos(this->theta) + 30 * (50)*sin(this->theta) + this->x;
		y1 = -50 * -sin(this->theta) + 30 * (-50)*cos(this->theta) + this->z;
		y2 = 50 * -sin(this->theta) + 30 * (-50)*cos(this->theta) + this->z;
		y3 = -sin(this->theta) + 30 * (50)*cos(this->theta) + this->z;
		y4 = -50 * -sin(this->theta) + 30 * (50)*cos(this->theta) + this->z;

		x11 = 30 * -50 * cos(this->theta) + (-50)*sin(this->theta) + this->x;
		x22 = 30 * 50 * cos(this->theta) + (-50)*sin(this->theta) + this->x;
		x33 = 30 * 50 * cos(this->theta) + (50)*sin(this->theta) + this->x;
		x44 = 30 * -50 * cos(this->theta) + (50)*sin(this->theta) + this->x;
		y11 = 30 * -50 * -sin(this->theta) + (-50)*cos(this->theta) + this->z;
		y22 = 30 * 50 * -sin(this->theta) + (-50)*cos(this->theta) + this->z;
		y33 = 30 * 50 * -sin(this->theta) + (50)*cos(this->theta) + this->z;
		y44 = 30 * -50 * -sin(this->theta) + (50)*cos(this->theta) + this->z;

		Death_Boss();
		Collide_Boss(b);
		if (this->isTrue == true) {
			timer++;

			if (timer % 36 < 9) {
				angle += 10;
			}
			else if (timer % 36 < 27)
			{
				angle -= 10;
			}
			else
			{
				angle += 10;
			}

			if (this->n == false) {
				this->dir = -atan((this->z - z) / (this->x - x))*ANGLE_TO_RAD;
			}
			if (timer % 250 == 0 && Needle_Targetin == false)
			{
				earth_Quake = true;
				this->y = 1000;
			}

			if (timer % 100 == 0 && earth_Quake == false)
			{
				Needle_Targetin = true;
			}

			if (Needle_Targetin == true)
			{
				ntime++;
			}

			if (ntime > 20)
			{
				Needle_Targetin = false;
				n = true;
				ntime = 0;
				if (Collide_Needle(x1, y1, x2, y2, x3, y3, x4, y4, x, 20, z))
				{
					c->hp -= 50;
				}
				if (Collide_Needle(x11, y11, x44, y44, x22, y22, x33, y33, x, 20, z))
				{
					c->hp -= 50;
				}
			}

			if (n == true)
			{
				Needle_Time++;
			}

			if (Needle_Time > 10)
			{
				Needle_Time = 0;

				n = false;
			}

			if (c->bm.explode == true && Collide_Sphere(c->bm.x, c->bm.z, this->x, this->z) == true)
			{
				this->hp -= 100;
			}


			if (earth_Quake == true)
			{
				skilltime_EarthQuake++;
				if (skilltime_EarthQuake > 50)
				{
					this->y -= 50 + timer % 50;
					if (this->y < 100)
					{
						earth_Quake = false;
						Q = true;
						quake = true;
						skilltime_EarthQuake = 0;
					}
				}
			}
			if (Q == true)
			{
				Qtimer++;
				if (Qtimer > 20)
				{
					if (c->get_cx() > this->x - 300 && c->get_cx() < this->x + 300 && c->get_cz() > this->z - 300 && c->get_cz() < this->z + 300)
					{
						c->hp -= 50;
					}
					Q = false;
					quake = false;
					Qtimer = 0;
				}
			}
			if (this->fall == false) {
				this->y -= 50;
			}

			if (this->y < 100)
			{
				this->fall = true;
			}

			if (Collide_2D(x, z) > 200 && n == false) // 보스가 캐릭터를 따라댕김.
			{
				if (earth_Quake == false) {
					if (this->x < x)
					{
						this->x++;
					}
					else
					{
						this->x--;
					}
					if (this->z < z)
					{
						this->z++;
					}
					else
					{
						this->z--;
					}
				}
				else
				{
					if (this->x < x)
					{
						this->x += 30;
					}
					else
					{
						this->x -= 30;
					}
					if (this->z < z)
					{
						this->z += 30;
					}
					else
					{
						this->z -= 30;
					}
				}
			}
			else
			{
				//기본공격
			}
		}
	}

	bool Collide_Sphere(double x1, double z1, double x2, double z2)
	{
		if (sqrt((x1 - x2)*(x1 - x2) + (z1 - z2)*(z1 - z2)) < 500)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void initTextures()
	{
		glGenTextures(2, b_textures); //텍스처 이름을 생성한다. n:생성되어야할 텍스처이름의 수 
		glBindTexture(GL_TEXTURE_2D, b_textures[0]); // 텍스처링 할 객체에 텍스처를 연결해준다.
		pBytes = LoadDIBitmap("etc_B1.bmp", &info);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D, b_textures[1]); // 텍스처링 할 객체에 텍스처를 연결해준다.
		pBytes = LoadDIBitmap("Forward_B1.bmp", &info);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	}

	void Draw_Collide_Needle(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
	{
		double d_x = x1 + (x2 - x1) / 2;
		double d_y = y2 + (y2 - y1) / 2;
		double d_x2 = x3 + (x4 - x3) / 2;
		double d_y2 = y4 + (y4 - y3) / 2;
		for (int i = 0; i < 20; i++)
		{
			glPushMatrix();
			Draw_collide_rect(d_x + (d_x2 - d_x) / 20 * i, 20, d_y + (d_y2 - d_y) / 20 * i, 50, 60, 60);
			glPopMatrix();
		}
	}

	bool Collide_Needle(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double cx, double cy, double cz)
	{
		double d_x = x1 + (x2 - x1) / 2;
		double d_y = y2 + (y2 - y1) / 2;
		double d_x2 = x3 + (x4 - x3) / 2;
		double d_y2 = y4 + (y4 - y3) / 2;

		for (int i = 0; i < 20; i++)
		{

			if (Hex_by_Hex_collide_check(Get_minmax_dot(d_x + (d_x2 - d_x) / 20 * i, 20, d_y + (d_y2 - d_y) / 20 * i, 50, 60, 60)
				, Get_minmax_dot(cx, cy, cz, 60, 60, 60)))
			{
				return true;
			}

		}
		return false;
	}
};

#endif // !Boss