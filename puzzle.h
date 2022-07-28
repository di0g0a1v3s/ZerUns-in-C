/******************************************************************************
 *
 * File Name: puzzle.h
 * Authors:   Diogo Alves, Xavier Dias
 *
 *****************************************************************************/


#ifndef _PUZZLE_H_
#define _PUZZLE_H_


#define ONE 1
#define ZERO 0
#define EMPTY 9

typedef struct _puzzle puzzle;

/**/void printPuzzle(puzzle* puz);
puzzle *initPuzzle(int size, int** grid);
puzzle* copyPuzzle(puzzle* puz);
int getElement(puzzle* puz, int ln, int col);
int insertElement(puzzle* puz, int ln, int col, int val);
int not(int x);
void freePuzzle(puzzle** puz);
int puzzleSize(puzzle* puz);
int numberOfXInLine(puzzle* puz, int x, int ln);
int numberOfXInColmn(puzzle* puz, int x, int col);
int** puzzleGrid(puzzle* puz);


 
 #endif