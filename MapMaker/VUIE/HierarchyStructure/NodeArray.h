#include "Node.h"

typedef struct NodeArray_DataStructure
{
    int nodeAmount;

    Node **node;

} NodeArray;

int NodeArray_getNodeAmount(NodeArray *nodeArray)
{
    return nodeArray->nodeAmount;
}

void NodeArray_addNode(NodeArray *nodeArray, Node *node, Node *parent, void *pos)
{
    nodeArray->nodeAmount++;
    nodeArray->node = (Node **)realloc(nodeArray->node, nodeArray->nodeAmount * sizeof(Node *));
    nodeArray->node[nodeArray->nodeAmount - 1] = node;
    VUIE_GLOBAL_NODE_FUNCTIONS[node->type].addParent(node, parent, pos);
}
Node *NodeArray_getNode(NodeArray *nodeArray, int index)
{
    return nodeArray->node[index];
}

Node *NodeArray_getNodebyID(NodeArray *nodeArray, int ID)
{
    for (int i = 0; i < nodeArray->nodeAmount; i++)
    {
        if (nodeArray->node[i]->ID == ID)
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
        if (nodeArray->node[i]->ID == ID)
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
    NodeCallDraw(nodeArray->node[index]);
}
void NodeArray_callDrawByID(NodeArray *nodeArray, int ID)
{
    for (size_t i = 0; i < nodeArray->nodeAmount; i++)
    {
        if (nodeArray->node[i]->ID == ID)
        {
            NodeCallDraw(nodeArray->node[i]);
            return;
        }
    }
}

void NodeArray_drawAll(NodeArray *nodeArray)
{
    /*
    VUIE_GLOBAL_NODE_FUNCTIONS[1].draw(nodeArray->node[0]);
    printf("C2.ID = %d\n", ((Container *)nodeArray->node[0]->element)->info.ID);
    */
    for (int i = 0; i < nodeArray->nodeAmount; i++)
    {
        NodeCallDraw(nodeArray->node[i]);
    }
}

void NodeArray_callProcess(NodeArray *nodeArray, int index, void *args)
{
    NodeCallProcess(nodeArray->node[index], args);
}
void NodeArray_callProcessByID(NodeArray *nodeArray, int ID, void *args)
{
    for (size_t i = 0; i < nodeArray->nodeAmount; i++)
    {
        if (nodeArray->node[i]->ID == ID)
        {
            NodeCallProcess(nodeArray->node[i], args);
            return;
        }
    }
}
void NodeArray_processAll(NodeArray *nodeArray, bool argB, void **args)
{
    if (args)
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