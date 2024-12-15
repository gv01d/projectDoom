#include "Hierarchy.h"

typedef struct NodeArray_DataStructure
{
    int nodeAmount;

    Node **node;

} NodeArray;

int NodeArray_getNodeAmount(void *dataStructure)
{
    return ((NodeArray *)dataStructure)->nodeAmount;
}

void NodeArray_addNode(void *dataStructure, Node *node, Node *parent, void *pos, void *scale)
{

    ((NodeArray *)dataStructure)->nodeAmount++;
    ((NodeArray *)dataStructure)->node = (Node **)realloc(((NodeArray *)dataStructure)->node, ((NodeArray *)dataStructure)->nodeAmount * sizeof(Node *));
    ((NodeArray *)dataStructure)->node[((NodeArray *)dataStructure)->nodeAmount - 1] = node;
    NodeAddParent(node, parent, pos, scale);
}
Node *NodeArray_getNode(void *dataStructure, int index)
{
    NodeArray *nodeArray = (NodeArray *)dataStructure;

    return nodeArray->node[index];
}

Node *NodeArray_getNodebyID(void *dataStructure, int ID)
{
    NodeArray *nodeArray = (NodeArray *)dataStructure;

    for (int i = 0; i < nodeArray->nodeAmount; i++)
    {
        if (nodeArray->node[i]->ID == ID)
        {
            return nodeArray->node[i];
        }
    }
}

void NodeArray_removeNode(void *dataStructure, int index)
{
    NodeArray *nodeArray = (NodeArray *)dataStructure;

    if (index < 0 || index >= nodeArray->nodeAmount)
    {
        printf("<WARNING> : Index out of bounds on removing node from nodeArray\n");
        return;
    }

    for (int i = index; i < nodeArray->nodeAmount - 1; i++)
    {
        nodeArray->node[i] = nodeArray->node[i + 1];
    }

    nodeArray->nodeAmount--;
    if (nodeArray->nodeAmount == 0)
    {
        free(nodeArray->node);
        nodeArray->node = NULL;
    }
    else
    {
        nodeArray->node = (Node **)realloc(nodeArray->node, nodeArray->nodeAmount * sizeof(Node *));
    }
    if (nodeArray->node == NULL && nodeArray->nodeAmount > 0)
    {
        printf("<WARNING> : NodeArray is NULL and amount is greater than 0\n");
        return;
    }
}

void NodeArray_removeNodebyID(void *dataStructure, int ID)
{
    NodeArray *nodeArray = (NodeArray *)dataStructure;

    for (int i = 0; i < nodeArray->nodeAmount; i++)
    {
        if (nodeArray->node[i]->ID == ID)
        {
            NodeArray_removeNode(nodeArray, i);
            return;
        }
    }
}
void NodeArray_removeAll(void *dataStructure)
{
    NodeArray *nodeArray = (NodeArray *)dataStructure;

    for (size_t i = 0; i < nodeArray->nodeAmount; i++)
    {
        freeNode(nodeArray->node[i]);
        free(nodeArray->node[i]);
    }
    nodeArray->nodeAmount = 0;
    nodeArray->node = NULL;
}
/*

    TODO : Add new parameters for the drawAll ,callDraw(filter) and callDrawByID(filter) that use Z ordering

*/
void NodeArray_callDraw(void *dataStructure, int index)
{
    NodeArray *nodeArray = (NodeArray *)dataStructure;

    NodeCallDraw(nodeArray->node[index]);
}
void NodeArray_callDrawByID(void *dataStructure, int ID)
{
    NodeArray *nodeArray = (NodeArray *)dataStructure;

    for (size_t i = 0; i < nodeArray->nodeAmount; i++)
    {
        if (nodeArray->node[i]->ID == ID)
        {
            NodeCallDraw(nodeArray->node[i]);
            return;
        }
    }
}

void NodeArray_drawAll(void *dataStructure)
{
    NodeArray *nodeArray = (NodeArray *)dataStructure;

    /*
    VUIE_GLOBAL_NODE_FUNCTIONS[1].draw(nodeArray->node[0]);
    printf("C2.ID = %d\n", ((Container *)nodeArray->node[0]->element)->info.ID);
    */
    for (int i = 0; i < nodeArray->nodeAmount; i++)
    {
        NodeCallDraw(nodeArray->node[i]);
    }
}

void NodeArray_callProcess(void *dataStructure, int index, void *args)
{
    NodeArray *nodeArray = (NodeArray *)dataStructure;

    NodeCallProcess(nodeArray->node[index], args);
}
void NodeArray_callProcessByID(void *dataStructure, int ID, void *args)
{
    NodeArray *nodeArray = (NodeArray *)dataStructure;

    for (size_t i = 0; i < nodeArray->nodeAmount; i++)
    {
        if (nodeArray->node[i]->ID == ID)
        {
            NodeCallProcess(nodeArray->node[i], args);
            return;
        }
    }
}
void NodeArray_processAll(void *dataStructure, bool argB, void **args)
{
    NodeArray *nodeArray = (NodeArray *)dataStructure;

    if (argB && args != NULL)
    {
        for (int i = 0; i < nodeArray->nodeAmount; i++)
        {
            NodeCallProcess(nodeArray->node[i], args[i]);
        }
        return;
    }
    for (int i = 0; i < nodeArray->nodeAmount; i++)
    {
        NodeCallProcess(nodeArray->node[i], NULL);
    }
}

void NodeArray_Init(void *hierarchy)
{
    NodeArray *newNdAr = (NodeArray *)malloc(sizeof(NodeArray));

    newNdAr->nodeAmount = 0;
    newNdAr->node = NULL;
    ((Hierarchy *)hierarchy)->dataStructure = (void *)newNdAr;
}

// ------------------------------------------------------------------------------------------------------------
// Data structure functions

DataStructure PRIVATE_NODEARRAY_INIT()
{
    DataStructure PRIVATE_NODEARRAY_DATASTRUCTURE;
    PRIVATE_NODEARRAY_DATASTRUCTURE.type = ARRAY_TYPE;
    PRIVATE_NODEARRAY_DATASTRUCTURE.name = "NodeArray";

    PRIVATE_NODEARRAY_DATASTRUCTURE.add = NodeArray_addNode;
    PRIVATE_NODEARRAY_DATASTRUCTURE.getAmount = NodeArray_getNodeAmount;
    PRIVATE_NODEARRAY_DATASTRUCTURE.get = NodeArray_getNode;
    PRIVATE_NODEARRAY_DATASTRUCTURE.getbyID = NodeArray_getNodebyID;
    PRIVATE_NODEARRAY_DATASTRUCTURE.remove = NodeArray_removeNode;
    PRIVATE_NODEARRAY_DATASTRUCTURE.removebyID = NodeArray_removeNodebyID;
    PRIVATE_NODEARRAY_DATASTRUCTURE.removeAll = NodeArray_removeAll;
    PRIVATE_NODEARRAY_DATASTRUCTURE.callDraw = NodeArray_drawAll;
    PRIVATE_NODEARRAY_DATASTRUCTURE.callDrawByID = NodeArray_callDrawByID;
    PRIVATE_NODEARRAY_DATASTRUCTURE.callDrawAboveZ = NULL;
    PRIVATE_NODEARRAY_DATASTRUCTURE.callDrawZ = NULL;
    PRIVATE_NODEARRAY_DATASTRUCTURE.callDrawBelowZ = NULL;
    PRIVATE_NODEARRAY_DATASTRUCTURE.drawAll = NodeArray_drawAll;
    PRIVATE_NODEARRAY_DATASTRUCTURE.callProcess = NodeArray_callProcess;
    PRIVATE_NODEARRAY_DATASTRUCTURE.callProcessByID = NodeArray_callProcessByID;
    PRIVATE_NODEARRAY_DATASTRUCTURE.processAll = NodeArray_processAll;

    PRIVATE_NODEARRAY_DATASTRUCTURE.init = NodeArray_Init;

    return PRIVATE_NODEARRAY_DATASTRUCTURE;
}