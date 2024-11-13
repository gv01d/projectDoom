#include "../window.h"

typedef struct Transform // Define transform
{
    Position pos;
    Size size;

} _Private_Transform;
void setTransform(_Private_Transform *transform, Position *pos, Size *size) // Set transform
{
    Position_copy(&transform->pos, pos);
    copySize(&transform->size, size);
}

void copyTransform(_Private_Transform *transform, _Private_Transform *copy) // Copy transform
{
    Position_copy(&transform->pos, &copy->pos);
    copySize(&transform->size, &copy->size);
}
