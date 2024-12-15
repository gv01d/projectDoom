#include "Node.h"
#include <stdlib.h>

enum DataStructureType
{
    ARRAY_TYPE, // 0
};

typedef struct datastructure
{
    int type;
    char *name;

    // Add
    void (*add)(void *datastructure, Node *node, Node *parent, void *pos, void *scale);
    // Get
    int (*getAmount)(void *datastructure);
    Node *(*get)(void *datastructure, int index);
    Node *(*getbyID)(void *datastructure, int ID);
    // Remove
    void (*remove)(void *datastructure, int index);
    void (*removebyID)(void *datastructure, int ID);
    void (*removeAll)(void *datastructure);
    // Free
    void (*free)(void *datastructure, int index);
    // Draw
    void (*callDraw)(void *datastructure);
    void (*callDrawByID)(void *datasctructure, int ID);
    void (*callDrawAboveZ)(void *datastructure, int Z);
    void (*callDrawZ)(void *datastructure, int Z);
    void (*callDrawBelowZ)(void *datastructure, int Z);
    void (*drawAll)(void *datastructure);
    // Process
    void (*callProcess)(void *datastructure, int index, void *args);
    void (*callProcessByID)(void *datasctructure, int ID, void *args);
    void (*processAll)(void *datastructure, bool argB, void **args);

    // Init Values
    void (*init)(void *hierarchy);

} DataStructure;

int PRIVATE_DATASTRUCTURE_AMOUNT = 1;
DataStructure *GLOBAL_VUIE_DATASTRUCTURES;
