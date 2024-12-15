enum SizeType
{
    RECT_TYPE, // 0
    CIRC_TYPE, // 1
};

typedef struct Size // Define size
{
    int height, width;

    int radius, points;

    int scale;

    int globalScale;

    bool afectedByParent;
    int *parentScale;

    enum SizeType type;

} Size;

void Size_setScale(Size *size, int scale) // Set scale
{
    size->scale = scale;
    if (size->afectedByParent && size->parentScale != NULL)
    {
        size->globalScale = *size->parentScale * scale;
    }
    else
    {
        size->globalScale = scale;
    }
}

void Size_setParent(Size *size, int *parentScale)
{
    size->afectedByParent = true;
    size->parentScale = parentScale;
}

void Size_set(struct Size *size, enum SizeType type, int a, int b, int scale) // Set size
{
    size->type = type;
    size->scale = scale;
    if (type == RECT_TYPE) // Rectangle (0)
    {
        size->height = a;
        size->width = b;
    }
    else if (type == CIRC_TYPE) // Circle (1)
    {
        size->radius = a;
        size->points = b;
        size->height = a * 2;
        size->width = a * 2;
    }
}
void Size_copy(struct Size *size, struct Size *copy) // Copy size
{
    size->type = copy->type;
    size->scale = copy->scale;
    size->globalScale = copy->globalScale;
    size->afectedByParent = copy->afectedByParent;
    size->parentScale = copy->parentScale;
    size->height = copy->height;
    size->width = copy->width;
    size->radius = copy->radius;
    size->points = copy->points;
}

void Size_process(struct Size *size)
{
    if (size->afectedByParent && size->parentScale != NULL)
    {
        size->globalScale = *size->parentScale * size->scale;
    }
    else
    {
        size->globalScale = size->scale;
    }
};

Size PRIVATE_DEFAULT_SIZE = {RECT_TYPE, 0, 0};
