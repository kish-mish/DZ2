#include <iostream>
#include "stdio.h"
#include <math.h>
#include "glut.h"

#define PI 3.14

using namespace std;

int b;

class point
{
public:
	float x;
	float y;
	int *arr;
};

point *p;

void render(void)
{
	glColor3f(1.0, 0.0, 0.0);
	for (int i = 0; i < b; i++)
	{
		int l = 0;
		while (p[i].arr[l] > 0)
		{
			glBegin(GL_LINES);
				glVertex2f(p[i].x*0.75, p[i].y*0.75);
				glVertex2f(p[p[i].arr[l]-1].x*0.75, p[p[i].arr[l]-1].y*0.75);
			glEnd();
			l++;
		}
		glBegin(GL_TRIANGLE_FAN);
			glVertex2f(p[i].x*0.75,p[i].y*0.75);
			for (int j = 0; j <= 50; j++) 
			{
				float a = (float)j / 50.0 * PI * 2.0;
				glVertex2f(p[i].x*0.75+cos(a) * 0.01, p[i].y*0.75+ sin(a) * 0.01);
			}
		glEnd();
	}
	glFlush();
}

int main(int argc, char **argv)
{
	cout << "How many points?" << endl;
	int f,flag;
	cin>>b;
	p = new point[b];
	float fi = (2 * PI) / b;
	float angel = 0.0;
	for (int i = 0; i < b; i++)
	{
		cout << "Enter point with which "<<i+1<<" is connected: "<<endl;
		p[i].arr = new int[b];
		p[i].x = cos(angel);
		p[i].y = sin(angel);
		int l = 0;
		while (true)
		{
			cin >> f;
			if ((f > 0) && (f <= b))
				p[i].arr[l] = f;
			else cout << "Invalid number" << endl;
			cout << "This is all?" << endl << "1-Yes\\2-No" << endl;
			while (true)
			{
				cin >> flag;
				if ((flag == 1) || (flag == 2))
					break;
				else cout << "Invalid number" << endl;
			}
			if (flag == 1)
				break;
			l++;
		}
		angel += fi;
	}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600,600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Graph");
	glClearColor(1.0, 1.0, 1.0, 0.0);	
	glClear(GL_COLOR_BUFFER_BIT);
	glutDisplayFunc(render);
	glutMainLoop();
	return 0;
}