/******************************************************************************
 *
 * File Name: puzzlemngt.h
 * Authors:   Diogo Alves, Xavier Dias
 *
 *****************************************************************************/


#ifndef _PUZZLEMNGT_H_
#define _PUZZLEMNGT_H_

#include "puzzle.h"
#include "bigInts.h"

int checkAdjacent(puzzle* puz, int ln, int col, int val);
int isNotSolution(puzzle* puz, int ln, int col, int val);
puzzle* fillTrivialSolutions(puzzle* puz, int* num_empty);
int firstEmptySpace(puzzle* puz, int* ln, int* col);
int emptySpaces(puzzle* puz);

bigInt* columnCode(puzzle* puz, int col);
bigInt* lineCode(puzzle* puz, int ln);
bigInt** createCodeArray(int size);
void UpdateLineCodeArray(bigInt** line_codes, puzzle* puz, int variant);
void UpdateColmnCodeArray(bigInt** colmn_codes, puzzle* puz, int variant);
int checkRepeatedValues( bigInt** line_codes, bigInt** colmn_codes, int size);
puzzle* solvePuzzle(puzzle* p, int rule);

#endif