/****
 *
 * Filename:    main.c
 *
 * Authors:     Hyung Jip Moon
 *
 * Project:     Text File Decryptor
 *
 * VersionDate: December 9, 2016
 *
 * Description: main.c : Handles program initialization and Entry point of the overall program. 
 *
 ****/

#include "decrypt.h"
#include "memwatch.h"

#define MAX 256

//
// Modify the fopen function that checks for errors and exits the program.
//
FILE* fileOpen(char* fileName, char* type) {

  FILE* filePointer = fopen(fileName, type);

  if (filePointer == NULL) {

    fprintf(stderr, "ERROR: Unable to open file '%s'\n", fileName);
    exit(13);
  }
  return filePointer;
}

//
// Modify the fclose function that checks for errors and exits the program
//
void fileClose(FILE* filePointer) {

  if (fclose(filePointer) != 0) {

    fprintf(stderr, "ERROR: Unable to close file!\n");
    exit(14);
  }
}

//
// Entry point of the program. 
//
main (int argc, char **argv) {   

  FILE * inputFile = NULL;    
  FILE * outputFile = NULL; 

  char inputString[MAX]={0};   
  char outputString[MAX+1] ={0};
  
  // Check to make sure the command line arguments are there. 
  if (argc < 3) {

    printf("Usage: %s input.txt output.txt\n", argv[0]);
    exit(argc);
  }

  inputFile = fileOpen (argv[1] , "r");    
  outputFile = fileOpen (argv[2] , "w");   

  while (feof(inputFile) == 0) {

    fgets(inputString, sizeof(inputString), inputFile);

    if(strlen(inputString) == 0 && feof(inputFile)) break;

    decrypt(inputString, outputString);
    fputs(outputString, outputFile);
    fputc('\n', outputFile);
    memset(outputString, 0, MAX);
  }
  fileClose(inputFile);
  fileClose(outputFile);
}