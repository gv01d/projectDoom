#include "Color.h"

int pixelScale;

void Draw_SetPixelScale(int pS)
{
    pixelScale = pS;
}

void Draw_pixel(int x, int y, Color *color, int w) // draw a pixel at x/y with rgb
{

    setColor(color);

    glPointSize(w);
    glBegin(GL_POINTS);
    glVertex2i(x * pixelScale + 2, y * pixelScale + 2);
    glEnd();
}

void Draw_line(int x1, int y1, int x2, int y2, Color *color, int w)
{

    setColor(color);

    glLineWidth(w);
    glBegin(GL_LINES);
    glVertex2i(x1 * pixelScale + 2, y1 * pixelScale + 2);
    glVertex2i(x2 * pixelScale + 2, y2 * pixelScale + 2);
    glEnd();
}

void Draw_quads(int x1, int y1, int x2, int y2, Color *color)
{
    setColor(color);

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

void Draw_Polygon(Vector2 *points, int amount, Color *color)
{
    printf("Drawing Polygon\n");
    setColor(color);

    glBegin(GL_POLYGON);
    for (size_t i = 0; i < amount; i++)
    {
        glVertex2i(points[i].x * pixelScale + 2, points[i].y * pixelScale + 2);
    }
    glEnd();
}
/*
    TODO : Add outline width
*/
void Draw_PolygonOutline(Vector2 *points, int amount, Color *color, int width)
{
    if (width < 1)
    {
        return;
    }

    setColor(color);

    // get width
    int glWidth = glutGet(GL_LINE_WIDTH);
    glLineWidth(width * glWidth);
    glBegin(GL_LINE_LOOP);
    for (size_t i = 0; i < amount; i++)
    {
        glVertex2i(points[i].x * pixelScale + 2, points[i].y * pixelScale + 2);
    }
    glEnd();
    glLineWidth(glWidth);
}