/******************************************************************************
 *
 * File Name: bigInts.c
 * Authors:   Diogo Alves, Xavier Dias
 *
 *****************************************************************************/
 
#include <stdlib.h>
#include "bigInts.h"

/*número inteiro positivo de tamanho arbitrário*/
struct _bigInt{
	
	unsigned int* array; /*conjunto de inteiros em tabela*/
	int array_size; /*tamanho da tabela*/
};

/******************************************************************************
 * newBigInt()
 *
 * Arguments: num_bits (int) - número de bits pretendidos para o bigInt
 * Returns: (bigInt*) - ponteiro para o bigInt criado
 * Side-Effects: Aloca memória para o bigInt
 *
 * Description: Função para inicializar um inteiro de tamanho arbitrário a 0
 *
 *****************************************************************************/	
bigInt* newBigInt(int num_bits)
{
	int array_size, i;
	bigInt* b_int;
	
	b_int = (bigInt*) malloc(sizeof(bigInt));
	if(num_bits <= 0) return NULL;

	array_size = num_bits/(sizeof(unsigned int)*8); /*tamanho do vetor (número de unsigned ints necessários para representar num_bit bits)*/
	if(((float)num_bits/(sizeof(unsigned int)*8)) != num_bits/(sizeof(unsigned int)*8)) /*aproximação por excesso*/
	{
		array_size = array_size + 1;
	}
	
	b_int->array = (unsigned int*) malloc(array_size*sizeof(unsigned int));
	b_int->array_size = array_size;
	
	for(i = 0; i < array_size; i++)
		b_int->array[i] = (unsigned int)0; /*inicializado a 0*/
	
	return b_int;
	
}

/******************************************************************************
 * addBitRight()
 *
 * Arguments: b_int (bigInt*) - inteiro ao qual será adicionado o bit
			  bit (int) - booleano (0 ou 1) a ser adicionado à direita de b_int
 * Returns: (none)
 * Side-Effects: Altera o conteudo da posição de memória apontada por b_int
 *
 * Description: Função para adicionar um bit à direita de um inteiro de tamanho arbitrário
 *
 *****************************************************************************/
void addBitRight(bigInt* b_int, int bit)
{
	int i, aux;
	int carry = bit & (unsigned int)1; /*bit que é transportado do fim de uma entrada da tabela para a próxima*/
	for(i = 0; i < b_int->array_size; i++)
	{
		aux = ((unsigned int)1) << (sizeof(unsigned int)*8 - 1); /*1000...00*/
		aux = aux & (b_int->array[i]);
		aux = aux >> (sizeof(unsigned int)*8 - 1); /*aux é o bit mais significativo da entrada i da tabela*/
		b_int->array[i] = b_int->array[i] << 1; /*shift left*/
		(b_int->array[i]) = (b_int->array[i]) | carry; /*adição do bit à direita*/
		carry = aux; /*novo carry passa a ser aux*/
	}
}

/******************************************************************************
 * cmpBigInts()
 *
 * Arguments: first (bigInt*) - primeiro inteiro
			  first (bigInt*) - segundo inteiro
 * Returns: (int) 0 se os inteiros forem diferentes e 1 se forem iguais
 * Side-Effects: (none)
 *
 * Description: Função que informa se dois inteiros de tamanho arbitrário são iguais ou diferentes
 *
 *****************************************************************************/
int cmpBigInts(bigInt* first, bigInt* second)
{
	int i;
	
	if(first->array_size != second->array_size) return 0; /*assume-se que dois inteiros têm que ocupar o mesmo espaço em memória para serem iguais*/
	
	for(i = 0; i < first->array_size; i++)
	{
		if(first->array[i] != second->array[i]) return 0; /*todos os elementos dos dois vetores têm que ser iguais entre si*/
	}
	
	return 1;
	
}

/******************************************************************************
 * freeBigInt()
 *
 * Arguments: b_int (bigInt**) - inteiro de tamanho variável a ser libertado
 * Returns: (none)
 * Side-Effects: liberta a memória associada a *b_int e põe esta variável a apontar para NULL
 *
 * Description: Função que liberta um interio de tamanho arbitrário
 *
 *****************************************************************************/
void freeBigInt(bigInt** b_int)
{
	if(*b_int != NULL)
	{
		if((*b_int)->array != NULL)
		{
			free((*b_int)->array);
		}
		free((*b_int));
	}
	*b_int = NULL;
}