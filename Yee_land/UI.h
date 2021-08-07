#pragma once
#ifndef UI
#include "Texture.h"
#include <math.h>
#include "Obstacle.h"
#define UI_HP 200
#define UI_MP 200
#define KC 10
#define WX 1200
#define WY 700 //window xy,
class UI : Texture
{
private:
	char char_buf[100];
	int len;
public:
	int timer;

	void UI_enter() {
		initTextures(); // 여기서 하면 안된다! -> 그럼 어디서?
	}
	GLubyte *pBytes; // 데이터를 가리킬 포인터
	BITMAPINFO *info; // 비트맵 헤더 저장할 변수
	GLuint UI_textures[3];

	void draw_crosshair(int fps, int kill, int hp, int mp, int numofHP_Portion, int numofMP_Portion, int boss_hp, bool boss_istrue) { //fps on이면 1인칭
		if (fps == 1) {
			glColor3f(1, 1, 1);
			glPointSize(2);
			glBegin(GL_POINTS);// Crosshair
			glVertex2f(WX / 2, WY / 2);
			glEnd();
		}
		else {
			glColor3f(1, 1, 1);
			glPointSize(2);
			glBegin(GL_POINTS);// Crosshair
			glVertex2f(WX / 2, WY / 2);
			glEnd();
		}




		glColor3f(1, 0, 0);

		glPushMatrix();//kill 표시
		glColor3f(1, 0, 0);
		glTranslatef(WX - 160, 25, 0);
		glRasterPos2f(0.0, 0.0);
		sprintf(char_buf, "KillCount : %d", kill);
		len = (int)strlen(char_buf);
		for (int i = 0; i < len; i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, char_buf[i]);
		glPopMatrix();


		if (kill > KC&&timer < 30)
		{
			if (timer % 10 < 5) {
				glColor3f(1, 1, 1);
				renderBitmapCharacter(550, 350, GLUT_BITMAP_TIMES_ROMAN_24, "Boss appear!!");
			}
		}

		if (GAME_OVER)	
		{
			glPushMatrix();
			glColor3f(1, 1, 1);
			renderBitmapCharacter(550, 350, GLUT_BITMAP_TIMES_ROMAN_24, "GAME OVER");
			glPopMatrix();
		}

		if (boss_hp > 0 && boss_istrue == true) {
			glColor3f(1, 0, 0);
			renderBitmapCharacter(0, WY - 660, GLUT_BITMAP_TIMES_ROMAN_24, "BOSSHP");
			glBegin(GL_QUADS);// HP
			glVertex2f(100, WY - 690);
			glVertex2f(boss_hp / 100 + 100, WY - 690);
			glVertex2f(boss_hp / 100 + 100, WY - 660); // hp=200으로 잡음.
			glVertex2f(100, WY - 660);
			glEnd();
		}


		glColor3f(0, 0, 1);
		renderBitmapCharacter(10, WY - 20, GLUT_BITMAP_TIMES_ROMAN_24, "MP");
		glBegin(GL_QUADS);// Crosshair
		glColor3f(0, 0, 1);
		glVertex2f(50, WY - 40);
		glVertex2f(50, WY - 10);
		glVertex2f(mp + 50 + mp / 2, WY - 10);
		glVertex2f(mp + 50 + mp / 2, WY - 40); // hp=200으로 잡음.
		glEnd();

		glColor3f(1, 0, 0);
		renderBitmapCharacter(10, WY - 60, GLUT_BITMAP_TIMES_ROMAN_24, "HP");
		glBegin(GL_QUADS);// HP
		glVertex2f(50, WY - 80);
		glVertex2f(50, WY - 50);
		int t_hp;
		if (hp < 0) t_hp = 0;
		else t_hp = hp;
		
		glVertex2f(t_hp + 50 + t_hp / 2, WY - 50);
		glVertex2f(t_hp + 50 + t_hp / 2, WY - 80); // hp=200으로 잡음.
		glEnd();



		glRasterPos2f(690, 675);
		sprintf(char_buf, "%d", numofHP_Portion);
		len = (int)strlen(char_buf);
		glColor3f(1, 0, 1);
		for (int i = 0; i < len; i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, char_buf[i]);

		glRasterPos2f(790, 675);
		sprintf(char_buf, "%d", numofMP_Portion);
		len = (int)strlen(char_buf);
		glColor3f(0, 0, 1);
		for (int i = 0; i < len; i++)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, char_buf[i]);



		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, UI_textures[0]);
		glBegin(GL_QUADS);// Crosshair
		glColor3f(1, 1, 1);
		glTexCoord2f(0, 1);
		glVertex2f(0, WY - 100);
		glTexCoord2f(0, 0);
		glVertex2f(0, WY);
		glTexCoord2f(1, 0);
		glVertex2f(800, WY);
		glTexCoord2f(1, 1);
		glVertex2f(800, WY - 100);
		glEnd();
		glDisable(GL_TEXTURE_2D);

	}// 크로스헤어 그리는 함수
	void Draw_UI(int i, int kill, int hp, int mp, int hp_portion, int mp_portion, int boss_hp, bool boss_istrue, Character c, Monster m, Obstacle ob, double b_x, double b_z)
	{
		glPushMatrix();

		glViewport(0, 0, WX, WY);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, WX, WY, 0, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glDisable(GL_COLOR_MATERIAL);
		glDisable(GL_NORMALIZE);

		Draw_Minimap(c, m, ob, b_x, b_z, boss_istrue);
		draw_crosshair(i, kill, hp, mp, hp_portion, mp_portion, boss_hp, boss_istrue);

		glPopMatrix();

	}
	void Draw_Minimap(Character c, Monster m, Obstacle ob, double b_x, double b_z, bool boss_istrue)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		{
			glPushMatrix();
			glTranslatef(1200, 700, 0);
			glPointSize(5);
			glBegin(GL_POINTS);
			if (m.head != NULL) {
				for (m.temp = m.head; m.temp->next != NULL; m.temp = m.temp->next)
				{
					glColor4f(1, 0, 0, 0.5f);
					glVertex2f((m.temp->x - 5000) / 50, (m.temp->z - 5000) / 50);
				}
				glColor4f(1, 0, 0, 0.5f);
				glVertex2f((m.temp->x - 5000) / 50, (m.temp->z - 5000) / 50);
			}

			glColor4f(0, 0, 1, 0.5f);
			glVertex2f((c.c_x - 5000) / 50, (c.c_z - 5000) / 50);

			if (boss_istrue == true) {
				glColor4f(0, 1, 0, 0.5f);
				glVertex2f((b_x - 5000) / 50, (b_z - 5000) / 50);
			}
			for (int i = 0; i < 20; i++)
			{
				glColor4f(1, 0, 1, 0.5f);
				glVertex2f((p[i].x - 5000) / 50, (p[i].z - 5000) / 50);
			}
			glEnd();
			glPopMatrix();
		}
		glBegin(GL_QUADS);
		glColor4f(0, 0, 0, 0.5f);
		glVertex2f(1000, 500);
		glVertex2f(1000, 700);
		glVertex2f(1200, 700);
		glVertex2f(1200, 500);
		glEnd();
		glDisable(GL_BLEND);
	}

	void Draw_StartScene()
	{
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, UI_textures[2]);
		glClearColor(0, 0, 0, 0);            // 바탕색을 'black' 로 지정   
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glColor3f(1, 1, 1);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex2f(0, 0);
		glTexCoord2f(1, 0);
		glVertex2f(600, 0);
		glTexCoord2f(1, 1);
		glVertex2f(600, 600);
		glTexCoord2f(0, 1);
		glVertex2f(0, 600);
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}

	void renderBitmapCharacter(float x, float y, void *font, char *string)
	{
		char *c;
		glRasterPos2f(x, y);
		for (c = string; *c != '\0'; c++)
		{
			glutBitmapCharacter(font, *c);
		}
	}
	void initTextures()
	{
		glGenTextures(3, UI_textures); //텍스처 이름을 생성한다. n:생성되어야할 텍스처이름의 수 

		glBindTexture(GL_TEXTURE_2D, UI_textures[0]); // 텍스처링 할 객체에 텍스처를 연결해준다.
		pBytes = LoadDIBitmap("ui.bmp", &info);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 800, 106, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

		glBindTexture(GL_TEXTURE_2D, UI_textures[1]); // 텍스처링 할 객체에 텍스처를 연결해준다.
		pBytes = LoadDIBitmap("MP.bmp", &info);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

		glBindTexture(GL_TEXTURE_2D, UI_textures[2]); // 텍스처링 할 객체에 텍스처를 연결해준다.
		pBytes = LoadDIBitmap("Title.bmp", &info);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 397, 311, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);
	}
	void Update_UI(int kill)
	{
		if (kill > KC)
		{
			timer++;
		}
	}
};
#endif // !UI