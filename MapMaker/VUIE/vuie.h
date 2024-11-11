#include "Elements/Default_ElementCreators.h"

void VUIE_INIT()
{
    NodeFunctions NodeFunctionsTemp[2];

    NodeFunctionsTemp[0].free = PRIVATE_NODE_BASE_FREE;
    NodeFunctionsTemp[0].draw = PRIVATE_NODE_BASE_DRAW;
    NodeFunctionsTemp[0].process = PRIVATE_NODE_BASE_PROCESS;

    NodeFunctionsTemp[1].free = PRIVATE_NODE_CONTAINER_FREE;
    NodeFunctionsTemp[1].draw = PRIVATE_NODE_CONTAINER_DRAW;
    NodeFunctionsTemp[1].process = PRIVATE_NODE_CONTAINER_PROCESS;

    VUIE_inicializeNodeFunctions(NodeFunctionsTemp, 2);
}