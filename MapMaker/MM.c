#include <stdbool.h>
#include <string.h>

#include "VUIE/vuie.h"

// #---------------------------------------------------------------------------------------------------------------#
// <<<<<<<<<<' Inicialization '>>>>>>>>>>

Window mainWindow;
Container exampleBox;
Container example2;
Container c2;

void startWindow(struct Window *window)
{
    printf("Starting Window...\n");
    make_VUIE_Window(window, "MapMaker");

    window->GlobalScale = 10;
    window->rawSize.width = 1600;
    window->rawSize.height = 900;

    window->size.width = window->rawSize.width / window->GlobalScale;
    window->size.height = window->rawSize.height / window->GlobalScale;

    window->pos.x = 0;
    window->pos.y = 0;

    window->setOffsetByType(window, MIDDLE);
}

void example2Init()
{
    make_VUIE_Container(&example2);

    Position_set(&example2.transform.pos, CARTESIAN_TYPE, -20, -20);
    Size_set(&example2.transform.size, RECT_TYPE, 10, 10, 1);

    example2.setColors(&example2, RGBColor(0.1, 0.1, 1.0), RGBColor(1, 1, 1));
    example2.outlineWidth = 3;
}
//
void containerInit()
{
    make_VUIE_Container(&exampleBox);

    Position_setParent(&exampleBox.transform.pos, &mouse.pos);
    Position_set(&exampleBox.transform.pos, CARTESIAN_TYPE, 0, 0);
    Size_set(&exampleBox.transform.size, RECT_TYPE, 50, 50, 1);

    exampleBox.addChild(&exampleBox, c2.getSelf(&c2));
    c2.transform.pos.ReferToParent = false;
}
//
void c2Init()
{
    make_VUIE_Container(&c2);

    Position_setParent(&c2.transform.pos, NULL);
    Position_set(&c2.transform.pos, CARTESIAN_TYPE, 0, 0);
    c2.setColors(&c2, RGBColor(0.0, 1.0, 0.0), RGBColor(1.0, 0.0, 1.0));

    Size_set(&c2.transform.size, CIRC_TYPE, 14, 5, 1);
    // Size_set(&c2.transform.size, RECT_TYPE, 28, 28, 1);
}

//

// #---------------------------------------------------------------------------------------------------------------#
// <<<<<<<<<<' Display Funtion '>>>>>>>>>>

void idle()
{
    glutPostRedisplay(); // Request a redraw
}
int delay = 0;
bool conected = true;
bool jpW = false;
bool jpS = false;
void keyControls()
{
    if (delay > 0)
    {

        delay--;
    }
    if (keys.w && delay <= 0)
    {
        jpW = true;
        mainWindow.setScale(&mainWindow, mainWindow.GlobalScale - 1);
        delay = 10;
    }
    else if (keys.s && delay <= 0)
    {
        jpS = true;
        mainWindow.setScale(&mainWindow, mainWindow.GlobalScale + 1);
        delay = 10;
    }
}

void mouseControls()
{
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
}

void display(struct Window *window, void *args)
{
    printf("Displaying...\n");

    mouseControls();
    keyControls();

    Vector2 points[10] = {
        {mouse.pos.x, mouse.pos.y},
        {0, 0},
        {50, 0},
        {50, 30},
        {0, 30},
        {-50, 0},
        {-50, -30},
        {0, -30},
        {50, -30},
        {-50, 30}};

    Draw_Pixels(10, points, RGBColor(1.0, 1.0, 1.0), 1);

    /*
        Draw_pixel(mouse.pos.x, mouse.pos.y, RGBColor(1.0, 1.0, 1.0), 1);
        Draw_pixel(0, 0, RGBColor(1.0, 1.0, 1.0), 1);
        Draw_pixel(50, 0, RGBColor(1.0, 1.0, 1.0), 1);
        Draw_pixel(50, 30, RGBColor(1.0, 1.0, 1.0), 1);
        Draw_pixel(0, 30, RGBColor(1.0, 1.0, 1.0), 1);
        Draw_pixel(-50, 0, RGBColor(1.0, 1.0, 1.0), 1);
        Draw_pixel(-50, -30, RGBColor(1.0, 1.0, 1.0), 1);
        Draw_pixel(0, -30, RGBColor(1.0, 1.0, 1.0), 1);
        Draw_pixel(50, -30, RGBColor(1.0, 1.0, 1.0), 1);
        Draw_pixel(-50, 30, RGBColor(1.0, 1.0, 1.0), 1);
    */
}

// <.----------------.>
// #---------------------------------------------------------------------------------------------------------------#
// <<<<<<<<<<' Main '>>>>>>>>>>

int main(int argc, char *argv[])
{
    VUIE_INIT();

    startWindow(&mainWindow);

    VUIE_INIT_MAIN_WINDOW(&mainWindow);
    VUIE_WINDOW_INIT(argc, argv);

    printf("Inicialized\n");

    // Inicializing Containers
    c2Init();
    example2Init();
    containerInit();

    VUIE_ADD_ELEMENT(exampleBox.getSelf(&exampleBox));
    VUIE_ADD_ELEMENT(example2.getSelf(&example2));

    printf("Container Inicialized Succesfully!\n");

    VUIE_PROCESS(idle, display);

    return 0;
}