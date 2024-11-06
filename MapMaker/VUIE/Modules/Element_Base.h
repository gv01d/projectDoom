#include "Module_Transform.h"

struct Element_Base // Define base
{
    Private_Info info;
    Position pos;
    Size size;

    // functions

    void (*eraseSelf)(struct Base *);
    void (*drawCall)(struct Base *);
    void (*drawFunc)();
    void (*functionBaseDefine)(struct Base *, void (*)());
};

void draw(Base *base)
{
    int *x;
    int *y;
    if (base->size.type == RECT_TYPE)
    {
        x = (int *)malloc(2 * sizeof(int));
        y = (int *)malloc(2 * sizeof(int));

        definePos(&base->pos, &x[0], &y[0]);

        x[1] = x[0] + base->size.rect.width;
        y[1] = y[0] + base->size.rect.height;
        glEnable(GL_SCISSOR_TEST);
        glScissor(x[0], y[0], x[1], y[1]);
    }
    else if (base->size.type == CIRC_TYPE)
    {
        x = (int *)malloc(base->size.circ.points * sizeof(int));
        y = (int *)malloc(base->size.circ.points * sizeof(int));

        int r = base->size.circ.radius;
        int theta = 360 / base->size.circ.points;
        for (int i = 0; i < base->size.circ.points; i++)
        {
            polarToCartesian(r, theta * i, &x[i], &y[i]);
        }
    }

    base->drawFunc();

    glDisable(GL_SCISSOR_TEST);
}
void functionBaseDefine(Base *base, void (*drawFunc)())
{
    base->drawFunc = drawFunc;
}
void eraseBase(Base *base)
{
    base->info.eraseSelf(&base->info);
    base->pos.eraseSelf(&base->pos);
    base->size.eraseSelf(&base->size);
    free(base);
}
Base *newBase()
{
    Base *base = (Base *)malloc(sizeof(Base));
    base->info = *newInfo();
    base->pos = *newPosition();
    base->size = *newSize();
    base->eraseSelf = eraseBase;
    base->drawCall = draw;
    return base;
}
