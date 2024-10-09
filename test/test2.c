#include <GL/glut.h> // Ensure this header is included for OpenGL functions
#include <stdbool.h> // Ensure this header is included for bool type

typedef struct
{
    int posX, posY;
    int sW, sH;
    int col, Pcol, Bcol;
    bool hold, Shold;
    bool selected, Sslct;
    int PclkRadius;
    int OffsetX, OffsetY;
    bool active;
} Parameters;

Parameters P;
int pixelScale = 10; // Define and initialize pixelScale
int GLSW = 800;      // Define and initialize GLSW (window width)
int GLSH = 600;      // Define and initialize GLSH (window height)
int SH = 600;        // Define and initialize SH (screen height)

// Function prototypes
void init()
{
    // Initialize OpenGL settings here
    glClearColor(0.0, 0.0, 0.0, 0.0); // Set the background color to black
}

void drawQuad()
{
    glColor3f(1.0, 0.0, 0.0); // Set the color to red
    glBegin(GL_QUADS);
    glVertex2f(100, 100); // Bottom left
    glVertex2f(200, 100); // Bottom right
    glVertex2f(200, 200); // Top right
    glVertex2f(100, 200); // Top left
    glEnd();
}

void drawQuadBorder()
{
    glColor3f(1.0, 1.0, 1.0); // Set the color to white
    glLineWidth(pixelScale);
    glBegin(GL_LINE_LOOP);
    glVertex2f(100, 100); // Bottom left
    glVertex2f(200, 100); // Bottom right
    glVertex2f(200, 200); // Top right
    // glVertex2f(100, 200); // Top left
    glEnd();
}

void drawPoint()
{
    glColor3f(0.0, 1.0, 0.0); // Set the color to green
    glBegin(GL_POINTS);
    glVertex2f(150, 150); // Draw point at (150, 150)
    glEnd();
}

int fr1;
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);     // Clear the screen
    fr1 = glutGet(GLUT_ELAPSED_TIME); // 1000 Milliseconds per second
    // Add your drawing code here

    // Draw a box
    drawQuad();
    drawPoint();
    drawQuadBorder();

    glutSwapBuffers(); // Swap the buffers to display the scene
    glutPostRedisplay();
}

void keysDown(unsigned char key, int x, int y)
{
    // Handle key press events here
}

void keysUp(unsigned char key, int x, int y)
{
    // Handle key release events here
}

void mouseBtn(int button, int state, int x, int y)
{
    // Handle mouse button events here
}

void mouse(int x, int y)
{
    P.posX = (x / pixelScale);
    P.posY = SH - (y / pixelScale);
    // printf("%d - %d\n", P.posX, P.posY);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(GLSW, GLSH);
    glutCreateWindow("OpenGL Window");
    glPointSize(pixelScale);      // pixel size
    gluOrtho2D(0, GLSW, 0, GLSH); // origin bottom left
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keysDown);
    glutKeyboardUpFunc(keysUp);
    glutMotionFunc(mouse);
    glutPassiveMotionFunc(mouse);
    glutMouseFunc(mouseBtn);
    glutMainLoop();
    return 0;
}