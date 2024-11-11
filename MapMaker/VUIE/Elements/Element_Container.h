#include "Element_Base.h"

typedef struct Container
{
    // Info
    Private_Info info;

    // Position & Size
    _Private_Transform transform;

    // Hierachy structure
    Hierarchy hierarchy;

    // ------------------ Hierachy ------------------

    // Parent
    Node *(*getParent)(struct Container *);
    void (*setParent)(struct Container *, struct Node *);

    // Children
    void (*addChild)(struct Container *, struct Node *);
    void (*removeChild)(struct Container *, int);
    void (*removeChildByID)(struct Container *, int);
    Node *(*getChild)(struct Container *, int);
    Node *(*getChildByID)(struct Container *, int);

    // -------------- Render Structure --------------
    // Points & Outline
    Vector2 *points;
    int pointCount;
    int outlineWidth;
    void (*createPoints)(struct Container *); // PRIVATE_DEFAULT_CONTAINER_CREATE_POINTS : Done

    // Colors
    Color backgroundColor;
    Color outlineColor;
    void (*setColors)(struct Container *, struct Color *, struct Color *); // PRIVATE_DEFAULT_CONTAINER_SET_COLORS : Done

    // Draw calling
    bool draw;
    void (*_draw)(struct Container *); // PRIVATE_DEFAULT_CONTAINER_DRAW_CALLING : Done

    // Draw Itself
    bool drawSelf;
    void (*_drawSelf)(struct Container *); // Set by user | Use drawPolygon

    // Draw Children
    bool drawChildren;
    void (*_drawChildren)(struct Container *); // TODO

    // -------------- Process Structure --------------
    // Process calling
    void (*_process)(struct Container *, void *); // PRIVATE_DEFAULT_CONTAINER_PROCESS_CALLING : TODO

    // Self Process
    bool processSelf;
    void (*_processSelf)(struct Container *, void *); // Set by user

    // Children Process
    bool processChildren;
    void (*_processChildren)(struct Container *, void **); // TODO

    // ------------------ Functions ------------------
    // Erase Self
    void (*free)(struct Container *);
} Container;

// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv //
// -------------------------------------------------- Container Functions -------------------------------------------------- //
// ^                                                                                                                       ^ //

// Create the Container points --------------------------------------------------------------------------------------------- //
void PRIVATE_DEFAULT_CONTAINER_CREATE_POINTS(Container *container)
{
    if (container->transform.size.type == RECT_TYPE)
    {
        container->pointCount = 2;
        container->points = (Vector2 *)malloc(2 * sizeof(Vector2));

        definePos(&container->transform.pos, &container->points[0].x, &container->points[0].y);

        container->points[1].x = container->points[0].x + container->transform.size.rect.width;
        container->points[1].y = container->points[0].y + container->transform.size.rect.height;
    }
    else if (container->transform.size.type == CIRC_TYPE)
    {
        container->pointCount = container->transform.size.circ.points;
        container->points = (Vector2 *)malloc(container->transform.size.circ.points * sizeof(Vector2));

        int r = container->transform.size.circ.radius;
        int theta = 360 / container->transform.size.circ.points;
        for (int i = 0; i < container->transform.size.circ.points; i++)
        {
            polarToCartesian(r, theta * i, &container->points[i].x, &container->points[i].y);
        }
    };
}
// ------------------------------------------------------------------------------------------------------------------------- //

//

// Set the Container colors // --------------------------------------------------------------------------------------------- //
void PRIVATE_DEFAULT_CONTAINER_SET_COLORS(Container *container, Color *backgroundColor, Color *outlineColor)
{
    copyColor(&container->backgroundColor, backgroundColor);
    copyColor(&container->outlineColor, outlineColor);
}
// ------------------------------------------------------------------------------------------------------------------------- //

//

// Draw calling for container // ------------------------------------------------------------------------------------------- //
void PRIVATE_DEFAULT_CONTAINER_DRAW_CALLING(Container *container)
{
    if (!container->draw)
    {
        return;
    }

    /*
        TODO : Add z ordeing

        Example : For loop that gets the Z order for each Node and then draw based on the Z order and datastructure order

        Needs : Reestructuring of how NodeStructure works
    */

    // Create points
    container->createPoints(container);

    // Draw Itself
    printf("Container.drawSelf = %s\n", container->drawSelf ? "true" : "false");
    if (container->drawSelf)
    {
        printf("TEST\n");
        container->_drawSelf(container);
    }

    // Cut outside of container
    // -------------------------------------------------
    glEnable(GL_SCISSOR_TEST);

    int max_x;
    int max_y;
    int min_x;
    int min_y;
    for (size_t i = 0; i < container->pointCount; i++)
    {
        if (container->points[i].x > max_x)
        {
            max_x = container->points[i].x;
        }
        if (container->points[i].x < min_x)
        {
            min_x = container->points[i].x;
        }
        if (container->points[i].y > max_y)
        {
            max_y = container->points[i].y;
        }
        if (container->points[i].y < min_y)
        {
            min_y = container->points[i].y;
        }
    }

    glScissor(min_x, min_y, max_x, max_y);
    // -------------------------------------------------

    // Draw Children
    if (container->drawChildren)
    {
        container->_drawChildren(container);
    }

    // End cut
    glDisable(GL_SCISSOR_TEST);
}
// ------------------------------------------------------------------------------------------------------------------------- //

// Default draw function for container ------------------------------------------------------------------------------------- //
void DEFAULT_CONTAINER_DRAW_FUNCTION(Container *container)
{
    // Draw Polygon
    Draw_Polygon(container->points, container->pointCount, &container->backgroundColor);
    Draw_PolygonOutline(container->points, container->pointCount, &container->outlineColor, container->outlineWidth);
}
// ------------------------------------------------------------------------------------------------------------------------- //

// Draw Children for container --------------------------------------------------------------------------------------------- //
void PRIVATE_DEFAULT_CONTAINER_DRAW_CHILDREN(Container *container)
{
    drawAll(&container->hierarchy);
}
// ------------------------------------------------------------------------------------------------------------------------- //

// Process calling for container // ---------------------------------------------------------------------------------------- //
void PRIVATE_DEFAULT_CONTAINER_PROCESS_CALLING(Container *container, void *args)
{
    /*

        TODO : Add Processing Order

    */

    // Process itself
    if (container->processSelf)
    {
        container->_processSelf(container, args);
    }

    // Process Children
    if (container->processChildren)
    {
        container->_processChildren(container, NULL);
    }
}
// ------------------------------------------------------------------------------------------------------------------------- //

// Process children for container // --------------------------------------------------------------------------------------- //
void PRIVATE_DEFAULT_CONTAINER_PROCESS_CHILDREN(Container *container, void **args)
{
    processAll(&container->hierarchy, args);
}
// ------------------------------------------------------------------------------------------------------------------------- //

// Free the container ------------------------------------------------------------------------------------------------------ //
void PRIVATE_DEFAULT_CONTAINER_FREE(Container *container)
{
    free(container->points);
}
// ------------------------------------------------------------------------------------------------------------------------- //

// Add node to container -------------------------------------------------------------------------------------------------- //
void PRIVATE_DEFAULT_CONTAINER_ADD_CHILD(Container *container, Node *node)
{
    addChild(&container->hierarchy, node);
}
// ------------------------------------------------------------------------------------------------------------------------- //

// Remove node from container by ID ---------------------------------------------------------------------------------------- //
void PRIVATE_DEFAULT_CONTAINER_REMOVE_CHILD(Container *container, int index)
{
    removeChild(&container->hierarchy, index);
}
// ------------------------------------------------------------------------------------------------------------------------- //

// Remove node from container by ID ---------------------------------------------------------------------------------------- //
void PRIVATE_DEFAULT_CONTAINER_REMOVE_CHILD_BY_ID(Container *container, int ID)
{
    removeChildbyID(&container->hierarchy, ID);
}
// ------------------------------------------------------------------------------------------------------------------------- //

// Get child from container by index --------------------------------------------------------------------------------------- //
Node *PRIVATE_DEFAULT_CONTAINER_GET_CHILD(Container *container, int index)
{
    return getChild(&container->hierarchy, index);
}
// ------------------------------------------------------------------------------------------------------------------------- //

// Get child from container by ID ------------------------------------------------------------------------------------------ //
Node *PRIVATE_DEFAULT_CONTAINER_GET_CHILD_BY_ID(Container *container, int ID)
{
    return getChildbyID(&container->hierarchy, ID);
}
// ------------------------------------------------------------------------------------------------------------------------- //

// Get parent from container ---------------------------------------------------------------------------------------------- //
Node *PRIVATE_DEFAULT_CONTAINER_GET_PARENT(Container *container)
{
    return container->hierarchy.parent;
}
// ------------------------------------------------------------------------------------------------------------------------- //

// Set parent in container ------------------------------------------------------------------------------------------------- //
void PRIVATE_DEFAULT_CONTAINER_SET_PARENT(Container *container, Node *parent)
{
    setParent(&container->hierarchy, parent);
}
// ------------------------------------------------------------------------------------------------------------------------- //

// ------------------------------------------------------------------------------------------------------------------------- //

// CREATORS :

//

void make_VUIE_Container(Container *container)
{
    // Info
    container->info.ID = GlobalNextID++;

    // Position & Size
    setTransform(&container->transform, &PRIVATE_DEFAULT_POSITION, &PRIVATE_DEFAULT_SIZE);

    // --- Hierachy --- //
    // Parent
    container->hierarchy.parent = NULL;
    container->getParent = PRIVATE_DEFAULT_CONTAINER_GET_PARENT;
    container->setParent = PRIVATE_DEFAULT_CONTAINER_SET_PARENT;

    // Children
    container->addChild = PRIVATE_DEFAULT_CONTAINER_ADD_CHILD;
    container->removeChild = PRIVATE_DEFAULT_CONTAINER_REMOVE_CHILD;
    container->removeChildByID = PRIVATE_DEFAULT_CONTAINER_REMOVE_CHILD_BY_ID;
    container->getChild = PRIVATE_DEFAULT_CONTAINER_GET_CHILD;
    container->getChildByID = PRIVATE_DEFAULT_CONTAINER_GET_CHILD_BY_ID;

    // --- Render --- //
    // Points & Outline
    container->points = NULL;
    container->pointCount = 0;
    container->outlineWidth = false;
    container->createPoints = PRIVATE_DEFAULT_CONTAINER_CREATE_POINTS;

    // Colors
    setColorByVal(&container->backgroundColor, RGB_TYPE, 0, 0, 0);
    setColorByVal(&container->outlineColor, RGB_TYPE, 0, 0, 0);
    container->setColors = PRIVATE_DEFAULT_CONTAINER_SET_COLORS;

    // Draw calling
    container->draw = false;
    container->_draw = PRIVATE_DEFAULT_CONTAINER_DRAW_CALLING;

    // Draw Itself
    container->drawSelf = false;
    container->_drawSelf = DEFAULT_CONTAINER_DRAW_FUNCTION;

    // Draw Children
    container->drawChildren = false;
    container->_drawChildren = PRIVATE_DEFAULT_CONTAINER_DRAW_CHILDREN;

    // --- Process --- //
    // Process calling
    container->_process = PRIVATE_DEFAULT_CONTAINER_PROCESS_CALLING;

    // Self Process
    container->processSelf = false;
    container->_processSelf = NULL;

    // Children Process
    container->processChildren = false;
    container->_processChildren = PRIVATE_DEFAULT_CONTAINER_PROCESS_CHILDREN;

    // --- Funtions --- //
    container->free = PRIVATE_DEFAULT_CONTAINER_FREE;
}

Container *new_VUIE_Container()
{
    Container *container = (Container *)malloc(sizeof(Container));
    make_VUIE_Container(container);
    return container;
}

// ------------------------------------------------------------------------------------------------------------------------- //

//

void PRIVATE_NODE_CONTAINER_FREE(Node *Node)
{
    ((Container *)Node->element)->free((Container *)Node->element);
}

void PRIVATE_NODE_CONTAINER_DRAW(Node *Node)
{
    ((Container *)Node->element)->_draw((Container *)Node->element);
}

void PRIVATE_NODE_CONTAINER_PROCESS(Node *Node, void *args)
{
    ((Container *)Node->element)->_process((Container *)Node->element, args);
}