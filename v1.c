#include <stdio.h>

#define MAX_SIZE 50
#define MAX_STATE 3000

// int TraversedI1J1I2J2[MAX_STATE][4];
// int NumState=0;

void initialBoard( int board[MAX_SIZE][MAX_SIZE], int size )
{
  int i,j;
  for( i=0; i<size;i ++ )
  {
    for( j=0; j<size; j++ )
    {
      board[i][j] = 0;
    }
  }
}

void displayBoard( int board[MAX_SIZE][MAX_SIZE], int size,
                  int i1, int j1, int i2, int j2 )
{
  int i,j;

  initialBoard( board, size );

  for( i=0; i<size; i++ )
  {
    for( j=0; j<size; j++ )
    {
      if( i == i1 && j == j1 )
        board[i][j]++;

      if( i == i2 && j == j2 )
        board[i][j]++;
    }
  }

  for( i=0; i<size; i++ )
  {
    for( j=0; j<size; j++ )
    {
        printf("%d ", board[i][j] );
    }
    printf("\n");
  }

  printf("-------------------\n");
}

int isTraversed( int tracebackStates[MAX_STATE][4], int numState,
                  int i1, int j1, int i2, int j2 )
{
  int i;
  for( i=0; i<numState; i++ )
  {
    if(tracebackStates[i][0] == i1 &&
       tracebackStates[i][1] == j1 &&
       tracebackStates[i][2] == i2 &&
       tracebackStates[i][3] == j2  )
       return 1;
  }

  return 0;
}

void traverse( int board[MAX_SIZE][MAX_SIZE],
                int size, int i1, int j1, int i2, int j2,
                int *numSolution,
                int tracebackStates[MAX_STATE][4],
                int numState, 
				int *times )
{
  if( i1<0 || j1<0 || i1>=size || j1>=size ||
      i2<0 || j2<0 || i2>=size || j2>=size )
  {
    //printf("Can't move - End\n");
    return;
  }

  if( isTraversed( tracebackStates, numState, i1, j1, i2, j2 ) )
    return;

  //   SUCCESS !!
  if( i1 == i2 && j1 == j2 && i1 == size-1 && j2 == size -1 )
  {
    int i;
    for( i=0; i<numState; i++ )
    {
      displayBoard( board, size,
                      tracebackStates[i][0],
                      tracebackStates[i][1],
                      tracebackStates[i][2],
                      tracebackStates[i][3] );
    }

    (*numSolution)++;
    displayBoard( board, size, i1, j1, i2, j2 );
    printf("######### Success %d times !!\n", *numSolution );
    printf("######### move %d times !!\n", numState );
    
    if((*times)>numState){
    	(*times)=(numState);
	}
	
    return;
  }

  //printf("It's in %d,%d - %d,%d\n", i1,j1, i2, j2 );

  //  Remember this position
  tracebackStates[numState][0] = i1;
  tracebackStates[numState][1] = j1;
  tracebackStates[numState][2] = i2;
  tracebackStates[numState][3] = j2;
  numState++;

  //displayBoard( board, size, i1, j1, i2, j2 );

  //    it's standing
  if( i1 == i2 && j1 == j2 )
  {
    //printf("It's standing\n");

    //  move up
    //printf("Moving up !\n");
    traverse( board, size, i1-2, j1, i2-1, j2, numSolution, tracebackStates, numState ,times);

    //  move down
    //printf("Moving down !\n");
    traverse( board, size, i1+1, j1, i2+2, j2, numSolution, tracebackStates, numState ,times);

    //  move left
    //printf("Moving left !\n");
    traverse( board, size, i1, j1-2, i2, j2-1, numSolution, tracebackStates, numState ,times);

    //  move right
    //printf("Moving right !\n");
    traverse( board, size, i1, j1+1, i2, j2+2, numSolution, tracebackStates, numState ,times);
  }

  //    it's flatting in X-Axis
  else if( i1 == i2 && j1+1 == j2 )
  {
    //printf("It's flatting in X-Axis\n");

    //  move up
    //printf("Moving up !\n");
    traverse( board, size, i1-1, j1, i2-1, j2, numSolution, tracebackStates, numState ,times);

    //  move down
    //printf("Moving down !\n");
    traverse( board, size, i1+1, j1, i2+1, j2, numSolution, tracebackStates, numState ,times);

    //  move left
    //printf("Moving left !\n");
    traverse( board, size, i1, j1-1, i2, j2-2, numSolution, tracebackStates, numState ,times);

    //  move right
    //printf("Moving right !\n");
    traverse( board, size, i1, j1+2, i2, j2+1, numSolution, tracebackStates, numState ,times);
  }

  //    it's flatting in Y-Axis
  else if( i1+1 == i2 && j1 == j2 )
  {
    //printf("It's flatting in Y-Axis\n");

    //  move up
    //printf("Moving up !\n");
    traverse( board, size, i1-1, j1, i2-2, j2, numSolution, tracebackStates, numState ,times);

    //  move down
    //printf("Moving down !\n");
    traverse( board, size, i1+2, j1, i2+1, j2, numSolution, tracebackStates, numState ,times);

    //  move left
    //printf("Moving left !\n");
    traverse( board, size, i1, j1-1, i2, j2-1, numSolution, tracebackStates, numState ,times);

    //  move right
    //printf("Moving right !\n");
    traverse( board, size, i1, j1+1, i2, j2+1, numSolution, tracebackStates, numState ,times);
  }
  else
  {
    printf("WRONG STATE !! Please Check %d,%d - %d,%d\n", i1, j1, i2, j2 );
  }
}

int main()
{
  int size;
  int board[MAX_SIZE][MAX_SIZE];
  int numSolution = 0;
  int tracebackStates[MAX_STATE][4];
  int numState=0;
  int times=500;

  // get board's size
  printf("Board Size (NxN): ");
  scanf("%d", &size );

  //  initial board
  initialBoard( board, size );

  //  traverse
  traverse( board, size, 0, 0, 0, 0, &numSolution, tracebackStates, numState ,&times);

  printf("==================================\n");
  printf("So, num solutions is %d\n", numSolution );
  printf("So, less move is %d\n", times );
  printf("==================================\n");

  return 0;
}
