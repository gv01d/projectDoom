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

    // self
    Node *(*getSelf)(struct Container *);

    // Parent
    Node *(*getParent)(struct Container *);
    void (*setParent)(struct Container *, struct Node *);

    // Children
    int (*getChildAmount)(struct Container *);
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
    bool cutOutSide;
    void (*_draw)(struct Container *); // PRIVATE_DEFAULT_CONTAINER_DRAW_CALLING : Done

    // Draw Itself
    bool drawSelf;
    void (*_drawSelf)(struct Container *);               // Set by user | Use drawPolygon
    void (*_renderFunction)(struct Container *, void *); // Set by user

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
    void (*_processChildren)(struct Container *, bool, void **); // TODO

    // ------------------ Functions ------------------
    // Erase Self
    void (*free)(struct Container *);
} Container;

// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv //
// -------------------------------------------------- Container Functions -------------------------------------------------- //
// ^                                                                                                                       ^ //

void VUIE_DEBUGTOOL_PRINTPOINTS(Vector2 *points, int amount)
{
    printf("Amount : %d >> ", amount);

    for (size_t i = 0; i < amount; i++)
    {
        printf("(%d, %d),", points[i].x, points[i].y);
    }
    printf("\n");
}

// Create the Container points --------------------------------------------------------------------------------------------- //
void PRIVATE_DEFAULT_CONTAINER_CREATE_POINTS(Container *container)
{
    int scale = container->transform.size.globalScale;
    int posX, posY;
    Position_get(&container->transform.pos, &posX, &posY);

    // posX = (posX + ((sign(posX) * scale) / 2)) * scale;
    posX = posX * scale;
    // posY = (posY + ((sign(posY) * scale) / 2)) * scale;
    posY = posY * scale;

    float OriginX = -0.5;
    float OriginY = -0.5;
    float OriginX2 = 0.5;
    float OriginY2 = 0.5;

    // printf("\n---------------------------------\nID : %d\n", container->info.ID);
    if (container->transform.size.type == RECT_TYPE)
    {
        container->pointCount = 4;
        container->points = (Vector2 *)realloc(container->points, 4 * sizeof(Vector2));

        // Position_get(&container->transform.pos, &container->points[0].x, &container->points[0].y);
        int w = container->transform.size.width * scale;
        int h = container->transform.size.height * scale;

        container->points[0].x = posX + (w * OriginX);
        container->points[0].y = posY + (h * OriginY);

        container->points[1].x = posX + (w * OriginX);
        container->points[1].y = posY + (h * OriginY2);
        //
        container->points[2].x = posX + (w * OriginX2);
        container->points[2].y = posY + (h * OriginY2);
        //
        container->points[3].x = posX + (w * OriginX2);
        container->points[3].y = posY + (h * OriginY);

        // printf("pos : (%d, %d) | size : (%d, %d)\n", container->transform.pos.Global.x, container->transform.pos.Global.y, container->transform.size.width, container->transform.size.height);
        // printf("Point (4) : (%d, %d) | (%d, %d) | (%d, %d) | (%d, %d)\n", container->points[0].x, container->points[0].y, container->points[1].x, container->points[1].y, container->points[2].x, container->points[2].y, container->points[3].x, container->points[3].y);
    }
    else if (container->transform.size.type == CIRC_TYPE)
    {
        OriginX -= -0.5; // Default Origin for Circle
        OriginY -= -0.5; //
        OriginX2 -= 0.5; //
        OriginY2 -= 0.5; //

        container->pointCount = container->transform.size.points;
        container->points = (Vector2 *)realloc(container->points, container->transform.size.points * sizeof(Vector2));

        int r = container->transform.size.radius * scale;
        int theta = 360 / container->transform.size.points;
        for (int i = 0; i < container->transform.size.points; i++)
        {
            polarToCartesian(r, theta * i, &container->points[i].x, &container->points[i].y);
            container->points[i].x += (posX + (r * OriginX));
            container->points[i].y += (posY + (r * OriginY));
            // printf("Point %d : (%d, %d)\n", i, container->points[i].x, container->points[i].y);
        }
    }
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
    // printf("Container.drawSelf = %s\n", container->drawSelf ? "true" : "false");
    if (container->drawSelf)
    {
        // printf("TEST\n");
        container->_drawSelf(container);
    }

    // Cut outside of container
    // -------------------------------------------------

    glEnable(GL_SCISSOR_TEST);

    int max_x = container->points[0].x;
    int max_y = container->points[0].y;
    int min_x = container->points[0].x;
    int min_y = container->points[0].y;
    for (int i = 0; i < container->pointCount; i++)
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

    bool cutBackup = false;
    glScissorSaveState backupGlScissor;

    if (glScissorEnabled)
    {
        backupGlScissor.x = globalGlScissor.x;
        backupGlScissor.y = globalGlScissor.y;
        backupGlScissor.width = globalGlScissor.width;
        backupGlScissor.height = globalGlScissor.height;
        backupGlScissor.scale = globalGlScissor.scale;

        scissorsIntercection(&globalGlScissor, min_x, backupGlScissor.x, (max_x - min_x), backupGlScissor.width, min_y, backupGlScissor.y, (max_y - min_y), backupGlScissor.height);
    }
    else
    {
        globalGlScissor.x = min_x;
        globalGlScissor.y = min_y;
        globalGlScissor.width = (max_x - min_x);
        globalGlScissor.height = (max_y - min_y);
        globalGlScissor.scale = container->transform.size.globalScale;
        glScissorEnabled = true;
    }

    if (container->cutOutSide)
    {
        GL_Scissors(globalGlScissor.x, globalGlScissor.y, globalGlScissor.width, globalGlScissor.height, globalGlScissor.scale);
    }

    // -------------------------------------------------

    // printf("Amount : %d \n", container->getChildAmount(container));

    // Draw Children

    if (container->drawChildren && !(container->getChildAmount(container) <= 0))
    {
        container->_drawChildren(container);
    }

    // End cut

    if (cutBackup)
    {
        GL_Scissors(backupGlScissor.x, backupGlScissor.y, backupGlScissor.width, backupGlScissor.height, backupGlScissor.scale);
    }
    else
    {
        glScissorEnabled = false;
        glDisable(GL_SCISSOR_TEST);
    }
}
// ------------------------------------------------------------------------------------------------------------------------- //

// Default draw function for container ------------------------------------------------------------------------------------- //
void DEFAULT_CONTAINER_DRAW_FUNCTION(Container *container)
{
    if (container->_renderFunction != NULL)
    {
        container->_renderFunction(container, NULL);
    }
    // Draw Polygon
    Draw_Polygon(container->points, container->pointCount, &container->backgroundColor, container->transform.size.globalScale);
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

    processTransform(&container->transform);

    /*

        TODO : Add Processing Order

    */

    // Process itself
    if (container->processSelf)
    {
        container->_processSelf(container, args);
    }

    // Process Children
    // printf("Container PROCESS Place thingy\n");
    if (container->processChildren && !(container->getChildAmount(container) <= 0))
    {
        container->_processChildren(container, false, NULL);
    }
}
// ------------------------------------------------------------------------------------------------------------------------- //

// Process children for container // --------------------------------------------------------------------------------------- //
void PRIVATE_DEFAULT_CONTAINER_PROCESS_CHILDREN(Container *container, bool argB, void **args)
{
    processAll(&container->hierarchy, argB, args);
}
// ------------------------------------------------------------------------------------------------------------------------- //

// Free the container ------------------------------------------------------------------------------------------------------ //
void PRIVATE_DEFAULT_CONTAINER_FREE(Container *container)
{
    free(container->info.name);
    free(container->points);
    freeHierarchy(&container->hierarchy);
}
// ------------------------------------------------------------------------------------------------------------------------- //

// Add node to container -------------------------------------------------------------------------------------------------- //
void PRIVATE_DEFAULT_CONTAINER_ADD_CHILD(Container *container, Node *node)
{
    addChild(&container->hierarchy, node, (void *)&container->transform.pos, (void *)&container->transform.size.globalScale);
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

// Get self Node from container -------------------------------------------------------------------------------------------- //
Node *PRIVATE_DEFAULT_CONTAINER_GET_SELF(Container *container)
{
    return container->hierarchy.self;
}
// ------------------------------------------------------------------------------------------------------------------------- //

// get Child amount from container ----------------------------------------------------------------------------------------- //
int PRIVATE_DEFAULT_CONTAINER_GET_CHILD_AMOUNT(Container *container)
{
    return getChildAmount(&container->hierarchy);
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
    container->transform.size.globalScale = 1;

    // --- Hierachy --- //
    // Self Node
    hierarchy_init(&container->hierarchy);
    container->hierarchy.self = newNode(CONTAINER, container, container->info.ID);
    container->getSelf = PRIVATE_DEFAULT_CONTAINER_GET_SELF;

    // Parent
    container->hierarchy.parent = NULL;
    container->getParent = PRIVATE_DEFAULT_CONTAINER_GET_PARENT;
    container->setParent = PRIVATE_DEFAULT_CONTAINER_SET_PARENT;

    // Children
    container->getChildAmount = PRIVATE_DEFAULT_CONTAINER_GET_CHILD_AMOUNT;
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
    setColorByVal(&container->backgroundColor, RGB_TYPE, 1.0, 0.0, 0.0);
    setColorByVal(&container->outlineColor, RGB_TYPE, 0.0, 1.0, 1.0);
    container->setColors = PRIVATE_DEFAULT_CONTAINER_SET_COLORS;

    // Draw calling
    container->draw = true;
    container->_draw = PRIVATE_DEFAULT_CONTAINER_DRAW_CALLING;

    // Draw Itself
    container->drawSelf = true;
    container->_drawSelf = DEFAULT_CONTAINER_DRAW_FUNCTION;
    container->_renderFunction = NULL;

    // Draw Children
    container->drawChildren = true;
    container->_drawChildren = PRIVATE_DEFAULT_CONTAINER_DRAW_CHILDREN;

    // --- Process --- //
    // Process calling
    container->_process = PRIVATE_DEFAULT_CONTAINER_PROCESS_CALLING;

    // Self Process
    container->processSelf = false;
    container->_processSelf = NULL;

    // Children Process
    container->processChildren = true;
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
    // printf("Node.COntainer Id: %d\n", ((Container *)Node->element)->info.ID);
    ((Container *)Node->element)->_draw((Container *)Node->element);
}

void PRIVATE_NODE_CONTAINER_PROCESS(Node *Node, void *args)
{
    ((Container *)Node->element)->_process((Container *)Node->element, args);
}

void PRIVATE_NODE_CONTAINER_ADD_PARENT(Node *node, Node *parent, void *pos, void *scale)
{
    ((Container *)node->element)->setParent((Container *)node->element, parent);
    Position_setParent(&((Container *)node->element)->transform.pos, (Position *)pos);
    Size_setParent(&((Container *)node->element)->transform.size, (int *)scale);
}

NodeFunctions PRIVATE_CONTAINER_NODE_FUNTIONS_INIT()
{
    NodeFunctions NodeFunctionsTemp;

    NodeFunctionsTemp.free = PRIVATE_NODE_CONTAINER_FREE;
    NodeFunctionsTemp.draw = PRIVATE_NODE_CONTAINER_DRAW;
    NodeFunctionsTemp.process = PRIVATE_NODE_CONTAINER_PROCESS;
    NodeFunctionsTemp.addParent = PRIVATE_NODE_CONTAINER_ADD_PARENT;

    return NodeFunctionsTemp;
}

// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv //
// --------------------------------------------------------- Saving --------------------------------------------------------- //
// ^                                                                                                                        ^ //

/*

    TODO : Add saving and loading functions

*/
