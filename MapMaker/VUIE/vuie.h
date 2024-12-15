#include "Input/mouse.h"

//

// DATA STRUCTURE FUNCTIONS
void VUIE_ADD_DEFAULT_DATASTRUCTURES()
{
    int PRIVATE_DATASTRUCTURE_AMOUNT = 1;
    GLOBAL_VUIE_DATASTRUCTURES = (DataStructure *)malloc(PRIVATE_DATASTRUCTURE_AMOUNT * sizeof(DataStructure));
    GLOBAL_VUIE_DATASTRUCTURES[0] = PRIVATE_NODEARRAY_INIT();
}
void VUIE_INIT_DEFAULT_DATASTRUCTURES()
{
    VUIE_ADD_DEFAULT_DATASTRUCTURES();
}
void VUIE_ADD_DATASTRUCTURE(DataStructure dataStructure)
{
    PRIVATE_DATASTRUCTURE_AMOUNT++;
    GLOBAL_VUIE_DATASTRUCTURES = (DataStructure *)realloc(GLOBAL_VUIE_DATASTRUCTURES, PRIVATE_DATASTRUCTURE_AMOUNT * sizeof(DataStructure));
    GLOBAL_VUIE_DATASTRUCTURES[PRIVATE_DATASTRUCTURE_AMOUNT - 1] = dataStructure;
}
// ------------------------------------------------------------------------------------------------------------

/*
    TO CREATE NEW ELEMENTS:

        Add the NODE FUNTIONS to VUIE_GLOBAL_NODE_FUNCTIONS and thats it, shiould be working fine IF you implement the functions correctly and
    add the Hierarchy structure properly

        The Funtions:
            free - free the element
            draw - Calls the Render Tree, so it should Draw the element AND call the draw funtion of the children
            process - Calls the process Tree, so it should Process the element AND call the process funtion of the children
            addParent - Adds a new parent to the element, it is impremented to acept a STRUCT POSITION pointer and a INT SCALE pointer
*/

// NODE FUNCTIONS
void VUIE_INIT_DEFAULT_NODE_FUNTIONS()
{
    VUIE_GLOBAL_NODE_FUNCTIONS_AMOUNT = 3;
    VUIE_GLOBAL_NODE_FUNCTIONS = (NodeFunctions *)malloc(VUIE_GLOBAL_NODE_FUNCTIONS_AMOUNT * sizeof(NodeFunctions));

    VUIE_GLOBAL_NODE_FUNCTIONS[0] = PRIVATE_WINDOW_NODE_FUNTIONS_INIT();
    VUIE_GLOBAL_NODE_FUNCTIONS[1] = PRIVATE_BASE_NODE_FUNTIONS_INIT();
    VUIE_GLOBAL_NODE_FUNCTIONS[2] = PRIVATE_CONTAINER_NODE_FUNTIONS_INIT();
}
void VUIE_INIT_NODE_FUNTIONS()
{
    VUIE_INIT_DEFAULT_NODE_FUNTIONS();
}
void VUIE_ADD_NODE_FUNTIONS(NodeFunctions nodeFunctions)
{
    VUIE_GLOBAL_NODE_FUNCTIONS_AMOUNT++;
    VUIE_GLOBAL_NODE_FUNCTIONS = (NodeFunctions *)realloc(VUIE_GLOBAL_NODE_FUNCTIONS, VUIE_GLOBAL_NODE_FUNCTIONS_AMOUNT * sizeof(NodeFunctions));
    VUIE_GLOBAL_NODE_FUNCTIONS[VUIE_GLOBAL_NODE_FUNCTIONS_AMOUNT - 1] = nodeFunctions;
}
// ------------------------------------------------------------------------------------------------------------

//

// OPEN GL FRAME
void PRIVATE_GL_SET_FRAME(Window *window, int x, int y, int x2, int y2)
{
    VUIE_GL_FRAME_PRESET = FRAME_CUSTOM;
    VUIE_GL_FRAME.x = x;
    VUIE_GL_FRAME.y = y;
    VUIE_GL_FRAME.x2 = x2;
    VUIE_GL_FRAME.y2 = y2;

    gluOrtho2D(VUIE_GL_FRAME.x, VUIE_GL_FRAME.x2, VUIE_GL_FRAME.y, VUIE_GL_FRAME.y2);
}

void PRIVATE_GL_SET_FRAME_BY_TYPE(Window *window, int type)
{
    VUIE_GL_FRAME_PRESET = type;
    switch (type)

    {
    case BOTTOM_RIGHT:
        VUIE_GL_FRAME.x = -window->rawSize.width;
        VUIE_GL_FRAME.y = 0;
        VUIE_GL_FRAME.x2 = 0;
        VUIE_GL_FRAME.y2 = window->rawSize.height;
        break;
    case BOTTOM_LEFT:
        VUIE_GL_FRAME.x = 0;
        VUIE_GL_FRAME.y = 0;
        VUIE_GL_FRAME.x2 = window->rawSize.width;
        VUIE_GL_FRAME.y2 = window->rawSize.height;
        break;
    case TOP_RIGHT:
        VUIE_GL_FRAME.x = -window->rawSize.width;
        VUIE_GL_FRAME.y = -window->rawSize.height;
        VUIE_GL_FRAME.x2 = 0;
        VUIE_GL_FRAME.y2 = 0;
        break;
    case TOP_LEFT:
        VUIE_GL_FRAME.x = 0;
        VUIE_GL_FRAME.y = -window->rawSize.height;
        VUIE_GL_FRAME.x2 = window->rawSize.width;
        VUIE_GL_FRAME.y2 = 0;
        break;
    case MIDDLE:
        VUIE_GL_FRAME.x = -window->rawSize.width / 2;
        VUIE_GL_FRAME.y = -window->rawSize.height / 2;
        VUIE_GL_FRAME.x2 = window->rawSize.width / 2;
        VUIE_GL_FRAME.y2 = window->rawSize.height / 2;
        break;
    default:
        break;
    }

    gluOrtho2D(VUIE_GL_FRAME.x, VUIE_GL_FRAME.x2, VUIE_GL_FRAME.y, VUIE_GL_FRAME.y2);
}
// ------------------------------------------------------------------------------------------------------------

void VUIE_setScale(Window *window, int scale)
{
    window->GlobalScale = scale;
    glPointSize(window->GlobalScale); // pixel size
    glLineWidth(window->GlobalScale);
}

void VUIE_INIT()
{
    VUIE_INIT_DEFAULT_NODE_FUNTIONS();
    VUIE_INIT_DEFAULT_DATASTRUCTURES();
    inicializar_tabelas();
}

void VUIE_CUSTOM_WINDOW_INIT(int argc, char *argv[], Window *window)
{
    glEnable(GL_LINE_WIDTH);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    //

    glutInitWindowPosition(window->pos.x, window->pos.y);              //
    glutInitWindowSize(window->rawSize.width, window->rawSize.height); //
    glutCreateWindow(window->info.name);                               //
    glPointSize(window->GlobalScale);                                  // pixel size
    glLineWidth(window->GlobalScale);                                  // line width

    //

    PRIVATE_GL_SET_FRAME_BY_TYPE(window, MIDDLE); //

    //

    Draw_SetPixelScale(&window->GlobalScale);

    window->setScale = VUIE_setScale;
}

void VUIE_CUSTOM_PROCESS(void (*idleFunc)(), void(*displayFunc), Window *window)
{
    glutDisplayFunc(displayFunc);     // Register the display function
    startMouse(window);               //
    startKeyboard();                  //
    glClearColor(0.0, 0.0, 0.0, 0.0); // Set the background color to black
                                      //
    glutIdleFunc(idleFunc);           // Register the idle function
    glutMainLoop();
}

// -------------------------------------------------------------------------------------------------------------------------

//

// MAIN WINDOW SYSTEM
struct
{
    Window *window;
} VUIE;

void PRIVATE_VUIE_DISPLAY_FUNCTION()
{
    glClear(GL_COLOR_BUFFER_BIT); // Clear the screen
    VUIE.window->_process(VUIE.window, NULL);
    Position_process(&mouse.pos);
    VUIE.window->_draw(VUIE.window);

    glutSwapBuffers(); // Swap the buffers to display the scene
}

// Assings the main window
void VUIE_INIT_MAIN_WINDOW(Window *window)
{
    VUIE.window = window;
}

// Starts the main window, Inicializing the whole OpenGL process
void VUIE_QUICKSTART_GL_BY_MAIN_WINDOW(int argc, char *argv[], void (*idleFunc)(), void (*displayFunc)(struct Window *, void *))
{
    if (VUIE.window == NULL)
    {
        printf("VUIE_MAINWINDOW is NULL\n");
        return;
    }
    VUIE_CUSTOM_WINDOW_INIT(argc, argv, VUIE.window);

    VUIE.window->_renderFunction = displayFunc;
    VUIE_CUSTOM_PROCESS(idleFunc, PRIVATE_VUIE_DISPLAY_FUNCTION, VUIE.window);
}

void VUIE_WINDOW_INIT(int argc, char *argv[])
{
    if (VUIE.window == NULL)
    {
        printf("VUIE_MAINWINDOW is NULL\n");
        return;
    }
    VUIE_CUSTOM_WINDOW_INIT(argc, argv, VUIE.window);
}

void VUIE_PROCESS(void (*idleFunc)(), void (*displayFunc)(struct Window *, void *))
{
    VUIE.window->_renderFunction = displayFunc;
    VUIE_CUSTOM_PROCESS(idleFunc, PRIVATE_VUIE_DISPLAY_FUNCTION, VUIE.window);
}

void VUIE_ADD_ELEMENT(Node *node)
{
    VUIE.window->addChild(VUIE.window, node);
}