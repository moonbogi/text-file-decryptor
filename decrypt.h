/****
 *
 * Filename:    decrypt.h
 *
 * Authors:     Hyung Jip Moon
 *
 * Project:     Text File Decryptor
*
 * VersionDate: December 9, 2016
 *
 * Description: descrypt.h
 *
 ****/

#ifndef _DECRYPT_H_
#define _DECRYPT_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "memwatch.h"

#define D_CONSTANT 1921821779
#define N_CONSTANT 4294434817
#define MW_STDIO
#define MEMWATCH

int ASCII_TABLE_ARRAY[256];
char CHAR_ARRAY[256];

void decrypt(char* in_string, char* out_buffer);
void removeEighthCharacter(char* in_string, char* out_buffer);
unsigned long long convertStringToCipher(char* in_string);
int lookUpCharacter(char c);
void initializeASCII();
unsigned long long modularPower(unsigned long long base, unsigned long long exponent, unsigned long long modulus);
void convertBackToString(unsigned long long result, char *str);
void initializeInteger();
char convertToText(unsigned int c); 

#endif 




