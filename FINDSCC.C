/*  Brandon Piper 
 *  
 *  Main reads in a file from command line argv[1]
 *  and sends the file to the Strongly Connected 
 *  Components ADT and the SCC's are printed out.
 */

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>
#include "sccADT.h"

int main(int argc, char** argv){
  
  FILE* file = fopen(argv[1], "r");
  if(file == NULL){
    printf("usage: findSCC [inputFile]\n");
    exit(1);
  }
  print_SCC(file);
  return 0;
}

