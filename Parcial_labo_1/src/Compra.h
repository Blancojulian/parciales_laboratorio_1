/*
 * Compra.h
 *
 *  Created on: 2 may. 2021
 *      Author: Planton1911
 */

#ifndef COMPRA_H_
#define COMPRA_H_

#define LONG_NAME 51
#define CUIT 12
#define QTY_COM 1000
#define LONG_COLOUR 32
#define LONG_DIRECTION 64

typedef struct{
	int idCliente;
	int cantidadBarbijos;
	char colorBarbijos[LONG_COLOUR];
	float precio;
	char direccion[LONG_DIRECTION];
	int isEmpty;

}Compra;

int compra_init(Compra* list, int len);
int compra_add(Compra* list, int len, Cliente* listCliente, int lenCliente);
int compra_clientAndAdsRemove(Compra* list, int len, Cliente* listCliente, int lenCliente);
int compra_changeStatus(Compra* list, int len, Cliente* listCliente, int lenCliente, int state);
int avi_showAds(Compra* list,int index);
int compra_printByIdCliente(Compra* list, int len, Cliente* listCliente, int lenCliente, int id);
int avi_mostrarAvisosPausadosOActivos(Cliente* list, int len, int state);
int avi_mostrarAvisosPausadosOActivosPorId(Cliente* list, int len, int state, int id);
int compra_findById(Cliente* list, int len, int id, int* pIndex);
int compra_findFree(Cliente* list, int len, int* pIndex);
int compra_findBusy(Cliente* list, int len);
int avi_sortByRubro(Cliente* list, int len, int order);
int compra_altaForzada(Cliente* list, int len, int idCliente, int rubro, char* texto);

#endif /* COMPRA_H_ */
