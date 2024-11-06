#include "Color.h"

int pixelScale;

void Draw_SetPixelScale(int pS)
{
    pixelScale = pS;
}

void pixel(int x, int y, Color col, int w) // draw a pixel at x/y with rgb
{

    setColor(col);

    glPointSize(w);
    glBegin(GL_POINTS);
    glVertex2i(x * pixelScale + 2, y * pixelScale + 2);
    glEnd();
}

void line(int x1, int y1, int x2, int y2, Color c, int w)
{

    setColor(c);

    glLineWidth(w);
    glBegin(GL_LINES);
    glVertex2i(x1 * pixelScale + 2, y1 * pixelScale + 2);
    glVertex2i(x2 * pixelScale + 2, y2 * pixelScale + 2);
    glEnd();
}

void quads(int x1, int y1, int x2, int y2, Color c)
{
    setColor(c);

    glBegin(GL_QUADS);
    glVertex2i(x1 * pixelScale + 2, y1 * pixelScale + 2);
    glVertex2i(x1 * pixelScale + 2, y2 * pixelScale + 2);
    glVertex2i(x2 * pixelScale + 2, y2 * pixelScale + 2);
    glVertex2i(x2 * pixelScale + 2, y1 * pixelScale + 2);
    glEnd();
}

int dist(int x1, int y1, int x2, int y2)
{
    int distance = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    return distance;
}

// POLYGON

void Polygon(Vector2 *points, int amount, Color col)
{
    setColor(col);

    glBegin(GL_POLYGON);
    for (size_t i = 0; i < amount; i++)
    {
        glVertex2i(points[i].x * pixelScale + 2, points[i].y * pixelScale + 2);
    }
    glEnd();
}

void PolygonOutline(Vector2 *points, int amount, Color col)
{
    setColor(col);

    glBegin(GL_LINE_LOOP);
    for (size_t i = 0; i < amount; i++)
    {
        glVertex2i(points[i].x * pixelScale + 2, points[i].y * pixelScale + 2);
    }
    glEnd();
}