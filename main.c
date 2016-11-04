
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "decrypt.h"
#include "memwatch.h"

#define MAX 200
#define D_CONSTANT 1921821779
#define N_CONSTANT 4294434817
#define MW_STDIO
#define MEMWATCH

int ASCII_ARRAY[256];
char CHAR_ARRAY[256];

void initializeASCII();
void initializeInteger();
int lookUpCharacter(char c);
void removeChar( char str[] );   
void splitSix(char *arr, int length, char *str);
unsigned long long convertStringToCipher(char *str);
void convertBackToString(unsigned long long result, char *str);
unsigned long long modular_expo( unsigned long long base, unsigned long long exponent, unsigned long long modulus);
void storeGroupOfSixCharacters(char *arr, int starting_index, char *str);

FILE* fileOpen(char* filename, char* mode) {

  FILE* file_pointer = fopen(filename, mode);

  if (file_pointer == NULL) {

    fprintf(stderr, "ERROR: Unable to open file '%s'\n", filename);
    exit(13);
  }
  return file_pointer;

}

void fileClose(FILE* file_pointer) {

  if (fclose(file_pointer) != 0) {

    fprintf(stderr, "ERROR: Unable to close file!\n");
    exit(14);
  }

}

main (int argc, char **argv) {   

  initializeASCII();
  initializeInteger();

  FILE * pFile = NULL;    
  FILE * pFile2 = NULL; 

  char mystring[MAX];   
  char mystringWithSixCharacters[7];
  char resultString[MAX+1];
  char * str3;
  
  /* Check to make sure the command line arguments are there. */
  if (argc < 3) {

    printf("Usage: %s input.txt output.txt\n",
     argv[0]);
    exit(argc);
  }

  pFile = fileOpen (argv[1] , "r");    
  pFile2 = fileOpen (argv[2] , "w");    
  while ( fgets(mystring , sizeof(mystring) , pFile) != NULL ) {   

    removeChar(mystring);
    resultString[strlen(mystring)] = '\0';
    int i =0;

    int myStringLength = strlen(mystring);

    for (i=0; i< strlen(mystring);i+=6) {

      unsigned long long convert_to_cipher = 0;
      splitSix(mystring, strlen(mystring)-i, mystringWithSixCharacters);

      convert_to_cipher = convertStringToCipher(mystringWithSixCharacters);
      convert_to_cipher = modular_expo(convert_to_cipher, D_CONSTANT, N_CONSTANT);

      convertBackToString(convert_to_cipher, mystringWithSixCharacters);
      storeGroupOfSixCharacters(resultString, (strlen(mystring)-6-i), mystringWithSixCharacters);

      str3 = (char *) malloc(6 + strlen(resultString)+ strlen(mystringWithSixCharacters));
      strncpy(str3, resultString, strlen(resultString));
      strncpy(str3, mystringWithSixCharacters, 6);

      fputs(str3,pFile2); 
      free(str3);
    }  
  }   
  fileClose (pFile);    
  fileClose (pFile2);
}

void initializeASCII() {

  memset(ASCII_ARRAY, 0, 256); 
  ASCII_ARRAY[' '] = 0;
  ASCII_ARRAY['a'] = 1;
  ASCII_ARRAY['b'] = 2;
  ASCII_ARRAY['c'] = 3;
  ASCII_ARRAY['d'] = 4;
  ASCII_ARRAY['e'] = 5;
  ASCII_ARRAY['f'] = 6;
  ASCII_ARRAY['g'] = 7;
  ASCII_ARRAY['h'] = 8;
  ASCII_ARRAY['i'] = 9;
  ASCII_ARRAY['j'] = 10;
  ASCII_ARRAY['k'] = 11;
  ASCII_ARRAY['l'] = 12;
  ASCII_ARRAY['m'] = 13;
  ASCII_ARRAY['n'] = 14;
  ASCII_ARRAY['o'] = 15;
  ASCII_ARRAY['p'] = 16;
  ASCII_ARRAY['q'] = 17;
  ASCII_ARRAY['r'] = 18;
  ASCII_ARRAY['s'] = 19;
  ASCII_ARRAY['t'] = 20;
  ASCII_ARRAY['u'] = 21;
  ASCII_ARRAY['v'] = 22;
  ASCII_ARRAY['w'] = 23;
  ASCII_ARRAY['x'] = 24;
  ASCII_ARRAY['y'] = 25;
  ASCII_ARRAY['z'] = 26;
  ASCII_ARRAY['#'] = 27;
  ASCII_ARRAY['.'] = 28;
  ASCII_ARRAY[','] = 29;
  ASCII_ARRAY['\''] = 30;
  ASCII_ARRAY['!'] = 31;
  ASCII_ARRAY['?'] = 32;
  ASCII_ARRAY['('] = 33;
  ASCII_ARRAY[')'] = 34;
  ASCII_ARRAY['-'] = 35;
  ASCII_ARRAY[':'] = 36;
  ASCII_ARRAY['$'] = 37;
  ASCII_ARRAY['/'] = 38;
  ASCII_ARRAY['&'] = 39;
  ASCII_ARRAY['\\'] = 40;
}

void initializeInteger() {

  memset(CHAR_ARRAY, 0, 256); 
  CHAR_ARRAY[0] = ' ';
  CHAR_ARRAY[1] = 'a';
  CHAR_ARRAY[2] = 'b';
  CHAR_ARRAY[3] = 'c'; 
  CHAR_ARRAY[4] = 'd';
  CHAR_ARRAY[5] = 'e';
  CHAR_ARRAY[6] = 'f';
  CHAR_ARRAY[7] = 'g';
  CHAR_ARRAY[8] = 'h';
  CHAR_ARRAY[9] = 'i';
  CHAR_ARRAY[10] = 'j';
  CHAR_ARRAY[11] = 'k';
  CHAR_ARRAY[12] = 'l';
  CHAR_ARRAY[13] = 'm';  
  CHAR_ARRAY[14] = 'n';
  CHAR_ARRAY[15] = 'o';
  CHAR_ARRAY[16] = 'p';
  CHAR_ARRAY[17] = 'q';
  CHAR_ARRAY[18] = 'r';
  CHAR_ARRAY[19] = 's';  
  CHAR_ARRAY[20] = 't';
  CHAR_ARRAY[21] = 'u';
  CHAR_ARRAY[22] = 'v';
  CHAR_ARRAY[23] = 'w';  
  CHAR_ARRAY[24] = 'x';
  CHAR_ARRAY[25] = 'y';
  CHAR_ARRAY[26] = 'z';
  CHAR_ARRAY[27] = '#';
  CHAR_ARRAY[28] = '.';
  CHAR_ARRAY[29] = ','; 
  CHAR_ARRAY[30] = '\'';
  CHAR_ARRAY[31] = '!';
  CHAR_ARRAY[32] = '?';
  CHAR_ARRAY[33] = '(';  
  CHAR_ARRAY[34] = ')';
  CHAR_ARRAY[35] = '-';
  CHAR_ARRAY[36] = ':';
  CHAR_ARRAY[37] = '$';
  CHAR_ARRAY[38] = '/';
  CHAR_ARRAY[39] = '&'; 
  CHAR_ARRAY[40] = '\\';
}

int lookUpCharacter(char c) {

  return ASCII_ARRAY[c];
}

char convertToText(unsigned int c) {

  return CHAR_ARRAY[c];
}

void removeChar( char str[] ) {   

  int i=0,j=0; 
  int size;    
  size = strlen(str);    
  for(i=7; i<size; i+=8) { 

    for(j=i;j<size;j++) {

      str[j] = str[j+1]; 
    } 
    size--; 
    i--; 
  }    
}   

unsigned long long modular_expo( unsigned long long base, unsigned long long exponent, unsigned long long modulus) {
  
  unsigned long long result = 1;
  base = base % modulus;
  while (exponent > 0) {

    if (exponent % 2 == 1) {

      result = (result * base) % modulus;
    }
    exponent = exponent >> 1;
    base = (base * base) % modulus;
  }
  return result;
}

void splitSix(char *arr, int length, char *str) {

  int i = 0;
  int y = 0;

  for (i=0; i<6;i++) {

    str[y] = arr[i];
    y++;
  }
  str[6] = '\0';

  int c = 0;
  while (c < strlen(arr)) {

      arr[c] = arr[6+c];
      c++;
   }
   arr[c] = '\0';
}

unsigned long long convertStringToCipher(char *str) {

  int i = 0;
  int new_six_digit = 0;
  unsigned long long result = 0;
  for(i=0;i<6;i++) {

      new_six_digit = lookUpCharacter(str[i]);
      result += new_six_digit*(unsigned long long)(pow(41, (5-i)));
  }
  return result;
}

void convertBackToString(unsigned long long result, char *str) {

  unsigned long long store_floor;
  char new_char;
  int i = 0;
  for(i = 0; i<6; i++) {

    store_floor = floor(result / (unsigned long long)(pow(41, (5-i))));

    new_char = convertToText(store_floor);
    str[i] = new_char;
    result -= store_floor*(unsigned long long)(pow(41, (5-i)));
  }
  str[6] = '\0';
}

void storeGroupOfSixCharacters(char *arr, int starting_index, char *str) {

  int i = 0;
  for(i=0; i<6; i++) {

    arr[starting_index] = str[i];
    starting_index++;
  }
}