#include <iostream>
#include <math.h>
#include "LUtil.h"

int windowWidth;
int windowHeight;

float rect1x = -25.0f;
float rect1y =  25.0f;

float rect2x = -25.0f;
float rect2y = -25.0f;

GLfloat sizes[2];
GLfloat step;
GLfloat curSize;

float rotationAngle = 360;

void circlePoints();

void triangleFanFront();

void triangleFanBack();

bool initGL()
{
    //Initialize Projection Matrix
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    //Initialize Modelview Matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    //Initialize clear color
    glClearColor( 0.f, 0.f, 0.f, 1.f );

    //Check for error
    GLenum error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
        return false;
    }

    
    glGetFloatv(GL_POINT_SIZE_RANGE,sizes);
    glGetFloatv(GL_POINT_SIZE_GRANULARITY,&step);
    
    curSize = sizes[0];
    
    glPolygonMode(GL_BACK,GL_LINE);

    return true;
}

void resize(int w, int h) {
    std::cout << "Size: " << w << ", " << h << "\n";
    glViewport(0, 0, w, h);
    
    glMatrixMode( GL_PROJECTION);
    glLoadIdentity();
    
    float aspectRatio =  (float) w / (float)h;
    if (w <= h)
    {
        windowWidth = 100;
        windowHeight = 100 / aspectRatio;
        glOrtho(-100.0, 100.0, -windowHeight, windowHeight, 1.0, -1.0);
    }
    else
    {
        windowWidth = 100 * aspectRatio;
        windowHeight = 100;
        glOrtho(-windowWidth, windowWidth, -100.0, 100.0, 1.0, -1.0);
    }
}


void update()
{
}

void render()
{
    //Clear color buffer
    glClear( GL_COLOR_BUFFER_BIT );
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    
        //BACK
        glVertex2f(0.0f, 0.0f); // V0
        glVertex2f(25.0f, 25.0f); // V1
        glVertex2f(50.0f, 0.0f); // V2
    
        //FRONT
        glVertex2f(-50.0f, 0.0f); // V3
        glVertex2f(-25.0f, 0.0f); // V4
        glVertex2f(-75.0f, 50.0f); // V5
    
    glEnd();
    
    glColor3f(1.0f, 0.0f, 0.0f);
    glPushMatrix();
    glTranslatef(25.0f, -35.0f, 0.0f);
    glBegin(GL_TRIANGLE_STRIP);
        glVertex2f(0.0f, 0.0f); // V0
        glVertex2f(50.0f, 0.0f); // V1
        glVertex2f(25.0f, 25.0f); // V2
        glVertex2f(75.0f, 25.0f); // V3
        glVertex2f(50.0f, 50.0f); // V4
    glEnd();
    glPopMatrix();
    
    triangleFanBack();
    triangleFanFront();
    glutSwapBuffers();
}

void triangleFanFront() {
    static float rotation = 0.0f;
    
    glColor3f(1.0f, 0.5f, 0.0f);
    glPushMatrix();
    glTranslatef(-65.0f, -35.0f, 0.0f);
    glRotatef(rotation, 0, 0, 1);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, 0.0f, 0.0f);
    float x, y, angle, accurancy = 20;
    for(int i = accurancy; i >= 0; i-- ) {
        float colorRed = (float)i / accurancy;
        glColor3f(colorRed, 1.0f, 0.0f);
        angle = (float)i / accurancy * 2.0f * M_PI;
        
        x = 20.0f * sin(angle);
        y = 20.0f * cos(angle);
        
        glVertex2f(x, y);
    }
    glEnd();
    
    rotation += 1.0f;
    if(rotation > 360) {
        rotation = 0;
    }
    glPopMatrix();
}

void triangleFanBack() {
    static float rotation = 0.0f;
    glColor3f(1.0f, 0.5f, 0.0f);
    glPushMatrix();
    glTranslatef(-25.0f, -35.0f, 0.0f);
    glRotatef(rotation, 0, 0, 1);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, 0.0f, 0.0f);
    float x, y, angle, accurancy = 20;
    for(int i = 0; i <= accurancy; i++ ) {
        angle = (float)i / accurancy * 2.0f * M_PI;
    
        x = 20.0f * sin(angle);
        y = 20.0f * cos(angle);
        
        glVertex2f(x, y);
    }
    glEnd();
    rotation += 1.0f;
    if(rotation > 360) {
        rotation = 0;
    }
    glPopMatrix();
}
