#include "ChildArray.h"

typedef struct ChildDataStructure
{
    enum ChildDataStructureType type;

    union
    {
        ChildArray array;
    };

} ChildDataStructure;
void addChild(ChildDataStructure *childDataStructure, Child *child)
{
    if (childDataStructure->type == ARRAY_TYPE)
    {
        ChildArray_addChild(&childDataStructure->array, child);
    }
}
void removeChild(ChildDataStructure *childDataStructure, int index)
{
    if (childDataStructure->type == ARRAY_TYPE)
    {
        ChildArray_removeChild(&childDataStructure->array, index);
    }
}
void removeChildbyID(ChildDataStructure *childDataStructure, int ID)
{
    if (childDataStructure->type == ARRAY_TYPE)
    {
        ChildArray_removeChildbyID(&childDataStructure->array, ID);
    }
}
Child *getChild(ChildDataStructure *childDataStructure, int index)
{
    if (childDataStructure->type == ARRAY_TYPE)
    {
        return ChildArray_getChild(&childDataStructure->array, index);
    }
}
void *getChildbyID(ChildDataStructure *childDataStructure, int ID)
{
    if (childDataStructure->type == ARRAY_TYPE)
    {
        return ChildArray_getChildbyID(&childDataStructure->array, ID);
    }
    return NULL;
}
void freeChildDataStructure(ChildDataStructure *childDataStructure, int index)
{
    if (childDataStructure->type == ARRAY_TYPE)
    {
        ChildArray_removeAll(&childDataStructure->array);
    }
}