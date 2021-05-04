/*
 * Cliente.h
 *
 *  Created on: 2 may. 2021
 *      Author: Blanco Julián Agustín
 */

#ifndef CLIENTE_H_
#define CLIENTE_H_

#define LONG_NAME 51
#define LONG_CUIT 12
#define QTY_CLI 100

typedef struct{
	int idCliente;
	char name[LONG_NAME];
	char lastName[LONG_NAME];
	char cuit[LONG_CUIT];
	int isEmpty;

}Cliente;

int cli_init(Cliente* list, int len);
int cli_add(Cliente* list, int len);
int cli_remove(Cliente* list, int len, int index);
int cli_modify(Cliente* list, int len);
int cli_print(Cliente* list, int len);
int cli_showClient(Cliente* list,int index);
int cli_findById(Cliente* list, int len, int id, int* pIndex);
int cli_findFree(Cliente* list, int len, int* pIndex);
int cli_findBusy(Cliente* list, int len);
int cli_sortByName(Cliente* list, int len, int order);
int cli_altaForzada(Cliente* list, int len, char* name, char* lastName, char* cuit);


#endif /* CLIENTE_H_ */
