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

struct
{
    bool w;
    bool s;
} k;

void startWindow(char *name)
{
    Draw_SetPixelScale(&window.PixelScale);
    window.PixelScale = 50;
    window.rawSize.width = 1600;
    window.rawSize.height = 900;
    window.size.width = window.rawSize.width / window.PixelScale;
    window.size.height = window.rawSize.height / window.PixelScale;

    Position_set(&window.pos, CARTESIAN_TYPE, 0, 0);

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
    Position pos;

    struct
    {
        int x;
        int y;
    } rawPos;

    /*
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
    */
    bool leftButton;
    bool rightButton;
    bool middleButton;
} mouse;

void startMouse()
{
    Position_set(&mouse.pos, CARTESIAN_TYPE, 0, 0);
    Position_setParent(&mouse.pos, &window.pos);

    /*
        mouse.pos.x = 0;
        mouse.pos.y = 0;
        mouse.rawPos.x = 0;
        mouse.rawPos.y = 0;
        mouse.windowPos.x = 0;
        mouse.windowPos.y = 0;
    */
    mouse.leftButton = false;
    mouse.rightButton = false;
    mouse.middleButton = false;
}

// <.------------------.>
// #---------------------------------------------------------------------------------------------------------------#
// <<<<<<<<<<' Inicialization '>>>>>>>>>>

Container exampleBox;
Container c2;

void containerInit()
{
    printf("Inicializing Container...\n");
    make_VUIE_Container(&exampleBox);

    printf("Inicializing Container Values...\n");
    exampleBox.transform.pos.type = CARTESIAN_TYPE;
    Position_setParent(&exampleBox.transform.pos, &mouse.pos);
    Position_set(&exampleBox.transform.pos, CARTESIAN_TYPE, 0, 0);

    exampleBox.transform.size.type = RECT_TYPE;
    exampleBox.transform.size.rect.width = 30;
    exampleBox.transform.size.rect.height = 10;

    exampleBox.outlineWidth = 0;

    exampleBox.draw = true;
    exampleBox.drawSelf = true;

    exampleBox.drawChildren = true;

    exampleBox.addChild(&exampleBox, c2.getSelf(&c2));

    Node *Test = exampleBox.getChild(&exampleBox, 0);
    ((Container *)Test->element)->_draw((Container *)Test->element);

    printf("exBox.ID = %d\n", ((Container *)Test->element)->info.ID);
}

void c2Init()
{
    printf("Inicializing Container2...\n");
    make_VUIE_Container(&c2);

    printf("Inicializing Container2 Values...\n");
    c2.transform.pos.type = CARTESIAN_TYPE;
    Position_setParent(&c2.transform.pos, NULL);
    Position_set(&c2.transform.pos, CARTESIAN_TYPE, 50, -10);
    c2.setColors(&c2, RGBColor(0.0, 1.0, 0.0), RGBColor(1.0, 0.0, 1.0));

    c2.transform.size.type = CIRC_TYPE;
    c2.transform.size.circ.points = 5;
    c2.transform.size.circ.radius = 10;

    c2.outlineWidth = 0;

    c2.draw = true;
    c2.drawSelf = true;

    Node *test = c2.getSelf(&c2);

    printf("C2.ID = %d\n", ((Container *)test->element)->info.ID);
}

void init()
{
    VUIE_INIT();
    printf("Inicialized\n");
    startWindow("Map Maker");
    startMouse();
    glClearColor(0.0, 0.0, 0.0, 0.0); // Set the background color to black

    c2Init();
    containerInit();

    printf("Container Inicialized Succesfully!\n");
}

// <.----------------.>
// #---------------------------------------------------------------------------------------------------------------#
// <<<<<<<<<<' Input '>>>>>>>>>>
bool jpW = false;
bool jpS = false;
void mouseMotion(int x, int y)
{
    // Update the mouse position
    mouse.rawPos.x = x;
    mouse.rawPos.y = y;
    x = (x + (window.PixelScale / 2)) / window.PixelScale;
    x *= window.PixelScale;
    y = (window.rawSize.height - (y - (window.PixelScale / 2))) / window.PixelScale;
    y *= window.PixelScale;
    Position_set(&mouse.pos, CARTESIAN_TYPE, x, y);
    /*
    mouse.windowPos.x = x;
    mouse.windowPos.y = window.rawSize.height - y;
    */

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
    Position_process(&mouse.pos);
    // printf("mouse.global.pos : (%d, %d)\n", mouse.pos.Global.x, mouse.pos.Global.y);
    Position_process(&exampleBox.transform.pos);
    // printf("exampleBox.global.pos : (%d, %d) | Refering? : %d\n", exampleBox.transform.pos.Global.x, exampleBox.transform.pos.Global.y, exampleBox.transform.pos.ReferToParent);

    exampleBox._process(&exampleBox, NULL);
    exampleBox._draw(&exampleBox);
    // printf("Positions: ExBox : (%d, %d) | C2 : (%d, %d)\n", exampleBox.transform.pos.Global.x, exampleBox.transform.pos.Global.y, c2.transform.pos.Global.x, c2.transform.pos.Global.y);

    // Node *Test = exampleBox.getChild(&exampleBox, 0);
    //((Container *)Test->element)->_draw((Container *)Test->element);

    // VUIE_GLOBAL_NODE_FUNCTIONS[1].draw(Test);
    //  PRIVATE_NODE_CONTAINER_DRAW(Test);

    // Draw a point at the mouse position

    if (k.w)
    {
        jpW = true;
        window.PixelScale--;
        printf("PixelScale-- : %d\n", window.PixelScale);
        glPointSize(window.PixelScale); // pixel size
        glLineWidth(window.PixelScale);
    }
    else if (k.s)
    {
        jpS = true;
        window.PixelScale++;
        printf("PixelScale++ : %d\n", window.PixelScale);
        glPointSize(window.PixelScale); // pixel size
        glLineWidth(window.PixelScale);
    }

    glColor3f(1.0, 0.0, 0.0); // Set the color to red
    glBegin(GL_POINTS);
    glVertex2i(40 * window.PixelScale, 40 * window.PixelScale);
    glVertex2i(mouse.pos.x, mouse.pos.y);
    glEnd();

    glutSwapBuffers(); // Swap the buffers to display the scene
}

// <.----------------.>
// #---------------------------------------------------------------------------------------------------------------#
// <<<<<<<<<<' Main '>>>>>>>>>>
void keysDown(unsigned char key, int x, int y)
{
    if (key == 'w' == 1)
    {
        k.w = true;
    }
    if (key == 's' == 1)
    {
        k.s = true;
    }
}

void keysUp(unsigned char key, int x, int y)
{
    if (key == 'w' == 1)
    {
        k.w = false;
    }
    if (key == 's' == 1)
    {
        k.s = false;
    }
}

int main(int argc, char *argv[])
{

    init();
    DEBUG_PRINT("Debugging is enabled.\n");
    DEBUG_PRINT("Debug level: %d", (int)DEBUG);

    glEnable(GL_LINE_WIDTH);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(window.rawSize.width, window.rawSize.height); //
    glutCreateWindow(window.name);                                   //
    glPointSize(window.PixelScale);                                  // pixel size
    glLineWidth(window.PixelScale);                                  // line width
    gluOrtho2D(0, window.rawSize.width, 0, window.rawSize.height);   // origin bottom left
    glutDisplayFunc(display);                                        //
    glutKeyboardFunc(keysDown);                                      //
    glutKeyboardUpFunc(keysUp);                                      //
    glutPassiveMotionFunc(mouseMotion);                              // Register the passive motion callback
    glutMotionFunc(mouseMotion);                                     // Register the active motion callback
    glutIdleFunc(idle);                                              // Register the idle function
    glutMainLoop();
    return 0;
}