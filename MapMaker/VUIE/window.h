#include <stdlib.h>

#include "Atributes/Transform.h"
#include "Atributes/Info.h"
#include "Render/Draw.h"
#include "HierarchyStructure/NodeArray.h"

typedef struct Window
{
    Private_Info info;

    int GlobalScale;

    struct
    {
        int width;
        int height;
    } rawSize;

    struct
    {
        int width;
        int height;
    } size;

    struct
    {
        int x;
        int y;
    } pos;

    struct
    {
        Position pos;
        enum
        {
            CUSTOM,
            TOP_LEFT,
            TOP_RIGHT,
            BOTTOM_LEFT,
            BOTTOM_RIGHT,
            MIDDLE
        } type;

    } offset;

    Hierarchy hierarchy;

    // ------------------ Transform ----------------

    void (*setPosition)(struct Window *, int x, int y);
    void (*setScale)(struct Window *, int scale);
    void (*setSize)(struct Window *, int width, int height);

    void (*setOffset)(struct Window *, Position *);
    void (*setOffsetByType)(struct Window *, int);

    // ------------------ Hierachy ------------------

    // self
    Node *(*getSelf)(struct Window *);

    // Parent
    Node *(*getParent)(struct Window *);
    void (*setParent)(struct Window *, struct Node *);

    // Children
    int (*getChildAmount)(struct Window *);
    void (*addChild)(struct Window *, struct Node *);
    void (*removeChild)(struct Window *, int);
    void (*removeChildByID)(struct Window *, int);
    Node *(*getChild)(struct Window *, int);
    Node *(*getChildByID)(struct Window *, int);

    // -------------- Render Structure --------------
    // Draw calling
    bool draw;
    void (*_draw)(struct Window *); // PRIVATE_DEFAULT_WINDOW_DRAW_CALLING : Done

    void (*_renderFunction)(struct Window *, void *); // Set by user

    // Draw Children
    bool drawChildren;
    void (*_drawChildren)(struct Window *); // TODO

    // -------------- Process Structure --------------
    // Process calling
    void (*_process)(struct Window *, void *); // PRIVATE_DEFAULT_WINDOW_PROCESS_CALLING : TODO

    // Self Process
    bool processSelf;
    void (*_processSelf)(struct Window *, void *); // Set by user

    // Children Process
    bool processChildren;
    void (*_processChildren)(struct Window *, bool, void **); // TODO

    // ------------------ Functions ------------------
    // Erase Self
    void (*free)(struct Window *);

} Window;

// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv //
// ---------------------------------------------------- Window Functions ---------------------------------------------------- //
// ^                                                                                                                        ^ //

// Draw calling for window // ----------------------------------------------------------------------------------------------- //
void PRIVATE_DEFAULT_WINDOW_DRAW_CALLING(Window *window)
{
    if (!window->draw)
    {
        return;
    }
    // printf("Drawing Window\n");

    /*
        TODO : Add z ordeing

        Example : For loop that gets the Z order for each Node and then draw based on the Z order and datastructure order

        Needs : Reestructuring of how NodeStructure works
    */

    // printf("Amount : %d \n", window->getChildAmount(window));

    // Draw Children

    if (window->drawChildren && !(window->getChildAmount(window) <= 0))
    {
        window->_drawChildren(window);
    }

    if (window->_renderFunction != NULL)
    {
        window->_renderFunction(window, NULL);
    }
}
// ------------------------------------------------------------------------------------------------------------------------- //

// Default draw function for window ------------------------------------------------------------------------------------- //
void DEFAULT_WINDOW_DRAW_FUNCTION(Window *window)
{
}
// ------------------------------------------------------------------------------------------------------------------------- //

// Draw Children for window --------------------------------------------------------------------------------------------- //
void PRIVATE_DEFAULT_WINDOW_DRAW_CHILDREN(Window *window)
{
    drawAll(&window->hierarchy);
}
// ------------------------------------------------------------------------------------------------------------------------- //

// Process calling for window // ---------------------------------------------------------------------------------------- //
void PRIVATE_DEFAULT_WINDOW_PROCESS_CALLING(Window *window, void *args)
{

    /*

        TODO : Add Processing Order

    */

    Position_process(&window->offset.pos);

    // Process itself
    if (window->processSelf)
    {
        window->_processSelf(window, args);
    }

    // Process Children
    if (window->processChildren && !(window->getChildAmount(window) <= 0))
    {
        window->_processChildren(window, false, NULL);
    }
}
// ------------------------------------------------------------------------------------------------------------------------- //

// Process children for window // --------------------------------------------------------------------------------------- //
void PRIVATE_DEFAULT_WINDOW_PROCESS_CHILDREN(Window *window, bool argB, void **args)
{
    processAll(&window->hierarchy, argB, args);
}
// ------------------------------------------------------------------------------------------------------------------------- //

// Free the window ------------------------------------------------------------------------------------------------------ //
void PRIVATE_DEFAULT_WINDOW_FREE(Window *window)
{
    free(window->info.name);
    freeHierarchy(&window->hierarchy);
}
// ------------------------------------------------------------------------------------------------------------------------- //

// Add node to window -------------------------------------------------------------------------------------------------- //
void PRIVATE_DEFAULT_WINDOW_ADD_CHILD(Window *window, Node *node)
{
    addChild(&window->hierarchy, node, (void *)&window->offset.pos, (void *)&window->GlobalScale);
}
// ------------------------------------------------------------------------------------------------------------------------- //

// Remove node from window by ID ---------------------------------------------------------------------------------------- //
void PRIVATE_DEFAULT_WINDOW_REMOVE_CHILD(Window *window, int index)
{
    removeChild(&window->hierarchy, index);
}
// ------------------------------------------------------------------------------------------------------------------------- //

// Remove node from window by ID ---------------------------------------------------------------------------------------- //
void PRIVATE_DEFAULT_WINDOW_REMOVE_CHILD_BY_ID(Window *window, int ID)
{
    removeChildbyID(&window->hierarchy, ID);
}
// ------------------------------------------------------------------------------------------------------------------------- //

// Get child from window by index --------------------------------------------------------------------------------------- //
Node *PRIVATE_DEFAULT_WINDOW_GET_CHILD(Window *window, int index)
{
    return getChild(&window->hierarchy, index);
}
// ------------------------------------------------------------------------------------------------------------------------- //

// Get child from window by ID ------------------------------------------------------------------------------------------ //
Node *PRIVATE_DEFAULT_WINDOW_GET_CHILD_BY_ID(Window *window, int ID)
{
    return getChildbyID(&window->hierarchy, ID);
}
// ------------------------------------------------------------------------------------------------------------------------- //

// Get parent from window ---------------------------------------------------------------------------------------------- //
Node *PRIVATE_DEFAULT_WINDOW_GET_PARENT(Window *window)
{
    return window->hierarchy.parent;
}
// ------------------------------------------------------------------------------------------------------------------------- //

// Set parent in window ------------------------------------------------------------------------------------------------- //
void PRIVATE_DEFAULT_WINDOW_SET_PARENT(Window *window, Node *parent)
{
    setParent(&window->hierarchy, parent);
}
// ------------------------------------------------------------------------------------------------------------------------- //

// Get self Node from window -------------------------------------------------------------------------------------------- //
Node *PRIVATE_DEFAULT_WINDOW_GET_SELF(Window *window)
{
    return window->hierarchy.self;
}
// ------------------------------------------------------------------------------------------------------------------------- //

// get Child amount from window ----------------------------------------------------------------------------------------- //
int PRIVATE_DEFAULT_WINDOW_GET_CHILD_AMOUNT(Window *window)
{
    return getChildAmount(&window->hierarchy);
}
// ------------------------------------------------------------------------------------------------------------------------- //

// Set position for window ---------------------------------------------------------------------------------------------- //
void PRIVATE_DEFAULT_WINDOW_SET_POSITION(Window *window, int x, int y)
{
    window->pos.x = x;
    window->pos.y = y;
}
// ------------------------------------------------------------------------------------------------------------------------- //

// Set scale for window ------------------------------------------------------------------------------------------------- //
void PRIVATE_DEFAULT_WINDOW_SET_SCALE(Window *window, int scale)
{
    window->GlobalScale = scale;
}
// ------------------------------------------------------------------------------------------------------------------------- //

// Set size for window -------------------------------------------------------------------------------------------------- //
void PRIVATE_DEFAULT_WINDOW_SET_SIZE(Window *window, int width, int height)
{
    window->size.width = width;
    window->size.height = height;
}
// ------------------------------------------------------------------------------------------------------------------------- //

// Set offset for window ------------------------------------------------------------------------------------------------ //
void PRIVATE_DEFAULT_WINDOW_SET_OFFSET(Window *window, Position *offset)
{
    Position_copy(&window->offset.pos, offset);
    window->offset.type = CUSTOM;
    Position_process(&window->offset.pos);
}
// ------------------------------------------------------------------------------------------------------------------------- //

// Set offset for window by type ---------------------------------------------------------------------------------------- //
void PRIVATE_DEFAULT_WINDOW_SET_OFFSET_BY_TYPE(Window *window, int type)
{
    window->offset.type = type;

    switch (type)
    {
    case BOTTOM_RIGHT:
        window->offset.pos.x = window->rawSize.width;
        window->offset.pos.y = 0;
        break;
    case BOTTOM_LEFT:
        window->offset.pos.x = 0;
        window->offset.pos.y = 0;
        break;
    case TOP_RIGHT:
        window->offset.pos.x = window->rawSize.width;
        window->offset.pos.y = window->rawSize.height;
        break;
    case TOP_LEFT:
        window->offset.pos.x = 0;
        window->offset.pos.y = window->rawSize.height;
        break;
    case MIDDLE:
        window->offset.pos.x = window->rawSize.width / 2;
        window->offset.pos.y = window->rawSize.height / 2;
        break;
    default:
        break;
    }
    Position_process(&window->offset.pos);
}
// ------------------------------------------------------------------------------------------------------------------------- //

// CREATORS :

//

void make_VUIE_Window(Window *window, char *name)
{
    // Info
    window->info.ID = GlobalNextID++;
    window->info.name = (char *)malloc((strlen(name) + 1) * sizeof(char));
    strcpy(window->info.name, name);

    // Position & Size
    window->pos.x = PRIVATE_DEFAULT_POSITION.x;
    window->pos.y = PRIVATE_DEFAULT_POSITION.y;
    window->setPosition = PRIVATE_DEFAULT_WINDOW_SET_POSITION;
    window->setSize = PRIVATE_DEFAULT_WINDOW_SET_SIZE;
    window->setScale = PRIVATE_DEFAULT_WINDOW_SET_SCALE;

    // Origin
    PRIVATE_DEFAULT_WINDOW_SET_OFFSET_BY_TYPE(window, MIDDLE);
    window->setOffset = PRIVATE_DEFAULT_WINDOW_SET_OFFSET;
    window->setOffsetByType = PRIVATE_DEFAULT_WINDOW_SET_OFFSET_BY_TYPE;

    window->GlobalScale = 1;

    // --- Hierachy --- //
    // Self Node
    hierarchy_init(&window->hierarchy);
    window->hierarchy.self = newNode(WINDOW, window, window->info.ID);
    window->getSelf = PRIVATE_DEFAULT_WINDOW_GET_SELF;

    // Parent
    window->hierarchy.parent = NULL;
    window->getParent = PRIVATE_DEFAULT_WINDOW_GET_PARENT;
    window->setParent = PRIVATE_DEFAULT_WINDOW_SET_PARENT;

    // Children
    window->getChildAmount = PRIVATE_DEFAULT_WINDOW_GET_CHILD_AMOUNT;
    window->addChild = PRIVATE_DEFAULT_WINDOW_ADD_CHILD;
    window->removeChild = PRIVATE_DEFAULT_WINDOW_REMOVE_CHILD;
    window->removeChildByID = PRIVATE_DEFAULT_WINDOW_REMOVE_CHILD_BY_ID;
    window->getChild = PRIVATE_DEFAULT_WINDOW_GET_CHILD;
    window->getChildByID = PRIVATE_DEFAULT_WINDOW_GET_CHILD_BY_ID;

    // --- Render --- //

    // Draw calling
    window->draw = true;
    window->_draw = PRIVATE_DEFAULT_WINDOW_DRAW_CALLING;

    window->_renderFunction = NULL;

    // Draw Children
    window->drawChildren = true;
    window->_drawChildren = PRIVATE_DEFAULT_WINDOW_DRAW_CHILDREN;

    // --- Process --- //
    // Process calling
    window->_process = PRIVATE_DEFAULT_WINDOW_PROCESS_CALLING;

    // Self Process
    window->processSelf = false;
    window->_processSelf = NULL;

    // Children Process
    window->processChildren = true;
    window->_processChildren = PRIVATE_DEFAULT_WINDOW_PROCESS_CHILDREN;

    // --- Funtions --- //
    window->free = PRIVATE_DEFAULT_WINDOW_FREE;

    // --- Security --- //
    window->rawSize.width = 0;
    window->rawSize.height = 0;

    window->size.width = 0;
    window->size.height = 0;

    window->pos.x = 0;
    window->pos.y = 0;

    window->GlobalScale = 1;

    window->offset.pos.x = 0;
    window->offset.pos.y = 0;
    window->offset.type = CUSTOM;
    Position_process(&window->offset.pos);
}

Window *new_VUIE_Window(char *name)
{
    Window *window = (Window *)malloc(sizeof(Window));
    make_VUIE_Window(window, name);
    return window;
}

// ------------------------------------------------------------------------------------------------------------------------- //

void PRIVATE_NODE_WINDOW_FREE(Node *Node)
{
    ((Window *)Node->element)->free((Window *)Node->element);
}

void PRIVATE_NODE_WINDOW_DRAW(Node *Node)
{
    // printf("Node.window Id: %d\n", ((Window *)Node->element)->info.ID);
    ((Window *)Node->element)->_draw((Window *)Node->element);
}

void PRIVATE_NODE_WINDOW_PROCESS(Node *Node, void *args)
{
    ((Window *)Node->element)->_process((Window *)Node->element, args);
}

void PRIVATE_NODE_WINDOW_ADD_PARENT(Node *node, Node *parent, void *pos, void *scale)
{
    printf("\n<WARNING> Cannot add parent to window\n");
}

NodeFunctions PRIVATE_WINDOW_NODE_FUNTIONS_INIT()
{
    NodeFunctions NodeFunctionsTemp;

    NodeFunctionsTemp.free = PRIVATE_NODE_WINDOW_FREE;
    NodeFunctionsTemp.draw = PRIVATE_NODE_WINDOW_DRAW;
    NodeFunctionsTemp.process = PRIVATE_NODE_WINDOW_PROCESS;
    NodeFunctionsTemp.addParent = PRIVATE_NODE_WINDOW_ADD_PARENT;

    return NodeFunctionsTemp;
}

// ------------------------------------------------------------------------------------------------------------------------- //