#include "../window.h"

typedef struct Transform // Define transform
{
    Position pos;
    Size size;

} _Private_Transform;
void setTransform(_Private_Transform *transform, Position *pos, Size *size) // Set transform
{
    Position_copy(&transform->pos, pos);
    Size_copy(&transform->size, size);
}

void copyTransform(_Private_Transform *transform, _Private_Transform *copy) // Copy transform
{
    Position_copy(&transform->pos, &copy->pos);
    Size_copy(&transform->size, &copy->size);
}
