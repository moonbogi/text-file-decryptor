/****
 *
 * Filename:    decrypt.c
 *
 * Authors:     Hyung Jip Moon
 *
 * Project:     Text File Decryptor
 *
 * VersionDate: December 9, 2016
 *
 * Description: decrypt.c : Performs the decryption algorithm that decrypts  every 8th character (starting at position 8), thus, these characters should be removed. 
 							After performing that, the number of remaining characters should be a multiple of 6. 
 							Then, transform each group of 6 into an integer using base 41. 
 *
 ****/

#include "decrypt.h"
#include "memwatch.h"

//
//	Decrypt the given string and return it in the given buffer. 
//
void decrypt(char* inputString, char* outputString) {

    initializeASCII();
    initializeInteger();

    char* temp;
  	unsigned long long stringToCipher, cipherToString;
  	int groupBySix = 0;
  	int i;
	temp = malloc((strlen(inputString) + 1) * sizeof(char));
	memset(temp, 0, strlen(inputString) + 1);

  	removeEighthCharacter(inputString, temp);
	groupBySix = strlen(temp) / 6;

  	for (i = 0; i < groupBySix; i++) {

    	stringToCipher = convertStringToCipher(temp + i * 6);
    	cipherToString = modularPower(stringToCipher, D_CONSTANT, N_CONSTANT);
    	convertBackToString(cipherToString, outputString + i * 6);
    }
	free(temp);
}   

//
//	Remove every 8th character from the input string, then store them in the output buffer. 
//
void removeEighthCharacter(char* inputString, char* outputString) {

  int i;
  int size = strlen(inputString);
  for (i = 0; i < size; i++)
    if ( (i+1) % 8 ) {
      outputString[strlen(outputString)] = inputString[i];
    }
}

//
// Convert every character in a plain text string to cipher text characters.
// eg. a -> 1, b -> 2, c -> 3, d -> 4, ... , z -> 26
// Grouping them by 6 digits, power each digit from 5 to 0. 
// This process will end up giving extraneouly large number.
//
unsigned long long convertStringToCipher(char *str) {

  int i = 0;
  int everySixDigit = 0;
  unsigned long long result = 0;

  for(i = 0; i < 6; i++) {

    everySixDigit = lookUpCharacter(str[i]);
    result = result + everySixDigit * (unsigned long long)(pow(41, (5 - i)));
  }
  return result;
}

//  
// Helper function for looking up character from ASCII Table
//
int lookUpCharacter(char c) {

  return ASCII_TABLE_ARRAY[c];
}

//
// Map every character text to cipher text
//
void initializeASCII() {

	memset(ASCII_TABLE_ARRAY, 0, 256); 
	ASCII_TABLE_ARRAY[' '] = 0;
	ASCII_TABLE_ARRAY['a'] = 1;
	ASCII_TABLE_ARRAY['b'] = 2;
	ASCII_TABLE_ARRAY['c'] = 3;
	ASCII_TABLE_ARRAY['d'] = 4;
	ASCII_TABLE_ARRAY['e'] = 5;
	ASCII_TABLE_ARRAY['f'] = 6;
	ASCII_TABLE_ARRAY['g'] = 7;
	ASCII_TABLE_ARRAY['h'] = 8;
	ASCII_TABLE_ARRAY['i'] = 9;
	ASCII_TABLE_ARRAY['j'] = 10;
	ASCII_TABLE_ARRAY['k'] = 11;
	ASCII_TABLE_ARRAY['l'] = 12;
	ASCII_TABLE_ARRAY['m'] = 13;
	ASCII_TABLE_ARRAY['n'] = 14;
	ASCII_TABLE_ARRAY['o'] = 15;
	ASCII_TABLE_ARRAY['p'] = 16;
	ASCII_TABLE_ARRAY['q'] = 17;
	ASCII_TABLE_ARRAY['r'] = 18;
	ASCII_TABLE_ARRAY['s'] = 19;
	ASCII_TABLE_ARRAY['t'] = 20;
	ASCII_TABLE_ARRAY['u'] = 21;
	ASCII_TABLE_ARRAY['v'] = 22;
	ASCII_TABLE_ARRAY['w'] = 23;
	ASCII_TABLE_ARRAY['x'] = 24;
	ASCII_TABLE_ARRAY['y'] = 25;
	ASCII_TABLE_ARRAY['z'] = 26;
	ASCII_TABLE_ARRAY['#'] = 27;
	ASCII_TABLE_ARRAY['.'] = 28;
	ASCII_TABLE_ARRAY[','] = 29;
	ASCII_TABLE_ARRAY['\''] = 30;
	ASCII_TABLE_ARRAY['!'] = 31;
	ASCII_TABLE_ARRAY['?'] = 32;
	ASCII_TABLE_ARRAY['('] = 33;
	ASCII_TABLE_ARRAY[')'] = 34;
	ASCII_TABLE_ARRAY['-'] = 35;
	ASCII_TABLE_ARRAY[':'] = 36;
	ASCII_TABLE_ARRAY['$'] = 37;
	ASCII_TABLE_ARRAY['/'] = 38;
	ASCII_TABLE_ARRAY['&'] = 39;
	ASCII_TABLE_ARRAY['\\'] = 40;
}

//
//	Uses the algorithm called "exponentiation by squaring" to calculate the remainder when the modulus that is extremely large.
//	Referenced from : https://en.wikipedia.org/wiki/Modular_exponentiation
//
unsigned long long modularPower(unsigned long long base, unsigned long long exponent, unsigned long long modulus) {

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

//
// By peforming algorithm using 'modularPower' function, it will give group of extraneouly large number.
// Then, you convert those numbers back to string by using inverse of the function used in convertStringToCipher
//
void convertBackToString(unsigned long long result, char *str) {

  unsigned long long storeFloor;
  char newCharacter;
  int i = 0;
  for(i = 0; i < 6; i++) {

    storeFloor = floor(result / (unsigned long long)(pow(41, (5 - i))));
    newCharacter = convertToText(storeFloor);
    str[i] = newCharacter;
    result = result - storeFloor * (unsigned long long)(pow(41, (5 - i)));
  }
  str[6] = '\0';
}

//
// Map every cipher text to character text
//
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

//  
// Helper function for looking up cipher from chracter table
//
char convertToText(unsigned int c) {

  return CHAR_ARRAY[c];
}


