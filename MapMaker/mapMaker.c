#include <math.h>
#include <stdio.h>
#include <GL/glut.h>
#include <stdbool.h>
#include "character.h"

#define Framerate 120
#define res 3                  // 0=160x120 1=360x240 4=640x480
#define SW 160 * res           // screen width
#define SH 90 * res            // screen height
#define SW2 (SW / 2)           // half of screen width
#define SH2 (SH / 2)           // half of screen height
#define pixelScale 12 / res    // OpenGL pixel scale
#define GLSW (SW * pixelScale) // OpenGL window width
#define GLSH (SH * pixelScale) // OpenGL window height

typedef struct
{
    int fr1, fr2; // frame 1 frame 2, to create constant frame rate
} time;
time T;

typedef struct
{
    int x, y;
    int cx, cy;
    bool click;
    bool Rclick;
} crossHair;
crossHair P;

typedef struct
{
    bool up, right, left, down;
    bool u;
} keyboard;
keyboard K;

void mouseBtn(int button, int state, int x, int y)
{
    P.x = (x / (pixelScale));
    P.y = SH - (y / (pixelScale));

    if (button == GLUT_LEFT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            P.click = true;
        }
        else
        {
            P.click = false;
        }
    }

    if (button == GLUT_RIGHT_BUTTON)
    {
        if (state == GLUT_DOWN)
        {
            P.Rclick = true;
        }
        else
        {
            P.Rclick = false;
        }
    }
}

void crosshair()
{
    int sX = 10;
    int sY = 10;
    for (int i = 0 - sX; i <= sX; i++)
    {
        for (int j = 0 - sY; j <= sY; j++)
        {
            pixel(P.x + i, P.y + j, 9, pixelScale);
        }
    }
}

typedef struct
{
    int posX, posY;
    int sW, sH;
    int col, Pcol, Bcol;
    bool hold, Shold;
    bool selected, Sslct;
    int PclkRadius;
    int OffsetX, OffsetY;
    bool active;
} UI;
UI U;

UI rC;

bool UPressed;
void UIfunc()
{
    int x1 = U.posX;
    int y1 = U.posY;
    int x2 = U.posX + U.sW;
    int y2 = U.posY + U.sH;

    if (U.hold)
    {
        if (!P.click)
        {
            U.hold = false;
        }
        else
        {
            if (U.selected)
            {
                U.posX = P.x - U.OffsetX;
                U.posY = P.y - U.OffsetY;
            }
            else if (U.Sslct)
            {
                U.sW = P.x - U.posX;
                U.sH = P.y - U.posY;
            }
        }
    }
    else if (dist(P.x, P.y, x2, y2) <= U.PclkRadius)
    {
        glutSetCursor(GLUT_CURSOR_INFO);
        if (P.click)
        {
            U.selected = false;
            U.Sslct = true;
            U.hold = true;
            U.sW = P.x - U.posX;
            U.sH = P.y - U.posY;
        }
    }
    else if (decBox(x1, y1, x2, y2, P.x, P.y))
    {
        glutSetCursor(GLUT_CURSOR_INFO);
        if (P.click)
        {
            U.OffsetX = P.x - U.posX;
            U.OffsetY = P.y - U.posY;

            glutSetCursor(GLUT_CURSOR_CROSSHAIR);
            U.Sslct = false;
            U.selected = true;
            U.hold = true;
            U.posX = P.x - U.OffsetX;
            U.posY = P.y - U.OffsetY;
        }
    }
    else
    {
        glutSetCursor(GLUT_CURSOR_INHERIT);
        if (P.click)
        {
            U.selected = false;
        }
    }

    if (K.u)
    {
        if (!UPressed)
        {
            printf("< %d; %d : %d; %d >", x1, y1, x2 - x1, y2 - y1);
            UPressed = true;
        }
    }
    else
    {
        UPressed = false;
    }

    quads(x1, y1, x2, y2, U.Bcol);

    line(x1, y1, x1, y2, U.col, 1);
    line(x1, y1, x2, y1, U.col, 1);
    line(x2, y2, x1, y2, U.col, 1);
    line(x2, y2, x2, y1, U.col, 1);

    pixel(x2, y2, 9, pixelScale + pixelScale / 2);
    pixel(x2, y2, 10, pixelScale);
}

// - // Map Structs \\ 

typedef struct
{
    int x1, y1;
    int x2, y2;
    int col;
} Wall;

typedef struct
{
    Wall *walls;
} Sector;

Sector *Map;
// - \\ Map Structs //

// - // Button \\ 

typedef struct button
{
    struct
    {
        int x;
        int y;
    } pos;
    struct
    {
        int x;
        int y;
    } size;

    bool clicked;
    void (*Draw)(struct button *, int, int);
} Button;

bool rCPressed;
Button CreateSector;
void drawButton(Button *self, int col, int colB)
{
    int x1 = self->pos.x;
    int y1 = self->pos.y;
    int x2 = self->size.x + self->pos.x;
    int y2 = self->size.y + self->pos.y;
    quads(x1, y1, x2, y2, colB);

    line(x1, y1, x1, y2, col, 1);
    line(x1, y1, x2, y1, col, 1);
    line(x2, y2, x1, y2, col, 1);
    line(x2, y2, x2, y1, col, 1);
}
void makeBtn(Button *btn, int x, int y, int sX, int sY)
{
    btn->Draw = drawButton;
    btn->pos.x = x;
    btn->pos.y = y;
    btn->size.x = sX;
    btn->size.y = sY;
}
void rightClick()
{
    if (P.Rclick && !rCPressed)
    {
        rC.active = true;
        rCPressed = true;
        rC.posX = P.x + rC.OffsetX;
        rC.posY = P.y + rC.OffsetY;
    }
    else if (!P.Rclick)
    {
        rCPressed = false;
    }
    int x1 = rC.posX;
    int y1 = rC.posY;
    int x2 = rC.posX + rC.sW;
    int y2 = rC.posY + rC.sH;

    if (P.click && !decBox(x1, y1, x2, y2, P.x, P.y))
    {
        rC.active = false;
    }

    if (rC.active)
    {
        quads(x1, y1, x2, y2, rC.Bcol);
        CreateSector.pos.x = x1 + 1;
        CreateSector.pos.y = y2 - 1 - CreateSector.size.y;
        CreateSector.Draw(&CreateSector, rC.col, 11);
        write("CREATE SECTOR", CreateSector.pos.x + 1, CreateSector.pos.y + 3, pixelScale, 1, rC.col, getFA());

        line(x1, y1, x1, y2, rC.col, 1);
        line(x1, y1, x2, y1, rC.col, 1);
        line(x2, y2, x1, y2, rC.col, 1);
        line(x2, y2, x2, y1, rC.col, 1);

        // int xc = character('B', x1 + 5, y1 + 5, pixelScale, 2, 1, getFA());
    }
}

void init()
{
    U.posX = 385;     //
    U.posY = 10;      //
    U.sW = 90;        //
    U.sH = 255;       //
    U.col = 9;        // white
    U.Pcol = 0;       // yellow
    U.Bcol = 10;      // gray blue ish
    U.hold = false;   //
    U.PclkRadius = 2; //

    rC.col = 9;        //
    rC.Pcol = 0;       //
    rC.Bcol = 10;      //
    rC.active = false; //
    rC.sW = 30;        //
    rC.sH = 30;        //
    makeBtn(&CreateSector, 0, 0, 28, 5);

    setPS(pixelScale);
    setSH(SH);
    setSW(SW);

    printf("Inicialized\n");
}

void display()
{

    int x, y;
    if (T.fr1 - T.fr2 >= (1000 / Framerate)) // only draw 20 frames/second
    {
        clearBackground();
        // draw3D();
        line(SW2 / 2, SH2 / 2, SW2, SH2, 9, 1);
        line(50, 200, SW2 / 2, SH2 / 2, 9, 1);

        pixel(SW2, SH2, 0, pixelScale);
        pixel(SW2 / 2, SH2 / 2, 0, pixelScale);
        pixel(50, 200, 0, pixelScale);

        rightClick();

        UIfunc();

        T.fr2 = T.fr1;
        glutSwapBuffers();
        glutReshapeWindow(GLSW, GLSH); // prevent window scaling
    }

    T.fr1 = glutGet(GLUT_ELAPSED_TIME); // 1000 Milliseconds per second
    glutPostRedisplay();
}

void keysDown(unsigned char key, int x, int y)
{
    if (key == 'w' == 1)
    {
        K.u = true;
    }
}

void keysUp(unsigned char key, int x, int y)
{
    if (key == 'w' == 1)
    {
        K.u = false;
    }
}

void mouse(int x, int y)
{
    P.x = (x / (pixelScale));
    P.y = SH - (y / (pixelScale));
    // printf("%d - %d\n", P.x, P.y);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(GLSW, GLSH);
    glutCreateWindow("");
    glPointSize(pixelScale);      // pixel size
    gluOrtho2D(0, GLSW, 0, GLSH); // origin bottom left
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keysDown);
    glutKeyboardUpFunc(keysUp);
    glutMotionFunc(mouse);
    glutPassiveMotionFunc(mouse);
    glutMouseFunc(mouseBtn);
    glutMainLoop();
    return 0;
}