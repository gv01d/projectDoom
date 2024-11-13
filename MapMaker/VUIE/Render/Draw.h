#include <math.h>

#include "Color.h"

#define PI 3.14159265
#define MAX_ANGLES 360

typedef struct Vector2
{
    int x, y;
} Vector2;

int *pixelScale;

void Draw_SetPixelScale(int *pS)
{
    pixelScale = pS;
}

void Draw_pixel(int x, int y, Color *color, int w) // draw a pixel at x/y with rgb
{

    setGLColor(color);

    glPointSize(*pixelScale * w);
    glBegin(GL_POINTS);
    glVertex2i(x * *pixelScale, y * *pixelScale);
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

void Draw_Polygon(Vector2 *points, int amount, Color *color)
{
    setGLColor(color);

    glBegin(GL_POLYGON);
    // printf("Amount : %d\n", amount);
    for (int i = 0; i < amount; i++)
    {
        glVertex2i(points[i].x * *pixelScale + (*pixelScale / 2), points[i].y * *pixelScale + (*pixelScale / 2));
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