#include "../Module_Transform.h"
#include "../HierarchyStructure/Hierarchy.h"

typedef struct Base // Define base
{
    // Info (ID)
    Private_Info info;

    // Position & Size
    _Private_Transform transform;

    // Hierachy structure
    Hierarchy hierarchy;

    // ------------------ Hierachy ------------------

    // Parent
    Node *(*getParent)(struct Base *);
    void (*setParent)(struct Base *, struct Node *);

    // Children
    void (*addChild)(struct Base *, struct Node *);
    void (*removeChild)(struct Base *, int);
    void (*removeChildByID)(struct Base *, int);
    Node *(*getChild)(struct Base *, int);
    Node *(*getChildByID)(struct Base *, int);

    // -------------- Render Structure --------------

    // Points & Outline
    Vector2 *points;
    int pointCount;
    void (*createPoints)(struct Base *); // PRIVATE_DEFAULT_BASE_CREATE_POINTS : Done

    // Draw calling
    bool draw;
    void (*_draw)(struct Base *); //

    // Draw Children
    bool drawChildren;
    void (*_drawChildren)(struct Base *); //

    // -------------- Process Structure --------------
    // Process calling
    void (*_process)(struct Base *, void *); // PRIVATE_DEFAULT_BASE_PROCESS_CALLING : TODO

    // Self Process
    bool processSelf;
    void (*_processSelf)(struct Base *, void *); // Set by user

    // Children Process
    bool processChildren;
    void (*_processChildren)(struct Base *, void **); // TODO

    // ------------------ Functions ------------------
    // Erase Self
    void (*free)(struct Base *);
} Base;
// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv //
// -------------------------------------------------- Container Functions -------------------------------------------------- //
// ^                                                                                                                       ^ //

// Create points for container --------------------------------------------------------------------------------------------- //
void PRIVATE_DEFAULT_BASE_CREATE_POINTS(Base *base)
{
    if (base->transform.size.type == RECT_TYPE)
    {
        base->pointCount = 2;
        base->points = (Vector2 *)malloc(2 * sizeof(Vector2));

        definePos(&base->transform.pos, &base->points[0].x, &base->points[0].y);

        base->points[1].x = base->points[0].x + base->transform.size.rect.width;
        base->points[1].y = base->points[0].y + base->transform.size.rect.height;
    }
    else if (base->transform.size.type == CIRC_TYPE)
    {
        base->pointCount = base->transform.size.circ.points;
        base->points = (Vector2 *)malloc(base->transform.size.circ.points * sizeof(Vector2));

        int r = base->transform.size.circ.radius;
        int theta = 360 / base->transform.size.circ.points;
        for (int i = 0; i < base->transform.size.circ.points; i++)
        {
            polarToCartesian(r, theta * i, &base->points[i].x, &base->points[i].y);
        }
    };
}
// ------------------------------------------------------------------------------------------------------------------------- //

// Draw calling for container // ------------------------------------------------------------------------------------------- //
void PRIVATE_DEFAULT_BASE_DRAW_CALLING(Base *base)
{
    if (!base->draw)
    {
        return;
    }

    /*
        TODO : Add z ordeing

        Example : For loop that gets the Z order for each Node and then draw based on the Z order and datastructure order

        Needs : Reestructuring of how NodeStructure works
    */

    // Create points
    base->createPoints(base);

    // Cut outside of base
    // -------------------------------------------------
    glEnable(GL_SCISSOR_TEST);

    int max_x;
    int max_y;
    int min_x;
    int min_y;
    for (size_t i = 0; i < base->pointCount; i++)
    {
        if (base->points[i].x > max_x)
        {
            max_x = base->points[i].x;
        }
        if (base->points[i].x < min_x)
        {
            min_x = base->points[i].x;
        }
        if (base->points[i].y > max_y)
        {
            max_y = base->points[i].y;
        }
        if (base->points[i].y < min_y)
        {
            min_y = base->points[i].y;
        }
    }

    glScissor(min_x, min_y, max_x, max_y);
    // -------------------------------------------------

    // Draw Children
    if (base->drawChildren)
    {
        base->_drawChildren(base);
    }

    // End cut
    glDisable(GL_SCISSOR_TEST);
}
// ------------------------------------------------------------------------------------------------------------------------- //

// Draw Children for base -------------------------------------------------------------------------------------------------- //
void PRIVATE_DEFAULT_BASE_DRAW_CHILDREN(Base *base)
{
    drawAll(&base->hierarchy);
}
// ------------------------------------------------------------------------------------------------------------------------- //

// Process calling for base // --------------------------------------------------------------------------------------------- //
void PRIVATE_DEFAULT_BASE_PROCESS_CALLING(Base *base, void *args)
{
    /*

        TODO : Add Processing Order

    */

    // Process itself
    if (base->processSelf)
    {
        base->_processSelf(base, args);
    }

    // Process Children
    if (base->processChildren)
    {
        base->_processChildren(base, NULL);
    }
}
// ------------------------------------------------------------------------------------------------------------------------- //

// Process children for container // --------------------------------------------------------------------------------------- //
void PRIVATE_DEFAULT_BASE_PROCESS_CHILDREN(Base *base, void **args)
{
    processAll(&base->hierarchy, args);
}
// ------------------------------------------------------------------------------------------------------------------------- //

// Free the base ----------------------------------------------------------------------------------------------------------- //
void PRIVATE_DEFAULT_BASE_FREE(Base *base)
{
    free(base->points);
}
// ------------------------------------------------------------------------------------------------------------------------- //

// Add node to base -------------------------------------------------------------------------------------------------------- //
void PRIVATE_DEFAULT_BASE_ADD_CHILD(Base *base, Node *node)
{
    addChild(&base->hierarchy, node);
}
// ------------------------------------------------------------------------------------------------------------------------- //

// Remove node from base by ID --------------------------------------------------------------------------------------------- //
void PRIVATE_DEFAULT_BASE_REMOVE_CHILD(Base *base, int index)
{
    removeChild(&base->hierarchy, index);
}
// ------------------------------------------------------------------------------------------------------------------------- //

// Remove node from base by ID --------------------------------------------------------------------------------------------- //
void PRIVATE_DEFAULT_BASE_REMOVE_CHILD_BY_ID(Base *base, int ID)
{
    removeChildbyID(&base->hierarchy, ID);
}
// ------------------------------------------------------------------------------------------------------------------------- //

// Get child from base by index -------------------------------------------------------------------------------------------- //
Node *PRIVATE_DEFAULT_BASE_GET_CHILD(Base *base, int index)
{
    return getChild(&base->hierarchy, index);
}
// ------------------------------------------------------------------------------------------------------------------------- //

// Get child from base by ID ----------------------------------------------------------------------------------------------- //
Node *PRIVATE_DEFAULT_BASE_GET_CHILD_BY_ID(Base *base, int ID)
{
    return getChildbyID(&base->hierarchy, ID);
}
// ------------------------------------------------------------------------------------------------------------------------- //

// Get parent from base ---------------------------------------------------------------------------------------------------- //
Node *PRIVATE_DEFAULT_BASE_GET_PARENT(Base *base)
{
    return base->hierarchy.parent;
}
// ------------------------------------------------------------------------------------------------------------------------- //

// Set parent in base ------------------------------------------------------------------------------------------------------ //
void PRIVATE_DEFAULT_BASE_SET_PARENT(Base *base, Node *parent)
{
    setParent(&base->hierarchy, parent);
}
// ------------------------------------------------------------------------------------------------------------------------- //

// ------------------------------------------------------------------------------------------------------------------------- //

// CREATORS :

//

void make_VUIE_base(Base *base)
{
    // Info
    base->info.ID = GlobalNextID++;

    // Position & Size
    setTransform(&base->transform, &PRIVATE_DEFAULT_POSITION, &PRIVATE_DEFAULT_SIZE);

    // --- Hierachy --- //
    // Parent
    base->hierarchy.parent = NULL;
    base->getParent = PRIVATE_DEFAULT_BASE_GET_PARENT;
    base->setParent = PRIVATE_DEFAULT_BASE_SET_PARENT;

    // Children
    base->addChild = PRIVATE_DEFAULT_BASE_ADD_CHILD;
    base->removeChild = PRIVATE_DEFAULT_BASE_REMOVE_CHILD;
    base->removeChildByID = PRIVATE_DEFAULT_BASE_REMOVE_CHILD_BY_ID;
    base->getChild = PRIVATE_DEFAULT_BASE_GET_CHILD;
    base->getChildByID = PRIVATE_DEFAULT_BASE_GET_CHILD_BY_ID;

    // --- Render --- //
    // Points & Outline
    base->points = NULL;
    base->pointCount = 0;
    base->createPoints = PRIVATE_DEFAULT_BASE_CREATE_POINTS;

    // Draw calling
    base->draw = false;
    base->_draw = PRIVATE_DEFAULT_BASE_DRAW_CALLING;

    // Draw Children
    base->drawChildren = false;
    base->_drawChildren = PRIVATE_DEFAULT_BASE_DRAW_CHILDREN;

    // --- Process --- //
    // Process calling
    base->_process = PRIVATE_DEFAULT_BASE_PROCESS_CALLING;

    // Self Process
    base->processSelf = false;
    base->_processSelf = NULL;

    // Children Process
    base->processChildren = false;
    base->_processChildren = PRIVATE_DEFAULT_BASE_PROCESS_CHILDREN;

    // --- Funtions --- //
    base->free = PRIVATE_DEFAULT_BASE_FREE;
}

Base *new_VUIE_base()
{
    Base *base = (Base *)malloc(sizeof(Base));
    make_VUIE_base(base);
    return base;
}

//

//

void PRIVATE_NODE_BASE_FREE(Node *Node)
{
    ((Base *)Node->element)->free((Base *)Node->element);
}

void PRIVATE_NODE_BASE_DRAW(Node *Node)
{
    ((Base *)Node->element)->_draw((Base *)Node->element);
}

void PRIVATE_NODE_BASE_PROCESS(Node *Node, void *args)
{
    ((Base *)Node->element)->_process((Base *)Node->element, args);
}
