#include "Position.h"
#include "Size.h"

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

void processTransform(_Private_Transform *transform)
{
    Size_process(&transform->size);
    Position_process(&transform->pos);
}

void TrasnformFree(_Private_Transform *transform)
{
    free(transform->pos.parent);
    free(transform->size.parentScale);
}
