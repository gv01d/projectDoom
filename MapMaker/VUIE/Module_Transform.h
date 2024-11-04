#include "../draw/Draw.h"

typedef struct Transform // Define transform
{
    Position pos;
    Size size;

} _Private_Transform;
void setTransform(_Private_Transform *transform, Position pos, Size size) // Set transform
{
    transform->pos = pos;
    transform->size = size;
}