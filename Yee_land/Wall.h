#include <stdio.h>
#include<glut.h>
#include <Windows.h>
#include "Texture.h"
#define LEFT -5000
#define RIGHT 5000
#define UP 5000
#define DOWN -5000
#define Height 5000

#pragma once
#ifndef Wall
class Wall : Texture
{
public:
	GLubyte *pBytes; // �����͸� ����ų ������
	BITMAPINFO *info; // ��Ʈ�� ��� ������ ����
	GLuint textures[6];
	void Wall_enter()
	{
		initTextures();
	}
	void Draw_Wall()
	{
		glEnable(GL_TEXTURE_2D);
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

		{
			{ // ����
				glEnable(GL_CULL_FACE);
				glPushMatrix();
				glBindTexture(GL_TEXTURE_2D, textures[5]);
				glColor3f(1, 1, 1);
				{
					glBegin(GL_QUADS);
					glTexCoord2f(0, 0);
					glVertex3f(-5000, 0, 5000);
					glTexCoord2f(1, 0);
					glVertex3f(5000, 0, 5000);
					glTexCoord2f(1, 1);
					glVertex3f(5000, 0, -5000);
					glTexCoord2f(0, 1);
					glVertex3f(-5000, 0, -5000);
					glEnd();
				}
				glPopMatrix();
				glDisable(GL_CULL_FACE);
			}
		}

		{
			glBindTexture(GL_TEXTURE_2D, textures[4]);
			glColor3f(1, 1, 1);
			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex3f(LEFT, Height, DOWN);
			glTexCoord2f(1, 0);
			glVertex3f(RIGHT, Height, DOWN);
			glTexCoord2f(1, 1);
			glVertex3f(RIGHT, Height, UP);
			glTexCoord2f(0, 1);
			glVertex3f(LEFT, Height, UP);
			glEnd();
		}

		glEnable(GL_CULL_FACE);
		glColor3f(1, 1, 1);
		{
			glBindTexture(GL_TEXTURE_2D, textures[0]);
			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex3f(RIGHT, 0.0, DOWN);
			glTexCoord2f(1, 0);
			glVertex3f(RIGHT, 0.0, UP);
			glTexCoord2f(1, 1);
			glVertex3f(RIGHT, Height, UP);
			glTexCoord2f(0, 1);
			glVertex3f(RIGHT, Height, DOWN);
			glEnd();
		} // ������ ��
		glDisable(GL_CULL_FACE);

		glEnable(GL_CULL_FACE);
		{
			glBindTexture(GL_TEXTURE_2D, textures[1]);
			glBegin(GL_QUADS);
			glTexCoord2f(1, 0);
			glVertex3f(LEFT, 0, UP);
			glTexCoord2f(0, 0);
			glVertex3f(LEFT, 0, DOWN);
			glTexCoord2f(0, 1);
			glVertex3f(LEFT, Height, DOWN);
			glTexCoord2f(1, 1);
			glVertex3f(LEFT, Height, UP);
			glEnd();
		} // ���� ��
		glDisable(GL_CULL_FACE);

		glEnable(GL_CULL_FACE);
		{
			glBindTexture(GL_TEXTURE_2D, textures[2]);
			glBegin(GL_QUADS);
			glTexCoord2f(0, 0);
			glVertex3f(LEFT, 0, DOWN);
			glTexCoord2f(1, 0);
			glVertex3f(RIGHT, 0, DOWN);
			glTexCoord2f(1, 1);
			glVertex3f(RIGHT, Height, DOWN);
			glTexCoord2f(0, 1);
			glVertex3f(LEFT, Height, DOWN);
			glEnd();
		} // ���� ��
		glDisable(GL_CULL_FACE);

		glEnable(GL_CULL_FACE);
		{
			glBindTexture(GL_TEXTURE_2D, textures[3]);
			glBegin(GL_QUADS);
			glTexCoord2f(0, 1);
			glVertex3f(LEFT, Height, UP);
			glTexCoord2f(1, 1);
			glVertex3f(RIGHT, Height, UP);
			glTexCoord2f(1, 0);
			glVertex3f(RIGHT, 0, UP);
			glTexCoord2f(0, 0);
			glVertex3f(LEFT, 0, UP);
			glEnd();
		}// �Ʒ��� ��
		glDisable(GL_CULL_FACE);

		glDisable(GL_TEXTURE_2D);

	}
	void initTextures()
	{
		glGenTextures(5, textures); //�ؽ�ó �̸��� �����Ѵ�. n:�����Ǿ���� �ؽ�ó�̸��� �� 

		glBindTexture(GL_TEXTURE_2D, textures[0]); // �ؽ�ó�� �� ��ü�� �ؽ�ó�� �������ش�.
		pBytes = LoadDIBitmap("W1.bmp", &info);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 400, 400, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

		glBindTexture(GL_TEXTURE_2D, textures[1]);
		pBytes = LoadDIBitmap("W4.bmp", &info);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 400, 400, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

		glBindTexture(GL_TEXTURE_2D, textures[2]);
		pBytes = LoadDIBitmap("W3.bmp", &info);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 400, 400, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

		glBindTexture(GL_TEXTURE_2D, textures[3]);
		pBytes = LoadDIBitmap("W1.bmp", &info);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 400, 400, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

		glBindTexture(GL_TEXTURE_2D, textures[4]);
		pBytes = LoadDIBitmap("sky.bmp", &info);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

		glBindTexture(GL_TEXTURE_2D, textures[5]);
		pBytes = LoadDIBitmap("Ground.bmp", &info);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	}

};
#endif // !Wall
