#include<glut.h>
#include<stdio.h>
#include <gl\GL.h>
#define FPS 1
#define TPS 2
#pragma once
#ifndef Camera

class Camera
{
private:
	
public:
	double c_x, c_y, c_z;
	double v_x, v_y, v_z;
	double cm_x, cm_y, cm_z;
	double boss_x, boss_y, boss_z;
	int time;
	int View_Port;
	Camera()
	{
		/*
		float camxrotate = 0, camyrotate = -90, Viewx = 0, Viewy = 0, Viewz = -1000, Camx, Camy, Camz;
		float Charx = 0, Chary = 20, Charz = 100; // 캐릭터의 처음 좌표 : 0,40,100
		float nx = 0, ny = 0;
		*/
		c_x = 0;
		c_y = 20;
		c_z = 100;
		v_x = 0;
		v_y = 0;
		v_z = -100;
	}
	void init()
	{
		c_x = 0;
		c_y = 20;
		c_z = 100;
		v_x = 0;
		v_y = 0;
		v_z = -100;
	}
	void timer()
	{
		time++;
	}
	void set_cam_coordinate() 
	{
		c_x = 0;
		c_y = 20;
		c_z = 100;
		v_x = 0;
		v_y = 0;
		v_z = -100;
	}
	void set_cam(double x,double y,double z)
	{
		c_x = x;
		c_y = y;
		c_z = z;
	}
	void set_babo_cam()
	{
		c_x -= 10;
		c_y = 20;
		c_z -=10;
		v_x -= 10;
		v_z -= 10;
	}
	void Change_Char(double x, double y, double z) // 캐릭터에 따라 카메라도 이동하도록.
	{
		c_x += x;
		c_y += y;
		c_z += z;
	}
	void Change_View(double x, double y, double z)
	{
		v_x = x;
		v_y = y;
		v_z = z;
	}
	void Change_cam(double x, double y, double z)
	{
		cm_x = x;
		cm_y = y;
		cm_z = z;
	}
	void Change_ViewPort()
	{
		if (View_Port == FPS)
		{
			View_Port = TPS;
		}
		else
		{
			View_Port = FPS;
		}
	}
	int returnView()
	{
		return View_Port;
	}
	void Draw_scene()
	{
		glLoadIdentity();

		if (View_Port == FPS) {
			glTranslatef(0, -70, 40);
			gluLookAt(c_x, c_y+80, c_z, c_x + v_x, c_y + v_y, c_z + v_z, 0.0, 1.0, 0.0);
		}
		else {
			glTranslated(80, 0, -120);
			gluLookAt(c_x + cm_x, c_y + cm_y + 50, c_z + cm_z,
				c_x + v_x, c_y + v_y + 50, c_z + v_z,
				0.0, 1.0, 0.0);
		}
	}
};

#endif // !Camera
