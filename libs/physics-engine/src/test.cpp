
#include "pmframework.hpp"
#include <time.h>
#include <gl/gl.h>
#include <gl/GLU.h>
#include <GL/glut.h>
using namespace pmframework;

void initRendering()
{
    glEnable(GL_DEPTH_TEST);
}

void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, w / h, 1, 200);
}

void drawBall1()
{
    glColor3f(1, 0, 0);
    glPushMatrix();
    glTranslatef(-2, 0, -5);
    glutSolidSphere(0.4, 20, 20);
    glPopMatrix();
}

void drawBall2()
{
    glColor3f(0, 0, 1);
    glPushMatrix();
    glTranslatef(2, 0, -5);
    glutSolidSphere(0.4, 20, 20);
    glPopMatrix();
}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    drawBall1();
    drawBall2();
    glutSwapBuffers();
}
int main(int argc, char **argv)
{
    Simulation simulation(10, 10, 10);
    RigidBody *Ball1;
    scalar dx = 1;
    scalar dy = 1;
    scalar dz = 1;
    Ball1->Position(Vector3d(dx, dy, dz));
    Ball1->Mass(5);
    Matrix3x3 m;
    m(0, 0) = 3.0 / Ball1->Mass()*(dy*dy + dz*dz);
    m(1, 1) = 3.0 / Ball1->Mass()*(dx*dx + dz*dz);
    m(2, 2) = 3.0 / Ball1->Mass()*(dx*dx + dy*dy);
    Ball1->InverseBodyInertiaTensor(m);
    Ball1->Restitution(0.9);
    simulation.AddBody(Ball1);

    dx = 4;
    dy = 5;
    dz = 1;
    Ball1->Position(Vector3d(dx, dy, dz));
    Ball1->Mass(5);
    m(0, 0) = 3.0 / Ball1->Mass()*(dy*dy + dz*dz);
    m(1, 1) = 3.0 / Ball1->Mass()*(dx*dx + dz*dz);
    m(2, 2) = 3.0 / Ball1->Mass()*(dx*dx + dy*dy);
    Ball1->InverseBodyInertiaTensor(m);
    Ball1->Restitution(0.9);
    simulation.AddBody(Ball1);

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Collision window");
    initRendering();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
