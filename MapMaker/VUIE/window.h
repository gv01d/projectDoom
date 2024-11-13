#include "Atributes/Position.h"
#include "Atributes/Size.h"

struct
{
    int PixelScale;
    struct
    {
        int width;
        int height;
    } rawSize;
    struct
    {
        int width;
        int height;
    } size;

    Position pos;

    char *name;
} window;