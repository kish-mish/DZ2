#include <iostream>
#include "stdio.h"
#include <math.h>
#include "glut.h"

#define PI 3.14159

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
int *pre;

void render(void)
{
	glColor3f(1.0, 0.0, 0.0);
	for (int i = 0; i < b; i++)
	{
		int l = 0;
		while (p[i].arr[l] != -1)
		{
			glBegin(GL_LINES);
				glVertex2f(p[i].x*0.75, p[i].y*0.75);
				glVertex2f(p[p[i].arr[l]].x*0.75, p[p[i].arr[l]].y*0.75);
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

bool search(int *arr,int n)
{
	for (int i = 0; i < b; i++)
	{
		if (arr[i] == n)
			return true;
	}
	return false;
}

void connected(int n,int k)
{
	int flag;
	for (int i = 0; i < n; i++)
	{
		if (p[k].arr[i] != -1)
		{
			flag = 0;
			for (int j=0;j<n;j++)
				if (pre[j]==p[k].arr[i])
				{
					flag = 1;
					break;
				}
			if (flag != 1)
			{
				for (int j = 0; j < n; j++)
					if (pre[j] == -1)
					{
						pre[j] = p[k].arr[i];
						break;
					}
				connected(n, p[k].arr[i]);
			}
		}
	}
}

int main(int argc, char **argv)
{
	cout << "How many points?" << endl;
	int f,flag,k;
	cin>>b;
	p = new point[b];
	pre = new int[b];
	float fi = (2 * PI) / b;
	float angel = 0.0;
	for (int i = 0; i < b; i++)
	{
		p[i].arr = new int[b];
		for(int j=0;j<b;j++)
			p[i].arr[j] =  -1 ;
	}
	for (int j = 0; j<b; j++)
		pre[j] = -1;
	for (int i = 0; i < b; i++)
	{
		cout << "Enter point with which "<<i+1<<" is connected: "<<endl;
		p[i].x = cos(angel);
		p[i].y = sin(angel);
		int l;
		for (l = 0; l < b; l++)
		{
			if (p[i].arr[l] == -1)
				break;
		}
		while (true)
		{
			cin >> f;
			f--;
			if ((f >= 0) && (f < b) && (f != i))
			{
				if (search(p[i].arr, f))
					cout << "This number is available" << endl;
				else
				{
					p[i].arr[l] = f;
					for (int j = 0; j < b; j++)
					{
						if (p[f].arr[j] == -1)
						{
							p[f].arr[j] = i;
							break;
						}
					}
					l++;
				}
			}
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
		}
		angel += fi;
	}
	pre[0] = 0;
	int count = 0;
	connected(b, 0);
	for (int i = 0; i < b; i++)
	{
		if (pre[i] != -1)
			count++;
	}
	if (count == b)
		cout << "Graph is connected" << endl;
	else cout << "Graph is not connected" << endl;
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