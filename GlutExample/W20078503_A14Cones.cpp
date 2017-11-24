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
void render();
void update(int value);
void specialKeys();

void viewportTopLeft();
void viewportTopRight();
void viewportBottomLeft();
void viewportBottomRight();


// ----------------------------------------------------------
// Cone class that saves all the variabels and contains a
// draw method.
// ----------------------------------------------------------
class Cone {
public:
    float x, y, z;
    float rotX, rotY, rotZ;
    float radius;
    int mode;
    
    Cone() : x(0.0f), y(0.0f), z(50.0f), rotX(0.0f), rotY(0.0f), rotZ(0.0f), radius(20.0f), mode(0) {}
    
    void draw() {
        if(mode == 0) {
            glPolygonMode(GL_FRONT,GL_LINE);
            glPolygonMode(GL_BACK, GL_LINE);
        }
        glPushMatrix();
        glRotatef(rotX, 1.0f, 0.0f, 0.0f);
        glRotatef(rotY, 0.0f, 1.0f, 0.0f);
        glRotatef(rotZ, 0.0f, 0.0f, 1.0f);
        
        glBegin(GL_TRIANGLE_FAN);
        int step = 0, accurancy = 16;
        
        glVertex3f(x, y, z);
        float angle;
        for(int i = 0; i <= accurancy; i++)
        {
            angle = ((float)i / accurancy) * (2.0f * GL_PI);
            glColor3f(step % 2 == 0, step % 2, 0.0f);
            step++;
            x = radius*sin(angle);
            y = radius*cos(angle);
            
            glVertex2f(x, y);
        }
        glEnd();
        glPopMatrix();
        if(mode == 0) {
            glPolygonMode(GL_FRONT,GL_FILL);
            glPolygonMode(GL_BACK, GL_FILL);
        }
    }
};

Cone cone1, cone2, cone3, cone4;

// --------------------------------------------------------------
// update(int value) is the function that is called by the timer
// --------------------------------------------------------------
void update(int value) {
    cone1.rotX += 1.0f;
    cone2.rotY += 1.0f;
    cone3.rotZ += 1.0f;
    
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

// ----------------------------------------------------------
// viewportTopLeft() draws the top - left viewport
// ----------------------------------------------------------
void viewportTopLeft() {
    cone1.draw();
}

// ----------------------------------------------------------
// viewportTopRight() draws the top - right viewport
// ----------------------------------------------------------
void viewportTopRight() {
    cone2.draw();
}

// ----------------------------------------------------------
// viewportBottomLeft() draws the bottom - left viewport
// ----------------------------------------------------------
void viewportBottomLeft() {
    cone3.draw();
}

// ----------------------------------------------------------
// viewportBottomRight() draws the bottom - right viewport
// ----------------------------------------------------------
void viewportBottomRight() {
    cone4.draw();
}

void specialKeys(int key, int x, int y) {
    int xRot = 0, yRot = 0, zRot = 0;
    
    xRot = (key == GLUT_KEY_UP) ? -1 : xRot;
    xRot = (key == GLUT_KEY_DOWN) ? 1 : xRot;
    yRot = (key == GLUT_KEY_LEFT) ? -1 : yRot;
    yRot = (key == GLUT_KEY_RIGHT) ? 1 : yRot;
    
    zRot = (key == GLUT_KEY_PAGE_UP) ? -1 : zRot;
    zRot = (key == GLUT_KEY_PAGE_DOWN) ? 1 : zRot;
    
    cone4.rotX += xRot;
    cone4.rotY += yRot;
    cone4.rotZ += zRot;
    
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
    
    cone4.mode = 1;
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
    glutCreateWindow("4Cones");
    
    //  Enable Z-buffer depth test
    //glEnable(GL_DEPTH_TEST);
    
    // Callback functions
    glutDisplayFunc(render);
    glutSpecialFunc(specialKeys);
    glutTimerFunc(33, update, 1);
    
    setupRC();
    //  Pass control to GLUT for events
    glutMainLoop();
    
    //  Return to OS
    return 0;
    
}