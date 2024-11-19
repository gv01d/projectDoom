#include "Input/mouse.h"

void VUIE_INIT(int argc, char *argv[])
{
    NodeFunctions NodeFunctionsTemp[2];

    NodeFunctionsTemp[0].free = PRIVATE_NODE_BASE_FREE;
    NodeFunctionsTemp[0].draw = PRIVATE_NODE_BASE_DRAW;
    NodeFunctionsTemp[0].process = PRIVATE_NODE_BASE_PROCESS;
    NodeFunctionsTemp[0].addParent = PRIVATE_NODE_BASE_ADD_PARENT;

    NodeFunctionsTemp[1].free = PRIVATE_NODE_CONTAINER_FREE;
    NodeFunctionsTemp[1].draw = PRIVATE_NODE_CONTAINER_DRAW;
    NodeFunctionsTemp[1].process = PRIVATE_NODE_CONTAINER_PROCESS;
    NodeFunctionsTemp[1].addParent = PRIVATE_NODE_CONTAINER_ADD_PARENT;

    VUIE_inicializeNodeFunctions(NodeFunctionsTemp, 2);
    inicializar_tabelas();

    //
    glEnable(GL_LINE_WIDTH);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    //
    startWindow("MapMaker");
    glutDisplayFunc(display); //
    startMouse();
    glClearColor(0.0, 0.0, 0.0, 0.0); // Set the background color to black

    glutIdleFunc(idle); // Register the idle function
    glutMainLoop();
}