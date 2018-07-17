/*  Brandon Piper 
 *  sccADT.h 
 */

#ifndef __SCCADT_H__
#define __SCCADT_H__

typedef enum {false, true} boolean;

/* define the maximum number of vertices */
#define MAXVER 51

/* prints the strongly connected components of graph
 * which is represented by the graphs edges in the file */
void print_SCC(FILE* file);

/* performs dfs on a 2-d array */
void dfs(int graph[MAXVER][MAXVER]);

/* visits each adjacent vertex in a 2-d array */
void dfs_visit(int graph[MAXVER][MAXVER], int y);

/* finds the strongly connected components of a 2-d array */
void SCC(int graph[MAXVER][MAXVER]);

/* visits the adjacent vertices in the SCC traversal */
void scc_visit(int graph[MAXVER][MAXVER], int y);

#endif
