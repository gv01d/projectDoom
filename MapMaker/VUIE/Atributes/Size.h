enum SizeType
{
    RECT_TYPE, // 0
    CIRC_TYPE, // 1
};

typedef struct Size // Define size
{
    union
    {
        struct // Rectangle ( Height, Width )
        {
            int height, width;
        } rect;
        struct // Circle ( Radius )
        {
            int radius;
            int points;
        } circ;
    };

    enum SizeType type;

} Size;
void setSize(struct Size *size, enum SizeType type, int height, int width) // Set size
{
    size->type = type;
    if (type == RECT_TYPE) // Rectangle (0)
    {
        size->rect.height = height;
        size->rect.width = width;
    }
    else if (type == CIRC_TYPE) // Circle (1)
    {
        size->circ.radius = height;
    }
}
void copySize(Size *size, Size *copy) // Copy size
{
    size->type = copy->type;
    if (copy->type == RECT_TYPE) // Rectangle (0)
    {
        size->rect.height = copy->rect.height;
        size->rect.width = copy->rect.width;
    }
    else if (copy->type == CIRC_TYPE) // Circle (1)
    {
        size->circ.radius = copy->circ.radius;
        size->circ.points = copy->circ.points;
    }
}

Size PRIVATE_DEFAULT_SIZE = {RECT_TYPE, 0, 0};
