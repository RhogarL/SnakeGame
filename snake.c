#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>

typedef struct snake
{
    int x_pos;
    int y_pos;
    struct snake* next;
} snake;

int randomBetween(int min, int max);
void windowManagement(int wind_x, int wind_y, int wind_h, int wind_w);
void georginasCookies(snake** segmentPtr, int* x_food, int* y_food, int* snakesLength, int x_buffer, int y_buffer);
void addSegment(snake** segmentPtr, int x_pos, int y_pos);
void controls(snake* segment);
void drawSnake(snake* segmentPtr);
void updateSnake(snake* segment);

int main() {

    //Starts random seed
    srand(time(NULL));

    //Manages console position and size
    windowManagement(710, 290, 600, 600);

    //Hides cursor
    printf("\033[?25l");

    //Creates a snake
    snake* segmentPtr = NULL;
    snake* segment = malloc(sizeof(snake));
    if (segment == NULL)
    {
        printf("Theres no space in memory to run the game");
        return 1;
    }

    //Declares the head of the snake
    segment->x_pos = 1;
    segment->y_pos = 1;
    segment->next = NULL;
    //We get a pointer to the head for later use
    segmentPtr = segment;

    segment = malloc(sizeof(snake));
    if (segment == NULL)
    {
        printf("Theres no space in memory to run the game");
        return 1;
    }
    segment->x_pos = 1;
    segment->y_pos = 1;
    segment->next = segmentPtr;
    segmentPtr = segment;


    //A position buffer that will go behind the snake changing its trail back into air
    int x_buffer = 0;
    int y_buffer = 0;

    // Random food position
    int x_food = 5;
    int y_food = 5;
    printf("\x1b[%d;%dHX", y_food, x_food);
    int points = 0;
    //Program is running nonstop unless the user hits the esc key
    while (1)
    {

        printf("\x1b[%d;%d ", segmentPtr->y_pos, segmentPtr->x_pos);

        x_buffer = segmentPtr->x_pos;
        y_buffer = segmentPtr->y_pos;

        updateSnake(segment);
        //Game controls
        controls(segment);



        georginasCookies(&segmentPtr, &y_food, &x_food, &points, x_buffer, y_buffer);

        //Draws the snake head
        drawSnake(segmentPtr);
        //printf("\x1b[%d;%dHO:%p", 10, 10,(void*)&segmentPtr);
        printf("\x1b[%d;%dHO Address: %p Points: %p",10,10, (void*)&segmentPtr, (void*)segmentPtr);
        printf("\x1b[%d;%dHO Xpos: %p Ypos: %p", 15, 15, segmentPtr->x_pos, segmentPtr->y_pos);


        // Controls game ticks
        Sleep(20);
    }
    return 0;
}


void georginasCookies(snake** segmentPtr, int* x_food, int* y_food, int* points, int x_buffer, int y_buffer)
{
    if ((*segmentPtr)->x_pos == *x_food && (*segmentPtr)->y_pos == *y_food)
    {
        (*points)++;
        //addSegment(segmentPtr, x_buffer, y_buffer);
        *x_food = randomBetween(3, 47);
        *y_food = randomBetween(3, 27);
        printf("\x1b[%d;%dHX", *y_food, *x_food);
    }
}

void addSegment(snake** segmentPtr, int x_buffer, int y_buffer)
{
    snake* newSegment = malloc(sizeof(snake));
    if (newSegment == NULL)
    {
        printf("Theres no space in memory to run the game");
        exit(1);
    }
    newSegment->x_pos = x_buffer;
    newSegment->y_pos = y_buffer;
    newSegment->next = *segmentPtr;
    *segmentPtr = newSegment;
    //printf("\x1b[%d;%dHO:%p", (*segmentPtr)->y_pos, (*segmentPtr)->x_pos, (void*)segmentPtr);

}

void updateSnake(snake* segment)
{
    if (segment == NULL)
    {
        return;
    }

    // Recorremos desde la cola hacia la cabeza
    snake* current = segment;
    while (current->next != NULL)
    {
        current->next->x_pos = current->x_pos;
        current->next->y_pos = current->y_pos;
        current = current->next;
        
    }
}

//Draws the snake recursively 
void drawSnake(snake* segmentPtr)
{
    if (segmentPtr == NULL)
    {
        // Base case
        return;
    }

    // Draws this segment
    printf("\x1b[%d;%dHO", segmentPtr->y_pos, segmentPtr->x_pos);
    //printf("\x1b[%d;%dHO:%p", 10, 10,(void*)&segmentPtr);
    //Sleep(100);
    // Calls the function recursively on itself to draw the snake
    drawSnake(segmentPtr->next);
}

void windowManagement(int wind_x, int wind_y, int wind_h, int wind_w) {

    //Set console size 
    HWND consoleWindow = GetConsoleWindow();

    //Console  window x position , y position, height and width
    MoveWindow(consoleWindow, wind_x, wind_y, wind_h, wind_w, TRUE);

    //Set the buffer size with the same rate as the window
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = { wind_h, wind_w };
    SetConsoleScreenBufferSize(hConsole, coord);
}

void controls(snake* segment)
{
    //Arrow keys are observed and whenever one is pressed it changes x and y coordinates of the snakes head accordingly
    if ((GetAsyncKeyState(VK_LEFT) & 0x8000))
    {
        segment->x_pos--;
        if (segment->x_pos < 0)
        {
            segment->x_pos = 0;
        }
    }
    if ((GetAsyncKeyState(VK_RIGHT) & 0x8000))
    {
        segment->x_pos++;
    }
    if ((GetAsyncKeyState(VK_UP) & 0x8000))
    {
        segment->y_pos--;
        if (segment->y_pos < 0)
        {
            segment->y_pos = 0;
        }
    }
    if ((GetAsyncKeyState(VK_DOWN) & 0x8000))
    {
        segment->y_pos++;
    }
    // Press esc to exit the program
    if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
    {
        printf("Esc pressed, exiting program...");
        exit(0);
    }
}

int randomBetween(int min, int max)
{
    int value = rand() % ((max + 1) - min) + min;
    return value;
}

void freeMemory() // IMPORTANTE NO OLVIDAR LIBERAR LA MEMORIA
{

}

