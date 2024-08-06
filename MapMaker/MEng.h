#include <math.h>
#include <stdio.h>
#include <GL/glut.h>
#include <stdbool.h>

int MpixelScale;

int MSH;
int MSW;

void setPS(int pS)
{
    MpixelScale = pS;
}

void setSH(int SH)
{
    MSH = SH;
}

void setSW(int SW)
{
    MSW = SW;
}

void setCol(int c)
{
    int rgb[3];
    if (c == 0)
    {
        rgb[0] = 255;
        rgb[1] = 255;
        rgb[2] = 0;
    } // Yellow
    if (c == 1)
    {
        rgb[0] = 160;
        rgb[1] = 160;
        rgb[2] = 0;
    } // Yellow darker
    if (c == 2)
    {
        rgb[0] = 0;
        rgb[1] = 255;
        rgb[2] = 0;
    } // Green
    if (c == 3)
    {
        rgb[0] = 0;
        rgb[1] = 160;
        rgb[2] = 0;
    } // Green darker
    if (c == 4)
    {
        rgb[0] = 0;
        rgb[1] = 255;
        rgb[2] = 255;
    } // Cyan
    if (c == 5)
    {
        rgb[0] = 0;
        rgb[1] = 160;
        rgb[2] = 160;
    } // Cyan darker
    if (c == 6)
    {
        rgb[0] = 160;
        rgb[1] = 100;
        rgb[2] = 0;
    } // brown
    if (c == 7)
    {
        rgb[0] = 110;
        rgb[1] = 50;
        rgb[2] = 0;
    } // brown darker
    if (c == 8)
    {
        rgb[0] = 9;
        rgb[1] = 10;
        rgb[2] = 20;
    } // background
    if (c == 9)
    {
        rgb[0] = 255;
        rgb[1] = 255;
        rgb[2] = 255;
    }
    if (c == 10)
    {
        rgb[0] = 21;
        rgb[1] = 29;
        rgb[2] = 40;
    }

    glColor3ub(rgb[0], rgb[1], rgb[2]);
}

void pixel(int x, int y, int c, int w) // draw a pixel at x/y with rgb
{

    setCol(c);

    glPointSize(w);
    glBegin(GL_POINTS);
    glVertex2i(x * MpixelScale + 2, y * MpixelScale + 2);
    glEnd();
}

void line(int x1, int y1, int x2, int y2, int c, int w)
{

    setCol(c);

    glLineWidth(w);
    glBegin(GL_LINES);
    glVertex2i(x1 * MpixelScale + 2, y1 * MpixelScale + 2);
    glVertex2i(x2 * MpixelScale + 2, y2 * MpixelScale + 2);
    glEnd();
}

void quads(int x1, int y1, int x2, int y2, int c)
{
    setCol(c);

    glBegin(GL_QUADS);
    glVertex2i(x1 * MpixelScale + 2, y1 * MpixelScale + 2);
    glVertex2i(x1 * MpixelScale + 2, y2 * MpixelScale + 2);
    glVertex2i(x2 * MpixelScale + 2, y2 * MpixelScale + 2);
    glVertex2i(x2 * MpixelScale + 2, y1 * MpixelScale + 2);
    glEnd();
}

void clearBackground()
{
    int x, y;
    for (y = 0; y < MSH; y++)
    {
        for (x = 0; x < MSW; x++)
        {
            pixel(x, y, 8, MpixelScale);
        } // clear background color
    }
}

int dist(int x1, int y1, int x2, int y2)
{
    int distance = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    return distance;
}

bool decBox(int x1, int y1, int x2, int y2, int px, int py)
{
    if (x1 > x2)
    {
        if (px > x1 || px < x2)
        {
            return false;
        }
    }
    if (x1 <= x2)
    {
        if (px < x1 || px > x2)
        {
            return false;
        }
    }

    if (y1 > y2)
    {
        if (py > y1 || py < y2)
        {
            return false;
        }
    }
    if (y1 <= y2)
    {
        if (py < y1 || py > y2)
        {
            return false;
        }
    }

    return true;
}
