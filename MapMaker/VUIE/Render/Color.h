#include <GL/glut.h>

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
            float r, g, b;
        } rgb;
        struct
        {
            float h, s, v;
        } hsv;
    };

    enum ColorType type;
} Color;

void setColorByID(Color *col, int id) // Set color ID
{
    col->type = ID_TYPE;
    col->id = id;
}
void setColorByVal(Color *col, enum ColorType type, float r, float g, float b) // Set color value
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
Color *RGBColor(float r, float g, float b)
{
    Color *col = (Color *)malloc(sizeof(Color));
    setColorByVal(col, RGB_TYPE, r, g, b);
    return col;
}
Color *IDColor(int id)
{
    Color *col = (Color *)malloc(sizeof(Color));
    setColorByID(col, id);
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

void setGLColorByID(int id)
{
    if (id == 0)
    {
        glColor3f(1.0, 1.0, 0.0);
    } // Yellow
    if (id == 1)
    {
        glColor3f(0.63, 0.63, 0.0);
    } // Yellow darker
    if (id == 2)
    {
        glColor3f(0.0, 1.0, 0.0);
    } // Green
    if (id == 3)
    {
        glColor3f(0.0, 0.63, 0.0);
    } // Green darker
    if (id == 4)
    {
        glColor3f(0.0, 1.0, 1.0);
    } // Cyan
    if (id == 5)
    {
        glColor3f(0.0, 0.63, 0.63);
    } // Cyan darker
    if (id == 6)
    {
        glColor3f(0.0, 0.0, 1.0);
    } // Blue
    if (id == 7)
    {
        glColor3f(0.0, 0.0, 0.63);
    } // Blue darker
    if (id == 8)
    {
        glColor3f(1.0, 0.0, 1.0);
    } // Magenta
    if (id == 9)
    {
        glColor3f(0.63, 0.0, 0.63);
    } // Magenta darker
    if (id == 10)
    {
        glColor3f(1.0, 0.0, 0.0);
    } // Red
    if (id == 11)
    {
        glColor3f(0.63, 0.0, 0.0);
    } // Red darker
    if (id == 12)
    {
        glColor3f(1.0, 1.0, 1.0);
    } // White
}

void setGLColorByRGB(float r, float g, float b)
{
    glColor3f(r, g, b);
}

void setGLCOlorByHSV(float H, float S, float V)
{
    float r, g, b;

    float h = H / 360;
    float s = S / 100;
    float v = V / 100;

    int i = floor(h * 6);
    float f = h * 6 - i;
    float p = v * (1 - s);
    float q = v * (1 - f * s);
    float t = v * (1 - (1 - f) * s);

    switch (i % 6)
    {
    case 0:
        r = v, g = t, b = p;
        break;
    case 1:
        r = q, g = v, b = p;
        break;
    case 2:
        r = p, g = v, b = t;
        break;
    case 3:
        r = p, g = q, b = v;
        break;
    case 4:
        r = t, g = p, b = v;
        break;
    case 5:
        r = v, g = p, b = q;
        break;
    }

    glColor3f(r, g, b);
}

void setGLColor(Color *col)
{
    if (col->type == ID_TYPE)
    {
        setGLColorByID(col->id);
    }
    else if (col->type == RGB_TYPE)
    {
        setGLColorByRGB(col->rgb.r, col->rgb.g, col->rgb.b);
    }
    else if (col->type == HSV_TYPE)
    {
        setGLCOlorByHSV(col->hsv.h, col->hsv.s, col->hsv.v);
    }
}