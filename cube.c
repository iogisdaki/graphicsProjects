#include <GL/freeglut.h>

GLuint squareList; // display list

void drawCube()
{
    float halfEdge = 7 / 2.0f; // Μισή ακμή του κύβου

    // front face
    glPushMatrix();
    glTranslatef(0, 0, halfEdge);
    glRotatef(45, 0, 0, 1);  // "ξεστραβώνει" το τετράγωνο από το x=y προς XY
    glColor3f(1.0, 0.0, 0.0); // κόκκινη
    glScalef(halfEdge, halfEdge, 1);
    glCallList(squareList);
    glPopMatrix();

    // back face
    glPushMatrix();
    glTranslatef(0, 0, -halfEdge);
    glRotatef(45, 0, 0, 1);  // "ξεστραβώνει" το τετράγωνο από το x=y προς XY
    glColor3f(0.0, 1.0, 0.0); // πράσινη
    glScalef(halfEdge, halfEdge, 1);
    glCallList(squareList);
    glPopMatrix();

    // above face
    glPushMatrix();
    glTranslatef(0, halfEdge, 0);
    glRotatef(90, 1, 0, 0);
    glRotatef(45, 0, 0, 1);  // "ξεστραβώνει" το τετράγωνο από το x=y προς XY
    glColor3f(0.0, 0.0, 1.0); // μπλε
    glScalef(halfEdge, halfEdge, 1);
    glCallList(squareList);
    glPopMatrix();

    // below face
    glPushMatrix();
    glTranslatef(0, -halfEdge, 0);
    glRotatef(90, 1, 0, 0);
    glRotatef(45, 0, 0, 1);  // "ξεστραβώνει" το τετράγωνο από το x=y προς XY
    glColor3f(1.0, 1.0, 0.0); // κίτρινη
    glScalef(halfEdge, halfEdge, 1);
    glCallList(squareList);
    glPopMatrix();

    // right face
    glPushMatrix();
    glTranslatef(halfEdge, 0, 0);
    glRotatef(90, 0, 1, 0);
    glRotatef(45, 0, 0, 1);  // "ξεστραβώνει" το τετράγωνο από το x=y προς XY
    glColor3f(1.0, 0.0, 1.0); // μωβ
    glScalef(halfEdge, halfEdge, 1);
    glCallList(squareList);
    glPopMatrix();

    // left face
    glPushMatrix();
    glTranslatef(-halfEdge, 0, 0);
    glRotatef(90, 0, 1, 0);
    glRotatef(45, 0, 0, 1);  // "ξεστραβώνει" το τετράγωνο από το x=y προς XY
    glColor3f(0.0, 1.0, 1.0); // γαλάζια
    glScalef(halfEdge, halfEdge, 1);
    glCallList(squareList);
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
    glOrtho(-10.0, 10.0, -10.0, 10.0, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST); // ενεργοποιεί το depth test, για σωστή απεικόνιση βάθους (ποιο αντικείμενο είναι μπροστά/πίσω).
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    squareList = glGenLists(1);
    glNewList(squareList, GL_COMPILE); // Ξεκινάμε την εγγραφή εντολών μέσα στη συγκεκριμένη display list. Το GL_COMPILE σημαίνει "κατασκεύασέ την τώρα για μελλοντική χρήση".

    glBegin(GL_QUADS);      
    glVertex3f(1, 1, 1);   
    glVertex3f(1, 1, -1);   
    glVertex3f(-1, -1, 1); 
    glVertex3f(-1, -1, -1); 
    glEnd();

    glEndList();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Καθαρίζει την οθόνη (χρώμα + βάθος) ώστε να ξεκινήσει νέα σχεδίαση κάθε φορά που καλείται η display().
    glLoadIdentity();
    // ορισμος καμερας
    // Βρίσκεται στο σημείο (0, 0, 6)
    // Κοιτάζει προς το (0, 0, 0)
    // Το "πάνω" της είναι προς τον άξονα y (δηλαδή κάθετα)
    gluLookAt(10, 0, 20, 0, 0, 0, 0, 1, 0);
    // glRotatef(45, 1, 1, 1); // περιστροφή και ως προς τον z για πιο "στριμμένη" γωνία
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
    glutMainLoop();
    return 0;
}
