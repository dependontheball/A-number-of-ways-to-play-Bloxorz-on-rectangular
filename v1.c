#include <stdio.h>

#define MAX_SIZEx 50
#define MAX_SIZEy 50
#define MAX_STATE 3000

// int TraversedI1J1I2J2[MAX_STATE][4];
// int NumState=0;

void initialBoard( int board[MAX_SIZEx][MAX_SIZEy], int sizex, int sizey)
{
  int i,j;
  for( i=0; i<sizex;i++ )
  {
    for( j=0; j<sizey; j++ )
    {
      board[i][j] = 0;
    }
  }
}

void displayBoard( int board[MAX_SIZEx][MAX_SIZEy], int sizex,int sizey,
                  int i1, int j1, int i2, int j2, int i3, int j3, int i4, int j4,int i5, int j5, int i6, int j6, int fuc[4])
{
  int i,j;

  initialBoard( board, sizex, sizey );

  for( i=0; i<sizex; i++ )
  {
    for( j=0; j<sizey; j++ )
    {
    	if(1<fuc[3]){
    		if( i == i1 && j == j1 )
       		 board[i][j]++;
      		if( i == i2 && j == j2 )
       		 board[i][j]++;
		}
		if(2<fuc[3]){
    		if( i == i3 && j == j3 )
       		 board[i][j]++;
		}
      	if(3<fuc[3]){
    		if( i == i4 && j == j4 )
       		 board[i][j]++;
		}
		if(4<fuc[3]){
    		if( i == i5 && j == j5 )
       		 board[i][j]++;
		}
		if(5<fuc[3]){
    		if( i == i6 && j == j6 )
       		 board[i][j]++;
		}
    }
  }

  for( i=0; i<sizex; i++ )
  {
    for( j=0; j<sizey; j++ )
    {
        printf("%d ", board[i][j] );
    }
    printf("\n");
  }

  printf("-------------------\n");
}

int isTraversed( int tracebackStates[MAX_STATE][12], int numState,
                  int i1, int j1, int i2, int j2, int i3, int j3, int i4, int j4,int i5, int j5, int i6, int j6, int fuc[4] )
{
  int i;
  for( i=0; i<numState; i++ )
  {
    if(tracebackStates[i][0] == i1 &&
       tracebackStates[i][1] == j1 &&
       tracebackStates[i][2] == i2 &&
       tracebackStates[i][3] == j2 &&
	   tracebackStates[i][4] == i3 &&
       tracebackStates[i][5] == j3 &&
       tracebackStates[i][6] == i4 &&
       tracebackStates[i][7] == j4 &&
	   tracebackStates[i][8] == i5 &&
       tracebackStates[i][9] == j5 &&
       tracebackStates[i][10] == i6 &&
       tracebackStates[i][11] == j6  )
       return 1;
  }

  return 0;
}

void traverse(  int board[MAX_SIZEx][MAX_SIZEy],
                int sizex, int sizey, int i1, int j1, int i2, int j2, int i3, int j3, int i4, int j4,int i5, int j5, int i6, int j6,
                int *numSolution,
                int tracebackStates[MAX_STATE][12],
                int numState, 
				int *times,
				int *lesstimes,
				int pnt, 
				int fuc[4],
				int x,
				int y,
				int z )
{
	int i;
	
  if( i1<0 || j1<0 || i1>=sizex || j1>=sizey ||
      i2<0 || j2<0 || i2>=sizex || j2>=sizey ||
	  i3<0 || j3<0 || i3>=sizex || j3>=sizey ||
      i4<0 || j4<0 || i4>=sizex || j4>=sizey ||
	  i5<0 || j5<0 || i5>=sizex || j5>=sizey ||
      i6<0 || j6<0 || i6>=sizex || j6>=sizey )
  {
    //printf("Can't move - End\n");
    return;
  }

  if( isTraversed( tracebackStates, numState, i1, j1, i2, j2, i3, j3, i4, j4, i5, j5, i6, j6, fuc ) )
    return;

  if(pnt==2 && numState>*times){
	return;
  }


  //   SUCCESS !!
  if( i1 == i2 && j1 == j2 && i1 == sizex-1 && j2 == sizey -1 && (sizex-1)*(fuc[3])==i1+i2+i3+i4+i5+i6 && (sizey-1)*(fuc[3])==j1+j2+j3+j4+j5+j6)
  {
    if(pnt==1 && numState == *times && fuc[1]==1){
    for( i=0; i<numState; i++ )
    {
      displayBoard( board, sizex,sizey,
                      tracebackStates[i][0],
                      tracebackStates[i][1],
                      tracebackStates[i][2],
                      tracebackStates[i][3],
					  tracebackStates[i][4],
                      tracebackStates[i][5],
                      tracebackStates[i][6],
                      tracebackStates[i][7],
					  tracebackStates[i][8],
                      tracebackStates[i][9],
                      tracebackStates[i][10],
                      tracebackStates[i][11],
					  fuc );
    }
    displayBoard( board, sizex,sizey, i1, j1, i2, j2, i3, j3, i4, j4, i5, j5, i6, j6, fuc );
    printf("-------------------\n");
	}
	if(pnt==1 && numState == *times &&fuc[2]==1){
		if(fuc[1]==2){
			printf("-------------------\n");
		}
		printf("flatt in z a-xis : %d times\n",z);
		printf("flatt in x a-xis : %d times\n",x);
		printf("flatt in y a-xis : %d times\n",y);
		if(fuc[1]==2){
			printf("-------------------\n");
		}
	}
	
    (*numSolution)++;
    
  if((*times)==numState){
    	(*lesstimes)++;
	}
    
    if((*times)>numState){
    	(*times)=(numState);
    	(*lesstimes)=1;
	}

    return;
  }
  if((*times)<numState){
  	return;
  }

  //printf("It's in %d,%d - %d,%d\n", i1,j1, i2, j2 );

  //  Remember this position
    if(1<fuc[3]){
  	 	tracebackStates[numState][0] = i1;
  		tracebackStates[numState][1] = j1;
  		tracebackStates[numState][2] = i2;
 		tracebackStates[numState][3] = j2;
  	}
	if(2<fuc[3]){
  	 	tracebackStates[numState][4] = i3;
  		tracebackStates[numState][5] = j3;
  	}
  	if(3<fuc[3]){
  	 	tracebackStates[numState][6] = i4;
  		tracebackStates[numState][7] = j4;
  	}
  	if(4<fuc[3]){
  	 	tracebackStates[numState][8] = i5;
  		tracebackStates[numState][9] = j5;
  	}
	if(5<fuc[3]){
  	 	tracebackStates[numState][10] = i6;
  		tracebackStates[numState][11] = j6;
  	}
  
  numState++;
	int w3=0,w4=0,w5=0,w6=0,w,l1=1,l2=2,l3=0,l4=0,l5=0,l6=0,k1=0,k2=0,k3=0,k4=0,k5=0,k6=0;
	w=fuc[3];
	if(1<fuc[3]){
		k1=w-l1+1;
		k2=w-l2+1;
	}
	if(2<fuc[3]){
		w3=1;
		l3=3;
		k3=w-l3+1;
	}
	if(3<fuc[3]){
		w4=1;
		l4=4;
		k4=w-l4+1;
	}
	if(4<fuc[3]){
		w5=1;
		l5=5;
		k5=w-l5+1;
	}
	if(5<fuc[3]){
		w6=1;
		l6=6;
		k6=w-l6+1;
		}
  //displayBoard( board, size, i1, j1, i2, j2 );
  if( i1 == i2 && j1 == j2 )
  {
    //printf("It's standing\n");

    //  move up
    //printf("Moving up !\n");
    traverse( board, sizex, sizey, i1-k1, j1, i2-k2, j2, i3-k3, j3, i4-k4, j4, i5-k5, j5, i6-k6, j6, numSolution, tracebackStates, numState ,times,lesstimes,pnt,fuc,x,y+1,z);

    //  move down
    //printf("Moving down !\n");
    traverse( board, sizex, sizey, i1+l1, j1, i2+l2, j2, i3+l3, j3, i4+l4, j4, i5+l5, j5, i6+l6, j6, numSolution, tracebackStates, numState ,times,lesstimes,pnt,fuc,x,y+1,z);

    //  move left
    //printf("Moving left !\n");
    traverse( board, sizex, sizey, i1, j1-k1, i2, j2-k2, i3, j3-k3, i4, j4-k4, i5, j5-k5, i6, j6-k6, numSolution, tracebackStates, numState ,times,lesstimes,pnt,fuc,x+1,y,z);

    //  move right
    //printf("Moving right !\n");
    traverse( board, sizex, sizey, i1, j1+l1, i2, j2+l2, i3, j3+l3, i4, j4+l4, i5, j5+l5, i6, j6+l6, numSolution, tracebackStates, numState ,times,lesstimes,pnt,fuc,x+1,y,z);
  }

  //    it's flatting in X-Axis
  else if( i1 == i2 && j1+1 == j2 )
  {
    //printf("It's flatting in X-Axis\n");

    //  move up
    //printf("Moving up !\n");
    traverse( board, sizex, sizey, i1-1, j1, i2-1, j2, i3-w3, j3, i4-w4, j4, i5-w5, j5, i6-w6, j6, numSolution, tracebackStates, numState ,times,lesstimes,pnt,fuc,x+1,y,z);

    //  move down
    //printf("Moving down !\n");
    traverse( board, sizex, sizey, i1+1, j1, i2+1, j2, i3+w3, j3, i4+w4, j4, i5+w5, j5, i6+w6, j6, numSolution, tracebackStates, numState ,times,lesstimes,pnt,fuc,x+1,y,z);

    //  move left
    //printf("Moving left !\n");
    traverse( board, sizex, sizey, i1, j1-l1, i2, j2-l2, i3, j3-l3, i4, j4-l4, i5, j5-l5, i6, j6-l6, numSolution, tracebackStates, numState ,times,lesstimes,pnt,fuc,x,y,z+1);

    //  move right
    //printf("Moving right !\n");
    traverse( board, sizex, sizey, i1, j1+k1, i2, j2+k2, i3, j3+k3, i4, j4+k4, i5, j5+k5, i6, j6+k6, numSolution, tracebackStates, numState ,times,lesstimes,pnt,fuc,x,y,z+1);
  }

  //    it's flatting in Y-Axis
  else if( i1+1 == i2 && j1 == j2 )
  {
    //printf("It's flatting in Y-Axis\n");

    //  move up
    //printf("Moving up !\n");
    traverse( board, sizex, sizey, i1-l1, j1, i2-l2, j2, i3-l3, j3, i4-l4, j4, i5-l5, j5, i6-l6, j6, numSolution, tracebackStates, numState ,times,lesstimes,pnt,fuc,x,y,z+1);

    //  move down
    //printf("Moving down !\n");
    traverse( board, sizex, sizey, i1+k1, j1, i2+k2, j2, i3+k3, j3, i4+k4, j4, i5+k5, j5, i6+k6, j6, numSolution, tracebackStates, numState ,times,lesstimes,pnt,fuc,x,y,z+1);

    //  move left
    //printf("Moving left !\n");
    traverse( board, sizex, sizey, i1, j1-1, i2, j2-1, i3, j3-w3, i4, j4-w4, i5, j5-w5, i6, j6-w6, numSolution, tracebackStates, numState ,times,lesstimes,pnt,fuc,x,y+1,z);
    
    //  move right
    //printf("Moving right !\n");
    traverse( board, sizex, sizey, i1, j1+1, i2, j2+1, i3, j3+w3, i4, j4+w4, i5, j5+w5, i6, j6+w6, numSolution, tracebackStates, numState ,times,lesstimes,pnt,fuc,x,y+1,z);
  }
  else
  {
    printf("WRONG STATE !! Please Check %d,%d - %d,%d\n", i1, j1, i2, j2 );
  }
	
}

int end(times,numSolution,lesstimes)
{
	if(times==99999){
 	times=0;
 }
 
  printf("==================================\n");
  //printf("So, num solutions is %d\n", numSolution/2 );
  printf("less move is %d\n", times );
  printf("Have %d format \n",lesstimes/2);
  printf("==================================\n");
}
int func(int fuc[4]){
	printf("Show the way (1),not(2) : "  );
	scanf("%d",&fuc[1]);
	printf("Show the position of box (1),not(2) : ");
	scanf("%d",&fuc[2]);
	printf("leght of box : ");
	scanf("%d",&fuc[3]);
	
}
int main()
{
  int sizex;
  int sizey;
  int board[MAX_SIZEx][MAX_SIZEy];
  int numSolution = 0;
  int tracebackStates[MAX_STATE][12];
  int numState=0;
  int times=99999;
  int lesstimes=1;
  int pnt=0;
  int fuc[4];
  int z=0;
  int x=0;
  int y=0;
  // get board's size
  printf("Board Size (XxY): ");
  scanf("%d", &sizex );
  scanf("%d", &sizey );
  //get func
  func(fuc);
  //  initial board
  initialBoard( board, sizex, sizey );

  //  traverse
  traverse( board, sizex, sizey, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, &numSolution, tracebackStates, numState ,&times,&lesstimes,pnt,fuc,x,y,z);
  pnt=1;
  printf("Frist round complete\n");
  traverse( board, sizex, sizey, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, &numSolution, tracebackStates, numState ,&times,&lesstimes,pnt,fuc,x,y,z);
  //end
  end(times,numSolution,lesstimes);
  return 0;
}
