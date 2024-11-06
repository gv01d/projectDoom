#include "../Atributes.h"

typedef struct NodeArray_DataStructure
{
    int nodeAmount;

    Node **node;

} NodeArray;

void NodeArray_addNode(NodeArray *nodeArray, Node *node)
{
    nodeArray->nodeAmount++;
    nodeArray->node = (Node **)realloc(nodeArray->node, nodeArray->nodeAmount * sizeof(Node *));
    nodeArray->node[nodeArray->nodeAmount - 1] = node;
}
Node *NodeArray_getNode(NodeArray *nodeArray, int index)
{
    return nodeArray->node[index];
}

Node *NodeArray_getNodebyID(NodeArray *nodeArray, int ID)
{
    for (int i = 0; i < nodeArray->nodeAmount; i++)
    {
        if (getNodeID(nodeArray->node[i]) == ID)
        {
            return nodeArray->node[i];
        }
    }
}

void NodeArray_removeNode(NodeArray *nodeArray, int index)
{
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

void NodeArray_removeNodebyID(NodeArray *nodeArray, int ID)
{
    for (int i = 0; i < nodeArray->nodeAmount; i++)
    {
        if (getNodeID(nodeArray->node[i]) == ID)
        {
            NodeArray_removeNode(nodeArray, i);
            return;
        }
    }
}
void NodeArray_removeAll(NodeArray *nodeArray)
{
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
void NodeArray_callDraw(NodeArray *nodeArray, int index)
{
    callDraw(nodeArray->node[index]);
}
void NodeArray_callDrawByID(NodeArray *nodeArray, int ID)
{
    for (size_t i = 0; i < nodeArray->nodeAmount; i++)
    {
        if (getNodeID(nodeArray->node[i]) == ID)
        {
            callDraw(nodeArray->node[i]);
            return;
        }
    }
}

void NodeArray_drawAll(NodeArray *nodeArray)
{
    for (size_t i = 0; i < nodeArray->nodeAmount; i++)
    {
        callDraw(nodeArray->node[i]);
    }
}

void NodeArray_callProcess(NodeArray *nodeArray, int index)
{
    callProcess(nodeArray->node[index]);
}
void NodeArray_callProcessByID(NodeArray *nodeArray, int ID)
{
    for (size_t i = 0; i < nodeArray->nodeAmount; i++)
    {
        if (getNodeID(nodeArray->node[i]) == ID)
        {
            callProcess(nodeArray->node[i]);
            return;
        }
    }
}
void NodeArray_processAll(NodeArray *nodeArray)
{
    for (size_t i = 0; i < nodeArray->nodeAmount; i++)
    {
        callProcess(nodeArray->node[i]);
    }
}