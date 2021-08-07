#pragma once
#include <iostream>
#include <glut.h>
#include "Texture.h"
#include "Bullet_List.h"
#include "Portion.h"
#include "collide.h"
#include "Obstacle.h"
#include "Thunderbolt.h"
#ifndef Monster
#define TIME 300
#define M_ANGLE  180/3.141592 

/*
Monster 클래스에 필요한 것
- 인공지능 (공격, 임의이동, 캐릭터에게 접근)
- 충돌판정 (aabb or obb)
- 몬스터의 종류 (보스몹, 일반몹)
- 텍스처링
- 모션(죽는모션 + 공격모션) 등등
*/
double save_Mx;
double save_Mz;

struct Monster_Node
{
	double x, y, z;
	int hp;
	bool swing;
	double speed;
	double dir; // 바라보는 방향
	bool attack;
	int time; // 시간에 따라서 움직임.
	int angle;
	int monster_property; // 몬스터객체의 속성 
	Monster_Node * next;
	Monster_Node()
	{
		attack = false;
		monster_property = rand() % 2;
	}
};

class Monster : Texture
{
private:
	GLubyte *pBytes; // 데이터를 가리킬 포인터
	BITMAPINFO *info; // 비트맵 헤더 저장할 변수
	GLuint m_textures[4];
	int numOf_Monster; // 몬스터의 개체수
	int deathcount;
public:
	Monster_Node * head;
	Monster_Node * temp;
	Monster()
	{
		numOf_Monster = 0;
		head = nullptr;
		temp = nullptr;
	}
	void Monster_enter()
	{
		initTextures();
	}

	int Return_Monster_Num()
	{
		return numOf_Monster;
	}

	int Return_Monster_DeathCount()
	{
		return deathcount;
	}

	void Insert(double x, double y, double z) // 좌표값 넣기.
	{
		Monster_Node * newNode = new Monster_Node;
		newNode->hp = 300;
		newNode->x = x;
		newNode->y = y;
		newNode->z = z;
		newNode->time = 0;
		newNode->angle = 0;
		newNode->speed = 2;
		if (head == NULL)
		{
			head = newNode;
			newNode->next = NULL;
		}
		else
		{
			for (temp = head; temp->next != NULL; temp = temp->next) {}
			temp->next = newNode;
			newNode->next = NULL;
		}
		numOf_Monster++;
	}

	void Delete(Monster_Node * n)
	{
		Monster_Node * delNode = n;
		if (n == head)
		{
			if (delNode == head)
			{
				if (delNode->next == NULL)
				{
					head = NULL;
				}
				else
				{
					head = head->next;
				}
			}
		}
		else
		{
			for (temp = head; temp->next != delNode; temp = temp->next) {}
			temp->next = delNode->next;
			free(delNode);
		}
		deathcount++;
		numOf_Monster--;
	}
	void Draw_Monster() // 몬스터 그리기
	{
		if (head != NULL) {
			for (temp = head; temp->next != NULL; temp = temp->next) {
				if (temp->time < 10)
				{
					Make_Ani(temp->x, temp->y, temp->z, temp->time);

				}
				else
				{
					if (temp->monster_property == 0) {
						Monster_Model1(temp->x, temp->y, temp->z, temp->angle, temp->dir, temp->attack);
					}
					else
					{
						Monster_Model2(temp->x, temp->y, temp->z, temp->angle, temp->dir, temp->attack);
					}
					Draw_collide_rect(temp->x, temp->y, temp->z, 90, 60, 60);//추가 1208
				}
			}
			if (temp->time < 10)
			{
				Make_Ani(temp->x, temp->y, temp->z, temp->time);
			}
			else
			{
				if (temp->monster_property == 0) {
					Monster_Model1(temp->x, temp->y, temp->z, temp->angle, temp->dir, temp->attack);
				}
				else
				{
					Monster_Model2(temp->x, temp->y, temp->z, temp->angle, temp->dir, temp->attack);
				}
				Draw_collide_rect(temp->x, temp->y, temp->z, 90, 60, 60);//추가 1208
			}
		}
	}

	void Collide_Monster_Bullet(Bullet b,Portion *p)
	{
		if (head != NULL&&b.head != NULL)
		{
			for (b.temp = b.head; b.temp->next != NULL; b.temp = b.temp->next)
			{
				for (temp = head; temp->next != NULL; temp = temp->next)
				{
					if (temp->x - 100 < b.temp->x&&temp->x + 100 > b.temp->x
						&&temp->y - 100 < b.temp->y&&temp->y + 100 > b.temp->y
						&&temp->z - 100 < b.temp->z&&temp->z + 100 > b.temp->z)
					{
						temp->hp -= 50;
					}
				}
			}
			if (temp->x - 100 < b.temp->x&&temp->x + 100 > b.temp->x
				&&temp->y - 100 < b.temp->y&&temp->y + 100 > b.temp->y
				&&temp->z - 100 < b.temp->z&&temp->z + 100 > b.temp->z)
			{
				temp->hp -= 50;
			}
		}
		Death_Monster(p);
	}
	void Death_Monster(Portion * p)
	{
		if (head != NULL) {
			for (temp = head; temp->next != nullptr; temp = temp->next) {
				if (temp->hp < 0)
				{
					p->Insert(temp->x, temp->y, temp->z);
					Delete(temp);
				}
			}
			if (temp->hp < 0)
			{
				p->Insert(temp->x, temp->y, temp->z);
				Delete(temp);
			}
		}

	}
	void Make_Ani(double x,double y,double z,int time) // 몬스터가 생성될때 큐브가 한바퀴 돌면서 생성된다.
	{
		glPushMatrix();
		glTranslatef(x, y, z);
		glColor3f(0, 0, 1);
		glRotatef(time*36, 0, 1, 0);
		glutSolidCube(100);
		{
			glPushMatrix();
			glColor3f(0.4, 0.4, 1);
			glTranslatef(0,50,0);
			glutSolidCube(80);
			{
				glPushMatrix();
				glColor3f(0.5, 0.5,1);
				glTranslatef(0, 30, 0);
				glutSolidCube(50);
				glPopMatrix();
			}
			glPopMatrix();
		}
		glPopMatrix();
	}
	void Monster_Model1(double x,double y,double z,int angle,int dir,bool Attack)
	{
		{
			glPushMatrix();
			glTranslatef(x, y, z);
			glRotatef(dir, 0, 1, 0);
			glColor3f(1, 0.5, 0.2);
			glutSolidCube(50);
			{
				glPushMatrix();
				glTranslatef(0, 100, 0);
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, m_textures[0]);
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

				glBindTexture(GL_TEXTURE_2D, m_textures[0]);
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
				glBindTexture(GL_TEXTURE_2D, m_textures[0]);
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
				glBindTexture(GL_TEXTURE_2D, m_textures[0]);
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

				glBindTexture(GL_TEXTURE_2D, m_textures[1]);
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

				glBindTexture(GL_TEXTURE_2D, m_textures[1]);
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
			glColor3f(0.1, 0.6, 0.2);
			{
				glPushMatrix();
				glTranslatef(0, 50, 0);
				{
					glColor3f(1, 0.5, 0.2);
					{
						glPushMatrix();
						glTranslatef(0, -30, 40);
						glTranslatef(0, 30, 0);
						if (Attack == false) {
							glRotatef(-angle, 0, 0, 1);
						}
						else
						{
							glRotatef(-angle, 1, 0, 0);
						}
						glTranslatef(0, -30, 0);
						glScalef(0.5, 1.5, 0.5);
						glutSolidCube(50);
						glPopMatrix();
					}
					glColor3f(1, 0.5, 0.2);
					{
						glPushMatrix();
						glTranslatef(0, -30, -40);
						glTranslatef(0, 30, 0);
						if (Attack == false) {
							glRotatef(angle, 0, 0, 1);
						}
						else
						{
							glRotatef(angle, 1, 0, 0);
						}
						glTranslatef(0, -30, 0);
						glScalef(0.5, 1.5, 0.5);
						glutSolidCube(50);
						glPopMatrix();
					}
				}
				glutSolidCube(50);
				glPopMatrix();
			}
			glColor3f(1, 0.5, 0.2);
			{
				glPushMatrix();
				glTranslatef(0, -30, 40);
				glTranslatef(0, 30, 0);
				glRotatef(angle, 0, 0, 1);
				glTranslatef(0, -30, 0);
				glScalef(0.5, 1.5, 0.5);
				glutSolidCube(50);
				glPopMatrix();
			}
			glColor3f(1, 0.5, 0.2);
			{
				glPushMatrix();
				glTranslatef(0, -30, -40);
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
	void Search_Monster_Thunder(double cx, double cy, double cz)
	{
		for (temp = head; temp->next != NULL; temp = temp->next)
		{
			if (Hex_by_Hex_collide_check(Get_minmax_dot(cx, cy, cz, 80, 300, 300),
				Get_minmax_dot(temp->x, temp->y, temp->z, 80, 60, 60)))//스킬 범위내에 몬스터가 있으면
			{
				any_num = 0;
				thunder[thun_num].loop_num = thun_num;
				thunder[thun_num].match = true;
				thunder[thun_num].x = temp->x; thunder[thun_num].y = temp->y; thunder[thun_num].z = temp->z;
				thunder[thun_num].ex = temp->x; thunder[thun_num].ey = temp->y + 350; thunder[thun_num].ez = temp->z;
				temp->hp -= 200;
				thun_num++;
				if (thun_num == 4)
				{
					break;
				}

			}
		}
	}

	void Monster_Model2(double x, double y, double z, int angle, int dir, bool Attack)
	{
		{
			glPushMatrix();
			glTranslatef(x, y, z);
			glRotatef(dir, 0, 1, 0);
			glColor3f(0.6, 0.65, 0.4);
			{
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, m_textures[2]);
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

				glBindTexture(GL_TEXTURE_2D, m_textures[2]);
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
				glBindTexture(GL_TEXTURE_2D, m_textures[2]);
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
				glBindTexture(GL_TEXTURE_2D, m_textures[2]);
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

				glBindTexture(GL_TEXTURE_2D, m_textures[3]);
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

				glBindTexture(GL_TEXTURE_2D, m_textures[3]);
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
			}// 얼굴
			{
				glColor3f(0.603, 0.742, 0.545);
				glPushMatrix();
				glTranslatef(0, -50, 70);
				glTranslatef(0, 30, 0);
				if (Attack == false) {
					glRotatef(angle, 0, 0, 1);
				}
				else
				{
					glRotatef(angle, 1, 0, 0);
				}
				glTranslatef(0, -30, 0);
				glScalef(0.5, 1.5, 0.5);
				glutSolidCube(50);
				glPopMatrix();
			}

			{
				glPushMatrix();
				glTranslatef(0, -50, -70);
				glTranslatef(0, 30, 0);
				if (Attack == false) {
					glRotatef(-angle, 0, 0, 1);
				}
				else
				{
					glRotatef(-angle, 1, 0, 0);
				}
				glTranslatef(0, -30, 0);
				glScalef(0.5, 1.5, 0.5);
				glutSolidCube(50);
				glPopMatrix();
			}

			glPopMatrix();
		}
	}


	void Update_Monster(double x,double z,Character *c) // 기본몬스터 AI : 사방 이동 + 캐릭터 접근시 캐릭터에게 이동 + 공격 
										   // 캐릭터의 x,z좌표를 얻어서 범위 안에 있는지 체크.
										   // if 범위안에 있다. 캐릭터와의 거리계산후 각도 돌림. 그리고 캐릭터에게 이동.
										   // 캐릭터와의 거리가 일정거리가되면 공격을 함.
	{
		if (head != NULL) {
			for (temp = head; temp->next != NULL; temp = temp->next) {
				temp->time++;
				if (temp->time % 36 < 9) {
					temp->angle += 10;
				}
				else if (temp->time % 36 < 27)
				{
					temp->angle -= 10;
				}
				else
				{
					temp->angle += 10;
				}

				if (Collide_2D(x, z, temp)<500 && Collide_2D(x, z, temp)>100) {
					temp->attack = false;
					Move_to_Char(x, z, temp);
				}
				else if (Collide_2D(x, z, temp) < 100)
				{
					temp->attack = true;
					c->hp --;
				}
				else
				{
					temp->attack = false;
					Idle();
				}

				if (c->bm.explode == true&&Collide_Sphere(c->bm.x, c->bm.z,temp->x,temp->z)==true)
				{
					temp->hp -= 1000;
				}
			}
			temp->time++;
			if (temp->time % 36 < 9) {
				temp->angle += 10;
			}
			else if (temp->time % 36 < 27)
			{
				temp->angle -= 10;
			}
			else
			{
				temp->angle += 10;
			}
			if (Collide_2D(x, z, temp)<500 && Collide_2D(x, z, temp)>900) {
				temp->attack = false;
				Move_to_Char(x, z, temp);
			}
			else if (Collide_2D(x, z, temp) < 100)
			{
				temp->attack = true;
				c->hp --;
			}
			else
			{
				temp->attack = false;
				Idle();
			}
			if (c->bm.explode == true && Collide_Sphere(c->bm.x, c->bm.z, temp->x, temp->z) == true)
			{
				temp->hp -= 1000;
			}

		}
	}	
	void Idle()
	{
		if (temp->time%TIME * 4 < TIME)
		{
			temp->x += temp->speed;
			temp->dir = 0;
		}
		else if (temp->time%TIME * 4 >= TIME && temp->time%TIME * 4 < TIME * 2)
		{
			temp->z += temp->speed;
			temp->dir = 90;
		}
		else if (temp->time%TIME * 4 >= TIME * 2 && temp->time%TIME * 4 < TIME * 3)
		{
			temp->x -= temp->speed;
			temp->dir = 180;
		}
		else if (temp->time%TIME * 4 >= TIME * 3 && temp->time%TIME * 4 < TIME * 4)
		{
			temp->z -= temp->speed;
			temp->dir = 270;
		}
	}

	double Collide_2D(double x, double z,Monster_Node *n)
	{
		return sqrt((x - n->x)*(x - n->x) + (z - n->z)*(z - n->z));
	}
	bool Collide_Sphere(double x1, double z1, double x2, double z2)
	{
		if (sqrt((x1 - x2)*(x1 - x2) + (z1 - z2)*(z1 - z2)) < 500)
		{
			printf("닿았당");
			return true;
		}
		else
		{
			return false;
		}
	}
	void Move_to_Char(double c_x,double c_z,Monster_Node *n) // 캐릭터와 몬스터의 각도구하는 방법 theta = atan(y/x)
	{
		temp->dir = -atan((n->z - c_z)/(n->x-c_x))*M_ANGLE;
		save_Mx = temp->x;
		save_Mz = temp->z;

		double Movex = (c_x - temp->x) / 100;
		double Movez = (c_z - temp->z) / 100;




		temp->x += Movex;
		temp->z += Movez;

		for (Monster_Node * temp2 = head; temp2->next != NULL; temp2 = temp2->next)
		{
			if (temp2 != temp)
			{
				if (Hex_by_Hex_collide_check(Get_minmax_dot(temp->x, temp->y, temp->z, 90, 60, 60)
					, Get_minmax_dot(temp2->x, temp2->y, temp2->z, 90, 60, 60)))
				{
					temp->x -= temp->x - save_Mx;
					Push k = push_collide(Get_minmax_dot(temp->x, temp->y, temp->z, 90, 60, 60), Get_minmax_dot(temp2->x, temp2->y, temp2->z, 90, 60, 60));

				}

			}
			
		}


		temp->z += Movez;
		for (Monster_Node * temp2 = head; temp2->next != NULL; temp2 = temp2->next)
		{
			if (temp2 != temp)
			{
				if (Hex_by_Hex_collide_check(Get_minmax_dot(temp->x, temp->y, temp->z, 90, 60, 60)
					, Get_minmax_dot(temp2->x, temp2->y, temp2->z, 90, 60, 60)))
				{
					temp->z -= temp->z - save_Mz;
					Push k = push_collide(Get_minmax_dot(temp->x, temp->y, temp->z, 90, 60, 60), Get_minmax_dot(temp2->x, temp2->y, temp2->z, 90, 60, 60));


				}

			}

		}


		for (int i = 0; i < TREENUM; i++)
		{
			if (Hex_by_Hex_collide_check(Get_minmax_dot(temp->x, temp->y, temp->z, 90, 60, 60), Get_minmax_dot(p[i].x, p[i].y, p[i].z, 200, 30, 30)))
			{
				temp->x -= temp->x - save_Mx;
				temp->z -= temp->z - save_Mz;

				temp->x += (rand() % 10 + 15);
				temp->z += (rand() % 10 + 15);
			}
		}

		
	
		}
		/*if (temp->x < c_x)
		{
			temp->x += temp->speed;
			for (Monster_Node * temp2 = head; temp2->next != NULL; temp2 = temp2->next)
			{
				if (temp2 != temp)
				{
					if (Hex_by_Hex_collide_check(Get_minmax_dot(temp->x, temp->y, temp->z, 90, 60, 60)
						, Get_minmax_dot(temp2->x, temp2->y, temp2->z, 90, 60, 60)))
					{
						temp->x -= temp->x - save_Mx;
						Push k = push_collide(Get_minmax_dot(temp->x, temp->y, temp->z, 90, 60, 60), Get_minmax_dot(temp2->x, temp2->y, temp2->z, 90, 60, 60));

						temp->x += k.x1 / (rand() % 200 + 1);
						temp->z += k.z1 / (rand() % 200 + 1);
					}

				}

			}


			for (int i = 0; i < TREENUM; i++)
			{
				if (Hex_by_Hex_collide_check(Get_minmax_dot(temp->x, temp->y, temp->z, 90, 60, 60), Get_minmax_dot(p[i].x, p[i].y, p[i].z, 200, 30, 30)))
				{
					temp->x -= temp->x - save_Mx;
					Push k = push_collide(Get_minmax_dot(temp->x, temp->y, temp->z, 90, 60, 60), Get_minmax_dot(p[i].x, p[i].y, p[i].z, 200, 30, 30));

					//temp->x += k.x1 + (rand() % 10 + 5);
					temp->z += k.z1 + (rand() % 10 + 5);

				}
			}
		}
		else
		{
			temp->x -= temp->speed;

			for (Monster_Node * temp2 = head; temp2->next != NULL; temp2 = temp2->next)
			{
				if (temp2 != temp)
				{
					if (Hex_by_Hex_collide_check(Get_minmax_dot(temp->x, temp->y, temp->z, 90, 60, 60)
						, Get_minmax_dot(temp2->x, temp2->y, temp2->z, 90, 60, 60)))
					{
						temp->x -= temp->x - save_Mx;
						Push k = push_collide(Get_minmax_dot(temp->x, temp->y, temp->z, 90, 60, 60), Get_minmax_dot(temp2->x, temp2->y, temp2->z, 90, 60, 60));

						temp->x -= k.x1 / (rand() % 200 + 1);
						temp->z -= k.z1 / (rand() % 200 + 1);
					}
				}
			}
			for (int i = 0; i < TREENUM; i++)
			{
				if (Hex_by_Hex_collide_check(Get_minmax_dot(temp->x, temp->y, temp->z, 90, 60, 60), Get_minmax_dot(p[i].x, p[i].y, p[i].z, 200, 30, 30)))
				{
					temp->x -= temp->x - save_Mx;
					Push k = push_collide(Get_minmax_dot(temp->x, temp->y, temp->z, 90, 60, 60), Get_minmax_dot(p[i].x, p[i].y, p[i].z, 200, 30, 30));

					//temp->x += k.x1 + (rand() % 10 + 5);
					temp->z -= k.z1 + (rand() % 10 + 5);
				}
			}
		}
		if (temp->z < c_z)
		{
			temp->z += temp->speed;
			temp->z += temp->speed;

			for (Monster_Node * temp2 = head; temp2->next != NULL; temp2 = temp2->next)
			{
				if (temp2 != temp)
				{
					if (Hex_by_Hex_collide_check(Get_minmax_dot(temp->x, temp->y, temp->z, 90, 60, 60)
						, Get_minmax_dot(temp2->x, temp2->y, temp2->z, 90, 60, 60)))
					{
						temp->z -= temp->z - save_Mz;
						Push k = push_collide(Get_minmax_dot(temp->x, temp->y, temp->z, 90, 60, 60), Get_minmax_dot(temp2->x, temp2->y, temp2->z, 90, 60, 60));

						temp->x += k.x1 / (rand() % 200 + 1);
						temp->z += k.z1 / (rand() % 200 + 1);
					}
				}

			}

			for (int i = 0; i < TREENUM; i++)
			{
				if (Hex_by_Hex_collide_check(Get_minmax_dot(temp->x, temp->y, temp->z, 90, 60, 60), Get_minmax_dot(p[i].x, p[i].y, p[i].z, 200, 30, 30)))
				{
					temp->z -= temp->z - save_Mz;
					Push k = push_collide(Get_minmax_dot(temp->x, temp->y, temp->z, 90, 60, 60), Get_minmax_dot(p[i].x, p[i].y, p[i].z, 200, 30, 30));

					//temp->x += k.x1 + (rand() % 10 + 5);
					//temp->z += k.z1 + (rand() % 10 + 5);
				}
			}
		}
		else
		{
			temp->z -= temp->speed;

			for (Monster_Node * temp2 = head; temp2->next != NULL; temp2 = temp2->next)
			{
				if (temp2 != temp)
				{
					if (Hex_by_Hex_collide_check(Get_minmax_dot(temp->x, temp->y, temp->z, 90, 60, 60)
						, Get_minmax_dot(temp2->x, temp2->y, temp2->z, 90, 60, 60)))
					{
						temp->z -= temp->z - save_Mz;
						Push k = push_collide(Get_minmax_dot(temp->x, temp->y, temp->z, 90, 60, 60), Get_minmax_dot(temp2->x, temp2->y, temp2->z, 90, 60, 60));

						temp->x -= k.x1 / (rand() % 1000 + 1);
						temp->z -= k.z1 / (rand() % 1000 + 1);
					}
				}

			}

			for (int i = 0; i < TREENUM; i++)
			{
				if (Hex_by_Hex_collide_check(Get_minmax_dot(temp->x, temp->y, temp->z, 90, 60, 60), Get_minmax_dot(p[i].x, p[i].y, p[i].z, 200, 30, 30)))
				{
					temp->z -= temp->z - save_Mz;
					Push k = push_collide(Get_minmax_dot(temp->x, temp->y, temp->z, 90, 60, 60), Get_minmax_dot(p[i].x, p[i].y, p[i].z, 200, 30, 30));

					//temp->x += k.x1 + (rand() % 10 + 5);
					//temp->z += k.z1 + (rand() % 10 + 5);
				}
			}
		}*/
	

	void initTextures()
	{
		glGenTextures(4, m_textures); //텍스처 이름을 생성한다. n:생성되어야할 텍스처이름의 수 

		glBindTexture(GL_TEXTURE_2D, m_textures[0]); // 텍스처링 할 객체에 텍스처를 연결해준다.
		pBytes = LoadDIBitmap("etc_M1.bmp", &info);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

		glBindTexture(GL_TEXTURE_2D, m_textures[1]); // 텍스처링 할 객체에 텍스처를 연결해준다.
		pBytes = LoadDIBitmap("Forward_M1.bmp", &info);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

		glBindTexture(GL_TEXTURE_2D, m_textures[2]); // 텍스처링 할 객체에 텍스처를 연결해준다.
		pBytes = LoadDIBitmap("etc_M2.bmp", &info);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

		glBindTexture(GL_TEXTURE_2D, m_textures[3]); // 텍스처링 할 객체에 텍스처를 연결해준다.
		pBytes = LoadDIBitmap("Forward_M2.bmp", &info);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	}

};

#endif // !Monster
