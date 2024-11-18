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
// <<<<<<<<<<' Inicialization '>>>>>>>>>>

Container exampleBox;
Container c2;

void containerInit()
{
    printf("Inicializing Container...\n");
    make_VUIE_Container(&exampleBox);

    printf("Inicializing Container Values...\n");
    Position_setParent(&exampleBox.transform.pos, &mouse.pos);
    Position_set(&exampleBox.transform.pos, CARTESIAN_TYPE, 0, 0);

    Size_set(&exampleBox.transform.size, RECT_TYPE, 30, 30, 1);

    exampleBox.outlineWidth = 0;

    exampleBox.draw = true;
    exampleBox.drawSelf = true;

    exampleBox.drawChildren = true;

    exampleBox.addChild(&exampleBox, c2.getSelf(&c2));
    c2.transform.pos.ReferToParent = true;

    // Node *Test = exampleBox.getChild(&exampleBox, 0);
    // ((Container *)Test->element)->_draw((Container *)Test->element);

    // printf("exBox.ID = %d\n", ((Container *)Test->element)->info.ID);
}

void c2Init()
{
    printf("Inicializing Container2...\n");
    make_VUIE_Container(&c2);

    printf("Inicializing Container2 Values...\n");
    Position_setParent(&c2.transform.pos, NULL);
    Position_set(&c2.transform.pos, CARTESIAN_TYPE, 15, 10);
    c2.setColors(&c2, RGBColor(0.0, 1.0, 0.0), RGBColor(1.0, 0.0, 1.0));

    Size_set(&c2.transform.size, CIRC_TYPE, 14, 5, 1);

    // Size_set(&c2.transform.size, RECT_TYPE, 28, 28, 1);

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

// <.-----------------.>
// #---------------------------------------------------------------------------------------------------------------#
// <<<<<<<<<<' Display Funtion '>>>>>>>>>>

void idle()
{
    glutPostRedisplay(); // Request a redraw
}
int delay = 0;
bool conected = true;
void display()
{
    if (delay > 0)
    {

        delay--;
    }

    glClear(GL_COLOR_BUFFER_BIT); // Clear the screen
    Position_process(&mouse.pos);
    // printf("mouse.global.pos : (%d, %d)\n", mouse.pos.Global.x, mouse.pos.Global.y);
    Position_process(&exampleBox.transform.pos);
    // printf("exampleBox.global.pos : (%d, %d) | Refering? : %d\n", exampleBox.transform.pos.Global.x, exampleBox.transform.pos.Global.y, exampleBox.transform.pos.ReferToParent);

    exampleBox._process(&exampleBox, NULL);
    exampleBox._draw(&exampleBox);
    // c2._draw(&c2);
    printf("Positions: ExBox : (%d, %d) | C2 : (%d, %d) | scale : (%d)\n", exampleBox.transform.pos.Global.x, exampleBox.transform.pos.Global.y, c2.transform.pos.Global.x, c2.transform.pos.Global.y, window.PixelScale);
    printf("C2.Points (4) : (%d, %d) | (%d, %d) | (%d, %d) | (%d, %d)\n", c2.points[0].x, c2.points[0].y, c2.points[1].x, c2.points[1].y, c2.points[2].x, c2.points[2].y, c2.points[3].x, c2.points[3].y);

    // Node *Test = exampleBox.getChild(&exampleBox, 0);
    //((Container *)Test->element)->_draw((Container *)Test->element);

    // VUIE_GLOBAL_NODE_FUNCTIONS[1].draw(Test);
    //  PRIVATE_NODE_CONTAINER_DRAW(Test);

    // Draw a point at the mouse position
    if (mouse.leftButton && conected)
    {
        printf("Disconect\n");
        Position_setParent(&exampleBox.transform.pos, NULL);
        conected = false;
    }
    else if (mouse.rightButton && !conected)
    {
        Position_setParent(&exampleBox.transform.pos, &mouse.pos);
        conected = true;
    }

    if (keys.w && delay == 0)
    {
        jpW = true;
        window.PixelScale--;
        printf("PixelScale-- : %d\n", window.PixelScale);
        glPointSize(window.PixelScale); // pixel size
        glLineWidth(window.PixelScale);
        delay = 10;
    }
    else if (keys.s && delay == 0)
    {
        jpS = true;
        window.PixelScale++;
        printf("PixelScale++ : %d\n", window.PixelScale);
        glPointSize(window.PixelScale); // pixel size
        glLineWidth(window.PixelScale);
        delay = 10;
    }

    glColor3f(1.0, 1.0, 1.0); // Set the color to red
    glBegin(GL_POINTS);
    glVertex2i(40 * window.PixelScale, 40 * window.PixelScale);
    glVertex2i(mouse.pos.x * window.PixelScale, mouse.pos.y * window.PixelScale);
    glEnd();

    glutSwapBuffers(); // Swap the buffers to display the scene
}

// <.----------------.>
// #---------------------------------------------------------------------------------------------------------------#
// <<<<<<<<<<' Main '>>>>>>>>>>

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
    glutMouseFunc(mouseBtn);                                         //
    glutIdleFunc(idle);                                              // Register the idle function
    glutMainLoop();
    return 0;
}