#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>



const int screenWidth = 1200;
const int screenHeight = 1200;
const int margin = 100;
const int squareSize = 5;
const int maxCols = (screenHeight-margin)/squareSize;
const int maxRows = (screenWidth-margin)/squareSize;
const int matrixSize = screenWidth/squareSize;
static Vector2 offset = { 0 };

int** initMatrix(int rows, int cols)
{
    int** matrix = malloc(sizeof(int*)*rows);
    for(int i = 0; i < rows; ++i){
		matrix[i] = malloc(sizeof(int)*cols);
	}
    for(int i = 0; i < rows; ++i){
		for(int j = 0; j < cols; ++j){
			matrix[i][j] = 0;
		}
	}
	return matrix;
}

int** giveNoise(int row, int col, int density)
{
	int** matrix = initMatrix(row, col);
	for(int i = 0; i < row; ++i){
		for(int j = 0; j < col; ++j){
		int num = rand()%100;
		if(num < density)
			matrix[i][j] = 1;
		else
			matrix[i][j] = 0;
		}
	}
	return matrix;
}

int** step(int** matrix, int row, int col)
{
	int** newMatrix = initMatrix(row, col);
	for(int i = 0; i < row; ++i){
		for(int j = 0; j < col; ++j){
			int count = 0;
			if(i > 0 && matrix[i-1][j] == 1) count++;
			if(i < row-1 && matrix[i+1][j] == 1) count++;
			if(j > 0 && matrix[i][j-1] == 1) count++;
			if(j < col-1 && matrix[i][j+1] == 1) count++;
			if(i > 0 && j > 0 && matrix[i-1][j-1] == 1) count++;
			if(i < row-1 && j < col-1 && matrix[i+1][j+1] == 1) count++;
			if(i > 0 && j < col-1 && matrix[i-1][j+1] == 1) count++;
			if(i < row-1 && j > 0 && matrix[i+1][j-1] == 1) count++;

			if(matrix[i][j] == 1 && (count == 2 || count == 3))
			{
			    newMatrix[i][j] = 1;
			}
			else if (matrix[i][j] == 0 && (count == 3)) {
			    newMatrix[i][j] = 1;
			}
			else newMatrix[i][j] = 0;
		}
	}
	return newMatrix;
}

int main()
{
    int density = 50;
    int** screen = giveNoise(maxRows, maxCols, density);
    InitWindow(screenWidth, screenHeight, "quadriculado");
    SetTargetFPS(10);

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(BLACK);
            DrawText(TextFormat("Density: %d%%", density), 10, 10, 40, RED);
            for(int row = 0; row < maxRows; ++row)
            {
                for(int col = 0; col < maxCols; ++col)
                {
                    if (screen[row][col] == 1)
                    {
                     DrawRectangle(row*squareSize + margin/2, col*squareSize + margin/2, squareSize, squareSize, LIGHTGRAY);
                    }
                    if (screen[row][col] == 0) {
                        DrawRectangle(row*squareSize + margin/2, col*squareSize + margin/2, squareSize, squareSize, DARKGRAY);
                    }
                }
            }
        EndDrawing();

        if(IsKeyPressed(KEY_SPACE)){
            screen = giveNoise(maxRows, maxCols, density);
        }
        if (IsKeyPressed(KEY_UP)){
            if (density < 100) {
                density += 10;
            }
        }
        if(IsKeyPressed(KEY_DOWN)){
            if (density > 0) {
                density -= 10;
            }
        }
        if(IsKeyDown(KEY_RIGHT)){
            screen = step(screen, maxRows, maxCols);
        }
    }

    CloseWindow();

    return 0;
}
