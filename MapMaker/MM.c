#include <stdbool.h>
#include <string.h>

#include "VUIE/vuie.h"

// <<<<<<<<<<' Debug '>>>>>>>>>>

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

// <.------------------.>
// #---------------------------------------------------------------------------------------------------------------#
// <<<<<<<<<<' Global Variables '>>>>>>>>>>

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

void setColor(Color *col)
{
    if (col->type == ID_TYPE)
    {
        if (col->id == 0)
        {
            glColor3f(1.0, 1.0, 0.0);
        } // Yellow
        if (col->id == 1)
        {
            glColor3f(0.63, 0.63, 0.0);
        } // Yellow darker
        if (col->id == 2)
        {
            glColor3f(0.0, 1.0, 0.0);
        } // Green
        if (col->id == 3)
        {
            glColor3f(0.0, 0.63, 0.0);
        } // Green darker
        if (col->id == 4)
        {
            glColor3f(0.0, 1.0, 1.0);
        } // Cyan
        if (col->id == 5)
        {
            glColor3f(0.0, 0.63, 0.63);
        } // Cyan darker
        if (col->id == 6)
        {
            glColor3f(0.0, 0.0, 1.0);
        } // Blue
        if (col->id == 7)
        {
            glColor3f(0.0, 0.0, 0.63);
        } // Blue darker
        if (col->id == 8)
        {
            glColor3f(1.0, 0.0, 1.0);
        } // Magenta
        if (col->id == 9)
        {
            glColor3f(0.63, 0.0, 0.63);
        } // Magenta darker
        if (col->id == 10)
        {
            glColor3f(1.0, 0.0, 0.0);
        } // Red
        if (col->id == 11)
        {
            glColor3f(0.63, 0.0, 0.0);
        } // Red darker
        if (col->id == 12)
        {
            glColor3f(1.0, 1.0, 1.0);
        } // White
    }
    else if (col->type == RGB_TYPE)
    {
        glColor3f(col->rgb.r, col->rgb.g, col->rgb.b);
    }
    else if (col->type == HSV_TYPE)
    {
        glColor3f(col->hsv.h, col->hsv.s, col->hsv.v);
    }
}
// #---------------------------------------------------------------------------------------------------------------#
// <<<<<<<<<<' Inicialization '>>>>>>>>>>

Container exampleBox;

void containerInit()
{
    printf("Inicializing Container...\n");
    make_VUIE_Container(&exampleBox);

    printf("Inicializing Container Values...\n");
    exampleBox.transform.pos.cartesian.x = 20;
    exampleBox.transform.pos.cartesian.y = 20;
    exampleBox.transform.pos.type = CARTESIAN_TYPE;

    exampleBox.transform.size.rect.width = 300;
    exampleBox.transform.size.rect.height = 300;
    exampleBox.transform.size.type = RECT_TYPE;

    exampleBox.draw = true;
    exampleBox.drawSelf = true;
}

void init()
{
    printf("Inicialized\n");
    startWindow("Map Maker");
    startMouse();
    glClearColor(0.0, 0.0, 0.0, 0.0); // Set the background color to black

    containerInit();
    printf("Container Inicialized Succesfully!\n");
}

// <.----------------.>
// #---------------------------------------------------------------------------------------------------------------#
// <<<<<<<<<<' Input '>>>>>>>>>>

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

// <.----------------.>
// #---------------------------------------------------------------------------------------------------------------#
// <<<<<<<<<<' UI '>>>>>>>>>>

// <.-----------------.>
// #---------------------------------------------------------------------------------------------------------------#
// <<<<<<<<<<' Display Funtion '>>>>>>>>>>

void display()
{
    glClear(GL_COLOR_BUFFER_BIT); // Clear the screen

    // Draw the container
    printf("Container.draw = %s\n", exampleBox.draw ? "true" : "false");
    if (exampleBox.draw)
    {
        exampleBox._draw(&exampleBox);
    }

    // Draw a point at the mouse position
    setColor(RGBColor(1.0, 0.0, 0.0));
    // glColor3f(1.0, 0.0, 0.0); // Set the color to red
    glBegin(GL_POINTS);
    glVertex2f(mouse.pos.x, mouse.pos.y);
    glEnd();

    glutSwapBuffers(); // Swap the buffers to display the scene
}

// <.----------------.>
// #---------------------------------------------------------------------------------------------------------------#
// <<<<<<<<<<' Main '>>>>>>>>>>

int main(int argc, char *argv[])
{

    printf("Hello, World!\n");

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