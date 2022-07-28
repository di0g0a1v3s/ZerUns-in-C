/******************************************************************************
 *
 * File Name: puzzlemngt.c
 * Authors:   Diogo Alves, Xavier Dias
 *
 *****************************************************************************/


#include <stdlib.h>
#include "puzzlemngt.h"
#include "puzzle.h"
#include "stack.h"
#include "Item.h"
#include "bigInts.h"

 /******************************************************************************
 * emptySpaces()
 *
 * Arguments: puz (puzzle*) - puzzle em causa
 * Returns:	(int) - número de posições vazias
 * Side-Effects: (none)
 *
 * Description: Função que retorna o número de posições vazias de um puzzle
 *
 *****************************************************************************/ 
int emptySpaces(puzzle* puz)
{
	int ln, col;
	int num_empty = 0;
	for(ln = 1; ln <= puzzleSize(puz); (ln)++)
	{
		for(col = 1; col <= puzzleSize(puz); (col)++)
		{
			if(getElement(puz, ln, col) == EMPTY) 
			{
				num_empty++;
			}
		}
	}
	return num_empty;
}

 /******************************************************************************
 * firstEmptySpace()
 *
 * Arguments: puz (puzzle*) - puzzle em causa
 * Returns: (int) ln - linha correspondente à primeira posição vazia
 			(int) col - coluna correspondente à primeira posição vazia
			(int) - 1 se encontrar alguma posição vazia
			        0 se não existirem posições vazias
 * Side-Effects: (none)
 *
 * Description: Função para obter as coordenadas da primeira posição vazia de um puzzle
 *
 *****************************************************************************/ 
int firstEmptySpace(puzzle* puz, int* ln, int* col)
{
	int ln_, col_;
	for(ln_ = 1; ln_ <= puzzleSize(puz); (ln_)++)
	{
		for(col_ = 1; col_ <= puzzleSize(puz); (col_)++)
		{
			if(getElement(puz, ln_, col_) == EMPTY) 
			{
				*ln = ln_;
				*col = col_;
				return 1;
			}
		}
	}
	return 0;
}

/******************************************************************************
* checkAdjacent()
*
* Arguments: puz (puzzle*) - puzzle em causa
			  ln (int) - linha do puzzle
			  col (int) - coluna do puzzle
			  val (int) - valor binário
* Returns: (-1) se a insersão de val nas coordenadas (ln,col) irá significar que existem mais de 2 valores iguais seguidos
*		   (0) caso contrário
* Side-Effects: (none)
*
* Description: Função que determina se a insersão de val nas coordenadas (ln,col) irá significar que existem mais de 2 valores iguais seguidos
*
*****************************************************************************/
int checkAdjacent(puzzle* puz, int ln, int col, int val)
{
	/*vefificação dos valores nas duas casas seguintes em todas as direções*/
	if(getElement(puz, ln-1, col) == val && getElement(puz, ln-2, col) == val)
		return -1;
	if(getElement(puz, ln+1, col) == val && getElement(puz, ln+2, col) == val)
		return -1;
	if(getElement(puz, ln, col+1) == val && getElement(puz, ln, col+2) == val)
		return -1;
	if(getElement(puz, ln, col-1) == val && getElement(puz, ln, col-2) == val)
		return -1;
	/*verificação dos valores adjacentes nos dois sentidos*/
	if(getElement(puz, ln, col-1) == val && getElement(puz, ln, col+1) == val)
		return -1;
	if(getElement(puz, ln-1, col) == val && getElement(puz, ln+1, col) == val)
		return -1;
	
	return 0;
}

 /******************************************************************************
 * isNotSolution()
 *
 * Arguments: puz (puzzle*) - puzzle em causa
			  ln (int) - linha do puzzle
			  col (int) - coluna do puzzle
			  val (int) - valor binário que se pretende determinar se é solução
 * Returns: (1) se o valor binário NÂO for de certeza solução do problema nas coordenadas em causa, 
 			(0) caso contrário
 * Side-Effects: (none)
 *
 * Description: Função para descobrir se determinado número não é, de certeza, solução do problema em determinadas coordenadas
 *
 *****************************************************************************/ 
int isNotSolution(puzzle* puz, int ln, int col, int val)
{	
	/*se o número de zeros/uns em cada linha coluna for superior a metade do 
	tamanho do puzzle ou se existirem mais de dois valores seguidos após a 
	inserção de val nas coordenadas (ln, col), então val não é de certeza solução*/
	if(numberOfXInLine(puz, val, ln) >= puzzleSize(puz) / 2 || 
	   numberOfXInColmn(puz, val, col) >= puzzleSize(puz) / 2 ||
	   checkAdjacent(puz,ln,col,val) == -1)
		return 1;
	else 
	   return 0;
}



 /******************************************************************************
 * fillTrivialSolutions()
 *
 * Arguments: puz (puzzle*) - puzzle a ser preenchido
			  num_empty (int*) - posição de memória que contém o número de posições vazias
 * Returns: (puzzle*) ponteiro para o puzzle resultante ou NULL caso o puzzle seja impossivel de resolver
 * Side-Effects: altera o conteudo do puzzle passado como argumentoe atualiza o numero de posições vazias
 *
 * Description: Função que preenche no puzzle passado todas as soluções triviais
 *
 *****************************************************************************/ 
puzzle* fillTrivialSolutions(puzzle* puz, int* num_empty)
{
	int ln, col, zero, one, change = 0;
	
	do{
	    change = 0; /*indica se o puzzle sofreu alterações durante o cilco*/
		for(ln = 1; ln <= puzzleSize(puz); ln++)
		{
			for(col = 1; col <= puzzleSize(puz); col++)
			{
				if(getElement(puz, ln, col) != EMPTY)
					continue;
				one = isNotSolution(puz, ln, col, ONE);
				zero = isNotSolution(puz, ln, col, ZERO);
				
				if(one == 1 && zero == 0) /* 0 é solução trivial*/
				{
					insertElement(puz, ln, col, ZERO);
					(*num_empty)--;
					change = 1;
				}
				else if(zero == 1 && one == 0)/* 1 é solução trivial */
				{
					insertElement(puz, ln, col, ONE);
					(*num_empty)--;
					change = 1;
				}
				else if(zero == 1 && one == 1) /* o puzzle não tem solução */
				{
					return NULL;
				}
					
			}
		}
	}while(change == 1);
	return puz;
}

/******************************************************************************
 * columnCode()
 *
 * Arguments: puz (puzzle*) - puzzle em causa
			  col (int) - coluna do puzzle
 * Returns: (bigInt*) codificação do conteúdo da coluna
 * Side-Effects: aloca espaço para um bigInt
 *
 * Description: Função que retorna um inteiro de tamanho arbitrário com a codificação presente de uma coluna do puzzle
 *
 *****************************************************************************/
bigInt* columnCode(puzzle* puz, int col)
{
	int i; 
	int size = puzzleSize(puz);
	bigInt* col_code = newBigInt(size);
	
	/*a codificação da coluna corresponde ao número binário 
	cujos bits são as entradas da coluna*/
	for(i = 1; i <= size; i++)
	{
		addBitRight(col_code, getElement(puz, i, col));
	}
	return col_code;
}


/******************************************************************************
 * lineCode()
 *
 * Arguments: puz (puzzle*) - puzzle em causa
			  ln (int) - coluna do puzzle
 * Returns: (bigInt*) codificação do conteúdo da linha
 * Side-Effects: aloca espaço para um bigInt
 *
 * Description: Função que retorna um inteiro de tamanho arbitrário com a codificação presente de uma linha do puzzle
 *
 *****************************************************************************/
bigInt* lineCode(puzzle* puz, int ln)
{
	int i; 
	int size = puzzleSize(puz);
	bigInt* ln_code = newBigInt(size);
	
	/*a codificação da linha corresponde ao número binário 
	cujos bits são as entradas da linha*/
	for(i = 1; i <= size; i++)
	{
		addBitRight(ln_code, getElement(puz, ln, i));
	}
	return ln_code;
}

/******************************************************************************
 * createCodeArray()
 *
 * Arguments: size (int) - tamanho do vetor
 * Returns: (bigInt**) - vetor de (ponteiros para) inteiros de tamanho arbitrário
 * Side-Effects: aloca espaço para uma tabela de ponteiros para bigInt
 *
 * Description: Função cria uma tabela para inteiros de tamanho arbitrário
 *
 *****************************************************************************/
bigInt** createCodeArray(int size)
{
	int i = 0;
	
	bigInt** array = (bigInt**) malloc(size*sizeof(bigInt*));
	
	for(i = 0; i < size; i++)
		array[i] = NULL;
	
	return array;
}


/******************************************************************************
 * UpdateLineCodeArray()
 *
 * Arguments: line_codes (bigInt**) - vetor de inteiros de tamanho arbitrário com a codificação das linhas
			  puz (puzzle*) - puzzle com a informação atualizada
			  variant (int) - será 1 se adicionar informação ao vetor ou 0 se quisermos remover informação 
			  do vetor que esteja desatualizada
 * Returns: (none)
 * Side-Effects: altera o conteúdo do vetor
 *
 * Description: Função que atualiza no vetor line_codes a codificação das linhas do puzzle
 *
 *****************************************************************************/
void UpdateLineCodeArray(bigInt** line_codes, puzzle* puz, int variant)
{
	int i;
	
	for(i = 1; i <= puzzleSize(puz); i++)
	{
		/*o código é atualizado se:
		a posição referente a essa linha no vetor não estiver vazia mas existirem espaços vazios nessa linha do puzzle*/ 
		if( variant == 2 && line_codes[i-1] != NULL && numberOfXInLine(puz, EMPTY, i) != 0)
		{
			freeBigInt(&(line_codes[i-1]));
			line_codes[i-1] = NULL;
		}
		/*a posição referente a essa linha no vetor estiver vazia mas não existirem espaços vazios nessa linha do puzzle*/
		if( variant == 1 && line_codes[i-1] == NULL && numberOfXInLine(puz, EMPTY, i) == 0 )
			line_codes[i-1] = lineCode(puz, i);
		
	}
}

/******************************************************************************
 * UpdateColmnCodeArray()
 *
 * Arguments: colmn_codes (bigInt**) - vetor de inteiros de tamanho arbitrário com a codificação das colunas
			  puz (puzzle*) - puzzle com a informação atualizada
			  variant (int) - será 1 se adicionar informação ao vetor ou 0 se quisermos remover informação 
			  do vetor que esteja desatualizada
 * Returns: (none)
 * Side-Effects: altera o conteúdo do vetor
 *
 * Description: Função que atualiza no vetor colmn_codes a codificação das colunas do puzzle
 *
 *****************************************************************************/
void UpdateColmnCodeArray(bigInt** colmn_codes, puzzle* puz, int variant)
{
	int i;
	
	for(i = 1; i <= puzzleSize(puz); i++)
	{
		/*o código é atualizado se:
		a posição referente a essa coluna no vetor não estiver vazia mas existirem espaços vazios nessa coluna do puzzle*/ 
		if( variant == 2 && colmn_codes[i-1] != NULL && numberOfXInColmn(puz, 9, i) != 0)
		{
			freeBigInt(&(colmn_codes[i-1]));
			colmn_codes[i-1] = NULL;
		}
		/*a posição referente a essa coluna no vetor estiver vazia mas não existirem espaços vazios nessa coluna do puzzle*/
		if( variant == 1 && colmn_codes[i-1] == NULL && numberOfXInColmn(puz, 9, i) == 0 )
			colmn_codes[i-1] = columnCode(puz, i);
		
	}
}

/******************************************************************************
 * checkRepeatedValues()
 *
 * Arguments: colmn_codes (bigInt**) - vetor de inteiros de tamanho arbitrário com a codificação das colunas
			  line_codes (bigInt**) - vetor de inteiros de tamanho arbitrário com a codificação das linhas
			  size (int) - tamanho dos vetores
 * Returns: (int) - 1 se existirem elementos repitidos, 0 caso contrário
 * Side-Effects: (none)
 *
 * Description: Função que verifica se existem valores repetidos no vetor com a codificação das linhas e no das colunas
 *
 *****************************************************************************/
int checkRepeatedValues( bigInt** line_codes, bigInt** colmn_codes, int size)
{
	int i, j;
	
	for(i = 0; i < size - 1; i++)
	{
		for(j = i + 1; j < size; j++)
		{
			if( line_codes[i] != NULL && line_codes[j] != NULL && cmpBigInts(line_codes[i], line_codes[j]) == 1 ) /*iguais*/
				return 1;
		
			if( colmn_codes[i] != NULL && colmn_codes[j] != NULL && cmpBigInts(colmn_codes[i], colmn_codes[j]) == 1 ) /*iguais*/
				return 1;
		}
	}

	return 0;
	
}



/******************************************************************************
 * solvePuzzle()
 *
 * Arguments: p (puzzle*) - puzzle a resolver
			  rule (int) - regra para a resolução do puzzle (1 ou 2)
 * Returns: (puzzle*) - puzzle resolvido ou NULL caso não tenha solução
 * Side-Effects: aloca memória para o puzzle resolvido
 *
 * Description: Função que resolve um puzzle consoante uma determinada regra
 *
 *****************************************************************************/
puzzle* solvePuzzle(puzzle* p, int rule)
{
	bigInt** line_codes = NULL;
	bigInt** colmn_codes = NULL;
	puzzle* puz = copyPuzzle(p); /*cria uma cópia do puzzle*/
	puzzle* aux = NULL;
	Stack *s = StackInit(); /*inicialização da pilha*/
	int solved = 0; /*indica se o puzzle está resolvido (1), não está (0) ou não tem solução (-1)*/
	int ln = 1, col = 1, i;
	int num_empty = emptySpaces(puz);
	/*inicialização dos vetores com os códigos das linhas e colunas do puzzle*/
	if(rule == 2)
	{
		colmn_codes = createCodeArray(puzzleSize(p));
		line_codes = createCodeArray(puzzleSize(p));
	}
		
	while(solved == 0)
	{
		aux = fillTrivialSolutions(puz, &num_empty); /*preenche o puzzle com as soluções triviais*/
		
		/*atualiza os códigos das linhas e colunas*/
		if(rule == 2)
		{
			UpdateLineCodeArray(line_codes, puz, 1);
			UpdateColmnCodeArray(colmn_codes, puz, 1);
		}
		
		if(aux == NULL) /*caso o puzzle não tenha solução na configuração atual*/
		{
			freePuzzle(&puz);
		}
		else if(rule == 2 && checkRepeatedValues(line_codes, colmn_codes, puzzleSize(puz)) == 1) /*caso existam linhas/colunas repetidas*/
		{
			freePuzzle(&puz);
			aux = NULL;
		}
		
		puz = aux;
		
		if(puz == NULL)/*caso o puzzle não tenha solução na configuração atual*/
		{
			if(IsEmpty(s))/*se o stack estiver vazio, não existe solução*/
				solved = -1;
			else
			{
				puz = (puzzle*) Pop(&s); /*retira o primeiro puzzle do stack*/
				num_empty = emptySpaces(puz);
				if(rule == 2)/*atualiza os códigos das linhas e colunas*/
				{
					UpdateLineCodeArray(line_codes, puz, 2);
					UpdateColmnCodeArray(colmn_codes, puz, 2);
				}
				firstEmptySpace(puz, &ln, &col);
				insertElement(puz, ln, col, ZERO); /*coloca um 0 na primeira posição vazia*/
				(num_empty)--;
			}
		}
		else if(num_empty == 0)/*se estiver totalmente preenchido, está necessariamente resolvido*/
		{
			solved = 1;
		}
		else
		{
			Push(&s, (Item)copyPuzzle(puz)); /*guarda a configuração atual do puzzle no stack*/
			firstEmptySpace(puz, &ln, &col);
			insertElement(puz, ln, col, ONE);/*coloca um 1 na primeira posição vazia*/
			(num_empty)--;
		}
		
	}
	
	while((aux = (puzzle*) Pop(&s)) != NULL) /*liberta toda a memória presente na pilha*/
	{
		freePuzzle(&aux);
	}
	
	if(rule == 2)/*liberta toda a memória associada aos vetores dos códigos das linhas e colunas*/
	{
		for(i = 0; i < puzzleSize(puz); i++)
		{
			freeBigInt(&(line_codes[i]));
			freeBigInt(&(colmn_codes[i]));
		}
		free(line_codes);
		free(colmn_codes);
	}	
	
	if(solved == 1)
		return puz; /*puzzle resolvido*/
	else
		return NULL;
}

