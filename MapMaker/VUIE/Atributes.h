#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

// <===================================================================================================================>

//

//  /=======================================\ 
// <--------------- Atributes --------------->
//  \=======================================/

//

// <===================================================================================================================>

//

//

//

#include "Modules/modules.h"
typedef struct Child
{
    enum elementType type;
    union
    {
        Base base;
        Container container;
    };

} Child;

Child *newChild(enum elementType type, void *element)
{
    Child *child = (Child *)malloc(sizeof(Child));
    child->type = type;
    if (type == BASE)
    {
        child->base = *(Base *)element;
    }
    else if (type == CONTAINER)
    {
        child->container = *(Container *)element;
    }
    return child;
}

int getChildID(Child *child)
{
    switch (child->type)
    {
    case BASE:
        return child->base.info.ID;
        break;
    case CONTAINER:
        return child->container.info.ID;
        break;
    default:
        break;
    }
}
void freeChild(Child *child)
{
    switch (child->type)
    {
    case CONTAINER:
        child->container.free(&child->container);
        break;

    default:
        break;
    }
}

// <===================================================================================================================>

//

//

//
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

} Position;
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
void copyPosition(Position *pos, Position *copy) // Copy position
{
    pos->type = copy->type;
    if (copy->type == CARTESIAN_TYPE) // cartesian (0)
    {
        pos->cartesian.x = copy->cartesian.x;
        pos->cartesian.y = copy->cartesian.y;
    }
    else if (copy->type == POLAR_TYPE) // Polar (1)
    {
        pos->polar.r = copy->polar.r;
        pos->polar.A = copy->polar.A;
    }
    else if (copy->type == REFERENCIAL_TYPE) // Referencial (2)
    {
        pos->referencial.x = copy->referencial.x;
        pos->referencial.y = copy->referencial.y;
        pos->referencial.parent.x = copy->referencial.parent.x;
        pos->referencial.parent.y = copy->referencial.parent.y;
    }
}

//  <===================================================================================================================>

//

//

//

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

} Size;
void setSize(struct Size *size, enum SizeType type, int height, int width) // Set size
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
void copySize(Size *size, Size *copy) // Copy size
{
    size->type = copy->type;
    if (copy->type == RECT_TYPE) // Rectangle (0)
    {
        size->rect.height = copy->rect.height;
        size->rect.width = copy->rect.width;
    }
    else if (copy->type == CIRC_TYPE) // Circle (1)
    {
        size->circ.radius = copy->circ.radius;
        size->circ.points = copy->circ.points;
    }
}

// <===================================================================================================================>

//

//

//

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
} Color;

void setColorByID(Color *col, int id) // Set color ID
{
    col->type = ID_TYPE;
    col->id = id;
}
void setColorByVal(Color *col, enum ColorType type, int r, int g, int b) // Set color value
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
Color RGBColor(int r, int g, int b)
{
    Color col;
    setColorByVal(&col, RGB_TYPE, r, g, b);
    return col;
}
void copyColor(Color *col, Color *copy) // Copy color
{
    col->type = copy->type;
    if (copy->type == ID_TYPE) // ID (0)
    {
        col->id = copy->id;
    }
    else if (copy->type == RGB_TYPE) // RGB (1)
    {
        col->rgb.r = copy->rgb.r;
        col->rgb.g = copy->rgb.g;
        col->rgb.b = copy->rgb.b;
    }
    else if (copy->type == HSV_TYPE) // HSV (2)
    {
        col->hsv.h = copy->hsv.h;
        col->hsv.s = copy->hsv.s;
        col->hsv.v = copy->hsv.v;
    }
}

// <===================================================================================================================>

//

//

//

typedef struct Info
{
    int ID;

} Private_Info;
void setInfo(Private_Info *info, int ID)
{
    if (info == NULL)
    {
        printf("<WARNING> : Info is null\n");
    }

    if (ID < 0)
    {
        // ID -1 = null
        ID = -1;
    }
    info->ID = ID;
}
void copyInfo(Private_Info *info, Private_Info *copy)
{
    info->ID = copy->ID;
}
// <===================================================================================================================>

//

//

//

//  <===================================================================================================================>

//

//  /======================================\ 
// <--------------- Definers --------------->
//  \======================================/

//

//  <===================================================================================================================>

#define PI 3.14159265
#define MAX_ANGLES 360

typedef struct
{
    int x, y;
} Vector2;

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
        *x = pos->cartesian.x;
        *y = pos->cartesian.y;
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

//  <===================================================================================================================>

//

//  /======================================\ 
// <--------------- Elements --------------->
//  \======================================/

//

//  <===================================================================================================================>

//  <===================================================================================================================>
