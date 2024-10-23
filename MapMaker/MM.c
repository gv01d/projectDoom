#include <GL/glut.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// <' Global Variables '>

// Debug

#define DEBUG 1

#if defined(DEBUG) && DEBUG > 0
#define DEBUG_PRINT(fmt, args...) fprintf(stderr, "DEBUG: %s:%d:%s(): " fmt, \
                                          __FILE__, __LINE__, __func__, ##args)
#if DEBUG == 2
#define DEBUG_PRINT_MOUSE(fmt, args...) fprintf(stderr, "DB_MOUSE: %s:%d:%s(): " fmt, \
                                                __FILE__, __LINE__, __func__, ##args)
#elif DEBUG == 3
#define DEBUG_PRINT_3(fmt, args...) fprintf(stderr, "DB_2: %s:%d:%s(): " fmt, \
                                            __FILE__, __LINE__, __func__, ##args)
#elif DEBUG == 5
#define DEBUG_PRINT_MOUSE(fmt, args...) fprintf(stderr, "DB_MOUSE: %s:%d:%s(): " fmt, \
                                                __FILE__, __LINE__, __func__, ##args)
#define DEBUG_PRINT_3(fmt, args...) fprintf(stderr, "DB_2: %s:%d:%s(): " fmt, \
                                            __FILE__, __LINE__, __func__, ##args)
#endif
#endif
#if !defined(DEBUG_PRINT)
#define DEBUG_PRINT(fmt, args...) /* Don't do anything in release builds */
#endif
#if !defined(DEBUG_PRINT_MOUSE)
#define DEBUG_PRINT_MOUSE(fmt, args...) /* Don't do anything in release builds */
#endif
#if !defined(DEBUG_PRINT_3)
#define DEBUG_PRINT_3(fmt, args...) /* Don't do anything in release builds */
#endif

// Window variables
struct
{
    int PixelScale;
    struct
    {
        int width;
        int height;
    } rawSize;
    struct
    {
        int width;
        int height;
    } size;
    struct
    {
        int x;
        int y;
    } pos;
    char *name;
} window;

void startWindow(char *name)
{
    window.PixelScale = 10;
    window.rawSize.width = 1600;
    window.rawSize.height = 900;
    window.size.width = window.rawSize.width / window.PixelScale;
    window.size.height = window.rawSize.height / window.PixelScale;
    window.pos.x = 0;
    window.pos.y = 0;
    if (window.name != NULL)
    {
        free(window.name);
    }
    window.name = (char *)malloc((strlen(name) + 1) * sizeof(char));
    strncpy(window.name, name, strlen(name) + 1);
}

// Mouse variables
struct
{
    struct
    {
        int x;
        int y;
    } pos;
    struct
    {
        int x;
        int y;
    } windowPos;
    struct
    {
        int x;
        int y;
    } rawPos;
    bool leftButton;
    bool rightButton;
    bool middleButton;
} mouse;

void startMouse()
{
    mouse.pos.x = 0;
    mouse.pos.y = 0;
    mouse.rawPos.x = 0;
    mouse.rawPos.y = 0;
    mouse.windowPos.x = 0;
    mouse.windowPos.y = 0;
    mouse.leftButton = false;
    mouse.rightButton = false;
    mouse.middleButton = false;
}

// <.------------------.>
// #---------------------------------------------------------------------------------------------------------------#
// <' Inicialization '>

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0); // Set the background color to black
    startWindow("Map Maker");
    startMouse();
}

// <.----------------.>
// #---------------------------------------------------------------------------------------------------------------#
// Mouse motion callback function

void mouseMotion(int x, int y)
{
    // Update the mouse position
    mouse.pos.x = (x + (window.PixelScale / 2)) / window.PixelScale;
    mouse.pos.x *= window.PixelScale;
    mouse.pos.y = (window.rawSize.height - (y - (window.PixelScale / 2))) / window.PixelScale;
    mouse.pos.y *= window.PixelScale;
    mouse.windowPos.x = x;
    mouse.windowPos.y = window.rawSize.height - y;
    mouse.rawPos.x = x;
    mouse.rawPos.y = y;

    // Print the mouse position for debugging
    DEBUG_PRINT_MOUSE("Mouse Position: (%d, %d)\n", mouse.pos.x, mouse.pos.y);
    glutPostRedisplay(); // Request a redraw
}

// Idle function to continuously update the display
void idle()
{
    glutPostRedisplay(); // Request a redraw
}

// <.-----------------.>
// #---------------------------------------------------------------------------------------------------------------#
// <' Display Funtion '>

void display()
{
    glClear(GL_COLOR_BUFFER_BIT); // Clear the screen

    // Draw a point at the mouse position
    glColor3f(1.0, 0.0, 0.0); // Set the color to red
    glBegin(GL_POINTS);
    glVertex2f(mouse.pos.x, mouse.pos.y);
    glEnd();

    glutSwapBuffers(); // Swap the buffers to display the scene
}
// <.----------------.>

int main(int argc, char *argv[])
{
    init();
    DEBUG_PRINT("Debugging is enabled.\n");
    DEBUG_PRINT("Debug level: %d", (int)DEBUG);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(window.rawSize.width, window.rawSize.height);
    glutCreateWindow(window.name);
    glPointSize(window.PixelScale);                                // pixel size
    gluOrtho2D(0, window.rawSize.width, 0, window.rawSize.height); // origin bottom left
    glutDisplayFunc(display);
    glutPassiveMotionFunc(mouseMotion); // Register the passive motion callback
    glutMotionFunc(mouseMotion);        // Register the active motion callback
    glutIdleFunc(idle);                 // Register the idle function
    glutMainLoop();
    return 0;
}