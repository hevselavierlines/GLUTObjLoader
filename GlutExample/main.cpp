// ----------------------------------------------------------
// Includes
// ----------------------------------------------------------
#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <iostream>
#include <fstream>
#define GL_GLEXT_PROTOTYPES
#include <GLUT/glut.h>
#define GL_PI 3.1415
#include "Model.hpp"
#include "Camera.hpp"

using namespace std;

// ----------------------------------------------------------
// Function Prototypes
// ----------------------------------------------------------
void render();
void update(int value);
void specialKeys();
void keyboardKeys(unsigned char key, int num1, int num2);

void viewportTopLeft();
void viewportTopRight();
void viewportBottomLeft();
void viewportBottomRight();

int active = 4;
Model model1, model2, model3, model4;
Camera camera1, camera2, camera3, camera4;
// --------------------------------------------------------------
// update(int value) is the function that is called by the timer
// --------------------------------------------------------------
void update(int value) {
    model1.rotX += 1.0f;
    model2.rotY += 1.0f;
    model3.rotZ += 1.0f;
    
    glutPostRedisplay();
    glutTimerFunc(33, update, 1);
}

// ----------------------------------------------------------
// render() main drawing function
// ----------------------------------------------------------
void render(){
    //  Clear screen and Z-buffer
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    glColor3f(0.0f, 1.0f, 0.0f);
    
    //
    glLineWidth(1.0f);
    glBegin(GL_LINES);
    glVertex3f(0.0f, -100.0f, 0.0f);
    glVertex3f(0.0f, 100.0f, 0.0f);
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(-100.0f, 0.0f, 0.0f);
    glVertex3f(100.0f, 0.0f, 0.0f);
    glEnd();
    
    //top-left
    glPushMatrix();
    glTranslatef(-50.0f, 50.0f, 0.0f);
        viewportTopLeft();
    glPopMatrix();
    
    //top-right
    glPushMatrix();
    glTranslatef(50.0f, 50.0f, 0.0f);
    viewportTopRight();
    glPopMatrix();
    
    //bottom-left
    glPushMatrix();
    glTranslatef(-50.0f, -50.0f, 0.0f);
    viewportBottomLeft();
    glPopMatrix();
    
    //bottom-right
    glPushMatrix();
    glTranslatef(50.0f, -50.0f, 0.0f);
    viewportBottomRight();
    glPopMatrix();
    
    glutSwapBuffers();
}

void loadAndDraw(char * fileName)
{
    fstream inStream;
    inStream.open(fileName, ios::in);
    if (inStream.fail())
        return;
    GLint numpolys, numLines;
    inStream >> numpolys;
    for (int j = 0; j < numpolys; j++)
    {
        inStream >> numLines;
        glBegin( GL_LINE_STRIP);
        for (int i = 0; i < numLines; i++)
        {
            float x, y;
            inStream >> x >> y;
            glVertex2f(x, y);
        }
        glEnd();
    }
    inStream.close();
}

// ----------------------------------------------------------
// viewportTopLeft() draws the top - left viewport
// ----------------------------------------------------------
void viewportTopLeft() {
    if(active == 1) {
        glColor3f(1.0f, 0.0f, 0.0f);
    } else {
        glColor3f(0.0f, 1.0f, 0.0f);
    }
    camera1.render(&model1);
}

// ----------------------------------------------------------
// viewportTopRight() draws the top - right viewport
// ----------------------------------------------------------
void viewportTopRight() {
    if(active == 2) {
        glColor3f(1.0f, 0.0f, 0.0f);
    } else {
        glColor3f(0.0f, 1.0f, 0.0f);
    }
    camera2.render(&model2);
}

// ----------------------------------------------------------
// viewportBottomLeft() draws the bottom - left viewport
// ----------------------------------------------------------
void viewportBottomLeft() {
    if(active == 3) {
        glColor3f(1.0f, 0.0f, 0.0f);
    } else {
        glColor3f(0.0f, 1.0f, 0.0f);
    }
    camera3.render(&model3);
}

// ----------------------------------------------------------
// viewportBottomRight() draws the bottom - right viewport
// ----------------------------------------------------------
void viewportBottomRight() {
    if(active == 4) {
        glColor3f(1.0f, 0.0f, 0.0f);
    } else {
        glColor3f(0.0f, 1.0f, 0.0f);
    }
    camera4.render(&model4);
}

void keyboardKeys(unsigned char key, int num1, int num2) {
    Camera* activeCam = nullptr;
    switch(active) {
        case 1:
            activeCam = &camera1;
            break;
        case 2:
            activeCam = &camera2;
            break;
        case 3:
            activeCam = &camera3;
            break;
        default:
            activeCam = &camera4;
    }
    if(key == 'w') {
        activeCam->position.z += 1.0f;
    } else if(key == 's') {
        activeCam->position.z -= 1.0f;
    } else if(key == 'a') {
        activeCam->position.x -= 1.0f;
    } else if(key == 'd') {
        activeCam->position.x += 1.0f;
    } else if(key == 'e') {
        activeCam->position.y += 1.0f;
    } else if(key == 'q') {
        activeCam->position.y -= 1.0f;
    } else if(key == '\t') {
        active += 1;
        if(active > 4) {
            active = 1;
        }
    } else if(key == '1') {
        active = 1;
    } else if(key == '2') {
        active = 2;
    } else if(key == '3') {
        active = 3;
    } else if(key == '4') {
        active = 4;
    }
    glutPostRedisplay();
}

void specialKeys(int key, int x, int y) {
    int xRot = 0, yRot = 0, zRot = 0;
    
    xRot = (key == GLUT_KEY_UP) ? -1 : xRot;
    xRot = (key == GLUT_KEY_DOWN) ? 1 : xRot;
    yRot = (key == GLUT_KEY_LEFT) ? -1 : yRot;
    yRot = (key == GLUT_KEY_RIGHT) ? 1 : yRot;
    
    zRot = (key == GLUT_KEY_PAGE_UP) ? -1 : zRot;
    zRot = (key == GLUT_KEY_PAGE_DOWN) ? 1 : zRot;
    
    model4.rotX += xRot;
    model4.rotY += yRot;
    model4.rotZ += zRot;
    
    glutPostRedisplay();
}

void setupRC(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    
    gluPerspective(60.0f, 1, 50.0, 400.0);
    //glOrtho(-100.0f, 100.0f, -100.0f, 100.0f, -100.0f, 100.0f);
    glTranslatef(0, 0, -100.0f);
    
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_FILL);
    glShadeModel(GL_FLAT);
    
    model4.mode = 1;
}

// ----------------------------------------------------------
// main() function
// ----------------------------------------------------------
int main(int argc, char* argv[]){
    
    //  Initialize GLUT and process user parameters
    glutInit(&argc,argv);
    
    //  Request double buffered true color window with Z-buffer
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    // Create window
    glutCreateWindow("OBJLoader");
    
    //  Enable Z-buffer depth test
    glEnable(GL_DEPTH_TEST);
    
    // Callback functions
    glutDisplayFunc(render);
    glutSpecialFunc(specialKeys);
    glutKeyboardFunc(keyboardKeys);
    glutTimerFunc(33, update, 1);
    
    model1.load("/Users/Afaci/Documents/FHBachelor/iOS/jonas/GlutA2/GlutExample/horse.obj");
    model2 = model1;
    model3 = model1;
    model4 = model1;
    setupRC();
    //  Pass control to GLUT for events
    glutMainLoop();
    
    
    
    //  Return to OS
    return 0;
    
}