#include <GL/freeglut.h>
#include <math.h>
#include <stdbool.h>

#define PI 3.14159265

GLuint squareList; // display list

float scaleFactor = 1.0f;
float scaleStep = 0.01f; // πόσο αυξάνεται/μειώνεται κάθε frame
float rotationAngle = 0.1f;
bool scalingUp = true;

void drawCube()
{
    glPushMatrix();
    glTranslatef(0, 0, -100);          // μεταφέρει όλον τον κύβο στο (0, 0, -100)
    glRotatef(rotationAngle, 1, 1, 1); // περιστροφή γύρω από άξονα (vx, vy, vz)
    glScalef(scaleFactor, scaleFactor, scaleFactor); // ομαλή αυξομείωση μεγέθους

    // TODO change length to 7
    // TODO comments

    // front face
    glPushMatrix();
    glTranslatef(0, 0, 1);
    glRotatef(90, 0, 1, 0);   // "ξεστραβώνει" το τετράγωνο από το x=y προς XY
    glRotatef(45, 0, 0, 1);   // "ξεστραβώνει" το τετράγωνο από το x=y προς XY
    glColor3f(1.0, 0.0, 0.0); // κόκκινη
    // glScalef(halfEdge, halfEdge, 1);
    glCallList(squareList);
    glPopMatrix();

    // back face
    glPushMatrix();
    glTranslatef(0, 0, -1);
    glRotatef(90, 0, 1, 0);   // "ξεστραβώνει" το τετράγωνο από το x=y προς XY
    glRotatef(45, 0, 0, 1);   // "ξεστραβώνει" το τετράγωνο από το x=y προς XY
    glColor3f(0.0, 1.0, 0.0); // πράσινη
    // glScalef(halfEdge, halfEdge, 1);
    glCallList(squareList);
    glPopMatrix();

    // above face
    glPushMatrix();
    glTranslatef(0, 1, 0);
    glRotatef(90, 0, 1, 0);   // "ξεστραβώνει" το τετράγωνο από το x=y προς XY
    glRotatef(-45, 0, 0, 1);  // "ξεστραβώνει" το τετράγωνο από το x=y προς XY
    glColor3f(0.0, 0.0, 1.0); // μπλε
    // glScalef(halfEdge, halfEdge, 1);
    glCallList(squareList);
    glPopMatrix();

    // below face
    glPushMatrix();
    glTranslatef(0, -1, 0);
    glRotatef(90, 0, 1, 0);   // "ξεστραβώνει" το τετράγωνο από το x=y προς XY
    glRotatef(-45, 0, 0, 1);  // "ξεστραβώνει" το τετράγωνο από το x=y προς XY
    glColor3f(1.0, 1.0, 0.0); // κίτρινη
    // glScalef(halfEdge, halfEdge, 1);
    glCallList(squareList);
    glPopMatrix();

    // right face
    glPushMatrix();
    glTranslatef(1, 0, 0);
    glRotatef(45, 0, 0, 1);   // "ξεστραβώνει" το τετράγωνο από το x=y προς XY
    glColor3f(1.0, 0.0, 1.0); // μωβ
    // glScalef(halfEdge, halfEdge, 1);
    glCallList(squareList);
    glPopMatrix();

    // // left face
    glPushMatrix();
    glTranslatef(-1, 0, 0);
    glRotatef(45, 0, 0, 1);   // "ξεστραβώνει" το τετράγωνο από το x=y προς XY
    glColor3f(0.0, 1.0, 1.0); // γαλάζια
    // glScalef(halfEdge, halfEdge, 1);
    glCallList(squareList);
    glPopMatrix();

    glPopMatrix();
}

void drawAxes(float length)
{
    glLineWidth(2.0f);
    glBegin(GL_LINES);

    // X - κόκκινος
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0, 0, 0);
    glVertex3f(length, 0, 0);

    // Y - πράσινος
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0, 0, 0);
    glVertex3f(0, length, 0);

    // Z - μπλε
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, length);

    glEnd();
}

void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0, 10.0, -10.0, 10.0, 1.0, 400.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST); // ενεργοποιεί το depth test, για σωστή απεικόνιση βάθους (ποιο αντικείμενο είναι μπροστά/πίσω).
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    squareList = glGenLists(1);
    glNewList(squareList, GL_COMPILE); // Ξεκινάμε την εγγραφή εντολών μέσα στη συγκεκριμένη display list. Το GL_COMPILE σημαίνει "κατασκεύασέ την τώρα για μελλοντική χρήση".

    glBegin(GL_QUADS);
    glVertex3f(1, 1, 1);
    glVertex3f(1, 1, -1);
    glVertex3f(-1, -1, -1);
    glVertex3f(-1, -1, 1);
    glEnd();

    glEndList();
}

void update(int value)
{
    rotationAngle += 1.0f;
    if (rotationAngle >= 360.0f)
        rotationAngle -= 360.0f;

    if (scalingUp)
    {
        scaleFactor += scaleStep;
        if (scaleFactor >= 2.0f)
        {
            scaleFactor = 2.0f;
            scalingUp = false;
        }
    }
    else
    {
        scaleFactor -= scaleStep;
        if (scaleFactor <= 1.0f)
        {
            scaleFactor = 1.0f;
            scalingUp = true;
        }
    }

    glutPostRedisplay();          // ζητά νέα σχεδίαση
    glutTimerFunc(16, update, 0); // επαναλαμβάνει μετά από ~16ms (~60 FPS)
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Καθαρίζει την οθόνη (χρώμα + βάθος) ώστε να ξεκινήσει νέα σχεδίαση κάθε φορά που καλείται η display().
    glLoadIdentity();

    // ορισμος σταθερής κάμερας
    gluLookAt(30, 20, 50, 0, 0, -100, 0, 1, 0);
    drawAxes(10);
    drawCube();
    glutSwapBuffers(); // double buffering
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 1000);
    // Get screen resolution
    int screenWidth = glutGet(GLUT_SCREEN_WIDTH);
    int screenHeight = glutGet(GLUT_SCREEN_HEIGHT);

    // Calculate center position
    int windowX = (screenWidth - 1000) / 2;
    int windowY = (screenHeight - 1000) / 2;

    glutInitWindowPosition(windowX, windowY);
    glutCreateWindow("Cube");

    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0); // ξεκινάει το animation
    glutMainLoop();
    return 0;
}
