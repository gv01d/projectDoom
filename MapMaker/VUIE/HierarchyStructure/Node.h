enum elementType
{
    BASE,     // 0
    CONTAINER // 1
};

typedef struct Node
{
    enum elementType type;
    void *element;
    int ID;

} Node;

typedef struct NodeFunctions
{
    void (*free)(Node *);
    void (*draw)(Node *);
    void (*process)(Node *, void *);
    void (*addParent)(Node *, Node *, void *);

} NodeFunctions;

// GLOBAL FUNCTIONS

NodeFunctions *VUIE_GLOBAL_NODE_FUNCTIONS;

// NODE FUNTIONS

void VUIE_inicializeNodeFunctions(NodeFunctions *nodeFunctions, int amount)
{
    VUIE_GLOBAL_NODE_FUNCTIONS = (NodeFunctions *)malloc(amount * sizeof(NodeFunctions));
    for (int i = 0; i < amount; i++)
    {
        VUIE_GLOBAL_NODE_FUNCTIONS[i].free = nodeFunctions[i].free;
        VUIE_GLOBAL_NODE_FUNCTIONS[i].draw = nodeFunctions[i].draw;
        VUIE_GLOBAL_NODE_FUNCTIONS[i].process = nodeFunctions[i].process;
        VUIE_GLOBAL_NODE_FUNCTIONS[i].addParent = nodeFunctions[i].addParent;
    }
}

Node *newNode(enum elementType type, void *element, int ID)
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->type = type;
    node->element = element;
    node->ID = ID;
    return node;
}
void freeNode(Node *node)
{
    VUIE_GLOBAL_NODE_FUNCTIONS[node->type].free(node);
    free(node);
}
void NodeCallDraw(Node *node)
{
    VUIE_GLOBAL_NODE_FUNCTIONS[node->type].draw(node);
}
void NodeCallProcess(Node *node, void *args)
{
    VUIE_GLOBAL_NODE_FUNCTIONS[node->type].process(node, args);
}