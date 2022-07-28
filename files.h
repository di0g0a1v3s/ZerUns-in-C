/******************************************************************************
 *
 * File Name: files.h
 * Authors:   Diogo Alves, Xavier Dias
 *
 *****************************************************************************/


#ifndef _FILES_H_
#define _FILES_H_


char* fileExtension(char* file_name);
int readDataFromFile(FILE* fp, int* size, int* **grid, int* rule);
void writeOutputFile(FILE* fp, int size, int rule, int** grid);
void openFiles(FILE** fp_in, FILE** fp_out, char* fin_name);
void freeGrid(int*** grid, int size);

#endif