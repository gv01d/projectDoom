#include "Elements/Element_Container.h"
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

    //
    glutPassiveMotionFunc(mouseMotion); // Register the passive motion callback
    glutMotionFunc(mouseMotion);        // Register the active motion callback
    glutMouseFunc(mouseBtn);            //
}

void mouseMotion(int x, int y)
{
    // Update the mouse position
    mouse.rawPos.x = x;
    mouse.rawPos.y = y;
    x = (x + (window.PixelScale / 2)) / window.PixelScale;
    y = (window.rawSize.height - (y - (window.PixelScale / 2))) / window.PixelScale;
    Position_set(&mouse.pos, CARTESIAN_TYPE, x, y);
    /*
    mouse.windowPos.x = x;
    mouse.windowPos.y = window.rawSize.height - y;
    */

    // Print the mouse position for debugging
    DEBUG_PRINT_MOUSE("Mouse Position: (%d, %d)\n", mouse.pos.x, mouse.pos.y);
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