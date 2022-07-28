/******************************************************************************
 *
 * File Name: bigInts.h
 * Authors:   Diogo Alves, Xavier Dias
 *
 *****************************************************************************/

#ifndef _BIGINT_H_
#define _BIGINT_H_

typedef struct _bigInt bigInt;

bigInt* newBigInt(int num_bits);
int cmpBigInts(bigInt* first, bigInt* second);
void addBitRight(bigInt* b_int, int bit);
void freeBigInt(bigInt** b_int);

#endif