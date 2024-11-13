#include <math.h>

#define MAX_ANGLES 360
#define PI 3.14159265

// Tabelas para armazenar senos e cossenos
float sin_table[MAX_ANGLES];
float cos_table[MAX_ANGLES];

// Função para inicializar as tabelas
void inicializar_tabelas()
{
    for (int i = 0; i < MAX_ANGLES; i++)
    {
        float rad = (i * PI) / 180.0; // Convertendo para radianos
        sin_table[i] = sin(rad);
        cos_table[i] = cos(rad);
    }
}

// Função para converter de coordenadas polares para cartesianas usando as tabelas
void polarToCartesian(int r, int theta, int *x, int *y)
{
    // Garantir que o ângulo esteja no intervalo de 0 a 359
    theta = theta % MAX_ANGLES;
    *x = (int)(r * cos_table[theta]);
    *y = (int)(r * sin_table[theta]);
}

enum PositionType
{
    CARTESIAN_TYPE, // 0
    POLAR_TYPE,     // 1
};

typedef struct Pos
{
    int x, y;

    int radius, theta;

    struct
    {
        int x, y;
    } Global;

    bool ReferToParent;
    struct Pos *parent;

    enum PositionType type;

} Position;

void Position_get(Position *pos, int *x, int *y) // Get position
{
    *x = pos->Global.x;
    *y = pos->Global.y;
}
void Position_set(Position *pos, enum PositionType type, int x, int y) // Set position
{
    pos->type = type;
    if (type == POLAR_TYPE)
    {
        pos->radius = x;
        pos->theta = y;

        polarToCartesian(x, y, &pos->x, &pos->y);
    }
    else
    {
        pos->x = x;
        pos->y = y;
    }

    if (pos->ReferToParent)
    {
        pos->Global.x = pos->x + pos->parent->Global.x;
        pos->Global.y = pos->y + pos->parent->Global.y;
    }
    else
    {
        pos->Global.x = pos->x;
        pos->Global.y = pos->y;
    }
}
void Position_setParent(Position *pos, Position *parent) // Set referencial position
{
    if (parent == NULL)
    {
        pos->ReferToParent = false;
        if (pos->parent != NULL)
        {
            pos->x += pos->parent->Global.x;
            pos->y += pos->parent->Global.y;
        }
        pos->Global.x = pos->x;
        pos->Global.y = pos->y;

        return;
    }
    pos->x = pos->Global.x - parent->Global.x;
    pos->y = pos->Global.y - parent->Global.y;

    pos->ReferToParent = true;
    pos->parent = parent;
}
void Position_copy(Position *pos, Position *copy) // Copy position
{
    pos->type = copy->type;
    pos->x = copy->x;
    pos->y = copy->y;

    pos->parent = copy->parent;
}
void Position_process(Position *pos)
{
    if (pos->ReferToParent)
    {
        pos->Global.x = pos->x + pos->parent->Global.x;
        pos->Global.y = pos->y + pos->parent->Global.y;
    }
    else
    {
        pos->Global.x = pos->x;
        pos->Global.y = pos->y;
    }
}

Position PRIVATE_DEFAULT_POSITION = {CARTESIAN_TYPE, 0, 0};
