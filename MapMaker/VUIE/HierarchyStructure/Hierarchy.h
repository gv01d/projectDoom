
#include "DataStructures.h"
/*
    TODO : Make so i can add new structures without changing the base library
    EXAMPLE :
        some int with amount of data structures
        some array with all of the types of functions to each data structure
*/

typedef struct Hierarchy
{
    Node *self;
    Node *parent;

    int type;
    void *dataStructure;

} Hierarchy;

void setParent(Hierarchy *nodeDataStructure, Node *parent)
{
    nodeDataStructure->parent = parent;
}
void setDataStructure(Hierarchy *nodeDataStructure, int type)
{
    nodeDataStructure->type = type;
    hierarchy_init(nodeDataStructure);
}
// ------------------------------------------------------------------------------------------------------------
void hierarchy_init(Hierarchy *nodeDataStructure)
{
    nodeDataStructure->type = ARRAY_TYPE;
    GLOBAL_VUIE_DATASTRUCTURES[nodeDataStructure->type].init((void *)nodeDataStructure);
}
int getChildAmount(Hierarchy *nodeDataStructure)
{
    return GLOBAL_VUIE_DATASTRUCTURES[nodeDataStructure->type].getAmount(nodeDataStructure->dataStructure);
}
// Adds a child to the Hierarchy
void addChild(Hierarchy *nodeDataStructure, Node *node, void *pos, void *scale)
{
    GLOBAL_VUIE_DATASTRUCTURES[nodeDataStructure->type].add(nodeDataStructure->dataStructure, node, nodeDataStructure->self, pos, scale);
}
// Removes a child from the Hierarchy
void removeChild(Hierarchy *nodeDataStructure, int index)
{
    GLOBAL_VUIE_DATASTRUCTURES[nodeDataStructure->type].remove(nodeDataStructure->dataStructure, index);
}
// Removes a child from the Hierarchy by ID
void removeChildbyID(Hierarchy *nodeDataStructure, int ID)
{
    GLOBAL_VUIE_DATASTRUCTURES[nodeDataStructure->type].removebyID(nodeDataStructure->dataStructure, ID);
}
// Gets a child from the Hierarchy
Node *getChild(Hierarchy *nodeDataStructure, int index)
{
    return GLOBAL_VUIE_DATASTRUCTURES[nodeDataStructure->type].get(nodeDataStructure->dataStructure, index);
}
// Gets a child from the Hierarchy by ID
void *getChildbyID(Hierarchy *nodeDataStructure, int ID)
{
    return GLOBAL_VUIE_DATASTRUCTURES[nodeDataStructure->type].getbyID(nodeDataStructure->dataStructure, ID);
}
// Frees the Hierarchy
void freeHierarchy(Hierarchy *nodeDataStructure)
{
    GLOBAL_VUIE_DATASTRUCTURES[nodeDataStructure->type].removeAll(nodeDataStructure->dataStructure);
}
// Draws a child from the Hierarchy
void callDraw(Hierarchy *nodeDataStructure, int index)
{
    GLOBAL_VUIE_DATASTRUCTURES[nodeDataStructure->type].callDraw(nodeDataStructure->dataStructure);
}
// Draws a child from the Hierarchy by ID
void callDrawByID(Hierarchy *nodeDataStructure, int ID)
{
    GLOBAL_VUIE_DATASTRUCTURES[nodeDataStructure->type].callDrawByID(nodeDataStructure->dataStructure, ID);
}
// Draws all the Hierarchy
void drawAll(Hierarchy *nodeDataStructure)
{
    GLOBAL_VUIE_DATASTRUCTURES[nodeDataStructure->type].drawAll(nodeDataStructure->dataStructure);
}
// Processes a child from the Hierarchy
void callProcess(Hierarchy *nodeDataStructure, int index, void *args)
{
    GLOBAL_VUIE_DATASTRUCTURES[nodeDataStructure->type].callProcess(nodeDataStructure->dataStructure, index, args);
}
// Processes a child from the Hierarchy by ID
void callProcessByID(Hierarchy *nodeDataStructure, int ID, void *args)
{
    GLOBAL_VUIE_DATASTRUCTURES[nodeDataStructure->type].callProcessByID(nodeDataStructure->dataStructure, ID, args);
}
// Processes all the Hierarchy
void processAll(Hierarchy *nodeDataStructure, bool argB, void **args)
{
    GLOBAL_VUIE_DATASTRUCTURES[nodeDataStructure->type].processAll(nodeDataStructure->dataStructure, argB, args);
}