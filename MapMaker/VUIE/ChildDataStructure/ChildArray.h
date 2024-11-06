#include "../Atributes.h"

enum ChildDataStructureType
{
    ARRAY_TYPE, // 0
    LIST_TYPE   // 1
};

// TODO : Add other child data structures
typedef struct ChildArray_DataStructure
{
    int childAmount;

    Child **child;

} ChildArray;

void ChildArray_addChild(ChildArray *childArray, Child *child)
{
    childArray->childAmount++;
    childArray->child = (Child **)realloc(childArray->child, childArray->childAmount * sizeof(Child *));
    childArray->child[childArray->childAmount - 1] = child;
}
Child *ChildArray_getChild(ChildArray *childArray, int index)
{
    return childArray->child[index];
}

Child *ChildArray_getChildbyID(ChildArray *childArray, int ID)
{
    for (int i = 0; i < childArray->childAmount; i++)
    {
        if (getChildID(childArray->child[i]) == ID)
        {
            return childArray->child[i];
        }
    }
}

void ChildArray_removeChild(ChildArray *childArray, int index)
{
    if (index < 0 || index >= childArray->childAmount)
    {
        printf("<WARNING> : Index out of bounds on removing child from childArray\n");
        return;
    }

    for (int i = index; i < childArray->childAmount - 1; i++)
    {
        childArray->child[i] = childArray->child[i + 1];
    }

    childArray->childAmount--;
    childArray->child = (Child **)realloc(childArray->child, childArray->childAmount * sizeof(Child *));
    if (childArray->child == NULL && childArray->childAmount > 0)
    {
        printf("<WARNING> : ChildArray is NULL and amount is greater than 0\n");
        return;
    }
}

void ChildArray_removeChildbyID(ChildArray *childArray, int ID)
{
    for (int i = 0; i < childArray->childAmount; i++)
    {
        if (getChildID(childArray->child[i]) == ID)
        {
            ChildArray_removeChild(childArray, i);
            return;
        }
    }
}
void ChildArray_removeAll(ChildArray *childArray)
{
    for (size_t i = 0; i < childArray->childAmount; i++)
    {
        freeChild(childArray->child[i]);
        free(childArray->child[i]);
    }
}