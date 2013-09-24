#include <GL/freeglut.h>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <iostream>
#include <cassert>
#ifdef _MSC_VER
#include <crtdbg.h>
#endif

#ifndef LINE
#define LINE 0
#endif

#ifndef CIRCLE
//#define CIRCLE 1
#endif

#ifndef ELIPSE
//#define ELIPSE 2
#endif

using namespace std;
//Initialize OpenGL
void init(void) {
    glClearColor(1, 1, 1, 0);

    glViewport(0, 0, 500, 500);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    glOrtho(0, 500, 0, 500, 1, -1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
#ifdef LINE
void drawLines(void) {//dibujo de linea
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.4,0.4,0.7);
    glPointSize(3.0);

    glBegin(GL_LINES);//Linea dibujada
    glVertex2d(180, 15);
    glVertex2d(10, 145);
    glEnd();
    glFlush();
}
#endif
/**/
#ifdef CIRCLE
void drawLines(void) { //dibujo de circulo
    float PI=3.1415926535897932384626433832795;
    float x,y;
    float radius = 0.5f;
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.4,0.4,0.7);
    glPointSize(3.0);

    glBegin(GL_LINES);
    x = (float)radius * cos(359 * PI/180.0f)*180+360;
    y = (float)radius * sin(359 * PI/180.0f)*180+360;
    for(int j = 0; j < 360; j++)    {
        glVertex2d(x,y);
        x = (float)radius * cos(j * PI/180.0f)*180+360;
//        std::cout<<"x: "<<x<<endl;

        y = (float)radius * sin(j * PI/180.0f)*180+360;
//        std::cout<<"y: "<<y<<endl;
        glVertex2d(x,y);
    }
    glEnd();
    glFlush();
}

#endif
/**/

#ifdef ELIPSE
void drawEllipse(float xc, float yc, float x, float y)
{
    int p1[] = {(int)xc+x, (int)yc+y};
    int p2[] = {(int)xc-x, (int)yc+y};
    int p3[] = {(int)xc+x, (int)yc-y};
    int p4[] = {(int)xc-x, (int)yc-y};
    glVertex2iv(p1);
    glVertex2iv(p2);
    glVertex2iv(p3);
    glVertex2iv(p4);
}

void ellipseMidpoint(float xc, float yc, float rx, float ry)
{
    float rxSq = rx * rx;
    float rySq = ry * ry;
    float x = 0, y = ry, p;
    float px = 0, py = 2 * rxSq * y;
    drawEllipse(xc, yc, x, y);

    p = rySq - (rxSq * ry) + (0.25 * rxSq);
    while (px < py)
    {
        x++;
        px = px + 2 * rySq;
        if (p < 0)
            p = p + rySq + px;
        else
        {
            y--;
            py = py - 2 * rxSq;
            p = p + rySq + px - py;
        }
        drawEllipse(xc, yc, x, y);
    }

    p = rySq*(x+0.5)*(x+0.5) + rxSq*(y-1)*(y-1) - rxSq*rySq;
    while (y > 0)
    {
        y--;
        py = py - 2 * rxSq;
        if (p > 0)
            p = p + rxSq - py;
        else
        {
            x++;
            px = px + 2 * rySq;
            p = p + rxSq - py + px;
        }
        drawEllipse(xc, yc, x, y);
    }
}

void drawLines(void) {//dibujo de linea
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.4,0.4,0.7);
    glPointSize(3.0);

    glBegin(GL_LINES);//Linea dibujada
    ellipseMidpoint(250, 250, 100, 100);
    glEnd();
    glFlush();
}
#endif
/**/

int main(int argc, char**argv) {
    glutInit(&argc, argv);
    glutInitWindowPosition(10,10);
#ifdef   ELIPSE
    glutInitWindowSize(700,500);
#else
    glutInitWindowSize(700,700);
#endif
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutCreateWindow("Proyecto Formas");
    init();
    glutDisplayFunc(drawLines);
    glutMainLoop();
}
