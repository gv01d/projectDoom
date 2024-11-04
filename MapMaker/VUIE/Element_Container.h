#include "Module_Transform.h"

struct Element_Container
{
    Private_Info info;

    // Position & Size
    _Private_Transform transform;

    // Child
    ChildDataStructure childDataStructure;

    // ------------------ Render ------------------
    // Points & Outline
    Vector2 *points;
    int pointCount;
    int outlineWidth;
    void (*createPoints)(struct Container *);

    // Colors
    Color backgroundColor;
    Color outlineColor;
    void (*setColors)(struct Container *, struct Color, struct Color);

    // Draw calling
    void (*_draw)(struct Container *);

    // Draw Itself
    bool drawSelf;
    void (*_drawSelf)(struct Container *);

    // Draw Children
    bool drawChildren;
    void (*_drawChildren)(struct Container *);

    // ------------------ Process ------------------
    // Process calling
    void (*_process)(struct Container *);

    // Self Process
    bool selfProcess;
    void (*_selfProcess)(struct Container *, void *);

    // Children Process
    bool ChildrenProcess;
    void (*_childrenProcess)(struct Container *, void *);

    // ------------------ Function ------------------
    // Erase Self
    void (*eraseSelf)(struct Container *);
    void (*free)(struct Container *);
};

// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
// ------------------ Container Functions ------------------

// set the Container colors
void PRIVATE_DEFAULT_CONTAINER_SET_COLORS(Container *container, Color backgroundColor, Color outlineColor)
{
    container->backgroundColor = backgroundColor;
    container->outlineColor = outlineColor;
}
//

// create the Container points
void PRIVATE_DEFAULT_CONTAINER_CREATE_POINTS(Container *container)
{
    if (container->transform.size.type == RECT_TYPE)
    {
        container->pointCount = 2;
        container->points = (int *)malloc(2 * sizeof(int));

        definePos(&container->transform.pos, &container->points[0].x, &container->points[0].y);

        container->points[1].x = container->points[0].x + container->transform.size.rect.width;
        container->points[1].y = container->points[0].y + container->transform.size.rect.height;
    }
    else if (container->transform.size.type == CIRC_TYPE)
    {
        container->pointCount = container->transform.size.circ.points;
        container->points = (int *)malloc(container->transform.size.circ.points * sizeof(int));

        int r = container->transform.size.circ.radius;
        int theta = 360 / container->transform.size.circ.points;
        for (int i = 0; i < container->transform.size.circ.points; i++)
        {
            polarToCartesian(r, theta * i, &container->points[i].x, &container->points[i].y);
        }
    };
}
//

// Draw calling for container
void PRIVATE_DEFAULT_CONTAINER_DRAW_CALLING(Container *container)
{

    // Create points
    container->createPoints(container);

    // Draw Itself
    if (container->drawSelf)
    {
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

    // Draw children
    if (container->drawChildren)
    {
        container->_drawChildren(container);
    }

    // End cut
    glDisable(GL_SCISSOR_TEST);
}
void PRIVATE_ERASE_CONTAINER(Container *container)
{

    free(container);
}
void makeContainer(Container *container, int ID)
{
    container->info.ID = ID;

    // Childs
    container->childAmount = 0;
    container

    // Points & Outline
}

Container *createContainer(void (*draw)(int *, int *, int, struct Container *), int ID)
{
    Container *container = (Container *)malloc(sizeof(Container));
    container->childAmount = 0;

    // Points & Outline
    container->pointCount = 0;
    container->outlineWidth = 0;
    container->createPoints = PRIVATE_DEFAULT_CONTAINER_CREATE_POINTS;

    // Colors
    setColorByVal(&container->backgroundColor, RGB_TYPE, 0, 0, 0);
    setColorByVal(&container->outlineColor, RGB_TYPE, 0, 0, 0);
    container->setColors = PRIVATE_DEFAULT_CONTAINER_SET_COLORS;

    container->draw = draw;
    container->drawCall = drawPrivateContainer;
    container->eraseSelf = eraseContainer;
    container->dfExists = false;
    return container;
}