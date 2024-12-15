#include <math.h>

#include "Color.h"

#define PI 3.14159265
#define MAX_ANGLES 360

typedef struct glScissorSaveState
{

    int x, y;
    int width, height;
    int scale;

} glScissorSaveState;

bool glScissorEnabled = false;
glScissorSaveState globalGlScissor;

typedef struct Vector2
{
    int x, y;
} Vector2;

enum
{
    FRAME_BOTTOM_RIGHT,
    FRAME_BOTTOM_LEFT,
    FRAME_TOP_RIGHT,
    FRAME_TOP_LEFT,
    FRAME_MIDDLE,
    FRAME_CUSTOM

} VUIE_GL_FRAME_PRESET;

struct
{
    float x, y;
    float x2, y2;
} VUIE_GL_FRAME;

int *pixelScale;

void GL_Scissors(int x, int y, int width, int height, int scale)
{
    glScissor(x - VUIE_GL_FRAME.x + (scale / 2), y - VUIE_GL_FRAME.y + (scale / 2), width, height);
}

int sign(int t)
{
    if (t > 0)
    {
        return 1;
    }
    else if (t < 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

void scissorsIntercection(glScissorSaveState *result, int xa, int xb, int wa, int wb, int ya, int yb, int ha, int hb)
{

    int x1a = xa, x1b = xb;
    int x2a = xa + wa, x2b = xb + wb;

    int y1a = ya, y1b = yb;
    int y2a = ya + ha, y2b = yb + hb;

    if (x1a > x1b)
    {
        result->x = x1a;
    }
    else
    {
        result->x = x1b;
    }

    if (x2a < x2b)
    {
        result->width = x2a - result->x;
    }
    else
    {
        result->width = x2b - result->x;
    }
    if (result->width < 0)
    {
        result->width = 0;
    }

    if (y1a > y1b)
    {
        result->y = y1a;
    }
    else
    {
        result->y = y1b;
    }

    if (y2a < y2b)
    {
        result->height = y2a - result->y;
    }
    else
    {
        result->height = y2b - result->y;
    }
    if (result->height < 0)
    {
        result->height = 0;
    }
}

void Draw_SetPixelScale(int *pS)
{
    pixelScale = pS;
}

void Draw_pixel(int x, int y, Color *color, int w) // draw a pixel at x/y with rgb
{

    setGLColor(color);

    glPointSize(*pixelScale * w);
    glBegin(GL_POINTS);
    glVertex2i((x * *pixelScale), (y * *pixelScale));
    glEnd();
}

void Draw_Pixels(int amount, Vector2 *points, Color *color, int w)
{

    setGLColor(color);
    glPointSize(*pixelScale * w);
    glBegin(GL_POINTS);
    for (int i = 0; i < amount; i++)
    {
        glVertex2i(points[i].x * *pixelScale, points[i].y * *pixelScale);
    }
    glEnd();
}

void Draw_line(int x1, int y1, int x2, int y2, Color *color, int w)
{

    setGLColor(color);

    glLineWidth(*pixelScale * w);
    glBegin(GL_LINES);
    glVertex2i(x1 * *pixelScale, y1 * *pixelScale);
    glVertex2i(x2 * *pixelScale, y2 * *pixelScale);
    glEnd();
}

void Draw_quads(int x1, int y1, int x2, int y2, Color *color)
{
    setGLColor(color);

    glBegin(GL_QUADS);
    glVertex2i(x1 * *pixelScale, y1 * *pixelScale);
    glVertex2i(x1 * *pixelScale, y2 * *pixelScale);
    glVertex2i(x2 * *pixelScale, y2 * *pixelScale);
    glVertex2i(x2 * *pixelScale, y1 * *pixelScale);
    glEnd();
}

int dist(int x1, int y1, int x2, int y2)
{
    int distance = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    return distance;
}

// POLYGON

void Draw_Polygon(Vector2 *points, int amount, Color *color, int Scale)
{
    setGLColor(color);

    glBegin(GL_POLYGON);
    // printf("Amount : %d\n", amount);
    for (int i = 0; i < amount; i++)
    {
        glVertex2i(points[i].x + (Scale / 2), points[i].y + (Scale / 2));
        // printf("%d : (%d, %d)\n", i, points[i].x, points[i].y);
    }
    glEnd();
}
void Draw_PolygonOutline(Vector2 *points, int amount, Color *color, int width)
{
    if (width < 1)
    {
        return;
    }

    setGLColor(color);

    // get width
    glLineWidth(width);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < amount; i++)
    {
        glVertex2i(points[i].x + (*pixelScale / 2), points[i].y + (*pixelScale / 2));
    }
    glEnd();
    glLineWidth(*pixelScale);
}

/*
void runTest()
{
    glColor3f(1.0, 0.0, 0.0);

    Vector2 points[4];

    points[0].x = 10;
    points[0].y = 10;
    points[1].x = 20;
    points[1].y = 10;
    points[2].x = 20;
    points[2].y = 20;
    points[3].x = 10;
    points[3].y = 20;

    glBegin(GL_POLYGON);
    for (int i = 0; i < 4; i++)
    {
        glVertex2i(points[i].x * pixelScale + 2, points[i].y * pixelScale + 2);
    }

    glEnd();
}
// */