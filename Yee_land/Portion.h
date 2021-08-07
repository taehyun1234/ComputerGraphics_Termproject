#include "Include_All.h"
#pragma once
#ifndef Portion
#define HP 900
#define MP 901
struct Portion_Node
{
	int time; // Æ÷¼ÇÀº °è¼Ó ºùºù µ¼
	int HP_or_MP;
	double x, y, z;
	Portion_Node * next;
	Portion_Node() // »ý¼ºÀÚ mp/hpÆ÷¼ÇÀ» ·£´ýÀ¸·Î ÃÊ±âÈ­½ÃÄÑÁÜ
	{
		HP_or_MP = rand() % 2+900;
	}
};

class Portion
{
public:
	int the_number_of_HP;
	int the_number_of_MP;
	Portion_Node * head;
	Portion_Node * temp;

	Portion()
	{
		head = nullptr;
		temp = nullptr;
	}
	int Return_The_Number_Of_MP()
	{
		return the_number_of_MP;
	}

	int Return_The_Number_Of_HP()
	{
		return the_number_of_HP;
	}


	void Insert(double x, double y, double z) // ÁÂÇ¥°ª ³Ö±â.
	{
		Portion_Node * newNode = new Portion_Node;
		newNode->x = x;
		newNode->y = y;
		newNode->z = z;
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

	void Delete(Portion_Node * n)
	{
		Portion_Node * delNode = n;
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
	}

	void Draw_p()
	{
		glPushMatrix();
		if (temp->HP_or_MP == MP) {
			glColor3f(0, 0, 1);
		}
		else
		{
			glColor3f(1, 0, 0);
		}
		glTranslatef(temp->x, temp->y, temp->z);
		glRotatef(45, 1, 0, 0);
		glRotatef(temp->time * 30, 0, 1, 0);
		glutSolidCube(20);
		{
			glPushMatrix();
			if (temp->HP_or_MP == MP) {
				glColor3f(0.6, 0.4, 0.05);
			}
			else
			{
				glColor3f(0.6, 0.4, 0.05);
			}
			glTranslatef(0, 20, 0);
			glRotatef(temp->time, 0, 1, 0);
			glutSolidCube(10);
			glPopMatrix();
		}
		glPopMatrix();
	}
	void Draw_Portion()
	{
		if (head != NULL) {
			for (temp = head; temp->next != NULL; temp = temp->next)
			{
				Draw_p();
			}
			Draw_p();
		}
	}

	void Use_HP_Portion()
	{
		the_number_of_HP--;
	}
	void Use_MP_Portion()
	{
		the_number_of_MP--;
	}


	void Update_Portion(double x,double z) // ºù±Ûºù±Û~
	{
		if (head != NULL) {
			for (temp = head; temp->next != NULL; temp = temp->next)
			{
				temp->time++;
			}
			temp->time++;
		}
		if (head != NULL) {
			for (temp = head; temp->next != NULL; temp = temp->next)
			{
				if (Collide_2D(x, z, temp) == true)
				{
					if (temp->HP_or_MP == HP)
					{
						the_number_of_HP++;
					}
					else
					{
						the_number_of_MP++;
					}
					Delete(temp);
				}
			}
			if (Collide_2D(x, z, temp) == true)
			{
				if (temp->HP_or_MP == HP)
				{
					the_number_of_HP++;
				}
				else
				{
					the_number_of_MP++;
				}
				Delete(temp);
			}
		}
	}
	bool Collide_2D(double x, double z, Portion_Node *n)
	{
		if (sqrt((x - n->x)*(x - n->x) + (z - n->z)*(z - n->z))<50)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};



#endif // !Portion
