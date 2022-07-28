/******************************************************************************
 *
 * File Name: stack.h
 * Authors:   Diogo Alves, Xavier Dias
 *
 *****************************************************************************/


#ifndef _STACK_H_
#define _STACK_H_

#include "Item.h"


typedef struct stack Stack;

Stack* StackInit();
void Push(Stack **s, Item i);
Item Pop(Stack **s);
int IsEmpty(Stack *s);
void emptyStack(Stack **s);

#endif