/******************************************************************************
 *
 * File Name: zeruns.c
 * Authors:   Diogo Alves, Xavier Dias
 *
 *****************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include "puzzlemngt.h"
#include "puzzle.h"
#include "files.h"

int main(int argc, char** argv)
{
	puzzle* puz = NULL;
	puzzle* solved_puz = NULL;
	
	int size = 0; /*tamanho do puzzle*/
	int rule = 1; /*regra para resolver o puzzle (1 ou 2)*/
	int** grid = NULL; /*matriz do puzzle*/
	
	FILE* fp_in = NULL; /*ficheiro de entrada*/
	FILE* fp_out = NULL; /*ficheiro de saida*/
	
	if(argc != 2) exit(0);
	
	openFiles(&fp_in, &fp_out, argv[1]); /* abre o ficheiro de entrada e saida*/
		
	while( readDataFromFile(fp_in, &size, &grid, &rule) != -1 ) /*enquanto existirem puzzles no ficheiro*/
	{
		
		if(rule != 1 && rule != 2)
		{
			writeOutputFile(fp_out, size, rule, (int**)NULL);
			freeGrid(&grid, size);
			continue;
		}
		
		puz = initPuzzle(size, grid); /*inicializa o puzzle*/
		grid = NULL;
		
		
		
		solved_puz = solvePuzzle(puz, rule); /*resolve o puzzle*/
		
		writeOutputFile(fp_out, size, rule, puzzleGrid(solved_puz));	/*escreve no ficheiro a solução*/

		freePuzzle(&puz);		/*liberta a memoria dos puzzles*/
		freePuzzle(&solved_puz);
		
	}
	fclose(fp_in); /*fecha os ficheiros*/
	fclose(fp_out);
	
    return 0;		
}





		


