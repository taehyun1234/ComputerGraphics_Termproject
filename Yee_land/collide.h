#pragma once
#include<glut.h>
//1. 점을 하나 받고 그 점 기준으로 H , W , D값을 받아 직육면체 범위를 만들어준다.
//2. 직육면체를 선으로 충돌박스를 그려서 시각적으로 보여주는 함수
//3. 직육면체끼리 충돌검사 함수
bool OnOff_collide_box = true;

struct C_Dot {
	double mx, my, mz;
	double Mx, My, Mz;
};

void Draw_collide_rect(double x, double y, double z, double h, double w, double d)
{
	if (OnOff_collide_box) {
		glPushMatrix();
		glColor3d(1, 1, 1);
		glBegin(GL_LINE_LOOP);
		glVertex3d(x + w, y - h, z + d);
		glVertex3d(x + w, y - h, z - d);
		glVertex3d(x - w, y - h, z - d);
		glVertex3d(x - w, y - h, z + d);
		glEnd();


		glBegin(GL_LINE_LOOP);
		glVertex3d(x + w, y + h, z + d);
		glVertex3d(x + w, y + h, z - d);
		glVertex3d(x - w, y + h, z - d);
		glVertex3d(x - w, y + h, z + d);
		glEnd();

		glBegin(GL_LINES);
		glVertex3d(x + w, y - h, z + d);
		glVertex3d(x + w, y + h, z + d);
		glVertex3d(x + w, y - h, z - d);
		glVertex3d(x + w, y + h, z - d);
		glVertex3d(x - w, y - h, z - d);
		glVertex3d(x - w, y + h, z - d);
		glVertex3d(x - w, y - h, z + d);
		glVertex3d(x - w, y + h, z + d);
		glEnd();
		glPopMatrix();
	}
}

C_Dot Get_minmax_dot(double x, double y, double z, double h, double w, double d)
{
	C_Dot a;

	a.mx = x - w;
	a.Mx = x + w;
	a.my = y - h;
	a.My = y + h;
	a.mz = z - d;
	a.Mz = z + d;
	return a;
}

bool Hex_by_Hex_collide_check(C_Dot a, C_Dot b) //M = Max, m =min
{
	if (a.mx > b.Mx) return false;
	if (a.Mx < b.mx) return false;
	if (a.my > b.My) return false;
	if (a.My < b.my) return false;
	if (a.mz > b.Mz) return false;
	if (a.Mz < b.mz) return false;
	return true;
}

bool Map_by_char_collide_check(C_Dot a, C_Dot b) //a= 캐릭터, b는 맵
{
	int count = 0;
	if (a.Mx < b.Mx) { count++; }
	if (a.mx > b.mx) { count++; }
	if (a.My < b.My) { count++; }
	if (a.my > b.my) { count++; }
	if (a.Mz < b.Mz) { count++; }
	if (a.mz > b.mz) { count++; }

	if (count == 6)
		return true;
	else
		return false;
}


struct Push {
	double x1, z1;
};
Push push_collide(C_Dot a, C_Dot b) //M = Max, m =min
{
	Push n; n.x1 = 0; n.z1 = 0;	
	if (a.Mx < b.Mx && a.Mx > b.mx)
		n.x1 = a.Mx - b.mx;
	if (b.Mx< a.Mx && b.Mx> a.mx)
		n.x1 = b.Mx - a.mx;
	if (a.Mz < b.Mz && a.Mz > b.mz)
		n.z1 = a.Mz - b.mz;
	if (b.Mx< a.Mx && b.Mx> a.mx)
		n.z1 = b.Mz - a.mz;
	return n;
}