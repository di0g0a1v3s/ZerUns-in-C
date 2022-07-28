/******************************************************************************
 *
 * File Name: stack.c
 * Authors:   Diogo Alves, Xavier Dias
 *
 *****************************************************************************/


#include <stdlib.h>
#include "Item.h"
#include "stack.h"

/*pilha*/
struct stack {
	Item item; /*payload*/
	struct stack *next; /*próximo elemento da pilha*/
};

/******************************************************************************
 * StackInit()
 *
 * Arguments: (none)
 * Returns: (Stack*) Ponteiro para uma pilha vazia
 * Side-Effects: (none)
 *
 * Description: Função que inicializa uma pilha
 *
 *****************************************************************************/	
Stack* StackInit() 
{
	return NULL;
}

/******************************************************************************
 * Push()
 *
 * Arguments: s (Stack**) - Pilha onde irá ser inserido um elemento
			  i (Item) - Item a ser inserido na pilha
 * Returns: (none)
 * Side-Effects: aloca memória para um nó da pilha
 *
 * Description: Função que insere um elemento numa pilha
 *
 *****************************************************************************/	
void Push(Stack **s, Item i) 
{
	Stack* new_s = NULL;
	new_s = (Stack*) malloc(sizeof(Stack)); 
	if(new_s == NULL) exit(0);
	new_s->item = i;
	new_s->next = *s; /*novo elemento é inserido no inicio*/
	*s = new_s;
}

/******************************************************************************
 * Pop()
 *
 * Arguments: s (Stack**) - Pilha de onde irá ser retirado um elemento
 * Returns: (Item) - Elemento retirado da pilha (NULL caso não exista)
 * Side-Effects: Remove da pilha o primeiro elemento e liberta a memória associada ao nó
 *
 * Description: Função que retira da pilha o primeiro elemento
 *
 *****************************************************************************/	
Item Pop(Stack **s)
{
	if(*s == NULL) return NULL;
	Stack* aux = NULL;
	Item i = (*s)->item;
	aux = *s;
	*s = (*s)->next; /*elemento retirado do inicio*/
	free(aux);
	return i;
}

/******************************************************************************
 * IsEmpty()
 *
 * Arguments: s (Stack*) - Pilha em causa
 * Returns: (int) - 1 se a pilha estiver vazia, 0 se não estiver
 * Side-Effects: (none)
 *
 * Description: Função que indica se uma pilha está ou não vazia
 *
 *****************************************************************************/	
int IsEmpty(Stack *s) 
{
	if(s == NULL) return 1;
	return 0;
}



