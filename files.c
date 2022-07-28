/******************************************************************************
 *
 * File Name: files.c
 * Authors:   Diogo Alves, Xavier Dias
 *
 *****************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "files.h"

#define FILE_EXT_IN ".puz"
#define FILE_EXT_OUT ".sol"

/******************************************************************************
 * fileExtension()
 *
 * Arguments: file_name (char*) - nome do ficheiro
 * Returns: ponteiro para a extensão do ficheiro ou NULL caso não exista
 * Side-Effects: (none)
 *
 * Description: Função que retorna a extensão de um ficheiro
 *
 *****************************************************************************/	
char* fileExtension(char* file_name)
{
	char *aux = file_name + strlen(file_name) - 1; /*ultimo caracter*/
	do{
		if(*aux == '.')
			return aux; 
		aux--;
	}while(aux >= file_name);
	return NULL;
}

/******************************************************************************
 * openFiles()
 *
 * Arguments: fp_in (FILE**) - ficheiro de entrada
			  fp_in (FILE**) - ficheiro de saída
			  fin_name (char*) - nome do ficheiro de entrada
 * Returns: (none)
 * Side-Effects: abre o ficheiro de entrada existente e cria o ficheiro de saída 
 *               com nome igual ao ficheiro de entrada, mas extensão .query
 *
 * Description: Função para abrir os ficheiros de entrada e saída
 *
 *****************************************************************************/	
void openFiles(FILE** fp_in, FILE** fp_out, char* fin_name)
{
	char* fout_name = NULL, *aux = NULL;
	
	if((strcmp(fileExtension(fin_name), FILE_EXT_IN)) != 0) exit(0);
	
	*fp_in = fopen(fin_name, "r");
	if(*fp_in == NULL) exit(0);
	
	fout_name = (char*) malloc( (strlen(fin_name) - strlen(FILE_EXT_IN) + strlen(FILE_EXT_OUT) + 1) * sizeof(char) );
	if(fout_name == NULL) exit(0);
	
	strcpy(fout_name, fin_name);
	aux = fileExtension(fout_name);
	*aux = '\0';
	strcat(fout_name, FILE_EXT_OUT);
	
	*fp_out = fopen(fout_name, "w");
	if(*fp_out == NULL) exit(0);
	
	free(fout_name);
}


/******************************************************************************
 * readDataFromFile()
 *
 * Arguments: fp (FILE*) - ficheiro que será lido
 * Returns: (-1) se atingir o fim do ficheiro, (0) se conseguir ler os dados corretamente
 * Side-Effects: lê os elemtentos que constituem cada linha do ficheiro(que pode ter  
 *			     mais que um problema)
 *
 * Description: Função para obter determinado elemento de um puzzle

 *****************************************************************************/
int readDataFromFile(FILE* fp, int* size, int*** grid, int* rule)
{
	int i;
	int j;
	int elem = -1; 
	
	/*leitura da primeira linha de um problema*/
    if( fscanf(fp, "%d %d", size, rule) == 2 )
	{			
		/*alocação de memória para uma matriz*/
		*grid = (int **) malloc( (*size)*sizeof(int *) );
		if(*grid == NULL) exit(0);

		/*leitura de cada elemento de uma matriz*/
		for(i = 0; i < (*size); i++)
		{
			(*grid)[i] = (int *) malloc( (*size)*sizeof(int ) );
			/*verificação de memória alocada*/
			if((*grid)[i] == NULL)
				exit(0);
			
			for(j = 0; j < (*size); j++)
			{
				if ( fscanf ( fp, "%d", &elem ) == 1)
				{
					(*grid)[i][j] = elem;
				}
			}
		}
		return 0;
	}
	freeGrid(grid, *size);
	return -1;
} 

/******************************************************************************
 * freeGrid()
 *
 * Arguments: grid (int***) - ponteiro para a matriz quadrada a ser liberta
			  size (int) - tamanho da matriz
 * Returns: (none)
 * Side-Effects: liberta uma matriz quadrada passada como argumento, que fica a apontar para NULL
 *
 * Description: Função para libertar uma matriz quadrada

 *****************************************************************************/
void freeGrid(int*** grid, int size)
{
	int i;
	if(*grid != NULL)
	{
		for(i = 0; i < size; i++)
		{
			if((*grid)[i] != NULL)
				free((*grid)[i]);
		}
	    free(*grid);
	}
	*grid = NULL;
}


/******************************************************************************
 * writeOutputFile()
 *
 * Arguments: fp (FILE*) - ficheiro em que será escrito
              size (int) - tamanho do puzzle a ser escrito
			  rule (int) - regra para preenchimento do puzzle
			  grind (int**) - matriz do puzzle
 * Returns: (none)
 * Side-Effects: escreve no ficheiro as variáveis passadas como argumentos da função
 *
 * Description: Função escrever a solução de um puzzle
 *
 *****************************************************************************/
void writeOutputFile(FILE* fp, int size, int rule, int** grid)
{
	int i, j;
	
	if(rule != 1 && rule != 2)
		fprintf(fp, "%d %d\n", size, rule);
	else if(grid == NULL) /*não ha solução*/
		fprintf(fp, "%d %d %d\n", size, rule, -1);
	else /*ha solução*/
	{
		fprintf(fp, "%d %d %d\n", size, rule, 1);
		for(i = 0; i < size; i++)
		{
			for(j = 0; j < size; j++)
			{
				fprintf(fp, "%d ", grid[i][j]);
			}
			fprintf(fp, "\n");
		}
	}
	
	fprintf(fp, "\n");
}