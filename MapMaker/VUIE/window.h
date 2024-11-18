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

void startWindow(char *name)
{
    Draw_SetPixelScale(&window.PixelScale);
    window.PixelScale = 10;
    window.rawSize.width = 1600;
    window.rawSize.height = 900;
    window.size.width = window.rawSize.width / window.PixelScale;
    window.size.height = window.rawSize.height / window.PixelScale;

    Position_set(&window.pos, CARTESIAN_TYPE, 0, 0);

    if (window.name != NULL)
    {
        free(window.name);
    }
    window.name = (char *)malloc((strlen(name) + 1) * sizeof(char));
    strncpy(window.name, name, strlen(name) + 1);
}