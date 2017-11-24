// ----------------------------------------------------------
// Includes
// ----------------------------------------------------------
#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#define GL_GLEXT_PROTOTYPES
#include <GLUT/glut.h>
#define GL_PI 3.1415

// ----------------------------------------------------------
// Function Prototypes
// ----------------------------------------------------------
void display();
void specialKeys();

void drawCone(float x, float y, float z, float radius)
{
    glBegin(GL_TRIANGLE_FAN);
    int step = 0;
    
    glVertex3f(x, y, z);
    float angle;
    for (angle = 0.0f; angle < (2.0f*GL_PI); angle += (GL_PI / 8.0f))
    {
        glColor3f(step % 2 == 0, step % 2, 0.0f);
        step++;
        x = radius*sin(angle);
        y = radius*cos(angle);
        
        glVertex2f(x, y);
    }
    glEnd();
}


// ----------------------------------------------------------
// display() Callback function
// ----------------------------------------------------------
void render(){
    
    //  Clear screen and Z-buffer
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    glFrontFace(GL_CW);
    drawCone(0,0,75, 50);
    glFrontFace(GL_CCW);
    drawCone(0,0,0, 50);
    
    glutSwapBuffers();
}

void specialKeys(int key, int x, int y) {
    int xRot = 0, yRot = 0;
    
    xRot = (key == GLUT_KEY_UP) ? -1 : xRot;
    xRot = (key == GLUT_KEY_DOWN) ? 1 : xRot;
    yRot = (key == GLUT_KEY_LEFT) ? -1 : yRot;
    yRot = (key == GLUT_KEY_RIGHT) ? 1 : yRot;
    
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    
    glutPostRedisplay();
}

void setupRC(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glOrtho(-100.0f, 100.0f, -100.0f, 100.0f, -100.0f, 100.0f);
    
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_FILL);
    glShadeModel(GL_FLAT);
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
    glutCreateWindow("Awesome Cube");
    
    //  Enable Z-buffer depth test
    //glEnable(GL_DEPTH_TEST);
    
    // Callback functions
    glutDisplayFunc(render);
    glutSpecialFunc(specialKeys);
    
    setupRC();
    //  Pass control to GLUT for events
    glutMainLoop();
    
    //  Return to OS
    return 0;
    
}