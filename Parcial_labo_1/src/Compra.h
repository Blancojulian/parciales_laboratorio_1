/*
 * Compra.h
 *
 *  Created on: 2 may. 2021
 *      Author: Blanco Julián Agustín
 */

#ifndef COMPRA_H_
#define COMPRA_H_

#define LONG_NAME 51
#define CUIT 12
#define QTY_COM 1001
#define LONG_COLOUR 33
#define LONG_DIRECTION 65
#define LONG_TEXTO 65//no
#define COBRADO 1
#define PENDIENTE 0
#define SI 1
#define NO 2


typedef struct{
	int idCliente;
	int idCompra;
	int cantidadBarbijos;
	int idColorBarbijos;
	char colorBarbijos[LONG_COLOUR];
	float precio;
	char direccion[LONG_DIRECTION];
	int estado;
	int isEmpty;

}Compra;

int compra_init(Compra* list, int len);
int compra_add(Compra* list, int len, Cliente* listCliente, int lenCliente);
int compra_clientAndBuysRemove(Compra* list, int len, Cliente* listCliente, int lenCliente);
int compra_changeStatus(Compra* list, int len, Cliente* listCliente, int lenCliente, int state);
int compra_showBuys(Compra* list,int index);
int compra_printByIdCliente(Compra* list, int len, Cliente* listCliente, int lenCliente, int id);
int compra_mostrarComprasCobradasOPausadas(Compra* list, int len, int state);
int compra_mostrarComprasCobradasOPausadasId(Compra* list, int len, int state, int id);
int compra_findById(Compra* list, int len, int id, int* pIndex);//agregar
int compra_findFree(Compra* list, int len, int* pIndex);
int compra_findBusy(Compra* list, int len);
int avi_sortByRubro(Compra* list, int len, int order);
int compra_altaForzada(Compra* list, int len, int idCliente, int rubro, char* texto);

#endif /* COMPRA_H_ */
