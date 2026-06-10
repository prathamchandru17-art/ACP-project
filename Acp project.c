#include <stdio.h>
#include <math.h>

#define ROWS 20
#define COLS 60
#define MAX_SHAPES 50

char canvas[ROWS][COLS];

typedef struct
{
    int type;
    int row;
    int col;
    int radius;
} Shape;

Shape shapes[MAX_SHAPES];
int shapeCount = 0;

void initializeCanvas()
{
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            canvas[i][j] = '_';
        }
    }
}

void displayCanvas()
{
    printf("\n");

    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            printf("%c", canvas[i][j]);
        }
        printf("\n");
    }
}

void drawRectangle(int r, int c)
{
    for(int i = r; i < r + 4 && i < ROWS; i++)
    {
        for(int j = c; j < c + 8 && j < COLS; j++)
        {
            if(i == r || i == r + 3 || j == c || j == c + 7)
            {
                canvas[i][j] = '*';
            }
        }
    }
}

void drawLine(int r, int c)
{
    for(int j = c; j < c + 10 && j < COLS; j++)
    {
        canvas[r][j] = '*';
    }
}

void drawTriangle(int r, int c)
{
    if(r >= 0 && r < ROWS && c >= 0 && c < COLS)
        canvas[r][c] = '*';

    if(r + 1 < ROWS)
    {
        if(c - 1 >= 0)
            canvas[r + 1][c - 1] = '*';

        if(c + 1 < COLS)
            canvas[r + 1][c + 1] = '*';
    }

    if(r + 2 < ROWS)
    {
        for(int j = c - 2; j <= c + 2; j++)
        {
            if(j >= 0 && j < COLS)
            {
                canvas[r + 2][j] = '*';
            }
        }
    }
}

void drawCircle(int centerRow, int centerCol, int radius)
{
    for(int angle = 0; angle < 360; angle++)
    {
        double rad = angle * 3.14159265 / 180.0;

        int r = centerRow + (int)(radius * sin(rad));
        int c = centerCol + (int)(radius * cos(rad));

        if(r >= 0 && r < ROWS && c >= 0 && c < COLS)
        {
            canvas[r][c] = '*';
        }
    }
}

void redrawCanvas()
{
    initializeCanvas();

    for(int i = 0; i < shapeCount; i++)
    {
        switch(shapes[i].type)
        {
            case 1:
                drawRectangle(shapes[i].row, shapes[i].col);
                break;

            case 2:
                drawLine(shapes[i].row, shapes[i].col);
                break;

            case 3:
                drawTriangle(shapes[i].row, shapes[i].col);
                break;

            case 4:
                drawCircle(
                    shapes[i].row,
                    shapes[i].col,
                    shapes[i].radius
                );
                break;
        }
    }
}

void addShape()
{
    if(shapeCount >= MAX_SHAPES)
    {
        printf("Shape storage full!\n");
        return;
    }

    Shape s;

    printf("\n1. Rectangle\n");
    printf("2. Line\n");
    printf("3. Triangle\n");
    printf("4. Circle\n");
    printf("Choose Shape: ");
    scanf("%d", &s.type);

    printf("Enter Row (0-%d): ", ROWS - 1);
    scanf("%d", &s.row);

    printf("Enter Column (0-%d): ", COLS - 1);
    scanf("%d", &s.col);

    if(s.type == 4)
    {
        printf("Enter Radius: ");
        scanf("%d", &s.radius);
    }
    else
    {
        s.radius = 0;
    }

    shapes[shapeCount++] = s;

    redrawCanvas();
}

void deleteShape()
{
    int id;

    if(shapeCount == 0)
    {
        printf("No shapes available.\n");
        return;
    }

    printf("Enter Shape ID to Delete (0-%d): ", shapeCount - 1);
    scanf("%d", &id);

    if(id < 0 || id >= shapeCount)
    {
        printf("Invalid ID\n");
        return;
    }

    for(int i = id; i < shapeCount - 1; i++)
    {
        shapes[i] = shapes[i + 1];
    }

    shapeCount--;

    redrawCanvas();
}

void modifyShape()
{
    int id;

    if(shapeCount == 0)
    {
        printf("No shapes available.\n");
        return;
    }

    printf("Enter Shape ID to Modify (0-%d): ", shapeCount - 1);
    scanf("%d", &id);

    if(id < 0 || id >= shapeCount)
    {
        printf("Invalid ID\n");
        return;
    }

    printf("New Row: ");
    scanf("%d", &shapes[id].row);

    printf("New Column: ");
    scanf("%d", &shapes[id].col);

    if(shapes[id].type == 4)
    {
        printf("New Radius: ");
        scanf("%d", &shapes[id].radius);
    }

    redrawCanvas();
}

void listShapes()
{
    if(shapeCount == 0)
    {
        printf("No Shapes Added.\n");
        return;
    }

    printf("\nShape List:\n");

    for(int i = 0; i < shapeCount; i++)
    {
        printf("ID %d -> ", i);

        switch(shapes[i].type)
        {
            case 1:
                printf("Rectangle");
                break;

            case 2:
                printf("Line");
                break;

            case 3:
                printf("Triangle");
                break;

            case 4:
                printf("Circle (Radius = %d)", shapes[i].radius);
                break;
        }

        printf(" at (%d,%d)\n",
               shapes[i].row,
               shapes[i].col);
    }
}

int main()
{
    int choice;

    initializeCanvas();

    while(1)
    {
        printf("\n========== 2D GRAPHICS EDITOR ==========\n");
        printf("1. Add Shape\n");
        printf("2. Delete Shape\n");
        printf("3. Modify Shape\n");
        printf("4. Display Canvas\n");
        printf("5. List Shapes\n");
        printf("6. Exit\n");
        printf("Enter Choice: ");

        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                addShape();
                break;

            case 2:
                deleteShape();
                break;

            case 3:
                modifyShape();
                break;

            case 4:
                displayCanvas();
                break;

            case 5:
                listShapes();
                break;

            case 6:
                printf("Exiting Graphics Editor...\n");
                return 0;

            default:
                printf("Invalid Choice!\n");
        }
    }

    return 0;
}