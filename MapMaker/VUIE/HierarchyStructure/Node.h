enum elementType
{
    WINDOW,   // 0
    BASE,     // 1
    CONTAINER // 2
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
    void (*addParent)(Node *, Node *, void *, void *);

} NodeFunctions;

// GLOBAL FUNCTIONS

int VUIE_GLOBAL_NODE_FUNCTIONS_AMOUNT;
NodeFunctions *VUIE_GLOBAL_NODE_FUNCTIONS;

// NODE FUNTIONS

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

void NodeAddParent(Node *node, Node *parent, Position *pos, void *scale)
{
    VUIE_GLOBAL_NODE_FUNCTIONS[node->type].addParent(node, parent, pos, scale);
}