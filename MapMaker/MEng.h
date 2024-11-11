#include <math.h>
#include <stdio.h>
#include <string.h>
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

int getPS()
{
    return MpixelScale;
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
    } // white
    if (c == 10)
    {
        rgb[0] = 21;
        rgb[1] = 29;
        rgb[2] = 40;
    }
    if (c == 11)
    {
        rgb[0] = 165;
        rgb[1] = 48;
        rgb[2] = 48;
    } // red

    glColor3ub(rgb[0], rgb[1], rgb[2]);
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

int fA[] =
    {
        5, 7,
        //-------------// A
        0, 1, 1, 1, 0, //
        1, 0, 0, 0, 1, //
        1, 1, 1, 1, 1, //
        1, 0, 0, 0, 1, //
        1, 0, 0, 0, 1, //
        1, 0, 0, 0, 1, //
        1, 0, 0, 0, 1, //
                       // B
        1, 1, 1, 1, 0, //
        1, 0, 0, 0, 1, //
        1, 1, 1, 1, 0, //
        1, 0, 0, 0, 1, //
        1, 0, 0, 0, 1, //
        1, 0, 0, 0, 1, //
        1, 1, 1, 1, 0, //
                       // C
        0, 1, 1, 1, 0, //
        1, 0, 0, 0, 1, //
        1, 0, 0, 0, 0, //
        1, 0, 0, 0, 0, //
        1, 0, 0, 0, 0, //
        1, 0, 0, 0, 1, //
        0, 1, 1, 1, 0, //
                       // D
        1, 1, 1, 1, 0, //
        1, 0, 0, 0, 1, //
        1, 0, 0, 0, 1, //
        1, 0, 0, 0, 1, //
        1, 0, 0, 0, 1, //
        1, 0, 0, 0, 1, //
        1, 1, 1, 1, 0, //
                       // E
        1, 1, 1, 1, 1, //
        1, 0, 0, 0, 0, //
        1, 0, 0, 0, 0, //
        1, 1, 1, 1, 0, //
        1, 0, 0, 0, 0, //
        1, 0, 0, 0, 0, //
        1, 1, 1, 1, 1, //
                       // F
        1, 1, 1, 1, 1, //
        1, 0, 0, 0, 0, //
        1, 0, 0, 0, 0, //
        1, 1, 1, 0, 0, //
        1, 0, 0, 0, 0, //
        1, 0, 0, 0, 0, //
        1, 0, 0, 0, 0, //
                       // G
        0, 1, 1, 1, 1, //
        1, 0, 0, 0, 0, //
        1, 0, 0, 1, 1, //
        1, 0, 0, 0, 1, //
        1, 0, 0, 0, 1, //
        1, 0, 0, 0, 1, //
        0, 1, 1, 1, 0, //
                       // H
        1, 0, 0, 0, 1, //
        1, 0, 0, 0, 1, //
        1, 1, 1, 1, 1, //
        1, 0, 0, 0, 1, //
        1, 0, 0, 0, 1, //
        1, 0, 0, 0, 1, //
        1, 0, 0, 0, 1, //
                       // I
        0, 1, 1, 1, 0, //
        0, 0, 1, 0, 0, //
        0, 0, 1, 0, 0, //
        0, 0, 1, 0, 0, //
        0, 0, 1, 0, 0, //
        0, 0, 1, 0, 0, //
        0, 1, 1, 1, 0, //
                       // J
        0, 0, 0, 0, 1, //
        0, 0, 0, 0, 1, //
        0, 0, 0, 0, 1, //
        0, 0, 0, 0, 1, //
        0, 0, 0, 0, 1, //
        1, 0, 0, 0, 1, //
        0, 1, 1, 1, 0, //
                       // K
        1, 0, 0, 0, 1, //
        1, 0, 0, 1, 0, //
        1, 1, 1, 0, 0, //
        1, 0, 0, 1, 0, //
        1, 0, 0, 0, 1, //
        1, 0, 0, 0, 1, //
        1, 0, 0, 0, 1, //
                       // L
        1, 0, 0, 0, 0, //
        1, 0, 0, 0, 0, //
        1, 0, 0, 0, 0, //
        1, 0, 0, 0, 0, //
        1, 0, 0, 0, 0, //
        1, 0, 0, 0, 0, //
        1, 1, 1, 1, 1, //
                       // M
        1, 0, 0, 0, 1, //
        1, 1, 0, 1, 1, //
        1, 0, 1, 0, 1, //
        1, 0, 0, 0, 1, //
        1, 0, 0, 0, 1, //
        1, 0, 0, 0, 1, //
        1, 0, 0, 0, 1, //
                       // N
        1, 0, 0, 0, 1, //
        1, 1, 0, 0, 1, //
        1, 0, 1, 0, 1, //
        1, 0, 0, 1, 1, //
        1, 0, 0, 0, 1, //
        1, 0, 0, 0, 1, //
        1, 0, 0, 0, 1, //
                       // O
        0, 1, 1, 1, 0, //
        1, 0, 0, 0, 1, //
        1, 0, 0, 0, 1, //
        1, 0, 0, 0, 1, //
        1, 0, 0, 0, 1, //
        1, 0, 0, 0, 1, //
        0, 1, 1, 1, 0, //
                       // P
        1, 1, 1, 1, 0, //
        1, 0, 0, 0, 1, //
        1, 1, 1, 1, 0, //
        1, 0, 0, 0, 0, //
        1, 0, 0, 0, 0, //
        1, 0, 0, 0, 0, //
        1, 0, 0, 0, 0, //
                       // Q
        0, 1, 1, 1, 0, //
        1, 0, 0, 0, 1, //
        1, 0, 0, 0, 1, //
        1, 0, 0, 0, 1, //
        1, 0, 0, 0, 1, //
        1, 0, 0, 1, 0, //
        0, 1, 1, 0, 1, //
                       // R
        1, 1, 1, 1, 0, //
        1, 0, 0, 0, 1, //
        1, 1, 1, 1, 0, //
        1, 0, 0, 0, 1, //
        1, 0, 0, 0, 1, //
        1, 0, 0, 0, 1, //
        1, 0, 0, 0, 1, //
                       // S
        0, 1, 1, 1, 1, //
        1, 0, 0, 0, 0, //
        0, 1, 1, 1, 0, //
        0, 0, 0, 0, 1, //
        0, 0, 0, 0, 1, //
        1, 0, 0, 0, 1, //
        0, 1, 1, 1, 0, //
                       // T
        1, 1, 1, 1, 1, //
        0, 0, 1, 0, 0, //
        0, 0, 1, 0, 0, //
        0, 0, 1, 0, 0, //
        0, 0, 1, 0, 0, //
        0, 0, 1, 0, 0, //
        0, 0, 1, 0, 0, //
                       // U
        1, 0, 0, 0, 1, //
        1, 0, 0, 0, 1, //
        1, 0, 0, 0, 1, //
        1, 0, 0, 0, 1, //
        1, 0, 0, 0, 1, //
        1, 0, 0, 0, 1, //
        0, 1, 1, 1, 0, //
                       // V
        1, 0, 0, 0, 1, //
        1, 0, 0, 0, 1, //
        1, 0, 0, 0, 1, //
        1, 0, 0, 0, 1, //
        0, 1, 0, 1, 0, //
        0, 1, 0, 1, 0, //
        0, 0, 1, 0, 0, //
                       // W
        1, 0, 0, 0, 1, //
        1, 0, 0, 0, 1, //
        1, 0, 0, 0, 1, //
        1, 0, 0, 0, 1, //
        1, 0, 1, 0, 1, //
        1, 1, 0, 1, 1, //
        1, 0, 0, 0, 1, //
                       // X
        1, 0, 0, 0, 1, //
        0, 1, 0, 1, 0, //
        0, 0, 1, 0, 0, //
        0, 1, 0, 1, 0, //
        1, 0, 0, 0, 1, //
        1, 0, 0, 0, 1, //
        1, 0, 0, 0, 1, //
                       // Z
        1, 1, 1, 1, 1, //
        0, 0, 0, 0, 1, //
        0, 0, 0, 1, 0, //
        0, 0, 1, 0, 0, //
        0, 1, 0, 0, 0, //
        1, 0, 0, 0, 0, //
        1, 1, 1, 1, 1  //
};

int *getFA()
{
    return fA;
}

int character(char c, int x, int y, int pScale, int pSize, int col, int *font)
{
    int xS = font[0];
    int S = font[0] * font[1];
    int p = ((c - 65) * S) + 2;
    // printf("(%d)-\n", p);
    // printf("ret");

    if (c == ' ')
    {
        return ((xS * pSize) / MpixelScale) + 1;
    }

    setCol(col);
    glPointSize(pSize);
    glBegin(GL_POINTS);
    for (int i = 0; i < S; i++)
    {
        // printf("%d,", font[p + i]);
        if (font[p + i] == 1)
        {
            glVertex2i(x * MpixelScale + (i % xS) * pSize, y * MpixelScale - (i / xS) * pSize);
        }
    }
    // printf("\n");
    /*
    glVertex2i(x * MpixelScale + 2, y * MpixelScale + 2);
    glVertex2i(x * MpixelScale + 2, y * MpixelScale + 4);
    glVertex2i(x * MpixelScale + 2, y * MpixelScale + 6);
    glVertex2i(x * MpixelScale + 2, y * MpixelScale + 8);
    glVertex2i(x * MpixelScale + 4, y * MpixelScale + 10);
    glVertex2i(x * MpixelScale + 6, y * MpixelScale + 10);
    glVertex2i(x * MpixelScale + 8, y * MpixelScale + 8);
    glVertex2i(x * MpixelScale + 8, y * MpixelScale + 6);
    glVertex2i(x * MpixelScale + 8, y * MpixelScale + 4);
    glVertex2i(x * MpixelScale + 8, y * MpixelScale + 2);
    glVertex2i(x * MpixelScale + 6, y * MpixelScale + 4);
    glVertex2i(x * MpixelScale + 4, y * MpixelScale + 4);
    */
    glEnd();
    return ((xS * pSize) / MpixelScale) + 1;
}

int write(char *text, int x, int y, int pScale, int pSize, int col, int *font)
{
    int xI = x;
    for (size_t i = 0; i < strlen(text); i++)
    {
        x += character(text[i], x, y, pScale, pSize, col, font);
    }
    return x - xI;
}
