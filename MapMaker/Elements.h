#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

// <===================================================================================================================>

//  /=======================================\ 
// <--------------- Atributes --------------->
//  \=======================================/

// <===================================================================================================================>

enum PositionType
{
    CARTESIAN_TYPE,  // 0
    POLAR_TYPE,      // 1
    REFERENCIAL_TYPE // 2
};

typedef struct Position // Define position
{
    union
    {
        struct // cartesian ( X, Y )
        {
            int x, y;
        } cartesian;
        struct // Polar ( R, A )
        {
            int r;
            int A;
        } polar;
        struct // Referencial ( X, Y, Xg, Yg )
        {
            struct
            {
                int *x, *y;
            } parent;
            int x, y;
        } referencial;
    };

    enum PositionType type;

    // functions
    void (*setSelf)(struct Position *, enum PositionType, int, int);
    void (*setReferencialSelf)(struct Position *, int, int, int *, int *);
    void (*eraseSelf)(struct Position *);

} Position;
void setPosition(struct Position *, enum PositionType, int, int);
void setReferencialPosition(struct Position *, int, int, int *, int *);
void erasePosition(struct Position *);
void setPosition(Position *pos, enum PositionType type, int x, int y) // Set position
{
    pos->type = type;
    if (type == CARTESIAN_TYPE) // cartesian (0)
    {
        pos->cartesian.x = x;
        pos->cartesian.y = y;
    }
    else if (type == POLAR_TYPE) // Polar (1)
    {
        pos->polar.r = x;
        pos->polar.A = y;
    }
}
void setReferencialPosition(Position *pos, int x, int y, int *parentX, int *parentY) // Set referencial position
{
    pos->type = REFERENCIAL_TYPE;
    pos->referencial.x = x;
    pos->referencial.y = y;
    pos->referencial.parent.x = parentX;
    pos->referencial.parent.y = parentY;
}
void erasePosition(Position *pos) // Erase position
{
    free(pos);
}
Position *newPosition() // Position constructor
{
    Position *pos = (Position *)malloc(sizeof(Position));
    pos->setSelf = setPosition;
    pos->setReferencialSelf = setReferencialPosition;
    pos->eraseSelf = erasePosition;
    return pos;
}

//  <===================================================================================================================>

enum SizeType
{
    RECT_TYPE, // 0
    CIRC_TYPE, // 1
};

typedef struct Size // Define size
{
    union
    {
        struct // Rectangle ( Height, Width )
        {
            int height, width;
        } rect;
        struct // Circle ( Radius )
        {
            int radius;
            int points;
        } circ;
    };

    enum SizeType type;

    // functions
    void (*setSelf)(struct Size *, enum SizeType, int, int);
    void (*eraseSelf)(struct Size *);

} Size;

void setSize(struct Size *, enum SizeType, int, int);               // Declare setSize function
void setSize(Size *size, enum SizeType type, int height, int width) // Set size
{
    size->type = type;
    if (type == RECT_TYPE) // Rectangle (0)
    {
        size->rect.height = height;
        size->rect.width = width;
    }
    else if (type == CIRC_TYPE) // Circle (1)
    {
        size->circ.radius = height;
    }
}
void eraseSize(Size *size) // Erase size
{
    free(size);
}
Size *newSize() // Size constructor
{
    Size *size = (Size *)malloc(sizeof(Size));
    size->setSelf = setSize;
    size->eraseSelf = eraseSize;
    return size;
}

// <===================================================================================================================>

enum ColorType
{
    ID_TYPE,  // 0
    RGB_TYPE, // 1
    HSV_TYPE  // 2
};

typedef struct Color // Define color
{
    union
    {
        int id;
        struct
        {
            int r, g, b;
        } rgb;
        struct
        {
            int h, s, v;
        } hsv;
    };

    enum ColorType type;

    // functions
    void (*setSelfID)(struct Color *, int);
    void (*setSelfVal)(struct Color *, enum ColorType, int, int, int);
    void (*eraseSelf)(struct Color *);
} Color;

void setColorVal(Color *col, enum ColorType type, int r, int g, int b); // Declare setColorVal function

void setColorID(Color *col, int id) // Set color ID
{
    col->type = ID_TYPE;
    col->id = id;
}
void setColorVal(Color *col, enum ColorType type, int r, int g, int b) // Set color value
{
    if (type == RGB_TYPE) // RGB (1)
    {
        col->type = RGB_TYPE;
        col->rgb.r = r;
        col->rgb.g = g;
        col->rgb.b = b;
    }
    else if (type == HSV_TYPE) // HSV (2)
    {
        col->type = HSV_TYPE;
        col->hsv.h = r;
        col->hsv.s = g;
        col->hsv.v = b;
    }
}
void eraseColor(Color *col) // Erase color
{
    free(col);
}
Color *newColor() // Color constructor
{
    Color *col = (Color *)malloc(sizeof(Color));
    col->setSelfID = setColorID;
    col->setSelfVal = setColorVal;
    col->eraseSelf = eraseColor;
    return col;
}

// <===================================================================================================================>

//  /=====================================\ 
// <--------------- Modules --------------->
//  \=====================================/

//  <===================================================================================================================>

typedef struct Info
{
    int ID;

    // functions

    void (*eraseSelf)(struct Info *);
} Private_Info;

void eraseInfo(Private_Info *info)
{
    free(info);
}
Private_Info *newInfo()
{
    Private_Info *info = (Private_Info *)malloc(sizeof(Private_Info));
    info->eraseSelf = eraseInfo;
    return info;
}

//  <===================================================================================================================>

typedef struct Transform // Define transform
{
    Position pos;
    Size size;

    // functions
    void (*eraseSelf)(struct Transform *);

} Private_Transform;
void eraseTransform(Private_Transform *transform) // Erase transform
{
    transform->pos.eraseSelf(&transform->pos);
    transform->size.eraseSelf(&transform->size);
    free(transform);
}
Private_Transform *newTransform() // new transform
{
    Private_Transform *transform = (Private_Transform *)malloc(sizeof(Private_Transform));
    transform->pos = *newPosition();
    transform->size = *newSize();
    transform->eraseSelf = eraseTransform;
    return transform;
}

//  <===================================================================================================================>

typedef struct ContainerBox
{
    Private_Transform transform;
    Color col;

    // functions
    void (*eraseSelf)(struct ContainerBox *);
} Private_ContainerBox;
void eraseContainerBox(Private_ContainerBox *box) // Erase container box
{
    box->transform.eraseSelf(&box->transform);
    box->col.eraseSelf(&box->col);
    free(box);
}
Private_ContainerBox *newContainerBox() // new container box
{
    Private_ContainerBox *box = (Private_ContainerBox *)malloc(sizeof(Private_ContainerBox));
    box->transform = *newTransform();
    box->col = *newColor();
    return box;
}

//  /======================================\ 
// <--------------- Definers --------------->
//  \======================================/

#define PI 3.14159265
#define MAX_ANGLES 360

// Tabelas para armazenar senos e cossenos
float sin_table[MAX_ANGLES];
float cos_table[MAX_ANGLES];

// Função para inicializar as tabelas
void inicializar_tabelas()
{
    for (int i = 0; i < MAX_ANGLES; i++)
    {
        float rad = (i * PI) / 180.0; // Convertendo para radianos
        sin_table[i] = sin(rad);
        cos_table[i] = cos(rad);
    }
}

// Função para converter de coordenadas polares para cartesianas usando as tabelas
void polarToCartesian(int r, int theta, int *x, int *y)
{
    // Garantir que o ângulo esteja no intervalo de 0 a 359
    theta = theta % MAX_ANGLES;
    *x = (int)(r * cos_table[theta]);
    *y = (int)(r * sin_table[theta]);
}

void definePos(Position *pos, int *x, int *y)
{
    if (pos->type == CARTESIAN_TYPE)
    {
        x = &pos->cartesian.x;
        y = &pos->cartesian.y;
    }
    else if (pos->type == POLAR_TYPE)
    {
        polarToCartesian(pos->polar.r, pos->polar.A, x, y);
    }
    else if (pos->type == REFERENCIAL_TYPE)
    {
        x = pos->referencial.parent.x + pos->referencial.x;
        y = pos->referencial.parent.y + pos->referencial.y;
    }
}

void drawByType(Size size, int x1, int y1)
{
    if (size.type == RECT_TYPE)
    {
        int x2 = x1 + size.rect.width;
        int y2 = y1 + size.rect.height;
        // Draw rectangle
    }
    else if (size.type == CIRC_TYPE)
    {
        // Draw circle
    }
}

//  /======================================\ 
// <--------------- Elements --------------->
//  \======================================/

//  <===================================================================================================================>
typedef struct Base // Define base
{
    Private_Info info;
    Position pos;
    Size size;

    // functions

    void (*eraseSelf)(struct Base *);
    void (*drawCall)(struct Base *);
    void (*drawFunc)();
    void (*functionBaseDefine)(struct Base *, void (*)());
} Base;

void draw(Base *base)
{
    int *x;
    int *y;
    if (base->size.type == RECT_TYPE)
    {
        x = (int *)malloc(2 * sizeof(int));
        y = (int *)malloc(2 * sizeof(int));

        definePos(&base->pos, &x[0], &y[0]);

        x[1] = x[0] + base->size.rect.width;
        y[1] = y[0] + base->size.rect.height;
        glEnable(GL_SCISSOR_TEST);
        glScissor(x[0], y[0], x[1], y[1]);
    }
    else if (base->size.type == CIRC_TYPE)
    {
        x = (int *)malloc(base->size.circ.points * sizeof(int));
        y = (int *)malloc(base->size.circ.points * sizeof(int));

        int r = base->size.circ.radius;
        int theta = 360 / base->size.circ.points;
        for (int i = 0; i < base->size.circ.points; i++)
        {
            polarToCartesian(r, theta * i, &x[i], &y[i]);
        }
    }

    base->drawFunc();

    glDisable(GL_SCISSOR_TEST);
}
void functionBaseDefine(Base *base, void (*drawFunc)())
{
    base->drawFunc = drawFunc;
}
void eraseBase(Base *base)
{
    base->info.eraseSelf(&base->info);
    base->pos.eraseSelf(&base->pos);
    base->size.eraseSelf(&base->size);
    free(base);
}
Base *newBase()
{
    Base *base = (Base *)malloc(sizeof(Base));
    base->info = *newInfo();
    base->pos = *newPosition();
    base->size = *newSize();
    base->eraseSelf = eraseBase;
    base->drawCall = draw;
    return base;
}

//  <===================================================================================================================>

typedef struct Container
{
    Private_Info info;
    Private_Transform transform;
    Color col[20];

    // functions

    void (*eraseSelf)(struct Container *);
    void (*drawCall)(struct Container *);
    void (*draw)(int *, int *, int, struct Container *);
    void (*drawFunc)();
    void *drawFuncArgs;
} Container;
void drawContainer(Container *container)
{
    int *x;
    int *y;
    int n;
    if (container->transform.size.type == RECT_TYPE)
    {
        n = 2;
        x = (int *)malloc(2 * sizeof(int));
        y = (int *)malloc(2 * sizeof(int));

        definePos(&container->transform.pos, &x[0], &y[0]);

        x[1] = x[0] + container->transform.size.rect.width;
        y[1] = y[0] + container->transform.size.rect.height;
        glEnable(GL_SCISSOR_TEST);
        glScissor(x[0], y[0], x[1], y[1]);
    }
    else if (container->transform.size.type == CIRC_TYPE)
    {
        x = (int *)malloc(container->transform.size.circ.points * sizeof(int));
        y = (int *)malloc(container->transform.size.circ.points * sizeof(int));

        int r = container->transform.size.circ.radius;
        int theta = 360 / container->transform.size.circ.points;
        for (int i = 0; i < container->transform.size.circ.points; i++)
        {
            polarToCartesian(r, theta * i, &x[i], &y[i]);
        }
    }

    container->draw(x, y, n, container);

    container->drawFunc();

    // Draw container

    glDisable(GL_SCISSOR_TEST);
}
void eraseContainer(Container *container)
{
    container->info.eraseSelf(&container->info);
    container->transform.eraseSelf(&container->transform);
    for (int i = 0; i < 20; i++)
    {
        container->col[i].eraseSelf(&container->col[i]);
    }

    free(container);
}
Container *createContainer(void (*draw)(int *, int *, int, struct Container *))
{
    Container *container = (Container *)malloc(sizeof(Container));
    container->info = *newInfo();
    container->transform = *newTransform();
    for (int i = 0; i < 20; i++)
    {
        container->col[i] = *newColor();
    }
    container->draw = draw;
    container->drawCall = drawContainer;
    container->eraseSelf = eraseContainer;
    return container;
}
