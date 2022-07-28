/******************************************************************************
 *
 * File Name: puzzle.c
 * Authors:   Diogo Alves, Xavier Dias
 *
 *****************************************************************************/


#include <stdlib.h>
#include "puzzle.h"

/*estrutura que define um puzzle*/
struct _puzzle{
	int size; /*tamaho do puzzle*/
	int **grid; /*matriz de inteiros*/
};


/******************************************************************************
 * freePuzzle()
 *
 * Arguments: puz (puzzle**)  - puzzle a ser libertado
 * Returns: (none)
 * Side-Effects: toda a memória reservada para o puzzle é libertada, 
 *               puz fica a apontar para NULL
 *
 * Description: Função para libertar um elemento do tipo puzzle
 *
 *****************************************************************************/
void freePuzzle(puzzle** puz)
{
	int i;
	if((*puz) != NULL)
	{
		if((*puz)->grid != NULL)
		{
			for(i = 0; i < (*puz)->size; i++)
			{
				if(((*puz)->grid)[i] != NULL)
					free(((*puz)->grid)[i]);
			}
			free((*puz)->grid);
		}
		free(*puz);
	}
	*puz = NULL;
}

/******************************************************************************
 * initPuzzle()
 *
 * Arguments: size (int) - dimensão do puzzle (par)
			  grid (int**) - matriz (size*size) com os inteiros que irão ser os elementos do puzzle
 * Returns: (puzzle*) ponteiro para o puzzle criado
 * Side-Effects: reserva memória para e preenche os campos do puzzle (não reserva memória adicional para a matriz)
 *
 * Description: Função para inicializar um novo puzzle
 *
 *****************************************************************************/
puzzle* initPuzzle(int size, int** grid)
{
	puzzle *puz = NULL;
		
	puz = (puzzle*) malloc( sizeof(puzzle) );
	if(puz == NULL) exit(0);
	
	puz->size = size;
	
	puz->grid = grid; /*não é alocado espaço para uma nova matriz, é usada a passada como argumento da função*/
	
	return puz;
}

/******************************************************************************
 * copyPuzzle()
 *
 * Arguments: (puzzle*) puz - puzzle a ser copiado
 * Returns: (puzzle*) ponteiro para o puzzle criado
 * Side-Effects: reserva memória para um novo puzzle, incluindo a matriz, e preenche de modo a ficar igual ao puzzle passado como argumento
 *
 * Description: Função para efetuar uma cópia de um puzzle
 *
 *****************************************************************************/
puzzle* copyPuzzle(puzzle* puz)
{
	puzzle *new_puz = NULL;
	int i, j;
	if(puz == NULL) return NULL;
	new_puz = (puzzle*) malloc( sizeof(puzzle) );
	if(new_puz == NULL) exit(0);
	
	new_puz->size = puz->size;
	new_puz->grid = NULL;
	if(puz->grid == NULL) return new_puz;
	
	/*é alocado espaço para uma nova matriz*/
	new_puz->grid = (int**) malloc(new_puz->size * sizeof(int*));
	if(new_puz->grid == NULL)
	{
		freePuzzle(&new_puz);
		exit(0);
	}		
	
	for(i = 0; i < new_puz->size; i++)
	{
		(new_puz->grid)[i] = (int*) malloc(new_puz->size * sizeof(int));
		if((new_puz->grid)[i] == NULL)
		{
			freePuzzle(&new_puz);
			exit(0);
		}
		
		for(j = 0; j < new_puz->size; j++)
		{

			(new_puz->grid)[i][j] = (puz->grid)[i][j];
		}
	}
	return new_puz;
}
/******************************************************************************
 * getElement()
 *
 * Arguments: puz (puzzle*) - puzzle em causa
              ln (int) - linha do puzzle
			  col (int) - coluna do puzzle
 * Returns: elemento da coluna col e linha ln do puzzle (int)
 * Side-Effects: (none)
 *
 * Description: Função para obter determinado elemento de um puzzle
 *
 *****************************************************************************/
int getElement(puzzle *puz, int ln, int col)
{
	if(ln > puz->size || col > puz->size || ln <= 0 || col <= 0) return -1;
	return (puz->grid)[puz->size - ln][col - 1];
}

/******************************************************************************
 * insertElement()
 *
 * Arguments: puz (puzzle*) - puzzle em causa
              ln (int) - linha do puzzle
			  col (int) - coluna do puzzle
			  val (int) - valor a ser inserido no puzzzle
 * Returns: 1: se foi possivel inserir; -1: se não foi possivel inserir
 * Side-Effects: (none)
 *
 * Description: Função para inserir em determinadas coordenadas de um puzzle um elemento (val)
 *
 *****************************************************************************/
int insertElement(puzzle *puz, int ln, int col, int val)
{
	if(ln > puz->size || col > puz->size || ln <= 0 || col <= 0) return -1;
	(puz->grid)[puz->size - ln][col - 1] = val;
	return 1;
}



/******************************************************************************
 * not()
 *
 * Arguments: x (int) - valor binário
 * Returns: negação de x (ou -1 em caso de erro)
 * Side-Effects: (none)
 *
 * Description: Função para obter a negação do valor x
 *
 *****************************************************************************/
int not(int x)
{
	if(x == ONE)
		return ZERO;
	else if(x == ZERO)
		return ONE;
	else
		return -1;
}



/******************************************************************************
 * puzzleSize()
 *
 * Arguments: puz (puzzle*) - puzzle em causa
 * Returns: dimensão do puzzle (int)
 * Side-Effects: (none)
 *
 * Description: Função para obter a dimensão do puzzle
 *
 *****************************************************************************/
 int puzzleSize(puzzle* puz)
 {
	 if(puz != NULL)
	 	return puz->size;
	 else
		 return 0;
 }

 /******************************************************************************
 * puzzleGrid()
 *
 * Arguments: puz (puzzle*) - puzzle em causa
 * Returns: matriz que contém os elementos do puzzle (int**)
 * Side-Effects: (none)
 *
 * Description: Função para obter a matriz do puzzle
 *
 *****************************************************************************/
 int** puzzleGrid(puzzle* puz)
 {
	 if(puz != NULL)
	 	return puz->grid;
	 else
		 return NULL;
 }
 
 /******************************************************************************
 * numberOfXInLine()
 *
 * Arguments: puz (puzzle*) - puzzle em causa
			  x (int) - valor cujo numero de vezes se quer determinar (ZERO ou ONE ou EMPTY)
			  ln (int) - linha onde se quer procurar
 * Returns: número de vezes que o binário x aparece na linha ln (int)
 * Side-Effects: (none)
 *
 * Description: Função para obter a quantidade de vezes que um certo número aparece em determinada linha
 *
 *****************************************************************************/
 int numberOfXInLine(puzzle* puz, int x, int ln)
 {
	 int i = 0,counter = 0;
	 
	 for(i = 1; i <= puz->size; i++)
	 {
		 if(getElement(puz, ln, i) == x) counter++;
	 }
	 return counter;
 }
 
 /******************************************************************************
 * numberOfXInColmn()
 *
 * Arguments: puz (puzzle*) - puzzle em causa
			  x (int) - valor cujo numero de vezes se quer determinar (ZERO ou ONE ou EMPTY)
			  col (int) - coluna onde se quer procurar
 * Returns: número de vezes que o binário x aparece na coluna col (int)
 * Side-Effects: (none)
 *
 * Description: Função para obter a quantidade de vezes que um certo número aparece em determinada coluna
 *
 *****************************************************************************/
 int numberOfXInColmn(puzzle* puz, int x, int col)
 {
	 int i = 0,counter = 0;
	 
	 for(i = 1; i <= puz->size; i++)
	 {
		 if(getElement(puz, i, col) == x) counter++;
	 }
	 return counter;
 }
 

 
