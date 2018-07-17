// Brandon Piper 
// sccADT.c - handles the graph abstraction for an adjacency.

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>
#include "sccADT.h"

#define WHITE 0
#define GRAY  1
#define BLACK 2

// Variable used by the functions that figure out the SCC's.
int scc[MAXVER];
int S_C_C[MAXVER];
int vertices[MAXVER];
int discover[MAXVER];
int finish[MAXVER];
int color[MAXVER];
int pred[MAXVER];
int timer = 0;

void print_SCC( FILE* file ){
  int x, y, num, index, key, temp;
  int adjacent [MAXVER][MAXVER];
  int transpose [MAXVER][MAXVER];
  
  // Initialize the adjacency and vertices matrix.
  for( y = 0; y < MAXVER; y++ ){
    for( x = 0; x < MAXVER; x++ ){
      adjacent[y][x] = 0;
      vertices[y] = 0;
    }
  } 
  
  // Uses character parsing algorithm to read two digit integers.
  num = getc( file );
  while( num < 48 || num > 57 )
    num = getc( file );
  while( num != EOF ){
    x = num - 48;
    num = getc( file );
    if( num > 47 && num < 58)
      x = ( x * 10 ) + ( num - 48 );
    vertices[x] = 1;
    
    num = getc( file );
    while( num < 48 || num > 57 )
      num = getc( file );
    y = num - 48;
    num = getc( file );
    if( num > 47 && num < 58 )
      y = ( y * 10 ) + ( num - 48 );
    vertices[y] = 1;   
    adjacent[x][y] = 1;
    
    num = getc( file );
    while( num == 10 || num == 32)
      num = getc( file );
  }
  
  // Print the adjacency matrix
  printf("\n- ADJACENCY -\n");
  for( y = 0; y < MAXVER; y++ ){
    if( vertices[y] == 1 )
      printf("%d : ", y);
    for( x = 0; x < MAXVER; x++ ){
      if( adjacent[y][x] == 1 && vertices[y] == 1 )
	printf("%d ", x);
    }
    if( vertices[y] == 1 )
      printf("\n");
  }
  
  // Call dfs on the graph.  
  dfs( adjacent );
  
  // Transpose the graph.
  for( y = 0; y < MAXVER; y++ ){
    for( x = 0; x < MAXVER; x++ ){
      if( adjacent[y][x] == 1 ){
	transpose[x][y] = 1;
      }
    }
  }
  
  // Call dfs on the transpose.
  dfs( transpose );
  
  // Sort the finish time array in decreasing order.
  for( x = 0; x < MAXVER; x++ ){
    index = key = 0;
    for( y = 1; y < MAXVER; y++ ){
      if( finish[y] != 0){
	    if( vertices[y] == 1 ){
	      if( y == 1){
	        key = finish[1];
	        index = 1;
	      }
	      else{
	        temp = finish[y];
	        if( temp > key ){
	          key = temp;
	          index = y;
	        }
	      }
	    }
      }
    }
    scc[x] = key;
    finish[index] = 0;
  }
  SCC( transpose );
}

void dfs( int graph[MAXVER][MAXVER] ){
  int y;
  for( y = 0; y < MAXVER; y++ ){
    if( vertices[y] == 1 ){
      color[y] = WHITE;
      pred[y] = 0;
    }
  }
  timer = 0;
  for( y = 0; y < MAXVER; y++ ){
    if( color[y] == WHITE )
      dfs_visit( graph, y );
  }
}

void dfs_visit( int graph[MAXVER][MAXVER], int y ){
  int x;
  color[y] = GRAY;
  if( vertices[y] == 1 )
    timer = timer+1;
  discover[y] = timer;
  
  for( x = 1; x < MAXVER; x++ ){
    if( graph[y][x] == 1 && color[x] == WHITE){
      pred[x] = y;
      dfs_visit( graph, x );
    }
  }
  color[y] = BLACK;
  if(vertices[y] == 1)
    timer = timer + 1;
  finish[y] = timer;
}

// Find the strongly connected components with modified dfs.
void SCC( int graph[MAXVER][MAXVER] ){
  printf("\n- STRONGLY CONNECTED COMPONENTS -\n");
  int y, index;
  for( y = 0; y < MAXVER; y++ ){
    if( vertices[y] == 1 ){
      color[y] = WHITE;
      pred[y] = 0;
    }
  }
  timer = 0;
  for( index = 0; scc[index] != 0; index++ ){
    if( color[index] == WHITE ){
      scc_visit( graph, index );
      printf("\n");
    }
  }
  printf("\n");
}

// Prints strongly connected componnents as they are visited.
void scc_visit( int graph[MAXVER][MAXVER], int y ){
  int x;
  color[y] = GRAY;
  if( vertices[y] == 1 )
    timer = timer + 1;
  discover[y] = timer;
  printf("%d ",y);
  
  for( x = 1; x < MAXVER; x++ ){
    if( graph[y][x] == 1 && color[x] == WHITE){
      pred[x] = y;
      scc_visit( graph, x );
    }
  }
  color[y] = BLACK;
  if( vertices[y] == 1 )
    timer = timer + 1;
  finish[y] = timer;
}
