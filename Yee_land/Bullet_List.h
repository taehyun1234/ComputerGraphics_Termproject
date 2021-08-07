#include<glut.h>
#include <gl\GL.h>
#include <iostream>
#include "Camara.h"
#include "Monster.h"

#pragma once
#ifndef Bullet
struct Bullet_Node
{
	int time; // 총알이 발사된후로부터의 시간.
	double x, y, z;
	double rad;
	double angle_x, angle_y, angle_z;
	Bullet_Node * next;
};

class Bullet
{
public:
	Bullet_Node * head;
	Bullet_Node * temp;

	Bullet()
	{
		head = nullptr;
		temp = nullptr;
	}
	void Insert(double x, double y, double z,double rotateX,double rotateY) // 좌표값 넣기.
	{
		Bullet_Node * newNode = new Bullet_Node;
		newNode->x = x;
		newNode->y = y;
		newNode->z = z;
		newNode->time = 0;
		newNode->rad = 12;
//		newNode->angle_y = 30 * cos((rotateY)* 3.141592 / 180);
		newNode->angle_x = 30 * sin((rotateY)* 3.141592 / 180) * sin((rotateX)* 3.141592 / 180);
		newNode->angle_z = 30 * sin((rotateY)* 3.141592 / 180) * cos((rotateX)* 3.141592 / 180);
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
	}

	void Delete(Bullet_Node * n)
	{
		Bullet_Node * delNode = n;
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
			for(temp=head;temp->next!=delNode;temp=temp->next){}
			temp->next = delNode->next;
			free(delNode);
		}
	}
	void Draw_Bullet()
	{
		if (head != NULL) {
			for (temp = head; temp->next != NULL; temp = temp->next) {
				glPushMatrix();
				
					glColor3f(1,1,0);
				
				glTranslatef(temp->x, temp->y, temp->z);
				glutWireSphere(temp->rad, 6, 6);
				glPopMatrix();
			}
			glPushMatrix();
			
			glColor3f(1, 1, 0);
			
			glTranslatef(temp->x, temp->y, temp->z);
			glutWireSphere(temp->rad, 6, 6);
			glPopMatrix();
		}
	}
	void Update_Bullet()
	{
		if (head != NULL) {
			for (temp = head; temp->next != NULL; temp = temp->next) {
				temp->time++;
				temp->x += temp->angle_x;
	//			temp->y += temp->angle_y;
				temp->z += temp->angle_z;
			}
			temp->time++;
			temp->x += temp->angle_x;
	//		temp->y += temp->angle_y;
			temp->z += temp->angle_z;

			for (temp = head; temp->next != NULL; temp = temp->next) {
				if (temp != NULL)
				{
					if (temp->time > 15) {
						Delete(temp);
					}
				}
			}
			if (temp->time > 15) {
				Delete(temp);
			}

		}
	}
};

#endif // !Bullet