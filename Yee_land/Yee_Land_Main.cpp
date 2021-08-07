// ���� ��ü�鿡 ���Ͽ� �ؽ��ĸ��� ���ָ� �����Ӽ��� �������� �ؽ��İ� �׾������. ���̷�����??
// �޸𸮸� �Ҵ縸�ϰ� ���������� �ʴ´�. =>��ü ��?? Disable�Լ��� ����ϸ� �޸𸮰� �����Ǵ°� �ƴѰ�?
#include "Include_All.h"
#define FPS 1
#define TPS 2
#define WindowSize_X  1200   
#define WindowSize_Y  700
#define Main_Rad 3.141592 / 180
#define Height 5000
#define LEFT -5000
#define RIGHT 5000
#define UP 5000
#define DOWN -5000

float camxrotate = 0, camyrotate = -90;
float nx = 0, ny = 0;
float testx = 0, texty = 0;
float gravity = 0;
int Charspeed = 10, Camdistance = 400, MouseSens = 250;
int View_Port = 2;
bool start;
bool Keybuffer[256];
bool lock_mouse = true;
/*�浹*/
double savex, savez;
double save_cx, save_cz;
void char_by_Map_collide();
void char_by_Tree_collide();

Portion portion;
Boss boss;
Obstacle ob;
UI ui;
Character character;
Monster monster;
Camera cam;
Bullet bullet;
Wall wall;
GLvoid drawScene(GLvoid);
GLvoid start_scene(GLvoid);
GLvoid reshape(int w, int h);

void Keyboard(unsigned char, int, int);
void Keyboardup(unsigned char key, int x, int y);
void TimerFunction(int value);
void MouseFunc(int, int, int, int);
void Motion(int x, int y);
void target(int x, int y);
void Keyinput(int key);

GLfloat AmbientLight[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat DiffuseLight[] = { 0.4f, 0.4f, 0.4f, 1.0f };
GLfloat SpecularLight[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat lightPos[] = { 0, 2000, 0, 1 };

int zentime; // ������ ��Ÿ��.
void main(int argc, char** argv)    // ������ ����ϰ� ����Լ� ���� 
{   // �ʱ�ȭ �Լ��� 
	start = false;
	srand(time(NULL));
	glutInit(&argc, argv);    // glut �ʱ�ȭ       
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);   // ���÷��� ��� ����        
	glutInitWindowPosition(100, 100);   // �������� ��ġ ����        
	glutInitWindowSize(WindowSize_X, WindowSize_Y);    // �������� ũ�� ����   
	glutCreateWindow("Example1");   // ������ ���� (������ �̸�)         
	glutSetCursor(GLUT_CURSOR_NONE);
	for (int i = 0; i < 256; i++)
		Keybuffer[i] = false;

	glutPassiveMotionFunc(Motion);   //���콺���
	glutDisplayFunc(drawScene);    // ��� �Լ��� ����         
	glutReshapeFunc(reshape);   // �ٽ� �׸��� �Լ� ����        
	glutKeyboardFunc(Keyboard); // Ű���� �ݹ��Լ� ���
								//glutPassiveMotionFunc(Motion);//���콺���
	glutKeyboardUpFunc(Keyboardup);
	glutMotionFunc(Motion);
	glutMouseFunc(MouseFunc);

	if (start == false)
	{
		PlaySound("Yee_Land_BackGround_Music.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);
	}
	{
		character.initTextures();
		boss.initTextures();
		ImportTextures();
		wall.Wall_enter();
		ui.UI_enter();
		ob.Obstacle_enter();
		monster.Monster_enter();
		glutTimerFunc(60, TimerFunction, 1);
	}
	glutMainLoop();    // �̺�Ʈ ó�� ���� 
}

void MouseFunc(int button, int state, int x, int y)
{
	static int bul_control = 0; //��ư �������� ������ �Ѿ˳����� �����ϳ� �߰� (LEFT BUTTON UP �Լ��� �ֳ�??)
	if (button == GLUT_LEFT_BUTTON && !GAME_OVER) {
		if (bul_control % 2 == 0)
			bullet.Insert(character.get_cx(), character.get_cy() + 0, character.get_cz(), camxrotate, camyrotate);
		bul_control++;
	}
	glutPostRedisplay();   // ȭ�� �� ���
}
void Motion(int x, int y)
{
	target(x, y);
}
void TimerFunction(int value)
{
	Thunder_update();
	if (lock_mouse)   glutWarpPointer(WindowSize_X / 2, WindowSize_Y / 2);
	//�ִϸ��̼�
	if (walk && walk_dir == 1)
	{
		walk_angle += 4;
		if (walk_angle > 45)
			walk_dir = 2;
	}
	else if (walk && walk_dir == 2)
	{
		walk_angle -= 4;
		if (walk_angle < -45)
			walk_dir = 1;
	}
	ui.Update_UI(monster.Return_Monster_DeathCount());
	glutPostRedisplay();   // ȭ�� �� ���
	character.Update(camyrotate, camxrotate);
	for (int i = 0; i < 256; i++)
		if (Keybuffer[i])
			Keyinput(i);
	if (start == true) {
		if (monster.Return_Monster_Num() < 20 && zentime % 50 == 0)
		{
			monster.Insert(rand() % 9000 - 4500, 70, rand() % 9000 - 4500);
		}

		boss.Update_Boss(character.get_cx(), character.get_cz(), bullet, &character);
		monster.Collide_Monster_Bullet(bullet, &portion);
		zentime++;
		cam.timer();
		portion.Update_Portion(character.get_cx(), character.get_cz());
		bullet.Update_Bullet();
		monster.Update_Monster(character.get_cx(), character.get_cz(), &character);
	}
	glutTimerFunc(40, TimerFunction, 1);
}

void Keyboardup(unsigned char key, int x, int y)
{
	Keybuffer[key] = false;
	if (key == 'w' || key == 's' || key == 'a' || key == 'd')
	{
		walk = false;
		walk_angle = 0;
		walk_dir = 1;
	}
	else if (key == 'm')
	{
		if (lock_mouse)   lock_mouse = false;
		else lock_mouse = true;
	}
}
void Keyboard(unsigned char key, int x, int y)
{
	Keybuffer[key] = true;
	if (start == true )
	{
		switch (key)
		{
		case '1':
			if (portion.Return_The_Number_Of_HP() > 0 && !GAME_OVER)
			{
				portion.Use_HP_Portion();
				character.Recovery_HP();
			}
			break;
		case '2':
			if (portion.Return_The_Number_Of_MP() > 0 && !GAME_OVER)
			{
				portion.Use_MP_Portion();
				character.Recovery_MP();
			}
			break;
		case 'e':
			if (character.bm.isTrue == false && character.bm.explode == false && character.mp >= 10 && !GAME_OVER)
			{
				character.set_bomb_True();
				character.mp -= 10;
			}
			break;
		case 'r':
		{
			if (character.mp >= 10 && !GAME_OVER)//��� �¿����� Ʈ���̸� -> �� �� �ִ»����̸�
			{
				thun_num = 0;
				Thunder_OF = false; //false 
				if (Hex_by_Hex_collide_check(Get_minmax_dot(character.c_x, character.c_y, character.c_z, 80, 300, 300),
					Get_minmax_dot(boss.x, boss.y, boss.z, 80, 60, 60)))//��ų �������� ���Ͱ� ������
				{
					any_num = 0;
					thunder[thun_num].loop_num = thun_num;
					thunder[thun_num].match = true;
					thunder[thun_num].x = boss.x; thunder[thun_num].y = boss.y +350 ; thunder[thun_num].z = boss.z;
					thunder[thun_num].ex = boss.x; thunder[thun_num].ey = boss.y +700; thunder[thun_num].ez = boss.z;
					boss.hp -= 450;
					thun_num++;
					if (thun_num == 4)
					{
						break;
					}
				}
				monster.Search_Monster_Thunder(character.c_x, character.c_y, character.c_z);
				character.mp -= 10;
			}
		}break;
		case ' ':
			if (character.jump == false && !GAME_OVER)
				character.Jump();
			break;
		case '3':
			for (int i = 0; i < 100; i++)
			{
				character.Move_Up(camxrotate, Charspeed);
				cam.Change_Char(Charspeed * cos((-camxrotate - 90) *Main_Rad), 0, Charspeed * sin((-camxrotate - 90) * Main_Rad));
			}
			break;
		case 'f':
			cam.Change_ViewPort();
			break;
		case 'b':
			if (OnOff_collide_box)
				OnOff_collide_box = false;
			else
				OnOff_collide_box = true;
			break;
		case 'q':
			exit(0);
			break;

		case '9':
			MouseSens += 10;
			break;
		case '0':
			MouseSens -= 10;
			break;
		case '-':
			if (GAME_OVER)
			{
				
					printf("��Ȱ");
					character.init();
					cam.init();
					GAME_OVER = false;

				
			}
		}
	}
	else if(!start && !GAME_OVER)
	{
		switch (key)
		{
		case ' ':
			start = true;
			break;
		}
	}

}


void Keyinput(int key)
{
	if (!GAME_OVER) {
		savex = character.get_cx();
		savez = character.get_cz();
		save_cx = cam.c_x;
		save_cz = cam.c_z;
		if (key == 'w')
		{
			walk = true;
			character.Move_Up(camxrotate, Charspeed);
			cam.Change_Char(Charspeed * cos((-camxrotate - 90) *Main_Rad), 0, Charspeed * sin((-camxrotate - 90) * Main_Rad));
			char_by_Map_collide();
			char_by_Tree_collide();
		}
		else if (key == 's')
		{
			walk = true;
			character.Move_Down(camxrotate, Charspeed);
			cam.Change_Char(-Charspeed * cos((-camxrotate - 90) * Main_Rad), 0, -Charspeed * sin((-camxrotate - 90) * Main_Rad));
			char_by_Tree_collide();
			char_by_Map_collide();
		}
		if (key == 'a')
		{
			walk = true;
			character.Move_Left(camxrotate, Charspeed);
			cam.Change_Char(-Charspeed * cos((-camxrotate) * Main_Rad), 0, -Charspeed * sin((-camxrotate) * Main_Rad));
			char_by_Tree_collide();
			char_by_Map_collide();
		}
		else if (key == 'd')
		{
			walk = true;
			character.Move_Right(camxrotate, Charspeed);
			cam.Change_Char(Charspeed * cos((-camxrotate) * Main_Rad), 0, Charspeed * sin((-camxrotate) * Main_Rad));
			char_by_Tree_collide();
			char_by_Map_collide();
		}
	}
}


GLvoid drawScene()// ��� �Լ�
{
	if (start == true)
	{
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);//��������'black'������
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, WindowSize_X, WindowSize_Y);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60.0f, (float)WindowSize_X / (float)WindowSize_Y, 0.1, 20000.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
		glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
		glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
		cam.Draw_scene(); // ī�޶�
		if (monster.Return_Monster_DeathCount() > 10) // �������ΰ� 1����ũ�� ��������
		{
			if (ui.timer < 60) {
				boss.Boss_isTrueSet();
				cam.set_cam(boss.x , boss.y + 150, boss.z );
			}
			else if (boss.Quake() == true)
			{
				if (zentime % 2 == 0) {
					cam.set_cam(character.get_cx() - 20, character.get_cy() - 50 + rand() % 20 + 10, character.get_cz() - 20);
				}
				else
				{
					cam.set_cam(character.get_cx() + 20, character.get_cy() - 50 - rand() % 20 + 10, character.get_cz() + 20);
				}
			}
			else
			{
				cam.set_cam(character.get_cx(), character.get_cy() - 50, character.get_cz());
			}
		}
		Thunder_Draw();
		portion.Draw_Portion();
		boss.Draw_Boss(character.get_cx(), character.get_cz());
		ob.Draw_Tree_set();
		monster.Draw_Monster();
		wall.Draw_Wall();
		bullet.Draw_Bullet();
		Draw_collide_rect(character.get_cx(), character.get_cy(), character.get_cz(), 80, 50, 50);
		character.Draw(camxrotate, camyrotate);// ĳ���� �׸���
		glDisable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		glDisable(GL_COLOR_MATERIAL);
		ui.Draw_UI(View_Port, monster.Return_Monster_DeathCount(), character.hp, character.mp, portion.Return_The_Number_Of_HP(), portion.Return_The_Number_Of_MP(), boss.hp, boss.get_isTrue(), character, monster, ob, boss.x, boss.z);
	}
	else
	{
		ui.Draw_StartScene();
	}
	glutSwapBuffers();      // ȭ�鿡 ����ϱ�
}
GLvoid reshape(int w, int h)    // �ٽ� �׸��� �Լ�
{   //����Ʈ ��ȯ ����
	if (start == true)
	{
		glViewport(0, 0, w, h);
		//���� ��� ���� �缳��
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		//Ŭ���� ���� ���� : ��������
		gluPerspective(60.0f, (float)w / (float)h, 0.1, 20000.0);
		//�� �� ��� ���� �缳��
		glMatrixMode(GL_MODELVIEW);
	}
	else
	{
		glViewport(0, 0, w, h);
		glOrtho(0, 600, 0, 600, 1, -1);
		glutPostRedisplay();
	}
}
void target(int x, int y)
{
	if (!GAME_OVER)
	{
		nx = WindowSize_X / 2 - x;
		ny = WindowSize_Y / 2 - y;
		camxrotate = camxrotate + (nx / MouseSens);
		camyrotate = camyrotate + (ny / MouseSens);
		cam.Change_View(10000 * sin((camyrotate)* Main_Rad) * sin((camxrotate)* Main_Rad), 10000 * cos((camyrotate)* Main_Rad), 10000 * sin((camyrotate)* Main_Rad) * cos((camxrotate)* Main_Rad));
		cam.Change_cam(-Camdistance * sin((camyrotate)*Main_Rad) * sin((camxrotate + 15)* Main_Rad), -Camdistance * cos((camyrotate - 15)* Main_Rad), -Camdistance * sin((camyrotate)* Main_Rad) * cos((camxrotate + 15)* Main_Rad));
		if (camxrotate <= -360 || camxrotate >= 360)
			camxrotate = 0;
		if (camyrotate < -179)
			camyrotate = -179;
		else if (camyrotate > -1)
			camyrotate = -1;
	}
}
void char_by_Map_collide()
{
	if (!(Map_by_char_collide_check(Get_minmax_dot(character.get_cx(), character.get_cy(), character.get_cz(), 80, 50, 50), Get_minmax_dot(0, 0, 0, 5000, 5000, 5000))))
	{
		character.c_x -= (character.c_x - savex);
		character.c_z -= (character.c_z - savez);
		cam.c_x -= (cam.c_x - save_cx);
		cam.c_z -= (cam.c_z - save_cz);
	}//�ʰ��� �浹�Ǹ� �ǵ����� ��
}
void char_by_Tree_collide()
{
	for (int i = 0; i < TREENUM; i++) {
		if (Hex_by_Hex_collide_check(Get_minmax_dot(character.get_cx(), character.get_cy(), character.get_cz(), 80, 50, 50), Get_minmax_dot(p[i].x, p[i].y, p[i].z, 200, 30, 30))) //������ ĳ���Ͱ� �浹�Ͼ��
		{
			character.c_x -= (character.c_x - savex);
			character.c_z -= (character.c_z - savez);
			cam.c_x -= (cam.c_x - save_cx);
			cam.c_z -= (cam.c_z - save_cz);
		}
	}
}