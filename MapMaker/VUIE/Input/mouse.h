#include "../Elements/Element_Container.h"
#include "keys.h"

// Mouse variables
struct
{
    Position pos;

    struct
    {
        int x;
        int y;
    } rawPos;

    bool leftButton, middleButton, rightButton;

    bool scrollUp, scrollDown;

    Window *window;

} mouse;

void mouseMotion(int x, int y)
{
    int sX1 = VUIE_GL_FRAME.x;
    int sX2 = VUIE_GL_FRAME.x2;
    int sY1 = VUIE_GL_FRAME.y;
    int sY2 = VUIE_GL_FRAME.y2;

    // Update the mouse position
    mouse.rawPos.x = x;
    mouse.rawPos.y = y;
    x = (sX1 + (x));
    y = (sY2 - (y));

    x = (x + ((sign(x) * mouse.window->GlobalScale) / 2)) / mouse.window->GlobalScale;
    y = (y + ((sign(y) * mouse.window->GlobalScale) / 2)) / mouse.window->GlobalScale;
    Position_set(&mouse.pos, CARTESIAN_TYPE, x, y);
    /*
    mouse.windowPos.x = x;
    mouse.windowPos.y = window.rawSize.height - y;
    */
    // printf("Rawpos: (x: %d,y: %d)", mouse.rawPos.x, mouse.rawPos.y);
    // printf("- Tpos: (x: %d,y: %d)", sX1 + mouse.rawPos.x, sY2 - mouse.rawPos.y);
    // printf("- pos: (x: %d,y: %d)\n", x, y);
    glutPostRedisplay(); // Request a redraw
}

void mouseBtn(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            mouse.leftButton = true;
        }
        else
        {
            mouse.leftButton = false;
        }
    }

    if (button == GLUT_RIGHT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            mouse.rightButton = true;
        }
        else
        {
            mouse.rightButton = false;
        }
    }
}

void startMouse(Window *window)
{

    mouse.window = window;
    Position_set(&mouse.pos, CARTESIAN_TYPE, 0, 0);

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

    //
    glutPassiveMotionFunc(mouseMotion); // Register the passive motion callback
    glutMotionFunc(mouseMotion);        // Register the active motion callback
    glutMouseFunc(mouseBtn);            //
}