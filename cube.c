#include <GL/freeglut.h>
#include <math.h>

#define PI 3.14159265

GLuint squareList; // display list

float camAngle = 0.0f; // γωνία κάμερας σε μοίρες

void drawCube()
{
    glPushMatrix();
    glTranslatef(0, 0, -100); // μεταφέρει όλον τον κύβο στο (0, 0, -100)
    // TODO change length to 7

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

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Καθαρίζει την οθόνη (χρώμα + βάθος) ώστε να ξεκινήσει νέα σχεδίαση κάθε φορά που καλείται η display().
    glLoadIdentity();

    float radius = 20.0f;
    float camX = radius * sin(camAngle * PI / 180.0f);
    float camZ = radius * cos(camAngle * PI / 180.0f);

    // ορισμος καμερας
    // Κινείται κυκλικά γύρω από τον κύβο
    gluLookAt(camX, 10, camZ - 100, 0, 0, -100, 0, 1, 0);
    // glRotatef(45, 1, 1, 1); // περιστροφή και ως προς τον z για πιο "στριμμένη" γωνία
    drawAxes(10);
    drawCube();
    glutSwapBuffers(); // double buffering
}

void update(int value)
{
    camAngle += 1.0f;
    if (camAngle >= 360.0f)
        camAngle -= 360.0f;

    glutPostRedisplay();          // ζητά επανασχεδίαση
    glutTimerFunc(16, update, 0); // επανάκληση ~60 FPS
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
    glutTimerFunc(0, update, 0); // ξεκινάμε το animation
    glutMainLoop();
    return 0;
}
