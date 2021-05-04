/*
 * Color.h
 *
 *  Created on: 4 may. 2021
 *      Author: Blanco Julián Agustín
 */

#ifndef COLOR_H_
#define COLOR_H_

#define QTY_COL 6
#define LONG_COLOUR 33

typedef struct{
	int idColorBarbijos;
	char colorBarbijos[LONG_COLOUR];
	int isEmpty;
}Color;

int col_init(Color* list, int len);
int col_altaForzada(Color* list, int len, char* name, char* lastName, char* cuit);
int col_findFree(Color* list, int len, int* pIndex);
int col_findById(Color* list, int len, int id, int* pIndex);
int col_colorFindById(Color* list, int len, int id, char* color);
int col_add(Color* list, int len);

#endif /* COLOR_H_ */
