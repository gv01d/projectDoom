#include <stdlib.h>
#include <stdio.h>

int GlobalNextID = 0;

typedef struct Info
{
    int ID;
    char *name;

} Private_Info;
void setInfo(Private_Info *info, int ID)
{
    if (info == NULL)
    {
        printf("<WARNING> : Info is null\n");
    }

    if (ID < 0)
    {
        // ID -1 = null
        ID = -1;
    }
    info->ID = ID;
}
void copyInfo(Private_Info *info, Private_Info *copy)
{
    info->ID = copy->ID;
}