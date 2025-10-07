#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>

//gcc -o teste.exe main.c -I include -L lib -lraylib -lgdi32 -lwinmm

const int screenWidth = 1200;
const int screenHeight = 1200;
const int squareSize = 10;
const int maxCols = screenHeight/squareSize;
const int maxRows = screenWidth/squareSize;
const int matrixSize = screenWidth/squareSize;
static Vector2 offset = { 0 };


bool Pause = false;

int** initMatrix(int rows, int cols)
{
    int** matrix = malloc(sizeof(int*)*rows);

    for(int i = 0; i < rows; ++i){
		matrix[i] = malloc(sizeof(int)*rows);
	}
    for(int i = 0; i < rows; ++i){
		for(int j = 0; j < cols; ++j){
			matrix[i][j] = 0;
		}

	}

	return matrix;
}

int checkNeighbours(int** matrix, int row, int col, int rows, int cols)
{
    int x[] = {-1,-1,-1,0,0,+1,+1,+1};
    int y[] = {-1,0,+1,-1,+1,-1,0,+1};
    int count = 0;

    for(int i = 0; i < 8; i++)
    {
        int newRow = row + x[i];
        int newCol = col + y[i];

        if(newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols)
        {
            if (matrix[newRow][newCol] == 1)
            {
                count++;
            }
        }
    }
    return count;
}

int stateUpdate(int Cell, int Neighbours)
{
    int dora;
    if(Cell == 1 && (Neighbours == 2 || Neighbours == 3))
    {
        dora = 1;
    }
    else if(Cell == 0 && Neighbours == 3)
    {
        dora = 1;
    }
    else{
        dora = 0;
    }

    return dora;

}

int** step(int** matrixA){
    int neigh;
    int state;
    int** auxMatrix = initMatrix(maxRows, maxCols);
	for(int i = 0; i < maxRows; ++i){
		for(int j = 0; j < maxCols; ++j){
                neigh = checkNeighbours(matrixA,i,j,maxRows,maxCols);
                state = stateUpdate(matrixA[i][j], neigh);
                auxMatrix[i][j] = state;
        }
	}
    return auxMatrix;
    }



int main()
{
    int** screenMatrix = initMatrix(maxRows, maxCols);
    int** backMatrix = initMatrix(maxRows, maxCols);
    int** blankMatrix = initMatrix(maxRows, maxCols);

    InitWindow(screenWidth, screenHeight, "Conway's Game of Life");
    SetTargetFPS(15);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        {
            ClearBackground(GRAY);
            for(int row = 0; row < maxRows; row++)
            {
                for(int col = 0; col < maxCols; col++)
                {
                    if(screenMatrix[row][col] == 1)
                    {
                        DrawRectangle(squareSize * col, squareSize * row, squareSize, squareSize, BLACK);
                    }
                    else
                    {
                        DrawRectangle(squareSize * col, squareSize * row, squareSize, squareSize, WHITE);
                    }
                }
            }

            for(int i = 0; i < matrixSize ; i++)
            {
                DrawLineV((Vector2){squareSize*i + offset.x/2, offset.y/2}, (Vector2){squareSize*i + offset.x/2, screenHeight - offset.y/2}, LIGHTGRAY);
            }
            for(int i = 0; i < matrixSize; i++)
            {
                DrawLineV((Vector2){offset.x/2, squareSize*i + offset.y/2}, (Vector2){screenWidth - offset.x/2, squareSize*i + offset.y/2}, LIGHTGRAY);
            }

            if(IsKeyPressed(KEY_SPACE))
            {
                Pause = !Pause;
                if(Pause == true){
                    printf("pausado\n");
                }
                else if(Pause == false){
                    printf("despausado\n");
                }
            }

            if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !Pause)
            {
                int mouseX = GetMouseX() / squareSize;
                int mouseY = GetMouseY() / squareSize;
                (screenMatrix[mouseY][mouseX] == 0) ? (screenMatrix[mouseY][mouseX] = 1) : (screenMatrix[mouseY][mouseX] = 0);
            }

            if(IsKeyDown(KEY_RIGHT) && !Pause)
            {
                backMatrix = step(screenMatrix);
                screenMatrix = backMatrix;
            }
            if(IsKeyPressed(KEY_N) && !Pause)
            {
                backMatrix = step(screenMatrix);
                screenMatrix = backMatrix;
            }
            if(IsKeyPressed(KEY_C) && !Pause)
            {
                screenMatrix = blankMatrix;
                backMatrix = blankMatrix;
            }
            if(IsKeyPressed(KEY_T) && !Pause)
            {
                int centerPoint = ((screenWidth/squareSize) /2);
                screenMatrix[centerPoint][centerPoint] = 1;
                screenMatrix[centerPoint + 1][centerPoint] = 1;
                screenMatrix[centerPoint - 1][centerPoint] = 1;
                screenMatrix[centerPoint - 1][centerPoint + 1] = 1;
                screenMatrix[centerPoint][centerPoint - 1] = 1;
            }

        EndDrawing();

        }
    }
    CloseWindow();
    return 0;
}
