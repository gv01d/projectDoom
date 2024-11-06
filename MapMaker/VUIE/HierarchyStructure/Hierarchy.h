#include "NodeArray.h"
/*
    TODO : Make so i can add new structures without changing the base library
    EXAMPLE :
        some int with amount of data structures
        some array with all of the types of functions to each data structure

        typedef struct datastructure
        {
            int type;
            char *name;

            // Add
            void (*add)(struct Hierarchy *nodeDataStructure, Node *node);
            // Get
            Node *(*get)(struct Hierarchy *nodeDataStructure, int index);
            Node *(*getbyID)(struct Hierarchy *nodeDataStructure, int ID);
            // Remove
            int (*remove)(struct Hierarchy *nodeDataStructure, int index);
            int (*removebyID)(struct Hierarchy *nodeDataStructure, int ID);
            // Free
            void (*free)(struct Hierarchy *nodeDataStructure, int index);
            // Draw
            void (*callDraw) (struct Hierarchy *nodeDataStructure);
            void (*drawAll) (struct Hierarchy *nodeDataStructure);
            // Process
            void (*callProcess) (struct Hierarchy *nodeDataStructure);
            void (*processAll) (struct Hierarchy *nodeDataStructure);

        } DataStructure;

        int PRIVATE_DATASTRUCTURE_AMOUNT = 1;
*/

enum DataStructureType
{
    ARRAY_TYPE, // 0
    LIST_TYPE   // 1
};

typedef struct Hierarchy
{
    Node *parent;

    enum DataStructureType type;
    union
    {
        NodeArray array;
    };

} Hierarchy;
void setParent(Hierarchy *nodeDataStructure, Node *parent)
{
    nodeDataStructure->parent = parent;
}
// Adds a child to the Hierarchy
void addChild(Hierarchy *nodeDataStructure, Node *node)
{
    switch (nodeDataStructure->type)
    {
    case ARRAY_TYPE:
        NodeArray_addNode(&nodeDataStructure->array, node);
        break;

    default:
        break;
    }
}
// Removes a child from the Hierarchy
void removeChild(Hierarchy *nodeDataStructure, int index)
{
    switch (nodeDataStructure->type)

    {
    case ARRAY_TYPE:
        NodeArray_removeNode(&nodeDataStructure->array, index);
        break;

    default:
        break;
    }
}
// Removes a child from the Hierarchy by ID
void removeChildbyID(Hierarchy *nodeDataStructure, int ID)
{
    switch (nodeDataStructure->type)
    {
    case ARRAY_TYPE:
        NodeArray_removeNodebyID(&nodeDataStructure->array, ID);
        break;

    default:
        break;
    }
}
// Gets a child from the Hierarchy
Node *getChild(Hierarchy *nodeDataStructure, int index)
{
    switch (nodeDataStructure->type)
    {
    case ARRAY_TYPE:
        return NodeArray_getNode(&nodeDataStructure->array, index);
        break;

    default:
        break;
    }
}
// Gets a child from the Hierarchy by ID
void *getChildbyID(Hierarchy *nodeDataStructure, int ID)
{
    switch (nodeDataStructure->type)
    {
    case ARRAY_TYPE:
        return NodeArray_getNodebyID(&nodeDataStructure->array, ID);
        break;

    default:
        break;
    }
}
// Frees the Hierarchy
void freeHierarchy(Hierarchy *nodeDataStructure, int index)
{
    switch (nodeDataStructure->type)
    {
    case ARRAY_TYPE:
        NodeArray_removeAll(&nodeDataStructure->array);
        break;

    default:
        break;
    }
}
// Draws a child from the Hierarchy
void callDraw(Hierarchy *nodeDataStructure, int index)
{
    switch (nodeDataStructure->type)
    {
    case ARRAY_TYPE:
        NodeArray_callDraw(&nodeDataStructure->array, index);
        break;

    default:
        break;
    }
}
// Draws a child from the Hierarchy by ID
void callDrawByID(Hierarchy *nodeDataStructure, int ID)
{
    switch (nodeDataStructure->type)
    {
    case ARRAY_TYPE:
        NodeArray_callDrawByID(&nodeDataStructure->array, ID);
        break;

    default:
        break;
    }
}
// Draws all the Hierarchy
void drawAll(Hierarchy *nodeDataStructure)
{
    switch (nodeDataStructure->type)
    {
    case ARRAY_TYPE:
        NodeArray_drawAll(&nodeDataStructure->array);
        break;

    default:
        break;
    }
}
// Processes a child from the Hierarchy
void callProcess(Hierarchy *nodeDataStructure, int index)
{
    switch (nodeDataStructure->type)
    {
    case ARRAY_TYPE:
        NodeArray_callProcess(&nodeDataStructure->array, index);
        break;

    default:
        break;
    }
}
// Processes a child from the Hierarchy by ID
void callProcessByID(Hierarchy *nodeDataStructure, int ID)
{
    switch (nodeDataStructure->type)
    {
    case ARRAY_TYPE:
        NodeArray_callProcessByID(&nodeDataStructure->array, ID);
        break;

    default:
        break;
    }
}
// Processes all the Hierarchy
void processAll(Hierarchy *nodeDataStructure)
{
    switch (nodeDataStructure->type)
    {
    case ARRAY_TYPE:
        NodeArray_processAll(&nodeDataStructure->array);
        break;

    default:
        break;
    }
}