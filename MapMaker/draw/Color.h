#include <GL/freeglut.h>
#include "../VUIE/Atributes.h"

void setColor(Color col)
{
    if (col.type == ID_TYPE)
    {
        if (col.id == 0)
        {
            glColor3f(1.0, 1.0, 0.0);
        } // Yellow
        if (col.id == 1)
        {
            glColor3f(0.63, 0.63, 0.0);
        } // Yellow darker
        if (col.id == 2)
        {
            glColor3f(0.0, 1.0, 0.0);
        } // Green
        if (col.id == 3)
        {
            glColor3f(0.0, 0.63, 0.0);
        } // Green darker
        if (col.id == 4)
        {
            glColor3f(0.0, 1.0, 1.0);
        } // Cyan
        if (col.id == 5)
        {
            glColor3f(0.0, 0.63, 0.63);
        } // Cyan darker
        if (col.id == 6)
        {
            glColor3f(0.0, 0.0, 1.0);
        } // Blue
        if (col.id == 7)
        {
            glColor3f(0.0, 0.0, 0.63);
        } // Blue darker
        if (col.id == 8)
        {
            glColor3f(1.0, 0.0, 1.0);
        } // Magenta
        if (col.id == 9)
        {
            glColor3f(0.63, 0.0, 0.63);
        } // Magenta darker
        if (col.id == 10)
        {
            glColor3f(1.0, 0.0, 0.0);
        } // Red
        if (col.id == 11)
        {
            glColor3f(0.63, 0.0, 0.0);
        } // Red darker
        if (col.id == 12)
        {
            glColor3f(1.0, 1.0, 1.0);
        } // White
    }
    else if (col.type == RGB_TYPE)
    {
        glColor3f(col.rgb.r, col.rgb.g, col.rgb.b);
    }
    else if (col.type == HSV_TYPE)
    {
        glColor3f(col.hsv.h, col.hsv.s, col.hsv.v);
    }
}