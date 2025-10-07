# Noise-And-Conways
A noise generator and Conways game.


## Ideia
This is a project that i already have mede, sort of.
I just wanted to do it with better visuals, so i used the Raylib library to help me with that.
Making the game i became curious with noise and how it can generate terrain, 
and there i begin to make a new program very simple to play with it.



## Conway's Game Of Life: How it works
Basic a matrix with cells that are live or dead and change the states(dead/live) based on how many neighbours they have
The rule used on the game is:
If the cell is alive and have 2 or 3 neighbours it continues alive
if the cell is dead and heve exactly 3 neighbours it becomes alive
everything else the cell die

### How i made it
The idea is simple, a matrix, and a function to update
The matrix part is easy, the funtions not that much
first i made the neighbours check funtion that recives the matrix, row and collum of the cell we want to check
than it iterates through and returns the neighbours count.
```
int checkNeighbours(int** matrix, int row, int col, int rows, int cols)
int x[] = {-1,-1,-1,0,0,+1,+1,+1};
    int y[] = {-1,0,+1,-1,+1,-1,0,+1};
    int count = 0;
    for(int i = 0; i < 8; i++){
        int newRow = row + x[i];
        int newCol = col + y[i];
        if(newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols){
            if (matrix[newRow][newCol] == 1){
                count++;
            }
        }
    }
    return count;
```

Then i need to make an update Function that changes the state of the cell based on the neighbours and rules we stablish for the game
```
int stateUpdate(int Cell, int Neighbours){
    int state;
    if(Cell == 1 && (Neighbours == 2 || Neighbours == 3)){
        state = 1;
    }
    else if(Cell == 0 && Neighbours == 3){
        state = 1;
    }
    else{
        state = 0;
    }
    return state;
}
```
And finaly the last funtion to combine all and make it works, it iterate through every martix values and update the cell
i need to use a copy(auxMatrix) of the matrix to check, because if i change the cell and go to the next of it check will change the value that is supposed to be
```
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
```
### Controls and how to play
To play you just execute the Conway.exe, it will open a window with squares all white, if you left click it turns the square black and the cell become alive
nothing realy happens, that because it needs you to hold the right arrow key to works and iterate the rules, if you probably just click in one cell it wil die
Try press T that make apears some test cells that make some patterns when you hold the right arrow key 

[gifs here]




 
## Noise generator: How it works





