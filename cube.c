#include <GL/freeglut.h>

GLuint squareList; // display list

void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST); // ενεργοποιεί το depth test, για σωστή απεικόνιση βάθους (ποιο αντικείμενο είναι μπροστά/πίσω).
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    squareList = glGenLists(1);
    glNewList(squareList, GL_COMPILE); // Ξεκινάμε την εγγραφή εντολών μέσα στη συγκεκριμένη display list. Το GL_COMPILE σημαίνει "κατασκεύασέ την τώρα για μελλοντική χρήση".

    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_QUADS);      // σχεδιαση τετραπλευρου
    glVertex3f(1, 1, 1);    // κορυφή 1
    glVertex3f(1, 1, -1);   // κορυφή 2
    glVertex3f(-1, -1, -1); // κορυφή 3
    glVertex3f(-1, -1, 1);  // κορυφή 4
    glEnd();

    glEndList();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Καθαρίζει την οθόνη (χρώμα + βάθος) ώστε να ξεκινήσει νέα σχεδίαση κάθε φορά που καλείται η display().
    glLoadIdentity();                                   // μηδενίζει" μετασχηματισμούς πριν τη σχεδίαση

    // ορισμος καμερας
    // Βρίσκεται στο σημείο (0, 0, 6)
    // Κοιτάζει προς το (0, 0, 0)
    // Το "πάνω" της είναι προς τον άξονα y (δηλαδή κάθετα)
    glLoadIdentity();
    gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0); // πρώτα ορίζεις την κάμερα
    glRotatef(45, 1, 1, 0);                // μετά εφαρμόζεις περιστροφή
    glCallList(squareList);
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
