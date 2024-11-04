#include "Module_Transform.h"

typedef struct ContainerBox
{
    _Private_Transform transform;
    Color col;

    // functions
    void (*eraseSelf)(struct ContainerBox *);
} _Private_ContainerBox;
_Private_ContainerBox *newContainerBox() // new container box
{
    _Private_ContainerBox *box = (_Private_ContainerBox *)malloc(sizeof(_Private_ContainerBox));
    return box;
}
