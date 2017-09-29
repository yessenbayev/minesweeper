// This is a text-based version of Minesweeper. Based on the mine.c assignment from the ECE 15 class at UCSD.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void initializeBoard(int sizerow, int sizecol, int board[][sizecol], int numMines){
srand(time(NULL));
int i = 0;
while (i<numMines) {
int row = rand()%sizerow;
int col = rand()%sizecol;
if (board[row][col]==-2)
continue;
else{
    board[row][col] = -2;
    i++;
 }
 }
}


bool validMove(int sizerow, int sizecol, int board[][sizecol], int row, int column){
    if((row<sizerow)&&(row>=0)&&(column<sizecol)&&(column>=0))
        return true;
    else
        return false;
}


int numMinesNear(int sizerow, int sizecol, int board[][sizecol], int row, int column){
    int count = 0;
    int checkrow = row - 1;
    int checkcol = column - 1;
    while(checkrow<=(row+1) && checkrow>=(row-1) && checkrow < sizerow){
      while(checkcol<=(column+1) && checkcol>=(column-1) && checkcol < sizecol){
        if(checkrow < 0 || checkcol < 0){
            checkcol++;
            continue;
        }
        else if(board[checkrow][checkcol]==-2){
		  count++;
		}
        checkcol++;
      }
        checkrow += 1;
        checkcol = column - 1;
    }
     return count;
}


void printBoard(int sizerow, int sizecol, int board[][sizecol], bool showMines){
  int i = 0, j = 0;
  printf(" ");
    for(i=0;i<sizecol;i++){
        printf( " %d ", i);
    }
    printf("\n");
    for(i=0;i<sizecol;i++){
        printf(" - ");
    }
    printf("\n");
    for(i=0;i<sizerow;i++){
        printf("%d |", i);
        for(j=0;j<sizecol;j++){
            if(((board[i][j]==-2)&&(showMines==false))||(board[i][j]==-1))
                printf("   |");
            else if((board[i][j]==-2)&&(showMines==true))
                printf(" * |");
            else
                printf(" %d |",board[i][j]);
        }
            printf("\n ");
	    for(j=0;j<sizecol;j++){
        printf(" - ");
	    }
        printf("\n");
    }
    return;
}

int main(){
    int i, j, sizerow, sizecol, row, column, numMines, moves = 0;
    bool  valid, winning=true, showMines=false;
    printf("Board row and column size: ");
    scanf(" %d %d", &sizerow, &sizecol);
    printf("Number of mines: ");
    scanf(" %d", &numMines);
    int board[sizerow][sizecol];
    for(i=0;i<sizerow;i++){
        for(j=0;j<sizecol;j++){
            board[i][j] = -1;
        }
    }
    initializeBoard(sizerow, sizecol, board, numMines);
    if(numMines>= (sizerow*sizecol)){
        showMines=true;
        printBoard(sizerow, sizecol, board, showMines);
        printf("You won!\n");
        return 0;
    }
    printBoard(sizerow, sizecol, board, showMines);
    while(moves<((sizecol*sizerow)-numMines)){
        printf("Row and column [0 to %d] [0 to %d]: ", sizerow-1, sizecol-1);
        scanf(" %d %d",&row,&column);
        valid = validMove(sizerow, sizecol, board, row, column);
        if(board[row][column]>=0){
	  printf("Already cleared!\n");
                continue;
        }
        if(!valid){
            printf("Out of bounds!\n");
            continue;
        }
        if(board[row][column]==-1){
            board[row][column] = numMinesNear(sizerow, sizecol, board, row, column);
        }
        if(board[row][column]==-2){
            winning = false;
            showMines = true;
            printBoard(sizerow,sizecol,board,showMines);
            break;
        }
        if(moves==((sizecol*sizerow)-numMines-1))
            showMines = true;
        printBoard(sizerow,sizecol,board,showMines);
        moves++;
    }
    if(winning)
        printf("You won!\n");
    else
        printf("You lost!\n");
    return 0;
}
